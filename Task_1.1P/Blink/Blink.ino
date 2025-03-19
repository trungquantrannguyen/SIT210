/*
  Blink


  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/
#include <unordered_map>
#include <iostream>
int shortTime = 100;
int longTime = 300;
int spaceTime = 700;
int pin = 2;

using namespace std;

unordered_map<char,string> morseCodeDictionary = {
        {'A', ".-"},   {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
        {'E', "."},    {'F', "..-."}, {'G', "--."},  {'H', "...."},
        {'I', ".."},   {'J', ".---"}, {'K', "-.-"},  {'L', ".-.."},
        {'M', "--"},   {'N', "-."},   {'O', "---"},  {'P', ".--."},
        {'Q', "--.-"}, {'R', ".-."},  {'S', "..."},  {'T', "-"},
        {'U', "..-"},  {'V', "...-"}, {'W', ".--"},  {'X', "-..-"},
        {'Y', "-.--"}, {'Z', "--.."}, {'1', ".----"},
        {'2', "..---"},{'3', "...--"},{'4', "....-"},
        {'5', "....."},{'6', "-...."},{'7', "--..."},
        {'8', "---.."},{'9', "----."},{'0', "-----"}
    };

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  
  string myName = "QUAN";

  for (int i = 0; i < myName.length(); i++){
    if(myName[i] == ' '){
      delay(spaceTime);
    }
    if(morseCodeDictionary.find(myName[i]) != morseCodeDictionary.end()){
      string charMorseCode = morseCodeDictionary[myName[i]];
      for(int j = 0; j < charMorseCode.length(); j++){
        if(charMorseCode[j] == '-'){
          blink(longTime);
        }
        else if (charMorseCode[j] == '.'){
          blink(shortTime);
        }
        delay(longTime);
      }
    }
  }
}

void blink(int timing){
    digitalWrite(pin, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(timing);                      // wait for a second
  digitalWrite(pin, LOW);   // turn the LED off by making the voltage LOW
  delay(shortTime); 
}
