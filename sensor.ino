#include "ClientSide.h"

// Define pins for the US sensor
const int trigPin = 19;
const int echoPin = 18;
// Define pin for reading from the potentiometer
const int potPin = 4;

//define sound speed in cm/uS
const int speedOfSound = 0.034;

// Define variables used in distance US distance calculation
long duration;
float distanceCm;

// The threshold distance, when recording a distance under it for long enough send an alert.
float threshold;

// This variable counts the time since last sending an alert. After a certain time, a request will be sent to see
// whether the alert was resolved
int getCounter = 0;

// Whether an alert was sent to the server recently.
bool alerted = false;

// A variable which will serve as a sort of lower threshold for determining whether an alert was resolved on its own.
float  normalisedLastAverges;

// Variables used for moving average calculation
int currMinSamples = 0;
float avgs[5];
float samples[60];

void setup() {
    const char* ID = "3agnb6";
    const char* location = "";

    bool alerted = false;
    float  normalisedLastAverges;

    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(potPin, INPUT);
}

void loop() {
    // Distance calculation - sends a pulse, records its travel time then divides by half the speed of sound
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration * speedOfSound/2;
  
    // Calculates the threshold distance value from the potentiometer's position - between 5cm and 205cm
    threshold = 5 + analogRead(potPin) * 200 / 4095;

    // Records the calculation, in a way making a moving average
    samples[currMinSamples] = distanceCm; 
    ++currMinSamples;

    // If 60 samples have already been recorded this minute, 
    // calculate their average then record it - then erase the first average
    if(currMinSamples == 60) {
        currMinSamples=0;
        for(int i = 1; i <= 4; ++i) {
            avgs[i - 1] = avgs[i];
        }
        avgs[4] = 0;
        for(int i = 0; i < 60; i++) {
            avgs[4] += samples[i] / 60;
        }

        // If the average distance from the last minute is lower than the threshold distance, and there was not alert sent send an alert
        if (avgs[4] <= threshold) {
            if(alerted=false) {
                sendAlert(location, avgs[4], ID, alerted);
                normalisedLastAverges=(avgs[0] + avgs[1] + avgs[2] + avgs[3]) / (4 * threshold);
            }
            Serial.println('Alert!');
            alerted = true;
        }
        else if(alerted && avgs[4] > threshold * normalisedLastAverges)  {
            // The water levels are down, send a message about that to the server
            alerted = false;
            sendAlert(location, avgs[4], ID, alerted);
            Serial.println("The waters are down.")
        }
        
        // Handle the case when the alert was manually resolved
        if (alerted) {
            ++getCounter;
            if (getCounter % 30 === 0) {
                if(!sendRequest(ID)) {
                    Serial.println("Alert resolved.");
                    alerted = false;
                    getCounter = 0;
                } 
            }
        }
    }
    delay(1000);
}