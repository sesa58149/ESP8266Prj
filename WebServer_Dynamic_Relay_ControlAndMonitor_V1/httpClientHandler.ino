String tmpStr = " ";
void handleHomePage()
{
  tmpStr =  "<html> <head><style> body {background-color: rgb(50,100,50); }</style> </head> <body>";
  tmpStr += "<p style=text-align:center> <font size=+10 face = arial color=#FC5E3C>Home Automation System </font></p>";  
  tmpStr += "\r\n\r\n<p><a href=\"monitoring\"><button><font color=green>Device Monitoring and Control</font> </button></a>&nbsp;</p>";
  tmpStr += "\r\n <p><a href=\"config\"><button> <font color=green>Device Configuration </font></button></a>&nbsp;</p>";  
  tmpStr += "<p style=text-align:center> <font color=#F7BE8F size=5> Device Connected To WiFi Network :</font> <b><font size=4 color=orange>" 
              + String (epromStruct.WAccessInfo.ssid) + "</font></b> </p>"; 
              
  tmpStr += "\r\n\r\n<h1><font color=orange> Wifi Config </font></h1>" ;
  tmpStr += "<table border = 1><tr> <th> SSID</th> <th> Device IP</th></tr> <tr><td>" + String(epromStruct.WAccessInfo.ssid) +
              "</td> <td>" + DeviceIP()+"</td></tr> </table>" ;
            
  tmpStr += "<br> <p><a href=\"ScanNetwrok\"><button><font color=green size=3>Scan WiFi Devices </font></button></a> </p>";
  tmpStr +=  "</html>  </body>";
  
  server.send(200, "text/html", tmpStr);
}

void handleScanNetwork()
{   
  scanWiFiNetworkPage();        
  server.send(200, "text/html", tmpStr);        
}

void handlerMonitoringNcontrol()
{
  setOutputPage();
  server.send(200, "text/html", tmpStr); 
}

void handlesetOutput()
{

  int numArgs = server.args();
  for(int i=0; i<numArgs;i++)
  {
    String fieldName = server.argName(i);
    String fieldVal = server.arg(i);
    if(fieldName.equals("OUT1"))
    {
      if( fieldVal.equals("ON") )
      {
        setOut(0, LOW);
      }
      else
      {
        setOut(0, HIGH);
      }
    }
    if(fieldName.equals("OUT2") )
    {
      if(fieldVal.equals("ON") )
      {
        setOut(1, LOW);
      }
      else
      {
        setOut(1, HIGH);
      }      
    }
    if(fieldName.equals("OUT3") )
    {
      if( fieldVal.equals("ON") )
      {
        setOut(2, LOW);
      }
      else
      {
        setOut(2, HIGH);
      }      
    }
    if(fieldName.equals("OUT4") )
    {
      if( fieldVal.equals("ON") )
      {
        setOut(3, LOW);
      }
      else
      {
        setOut(3, HIGH);
      }      
    }
   
  }
  /*
  Serial.print("Number of Argument received Monitoring : \t");
  
  Serial.println();
  Serial.println(server.argName(0));
  Serial.println(server.argName(1));
  Serial.println(server.argName(2));
  Serial.println(server.argName(3));
  Serial.println(server.arg(0));
  Serial.println(server.arg(1));
  Serial.println(server.arg(2));
  Serial.println(server.arg(3));
  */
  setOutputPage();
  server.send(302, "text/html", tmpStr);
}

void handleDeviceConfig()
{
  wifiConfigPage();
  server.send(200, "text/html", tmpStr);
}

void handlewifiSaveConf()
{
  String tmpSsid= " ";
  String tmpPass= " ";
  
  Serial.print("Number of Argument received: \t");
  Serial.println(server.args()); 
  tmpSsid +=server.arg(0);
  tmpPass +=server.arg(1);
  
  Serial.print("SSID: \t");
  Serial.println(tmpSsid); 
  
  Serial.print("Password: \t");
  Serial.println(tmpPass); 
  
  
  wifiConfigPage();
  server.send(302, "text/html", tmpStr);
  
}
