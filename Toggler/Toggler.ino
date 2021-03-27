/*This is a simple button toggling program for arduino
The input here is pin 6 is connected to button.
           10 K
5V -----/\/\/\/\----- Ground
                  |
                  |
                 |O| Button
                  |
                Pin 6
The Output pin is 2 
            LED       220 Ohms
Pin 2 ------|>|-----/\/\/\/\----- Ground
This program used some parts of another program from Blinkwithoutdelay.
http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
Modified by Karthhic 2021
*/
int inputpin = 6;
int outputpin = 2;
/*
 * TOGGLE CLASS DEFINITION
 */
class Toggle
{
  private:
    int state = LOW;      // the current state of the output pin
    int reading;           // the current reading from the input pin
    int previous = LOW;    // the previous reading from the input pin

    long time_ = 0;         // the last time the output pin was toggled
    long debounce = 200;   // the debounce time, increase if the output flickers
    bool now(int inPin);
    int inputpin;

  public:
    Toggle(int input, long debounce) {
        this->inputpin = input;
        this->debounce = debounce;

        pinMode(inputpin, INPUT);
    }

    bool updater(){
        reading = digitalRead(inputpin);
        if (reading == HIGH && previous == LOW && millis() - time_ > debounce) {
            if (state == HIGH)
                state = LOW;
            else
                state = HIGH;
        
        time_ = millis();
        }
        Serial.print(state);
        previous = reading;
        return state;
        
    }

};


/*
 *  CLASS VARIABLES DECLARATION
 */

Toggle Button = Toggle(inputpin, 500);

void setup()
{
  pinMode(outputpin, OUTPUT);
}

void loop()
{
  digitalWrite(outputpin, Button.updater());
}