#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "TP-Link_37AB";
const char* password = "PASS";

WebServer server(80);

void handleRoot() {
	server.send(200, "text/plain", "Use /13 to monitor 34 pin");
}

void handleNotFound() {
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
}

void setup(void) {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	if (MDNS.begin("esp32")) {
		Serial.println("MDNS responder started");
	}
	server.on("/", handleRoot);
	server.on("/13", []() {
		int val;
		val=analogRead(34);
		server.send(200, "text/plain", String(val));
	});
	server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
	server.handleClient();
	Serial.println(analogRead(34));
	delay(2);//allow the cpu to switch to other tasks
}
