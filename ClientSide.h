#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H

void WiFiConnect();
void sendAlert(char* location, float waterHeight, char* ID);
String generateAlert(char* location, float waterHeight, char* ID);

#endif