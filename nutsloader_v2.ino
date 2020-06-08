#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>

std::vector<String> knownSSIDs = {"TP-LINK_408C", "TP-LINK_96CB"};
std::vector<String> wifiKeys = {"47462687", "36C5E6C939"};
int wifiStatus = WL_IDLE_STATUS;  // Wifi radio status

const String GET_FUEL_LEVEL_CMD_TYPE = "LEV";
const String START_REFILL_CMD_TYPE = "REF";
const String STOP_CMD_TYPE = "STOP";

HTTPClient httpClient;

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  pinMode(26, OUTPUT);

  while (1) {
    // Scan for networks to connect to.
    Serial.println("Scanning available networks...");
    int foundNetsCount = WiFi.scanNetworks();

    // If there isn't any available network, retry again in 5 seconds.
    if (foundNetsCount == -1) {
      Serial.println("No available networks found. Retrying in 5 seconds.");
      delay(5000);
      continue;
    }

    // Search for the best network to connect to.
    // An electable network must be within the known array. The network
    // having the best signal index will be choosen.
    String bestKnownNetSSID = "";
    int bestKnownNetSignal = -999;
    for (int i = 0; i < foundNetsCount; i++) {
      String ssid = WiFi.SSID(i);
      // Check if the ssid is within the known ones, if not continue
      // searching for a known network.
      if (std::find(knownSSIDs.begin(), knownSSIDs.end(), ssid) ==
          knownSSIDs.end()) {
        continue;
      }

      // Check if the network signal is better than the last known network
      // found.
      // If it is, overwrite the best known network's ssid.
      // If it's not, skip this ssid.
      int signal = WiFi.RSSI(i);
      if (signal < bestKnownNetSignal) {
        continue;
      }
      bestKnownNetSSID = ssid;
      bestKnownNetSignal = signal;
    }

    // If there isn't any known network, retry again in 5 seconds.
    if (bestKnownNetSSID.isEmpty()) {
      Serial.println("No known networks found. Retrying in 5 seconds.");
      delay(5000);
      continue;
    }

    // Try connecting to the network found.
    int selectedNetIndex = std::distance(
        knownSSIDs.begin(),
        std::find(knownSSIDs.begin(), knownSSIDs.end(), bestKnownNetSSID));

    char ssidCharArray[bestKnownNetSSID.length() + 1];
    bestKnownNetSSID.toCharArray(ssidCharArray, bestKnownNetSSID.length() + 1);

    String selectedNetKey = wifiKeys[selectedNetIndex];
    char keyCharArray[selectedNetKey.length() + 1];
    selectedNetKey.toCharArray(keyCharArray, selectedNetKey.length() + 1);

    while (wifiStatus != WL_CONNECTED) {
      Serial.print("Attempting to connect to network having SSID: ");
      Serial.println(bestKnownNetSSID + "SIG: " + bestKnownNetSignal);
      wifiStatus = WiFi.begin(ssidCharArray, keyCharArray);
      delay(2000);
    }
    Serial.println("Wifi connected.");
    break;
  }
}

void loop() {
  String nextCommand = fetchNextCommand();
  if (nextCommand != "") {
    Serial.println(nextCommand);
    String* commandParts = unpackCommand(nextCommand);
    String clientID = commandParts[0];
    String requestID = commandParts[1];
    String commandType = commandParts[2];
    String error;
    String result;
    if (commandType == GET_FUEL_LEVEL_CMD_TYPE) {
      // Read from sensor
      result = "{\"level\":90}";
    }
    if (commandType == START_REFILL_CMD_TYPE) {
      // Read from sensor
      result = "{}";
      error = "";
      digitalWrite(26, HIGH);
    }
    if (commandType == STOP_CMD_TYPE) {
      // Read from sensor
      result = "{}";
      error = "";
      digitalWrite(26, LOW);
    }
    completeCommand(clientID, requestID, commandType, result, error);
  }
}

String buildResponse(String clientID, String requestID, String commandType,
                     String result = "", String error = "") {
  return "{\"clientID\":\"" + clientID + "\",\"requestID\":\"" + requestID +
         "\",\"commandType\":\"" + commandType + "\",\"result\":" + result +
         ",\"error\":\"" + error + "\"}";
}

String fetchNextCommand() {
  httpClient.begin("http://192.168.1.108:8080/nutsify/rest/commands");

  int statusCode = httpClient.GET();

  String command = "";
  if (statusCode == 200) {
    command = httpClient.getString();
  } else {
    Serial.println(statusCode);
    Serial.println(httpClient.errorToString(statusCode).c_str());
  }
  return command;
}

String* unpackCommand(String command) {
  String* parts = new String[3];
  int partIndex = 0;
  String temp;

  int commandLength = command.length();
  for (int i = 0; i < commandLength; i++) {
    char charAtIndex = command.charAt(i);
    if (charAtIndex == '_') {
      parts[partIndex] = temp;
      temp = "";
      partIndex++;
      continue;
    }
    temp.concat(charAtIndex);
    if (i == commandLength - 1) {
      parts[partIndex] = temp;
      break;
    }
  }

  return parts;
}

bool completeCommand(String clientID, String requestID, String commandType,
                     String result, String error) {
  httpClient.begin("http://192.168.1.108:8080/nutsify/rest/commands");

  String response =
      buildResponse(clientID, requestID, commandType, result, error);
  int statusCode = httpClient.POST(response);

  if (statusCode == 200) {
    return true;
  } else {
    Serial.print("response");
    Serial.println(statusCode);
    Serial.println(httpClient.errorToString(statusCode).c_str());
    return false;
  }
}