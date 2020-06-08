package main

import (
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"nutsify"
)

type nutsifyRESTService struct {
	nutsifyInstance nutsify.Nutsify
}

func newNutsifyRESTService(n nutsify.Nutsify) nutsifyRESTService {
	return nutsifyRESTService{
		nutsifyInstance: n,
	}
}

func (ns *nutsifyRESTService) commandAPIHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		nextCommand := ns.nutsifyInstance.FetchNextCommand()
		w.Header().Set("Content-Type", "text/plain; charset=UTF-8")

		_, err := io.WriteString(w, nextCommand)
		if err != nil {
			w.WriteHeader(http.StatusInternalServerError)
			return
		}

	case http.MethodPost:
		responseBody, err := ioutil.ReadAll(r.Body)
		defer r.Body.Close()
		if err != nil {
			w.WriteHeader(http.StatusInternalServerError)
			return
		}
		fmt.Println(string(responseBody))

		var commandResponse nutsify.CommandResponse
		err = json.Unmarshal(responseBody, &commandResponse)
		if err != nil {
			fmt.Println(err)
			w.WriteHeader(http.StatusInternalServerError)
			return
		}

		err = ns.nutsifyInstance.CompleteCommand(commandResponse)
		if err != nil {
			fmt.Println(err)
			w.WriteHeader(http.StatusInternalServerError)
			return
		}

		w.WriteHeader(http.StatusOK)
	}
}
