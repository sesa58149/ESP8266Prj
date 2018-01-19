#include <EEPROM.h>

/*********
 Pawan Modi
  Complete project details at 
*********/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define EXEC_FW_VER "1.0.000"
#define EEP_SIG_MAX_SIZE 3
#define SSID_MAX_SIZE 32
#define PASS_MAX_SIZE 32

typedef struct
{ 
  char ssid[SSID_MAX_SIZE];
  char password[PASS_MAX_SIZE];  
}WiFiInfo;

typedef struct{
  char eepromSignature[EEP_SIG_MAX_SIZE];
  WiFiInfo WAccessInfo;
}EEPROMStruct;


MDNSResponder mdns;
EEPROMStruct epromStruct;
void loadCredentials();
void saveCredentials();
String DeviceIP();
// Replace with your network credentials
const char* ssid_tmp = "belkin_PM";
const char* password_tmp = "pawan@158";

ESP8266WebServer server(2000);


void setup(void){
 
  Serial.begin(115200);
  Serial.println("");
  Serial.println(EXEC_FW_VER);
  loadCredentials();
  gpioSetup();

  delay(1000);
  
  WiFi.begin(epromStruct.WAccessInfo.ssid, epromStruct.WAccessInfo.password);
  Serial.println("");

  // Wait for connection
  Serial.print("Searching for Network :");
  Serial.println(epromStruct.WAccessInfo.ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(epromStruct.WAccessInfo.ssid);
  Serial.print("IP address: ");  
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/",handleHomePage);
  server.on("/homeIndex",handleHomePage); 
  server.on("/monitoring",handlerMonitoringNcontrol);
  server.on("/setOutput",handlesetOutput);
  server.on("/ScanNetwrok",handleScanNetwork);
  server.on("/config",handleDeviceConfig);
  server.on("/wifiSaveConf",handlewifiSaveConf);
  
  server.begin();
  Serial.println("HTTP server started");
 
}


void loop(void){
  server.handleClient();
} 



