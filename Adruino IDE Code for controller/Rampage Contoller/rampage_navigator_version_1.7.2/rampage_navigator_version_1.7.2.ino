#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif

Adafruit_BluefruitLE_SPI ble(8, 7, 4);

//PUSH BUTTONS STATE
const int button1state = LOW; 
const int button2state = LOW;
const int button3state = LOW;
const int button4state = LOW;
const int button5state = LOW;
const int button6state = LOW;
const int button7state = LOW;

//PUSH BUTTONS
const int button1 = 12; //Black
const int button2 = 11; //Dark blue
const int button3 = 10; //Blue
const int button4 = 9; //White
const int button5 = 5; //Dark blue

//APP LED
const int ledGREEN = A0;
const int ledRED = A1;

//TOGGLE SWITCH BUTTONS
const int button6 = A2;
const int button7 = A3;

//APP SWITCH BUTTON
const int modeSelect = 6;
int softApp;

//TOGGLE FIXED SCROLL SPEED
const int toggleScroll = 20;

//button & toggle Wait millisecs
const int buttonWait = 250;
const int toggleWait = 250;

////////////////////////////////////////////////////////////////////////////////////////////////
void setup(void)
{

  Serial.begin(115200);
  Serial.println("Starting up ...");
  
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
  
  ble.begin(false);
  ble.sendCommandCheckOK("AT+GAPDEVNAME=Rampage Navigator BLUE" );
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(void)
{
//  Serial.print("SoftApp # at startup is: ");
//  Serial.println(softApp);

//////////////////////////////////////////////////////////////
// START SOFT APP SELECT LOOP
//////////////////////////////////////////////////////////////
if (digitalRead(modeSelect) == LOW){
  digitalWrite(ledRED, HIGH);
  digitalWrite(ledGREEN, LOW);
  if (digitalRead(button1) == button1state){
    softApp = 1;
    Serial.println ("While in Mode Select you have selected softApp 1: Locus Maps button mapping");
    digitalWrite(ledRED, LOW);
    delay (500);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
      }
    delay (300);
    digitalWrite(ledRED, HIGH);
    } //End of state 1
  if (digitalRead(button2) == button2state){
    softApp = 2;
    Serial.println ("While in Mode Select you have selected softApp 2: Rally navigator");
    digitalWrite(ledRED, LOW);
    delay (500);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
      }
    delay (300);
    digitalWrite(ledRED, HIGH);
    } //End of state 2
  if (digitalRead(button3) == button3state){
    softApp = 3;
    Serial.println ("While in Mode Select you have selected softApp 3: OsMand");
    digitalWrite(ledRED, LOW);
    delay (500);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
      }
    delay (300);
    digitalWrite(ledRED, HIGH);
    } //End of state 3
  if (digitalRead(button4) == button4state){
    softApp = 4;
    Serial.println ("While in Mode Select you have selected softApp 4: Piste");
    digitalWrite(ledRED, LOW);
    delay (500);
    for (int i = 1; i <= softApp; i++) {
      digitalWrite(ledGREEN, HIGH);
      delay(300);
      digitalWrite(ledGREEN, LOW);
      delay(300);
      }
    delay (300);
    digitalWrite(ledRED, HIGH);
    } //End of state 4
  } 

