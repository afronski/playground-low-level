package main

import (
	"fmt"
	"time"
	"net/http"
	"io/ioutil"
	"math/rand"
)

func root (response http.ResponseWriter, request *http.Request) {
	rand.Seed(time.Now().UnixNano())

	data, _ := ioutil.ReadFile("./index.html")
	body := string(data)

	answers := []string{
		"Watch one movie from Vimeo 'Watch Later' playlist",
		"Watch one movie from Youtube 'Watch Later' playlist",
		"Watch one movie from UStream 'Watch Later' playlist",

		"Read one article from the 'Pending' list",

		"Write one easy program in Erlang (99 problems)",
		"Write one easy program in Clojure (99 problems)",
		"Write one easy program in Go (99 problems)",
		"Write one easy program in Prolog (99 problems)",

		"Read the book - Distributed Systems for fun and profit",
		"Read the book - Learn You Some Erlang for great good!",
		"Read the book - Code Connected volume 1",
		"Read the book - Learn the C in hard way",

		"TDD Kata in Erlang",
		"TDD Kata in JavaScript",
		"TDD Kata in C#",

		"Pattern Kata in C#",
		"Pattern Kata in Java",

		"Write one assignment from 'Learn you some Erlang for great good!'",
		"Write one assignment from 'Learn C the hard way'",
		"Write one assignment from 'Structure and Interpretation of Computer Programs'",
		"Write one assignment from 'Distributed Systems'",

		"Prepare one article to the blog",
		"Prepare one assignment about HTML5 / CSS3 / JavaScript",
	}

	fmt.Fprintf(response, body, answers[rand.Intn(len(answers))])
}

func css (response http.ResponseWriter, request *http.Request) {
	http.ServeFile(response, request, "./style.css")
}

func js (response http.ResponseWriter, request *http.Request) {
	http.ServeFile(response, request, "./script.js")
}

func favicon (response http.ResponseWriter, request *http.Request) {
	http.ServeFile(response, request, "./favicon.png")
}

func main() {
	http.HandleFunc("/", root)

	http.HandleFunc("/style.css", css)
	http.HandleFunc("/script.js", js)
	http.HandleFunc("/favicon.png", favicon)

	err := http.ListenAndServe("0.0.0.0:80", nil)

	if err != nil {
		fmt.Printf("ListenAndServe Error: %s", err)
	}
}