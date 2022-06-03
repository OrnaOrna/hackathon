# Hackathon Project - Team 4 #

## overview ##
A monitoring system for floods in sewage or drainage systems. Endpoint ESP32-microcontrolled sensors installed inside sewer grates  communicate periodically over WiFi and HTTP with a Node.JS server app which is used by the end-user.

## File descriptions ##
`ClientSide.h` and `ClientSide.cpp` are responsible for sending requests from the sensors, acting as HTTP clients, to the server.
`ServerSide.js` is responsible for receiving these requests on the app-side and responding accordingly. `App.js` is responsible for showing alerts to the user. `sensor.ino` controls the sensor, reads data and decides whether an alert should be sent to the user or an existing alert should be resolved automatically.