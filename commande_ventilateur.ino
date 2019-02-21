/*1-Incorpoation des bibliothèques, définition de constantes, déclaration des variables et
instanciation des objets*/
#include <OneWire.h>
#include <DallasTemperature.h>
#include<LiquidCrystal.h>
#define ONE_WIRE_BUS 2 // Broche de données du bus oneWire connecté sur la broche 2
#define RS 2 // Register Select
#define E 3 // Enable
#define D4 4 // Ligne de données 4
#define D5 5 // Ligne de données 5
#define D6 6 // Ligne de données 6
#define D7 7 // Ligne de données 7
#define COL 16 // Nombre de colonnes
#define LIGNES 2 // Nombre de lignes
#define Trans 8
#define LedR 12
#define LedV 11
float T;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7); // Instanciation de l'objet ‘lcd’
OneWire oneWire(ONE_WIRE_BUS); // Instanciation de l'objet ‘oneWire’
DallasTemperature sensors(&oneWire); // Instanciation de l'objet ‘ sensors’);//Transmettre
//notre référence oneWire au capteur de température Dallas
void setup()
{
/*2-Vitesse de transmission du moniteur série et, initialisation du module LCD et
programmation des broches 8,11 et 12 en sorties*/
lcd.begin(COL, LIGNES); // Nombres de colonnes et de lignes
sensors.begin(); //Initialiser le capteur DS18B20
pinMode(LedV, OUTPUT); //Broche numérique 11 comme sortie
pinMode(LedR, OUTPUT); //Broche numérique 12 comme sortie
pinMode(Trans, OUTPUT); //Broche numérique 8 comme sortie
}
void loop(){
getTemp(); //Apelle de la fonction ‘getTemp’ mesurer la température
AfficherTlcd(); //Apelle de la fonction ‘AfficherTlcd’ pour afficher la température sur le LCD
/*3-Traitement du cas où la température est inférieure ou égale à 35°C */
if(T<=35){
lcd.setCursor(0,1);
lcd.print("Ventilateur: OFF");
digitalWrite(LedV, HIGH); //Allumer la LED verte
digitalWrite(Trans, LOW);// Ventilateur OFF
digitalWrite(LedR, LOW);//Eteindre la LED rouge
delay(500);
}
/*4-Traitement du cas où la température est supérieure à 35°C */
else{
lcd.clear();
digitalWrite(LedV, LOW); // Eteindre la LED verte
digitalWrite(Trans, HIGH); // Ventilateur ON
digitalWrite(LedR, HIGH); // Allumer la LED rouge
AfficherTlcd();//Afficher la température sur le module LCD
lcd.setCursor(0,1);
lcd.print("Ventilateur: ON");
delay(500);
getTemp(); //Actualiser la valeur de mesure de température
}
}
/*5-Définition de la fonction ‘getTemp’ qui mesure la température */
void getTemp(){
sensors.requestTemperatures(); // Demande de mesure de température
T=sensors.getTempCByIndex(0); //Stocker la valeur de mesure dans la variable ’T’, vous
//pouvez avoir plus d'un capteur sur le même bus. 0 se réfère au premier capteur (DS18B20)
//sur le bus
}
/*5-Définition de la fonction ‘AfficherTlcd’ qui affiche la température sur le module LCD */
void AfficherTlcd(){
lcd.setCursor(0,0);
lcd.print(" Temp: ");
lcd.print(T);
lcd.print(" ");
lcd.print((char)223);//’223’ :code ASCCI du caractère ‘°’ (degré)
lcd.print("C");
}
