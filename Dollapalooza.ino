/*
  Sketch created by Matthew Barry, Nicholaus Gutierrez, and Robin Wharton
  for Physical Computing and Desktop Fabrication at Digital Humanities
  Summer Institute 2016.
  
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  Also integrates Arduino code "Melody" available at
  https://www.arduino.cc/en/tutorial/melody.
  
 */

int speakerPin = 9;

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

// These constants won't change:
const int photocellPin = A5;    // pin that the sensor is attached to
const int ledredPin = 4;       // pin that the LED is attached to
const int ledgreenPin = 7;       // pin that the LED is attached to
const int threshold = 175;   // an arbitrary threshold level that's in the range of the analog input

void playSong() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2); 
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(ledredPin, OUTPUT);
  pinMode(ledgreenPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
 
  // initialize serial communications:
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // read the value of the potentiometer:
  int analogValue = analogRead(photocellPin);

  // if the analog value is high enough, turn on the LED:
  if (analogValue <= threshold) {
    digitalWrite(ledredPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    playSong();
    digitalWrite(ledredPin, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
  } else {
    digitalWrite(ledgreenPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    playTone(4000, 100);
    delay(1000);              // wait for a second
    digitalWrite(ledgreenPin, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
  }

  // print the analog value:
  Serial.println(analogValue);
  delay(1);        // delay in between reads for stability  
}
