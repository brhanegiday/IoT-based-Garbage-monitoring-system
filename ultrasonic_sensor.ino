int trigPin=12;
int echoPin=11;
int led=10;
// settng the threshold value of a dustpin
int threshold=10;
int buzzer=9;
long duration,distance;
void setup() {

//Serial Port begin
Serial.begin (9600);
//Define inputs and outputs
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(led,OUTPUT); 
pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

digitalWrite(led,LOW);
// read the signal ffrom the sensor: a HIGH pulse 
// duration is the time in (microseconds) from the sending 
// of the pinng to the reception of its echo off of an object

pinMode(echoPin,HIGH);
duration=pulseIn(echoPin,HIGH);

//convert the time into a distance
// speed of sound 340m/s
//distance=speed*duration=340m/s*duration

distance=(duration/2)*29.1;// Divide by 29.1 or multiply by 0.0343

//About the Buzzer
/*Tone needs 2 arguments, but can take three
    1) Pin#
    2) Frequency - this is in hertz (cycles per second) which determines the pitch of the noise made
    3) Duration - how long the tone plays
*/    
if (distance <=threshold)
{
  //blink LED
  digitalWrite(led,HIGH);
  Serial.println("Trash Can is FULL");
  tone(buzzer,1000,500);  // send 1KHz sound signal
  delay(1000);        // delay for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // delay for 1sec
}
else
{}

Serial.print("Distance is: ");
Serial.print(distance);
Serial.println();
delay(250);
}
