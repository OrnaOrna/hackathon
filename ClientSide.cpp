#include <ArduinoJson.h>
#include <HTTPClient.h>
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

bool sendAlert(String location, float waterHeight, String ID) {
    /*
    Sends an alert to the HTTP server, returning whether the message was successfully sent.
    */

    // If still connected to WiFi, connect to the server
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        // Begin the connection
        http.begin(client, serverURL);

        // Specify the content-type header to specify we're sending JSON
        http.addHeader("Content-Type",  "application/json");

        // Get the alert data from the parameters
        String alertText = generateAlert(location, waterHeight, ID);

        // End the connection to free resources
        http.end();

        // Send the alert to the server then return the response code.
        return (http.POST(alertText) == HTTP_CODE_ACCEPTED);
    }
}

String generateAlert(String location, float waterHeight, String ID) {
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

bool sendRequest(String ID) {
    /*
    Asks the server if the alert has been resolved, returning whether it was or not.
    */

    // If still connected to WiFi, connect to the server
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        // Begin the connection
        http.begin(client, serverURL);

        // Send a request for the alert's status to the server. This variable contains the response code.
        int responseCode = http.GET();

        // Get whether the message was sent
        if (responseCode == HTTP_CODE_ACCEPTED)
        {
            String payload = http.getString();

            // End the connection to free resources
            http.end();

            // Check whtether the alert has been resolved or not.
            return strcmp(payload, "true");
        } else {
            // End the connection to free resources
            http.end();

            Serial.println("Error receiving status from server");
            return false;
        }
        
    }
}

