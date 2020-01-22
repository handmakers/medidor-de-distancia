/*==========================================================================
                Baú da Eletrônica Componentes Eletrônicos
                        www.baudaeletronica.com.br
            Projeto: Faça um vidente com Arduino e Reed Switch
==========================================================================*/

// Declaração de bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13 // pino de backlight

//LiquidCrystal_I2C lcd(0x27);  // Endereço i2c

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 

const int switchPin = 6; // pino reed switch
int switchState = 0; // estado inicial
int prevSwitchState = 0; // estado anterior
int resposta; // resposta

void setup()
{
  pinMode(switchPin, INPUT); // declarando switch como entrada
  // Switch on the backlight
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  
  lcd.begin(16,2);               // inicializa o display lcd 
  lcd.home ();                   // move o cursor para inicio
  lcd.print("Sou um vidente");   // escreve mensagem na tela
  lcd.setCursor ( 0, 1 );        // vai para proxima linha
  lcd.print ("Faca a pergunta"); // escreve mensagem na tela
  }

void loop()
{
   switchState = digitalRead(switchPin); //le o pino do interruptor
   if (switchState != prevSwitchState){ //compara se estado atual e anterior sao diferentes
    if(switchState == HIGH){ // se sim, verifica se switch foi ativado
      resposta = random(8); // respostas randomicas
      lcd.clear(); // limpa tela
      lcd.home (); // posiciona cursor no inicio do display
      lcd.print("A resposta eh: "); // escreve mensagem na tela
      lcd.setCursor(0,1);

      switch(resposta){
        case 0:
        lcd.print("Sim");
        break;

        case 1:
        lcd.print("Provavelmente");
        break;

        case 2:
        lcd.print("Definitivamente");
        break;
        
        case 3:
        lcd.print("Nao seja bobo(a)");
        break;
        
        case 4:
        lcd.print("Com certeza");
        break;

        case 5:
        lcd.print("Pergunte de novo");
        break;

        case 6:
        lcd.print("Eu duvido");
        break;

        case 7:
        lcd.print("Nao");
        break;
      }
    }
   }
   prevSwitchState = switchState; // guarda o estado atual no anterior
}   
