#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif

Adafruit_BluefruitLE_SPI ble(8, 7, 4);

//////////////////////////////////////////////////////
// Buttons used on the controller can be Normaly-Closed or Normaly-Open as a state. 
// For Normaly-Open controller buttons the state used in the code is set to LOW
// For Normaly-Closed controller buttons the state in the code is set to HIGH
//////////////////////////////////////////////////////
  int button1state = LOW; 
  int button2state = LOW;
  int button3state = LOW;
  int button4state = LOW;
  int button5state = LOW;
  int button6state = LOW;
  int button7state = LOW;
//////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//PUSH BUTTONS
  int button1 = 12; //Black
  int button2 = 11; //Dark blue
  int button3 = 10; //Blue
  int button4 = 9; //White
  int button5 = 5; //Dark blue

//APP LED
  int ledGREEN = A0;
  int ledRED = A1;

//TOGGLE SWITCH BUTTONS
  int button6 = A2;
  int button7 = A3;

//APP SELECT
  int modeSelect = 6;
  int softApp;

//TOGGLE FIXED SCROLL SPEED
  int toggleScroll = 20;

//button & toggle Wait millisecs
  int buttonWait = 250;
  int toggleWait = 250;

////////////////////////////////////////////////////////////////////////////////////////////////
void setup(void)
{
  //Push buttons
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  //Toggle switch buttons
  pinMode(button6, INPUT_PULLUP);
  pinMode(button7, INPUT_PULLUP);
  //Mode LEDs
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledRED, OUTPUT);

  //App rocker switch
  pinMode(modeSelect, INPUT_PULLUP);
  
  Serial.begin(115200);
  ble.begin(false);
  ble.sendCommandCheckOK("AT+GAPDEVNAME=Rampage Navigator" );
  ble.sendCommandCheckOK("AT+BLEHIDEN=On");
  ble.reset();
  Serial.println("Bluetooth Started OK!");
  digitalWrite(LED_BUILTIN, LOW);
  
  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();
}

////////////////////////////////////////////////////////////////////////////////////////////////
void loop(void){
  Serial.print("SoftApp at startup is: ");
  Serial.println(softApp);

//////////////////////////////////////////////////////////////
while (digitalRead(modeSelect) == LOW){
  digitalWrite(ledRED, HIGH);
  digitalWrite(ledGREEN, LOW);
  if (digitalRead(button1) == LOW){
    softApp = 1;
    Serial.println ("While in Mode Select you have selected softApp 1: Locus Maps button mapping");
    digitalWrite(ledRED, LOW);
    delay (1000);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
    }
    delay (1000);
    digitalWrite(ledRED, HIGH);
  }
  if (digitalRead(button2) == LOW){
    softApp = 2;
    Serial.println ("While is Mode Select you have selected softApp 2: Rally Navigator button mapping");
    digitalWrite(ledRED, LOW);
    delay (1000);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
    }   
    delay (1000);
    digitalWrite(ledRED, HIGH);
  }
  if (digitalRead(button3) == LOW){
    softApp = 3;
    Serial.println ("While is Mode Select you have selected softApp 3: Media button mapping");    
    digitalWrite(ledRED, LOW);    
    delay (1000);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
    }   
    delay (1000);
    digitalWrite(ledRED, HIGH);
  }
  if (digitalRead(button4) == LOW){
    softApp = 4;
    Serial.println ("While is Mode Select you have selected softApp 4: Not mapped yet");
    digitalWrite(ledRED, LOW);    
    delay (1000);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
    }   
    delay (1000);
    digitalWrite(ledRED, HIGH);
  } 
   if (digitalRead(button5) == LOW){
    softApp = 5;
    Serial.println ("While is Mode Select you have selected softApp 5: Not mapped yet");
    digitalWrite(ledRED, LOW);    
    delay (1000);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
    }   
    delay (1000);
    digitalWrite(ledRED, HIGH);
  } 
}

