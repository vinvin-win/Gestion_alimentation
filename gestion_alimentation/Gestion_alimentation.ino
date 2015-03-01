#include <SPI.h>
#include <Adafruit_GFX.h>  
#include <Adafruit_ST7735.h>

const int PintensionIn = A4;
const int PintensionOut = A3;
const int PinintensiteIn = A2;
const int Pinretro = 3;
const int Pinsonde = A0;
const int Pinventilo = 5;

float tension = 0.0;
float tension_volt = 0.0;
double intensite = 0.0;

float RTens = 4700.0;
float RTensTotal = 51700.0;
float RInten = 470.0;
float RIntenTotal = 940.0;
double RIntenIn = 0.0008;

float RSonde = 10000;
float RSbase = 10000;

double A_1 = 3.354016E-3;
double B_1 = 2.569850E-4;
double C_1 = 2.620131E-6;
double D_1 = 6.383091E-8;
double equationB1 = 0.0;
double equationC1 = 0.0;
double equationD1 = 0.0;
double equation = 0.0;
double Temperature = 0.0;
float lastMesure_temperature = 0;

int boucle = 200;
int pixel = 0;
int x = 0;
int y =0;


#define sclk 13
#define mosi 11
#define cs   10
#define dc   12
#define rst  2


Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

void setup() 
{

  pinMode(PinintensiteIn, INPUT);
  pinMode(PintensionOut, INPUT);
  pinMode(PinintensiteIn, INPUT);
  pinMode(Pinsonde, INPUT);
  pinMode(Pinventilo, OUTPUT);
  pinMode(Pinretro, OUTPUT);
  
  PwmFrequence(5, 1);
  
  analogWrite(Pinretro, 120);
  tft.initR(INITR_BLACKTAB);
  
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
  
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_SILVER,ST7735_BLACK);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  
  Affiche_image();
  
  analogWrite(Pinsonde,0);
}

void loop() 
{
  
  if(boucle >= 200)
  {
    Mesure_temperature();
    
    tft.setCursor(0, 5);
    tft.setTextColor(ST7735_SILVER,ST7735_BLACK);
    tft.setTextWrap(true);
    tft.println("Tension:");
    tft.print("- En entre: ");
    tft.print(Mesure_tension(PintensionIn));
    tft.println("V");
    tft.print("- En sortie: ");
    tft.print(Mesure_tension(PintensionOut));
    tft.println("V");
    tft.println("");
    tft.println("Consomation: ");
    tft.print("- Total: ");
    tft.print(Mesure_intensite());
    tft.println("A");
    boucle = 0; 
  }
  boucle ++;
  
  if ((lastMesure_temperature <= (Mesure_temperature() - 0.25)) || (lastMesure_temperature >= (Mesure_temperature() + 0.25)))
  {
    analogWrite(Pinventilo, Vitesse_ventilateur());
   
    lastMesure_temperature = Mesure_temperature();
   
    tft.setCursor(0, 53);
    tft.setTextColor(ST7735_SILVER, ST7735_BLACK);
    tft.setTextWrap(true);
    tft.println("Temperature: ");
    tft.print(Mesure_temperature());
    tft.println(" degre");
    
  }

}

float Mesure_temperature()
{   
    pinMode(Pinsonde, INPUT);
    tension = analogRead(Pinsonde); 
    tension_volt = tension * (3.30 / 1024.00);
    double RSvar = (RSbase * tension_volt ) / (3.30 - tension_volt);
    double equationB1 = B_1 * log(RSvar/RSbase);
    double equationC1 = C_1 * pow(log(RSvar/RSbase), 2);
    double equationD1 = D_1 * pow(log(RSvar/RSbase), 3);
    double equation = A_1 + equationB1 + equationC1 + equationD1;
    Temperature = pow(equation, -1);
    Temperature = Temperature - 273.15;
    return Temperature;
    
}

int Vitesse_ventilateur()
{
float vitesse = 0.0; 
float T = Mesure_temperature();

  if (Mesure_temperature() <= 30)
  {
    vitesse = 0.0225*T*T - 0.5*T + 20;
  } 
  else
  {
    
    if(Mesure_temperature() >= 49)
    {
      vitesse = 255;
    }
    else
    {
      vitesse = 0.1764*T*T - 1.5*T - 100;
    }
  }

  return int(vitesse);
}

float Mesure_tension(int Pintension)
{
    tension = analogRead(Pintension); 
    tension_volt = tension * (3.30 / 1024.00);
    tension_volt = tension_volt / (RTens / RTensTotal);
    
    return tension_volt;
}


float Mesure_intensite()
{ 
    tension = analogRead(PinintensiteIn); 
    tension_volt = tension * (5.00 / 1024.00);
    tension_volt = tension_volt / (RInten / RIntenTotal);
    
    intensite = 1 / (RIntenIn / tension_volt);
   
    return tension_volt;
}

void Affiche_image()
{
                           // Rempacer ce qui est entre "" par les valeurs demandés
  while(pixel <= "h * l")
   {
     
    tft.drawPixel(x + 96, y + 3, pgm_read_word_near("nom de l'image" + pixel));
    
    x ++;
    
    if(x == 64)
    {
     y ++;
     x = 0;
    }
    pixel ++;
   }
  
  x = 0;
  y = 0;
  pixel = 0;
}

void PwmFrequence(int pin, int diviseur) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(diviseur) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}


