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
const int trigPin = 4;              //pin du trigger du détecteur ultrason
const int echoPin = 5;              //pin pour le déclenchement du détecteur ultrason
const int entreeAnalogique = 32;    //Lecture du potar pour varier la distance de détection
int readPot = 0;                    //tempo pour la durée du moteur
int rp = 0;                         //lecture analogique du potar
int VIBRATOR = 23;                  //piezo pour le buzzer
long duration;                      //durée de l'allée retour de l'onde du capteur
int distance;                       //distance avec l'obstacle
int annee = 0;                      //année pour la date
int jour = 0;                       //jour pour la date
int mois = 0;                       //mois pour la date
int heure = 0;                      //heure pour la date
int minutes = 0;                    //minutes pour la date
int seconde = 0;                    //seccondes pour la date
//int an = 0;  
String inString = "";               //variable pour la conversion du jour de la date 
//int jourDuMois = 0;
int flagDist = 0;                   //drapeau pour n'envoyer qu'une fois dans la bdd
int temp = 100;                     //base principale du délai de la boucle "loop"
float duree = 100;                  //durée des bip
String laNouvelleDate = "";         //actualisation de la date lors de l'envoi
String ladate = "";                 //date lors de l'initialisation
String elem = "";                   //la chaine des éléments à envoyer à la bdd
const int entree = 18;              //pin de l'entrée bouton qui désactive le buzzer
int buttonState = 1;                //état du bouton buzzer
int varDist = 0;                    //palier de la distance pour la durée du bip
bool boolConnect = 0;               //connexion ou non au Wifi 

void setup() {
  
  Serial.begin(115200); 
  //initialisation des entrées/sorties
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(buzer, OUTPUT);
  digitalWrite(buzer, LOW);
  pinMode(VIBRATOR, OUTPUT);
  digitalWrite(VIBRATOR, LOW);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(entree, INPUT);
  //init du Wifi
  WiFi.begin(ssid, password);
  //envoi 3 bip d'initialisation pour avertir l'utilisateur
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
  //essai de connexion au Wifi
  if( WiFi.status() != WL_CONNECTED ) {
    boolConnect = 0;
  } else if( WiFi.status() == WL_CONNECTED ) {
    boolConnect = 1;
  }
  delay (300);
  //affiche sur le terminal le statut de la connexion Wifi
  Serial.println( WiFi.status());
  Serial.println( WL_CONNECTED);
  delay(300);
  //récupération des éléments date heure du réseau NTP
  timeClient.begin();
  timeClient.update();  
  ladate = timeClient.getFullFormattedTime();
  //affiche date et heure sur le terminal
  Serial.println(ladate);
  //bip long d'initialisation
  bipInit();
}

void loop() {
  //on récupère l'état du bouton buzzer on/off
  buttonState = digitalRead(entree);
  //on récupère la valeur du potar pour la distance
  rp = analogRead(entreeAnalogique);
  //on converti cette valeur en durée
  readPot = 2*rp/100;
  readPot += 80;
  //initialisation du trigger du capteur ultrason
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //déclenchement du capteur
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //lecture du retour de l'onde en durée en microseconde
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print("connexion: ");
  Serial.println(boolConnect);

  //routine pour la durée de vibration et du buzzer
  if(distance < 10)
    varDist = 1;
  else if(distance >= 10 || distance < 20)
    varDist = 2;
  else if(distance >= 20 || distance < 30)
    varDist = 3;
  else if(distance >= 30 || distance < 40)
    varDist = 4;
  else if(distance >= 40 || distance < 50)
    varDist = 5;
  else if(distance >= 50 || distance < 60)
    varDist = 6;
  else if(distance >= 60 || distance < 70)
    varDist = 7;
  else if(distance >= 70)
    varDist = 8;

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
      if(boolConnect) {
        elem = distance;
        envoiDonnees(); 
      }
      flagDist = 1;
    } 
  } 
  
  if(distance >= readPot && distance <= 255) {
    digitalWrite(VIBRATOR, LOW);
    flagDist = 0;
  }
  //durée de la boucle
  temp = distance;
  duree = 8000/temp;
  delay(distance*5+1);
}

void bip() {
  if (buttonState == LOW) {
    for(int j = 0; j < varDist; j++) {
      for(int i = 0; i < duree/10; i++) {
        digitalWrite(VIBRATOR, HIGH); 
        digitalWrite(buzer, HIGH);
        delayMicroseconds(666);
        digitalWrite(buzer, LOW);
        delayMicroseconds(666);
      } 
       digitalWrite(VIBRATOR, LOW);
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
