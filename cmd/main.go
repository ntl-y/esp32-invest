package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

func main() {
	port := ":8999"
	key := "CG-Wwke7hzEzDqubwat4rf86LrN"
	url := "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin%2Cethereum%2Cthe-open-network&vs_currencies=usd&precision=5"

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")

		response := makeRequest(url, key)
		w.Write(response)
	})

	fmt.Printf("start server at %s", port)
	http.ListenAndServe(port, nil)
}

func makeRequest(url string, key string) []byte {
	client := &http.Client{}
	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		log.Fatalf("Error creating request: %v", err)
	}

	req.Header.Add("accept", "application/json")
	req.Header.Add("x-cg-demo-api-key", key)

	resp, err := client.Do(req)
	if err != nil {
		log.Fatalf("Error making request: %v", err)
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatalf("Error reading response body: %v", err)
	}
	return body
}
