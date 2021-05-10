package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"net"
	"strings"
	"time"
)

const (
	cmdRegister = "/reg"
	cmdMessage  = "/msg"
	cmdUsers    = "/users"
	cmdUser     = "/user"
	cmdTime     = "/time"
	cmdKick     = "/kick"
)

const (
	serverName = "irc-server"
)

var (
	connectedUsers       = make(map[net.Conn]*user)
	adminUser      *user = nil
)

func main() {
	host := flag.String("host", "localhost", "the ip the server should bind to")
	port := flag.Int("port", 9000, "the port the server should bind to")
	flag.Parse()

	listener, err := net.Listen("tcp", fmt.Sprintf("%s:%d", *host, *port))
	if err != nil {
		log.Fatalf("Unable to start tcp server: %s", err)
	}

	defer listener.Close()
	log.Printf("Simple IRC Server started at '%s:%d'", *host, *port)

	for {
		connection, err := listener.Accept()
		if err != nil {
			log.Fatalf("Error accepting new connections: %s", err)
		}

		go handleConnection(connection)
	}
}

func handleConnection(connection net.Conn) {
	defer connection.Close()

	isFirstMessage := true

	buffer := make([]byte, 4096)

	for {
		bytesRead, err := connection.Read(buffer)
		if err != nil {

			if io.EOF == err {
				log.Printf("[%s] left", connectedUsers[connection].name)
				if adminUser == connectedUsers[connection] {
					adminUser = nil
				}
				delete(connectedUsers, connection)
				checkForAdmin()
				break
			}
			log.Printf("Error reading message: %s", err)
			break
		}
		message := strings.TrimSpace(string(buffer[:bytesRead]))

		if isFirstMessage {
			if !strings.HasPrefix(message, cmdRegister) {
				log.Printf("Closing connection from '%s'. First message must be '%s'", connection.RemoteAddr(), cmdRegister)
				break
			}
			username := strings.TrimSpace(strings.ReplaceAll(message, cmdRegister, ""))
			if existingUser := getUserByUsername(username); existingUser != nil {
				sendServerMessage(connection, fmt.Sprintf("[%s] is already taken by another user", username))
				break
			}

			newUser := user{
				name:      username,
				loginTime: time.Now(),
				isAdmin:   false,
				ip:        connection.RemoteAddr().String(),
			}

			broadcastServerMessage(fmt.Sprintf("New connected user [%s]", username))

			connectedUsers[connection] = &newUser
			isFirstMessage = false

			sendWelcomeMessage(connection, username)

			log.Printf("New connected user [%s]", username)
			checkForAdmin()
		}

		handleMessage(connection, message)
	}
}

func checkForAdmin() {
	if adminUser != nil {
		return
	}

	if len(connectedUsers) == 0 {
		return
	}

	var possibleAdminUser *user = nil

	for _, user := range connectedUsers {
		if possibleAdminUser == nil {
			possibleAdminUser = user
		}

		if possibleAdminUser.loginTime.Before(user.loginTime) {
			possibleAdminUser = user
		}
	}

	if adminUser == possibleAdminUser {
		return
	}

	if possibleAdminUser == nil {
		return
	}

	adminUser = possibleAdminUser
	adminUser.isAdmin = true
	connection := getConnectionByUsername(possibleAdminUser.name)
	sendYouAreAdminMessage(connection)
	log.Printf("[%s] was promoted as the channel ADMIN", possibleAdminUser.name)
}

func handleMessage(connection net.Conn, message string) {
	messageParts := strings.SplitN(message, " ", 2)
	if len(messageParts) < 1 {
		return
	}

	command := messageParts[0]
	switch command {
	case cmdMessage:
		if len(messageParts) != 2 {
			return
		}
		messageCommand(connection, messageParts[1])
	case cmdUsers:
		usersCommand(connection)
	case cmdUser:
		if len(messageParts) != 2 {
			return
		}
		userCommand(connection, messageParts[1])
	case cmdTime:
		timeCommand(connection)
	case cmdKick:
		if len(messageParts) != 2 {
			return
		}
		kickCommand(connection, messageParts[1])
	}
}

