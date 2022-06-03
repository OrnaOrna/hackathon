#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

// Replace later with relevant info
const char* ssid = "AndroidAP5DE7";
const char* password = "12345678";

// The name/IP address of the server.
const char* serverURL = "0.0.0.0:8000";

void WiFiConnect() {
    /*
    Connects to wifi. Call in setup()
    */
    
    // Connect to WiFi
    Serial.println("Connecting to WiFi");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Wait until a connection is estabilished (timeout: 1min.)
    bool connected = false;
    for (int i = 0; i < 60000 / 500; ++i)
    {
        Serial.print(".");
        delay(500);
        if (WiFi.waitForConnectResult() == WL_CONNECTED)
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

String generateAlert(const char* location, float waterHeight, const char* ID, bool resolved) {
    /*
    Generates a JSON alert from relevant parameters. The alert contains the sensor's location,
    the water height recorded and the sensor's ID.
    */
    DynamicJsonDocument alert(1024);
    alert["location"] = location;
    alert["waterHeight"] = waterHeight;
    alert["ID"] = ID;
    alert["resolved"] = resolved;

    // The output (serialized) JSON, returned as a string of text.
    String output = "";
    serializeJson(alert, output);

    return output;
}

bool sendAlert(const char* location, float waterHeight, const char* ID, bool resolved) {
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
        String alertText = generateAlert(location, waterHeight, ID, resolved);

        // End the connection to free resources
        http.end();

        // Send the alert to the server then return the response code.
        return (http.POST(alertText) == HTTP_CODE_ACCEPTED);
    }
}


bool sendRequest(const char* ID) {
    /*
    Asks the server if the alert has been resolved, returning whether it was or not.
    */

    // If still connected to WiFi, connect to the server
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        // Begin the connection
        http.begin(client, strcat(strcat(strdup(serverURL), "/?id="), strdup(ID)));

        // Send a request for the alert's status to the server. This variable contains the response code.
        int responseCode = http.GET();

        // Get whether the message was sent
        if (responseCode == HTTP_CODE_ACCEPTED) {
            String payload = http.getString();

            // End the connection to free resources
            http.end();

            // Check whtether the alert has been resolved or not.;
            return strcmp(payload.c_str(), "true");
        } else {
            // End the connection to free resources
            http.end();

            Serial.println("Error receiving status from server");
            return false;
        }
        
    }
}