//////////////////////////////////////////////////////////////
// END SOFT APP SELECT LOOP
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// START SOFT APP RUN LOOP
//////////////////////////////////////////////////////////////
if (digitalRead(modeSelect) == HIGH){ 
  digitalWrite(ledRED, LOW);
  digitalWrite(ledGREEN, HIGH);

  if (softApp == 0) { //App 0 No softApp value yet
    Serial.println("You are in softApp: ZERO");
    digitalWrite(ledGREEN, HIGH);
    delay(500);
    digitalWrite(ledGREEN, LOW);
    delay(500);
    } //End softapp 0

  if (softApp == 1) {  // App 1 Locus Maps
    digitalWrite(ledGREEN, HIGH);
    Serial.println("You are in softApp: Locus");
    //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.println("Button 1");
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
        }
      if (digitalRead(button2) == button2state) {
        Serial.println("Button 2");
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
        }
      if (digitalRead(button3) == button3state) {
        Serial.println("Button 3");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
        }
      if (digitalRead(button4) == button4state) {
        Serial.println("Button 4");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-06-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
        }
      if (digitalRead(button5) == button5state) {
        Serial.println("Button 5");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-07-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
        }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.println("Button 6");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-52-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
        }
      if (digitalRead(button7) == button7state) {
        Serial.println("Button 7");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-51-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
        }
    } //End softapp 1 

  if (softApp == 2){  // App 2 Rally Navigator
    digitalWrite(ledGREEN, HIGH);
    digitalWrite(ledRED, LOW);
    Serial.println("You are in softApp: Rally Navigator");    
    //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.println("Button 1");
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME+");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button2) == button2state) {
        Serial.println("Button 2");
        ble.sendCommandCheckOK("AT+BleHidControlKey=VOLUME-");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button3) == button3state) {
        Serial.println("Button 3");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-15-00-00-00-00"); //Map Up or turn r
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button4) == button4state) {
        Serial.print("Button 4");
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button5) == button5state) {
        Serial.println("Button 5");
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.println("Button 6");
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIAPREVIOUS");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
       if (digitalRead(button7) == button7state) {
        Serial.println("Button 7");
        ble.sendCommandCheckOK("AT+BleHidControlKey=MEDIANEXT");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      } 
    } //End softapp 2

  if (softApp == 3){  // App 3 OsMand
    digitalWrite(ledGREEN, HIGH);
    digitalWrite(ledRED, LOW);
    Serial.println("You are in softApp: OsMand");    
    //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.println("Button1");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-52-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button2) == button2state) {
        Serial.println("Button2");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-51-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");        
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button3) == button3state) {
        Serial.println("Button3");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-06-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button4) == button4state) {
        Serial.println("Button4");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-50-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button5) == button5state) {
        Serial.println("Button5");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-4F-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      } 
      //TOGGLE SWITCHES
      if (digitalRead(button6) == button6state) {
        Serial.println("Button6");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-57-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      } 
      if (digitalRead(button7) == button7state) {
        Serial.println("Button7");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-56-00-00-00-00");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }                       
    } //End softapp 3 
    
  if (softApp == 4){  // App 4 Piste
    digitalWrite(ledGREEN, HIGH);
    digitalWrite(ledRED, LOW);
    Serial.println("You are in softApp: Piste");    
    //PUSH BUTTONS
      if (digitalRead(button1) == button1state) {
        Serial.println("Button 1");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-1A-00-00-00-00"); //0x1A Keyboard w and W
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button2) == button2state) {
        Serial.println("Button 2");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-1B-00-00-00-00"); //0x1B Keyboard x and X
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button3) == button3state) {
        Serial.println("Button 3");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-04-00-00-00-00"); //0x04 Keyboard a and A
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button4) == button4state) {
        Serial.println("Button 4");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-07-00-00-00-00"); //0x07 Keyboard d and D
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button5) == button5state) {
        Serial.println("Button 5");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-14-00-00-00-00"); //0x14 Keyboard q and Q
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      //TOGGLE SWITCH
      if (digitalRead(button6) == button6state) {
        Serial.println("Button 6");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-07-00-00-00-00"); //0x07 Keyboard d and D
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
      if (digitalRead(button7) == button7state) {
        Serial.println("Button 7
        ");
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00-14-00-00-00-00"); //0x14 Keyboard q and Q
        ble.sendCommandCheckOK("AT+BLEKEYBOARDCODE=00-00");
        digitalWrite(ledGREEN, LOW);
        delay(buttonWait);
        digitalWrite(ledGREEN, HIGH);
      }
    } //End softapp 4        
  }
} //End of code