//////////////////////////////////////////////////////////////
while (digitalRead(modeSelect) == HIGH){  
  digitalWrite(ledGREEN, HIGH);
  digitalWrite(ledRED, LOW);
  
    if (softApp == 1) { //LOCUS MAPS
      Serial.println("You are in softApp: Locus");
      //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.print("Button 1 status: Zoom in with Volume+: ");
        Serial.println(digitalRead(button1));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+"); //Zoom in +
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
        }
      if (digitalRead(button2) == button2state) {
        Serial.print("Button 2 status: Zoom out with Volume-: ");
        Serial.println(digitalRead(button2));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-"); //Zoom out -
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
        }
      if (digitalRead(button3) == button3state) {
        Serial.print("Button 3 status: Map up with key r ");
        Serial.println(digitalRead(button3));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00"); //Map Up or turn r
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
        }
      if (digitalRead(button4) == button4state) {
        Serial.print("Button 4 status: Center map with key c: ");
        Serial.println(digitalRead(button4));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-06-00-00-00-00"); //Center Map c
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
        }
      if (digitalRead(button5) == button5state) {
        Serial.print("Button 5 status: Display of with key d: ");
        Serial.println(digitalRead(button5));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-07-00-00-00-00"); //Display off d
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
        }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.print("Button 6 status: Zoom in with Volume+: ");
        Serial.println(digitalRead(button6));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+"); //Zoom in +
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
        }
      if (digitalRead(button7) == button7state) {
        Serial.print("Button 7 status: Zoom in with Volume-: ");
        Serial.println(digitalRead(button7));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-"); //Zoom in +
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
        }
      }  
                     
    if (softApp == 2) {  //RALLY NAVIGATOR
      Serial.println("You are in softApp: Rally Navigator");    
      //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.print("Button 1 status: Volume+: ");
        Serial.println(digitalRead(button1));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button2) == button2state) {
        Serial.print("Button 2 status: Volume-: ");
        Serial.println(digitalRead(button2));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button3) == button3state) {
        Serial.print("Button 3 status: Map up with r: ");
        Serial.println(digitalRead(button3));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00"); //Map Up or turn r
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button4) == button4state) {
        Serial.print("Button 4 status: MediaNext: ");
        Serial.println(digitalRead(button4));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button5) == button5state) {
        Serial.print("Button 5 status: MediaPrevious: ");
        Serial.println(digitalRead(button5));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.print("Button 6 status: MediaPrevious: ");
        Serial.println(digitalRead(button6));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
       if (digitalRead(button7) == button7state) {
        Serial.print("Button 7 status: MediaNext: ");
        Serial.println(digitalRead(button7));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
     } 
     
    if (softApp == 3) { //MEDIA APP
      Serial.println("You are in softApp: Media");    
      //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.print("Button 1 status: Volume+: ");
        Serial.println(digitalRead(button1));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button2) == button2state) {
        Serial.print("Button 2 status: Volume-: ");
        Serial.println(digitalRead(button2));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button3) == button3state) {
        Serial.print("Button 3 status: Play or Pause: ");
        Serial.println(digitalRead(button3));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=PLAYPAUSE");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button4) == button4state) {
        Serial.print("Button 4 status: MediaNext: ");
        Serial.println(digitalRead(button4));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button5) == button5state) {
        Serial.print("Button 5 status: MediaPrevious: ");
        Serial.println(digitalRead(button5));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.print("Button 6 status: Mute: ");
        Serial.println(digitalRead(button6));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MUTE");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
       if (digitalRead(button7) == button7state) {
        Serial.print("Button 7 status: Home: ");
        Serial.println(digitalRead(button7));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=HOME");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
       }
     }   
      
    if (softApp == 4) { //NOTHING YET
      Serial.println("You are in softApp: Media");    
      //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.print("Button 1 status: Volume+: ");
        Serial.println(digitalRead(button1));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button2) == button2state) {
        Serial.print("Button 2 status: Volume-: ");
        Serial.println(digitalRead(button2));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button3) == button3state) {
        Serial.print("Button 3 status: Play or Pause: ");
        Serial.println(digitalRead(button3));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=PLAYPAUSE");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button4) == button4state) {
        Serial.print("Button 4 status: MediaNext: ");
        Serial.println(digitalRead(button4));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button5) == button5state) {
        Serial.print("Button 5 status: MediaPrevious: ");
        Serial.println(digitalRead(button5));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.print("Button 6 status: Mute: ");
        Serial.println(digitalRead(button6));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MUTE");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
       if (digitalRead(button7) == button7state) {
        Serial.print("Button 7 status: Home: ");
        Serial.println(digitalRead(button7));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=HOME");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
       }
     }    

     if (softApp == 5) { //NOTHING YET
      Serial.println("You are in softApp: Media");    
      //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.print("Button 1 status: Volume+: ");
        Serial.println(digitalRead(button1));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button2) == button2state) {
        Serial.print("Button 2 status: Volume-: ");
        Serial.println(digitalRead(button2));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button3) == button3state) {
        Serial.print("Button 3 status: Play or Pause: ");
        Serial.println(digitalRead(button3));
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=PLAYPAUSE");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button4) == button4state) {
        Serial.print("Button 4 status: MediaNext: ");
        Serial.println(digitalRead(button4));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      if (digitalRead(button5) == button5state) {
        Serial.print("Button 5 status: MediaPrevious: ");
        Serial.println(digitalRead(button5));      
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
        delay(buttonWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.print("Button 6 status: Mute: ");
        Serial.println(digitalRead(button6));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=MUTE");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
      }
       if (digitalRead(button7) == button7state) {
        Serial.print("Button 7 status: Home: ");
        Serial.println(digitalRead(button7));       
        digitalWrite(LED_BUILTIN, HIGH);
        ble.sendCommandCheckOK("AT+BleHidControlKey=HOME");
        delay(toggleWait);
        digitalWrite(LED_BUILTIN, LOW);
       }
     }
   }
}

////////////////////
/* END OF CODE*/
////////////////////