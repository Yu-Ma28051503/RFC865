package main

import (
	"crypto/rand"
	"fmt"
	"math/big"
	"net"
	"os"
	"time"
	"strings"
)

const quotes = `"The only way to do great work is to love what you do." - Steve Jobs
"Life is what happens when you're busy making other plans." - John Lennon
"Do not watch the clock. Do what it does. Keep going." - Sam Levenson
"Success is not the key to happiness. Happiness is the key to success." - Albert Schweitzer
"Believe you can and you're halfway there." - Theodore Roosevelt
"Do not watch the clock. Do what it does. Keep going." - Sam Levenson`

func getQuote() (string, error) {
	quotes := strings.Split(quotes, "\n")
	n, err := rand.Int(rand.Reader, big.NewInt(int64(len(quotes))))
	if err != nil {
		return "", err
	}
	return quotes[n.Int64()], nil
}

func getDay() int {
	now := time.Now()
	day := time.Date(now.Year(), now.Month(), now.Day(), 0, 0, 0, 0, now.Location())

	return day.Day()
}

func runTCPServer() error {
	quote, err := getQuote()
	if err != nil {
		fmt.Println("Error getting quote:", err)
		return err
	}
	fmt.Println("Today's quote:", quote)

	day := getDay()

	fmt.Println("Starting TCP Server")

	s, err := net.Listen("tcp", ":17")
	if err != nil {
		fmt.Println("Error listening:", err)
		return err
	}
	defer s.Close()

	for {
		conn, err := s.Accept()
		if err != nil {
			fmt.Println("Error accepting connection:", err)
			continue
		}

		now := getDay()
		if now != day {
			day = now
			quote, err = getQuote()
			if err != nil {
				fmt.Println("Error getting quote:", err)
				continue
			}
		}

		go func(c net.Conn) {
			defer c.Close()

			_, err = c.Write([]byte(quote + "\n"))
			if err != nil {
				fmt.Println("Error writing to connection:", err)
			}
		}(conn)
	}
}

func main() {
	if err := runTCPServer(); err != nil {
		fmt.Println("TCP server exited with error:", err)
		os.Exit(1)
	}
}
