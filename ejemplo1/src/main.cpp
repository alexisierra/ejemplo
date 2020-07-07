#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class conexionWb{
  private:

  public:
    conexionWb(const char *_SSID, const char* _PASSWORD ){
      WiFi.begin(_SSID, _PASSWORD);
      while(WiFi.status()!= WL_CONNECTED){
          delay(500);
          Serial.print("...");
      }
    }

}; 

class DateTime
{
private:
  int defaultTime;
  struct tm timeinfo;
  const char *ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 0;

public:
  char timeStringBuff[20];
  DateTime()
  {
    defaultTime = 0;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getTime();
  }

  void getTime()
  {   
    setLocalTime();
  }

  void setLocalTime()
  {
    
    if (!getLocalTime(&timeinfo))
    {
    }
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  }
};
conexionWb *webInterface;
DateTime *reloj;
StaticJsonDocument<512> hActual;


const char *ssid="IZZI-5D2F";
const char *passwrd="509551245D2F";


void setup() {
  Serial.begin(115200);
  webInterface= new conexionWb(ssid,passwrd);
  reloj=new DateTime();
  
}
int suma=0;
void loop() {
  suma++;
  hActual.clear();
  reloj->getTime();
  hActual["Hora"]=reloj->timeStringBuff;
  hActual["Sumatoria"]=suma;
  serializeJson(hActual,Serial);
  Serial.println("");
  delay(1000);
}

