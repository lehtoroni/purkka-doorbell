/* PINOUT
 * D1 = 5 
 * D2 = 4
 * D3 = 0
 */

int _buzzer = 4;
int _button = 0;

const char* ssid = "";
const char* password = "";

#include <WiFiServerSecure.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiType.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFiAP.h>
#include <WiFiClient.h>
#include <BearSSLHelpers.h>
#include <WiFiServer.h>
#include <ESP8266WiFiScan.h>
#include <WiFiServerSecureBearSSL.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiSTA.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiServerSecureAxTLS.h>
#include <ESP8266HTTPClient.h>

#include <WiFiUdp.h>
#include <mDNSResolver.h>


int lastButtonState = 1;

using namespace mDNSResolver;

WiFiUDP udp;
Resolver resolver(udp);

void setup() {
  
  Serial.begin(9600);
    while(!Serial) { 
  }
  
  WiFi.begin(ssid, password);
  
  Serial.println("");
  Serial.println("Doorbell proof-of-concept");
  Serial.print("\n");
  Serial.println("");

  pinMode(_buzzer, OUTPUT);
  pinMode(_button, INPUT_PULLUP);
  
  //ESP.deepSleep(16);

  ring();
  delay(200);
  
}

void loop() {

  int btn = digitalRead(_button);
  
  if (btn != lastButtonState && btn == 0) {
    lastButtonState = btn;
    
    for (int i = 0; i < 3; i++) {
      if (digitalRead(_button) != lastButtonState) {
        return;
      }
      delay(30);
    }

    ringBell();
    delay(200);
    
  }

  lastButtonState = btn;
  delay(10);
  
}


void ring(){

/*
  digitalWrite(_ledGreen, HIGH);
  delay(100);
  digitalWrite(_ledGreen, LOW);
  digitalWrite(_ledRed, HIGH);
  delay(100);
  digitalWrite(_ledRed, LOW);

  Serial.println("Ringing the doorbell. Wo-hoo.");
  Serial.println("Checking if WiFi available...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    digitalWrite(_ledRed, HIGH);
    delay(100);
    digitalWrite(_ledRed, LOW);
    delay(500);
  }

  resolver.setLocalIP(WiFi.localIP());

  Serial.println("\nWiFi available!");
  Serial.println("My IP:");
  Serial.println(WiFi.localIP());
   
  HTTPClient http;

  IPAddress ip = resolver.search("holvikello.local");

  if (ip != INADDR_NONE) {
    
    Serial.println("Bell IP:");
    Serial.println(ip);

    String _h1 = "http://";
    String _h2 = "/be592255a86fe6e774e3439f81014f0a";

    http.begin(_h1 + ip.toString() + _h2);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      
      Serial.println("Yay! Got a response.");
      digitalWrite(_ledGreen, HIGH);
     
      String payload = http.getString();
      Serial.println(payload);
      
    } else {
      Serial.println("Wait, what? It seems like we've got ourselves a -1.");
    }
    
    http.end();


    delay(5000);
    
    digitalWrite(_ledGreen, LOW);
    digitalWrite(_ledRed, LOW);
    
  } else {
    Serial.println("eipä tullu");
    
    for (int i = 0; i < 3; i++) {
      digitalWrite(_ledRed, HIGH);
      delay(200);
      digitalWrite(_ledRed, LOW);
      delay(500);
    }
    
  }

  delay(5000);
  ESP.deepSleep(0); 
*/
  
  
}

int cdelay = 100;
int tn = 440;

void beat(int dur, int mi, int ma) {
  for (int i = 0; i < dur; i++) {
    tn = random(mi, ma);
    tone(4, tn);
    delay(3);
    noTone(4);
  }
}

void ringBell() {

  for (int i = 0; i < 8; i++) {
    beat(10, 100, 200);
    tn = 110 + random(0, 20)*55;
    tone(4, tn);
    delay(150);
    noTone(4);
    delay(150);
    beat(10, 700, 1300);
    tn = 110 + random(0, 6)*110;
    tone(4, tn);
    delay(150);
    noTone(4);
    delay(150);
  }

  delay(150);
  beat(10, 100, 200);
  delay(100);
  beat(10, 100, 200);
  delay(100);
  beat(10, 100, 200);
  delay(150);
  beat(10, 100, 200);

  delay(500);
  
  
  tone(4, 660);
  delay(400);
  tone(4, 550);
  delay(400);
  tone(4, 440);
  delay(600);
  noTone(4);
  
}
