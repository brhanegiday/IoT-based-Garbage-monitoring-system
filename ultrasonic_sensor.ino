int trigPin=3;
int echoPin=2;
int led=10;
// settng the threshold value of a dustpin
int threshold=10;
int buzzer=9;
long duration,distance_in_centmeter;
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
// read the signal from the sensor: a HIGH pulse 
// duration is the time in (microseconds) from the sending 
// of the pinng to the reception of its echo off of an object

pinMode(echoPin,HIGH);
duration=pulseIn(echoPin,HIGH);

distance_in_centmeter =  microseconds_to_centmeter(duration); // this calles the method microseconds_to_centmeter

//About the Buzzer
/*Tone needs 2 arguments, but can take three
    1) Pin#
    2) Frequency - this is in hertz (cycles per second) which determines the pitch of the noise made
    3) Duration - how long the tone plays
*/    
if (distance_in_centmeter <=threshold)
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
}

long microseconds_to_centmeter(long time_in_microseconds) {
 //convert the time into a distance
// speed of sound 340m/s
//distance=speed*duration=340m/s*duration
  return (time_in_microseconds/2)*0.0343;
}
