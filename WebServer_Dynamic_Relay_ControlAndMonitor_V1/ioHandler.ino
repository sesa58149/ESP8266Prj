
#define MAX_DIO_SIZE  8
bool dout[MAX_DIO_SIZE];
int gpioPin[MAX_DIO_SIZE];
int gpioIn[MAX_DIO_SIZE];
int dIn[MAX_DIO_SIZE];

#define INVALID 0xFF

typedef struct
{
  int lastReadInput;
  int currentReadInput;
  int readCnt;  
}INPUT_READ_STRUCT;

INPUT_READ_STRUCT inputState[MAX_DIO_SIZE];

/*
output pins
D0->gpio16->MS LED
D1->gpio5-> Out0->Relay0
D2->gpio4-> Out1->Relay1
D3->gpio0-> Out2->Relay2
D4->gpio2-> Out3->Relay3
input pin
D5->gpio14->In0->button0
D6->gpio12->In1->button1
D7->gpio13->In2->button2
D8->gpio15->In3->button3
*/
uint8_t LED_Pin = D4;       // declare LED pin on NodeMCU Dev Kit


bool gpioSetup()
{
 /* gpioPin[0]= 5;
  gpioPin[1]= 4;
  gpioPin[2]= 0;
  gpioPin[3]= 2;*/
  gpioPin[0]= D1;
  gpioPin[1]= D2;
  gpioPin[2]= D3;
  gpioPin[3]= D4;
  for(int i=0; i<MAX_DIO_SIZE;i++)
  {
    dout[i]=HIGH;
    // preparing OUT PUT
    pinMode(gpioPin[i], OUTPUT);
    digitalWrite(gpioPin[i], dout[i]);
  } 
  setupMSled();

  gpioIn[0]= D5;
  gpioIn[1]= D6;
  gpioIn[2]= D7;
  gpioIn[3]= D8;
  for(int i=0; i<MAX_DIO_SIZE;i++)
  {
     pinMode(gpioIn[i], INPUT);
     inputState[i].currentReadInput=0;
     inputState[i].lastReadInput=0;
     inputState[i].readCnt=INVALID;    
     dIn[i]=0; 
  }

}

  /* setup module status LED @ freq 1sec*/
void setupMSled()
{
  pinMode(16,OUTPUT);  
}

void readInputPins()
{
  for(int i=0; i< MAX_DIO_SIZE;i++)
  {
    inputState[i].currentReadInput= digitalRead(gpioIn[i]);
    if(inputState[i].currentReadInput!= inputState[i].lastReadInput)
    {
      inputState[i].readCnt=0;
    }
    else
    {
      if(inputState[i].readCnt!= INVALID)
      {
        inputState[i].readCnt++;
      }
    }
    inputState[i].lastReadInput=inputState[i].currentReadInput;
    if(inputState[i].readCnt>=3 && inputState[i].readCnt!= INVALID)
    {
      dIn[i]= inputState[i].currentReadInput;
      inputState[i].readCnt=INVALID;
    }
  }
  
}

int* getInputStatus()
{
  return dIn;
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
     Serial.print("HW asigned pin=");
     Serial.println(gpioPin[outpin]);
     
     Serial.print("pin=");
     Serial.println(outpin);
     Serial.print("val=");
     Serial.println(val);
     ret=true; 
  }
  return ret;
}

void toggleOutput(int pin)
{
  if(pin<MAX_DIO_SIZE)
  {
    if(dout[pin]==HIGH)
    {
      dout[pin]=LOW;
    }
    else
    {
      dout[pin]=HIGH;
    }
    Serial.print("dout=");
    Serial.println(dout[pin]);
    digitalWrite(gpioPin[pin],dout[pin]);    
  }
  
}
void updateOutput(int* inStatus)
{
  for(int i=0; i<MAX_DIO_SIZE;i++)
  {
    if(inStatus[i]== 1)  
    {
     Serial.print("pinVal=");
     Serial.println(inStatus[i]);
     
     toggleOutput(i);
     inStatus[i]=0;
    }
  }
}

void updateMSLed()
{
  bool ms= digitalRead(16);
  if(ms==true)
  {
    digitalWrite(16,0);
  }
  else
  {
    digitalWrite(16,1);
  }
}
