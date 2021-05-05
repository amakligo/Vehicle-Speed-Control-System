//adding the new ping library
#include <NewPing.h>

//defining the trig pin on the first sensor
#define trigPin 11

//defining the echo pin in the first sensor
#define echoPin 10

//defining the trig pin for the second sensor
#define trigPin2 4

//defining the echo pin for the second
#define echoPin2 5

//defining the red led pin
#define redPin 7

//defining the green led pin
#define greenPin 8

//setting a constant variable to 50 cm
#define MAX_DISTANCE 50

//sensor position indicator
uint8_t currentSensor = 0;

//defining the time variables
unsigned int tm, tm1;

//creating an instance of the class NewPing as ping
NewPing pingg = NewPing(trigPin2, echoPin2, MAX_DISTANCE);

//creating another instance of the class New ping as sonar
NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE);


void setup() {
  //code runs once:

  //setting the baud rate to 9600
  Serial.begin(9600);

  //light strip pin modes
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}
 //declaring the variables as double
double one, two = 0, spd, tim, tim2, ftm;

void loop() {
  // put your main code here, to run repeatedly:

  //turns off the red led
  digitalWrite(redPin, 255);

  //turns ont the green led
  digitalWrite(greenPin, 0);

  //the distance conversion from the second sensor
  two = pingg.ping_cm();

  //the distance conversion from the first sensor
  one = sonar.ping_cm();

  //setting a timer and converting it to seconds
  tm = millis() / 1000.0;

  //displaying the timer in serial monitor
  Serial.println(tm / 1000.0);

  //if the first sensor picks a movement and the previous value in its time variable is 0
  if (one > 0 && tim == 0) {
    //set the time at which the sensor picks a movement
    tim = tm;

    //display the tm value in the serial monitor
    Serial.print("Condition ");
    Serial.print(tim);
  }

  //if the second sensor picks a movement and the previous value in its time variable is 0
  if (two > 0 && tim2 == 0) {
    //set the time at which the sensor picks a movement
    tim2 = tm;

    //display the tm2 value in the serial monitor
    Serial.print("Condition2= ");
    Serial.print(tim2);
  }

  //if the two time varibles are not 0 then compute the speed
  if (tim > 0 && tim2 > 0) {
    //get the absolute value of the difference in the two time variables
    ftm = abs(tim2 - tim);

    //compute the speed given the distance between the two sensors are known to be 100m
    spd = 100.0 / ftm;

    //display the values in the serial monitor
    Serial.print("final time= ");
    Serial.print(ftm);
    Serial.print("Speed= ");
    Serial.print(spd);


    //if the speed is above 50m/sec then turn on the red led
    if (spd > 50.0) {
      // This is where the LED On/Off happens
      // When the Red condition is met, the Green LED should turn off
      Serial.print("RED");

      //turn off the green LED
      digitalWrite(greenPin, 255);

      //turn on the red LED
      digitalWrite(redPin, 0);
    }

    //if there is no movement turn of the leds
    else if (spd == 0) {
      //turn of the green LED
      digitalWrite(greenPin, 255);

      //turn off the red LED
      digitalWrite(redPin, 255);
    } else {
      //turn on the green LED
      digitalWrite(greenPin, 0);

      //turn off the red LED
      digitalWrite(redPin, 255);
    }
  }

  //the speed variable still has the value that is not 0 then set all its parameters to 0
  if (spd > 0) {
    //set the speed variable to 0
    spd = 0;
    //set time variables to 0
    tim = 0;
    tim2 = 0;
  }

  //display the values
  Serial.print("One = ");
  Serial.println(one);
  Serial.print("Two = ");
  Serial.println(two);

  //delay the program for 0.5 seconds
  delay(500);
}
