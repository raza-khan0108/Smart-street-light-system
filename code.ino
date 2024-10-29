#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char ssid[] = {Your Wifi} ;
char pass[] = "Your Wifi password";

// Pin definitions
const int led1 = D5;        // LED pin
const int trigPin = D3;     // Trigger pin for ultrasonic sensor
const int echoPin = D4;      // Echo pin for ultrasonic sensor
const int buttonPin = D7;    // Panic button pin

bool detect = true;          // Detection flag
int intensity = 300;         // LED intensity (0-1023)

// Blynk Auth Token
char auth[] = "Your Auth Token here";

BlynkTimer timer;            // Create a Timer object
WidgetLED blynkled1(V1);     // Widget for Blynk LED

// Function to trigger radar and measure distance
int triggerRadar(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    int d = duration * 0.0343 / 2; // Calculate distance
    return d;
}

// Blynk Virtual Pin V3: Slider for LED intensity
BLYNK_WRITE(V3) {
    intensity = param.asInt(); // Assign incoming value from pin V3 to intensity
    Serial.println("LED intensity is set to: " + String(intensity));
}

// Blynk Virtual Pin V2: Control street light manually
BLYNK_WRITE(V2) {
    int pinValue = param.asInt(); // Get value from pin V2
    detect = (pinValue == 0);      // Set detect flag based on pin value
}

// Notify function for panic button
void notifyOnButtonPress() {
    int isButtonPressed = !digitalRead(buttonPin); // Check if button is pressed
    if (isButtonPressed) {
        Blynk.notify("Panic button pressed!"); // Send notification to Blynk app
    }
}

void setup() {
    Serial.begin(115200); // Start serial communication

    // Set pin modes
    pinMode(led1, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP); 

    // Setup PWM for LED using analogWrite (works with ESP8266)
    // Note: On ESP8266, D0 to D8 are used for PWM
    analogWriteRange(1023); // Set the range for analogWrite to 0-1023

    // Initialize Blynk
    Blynk.begin(auth, ssid, pass);
    
    // Attach interrupt for the panic button
    attachInterrupt(digitalPinToInterrupt(buttonPin), notifyOnButtonPress, FALLING);
    
    // Set timer to call updateChart every 2 seconds
    timer.setInterval(2000L, updateChart); 
}

void loop() {
    Blynk.run();   // Run Blynk
    timer.run();   // Run timer
}

// Function to update sensor readings and control logic
void updateChart() {
    int d = triggerRadar(trigPin, echoPin);   // Read distance from ultrasonic sensor
    int brightness = analogRead(A0);           // Read brightness value from light sensor
    
    if (brightness < 580 && detect) {          // At night
        if (d < 10) {                           // If a car is detected
            analogWrite(led1, 255);            // Set full brightness
            blynkled1.setValue(255);           // Update Blynk LED
        } else {
            analogWrite(led1, intensity);      // Set LED intensity
            int mappedIntensity = map(intensity, 0, 1023, 0, 255);
            blynkled1.setValue(mappedIntensity); // Update Blynk LED
        }
    } else {                                   // During the day
        blynkled1.off();                       // Turn off Blynk LED
        analogWrite(led1, 0);                  // Turn off LED
    }

    Serial.println("Distance: " + String(d)); // Debugging output for distance
    Serial.println("Brightness: " + String(brightness)); // Debugging output for brightness
    Blynk.virtualWrite(V0, brightness);       // Send brightness value to Blynk app

    notifyOnButtonPress();                     // Check for panic button press
}