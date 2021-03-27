int inputpin = 6;
int outputpin = 2;
int state;
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

Toggle Fan1 = Toggle(inputpin, 500);

void setup()
{
  pinMode(outputpin, OUTPUT);
}

void loop()
{
  state = Fan1.updater();
  digitalWrite(outputpin, state);
}