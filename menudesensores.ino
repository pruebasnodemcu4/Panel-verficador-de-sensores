#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

DHT dht (8, DHT11);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7 );
byte B_0 = 10,B_1 = 11, B_2 = 12, B_3 = 13, B_4 = 16;
String v = "Bienvenido!! ";
String t = "Que desea ver? ";
byte signo[] { 
  B00100, 
  B00100,
  B00100,
  B00100,
  B00000,
  B00000,
  B00100,
  B00000
};
byte signo_1[] { 
  B00100, 
  B00000,
  B00100,
  B01000,
  B10000,
  B10001,
  B01110,
  B00000
};
int menu = 0;
int luminosidad;
int valor;
long distancia;
long tiempo;
byte trigger = 19;
byte echo = 9;
int lectura;
int humo;

void setup() {
 pinMode (B_0, INPUT_PULLUP); 
 pinMode (B_1, INPUT_PULLUP);
 pinMode (B_2, INPUT_PULLUP);
 pinMode (B_3, INPUT_PULLUP);
 pinMode (B_4, INPUT_PULLUP);
 pinMode (echo, INPUT);
 pinMode (trigger, OUTPUT);
 dht.begin();
 lcd.begin (16, 2);
 lcd.clear();
 lcd.setCursor (1, 0); 
 lcd.createChar(1, signo);
 lcd.createChar(2, signo_1);
 Serial.begin(9600);  
}

void loop() {
 sensor_dist();
 sensor_temp();
 sensor_LDR();
 sensor_MQ();
 Serial.println();

 if (digitalRead(B_0) == LOW){
   if (menu == 3){
     menu = 0;}
     menu++;  
    switch (menu){
      case 1: lcd.clear();
              lcd.setCursor (1,0);
              lcd.write (1);
              lcd.write (1);
              lcd.print (v);
              break;
      case 2: lcd.clear();
              lcd.setCursor (0,0);
              lcd.write (2);
              lcd.print (t);
              break;
      case 3: lcd.clear();
              lcd.setCursor (0,0);
              lcd.print ("1:S.Dis 2:S.Temp");
              lcd.setCursor (0,1);
              lcd.print ("3:S.LDR 4:S.MQ");
              break;}
    while (!digitalRead(B_0));}
   
 if (digitalRead(B_1) == LOW){
   lcd.clear();
   lcd.print ("Distancia:");
   lcd.print (distancia);
   lcd.print ("cm ");}
             
   
 if (digitalRead(B_2) == LOW){
    float celsius = dht.readTemperature ();
    float humd = dht.readHumidity();
    lcd.clear();
    lcd.print ("Temp: ");
    lcd.print (celsius);
    lcd.print ("*C");
    lcd.setCursor (0,1);
    lcd.print ("Humedad: ");
    lcd.print (humd);
    lcd.print ("%");
     if (isnan (celsius)){
      lcd.print ("Fallo en la temp");
      return;}
     if (isnan (humd)){
      lcd.print (" Fallo en la humd");
      return;}  
   }
  if(digitalRead(B_3) == LOW){
    lcd.clear();
    lcd.print ("Lectura LDR: ");
    lcd.print (valor);
    lcd.setCursor (0,1);
    lcd.print ("Luminosidad: ");
    lcd.print (luminosidad);
    lcd.print ("%");
   }
  if(digitalRead(B_4) == LOW){
    lcd.clear();
    lcd.print("Lectura MQ: ");
    lcd.print(lectura);
    lcd.setCursor (0,1);
    lcd.print ("Concentr: ");
    lcd.print (humo);
    lcd.print ("%");
     
   }
  
}
void sensor_dist(){
  digitalWrite (trigger, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger, LOW);
  delayMicroseconds (10);
  tiempo = (pulseIn (echo, HIGH));
  distancia = (tiempo/58);
  Serial.print ( " Distancia: ");
  Serial.print (distancia);
  Serial.print ("cm ");
}

void sensor_temp(){
  float celsius = dht.readTemperature ();
  float humd = dht.readHumidity();
  Serial.print ("Temperatura: ");
  Serial.print (celsius);
  Serial.print ("°C");
  Serial.print (" Humedad: ");
  Serial.print (humd);
  Serial.print ("%");
   if (isnan (celsius)){
    Serial.println ("Fallo en la temperatura");
    return;}
   if (isnan (humd)){
    Serial.println (" Fallo en la humedad");
    return;}
}

void sensor_LDR(){
  valor = analogRead (A1);
  luminosidad = map(valor, 266, 109, 0, 100);
  Serial.print(" Lectura LDR: ");
  Serial.print(valor);
  Serial.print ("  Luminosidad: ");
  Serial.print (luminosidad);
  Serial.print ("%");
}

void sensor_MQ(){
  lectura = analogRead (A0);
  humo = map(lectura, 332, 590, 0, 100);
  Serial.print(" Lectura MQ: ");
  Serial.print(lectura);
  Serial.print ("  Concentración: ");
  Serial.print (humo);
  Serial.print ("%");
  
  }
