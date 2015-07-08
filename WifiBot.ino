
#include <SoftwareSerial.h>

#define MotDir_IN1 11
#define MotDir_IN2 12

#define MotProp_IN1 9
#define MotProp_IN2 10

#define PPS 6

String rcv, rcvGPS;
float Latitude, Longitude;
char NorthSouth;
char EastWest;

SoftwareSerial GPSSerial(3,2); // RX,TX

void setup()
{
   Serial.begin(9600);
  
   GPSSerial.begin(115200);

   GPSSerial.print("$PMTK1000,200*2C\r\n");
   delay(200);
   GPSSerial.print("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
   delay(200);
   GPSSerial.print("$PMTK300,1000,0,0,0,0*1C\r\n");
   delay(200);
   
 
   
   pinMode(MotDir_IN1,OUTPUT); 
   pinMode(MotDir_IN2,OUTPUT); 
   pinMode(MotProp_IN1,OUTPUT); 
   pinMode(MotProp_IN2,OUTPUT);
   pinMode(2,OUTPUT); 
   pinMode(3,INPUT);
   pinMode(PPS,INPUT);
 
   digitalWrite(MotDir_IN1,LOW);
   digitalWrite(MotDir_IN2,LOW);

   delay(1000);
  
   Serial.println("Drone Online");
 
 

 
   
}



void loop()
{
    
    if (Serial.available() > 0)
    {
     rcv = Serial.readStringUntil('\r');
     //Serial.println(rcv);
    }
    
    /*
   if (GPSSerial.available() > 0)
   { 
     rcvGPS = GPSSerial.readStringUntil('\n');
     Latitude = (rcvGPS.substring(20, 30)).toFloat();
     Longitude = (rcvGPS.substring(32, 43)).toFloat();
     NorthSouth = rcvGPS.charAt(31);
     NorthSouth = rcvGPS.charAt(44);
     Serial.print("Latitude: ");
     Serial.println(Latitude);
     Serial.print("Longitude: ");
     Serial.println(Longitude);
     
     Serial.println(rcvGPS);
   }
   */
   if(rcv.equals("forward"))
   {
     Motors(0,100,1);
   }
   else if (rcv == "backward")
   {
     Motors(0,100,-1);
   }
   else if (rcv == "left")
   {
     Motors(1,100,1);     
   }
   else if (rcv == "right")
   {
     Motors(-1,100,1);      
   }
   else if (rcv == "stop")
   {
     Motors(0,0,1); 
   }
   delay(100);
   rcv="";
  
   
    //Motors(1,100,1);
    //delay(1000);
    //Motors(-1,100,1);
    //delay(1000);
    
  
}




void Motors(int Dir,int Speed,int ForwBackw)
{
  if(Dir == 1)
  {
    digitalWrite(MotDir_IN1,HIGH);
    digitalWrite(MotDir_IN2,LOW);
  } 
  else if(Dir == -1)
  {
    digitalWrite(MotDir_IN1,LOW);
    digitalWrite(MotDir_IN2,HIGH);
  } 
  else
  {
    digitalWrite(MotDir_IN1,LOW);
    digitalWrite(MotDir_IN2,LOW);
    analogWrite(MotProp_IN1,0);
    analogWrite(MotProp_IN2,0);
  } 
  
  if(ForwBackw == -1)
  {
    analogWrite(MotProp_IN1,0);
    analogWrite(MotProp_IN2,Speed);
  }
  else if (ForwBackw == 1)
  {
    analogWrite(MotProp_IN1,Speed);
    analogWrite(MotProp_IN2,0);
  }
  
}

