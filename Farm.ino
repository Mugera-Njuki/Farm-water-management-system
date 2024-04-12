#include <SoftwareSerial.h>

#define trigPin1 1
#define echoPin1 2

#define trigPin2 3
#define echoPin2 4

#define trigPin3 5
#define echoPin3 6

#define GSM_TX 7
#define GSM_RX 8

#define RELAY_PIN 9

SoftwareSerial gsmSerial(GSM_TX, GSM_RX);

void setup(){
pinMode (trigPin1, OUTPUT);
pinMode (echoPin1, INPUT);

pinMode (trigPin2, OUTPUT);
pinMode (echoPin2, INPUT);

pinMode (trigPin3, OUTPUT);
pinMode (echoPin3, INPUT);

pinMode(RELAY_PIN, OUTPUT);

Serial.begin(9600);
gsmSerial.begin(9600);
delay(1000);

gsmSerial.println("AT+CMGF=1");
delay(1000);
}

void loop(){
float duration1, distance1, duration2, distance2, duration3, distance3;

digitalWrite(RELAY_PIN, LOW);

digitalWrite(trigPin1, LOW);
delay(2);
digitalWrite(trigPin1, HIGH);
delay(10);
digitalWrite(trigPin1, LOW);

digitalWrite(trigPin2, LOW);
delay(2);
digitalWrite(trigPin2, HIGH);
delay(10);
digitalWrite(trigPin2, LOW);

digitalWrite(trigPin3, LOW);
delay(2);
digitalWrite(trigPin3, HIGH);
delay(10);
digitalWrite(trigPin3, LOW);

duration1 = pulseIn(echoPin1, HIGH);
duration2 = pulseIn(echoPin2, HIGH);
duration3 = pulseIn(echoPin3, HIGH);

distance1 = duration1 * 0.034 / 2;
distance2 = duration2 * 0.034 / 2;
distance3 = duration3 * 0.034 / 2;

if(distance1 >=  10 || distance2 >=  10 || distance3 >= 10){
digitalWrite (RELAY_PIN, HIGH);
sendSMS( "WAASSUP! FYI, PUMP IS ON AND TANKS ARE BEING FILLED!");
    delay(60000);
}
else if(distance1 <= 10 || distance2 <= 10 || distance3 <= 10){
digitalWrite (RELAY_PIN, LOW);
sendSMS("WAASSUP! FYI, PUMP IS OFF AND ALL TANKS ARE FULL!");
    delay(60000);
}
}

void sendSMS(String message) {
  // Command to set recipient phone number (replace XXXXXXXXXX with recipient's phone number)
  gsmSerial.println("AT+CMGS=\"XXXXXXXXXX\"");
  delay(1000);
  
  // Send the message
  gsmSerial.print(message);
  delay(100);
  
  // Send Ctrl+Z to indicate end of message
  gsmSerial.println((char)26);
  delay(1000);
}