
String DeviceIP()
{  
  IPAddress Ip =  WiFi.localIP();
  String str = String(Ip[0]);
  str+= ".";
  str += String(Ip[1]);
  str+= ".";
  str += String(Ip[2]);
  str+= ".";
  str += String(Ip[3]);
  return str;
}

