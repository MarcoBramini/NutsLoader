#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <NewPing.h>
#include <NutsloaderService.h>
#include <PubSubClient.h>
#include <TimerSwitch.h>
#include <WiFi.h>

const uint cochleaSwitchPin = 19;
const uint levelSonarEchoPin = 12;
const uint levelSonarTriggerPin = 14;

NewPing levelSonar(levelSonarTriggerPin, levelSonarEchoPin, 400);
TimerSwitch cochleaSwitch(cochleaSwitchPin, 600000);

NutsloaderService
    nutsloaderService(&levelSonar, &cochleaSwitch, 100, 20, 100, 75, 15000);

const char* ssid = "Home_WiFi";
const char* password = "<removed>";

IPAddress mqttServer(192, 168, 178, 23);
const char* mqttUsername = "marchinho93";
const char* mqttPassword = "<removed>";

const char* deviceName = "nutsloader";
const char* sensorUniqueID = "nutsloader_level_sensor";
const char* switchUniqueID = "nutsloader_switch";
const char* errorIndicatorUniqueID = "nutsloader_error_indicator";

const char* deviceSensorConfigTopic =
    "homeassistant/sensor/nutsloader_level_sensor/config";
const char* deviceSwitchConfigTopic =
    "homeassistant/switch/nutsloader_switch/config";
const char* deviceErrorIndicatorConfigTopic =
    "homeassistant/binary_sensor/nutsloader_error_indicator/config";
const char* deviceSensorStateTopic =
    "homeassistant/sensor/nutsloader_level_sensor/state";
const char* deviceSwitchStateTopic =
    "homeassistant/switch/nutsloader_switch/state";
const char* deviceErrorIndicatorStateTopic =
    "homeassistant/binary_sensor/nutsloader_error_indicator/state";
const char* deviceSwitchCommandTopic =
    "homeassistant/switch/nutsloader_switch/set";
const char* homeAssistantStatusTopic = "homeassistant/status";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);

  cochleaSwitch.setStateChangeCallback(publishSwitchState);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize OTA
  ArduinoOTA.begin();
  ArduinoOTA.setHostname("nutsloader-ota");
  ArduinoOTA.setPassword("<removed>");

  // Set up OTA event handlers
  ArduinoOTA.onStart(onOTAStart);
  ArduinoOTA.onProgress(onOTAProgress);
  ArduinoOTA.onEnd(onOTAEnd);

  Serial.println(WiFi.getAutoReconnect());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(onMessageReceived);
  mqttClient.setBufferSize(1024);
  mqttClient.setCallback(subscriptionsCallback);
}

long lastUpdateMillis = 0;
const long updatePeriod = 5000;

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }

  ArduinoOTA.handle();

  if (!mqttClient.connected()) {
    onDisconnected();
    return;
  }

  mqttClient.loop();

  nutsloaderService.loop();

  long timeNow = millis();
  if (timeNow - lastUpdateMillis >= updatePeriod) {
    publishStateUpdates();
    lastUpdateMillis = timeNow;
  }

  mqttClient.loop();
  delay(50);
}

void subscriptionsCallback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, homeAssistantStatusTopic) == 0){
    publishDiscoveryConfigs();
  }
}

void onOTAStart() {
  // Turn off the cochlea just to be safe
  nutsloaderService.stopFill();

  Serial.println("OTA update starting...");
}

