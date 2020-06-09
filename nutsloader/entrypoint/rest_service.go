package main

import (
	"encoding/json"
	"fmt"
	"github.com/MarcoBramini/NutsLoader/nutsloader"
	"io"
	"io/ioutil"
	"net/http"
)

type nutsloaderRESTService struct {
	nutsloaderInstance nutsloader.NutsLoader
}

func newNutsloaderRESTService(n nutsloader.NutsLoader) nutsloaderRESTService {
	return nutsloaderRESTService{
		nutsloaderInstance: n,
	}
}

func (ns *nutsloaderRESTService) commandAPIHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		nextCommand := ns.nutsloaderInstance.FetchNextCommand()
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

		var commandResponse nutsloader.CommandResponse
		err = json.Unmarshal(responseBody, &commandResponse)
		if err != nil {
			fmt.Println(err)
			w.WriteHeader(http.StatusInternalServerError)
			return
		}

		err = ns.nutsloaderInstance.CompleteCommand(commandResponse)
		if err != nil {
			fmt.Println(err)
			w.WriteHeader(http.StatusInternalServerError)
			return
		}

		w.WriteHeader(http.StatusOK)
	}
}
