#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#define DATABASE_URL "https://heart-8ad13-default-rtdb.firebaseio.com" 
#define API_KEY "++" 
#define WIFI_SSID "NICO" 
#define WIFI_PASSWORD "D6" 
String USER_EMAIL = "juanjosebrandlondono@pascualbravo.edu.co";
String USER_PASSWORD = "++++";
String ID = "N7C7C7OR0B1N";
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String path = String("/MOCA/"+ID+"/latidos");
String pathLastUpdate = String("/MOCA/"+ID+"/timeUpdate");
unsigned long sendDataPrevMillis = 0;
unsigned long timemls,timemls2,times;

int espera = 1000;

int latidos = 0;

unsigned long count = 0;

int pulso = 0;
int last = 0;
int last2 = 0;

void setup()
{

  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    //Serial.print(".");
    delay(300);
  }
  //Serial.println(WiFi.localIP());
  /**Serial.println();
  Serial.print("Connected with IP: ");
  
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);*/
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  //Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
}

void loop()
{

    pulso = analogRead(0);
  if(pulso > 520 && pulso < last){
    Serial.println(last);
   }
   last = pulso;

 /** count = 0;
  while(count < 20){
    Serial.println(pulso);
   if( last < pulso && pulso >= 551){
    
     timemls = millis();
     times = timemls - timemls2;
     if(times > 400) {
      latidos = 120000/(times+100);  
     }
     count++;  
     timemls2 = timemls;
   }
   last = pulso;
  }
  
      if (Firebase.ready())
    {
      Firebase.setTimestamp(fbdo, pathLastUpdate);
      long lastDate = fbdo.to<long>();
      //if(latidos > 10 && latidos < 150)
      Firebase.setInt(fbdo, String(path+"/"+lastDate), latidos+8);
      //Serial.println(fbdo.to<int>());
      latidos = 0;
      delay(espera);
    } */
}
