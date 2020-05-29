

// "/button3" - LED 3

// Arduino setup RGBLED: https://create.arduino.cc/projecthub/muhammad-aqib/arduino-rgb-led-tutorial-fc003e
// Button: https://www.arduino.cc/en/tutorial/button

// https://shiftr.io/get-started
// https://forum.arduino.cc/index.php?topic=553587.0
// https://efcomputer.net.au/blog/5-steps-to-create-internet-controlled-ledstrip-using-esp8266-and-mqtt/
// https://www.element14.com/community/community/arduino/arduino-projects/blog/2019/02/05/mkr-wifi-1010-mqtt-remote-relay-board-control


#include <WiFiNINA.h> // import WiFiNINA library (Sketch --> Use Library --> Manage Library --> search and install)
#include <MQTT.h> // import adafruit MQTT library (Sketch --> Use Library --> Manage Library --> search and install)

#include <MqttClient.h>
#include <MQTTClient.h>
#include <ArduinoMqttClient.h>
#include <Adafruit_MQTT.h>



// "" set your wifi name and password + broker key and secret of shiftr.io. Device name you see on shiftr.io coming up.
const char WIFI_SSID[] = "VODAFONE-2A60"; // WiFI ssid
const char WIFI_PASS[] = "MJKSAB4Y5E47EBEE"; //WiFI password
const char mqttServer[] = "broker.shiftr.io"; // broker, with shiftr.io it's "broker.shiftr.io"
const int mqttServerPort = 1883; // broker mqtt port
const char key[] = "38d97696"; // broker key
const char secret[] = "a705482047c0cafb"; // broker secret
const char device[] = "ArduinoPamela"; // broker device identifier

// setting Wifi/MQTT
int status = WL_IDLE_STATUS;
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;

// setting buttonPin and State
const int buttonPin = 5;
int buttonState = 0;
int lastButtonState = 0;
int buttonClick = 0;
int lastButtonClick = 0;

//Set RGB LED 1 WENDY
int redPin= 0;
//int greenPin = 1;
//int bluePin = 0;

//Set RGB LED 2  PAM
int redPin2= 1;
//int greenPin2 = 4;
//int bluePin2 = 3;

//Set RGB LED 3
int redPin3 = 2; 
//int greenPin3 = ...;
//int bluePin3 = ...;

//Set RGB LED 4 VERONICA
int redPin4 = 3;
//int greenPin4 = ...;
//int bluePin4 = ...;

//Set internet connection pin
int internetPin = 4;

// check your connection with WiFi and MQTT broker
void connect() {
  Serial.print("checking wifi..."); // you see serial monitor
  while ( status != WL_CONNECTED) { // check if connected
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("."); // you see serial monitor
    delay(1000);
  }
  Serial.println("\nconnected to WiFi!\n"); // you see serial monitor

  client.begin(mqttServer, mqttServerPort, net); // check the server

  Serial.println("connecting to broker..."); // you see serial monitor
  while (!client.connect(device, key, secret)) { // check the broker of shiftr.io
    Serial.print("."); // you see serial monitor
    delay(1000);
  }

Serial.println("Connected to MQTT"); // you see serial monitor

  client.onMessage(messageReceived); // connected with void(messageReceived)

  client.subscribe("/button1");  // What Wendy button sends - can be received in void(messageReceived)
  client.subscribe("/button2");  // What Pamela button sends - can be received in void(messageReceived)
  client.subscribe("/button3");  // What Jasper button sends - can be received in void(messageReceived)
  client.subscribe("/button4");  // What Veronika button sends - can be received in void(messageReceive
}

void setup() {
  Serial.begin(115200); // to see serial monitor
  
  pinMode(redPin, OUTPUT); //Set RGB LED 1
  //pinMode(greenPin, OUTPUT); //Set RGB LED 1
  //pinMode(bluePin, OUTPUT); //Set RGB LED 1
  
  pinMode(redPin2, OUTPUT); //Set RGB LED 2
  //pinMode(greenPin2, OUTPUT); //Set RGB LED 2
  //pinMode(bluePin2, OUTPUT); //Set RGB LED 2
  
  pinMode(redPin3, OUTPUT); //Set RGB LED 3
  //pinMode(greenPin3, OUTPUT); //Set RGB LED 3
  //pinMode(bluePin3, OUTPUT); //Set RGB LED 3
  
  pinMode(redPin4, OUTPUT); //Set RGB LED 4
  //pinMode(greenPin4, OUTPUT); //Set RGB LED 4
  //pinMode(bluePin4, OUTPUT); //Set RGB LED 4

   pinMode(internetPin, OUTPUT); //Set internetPin
   
  pinMode(buttonPin, INPUT); // set buttonPin
  connect();  // setup void connect()
}

