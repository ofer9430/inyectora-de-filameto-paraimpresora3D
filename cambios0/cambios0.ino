/*
Lettura SONDA termica ds18b20, visualizzazione su display 20x4, e
comando relè.

Pin digitali 5 = modulo relais
Pin Digital 12 = linea dati sensore DS18B20
Pin Monitor = SCL SDA
 */


#include "motor.h"
  #include <Wire.h>
#include <OneWire.h>         //libreria per ds18b20
#include <DallasTemperature.h>      //libreria per conversione valore            
#include <LiquidCrystal_I2C.h>//libreria per lcd
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
#define ONE_WIRE_BUS 12                   // definimos el terminal donde llegara la señal del one wire
 
OneWire oneWire(ONE_WIRE_BUS);           // donde se menciona en la libreria el one wire
DallasTemperature sensors(&oneWire);   // de esta libreria se realizan lis calculos e immpresion de informacion del sensor

  
  int rele_out1 = 5;     //pin del rele
  int tx;                //variable de temperatura que le vas a poner
  int temperatura;       //temperatura rilevata
  
  int estado1=0;

 void setup (){
 pinMode(8,INPUT);  //declaramos el boton como entrada
  pinMode(4,OUTPUT);  //delaramos una salida

  sensors.begin();              //
  lcd.begin(16, 2);             //
  pinMode(rele_out1, OUTPUT);   //
  
  tx =120 ;                       //temperataura la cual de dara el aviso para encendido de motor

  setup_rele();//se creo un fichero .h y .cpp para ordenar el codigo
 }
 
void loop() {

///////////broca////////////////////////////////////////////////


  estado=dogitalRead(10);

if ((estado=HIGH)&&(estadoAnterior==LOW)){
  salida-1=salida;
  
  
  }

  estadoAnrterior=estado;

  if (salida==1){    //encendido y apagado de broca 
    digitalWrite(9,HIGH);

  }
  else{
    digitalWrite(9,LOW);
    
    }



///////////temperatura///////////////////////////////////////////////


  
  
  estado1=digitalRead(8);
  if (estado1==HIGH){
     digitalWrite(4,HIGH);

    }
  else{
    digitalWrite(4,LOW);//cuando el sensor esta arriba
  }

   sensors.requestTemperatures();    // Invia il comando di lettura delle temperatura

 
    /*Lettura temperatura con ds18b20 */
    int temperatura = sensors.getTempCByIndex(0);   //lettura ingresso digitale 12 e assegnazione del valore alla variabile temperatura
    
    
  

  

 
   if(temperatura <= tx && estado1==LOW  ){  //si la temperatuer en mayor a 120 c apagar rele de motor para broca
    
      
      lcd.setCursor(0,0);
      lcd.print("temp:  ");
      lcd.print(temperatura,DEC);
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("ACS:ON");
      
      digitalWrite(rele_out1, HIGH);    //comando  il rele
      }
      
      else{                  
    
    
      lcd.setCursor(0,0);
      lcd.print("temp:   ");
      lcd.print(temperatura,DEC);
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("ACS: OFF");
      digitalWrite(rele_out1, LOW);      //mantengo bassa l'uscita digitale 5
        }
  }
