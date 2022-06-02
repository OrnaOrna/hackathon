#include <HttpClient.h>
#include <WiFi.h>

// Replace later with relevant info
const char* ssid = "";
const char* password = "";

// The name/IP address of the server. As we are connetcing to localhost, this will be 127.0.0.1
const char* serverURL = "127.0.0.1";

void setup() {
    Serial.begin(115200);
    
    // Connect to the server
    Serial.println("Connecting to server");
    Wifi.begin(ssid, password);

    // Wait until a connection is estabilished (timeout: 1min.)
    for (int i = 0; i < count; i++)
    {
        /* code */
    }
    

}

void loop() {

}