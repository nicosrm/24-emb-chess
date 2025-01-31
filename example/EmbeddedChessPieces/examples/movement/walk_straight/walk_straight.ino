/**
 * @file walk_straight.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Example to test the straight movement of the Dezibot
 * @version 0.1
 * @date 2024-10-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>
#include <Wire.h>

// change for a calibration fitting the specific dezibot
#define MOVEMENT_CALIBRATION 3900

Dezibot dezibot = Dezibot();
ECPMovement ecpMovement(dezibot, MOVEMENT_CALIBRATION);
ECPColorDetection ecpColorDetection(dezibot);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
  dezibot.begin();
  Serial.println("Initialised");

  // initial delay to mitigate faulty color sensor readings
  delay(1000);
  ecpColorDetection.turnOnColorCorrectionLight();
}

void loop() {
  for (size_t numberOfFields = 1; numberOfFields < 5; numberOfFields++) {
    dezibot.display.print("Moving ");
    dezibot.display.print(numberOfFields);
    dezibot.display.println(" Fields");
    ecpMovement.move(numberOfFields);

    dezibot.display.println("\nDone");
    delay(10000);
    dezibot.display.clear();
  }
}
