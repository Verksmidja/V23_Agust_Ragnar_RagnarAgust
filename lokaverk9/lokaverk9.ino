/*
 * SimpleReceiverWithCallback.cpp
 *
 * Demonstrates receiving NEC IR codes with IRrecv
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 ************************************************************************************
 * MIT License
 *
 * Copyright (c) 2022 Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */

/*
 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 */
///////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "DHT.h"          // safn frá Adafruit
#include "PubSubClient.h" // Connect and publish to the MQTT broker

// Code for the ESP32
#include "WiFi.h" // Enables the ESP32 to connect to the local network (via WiFi)
//#define DHTPIN 4  // Pin connected to the DHT sensor


//#define DHTTYPE DHT14  // DHT11 or DHT22
//DHT dht(DHTPIN, DHTTYPE);

// WiFi


//const char* ssid = "TskoliVESM";  // Enter SSID here
//const char* wifi_password = "Fallegurhestur";  //Enter Password here

// const char* ssid = "";                 // Your personal network SSID
// const char* wifi_password = "";        // Your personal network password

const char* ssid = "TskoliVESM";  // Enter SSID here
const char* wifi_password = "Fallegurhestur";  //Enter Password here
//const char* ssid = "OnePlus 8 Pro";  // Enter SSID here
//const char* wifi_password = "j9qrtc5q";  //Enter Password here
// MQTT
const char* mqtt_server = "10.201.48.68";  // IP of the MQTT broker 10.201.48.68 91.121.93.94
const char* humidity_topic = "home/livingroom/humidity";
const char* temperature_topic = "home/livingroom/temperature";

const char* clientID = "dubydoommmmmmmmmmmmmmmmmmmmmm"; // MQTT client ID

const char* mqtt_username = "vesm3"; // MQTT username
const char* mqtt_password = "vesm3"; // MQTT password

//lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllife
const int ledPin = 12;
const int ledPin2 = 14;
const int ledPin3 = 27;

const int BUZZER_PIN = 26;


int life = 3;
//lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllife


// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient); 


#define LIGHT_SENSOR_PIN 35 // ESP32 pin GIOP36 (ADC0)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);




///////////////////////////////////////////////////////////////////////////////////









 
//#define DECODE_DENON        // Includes Sharp
//#define DECODE_JVC
//#define DECODE_KASEIKYO
//#define DECODE_PANASONIC    // alias for DECODE_KASEIKYO
//#define DECODE_LG
#define DECODE_NEC          // Includes Apple and Onkyo
//#define DECODE_SAMSUNG
//#define DECODE_SONY
//#define DECODE_RC5
//#define DECODE_RC6

//#define DECODE_BOSEWAVE
//#define DECODE_LEGO_PF
//#define DECODE_MAGIQUEST
//#define DECODE_WHYNTER
//#define DECODE_FAST

//#define DECODE_DISTANCE_WIDTH // Universal decoder for pulse distance width protocols
//#define DECODE_HASH         // special decoder for all protocols

//#define DECODE_BEO          // This protocol must always be enabled manually, i.e. it is NOT enabled if no protocol is defined. It prevents decoding of SONY!

//#define DEBUG               // Activate this for lots of lovely debug output from the decoders.

//#define RAW_BUFFER_LENGTH  180  // Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.

#include <Arduino.h>

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

/*
 * For callback
 */
#define PROCESS_IR_RESULT_IN_MAIN_LOOP
#if defined(PROCESS_IR_RESULT_IN_MAIN_LOOP) || defined(ARDUINO_ARCH_MBED) || defined(ESP32)
volatile bool sIRDataJustReceived = false;
#endif
void ReceiveCompleteCallbackHandler();





void setup() {
    Serial.begin(115200);
    delay(5000);
    Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    IrReceiver.registerReceiveCompleteCallback(ReceiveCompleteCallbackHandler);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols (&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));


    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);//LOW HIGH
    pinMode(ledPin2, OUTPUT);
    digitalWrite(ledPin2, HIGH);//LOW HIGH
    pinMode(ledPin3, OUTPUT);
    digitalWrite(ledPin3, HIGH);//LOW HIGH

    pinMode(BUZZER_PIN, OUTPUT);
}

//////////////////////////////////////////////////////////

