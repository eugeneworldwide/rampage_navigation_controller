#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif

Adafruit_BluefruitLE_SPI ble(8, 7, 4);

//APPS DEFINE
  #define locus 1
  #define rally 2
  #define media 3

//////////////////////////////////////////////////////////////////////////////////////////
//Select your button app assignments by commenting out the options you don't want.
//Make sure you only have one option available for each mode to avoid weird behaviour.
//////////////////////////////////////////////////////////////////////////////////////////

//MODE1 OPTIONS
  int modeONE = locus;
  //int modeONE = rally;
  //int modeONE = media;

//MODE2 OPTIONS
  //int modeTWO = locus;
  //int modeTWO = rally;
  int modeTWO = media;

/////////////////////////////////////////////////////////////////////////////////////////

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

//APP SWITCH BUTTON
  int buttonApp = 6;

//TOGGLE FIXED SCROLL SPEED
  int toggleScroll = 20;

//button & toggle Wait millisecs
  int buttonWait = 250;
  int toggleWait = 250;

//JOYSTICK BUTTONS
//int button9 = A4;
//int button10 = A5;

//THUMB JOYSTICK SCROLL SPEED
//int joystickHSCROLL = 30;
//int joystickVSCROLL = 30;

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
  //Joystick buttons
  //pinMode(button9, INPUT_PULLUP);
  //pinMode(button10, INPUT_PULLUP);
  //App rocker switch
  pinMode(buttonApp, INPUT_PULLUP);
  
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

