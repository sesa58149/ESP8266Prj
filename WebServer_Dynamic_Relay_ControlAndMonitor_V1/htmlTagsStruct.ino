
extern String tmpStr;

void wifiConfigPage()
{
  tmpStr =  "<html> <head><style> body {background-color: rgb(50,100,50); }</style> </head> <body>";
  tmpStr += "<p style=text-align:center> <font size=10 face = arial color=#FC5E3C>Home Automation System </font></p>";  
  tmpStr += "\r\n<br /><form method=POST action=wifiSaveConf><h1><font color=#F7BE8F> WiFi network Configuration : </font></h1>\
          <p>  <font size=5 color=orange>SSID      </font></p> <input type=text placeholder=network name=n/> \
          <p> <font size=5 color=orange>Password   </font></p> <input type=password placeholder=password name=p/>\
          <br>  <input type=submit value=\"Save Configuration\"/></form>";
  tmpStr +=  "</html>  </body>";
  tmpStr += "<p><a href=\"homeIndex\"><button align=center><font size=+2 color=green>Home </font></button></a>&nbsp;</a></p>";
}

void setOutputPage()
{
  tmpStr =  "<html> <head> <style> body {background-color: rgb(50,100,50); }</style> </head> <body>";  
  tmpStr += "<p style=text-align:center> <font size=+10 face = arial color=#FC5E3C>Home Automation System </font></p>";  
  tmpStr += "<p style=text-align:center> <font size=+2 face = arial color=#F7BE8F> Monitoring and Control</font></p>";             
  tmpStr += "<p><a href=\"homeIndex\"><button align=center><font size=+2 color=green>Home </font></button></a>&nbsp;</a></p>";
  
  tmpStr += "\r\n<form method=POST action=setOutput> <p> <font size=7 face = arial color=orange> Output selection</font></p>"; 
  
  tmpStr += "<br><p><font size=5 color=#DF1958> <b>Output-1</b></font></p>";
  tmpStr += "<div><input type=radio name=OUT1 value=ON> ON  &nbsp;&nbsp;&nbsp; \t OutputStatus =" + String(ioStatus(0))  +"<br/>";  
  tmpStr += "<input type=radio name=OUT1 value=OFF > OFF </div>"; 
  
  tmpStr += "<br><p><font size=5 color=#DF1958> <b>Output-2</b></font></p>";
  tmpStr += "<div><input type=radio name=OUT2 value=ON> ON   &nbsp;&nbsp;&nbsp; \t OutputStatus =" + String(ioStatus(1))  +"<br/>";
  tmpStr += "<input type=radio name=OUT2 value=OFF > OFF </div>";
  
  tmpStr += "<br><p><font size=5 color=#DF1958> <b>Output-3</b></font></p>"; 
  tmpStr += "<div><input type=radio name=OUT3 value=ON> ON   &nbsp;&nbsp;&nbsp; \t OutputStatus =" + String(ioStatus(2))  +"<br/>";
  tmpStr += "<input type=radio name=OUT3 value=OFF> OFF </div>"; 
  
  tmpStr += "<br><p><font size=5 color=#DF1958> <b>Output-4</b></font></p>";
  tmpStr += "<div><input type=radio name=OUT4 value=ON> ON    &nbsp;&nbsp;&nbsp \t OutputStatus =" + String(ioStatus(3))  +"<br/>";
  tmpStr += "<input type=radio name=OUT4 value=OFF> OFF <br/></div>"; 
  
  tmpStr += "<br><div> <input type=submit value=\" Write Output\"></div> </form>";

  tmpStr +=  "</html>  </body>";
}

void scanWiFiNetworkPage()
{
  tmpStr =  "<html> <head><style> body {background-color: rgb(50,100,50); }</style> </head> <body>";
  tmpStr += "<p style=text-align:center> <font size=+10 face = arial color=#FC5E3C>Home Automation System </font></p>";
  tmpStr += "<h1 style=text-align:center> <font size+=10 color=#F7BE8F > Wifi Device List </font> </h1>" +String("<p> Device Is Connected To WiFi Network : <b>") + String (epromStruct.WAccessInfo.ssid) + "</b> </p>"; 
  tmpStr += "\r\n <br><table border = 1><tr> <th> SSID</th> <th> Device IP</th></tr> <tr><td>" + String(epromStruct.WAccessInfo.ssid) + "</td> <td>" 
              + DeviceIP()+"</td></tr> </table>" ;
            
  tmpStr += "\r\n<p><a href=\"ScanNetwrok\"><button><font size=+2 color=green>Rescan WiFi Device </font></button></a>&nbsp;</a></p>";
  tmpStr += "<p><a href=\"homeIndex\"><button align=center><font size=+2 color=green>Home </font></button></a>&nbsp;</a></p>";
  
  tmpStr += "\r\n <br/>  <p> WiFI Network List</p> <table> <tr><th>SSID </th> <th> Encryption Type </th> </tr>";  
  int n = WiFi.scanNetworks();
  if(n>0)
  {
    for(int i=0; i<n;i++)
    {
      tmpStr += "\r\n <tr><td>" + WiFi.SSID(i)+ "</td><td>"+ String((WiFi.encryptionType(i) == ENC_TYPE_NONE)? " ": "**") + "</td></tr>";     
    }
  }
  else
  {
    tmpStr += "<tr><td> <b> No WLAN found </b> </td></tr>";
  }
  tmpStr += "</table>";  
  
  
  tmpStr+= "</body></html>"; 
}








