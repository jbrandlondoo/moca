#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <Hash.h>
const char* ssid = "NICO_ROBIN";
const char* password = "D60007000d";

//"2021-10-14 19:56:54,2021-10-14 19:56:55,2021-10-14 19:56:57,2021-10-14 19:56:59,2021-10-14 19:57:01,2021-10-14 19:57:04,2021-10-14 19:57:05,2021-10-14 19:57:06"
WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);
void handleRoot() 
{
  Serial.print("Connected");
  float _rand = random(60,90);
  String message = "2021-10-14 19:56:54,";
  message += _rand;
   server.send(200, "text/plain",message);
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
            Serial.printf("[%u] conected!\n", num);
            webSocket.sendTXT(num, "Connected");
            break;
        /**case WStype_TEXT:
            Serial.printf("[%u] get Text: %s\n", num, payload);
            webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[%u] get binary length: %u\n", num, length);
            hexdump(payload, length);
            break;**/
    }

}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Connect Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
  server.on("/", handleRoot);
  server.begin();
  Serial.print("Open http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to see it working");
  
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop(){
  server.handleClient();
  webSocket.loop();
}
