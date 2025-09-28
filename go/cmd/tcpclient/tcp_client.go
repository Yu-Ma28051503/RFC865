package main

import (
	"fmt"
	"net"
	"os"
)

func runTCPClient() error {
	fmt.Println("Starting TCP Client")

	conn, err := net.Dial("tcp", "localhost:17")
	if err != nil {
		fmt.Println("Error connecting:", err)
		return err
	}
	defer conn.Close()

	var recv [512]byte
	n, err := conn.Read(recv[:])
	if err != nil {
		fmt.Println("Error reading:", err)
		return err
	}

	fmt.Println(string(recv[:n]))

	return nil
}

func main() {
	if err := runTCPClient(); err != nil {
		fmt.Println("TCP client exited with error:", err)
		os.Exit(1)
	}
}