//Function RGB LED 1
//void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
//{
 // analogWrite(redPin, red_light_value);
 // analogWrite(greenPin, green_light_value);
  //analogWrite(bluePin, blue_light_value);
//}

//Function RGB LED 2
//void RGB_color2(int red_light_value2, int green_light_value2, int blue_light_value2)
//{
 // analogWrite(redPin2, red_light_value2);
  //analogWrite(greenPin2, green_light_value2);
  //analogWrite(bluePin2, blue_light_value2);
//}

//Function RGB LED 3
//void RGB_color3(int red_light_value2, int green_light_value2, int blue_light_value2)
//{
  //analogWrite(redPin3, red_light_value3);
  //analogWrite(greenPin3, green_light_value3);
  //analogWrite(bluePin3, blue_light_value3);
//}

//Function RGB LED 4
//void RGB_color4(int red_light_value2, int green_light_value2, int blue_light_value2)
//{
 // analogWrite(redPin4, red_light_value4);
  //analogWrite(greenPin4, green_light_value4);
  //analogWrite(bluePin4, blue_light_value4);
//}

// Receive Messages you send
void messageReceived(String &topic, String &payload) {
    Serial.print("incoming: "); // you see serial monitor
    Serial.print(topic); // you see serial monitor
    Serial.print(" - "); // you see serial monitor
    if (topic == "/button1") { // received from Wendy
      if (payload == "1") { // if send "1" in loop
        //RGB_color(255, 0, 0); // Set color Red on first LED
        digitalWrite(redPin, HIGH);
        
        Serial.println("ON"); // you see serial monitor
      }
      else if (payload == "0") { // if send "0" in loop
        //RGB_color(0, 0, 0); // Set color White on first LED
        digitalWrite(redPin, LOW);
        Serial.println("OFF"); // you see serial monitor
      }
    }
    if (topic == "/button2") { // received from Pam
      if (payload == "1") { // if send "1" in loop
        //RGB_color2(255, 0, 0); // Set color Red on second LED
        digitalWrite(redPin2, HIGH);
        Serial.println("ON"); // you see serial monitor
      }
      else if (payload == "0") { // if send "0" in loop
        //RGB_color2(0, 0, 0); // Set color White on second LED
        digitalWrite(redPin2, LOW);
        Serial.println("OFF"); // you see serial monitor
      }
    }
    if (topic == "/button3") { // received from Jasper
      if (payload == "1") { // if send "1" in loop
        //
        digitalWrite(redPin3, HIGH);
        //RGB_color3(255, 0, 0); // Set color Red on third LED
        Serial.println("ON"); // you see serial monitor
      }
      else if (payload == "0") { // if send "0" in loop
        //RGB_color3(0, 0, 0); // Set color White on third LED
        digitalWrite(redPin3, LOW);
        Serial.println("OFF"); // you see serial monitor
      }
    }
    if (topic == "/button4") { // received from Veronika
      if (payload == "1") { // if send "1" in loop
        //RGB_color4(255, 0, 0); // Set color Red on fourth LED
        digitalWrite(redPin4, HIGH);
        Serial.println("ON"); // you see serial monitor
      }
      else if (payload == "0") { // if send "0" in loop
        //RGB_color4(0, 0, 0); // Set color White on fourth LED
        digitalWrite(redPin4, LOW);
        Serial.println("OFF"); // you see serial monitor
      }
    }
}

// Send Messages
void loop() {
  client.loop(); // loop through WiFi/MQTT client

  if (!net.connected()) { // connect
    connect();
  }

// @CHANGE
  int buttonClick = digitalRead(buttonPin); //digitalRead your button value HIGH or LOW

  if (millis() - lastMillis > 1000) {
    lastMillis = millis(); // equal to

    if (buttonClick != lastButtonClick) { // isn't equal
      if (buttonClick == 1) {
        buttonState = !buttonState; // opposite of buttonState
        if (buttonState == HIGH) { // if button pressed
          client.publish("/button2", "1"); // client /button2 send value "1"
          Serial.println("1"); // you see serial monitor
        } else { // if button not pressed
          client.publish("/button2", "0"); // client /button2 send value "0"
          Serial.println("0"); // you see serial monitor
        }
        delay(50); // wait for a moment
      }
      lastButtonClick = buttonClick; // equal to
    }

    
    lastMillis = millis(); // equal to
  }

  // Switch LED off internet LED when internet is connected
    if (status == WL_CONNECTED) {
      analogWrite(internetPin, 0); // turn internetPin off
      Serial.print("+");
    }

    lastMillis = millis(); // equal to
  }


  
}
