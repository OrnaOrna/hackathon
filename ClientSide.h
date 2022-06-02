#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H

void WiFiConnect();
bool sendAlert(String location, float waterHeight, String ID);
int generateAlert(String location, float waterHeight, String ID);
bool sendRequest(String ID);

#endif