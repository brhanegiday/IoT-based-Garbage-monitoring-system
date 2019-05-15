<br data-mce-bogus="1">
 
#include &lt;Timer.h&gt;
Timer t;
 
#include &lt;Wire.h&gt;
#include &lt;LiquidCrystal.h&gt;
#include &lt;SoftwareSerial.h&gt;
SoftwareSerial esp8266(2,3);      /* This will make the pin 2 of arduino as RX pin and
pin 3 of arduino as the TX pin Which means that you have to connect the TX from the esp8266*/
#define DEBUG true
const int trigPin = 8;            // Making the arduino's pin 8 as the trig pin of ultrasonic sensor
const int echoPin = 9;            // Making the arduino's pin 9 as the ec
pinMode(trigPin, OUTPUT);   // Setting the trigPin as Output pinho pin of the ultrasonic sensor
// defining two variable for measuring the distance
long duration;
int distance;
 
void setup()
{
	Serial.begin(9600);//setting the baudrate at 9600
	esp8266.begin(11520);//setting the baud rate of the ESP8266
 
    pinMode(trigPin, OUTPUT);   // Setting the trigPin as Output pin
	pinMode(echoPin, INPUT);    // Setting the echoPin as Input pin

 
///////////////////////////////////////////////
//
// Connecting WIFI
//
//
 
Serial.begin(115200); // Baud rate of esp8266
Serial.println(F("Connecting Wifi...."));
Serial.println(F("Connecting Wifi...."));
 

connect_wifi("AT\r\n",6000,DEBUG); // time in milliseconds
connect_wifi("AT+RST\r\n",6000,DEBUG); // reseting esp
connect_wifi("AT+CWMODE=3\r\n",6000,DEBUG); // setting esp to both AP and station mode
connect_wifi("AT+CIFSR\r\n",6000,DEBUG); // This command will get the ip address
connect_wifi("AT+CIPMUX=1\r\n",6000,DEBUG);       // This will configure the esp for multiple connections
//connect_wifi("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // This command will turn on the server on port 80
connect_wifi("AT+CWJAP\r\n"="AAU-AAiT-Student","AAiT@Student!",6000); // Connecting wifi to router with SSID and Password.
//connect_wifi("AT+CWJAP=\"Testing\",\"12345\"",6000); // For example Wifi name= Testing &amp; Password=12345
 
delay(5000);
Serial.println(F("Wifi Connected"));
 
delay(2000);
 
t.every(3000, send2server); // 1000 milli seconds = 1 minute // timer.h class object
 
}
 
void loop()
{

digitalWrite(trigPin,LOW);// making the trig pin as low
delayMicroseconds(2);
digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);

t.update();
}
 
void send2server()
{
dustbin_height=120;// height of the dustbin in centmeter
duration=pulseIn(echoPin,HIGH);//reading the echo pin which tell us that how much time the signal takes to come back 
distance=duration*0.034/2;//calculating the distance and storing in the distance variable
STATUS=(dustbin_height-distance)*100/dustbin_height;
empty_status=(distance/dustbin_height)*100;
 
String postUrl="/localhost/IoT/registration/register.php?STATUS=";
postUrl.concat(STATUS);
postUrl+="&empty_status=";
postUrl.concat(empty_status);
 
Serial.println(postUrl);
httpGet("169.254.189.30", postUrl, 80);
 
}
 
void httpGet(String ip, String path, int port)
{
 
String atHttpGetCmd = "GET "+path+" HTTP/1.0\r\n\r\n"; // GET /status.php?slot1=1&amp;slot2=0&amp;slot3=0...
Serial.println(atHttpGetCmd);
//AT+CIPSTART="TCP","192.168.20.200",80
String atTcpPortConnectCmd = "AT+CIPSTART=\"TCP\",\""+ip+"\","+port+""; /// establishing a TCP conection with ip and port
Serial.println(atTcpPortConnectCmd);
connect_wifi(atTcpPortConnectCmd,1000,DEBUG);
int len = atHttpGetCmd.length();
Serial.println(len);
String atSendCmd = "AT+CIPSEND=";
atSendCmd+=len;
connect_wifi(atSendCmd,1000,DEBUG); /// sending data length to server for confirmation of its length.
connect_wifi(atHttpGetCmd,1000,DEBUG); // sending data to server
Serial.println(ip);
}
 
void connect_wifi(String cmd, int timeout,boolean debug)
{
String response="";
esp8266.print(cmd);
long int time=millis();

while((time+timeout)>millis())
{
while(esp8266.available())
{//lcd.clear();
//lcd.print(cmd);
	char c=esp8266.read();
	response+=c;

}
}
if (debug)
{
	Serial.print(response);
	lcd.setCursor(0,1);
	lcd.print("OK");

}
else
{
	Serial.println("Error");
	// lcd.setCursor(0,1);
    // lcd.print("Error");
}
return response;
}
<pre>