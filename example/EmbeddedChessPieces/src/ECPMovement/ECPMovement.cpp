#include "ECPMovement.h"

ECPMovement::ECPMovement(
  Dezibot &dezibot,
  uint movementCalibration,
  uint rotationTimeLeft,
  uint rotationTimeRight
) : dezibot(dezibot),
    ecpColorDetection(ECPColorDetection(dezibot)),
    movementCalibration(movementCalibration),
    rotationTimeLeft(rotationTimeLeft),
    rotationTimeRight(rotationTimeRight) {};

ECPColorDetection* ECPMovement::getECPColorDetection() {
    return &ecpColorDetection;
}

void ECPMovement::moveForward(int timeMovement, int timeBreak) {
    dezibot.motion.move(0, movementCalibration);
    delay(timeMovement);
    dezibot.motion.stop();
    delay(timeBreak);
};

void ECPMovement::moveToNextField() {
    const int startColor = ecpColorDetection.getFieldColor();
    const int wantedColor = startColor == 1 ? startColor + 1 : startColor -1;
    const int stopoverColor = wantedColor + 2;
    int currentColor = startColor;

    while (currentColor != stopoverColor) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        currentColor = ecpColorDetection.getFieldColor();
    }
    while (currentColor != wantedColor) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        currentColor = ecpColorDetection.getFieldColor();
    }
};

void ECPMovement::move(uint numberOfFields) {
    for (size_t i = 0; i < numberOfFields; i++) {
        moveToNextField();
    }
};

void ECPMovement::turnLeft(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const int startColor = ecpColorDetection.getFieldColor();

    dezibot.motion.right.setSpeed(ROTATION_SPEED);
    delay(rotationTimeLeft);
    dezibot.motion.right.setSpeed(0);
    delay(MOVEMENT_BREAK);
    
    const int currentColor = ecpColorDetection.getFieldColor();
    if (currentColor != startColor) {
        displayRotationCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::turnRight(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const int startColor = ecpColorDetection.getFieldColor();

    dezibot.motion.left.setSpeed(ROTATION_SPEED);
    delay(rotationTimeRight);
    dezibot.motion.left.setSpeed(0);
    delay(MOVEMENT_BREAK);

    const int currentColor = ecpColorDetection.getFieldColor();
    if (currentColor != startColor) {
        displayRotationCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::displayRotationCorrectionRequest(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    String request = "Faulty rotation\nPlease correct\nmy position in\n" 
        + String(ROTATION_CORRECTION_TIME/1000) + " seconds to\n\n> " 
        + currentField.toString() + " " + directionToString(intendedDirection) 
        + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(ROTATION_CORRECTION_TIME);
    dezibot.display.clear();
};
