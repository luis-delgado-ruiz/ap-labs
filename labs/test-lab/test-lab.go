package main

import (
	"fmt"
	"os"
)

func main() {
  if len(os.Args[0:]) > 1{
    fmt.Println("Welcome to the jungle", os.Args[1:])
  } else {
    fmt.Println("Error: No name passed")
  }
}
