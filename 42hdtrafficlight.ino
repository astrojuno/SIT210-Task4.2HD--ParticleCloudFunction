// SIT210 4.2HD
// Program to control 3 led's remotely via a web interface

// define the pins we'll be using
const pin_t redLED = D2;
const pin_t greenLED = D3;
const pin_t blueLED = D4;
// a variable to keep track of which pin is currently lit
pin_t current = NULL;

// love this line! Start your program running straight away before the 
// Particle connects to the web
SYSTEM_THREAD(ENABLED);

// Setup the program
void setup() {
    // set the pin modes
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
    
    // register the cloud function
    Particle.function("lights", cloudLEDBlink);
}

// nothing in here as we're just waiting for the signal from the 
// web interface
void loop() {
    
}

// the function exposed to the web interface
int cloudLEDBlink(String LEDColour) {
    // make sure we're dealing with a known case
    String ledToBlink = LEDColour.toLowerCase();
    // send it to the blinking function, if it's not valid it will just shut off
    // all the led's
    blinkLED(ledToBlink);
    // return 1 for correct paramater, -1 for failed
    if (ledToBlink == "red" || ledToBlink == "green" || ledToBlink == "blue") {
        return 1;
    }
    return -1;
}

// the function that actually does the blinking
// I wanted it to be such that you could not have more than one LED on at any one time
void blinkLED(String ledToBlink) {
    // start by turning all led's off
    turnAllLEDOff();
    // then, if the led sent was not already on, turn it on and set the current led
    // using if statements here as you can't switch on a string in arduino.
    if (ledToBlink == "red" && current != redLED) {
        digitalWrite(redLED, HIGH);
        current = redLED;
        return;
    } else if (ledToBlink == "green" && current != greenLED) {
        digitalWrite(greenLED, HIGH);
        current = greenLED;
        return;
    } else if (ledToBlink == "blue" && current != blueLED) {
        digitalWrite(blueLED, HIGH);
        current = blueLED;
        return;
    }
    // current set to null here as either we were turning an led off, or we were sent an incorrect colour
    current = NULL;
}

// simple function to turn all the led's off
void turnAllLEDOff() {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
}
