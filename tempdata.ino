//Added by the particle 
#include <ThingSpeak.h>



int analogvalue = 0;
int temp_f;

//The TcpClient class provides simple methods for connecting, sending, and receiving stream data over a network in synchronous blocking mode.
TCPClient client;

//Defininf the ThingSpeak Channel Details 
unsigned long myChannelNumber = 2109260;
const char * myWriteAPIKey = "6QWBZMO0KP5YGTIK";

void setup()
{
    ThingSpeak.begin(client);
  
    Particle.variable("analogvalue", analogvalue);
    Particle.variable("temp_f", temp_f);
 
    Serial.begin(9600);

    pinMode(A0, INPUT);
}

void loop()
{
    delay(1500);
  // Read the analog value of the sensor (TMP36)
    analogvalue = analogRead(A0);
  //Convert the reading into degree 
    temp_f = (analogvalue*-.08099688473520249+151.99688473520249); //To be accurate
  //temp = 69;
  
  
    Particle.publish("temperature",String (temp_f), ALL_DEVICES);// sends data to cloud
    ThingSpeak.setField(1,temp_f);
    Serial.print(temp_f);
    Serial.println("temp_f");
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(30000);

}