func sendWelcomeMessage(connection net.Conn, username string) {
	sendServerMessage(connection, "Welcome to the Simple IRC Server\n")
	sendServerMessage(connection, fmt.Sprintf("Your user [%s] is successfully logged\n", username))
}

func sendYouAreAdminMessage(connection net.Conn) {
	sendServerMessage(connection, "Congrats, you were the first user.\n")
	sendServerMessage(connection, "You're the new IRC Server ADMIN\n")
}

func sendServerMessage(connection net.Conn, textToSend string) {
	message := fmt.Sprintf("%s > %s", serverName, textToSend)
	if _, err := connection.Write([]byte(message)); err != nil {
		log.Println(err)
	}
}

func sendUserMessage(connection net.Conn, userFromName, textToSend string) {
	message := fmt.Sprintf("%s > %s", userFromName, textToSend)
	if _, err := connection.Write([]byte(message)); err != nil {
		log.Println(err)
	}
}

func broadcastServerMessage(textToSend string) {
	for connection, _ := range connectedUsers {
		sendServerMessage(connection, textToSend)
	}
}

func broadcastUserMessage(connectionFrom net.Conn, textToSend string) {
	user, exists := connectedUsers[connectionFrom]
	if !exists {
		return
	}

	for connection, _ := range connectedUsers {
		if connection == connectionFrom {
			continue
		}
		sendUserMessage(connection, user.name, textToSend)
	}
}

func messageCommand(connection net.Conn, message string) {
	messageParts := strings.SplitN(message, " ", 2)
	if len(messageParts) < 2 {
		return
	}

	userTo := messageParts[0]
	messageToSend := messageParts[1]

	if userTo == "all" {
		broadcastUserMessage(connection, messageToSend)
	} else {
		userFrom := getUserByConnection(connection)
		if userFrom == nil {
			return
		}

		if connectionTo := getConnectionByUsername(userTo); connectionTo != nil {
			sendUserMessage(connectionTo, userFrom.name, messageToSend)
		}
	}
}

func usersCommand(connection net.Conn) {
	for _, user := range connectedUsers {
		message := fmt.Sprintf("%s - connected since %s", user.name, user.loginTime.Format(time.RFC3339))
		sendServerMessage(connection, message)
	}
}

func userCommand(connection net.Conn, username string) {
	user := getUserByUsername(username)
	if user == nil {
		sendServerMessage(connection, fmt.Sprintf("user with name [%s] not found", username))
		return
	}

	message := fmt.Sprintf("username: %s, IP: %s Connected since %s", user.name, user.ip, user.loginTime.Format(time.RFC3339))
	sendServerMessage(connection, message)
}

func timeCommand(connection net.Conn) {
	message := fmt.Sprintf("Local Time: %s", time.Now().Format("15:04"))
	sendServerMessage(connection, message)
}

func kickCommand(connection net.Conn, username string) {
	if adminUser := getUserByConnection(connection); !adminUser.isAdmin {
		sendServerMessage(connection, "you must be the admin to kick other users")
		return
	}

	connectionToKick := getConnectionByUsername(username)
	if connectionToKick == nil {
		sendServerMessage(connection, fmt.Sprintf("user with name [%s] not found", username))
		return
	}

	sendServerMessage(connection, fmt.Sprintf("[%s] was kicked from channel for bad language policy violation", username))
	if err := connectionToKick.Close(); err != nil {
		log.Println(err)
	}
	log.Printf("[%s] was kicked\n", username)
}

func getUserByConnection(con net.Conn) *user {
	for connection, user := range connectedUsers {
		if connection == con {
			return user
		}
	}
	return nil
}

func getConnectionByUsername(username string) net.Conn {
	for connection, user := range connectedUsers {
		if strings.ToLower(user.name) == strings.ToLower(username) {
			return connection
		}
	}
	return nil
}

func getUserByUsername(username string) *user {
	for _, user := range connectedUsers {
		if strings.ToLower(user.name) == strings.ToLower(username) {
			return user
		}
	}
	return nil
}

type user struct {
	name      string
	loginTime time.Time
	isAdmin   bool
	ip        string
}
