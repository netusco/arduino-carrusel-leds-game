int ledPins[] = {2,3,4,5,6,7,8};
int numPins = 7;
const int redPin = 5;
const int buttonPin = 12;
const int buzzerPin = 11;

boolean hasSound = true;
int punctuation;
int pause;
int lightPosition;
int failures;
int numMaxFailures = 1;

//What time it was when we last moved the light.
long lastMove = millis();

void setup() 
{
    for(int i=0; i<=sizeof(ledPins); i++) {
        pinMode(ledPins[i], OUTPUT);
    }
    
    pinMode(buttonPin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    
    newGame();
}

void loop() 
{
    carrusel();
}

void newGame() {
    pause = 1000;
    punctuation = 0;
    lightPosition = -1;
    failures = 0;
    
    snake();
}

void switchAllOff() 
{
    for(int i=0; i<=sizeof(ledPins); i++) {
        digitalWrite(ledPins[i], LOW);
    }
}

void carrusel() {
    
    // move the light
    if(millis() - lastMove >= pause) {
        
        // record the time when we move the light
        lastMove = millis();
        
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

void moveLight() {
    
    // switch last lights off
    if(lightPosition >= 0) {
        digitalWrite(ledPins[lightPosition], LOW);
    }
    
    nextLightPosition();
    
    digitalWrite(ledPins[lightPosition], HIGH);
}
                         
void nextLightPosition() {
    lightPosition++;
    
    if(lightPosition > numPins - 1) {
        lightPosition = 0;
    }
}

void success() {
    
    successSound();
    
    // blink redPin
    blinkLed(redPin, 2);
    
    // score points
    punctuation += 10;
        
    // reduce the pause
    pause -= abs(200 - (punctuation * 2));
}

void failure() {
    
    errorSound();
 
    // blink the led
    blinkLed(ledPins[lightPosition], 5);
    
    failures++;
    
    // loose points or game over
    if(punctuation == 0 || failures >= numMaxFailures) {
        gameOver();
    } else {
        punctuation -= 10;
    }
    
}

void errorSound() {
    if(hasSound) {
        tone(buzzerPin, 100, 500); 
    }
}

void successSound() {
    if(hasSound) {
        tone(buzzerPin, 530, 100);
        delay(150);            // wait for tone to finish  
        tone(buzzerPin, 530, 50);
    }
}

void blinkLed(int ledPin, int times) {
    
    for(int i=1; i<=times; i++) {
        digitalWrite(ledPin,LOW);
        delay(50);
        digitalWrite(ledPin,HIGH);
        delay(50);
    }
}

void gameOver() {
    
    // display punctuation bar
    punctuationBar();
    
    // start new game
    newGame();
}

void punctuationBar() {
 
    int ledPoints = round(punctuation/10/2);
    
    delay(1000);

    if(punctuation > 0) {
        
        switchAllOff();
        delay(1000);

        if(ledPoints > numPins) {
            ledPoints = numPins;
        }

        for(int i= 0; i < ledPoints; i++) {
            digitalWrite(ledPins[i], HIGH);
            delay(200);
        }

        delay(2000);
    }
    
    switchAllOff();
    delay(500);
}




void snake() {
    int index;
    int delayTime = 60;

    // step through the LEDs, from 0 to 7
  
    for(index = 0; index <= numPins; index++)
    {
        digitalWrite(ledPins[index], HIGH);  // turn LED on
        delay(delayTime);                    // pause to slow down
        digitalWrite(ledPins[index], LOW);   // turn LED off
    }

    // step through the LEDs, from 7 to 0

    for(index = numPins -2; index >= 0; index--)
    {
        digitalWrite(ledPins[index], HIGH);  // turn LED on
        delay(delayTime);                    // pause to slow down
        digitalWrite(ledPins[index], LOW);   // turn LED off
    }
    
    delay(1000);
}