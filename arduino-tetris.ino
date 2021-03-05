#include "GameEngine.h"

int unconnectedAnalog = A0;

void setup(void)
{
  Serial.begin(9600);
  Serial.print(F("Hello! ST7735 TFT Tetris"));
  Serial.println(F("Initialized"));

  randomSeed(analogRead(unconnectedAnalog));

}

void loop()
{
  GameEngine gameEngine;
}
