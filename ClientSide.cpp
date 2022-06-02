#include <ArduinoJson.h>
#include <HttpClient.h>
#include <WiFi.h>

// Replace later with relevant info
const char* ssid = "";
const char* password = "";

// The name/IP address of the server. As we are connetcing to localhost, this will be 127.0.0.1
const char* serverURL = "127.0.0.1";

void WiFiConnect() {
    Serial.begin(115200);
    
    // Connect to WiFi
    Serial.println("Connecting to WiFi");
    Wifi.begin(ssid, password);

    // Wait until a connection is estabilished (timeout: 1min.)
    bool connected = false;
    for (int i = 0; i < 60000 / 500; ++i)
    {
        Serial.print(".");
        delay(500);
        if (Wifi.status() == WL_CONNECTED)
        {
            connected = true;
            break;
        }
        
    }
    if (connected)
    {
        Serial.println("Connected to WiFi with IP address " + WiFi.localIP());
    } else {
        Serial.println("There was an error connecting to WiFi. 
        Check that you have an internet connection.");
    }    
}

void sendAlert(char* location, float waterHeight, char* ID) {
    // If still connected to WiFi, connect to the server
    if (WiFi.status() == WL_CONNECTED)
    {
        
    }
    
}


JsonObject& generateAlert(char* location, float waterHeight, char* ID) {
    StaticJSON<200> jsonBuffer;
}