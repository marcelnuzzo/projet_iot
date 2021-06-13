#include <HTTPClient.h>
#include <WiFi.h> 
#include <WiFiUdp.h>
#include "WiFi.h"
#include <NTPClient.h>
//const char *ssid     = "SFR-83e0";
//const char *password = "QJ3NLKTLNJ65";
const char *ssid     = "AndroidAP331E";
const char *password = "qhzt9330";
String serverName = "http://marcel1968.hopto.org/mesure/add3.php";
//String serverName = "http://192.168.0.29/mesure/add2.php";
HTTPClient http ;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);
#define LED_PIN 2
const int buzer = 2;
const int trigPin = 4;              //config pour pin du détecteur ultrason
const int echoPin = 5;              //config pour pin du détecteur ultrason
const int entreeAnalogique = 32;    //Lecture du potar pour varier la distance de détection
int readPot = 0;
int rp = 0;
int VIBRATOR = 23;
long duration;
int distance;
int annee = 0;
int jour = 0;
int mois = 0;
int heure = 0; 
int minutes = 0;
int seconde = 0;
int an = 0;  
String inString = ""; 
int jourDuMois = 0;
int flagDist = 0;
int temp = 100;
float duree = 100;
String laNouvelleDate = "";
String ladate = "";
String elem = "";
const int entree = 18;
int buttonState = 1;

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(115200); 
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(buzer, OUTPUT);
  digitalWrite(buzer, LOW);
  pinMode(VIBRATOR, OUTPUT);
  digitalWrite(VIBRATOR, LOW);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(entree, INPUT);

  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    for(int j = 0; j < 3; j++) {
      for(int i = 0; i < 50; i++) {
        digitalWrite(VIBRATOR, HIGH); 
      
        digitalWrite(buzer, HIGH);
        delayMicroseconds(666);
        digitalWrite(buzer, LOW);
        delayMicroseconds(666);
      }
      delay(100);
    }
    delay ( 300 );
  }
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  
  timeClient.begin();
  timeClient.update();  
  ladate = timeClient.getFullFormattedTime();
  Serial.println(ladate);

  bipInit();
}
void loop() {
  //esp_sleep_enable_timer_wakeup(1000000); //1 seconds
  //int ret = esp_light_sleep_start();
  buttonState = digitalRead(entree);
  rp = analogRead(entreeAnalogique);
  readPot = 2*rp/100;
  readPot += 80;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print("potar: ");
  Serial.println(readPot);

  if(distance > 255) {
    distance = 255;
    digitalWrite(VIBRATOR, LOW);
    flagDist = 0;
  }
  
  if(distance < readPot && distance >= 10)
  {
    flagDist = 0;
    bip();
  } 
  
  if(distance < 10) { 
    bip();
    if(flagDist == 0) {
      Serial.println(distance);
      elem = distance;
      envoiDonnees();
      flagDist = 1;
    } 
  } 
  
  if(distance >= readPot && distance <= 255) {
    digitalWrite(VIBRATOR, LOW);
    flagDist = 0;
  }
  
  temp = distance;
  //Serial.println(temp);
  duree = 8000/temp;
  Serial.print("état bouton: ");
  Serial.println(buttonState);
  delay(distance*5+1);
}

void bip() {
  if (buttonState == LOW) {
    for(int i = 0; i < duree; i++) {
      digitalWrite(VIBRATOR, HIGH); 
    
      digitalWrite(buzer, HIGH);
      delayMicroseconds(666);
      digitalWrite(buzer, LOW);
      delayMicroseconds(666);
    } 
  }else{
    digitalWrite(VIBRATOR, HIGH);
    delay(100);
  }
  digitalWrite(VIBRATOR, LOW); 
}

void bipInit() {
    for(int i = 0; i < 500; i++) {
      digitalWrite(buzer, HIGH);
      delayMicroseconds(666);
      digitalWrite(buzer, LOW);
      delayMicroseconds(666);
    }
}

void envoiDonnees() {
  minutes = timeClient.getMinutes();
  heure = timeClient.getHours();
  inString = timeClient.getJourDuMois();
  jour = inString.toInt();
  mois = timeClient.getMonth();
  annee = timeClient.getYear();
  seconde = timeClient.getSeconds();
  
  laNouvelleDate = annee;
  laNouvelleDate += "-";
  laNouvelleDate += mois;
  laNouvelleDate += "-";
  laNouvelleDate += jour;
  
  laNouvelleDate += ",";
  laNouvelleDate += heure;
  laNouvelleDate += ":";
  laNouvelleDate += minutes;
  laNouvelleDate += ":";
  laNouvelleDate += seconde;

  Serial.println(laNouvelleDate);
  
  //elem = "13";
  elem += ",";
  elem += laNouvelleDate;
  Serial.println(elem);
  
  String champ = "?M_distance1=";
  String serverPath = serverName + champ + elem;
  Serial.println(serverPath);
  http.begin(serverPath); 
  http.addHeader("Content-Type", "text/plain"); 
  //String httpRequestData;
  //httpRequestData = "?M_distance1=10";
  int httpResponseCode;
  httpResponseCode = http.GET();  
  if (httpResponseCode > 0) {       
    String response = http.getString();  //Get the response to the request   
    Serial.println(httpResponseCode);   //Print return code         
    Serial.println(response);           //Print request answer  
  } else {
    Serial.print("Error on sending POST: ");        
    Serial.println(httpResponseCode);           
 }
}
