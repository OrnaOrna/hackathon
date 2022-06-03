#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H

void WiFiConnect();
bool sendAlert(const char* location, float waterHeight, const char* ID, bool resolved);
String generateAlert(const char* location, float waterHeight, const char* ID, bool resolved);
bool sendRequest(const char* ID);

#endif