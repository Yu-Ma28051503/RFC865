package main

import (
	"fmt"
	"net"
	"os"
)

func runUDPClient() error {
	fmt.Println("Starting UDP Client")

	conn, err := net.Dial("udp", "localhost:17")
	if err != nil {
		fmt.Println("Error connecting:", err)
		return err
	}
	defer conn.Close()

	conn.Write([]byte(""))

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
	if err := runUDPClient(); err != nil {
		fmt.Println("UDP client exited with error:", err)
		os.Exit(1)
	}
}