void onOTAProgress(unsigned int progress, unsigned int total) {
  Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

void onOTAEnd() {
  Serial.println("\nOTA update complete!");
  ESP.restart();
}

void onMessageReceived(char* topic, byte* payload, unsigned int length) {
  if (strcmp(deviceSwitchCommandTopic, topic) == 0) {
    // Convert payload to chars array
    payload[length] = NULL;
    char* payloadChar = (char*)payload;

    // Do action
    if (strcmp(payloadChar, "ON") == 0) {
      nutsloaderService.startFill();
    } else {
      nutsloaderService.stopFill();
    }
  }
}

void onDisconnected() {
  // Turn off the cochlea just to be safe
  nutsloaderService.stopFill();

  // Try to reconnect forever
  Serial.print("Attempting MQTT connection...");

  bool res = mqttClient.connect(deviceName, mqttUsername, mqttPassword);
  if (!res) {
    Serial.print("failed, rc=");
    Serial.println(mqttClient.state());
    return;
  }

  Serial.println("Connected!");

  // Subscribe to topics
  subscribeAllTopics();

  // Publish discovery messages
  publishDiscoveryConfigs();

  // Publish states
  publishStateUpdates();

  // Subscribe to HA status topic
  mqttClient.subscribe(homeAssistantStatusTopic);
}

void subscribeAllTopics() {
  mqttClient.subscribe(deviceSwitchCommandTopic);
}

void publishDiscoveryConfigs() {
  publishSensorDiscoveryConfig();
  publishSwitchDiscoveryConfig();
  publishErrorIndicatorhDiscoveryConfig();
}

void publishStateUpdates() {
  publishSensorState();
  publishSwitchState();
  publishErrorIndicatorState();
}

void publishSensorDiscoveryConfig() {
  DynamicJsonDocument json(1024);

  json["name"] = sensorUniqueID;
  json["unique_id"] = sensorUniqueID;
  json["device"]["name"] = deviceName;
  json["device"]["identifiers"] = deviceName;
  json["unit_of_measurement"] = "%";
  json["value_template"] = "{{ value_json.level }}";
  json["state_topic"] = deviceSensorStateTopic;
  json["icon"] = "mdi:train-car-container";

  char payload[1024];
  serializeJson(json, payload);

  bool res = mqttClient.publish(deviceSensorConfigTopic, payload);
  if (!res) {
    Serial.println("Error occurred publishing sensor discovery config");
  }
}

void publishSwitchDiscoveryConfig() {
  DynamicJsonDocument json(1024);

  json["name"] = switchUniqueID;
  json["unique_id"] = switchUniqueID;
  json["device"]["name"] = deviceName;
  json["device"]["identifiers"] = deviceName;
  json["payload_on"] = "ON";
  json["payload_off"] = "OFF";
  json["state_on"] = "ON";
  json["state_off"] = "OFF";
  json["state_topic"] = deviceSwitchStateTopic;
  json["command_topic"] = deviceSwitchCommandTopic;
  json["icon"] = "mdi:tray-arrow-down";

  char payload[1024];
  serializeJson(json, payload);

  bool res = mqttClient.publish(deviceSwitchConfigTopic, payload);
  if (!res) {
    Serial.println("Error occurred publishing switch discovery config");
  }
}

void publishErrorIndicatorhDiscoveryConfig() {
  DynamicJsonDocument json(1024);

  json["name"] = errorIndicatorUniqueID;
  json["unique_id"] = errorIndicatorUniqueID;
  json["device_class"] = "problem";
  json["device"]["name"] = deviceName;
  json["device"]["identifiers"] = deviceName;
  json["payload_on"] = "ON";
  json["payload_off"] = "OFF";
  json["state_topic"] = deviceErrorIndicatorStateTopic;

  char payload[1024];
  serializeJson(json, payload);

  bool res = mqttClient.publish(deviceErrorIndicatorConfigTopic, payload);
  if (!res) {
    Serial.println(
        "Error occurred publishing error indicator discovery config");
  }
}

void publishSensorState() {
  DynamicJsonDocument json(1024);

  int level = nutsloaderService.getLevel();

  json["level"] = level;

  char payload[1024];
  serializeJson(json, payload);

  bool res = mqttClient.publish(deviceSensorStateTopic, payload);
  if (!res) {
    Serial.println("Error occurred publishing sensor state");
  }
}

void publishSwitchState() {
  char payload[1024];
  if (cochleaSwitch.status()) {
    strcpy(payload, "ON");
  } else {
    strcpy(payload, "OFF");
  }

  bool res = mqttClient.publish(deviceSwitchStateTopic, payload);
  if (!res) {
    Serial.println("Error occurred publishing switch state");
  }
}

void publishErrorIndicatorState() {
  char payload[1024];
  if (nutsloaderService.checkError()) {
    strcpy(payload, "ON");
  } else {
    strcpy(payload, "OFF");
  }

  bool res = mqttClient.publish(deviceErrorIndicatorStateTopic, payload);
  if (!res) {
    Serial.println("Error occurred publishing error indicator state");
  }
}
