package main

import (
	"fmt"
	"net"
	"os"
	"crypto/rand"
	"math/big"
	"strings"
	"time"
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

func runUDPServer() error {
	quote, err := getQuote()
	if err != nil {
		return err
	}
	fmt.Println("Today's quote:", quote)

	day := getDay()

	fmt.Println("Starting UDP Server")

	s, err := net.ListenPacket("udp", ":17")
	if err != nil {
		fmt.Println("Error listening:", err)
		return err
	}
	defer s.Close()

	for {
		var buf [512]byte
		n, addr, err := s.ReadFrom(buf[:])
		if err != nil {
			fmt.Println("Error reading:", err)
			continue
		}

		now := getDay()
		if now != day {
			day = now
			newQuote, err := getQuote()
			if err != nil {
				fmt.Println("Error getting quote:", err)
				continue
			}
			quote = newQuote
			fmt.Println("Today's quote:", quote)
		}

		go func(a net.Addr, data []byte) {
			_, err = s.WriteTo([]byte(quote+"\n"), a)
			if err != nil {
				fmt.Println("Error writing:", err)
			}
		}(addr, buf[:n])
	}
}

func main() {
	if err := runUDPServer(); err != nil {
		fmt.Println("UDP server exited with error:", err)
		os.Exit(1)
	}
}