void connect_MQTT(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

 //  Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}

//////////////////////////////////////////////////////////
void loop() {
//life--;
//Serial.print(life);


  if (life == 3){
        digitalWrite(ledPin, HIGH);//LOW HIGH
        digitalWrite(ledPin2, HIGH);//LOW HIGH
        digitalWrite(ledPin3, HIGH);}//LOW HIGH

  if (life == 2){
        digitalWrite(ledPin, HIGH);//LOW HIGH
        digitalWrite(ledPin2, HIGH);//LOW HIGH
        digitalWrite(ledPin3, LOW);}//LOW HIGH
        

  if (life == 1){
        digitalWrite(ledPin, HIGH);//LOW HIGH
        digitalWrite(ledPin2, LOW);//LOW HIGH
        digitalWrite(ledPin3, LOW);}//LOW HIGH


  if (life == 0){
        digitalWrite(ledPin, LOW);//LOW HIGH
        digitalWrite(ledPin2, LOW);//LOW HIGH
        digitalWrite(ledPin3, LOW);//LOW HIGH
        digitalWrite(BUZZER_PIN, HIGH);
        delay(5000);
        digitalWrite(BUZZER_PIN, LOW);
        life=3;}
    /*
     * Print in loop (interrupts are enabled here) if received data is available.
     */
    if (sIRDataJustReceived) {
        // Print a short summary of received data
        Serial.println("DataJustReceived");
        Serial.println(sIRDataJustReceived);
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println("UNKNOWN");

            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            /*
             * We have an unknown protocol here, print more info.
             * !!!Attention!!! This prints incorrect values, if we are late (not in this simple example :-))
             * and the the first mark of the next (repeat) data was yet received
             */
            IrReceiver.printIRResultRawFormatted(&Serial, true); //
            sIRDataJustReceived=0;
        }
        Serial.println();
        sIRDataJustReceived=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

  
  connect_MQTT();
  
  Serial.setTimeout(2000); //  maximum milliseconds to wait for serial data


  //readligt();
  

  //Serial.print(analogValue);   // the raw analog reading

  //float h = dht.readHumidity();
  //float t = dht.readTemperature();
  //lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllife
  //life=life-1;
  //int analogValue = life;
  life--;
  
  if (life == 3){
        digitalWrite(ledPin, HIGH);//LOW HIGH
        digitalWrite(ledPin2, HIGH);//LOW HIGH
        digitalWrite(ledPin3, HIGH);}//LOW HIGH

  if (life == 2){
        digitalWrite(ledPin, HIGH);//LOW HIGH
        digitalWrite(ledPin2, HIGH);//LOW HIGH
        digitalWrite(ledPin3, LOW);}//LOW HIGH
        

  if (life == 1){
        digitalWrite(ledPin, HIGH);//LOW HIGH
        digitalWrite(ledPin2, LOW);//LOW HIGH
        digitalWrite(ledPin3, LOW);}//LOW HIGH

  if (life == 0){
        digitalWrite(ledPin, LOW);//LOW HIGH
        digitalWrite(ledPin2, LOW);//LOW HIGH
        digitalWrite(ledPin3, LOW);//LOW HIGH
        digitalWrite(BUZZER_PIN, HIGH);
        delay(5000);
        digitalWrite(BUZZER_PIN, LOW);
        life=3;}
        
  Serial.print("Life: ");
  Serial.print(life);

  //lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllife
  //while (analogValue != 0){
  //      readligt();
        
  //}
    
  delay(500);
  

  if (client.publish(temperature_topic, String(100).c_str())) { 
    
    Serial.println("g sent!");
    
  }

  else {
    Serial.println("Temperature failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(temperature_topic, String(100).c_str());
  }
  if (client.publish(temperature_topic, String(life).c_str())) { 
    
    Serial.println("Temperature sent!");
    
  }

  else {
    Serial.println("Temperature failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(temperature_topic, String(life).c_str());
  }


  delay(5000);       // print new values every 1 Minute

sIRDataJustReceived=0;
        /////////////////////////////////////////////////////////
    }
}

/*
 * Callback function
 * Here we know, that data is available.
 * This function is executed in ISR (Interrupt Service Routine) context (interrupts are blocked here).
 * Make it short and fast and keep in mind, that you can not use delay(), prints longer than print buffer size etc.,
 * because they require interrupts enabled to return.
 * In order to enable other interrupts you can call sei() (enable interrupt again) after evaluating/copying data.
 * Good practice, but somewhat more complex, is to copy relevant data and signal receiving to main loop.
 */
#if defined(ESP32) || defined(ESP8266)
IRAM_ATTR
# endif
void ReceiveCompleteCallbackHandler() {
    IrReceiver.decode(); // fill IrReceiver.decodedIRData
    
Serial.println("IrReceiver.decode");

    /*
     * Check the received data and perform actions according to the received command
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command,
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decodedIRData.command == 0x10) {
      Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        delay(5000);
    } else if (IrReceiver.decodedIRData.command == 0x11) {
      Serial.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        delay(5000);
    }

    /*
     * Set flag to trigger printing of results in main loop,
     * since printing should not be done in a callback function
     * running in ISR (Interrupt Service Routine) context where interrupts are disabled.
     */
    sIRDataJustReceived = true;

    /*
     * Enable receiving of the next value.
     * !!!Attention!!!
     * After receiving the first mark of the next (repeat) data, 3 variables required for printing are reset/overwritten.
     * - IrReceiver.irparams.rawlen
     * - IrReceiver.irparams.rawbuf[0]
     * - IrReceiver.irparams.OverflowFlag)
     */
    
    IrReceiver.resume();
}
