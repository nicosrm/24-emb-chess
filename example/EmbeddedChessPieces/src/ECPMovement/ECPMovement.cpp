#include "ECPMovement.h"

ECPMovement::ECPMovement(
    Dezibot &dezibot,
    uint movementCalibration
) : dezibot(dezibot),
    ecpColorDetection(ECPColorDetection(dezibot)),
    ecpSignalDetection(ECPSignalDetection(dezibot)),
    movementCalibration(movementCalibration) {};

void ECPMovement::move(uint numberOfFields) {
    for (size_t i = 0; i < numberOfFields; i++) {
        moveToNextField();
    }
};

void ECPMovement::turnLeft(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const bool hasStartedOnWhite = ecpColorDetection.isWhiteField();
    const int initialAngle = ecpSignalDetection.measureDezibotAngle();
    
    // if dezibot initially faces 270°, subtract 90° to turn left, resulting
    // in the dezibot facing 180°
    // add 360 before applying modulo to prevent negative values
    const int goalAngle = (initialAngle - 90 + 360) % 360;
    
    const bool wasRotationSuccessful = rotateToAngle(goalAngle, initialAngle);

    delay(MEASURING_DELAY); // for better measuring results
    const bool isCurrentlyOnWhite = ecpColorDetection.isWhiteField();
    if (isCurrentlyOnWhite != hasStartedOnWhite || !wasRotationSuccessful) {
        displayRotionCorrectionRequest(currentField, intendedDirection);
    }
};

void ECPMovement::turnRight(
    ECPChessField currentField, 
    ECPDirection intendedDirection
) {
    const bool hasStartedOnWhite = ecpColorDetection.isWhiteField();
    const int initialAngle = ecpSignalDetection.measureDezibotAngle();

    // if dezibot initially faces 180°, add 90° to turn left, resulting
    // in the dezibot facing 270°
    const int goalAngle = (initialAngle + 90) % 360;

    const bool wasRotationSuccessful = rotateToAngle(goalAngle, initialAngle);

    delay(MEASURING_DELAY); // for better measuring results
    const bool isCurrentlyOnWhite = ecpColorDetection.isWhiteField();
    if (isCurrentlyOnWhite != hasStartedOnWhite || !wasRotationSuccessful) {
        displayRotionCorrectionRequest(currentField, intendedDirection);
    }
};

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

void ECPMovement::moveForward(int timeMovement, int timeBreak) {
    dezibot.motion.move(0, movementCalibration);
    delay(timeMovement);
    dezibot.motion.stop();
    delay(timeBreak);
};

void ECPMovement::moveToNextField() {
    const bool hasStartedOnWhite = ecpColorDetection.isWhiteField();
    bool isCurrentlyOnWhite = hasStartedOnWhite;

    while (isCurrentlyOnWhite == hasStartedOnWhite) {
        moveForward(FORWARD_TIME, MOVEMENT_BREAK);
        isCurrentlyOnWhite = ecpColorDetection.isWhiteField();
    }
};

void ECPMovement::displayRotionCorrectionRequest(
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

bool ECPMovement::rotateToAngle(int goalAngle, int initialAngle) {
    int currentAngle = initialAngle;
    int difference = goalAngle - currentAngle;
    size_t currentIteration = 0;

    bool shouldContinueRotation = std::abs(difference) > ROTATION_TOLERANCE
        && currentIteration < MAX_ROTATION_ITERATIONS;

    while (shouldContinueRotation) {
        int normalizedDifference = ((difference + 180 + 360) % 360) - 180;
        uint rotationTime = calculateRotationTime(normalizedDifference);

        if (normalizedDifference == 0 || normalizedDifference == -180) {
            // exactly opposed to goal angle, rotation direction does not matter
            rotateLeft(rotationTime);
        } else if (normalizedDifference < 0) {
            rotateLeft(rotationTime);
        } else {
            rotateRight(rotationTime);
        }

        delay(MEASURING_DELAY); // for better measuring results
        currentAngle = ecpSignalDetection.measureDezibotAngle();

        difference = goalAngle - currentAngle;
        
        currentIteration++;
        shouldContinueRotation = std::abs(difference) > ROTATION_TOLERANCE
            && currentIteration < MAX_ROTATION_ITERATIONS;
    }

    if (currentIteration == MAX_ROTATION_ITERATIONS) {
        // rotation failed
        return false;
    }

    // rotation successful
    return true;
};

void ECPMovement::rotateLeft(uint movementTime) {
    dezibot.motion.right.setSpeed(ROTATION_SPEED);
    delay(movementTime);
    dezibot.motion.right.setSpeed(0);
};

void ECPMovement::rotateRight(uint movementTime) {
    dezibot.motion.left.setSpeed(ROTATION_SPEED);
    delay(movementTime);
    dezibot.motion.left.setSpeed(0);
};

uint ECPMovement::calculateRotationTime(int normalizedAngleDifference) {
    float rotationTime = ROTATION_TIME_FACTOR * std::abs(normalizedAngleDifference);
    return std::round(rotationTime);
};
