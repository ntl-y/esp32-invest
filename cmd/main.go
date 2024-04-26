package main

import (
	"fmt"
	"math/rand"
	"net/http"
)

const (
	port = ":8999"
)

func main() {

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		randomNumber := rand.Intn(100) + 1
		response := fmt.Sprintf(`{"random_number": %d}`, randomNumber)
		fmt.Fprint(w, response)
	})

	fmt.Printf("start server at %s", port)
	http.ListenAndServe(port, nil)
}
