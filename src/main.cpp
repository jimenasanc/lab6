//*****************************************************************************************
//Universidad del Valle de Guatemala
//BE3015: Electrónica Digital 2
//Jimena Sánchez
//Lab 6: TIVA C y ESP32

//*****************************************************************************************

//*****************************************************************************************

//*****************************************************************************
// Librerías
//*****************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h>

//*****************************************************************************
// Definición de pines
//*****************************************************************************
#define d4 19
#define d5 21
#define d6 5
#define d7 22
#define en 15
#define rs 18

#define pot1 34

#define Rx2 16
#define TX2 17
//*****************************************************************************
// Prototipos de función
//*****************************************************************************

void poten1();

//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
uint8_t decenas, unidades, decimal;
uint8_t decenas2, unidades2, decimal2;
uint8_t decenas3, unidades3, decimal3;

float adcRaw= 0.0;
double voltpot1 = 0;
double alpha = 0.09;

//float voltaje;

int ledRdc = 0;
int ledAdc = 0;
int ledVdc = 0;

int flag = 0;

//*****************************************************************************
// Configuración
//*****************************************************************************
void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600); //tiva c  
  //LCD_Init(rs, en, d4, d5, d6, d7);
  // Initialize The LCD. Parameters: [ Columns, Rows ]
  LCD.begin(16, 2);

}
//*****************************************************************************
// Loop Principal
//*****************************************************************************
void loop()
{
  Serial2.write(ledRdc);
  /*
  //potenciometro 1

  decenas = ledRdc / 100.0;
  unidades = (ledRdc -(decenas * 100)) / 10.0;
  decimal = (ledRdc - decenas * 100)-(decenas * 10);

  //potenciometro 2
  decenas2 = ledAdc / 100.0;
  unidades2 = (ledAdc -(decenas2 * 100)) / 10.0;
  decimal2 = (ledAdc - decenas2 * 100)-(decenas2 * 10);
  
 //ledRGB, led verde
  decenas3 = ledVdc / 100.0;
  unidades3 = (ledVdc -(decenas3 * 100)) / 10.0;
  decimal3 = (ledVdc - decenas3 * 100)-(decenas3 * 10);

  Serial.print("Rojo");
  Serial.print(voltaje);
  Serial.print("\n");

  Serial.print("Verde");
  Serial.print(voltaje2);
  Serial.print("\n");

  Serial.print("Azul");
  Serial.print(ButtonCount);
  Serial.print("\n");
  Serial.print("\n");
*/
  //para limpiar LCD
  LCD.clear();
  LCD.print("Rojo:");
  LCD.print("Verde:");
  LCD.print("Azul:");

  LCD.setCursor(0, 1); //para cambiar de fila y columna
  LCD.print(decenas);
  LCD.print('.');
  LCD.print(unidades);
  LCD.print(decimal);
  LCD.print(" ");

  LCD.print(decenas2);
  LCD.print('.');
  LCD.print(unidades2);
  LCD.print(decimal2);
  LCD.print(" ");
  //LCD.print(ButtonCount);
  
  LCD.print(decenas3);
  LCD.print('.');
  LCD.print(unidades3);
  LCD.print(decimal3);
  LCD.print(" ");

  delay(800);

  
  if (Serial2.available() > 0)
  {   
    if (Serial2.read() == 1)
    {
      flag = 1;      
      }
      
      if (flag == 1)
      {
        DCLedG = Serial2.read();
        Serial.print("Led azul:");
        Serial.println(ledAdc);        
        flag = 0;
        }
        
        if (Serial2.read() == 2)
    {
      flag = 2;      
      }
      
      if (flag == 2)
      {
        DCLedB = Serial2.read();
        Serial.print("Led verde: ");
        Serial.println(ledVdc);
        flag = 0;
        }
        }
  delay(100);
}

//*****************************************************************************
// potenciometro1
//*****************************************************************************
void poten1(void)
{
  adcRaw = analogRead(pot1);
  voltpot1 = (alpha * voltpot1) + ((1.0 - alpha) * voltpot1); //Filtro pasa bajas
  ledRdc = map(voltpot1, 0, 4095, 0, 255);
  delay(100);
}
