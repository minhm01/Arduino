#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include <DHT.h>

#define DHTTYPE DHT11   // Sensor DHT 11                                                         

#define FIREBASE_HOST "arduino-9707d.firebaseio.com"                          // database URL 
#define FIREBASE_AUTH "XRdzZvzmRVWYVzqdPr8kju8P171t20yR0AORtbYX"             // secret key

#define WIFI_SSID "28 LS" //28 LS //SangTrongHungDungGiauManh
#define WIFI_PASSWORD "quangminh" //quangminh //quochoikhoa13


#define dht_dpin 14
DHT dht(dht_dpin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  dht.begin();                                                               //Start reading dht sensor
}

void loop() { 
  float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");                                         //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("°C ");
  String fireTemp = String(t) + String("°C");                                                     //convert integer temperature to string temperature
  delay(4000);
  
  Firebase.pushString("/DHT11/", fireHumid);                                  //setup path and send readings
  Firebase.pushString("/DHT11/", fireTemp);                                //setup path and send readings
   
}
