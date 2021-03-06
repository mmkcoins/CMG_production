#include <WiFi.h>
#include <Servo.h>

WiFiServer server(3000);
//char c = '0';
char c = '0';

// Use a Servo object to represent and control the servo.
Servo groveServo;


//const int pinLed    = 7;  //7番に変更したよ
const int motorA = 7;
const int motorB = 8;
int angle = 90;
String str;
char STR[3];
const int motorctl = 3;
const int pinServo = 5;


void setup() {
  
  Serial.begin(9600);
//  pinMode(pinLed,OUTPUT);
  pinMode(motorA,OUTPUT); //信号用ピン
  pinMode(motorB,OUTPUT); //信号用ピン
    
  server.begin();
  //Serial.print("Connected to TCP. My address:");
  IPAddress myAddress(127,0,0,1);
  //IPAddress myAddress(192,168,11,24);
  Serial.println(myAddress);

  groveServo.attach(pinServo);
  
}


void loop() {      
  
  WiFiClient client = server.available();
      
    if (client.available() > 0){
        str = "";
        int vmeter;
        while ((c = client.read()) != '\n')
        {
          str  = (str + c);
        }
        str.toCharArray(STR, 8);
        vmeter = atoi(STR);
        //if (c == '1') 
        if (str == "s") {
           //digitalWrite(pinLed, HIGH);
           //STOP
           digitalWrite(motorA,LOW);
           digitalWrite(motorB,LOW);
        } 
        //if (c == '1') 
        if (str == "f") {
           //digitalWrite(pinLed, LOW);
           //GO
           digitalWrite(motorA,HIGH);
           digitalWrite(motorB,LOW);
        }
        if (str == "b") {
          //BACK
           digitalWrite(motorA,LOW);
           digitalWrite(motorB,HIGH);
        }
        
        if (vmeter > 0 && vmeter < 255) {
           //速度調節
           analogWrite(motorctl,vmeter);
        }
        //左右の動作制御
        if (vmeter > 300) {
          // Use the Servo object to move the servo.
          groveServo.write(vmeter - 300);

        }
    }
  
  //Serial.println(str);
  delay(5);
    
}