void loop(void)
{

///////////////////////////////////////
//MODE ONE - TYICALLY ADVENTURE BUTTONS
//////////////////////////////////////
Serial.println("You are now in ModeONE");

while (digitalRead(buttonApp) == LOW) { //SWITCH BETWEEN APPS USING buttonAPP Status
  digitalWrite(ledGREEN, HIGH);
  digitalWrite(ledRED, LOW);
  Serial.print("ButtonApp ModeONE. Button PIN status is ");
  Serial.print(digitalRead(buttonApp));
  Serial.print(". The app selected for this mode is ");

  if (modeONE == locus) {
    Serial.println("Locus");
    //PUSH BUTTONS
    if (digitalRead(button1) == LOW) {
      Serial.print("Button 1 status: Zoom in with Volume+: ");
      Serial.println(digitalRead(button1));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+"); //Zoom in +
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button2) == LOW) {
      Serial.print("Button 2 status: Zoom out with Volume-: ");
      Serial.println(digitalRead(button2));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-"); //Zoom out -
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button3) == LOW) {
      Serial.print("Button 3 status: Map up with key r ");
      Serial.println(digitalRead(button3));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00"); //Map Up or turn r
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button4) == LOW) {
      Serial.print("Button 4 status: Center map with key c: ");
      Serial.println(digitalRead(button4));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-06-00-00-00-00"); //Center Map c
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button5) == LOW) {
      Serial.print("Button 5 status: Display of with key d: ");
      Serial.println(digitalRead(button5));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-07-00-00-00-00"); //Display off d
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    //TOGGLE SWITCH
    if (digitalRead(button6) == LOW) {
      Serial.print("Button 6 status: Zoom in with Volume-: ");
      Serial.println(digitalRead(button6));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-"); //Zoom in +
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button7) == LOW) {
      Serial.print("Button 7 status: Zoom in with Volume+: ");
      Serial.println(digitalRead(button7));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+"); //Zoom in +
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    }                 
  if (modeONE == rally) {
    Serial.println("Rally");    
    //PUSH BUTTONS
    if (digitalRead(button1) == LOW) {
      Serial.print("Button 1 status: Volume+: ");
      Serial.println(digitalRead(button1));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button2) == LOW) {
      Serial.print("Button 2 status: Volume-: ");
      Serial.println(digitalRead(button2));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button3) == LOW) {
      Serial.print("Button 3 status: Map up with r: ");
      Serial.println(digitalRead(button3));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00"); //Map Up or turn r
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button4) == LOW) {
      Serial.print("Button 4 status: MediaNext: ");
      Serial.println(digitalRead(button4));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button5) == LOW) {
      Serial.print("Button 5 status: MediaPrevious: ");
      Serial.println(digitalRead(button5));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    //TOGGLE SWITCH
    if (digitalRead(button6) == LOW) {
      Serial.print("Button 6 status: MediaPrevious: ");
      Serial.println(digitalRead(button6));       
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
     if (digitalRead(button7) == LOW) {
      Serial.print("Button 7 status: MediaNext: ");
      Serial.println(digitalRead(button7));       
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
   } 
  if (modeONE == media) {
    Serial.println("Media");    
    //PUSH BUTTONS
    if (digitalRead(button1) == LOW) {
      Serial.print("Button 1 status: Volume+: ");
      Serial.println(digitalRead(button1));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button2) == LOW) {
      Serial.print("Button 2 status: Volume-: ");
      Serial.println(digitalRead(button2));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button3) == LOW) {
      Serial.print("Button 3 status: Play or Pause: ");
      Serial.println(digitalRead(button3));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=PLAYPAUSE");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button4) == LOW) {
      Serial.print("Button 4 status: MediaNext: ");
      Serial.println(digitalRead(button4));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button5) == LOW) {
      Serial.print("Button 5 status: MediaPrevious: ");
      Serial.println(digitalRead(button5));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    //TOGGLE SWITCH
    if (digitalRead(button6) == LOW) {
      Serial.print("Button 6 status: Mute: ");
      Serial.println(digitalRead(button6));       
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MUTE");
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
     if (digitalRead(button7) == LOW) {
      Serial.print("Button 7 status: Home: ");
      Serial.println(digitalRead(button7));       
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=HOME");
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    }    
  }

///////////////////////////////////////
//MODE TWO - TYICALLY ADVENTURE BUTTONS
//////////////////////////////////////
Serial.println("You are now in ModeTWO");

while (digitalRead(buttonApp) == HIGH) {
  digitalWrite(ledGREEN, LOW);
  digitalWrite(ledRED, HIGH);
  Serial.print("ButtonApp ModeTWO. Button PIN status is ");
  Serial.print(digitalRead(buttonApp));
  Serial.print(". The app selected for this mode is ");

  if (modeTWO == locus) {
    Serial.println("Locus");
    //PUSH BUTTONS
    if (digitalRead(button1) == LOW) {
      Serial.print("Button 1 status: Zoom in with Volume+: ");
      Serial.println(digitalRead(button1));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+"); //Zoom in +
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button2) == LOW) {
      Serial.print("Button 2 status: Zoom out with Volume-: ");
      Serial.println(digitalRead(button2));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-"); //Zoom out -
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button3) == LOW) {
      Serial.print("Button 3 status: Map up with key r ");
      Serial.println(digitalRead(button3));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00"); //Map Up or turn r
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button4) == LOW) {
      Serial.print("Button 4 status: Center map with key c: ");
      Serial.println(digitalRead(button4));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-06-00-00-00-00"); //Center Map c
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button5) == LOW) {
      Serial.print("Button 5 status: Display of with key d: ");
      Serial.println(digitalRead(button5));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-07-00-00-00-00"); //Display off d
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    //TOGGLE SWITCH
    if (digitalRead(button6) == LOW) {
      Serial.print("Button 6 status: Zoom in with Volume-: ");
      Serial.println(digitalRead(button6));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-"); //Zoom in +
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    if (digitalRead(button7) == LOW) {
      Serial.print("Button 7 status: Zoom in with Volume+: ");
      Serial.println(digitalRead(button7));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+"); //Zoom in +
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
      }
    }                 
  if (modeTWO == rally) {
    Serial.println("Rally");    
    //PUSH BUTTONS
    if (digitalRead(button1) == LOW) {
      Serial.print("Button 1 status: Volume+: ");
      Serial.println(digitalRead(button1));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button2) == LOW) {
      Serial.print("Button 2 status: Volume-: ");
      Serial.println(digitalRead(button2));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button3) == LOW) {
      Serial.print("Button 3 status: Map up with r: ");
      Serial.println(digitalRead(button3));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00"); //Map Up or turn r
      ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button4) == LOW) {
      Serial.print("Button 4 status: MediaNext: ");
      Serial.println(digitalRead(button4));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button5) == LOW) {
      Serial.print("Button 5 status: MediaPrevious: ");
      Serial.println(digitalRead(button5));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    //TOGGLE SWITCH
    if (digitalRead(button6) == LOW) {
      Serial.print("Button 6 status: MediaPrevious: ");
      Serial.println(digitalRead(button6));       
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
     if (digitalRead(button7) == LOW) {
      Serial.print("Button 7 status: MediaNext: ");
      Serial.println(digitalRead(button7));       
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
   } 
  if (modeTWO == media) {
    Serial.println("Media");    
    //PUSH BUTTONS
    if (digitalRead(button1) == LOW) {
      Serial.print("Button 1 status: Volume+: ");
      Serial.println(digitalRead(button1));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button2) == LOW) {
      Serial.print("Button 2 status: Volume-: ");
      Serial.println(digitalRead(button2));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button3) == LOW) {
      Serial.print("Button 3 status: Play or Pause: ");
      Serial.println(digitalRead(button3));
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=PLAYPAUSE");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button4) == LOW) {
      Serial.print("Button 4 status: MediaNext: ");
      Serial.println(digitalRead(button4));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (digitalRead(button5) == LOW) {
      Serial.print("Button 5 status: MediaPrevious: ");
      Serial.println(digitalRead(button5));      
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
      delay(buttonWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
    //TOGGLE SWITCH
    if (digitalRead(button6) == LOW) {
      Serial.print("Button 6 status: Mute: ");
      Serial.println(digitalRead(button6));       
      digitalWrite(LED_BUILTIN, HIGH);
      ble.sendCommandCheckOK("AT+BleHidControlKey=MUTE");
      delay(toggleWait);
      digitalWrite(LED_BUILTIN, LOW);
    }
     if (digitalRead(button7) == LOW) {
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
