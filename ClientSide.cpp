#include <ArduinoJson.h>
#include <HttpClient.h>
#include <WiFi.h>

// Replace later with relevant info
const char* ssid = "";
const char* password = "";

// The name/IP address of the server. As we are connetcing to localhost, this will be 127.0.0.1
const char* serverURL = "127.0.0.1";

void WiFiConnect() {
    /*
    Connects to wifi. Call in setup()
    */

    Serial.begin(115200);
    
    // Connect to WiFi
    Serial.println("Connecting to WiFi");
    WiFi.begin(ssid, password);

    // Wait until a connection is estabilished (timeout: 1min.)
    bool connected = false;
    for (int i = 0; i < 60000 / 500; ++i)
    {
        Serial.print(".");
        delay(500);
        if (WiFi.status() == WL_CONNECTED)
        {
            connected = true;
            break;
        }
        
    }
    if (connected)
    {
        Serial.println("Connected to WiFi with IP address " + WiFi.localIP());
    } else {
        Serial.println("There was an error connecting to WiFi. "
        " Check that you have an internet connection.");
    }    
}

void sendAlert(char* location, float waterHeight, char* ID) {
    /*
    Sends an alert to the HTTP server.
    */

    // If still connected to WiFi, connect to the server
    if (WiFi.status() == WL_CONNECTED)
    {
    
    }
    
}


String generateAlert(char* location, float waterHeight, char* ID) {
    /*
    Generates a JSON alert from relevant parameters. The alert contains the sensor's location,
    the water height recorded and the sensor's ID.
    */
    DynamicJsonDocument alert(1024);
    alert["location"] = location;
    alert["waterHeight"] = waterHeight;
    alert["ID"] = ID;

    // The output (serialized) JSON, returned as a string of text.
    String output = "";
    serializeJson(alert, output);

    return output;
}