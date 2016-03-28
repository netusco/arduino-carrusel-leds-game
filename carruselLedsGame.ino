/* Carrusel led's light game
 * 
 * created 2016 
 * by Ernest Conill
 */
int ledPins[] = {2,3,4,5,6,7,8};
int numPins = 7;

// target middle pin
const int redPin =5;
const int buttonPin = 12;
const int buzzerPin = 11;

// set to false if there is no buzzer
boolean hasSound = true;

int punctuation;
int punctuationGain = 10;
int pause;
int lightPosition;

// failures counter and num. max of failures to allow failures if wanted
int failures;
int numMaxFailures = 1;

// what time it was when we last moved the light.
long lastMove = millis();

// where the initialization and setup of the game takes place
void setup() 
{
    // initializing pins for the leds
    for(int i=0; i<=sizeof(ledPins); i++) {
        pinMode(ledPins[i], OUTPUT);
    }
    
    // initializing the button pin
    pinMode(buttonPin, INPUT);

    // initializing the buzzer pin
    pinMode(buzzerPin, OUTPUT);
    
    // initializing main game variables
    newGame();
}

// hosts the code that runs all the time
void loop() 
{
    // the game method
    carrusel();
}

// initialization of main game vars plus running the snake lights
void newGame() {
    pause = 1000;
    punctuation = 0;
    lightPosition = -1;
    failures = 0;
    
    snake();
}

// switches all leds off
void switchAllOff() 
{
    for(int i=0; i<=sizeof(ledPins); i++) {
        digitalWrite(ledPins[i], LOW);
    }
}

// the game method
void carrusel() {
    
    // move the light
    if(millis() - lastMove >= pause) {
        
        // record the time when we move the light
        lastMove = millis();
        
        // moves to the next light
        moveLight();
    }
    
    // when button is pressed
    if(digitalRead(buttonPin) == HIGH) {
     
        // red pin
        if(ledPins[lightPosition] == redPin) {
            
            success();
        }
        // yellow pin
        else {
            
            failure();
        }
    }
}

// switches of the current light and switches on the next one
void moveLight() {
    
    // switch last light off
    if(lightPosition >= 0) {
        digitalWrite(ledPins[lightPosition], LOW);
    }
    
    // gets the next light position
    nextLightPosition();
    
    // switch on next light
    digitalWrite(ledPins[lightPosition], HIGH);
}
 
// gets the next light position                        
void nextLightPosition() {
    lightPosition++;
    
    // set lightPosition within limits
    constrain(lightPosition, 0, numPins - 1);
}

// success method
void success() {
    
    // emits success sound
    successSound();
    
    // blink redPin
    blinkLed(redPin, 2);
    
    // score points
    punctuation += punctuationGain;
        
    // reduce the pause
    pause -= abs(200 - (punctuation * 2));
}

// failure method
void failure() {
    
    // emits failure sound
    errorSound();
 
    // blink the led
    blinkLed(ledPins[lightPosition], 5);
    
    failures++;
    
    // loose points or game over
    if(punctuation == 0 || failures >= numMaxFailures) {
        gameOver();
    } else {
        punctuation -= punctuationGain;
    }
    
}

// emits failure sound
void errorSound() {
    if(hasSound) {
        tone(buzzerPin, 100, 500); 
    }
}

// emits success sound
void successSound() {
    if(hasSound) {
        tone(buzzerPin, 530, 100);
        delay(150);            // wait for tone to finish  
        tone(buzzerPin, 530, 50);
    }
}

// blinks the target led as many times as required by times variable
void blinkLed(int ledPin, int times) {
    
    for(int i=1; i<=times; i++) {
        digitalWrite(ledPin,LOW);
        delay(50);
        digitalWrite(ledPin,HIGH);
        delay(50);
    }
}

// game over method (displays punctuation bar, resets main game variables)
void gameOver() {
    
    // display punctuation bar
    punctuationBar();
    
    // start new game
    newGame();
}

// display the punctuation bar
void punctuationBar() {
 
    // points translated to led lights are half the punctuation divided by punctuationGain
    int ledPoints = round(punctuation/punctuationGain/2);
    
    delay(1000);

    if(punctuation > 0) {
        
        switchAllOff();
        delay(1000);

        // constraint the max ledPoints to the numPins
        if(ledPoints > numPins) {
            ledPoints = numPins;
        }
        
        // switch as much leds as ledPoints
        for(int i= 0; i < ledPoints; i++) {
            digitalWrite(ledPins[i], HIGH);
            delay(200);
        }

        delay(2000);
    }
    
    switchAllOff();
    delay(500);
}

// sanke light like effect
void snake() {
    int index;
    int delayTime = 60;

    // step through the LEDs, lighting them from 0 to 7
    for(index = 0; index <= numPins; index++)
    {
        digitalWrite(ledPins[index], HIGH);  // turn LED on
        delay(delayTime);                    // pause to slow down
        digitalWrite(ledPins[index], LOW);   // turn LED off
    }

    // step through the LEDs, switching them off from 7 to 0
    for(index = numPins -2; index >= 0; index--)
    {
        digitalWrite(ledPins[index], HIGH);  // turn LED on
        delay(delayTime);                    // pause to slow down
        digitalWrite(ledPins[index], LOW);   // turn LED off
    }
    
    delay(1000);
}
