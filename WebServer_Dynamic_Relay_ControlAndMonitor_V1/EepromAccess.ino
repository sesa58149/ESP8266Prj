void readEEPROM(char *data, int startAdd, int nByte)
{
  int i=0;
  
  for(i=0; i < nByte; i++)
  {
    data[i] = EEPROM.read(startAdd);
    startAdd++;
  }
}

void writeEEPROM(char *data, int startAdd, int nByte)
{
  int i=0;
  
  for(i=0; i < nByte; i++)
  {
    EEPROM.write(startAdd,data[i]);
    startAdd++;
  }
}
/** Load WLAN credentials from EEPROM */
void loadCredentials() {
  int i=0,j;
  Serial.println("loading the credentials");
  EEPROM.begin(512);
  char ssid[SSID_MAX_SIZE];
  char password[PASS_MAX_SIZE];
 
 
  readEEPROM(epromStruct.eepromSignature,0,EEP_SIG_MAX_SIZE);
  if(epromStruct.eepromSignature[0]!='O' || epromStruct.eepromSignature[1]!='K' )
  {
    /* EEPROM uninitialzed have to initialize with default value */
    strcpy(ssid, ssid_tmp);
    strcpy(password,password_tmp);
    writeEEPROM("OK", 0, EEP_SIG_MAX_SIZE);
    writeEEPROM(ssid, sizeof(epromStruct.eepromSignature), SSID_MAX_SIZE);
    writeEEPROM(password, sizeof(epromStruct.eepromSignature) +sizeof(epromStruct.WAccessInfo.ssid), PASS_MAX_SIZE);
    
  }
  else
  {
    readEEPROM(epromStruct.WAccessInfo.ssid,sizeof(epromStruct.eepromSignature),SSID_MAX_SIZE);
    readEEPROM(epromStruct.WAccessInfo.password,sizeof(epromStruct.eepromSignature) 
               +sizeof(epromStruct.WAccessInfo.ssid) ,PASS_MAX_SIZE);
               
    Serial.println("EEPROM have Vaild Configuration");
  }
  EEPROM.end();
}

/** Store WLAN credentials to EEPROM */
void saveDefaultCredentials() {
  /*
  //EEPROM.begin(512);
int i,j;
 for(i=0;i<=15;i++){
   EEPROM.write(i,ssid[i]);   
   EEPROM.commit();
   delay(100);
  } 
  
  for(j=0;j<=15; j++,i++){
   EEPROM.write(i,password[j]);
   EEPROM.commit();
   delay(100);
  }
  
  char ok[3]="OK";

   for(j=0;j<=2; j++,i++){
    EEPROM.write(i,ok[j]);
    EEPROM.commit();
    delay(100);
      }
 

  
  //EEPROM.put(0, ssid_tmp);
  //EEPROM.put(0+sizeof(ssid_tmp), password_tmp);
//  char ok[2+1] = "OK";
  //EEPROM.put(0+sizeof(ssid_tmp)+sizeof(password_tmp), ok);
  
  EEPROM.end();
  */
}

/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  /*
  Serial.println("Storing default credentials");
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(0+sizeof(ssid), password);
  char ok[2+1] = "OK";
  EEPROM.put(0+sizeof(ssid)+sizeof(password), ok);
  EEPROM.commit();
  EEPROM.end();
  */
}

