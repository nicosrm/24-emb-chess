/**
 * @file ir_color_detection.ino
 * @author Ines Rohrbach, Nico Schramm
 * @brief Example to determine if Dezibot is on white or black surface using infrared
 * @version 0.1
 * @date 2025-03-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Dezibot.h>
#include <EmbeddedChessPieces.h>

Dezibot dezibot = Dezibot();
ECPSignalDetection ecpSignalDetection = ECPSignalDetection(dezibot);
ECPColorDetection ecpColorDetection = ECPColorDetection(dezibot, ecpSignalDetection);

void setup() {
   dezibot.begin();
   delay(500);

   dezibot.display.flipOrientation();

   // select infrared as color detection mode
   ecpColorDetection.setUseInfraredColorDetection(true);
   ecpColorDetection.calibrateIRFieldColor();
}

void loop() {
    FieldColor fieldColor = ecpColorDetection.getFieldColor();

    dezibot.display.clear();
    dezibot.display.println(fieldColor);

    delay(500);
}
 