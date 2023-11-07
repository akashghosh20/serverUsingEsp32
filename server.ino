#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char *ssid = "OPTIMUS";
const char *password = "1223334444";

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Serve web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    float temperature = (float)temperatureRead() / 100.0; // Convert to Celsius
    request->send(200, "text/plain", "Temperature: " + String(temperature) + " °C");
  });

  // Start server
  server.begin();
}

void loop() {
  // Nothing to do here
}

// Server will be shown on esp 32's ip address.