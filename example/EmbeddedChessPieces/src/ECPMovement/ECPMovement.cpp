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

bool ECPMovement::moveToNextField() {
    const int startColor = ecpColorDetection.getFieldColor();
    const int wantedColor = startColor == 1 ? startColor + 1 : startColor -1;
    const int stopoverColor = wantedColor + 2;
    int currentColor = startColor;
    int currentIteration = 0;

    // reach middle of the next field with the front leg
    while (currentColor != stopoverColor) {
        if (currentIteration == MAX_ITERATIONS) {
            return false;
        }
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        currentColor = ecpColorDetection.getFieldColor();
        currentIteration++;
    }

    // move further to place the whole dezibot on the field
    while (currentColor != wantedColor) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        currentColor = ecpColorDetection.getFieldColor();
        if (currentColor == 4) { // unambiguous
            return false;
        }
    }

    return true;
};

void ECPMovement::move(
    uint numberOfFields, 
    ECPChessField intendedField, 
    ECPDirection intendedDirection
) {
    for (size_t i = 0; i < numberOfFields; i++) {
        bool successfulMovement = moveToNextField();
        if (!successfulMovement) {
            displayForwardMovementCorrectionRequest(
                intendedField, 
                intendedDirection
            );
            break;
        }
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
        + String(MANUEL_CORRECTION_TIME/1000) + " seconds to\n\n> " 
        + currentField.toString() + " " + directionToString(intendedDirection) 
        + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(MANUEL_CORRECTION_TIME);
    dezibot.display.clear();
};

void ECPMovement::displayForwardMovementCorrectionRequest(
    ECPChessField intendedField, 
    ECPDirection intendedDirection
) {
    String request = "Faulty movement\nPlease correct\nmy position in\n" 
        + String(MANUEL_CORRECTION_TIME/1000) + " seconds to\n\n> " 
        + intendedField.toString() + " " + directionToString(intendedDirection) 
        + "\n\n Thank you!";
    dezibot.display.clear();
    dezibot.display.print(request);
    delay(MANUEL_CORRECTION_TIME);
    dezibot.display.clear();
};
