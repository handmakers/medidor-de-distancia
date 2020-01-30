//arduino bike speedometer w lcd.print()
//by Amanda Ghassaei 2012 & actualized Fran Gozzi
//https://www.instructables.com/id/Arduino-Bike-Speedometer/

/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*Utilizar a biblioteca NewLiquidCrystal_1.5.1.zip
*/

// Declaração de bibliotecas
#include <SoftwareSerial.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 



//calculations
//tire radius ~ 13.5 inches
//circumference = pi*2*r =~85 inches
//max speed of 35mph =~ 616inches/second
//max rps =~7.25

#define reed A0//pin connected to read switch

//storage variables
int reedVal;
long timer;// time between one full rotation tempo entre uma volta completa(in ms)
float mph;
float time_th;
float distance_traveled;
float kmph;
float time_t = 0;
float radius = 13.5;//raio pneu(em polegadas)
float circumference;

int maxReedCounter = 100;//min time (in ms) of one rotation (for debouncing)
int reedCounter;


void setup(){
   
 // Serial.begin(9600);
  lcd.begin(16,2);               // inicializa o display lcd 
  lcd.home ();                   // move o cursor para inicio
//  lcd.print("Clara M Krafts rules");   // escreve mensagem na tela
//  lcd.setCursor ( 0, 1 );        // vai para proxima linha
//  lcd.print ("Faca a pergunta"); // escreve mensagem na tela


  reedCounter = maxReedCounter;
  circumference = 2*3.14*radius;
  pinMode(reed, INPUT);
 
  // TIMER SETUP- the timer interrupt allows precise timed measurements of the reed switch
  //for more info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1
  cli();//stop interrupts

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;
  // set timer count for 1khz increments
  OCR1A = 1999;// = (1/1000) / ((1/(16*10^6))*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
 
  sei();//allow interrupts
  //END TIMER SETUP
 
//  lcd.begin(16,2);
}


ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = digitalRead(reed);//get val of A0
  if (reedVal){//if reed switch is closed
    if (reedCounter == 0){//min time between pulses has passed
      mph = (56.8*float(circumference))/float(timer);//calculate miles per hour
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
    }
    else{
      if (reedCounter > 0){//don't let reedCounter go negative
        reedCounter -= 1;//decrement reedCounter
      }
    }
  }
  else{//if reed switch is open
    if (reedCounter > 0){//don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 2000){
    mph = 0;//if no new pulses from reed switch- tire is still, set mph to 0
  }
  else{
    timer += 1;//increment timer
  }
}

//void displayMPH(){
//  Serial.println(mph);
//lcd.print(mph);

//lcd.print(kmph);
//}

void loop(){

if (mph > 0) {
    time_t = time_t + 0.0166;//time traveled in mins
delay(1000);
  }

kmph = mph * 1.60934; //convert mph to kmph

time_th = time_t * 0.0166; //convert time traveled from mins to hours

distance_traveled += kmph * time_th; //distance traveled in km


float calorie_burnt;
float MET;
float weight_person;

calorie_burnt = MET * weight_person * time_th; //calorie burnt measured in calories/hour
 
//message to the receiving device
 lcd.clear(); // limpa tela
 lcd.home (); // posiciona cursor no inicio do display
 lcd.print("Vel  "); // escreve mensagem na tela
 lcd.print(kmph);
 lcd.print(" km/h");
 lcd.setCursor(0,1);
lcd.print("Dist ");
 lcd.print(distance_traveled);
  lcd.print(" km");

//lcd.print(mph);// message will be replaced with speed in mph
//lcd.print(",");

//lcd.print(kmph);// message will be replaced with speed in km/h
//lcd.print(",");

//lcd.print(time_t);// message will be replaced with time traveled
//lcd.print(",");

//lcd.print(distance_traveled);// message will be replaced with distance traveled
// lcd.print(",");

//lcd.print(calorie_burnt);// message will be replaced with calorie burnt
//lcd.print(";");

  //print mph once a second
//  displayMPH();
  delay(1000);
}
