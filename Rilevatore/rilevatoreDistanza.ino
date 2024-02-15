#include <LiquidCrystal.h>

LiquidCrystal lcd(0,1,8,9,10,11);
const int red = 2;
const int blue = 3;
const int green = 4;
const int button = 5;
const int trigger = 7;
const int echo = 6;
const int piezo = 12;

int cont = LOW;
int on = LOW;

const int buzz = 400;
const double suono = 0.03438;

double mostraLcd(int);
void rgb(int,int,int);

void setup(){
    lcd.begin(16,2);
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
  	pinMode(red,OUTPUT);
  	pinMode(blue,OUTPUT);
  	pinMode(green,OUTPUT);
    pinMode(button,INPUT);
}

void loop(){
  	int lettura = digitalRead(button);
  	if(lettura != cont && lettura == HIGH){
    	on = !on;
      rgb(0,0,0);
  	}
  	cont = lettura;
  	if(on == HIGH){
  		digitalWrite(trigger, LOW);
        digitalWrite(trigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger, LOW);
        double spostamento = mostraLcd(echo);
        if(spostamento<=50){
            rgb(255,0,0);
            tone(piezo,buzz,100);
        }else if(spostamento>=180){
            rgb(0,255,0);
        }else{
            rgb(255,165,0);
            tone(piezo,buzz,100);
            delay(500);
        }
        delay(500);
        lcd.clear(); 	
     }
}
  
double mostraLcd(int echo){
   	double tempo = pulseIn(echo,HIGH);
    double spostamento = suono*tempo/2;
    if(spostamento<=300){
      lcd.print((long int)spostamento);
      lcd.print("cm ");
    }else{
      lcd.print("Lontano");
    }
    lcd.setCursor(0,0); 
  	return spostamento;
}
void rgb(int r,int g,int b){
  	analogWrite(red,r);
  	analogWrite(green,g);
  	analogWrite(blue,b);
}
