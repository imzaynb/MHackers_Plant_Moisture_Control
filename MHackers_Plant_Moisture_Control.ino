// Initialize Pins
const int moisture = A0;
const int redLED = 0;
const int yellowLED = 1;
const int greenLED = 2;
const int transistor = 3;

// Set up constants for moisture readings.
// TODO: get moisture levels for 0% and 100%
const int zeroPercentMoisture    = 0; // To gather this value, read the value from the sensor when dry and exposed to air.
const int hundredPercentMoisture = 0; // To gather this value, read the value from the sensor when submerged in water.

// Initialize LED states
int greenState = LOW;
int yellowState = LOW;
int redState = LOW;

long readMoisture();
void controlLEDS(long moisture);
void controlPump();
void controlLCD();

void setup()
{
  pinMode(moisture, INPUT);
  pinMode(transistor, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  long moisture = readMoisture();
  
  controlLEDS(moisture);
  controlLCD();
  controlPump();
  
  delay(100);
}

long readMoisture() {
  int moistureReading = analogRead(moisture);
  // map(value, fromLow, fromHigh, toLow, toHigh)
  long moisturePercent = map((long)moisture, 
                             zeroPercentMoisture, hundredPercentMoisture,
                             0, 100);

  Serial.println(moistureReading);
  Serial.println(moisturePercent);

  return moisturePercent;
}

void controlLEDS(long moisture) {
  if(moisture > 80) {
    greenState  = HIGH;    
    yellowState = LOW;
    redState    = LOW;
  } else if(moisture < 20){
    greenState  = LOW;    
    yellowState = LOW;
    redState    = HIGH;
  } else {
    greenState  = LOW;    
    yellowState = HIGH;
    redState    = LOW;
  }

  digitalWrite(greenLED,  greenState);
  digitalWrite(yellowLED, yellowState);
  digitalWrite(redLED,    redState);
}

void controlLCD(long moisture) {
  (void) moisture;
  // TODO: write to the LCD screen.
}

void controlPump(long moisture) {
  digitalWrite(transistor, HIGH);
  (void) moisture;
  // TODO: do something with the moisture.
}
