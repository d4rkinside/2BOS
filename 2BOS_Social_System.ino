//Code for the NodeMCU
//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <BlynkSimpleEsp8266.h>

//Defining all variables used in the nodeMCU code
int temp = 1;
int led = D0;
int pos = 0;
int irsensor = D3;
int buttonstatus;
int irstatus;
int ping=D7;
int echo=D8;
int duration,cm;
Servo myservo;

//defining the template and authentications for connnecting wifi
#define BLYNK_TEMPLATE_ID "TMPLI2FuYEH9"
#define BLYNK_DEVICE_NAME "hackathon"
#define BLYNK_AUTH_TOKEN "WP0x4cpiipunEvxzm46L1-ws0fARvJQh"
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "D4RK wifi";//Enter your WIFI name
char pass[] = "#23702370";//Enter your WIFI password

//Writing to Blynk Cloud the initial value and syncing them
BLYNK_CONNECTED() {
  Blynk.syncAll();
  Blynk.virtualWrite(V1, temp);
}

//function for using ultrasonic sensor
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void setup() {
  //Setting pinmodes and all attributes
  pinMode(led, OUTPUT);
  pinMode(irsensor, INPUT);
  Serial.begin(115200);
  Serial.println("Welcome to the new project");
  myservo.attach(2);
  myservo.write(0);
  
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  
   irstatus = digitalRead(irsensor); //reading irsensor for garbage detection
   //reading from ultrasonic sensor for depth of garbage in dustbin
   pinMode(ping, OUTPUT);
   digitalWrite(ping, LOW);
   delayMicroseconds(2);
   digitalWrite(ping, HIGH);
   delayMicroseconds(10);
   digitalWrite(ping, LOW);
   pinMode(echo, INPUT);
   duration = pulseIn(echo, HIGH);
   cm = microsecondsToCentimeters(duration);
   Blynk.virtualWrite(V1,100-cm); //writing to the Blynk Cloud Gauge
   //condition for when garbage is detected
    if (irstatus == 0) {
      temp++;
      Blynk.virtualWrite(V2, temp); //writing to token distribution counter on Blynk Cloud
      digitalWrite(led, LOW);
      //turning the servo for token distribution
      myservo.write(180);
      delay(500);
      myservo.write(0);
      delay(500);
      digitalWrite(led, HIGH);
    

  }
  //Run the Blynk library
  Blynk.run();

}
