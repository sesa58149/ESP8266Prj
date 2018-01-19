
#define MAX_DIO_SIZE  8
bool dout[MAX_DIO_SIZE];
int gpioPin[MAX_DIO_SIZE];



bool gpioSetup()
{
  gpioPin[0]= 12;
  gpioPin[1]= 13;
  gpioPin[2]= 5;
  gpioPin[3]= 4;
  for(int i=0; i<MAX_DIO_SIZE;i++)
  {
    dout[i]=HIGH;
    // preparing OUT PUT
    pinMode(gpioPin[i], OUTPUT);
    digitalWrite(gpioPin[i], dout[i]);
  } 

}
  

String ioStatus(int outpin)
{  
  String OStatus = "ON";
  if(outpin < MAX_DIO_SIZE){
    if( dout[outpin] == HIGH) // OFF 
    {
      OStatus = "OFF";
    }
  }
  else{
   OStatus = "UNKNOWN";
  }

  //Serial.println(OStatus);
  return OStatus;    
}
bool setOut(int outpin, bool val)
{
  bool ret = false;
  if(outpin < MAX_DIO_SIZE){
     dout[outpin]=val;
     digitalWrite(gpioPin[outpin],val);
     ret=true; 
  }
  return ret;
}


