package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

const (
	cmdRegister = "/reg"
	cmdMessage  = "/msg"
	cmdUsers    = "/users"
	cmdUser     = "/user"
	cmdTime     = "/time"
	cmdKick     = "/kick"
)

var (
	allCommands = []string{cmdRegister, cmdMessage, cmdUsers, cmdUser, cmdTime, cmdKick}

	reader = bufio.NewReader(os.Stdin)
)

func main() {

	username := flag.String("user", "", "your chat name")
	server := flag.String("server", "localhost:9000", "the server to connect to")
	flag.Parse()

	if *username == "" {
		fmt.Println("user must be passed")
		return
	}

	connection, err := net.Dial("tcp", *server)
	if err != nil {
		log.Fatalf("Unable to connect to '%s' - '%s'", *server, err)
	}

	// read from connection
	go func() {
		buffer := make([]byte, 4096)
		for {
			bytesRead, err := connection.Read(buffer)
			if err != nil {
				if io.EOF == err {
					log.Fatal("Connection closed by server")
					return
				}
				log.Fatal(err)
			}
			fmt.Printf("\r                                                    \r%s\n", string(buffer[:bytesRead]))
			fmt.Printf("%s > ", *username)
		}
	}()

	// write to connection
	go func() {
		register(connection, *username)

		for {
			fmt.Printf("%s > ", *username)
			text, err := reader.ReadString('\n')
			if err != nil {
				log.Fatal(err)
			}

			sendMessage(connection, text)
		}
	}()

	select {}
}

func register(connection net.Conn, name string) {
	message := fmt.Sprintf("%s %s", cmdRegister, name)
	if _, err := connection.Write([]byte(message)); err != nil {
		log.Fatal(err)
	}
}

func sendMessage(connection net.Conn, text string) {
	// convert CRLF to LF
	text = strings.ReplaceAll(text, "\n", "")
	if !messageIsCommand(text) {
		text = fmt.Sprintf("%s all %s", cmdMessage, text)
	}

	if _, err := connection.Write([]byte(text)); err != nil {
		log.Fatal(err)
	}
}

func messageIsCommand(text string) bool {
	for _, command := range allCommands {
		if strings.HasPrefix(text, command) {
			return true
		}
	}
	return false
}
