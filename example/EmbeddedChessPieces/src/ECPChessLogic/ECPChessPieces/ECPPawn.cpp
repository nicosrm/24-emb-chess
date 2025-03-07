#include "ECPPawn.h"

ECPPawn::ECPPawn(
    Dezibot &d,
    ECPMovement &ecpMovement,
    ECPChessField initialField,
    bool isWhite
) : ECPChessPiece(d, ecpMovement, initialField, isWhite) {
    drawFigureToDisplay();
};

bool ECPPawn::isMoveValid(ECPChessField newField) {
    if (newField == currentField) {
        // pawn must move
        return false;
    }

    const bool doesNotChangeColumn = currentField.column == newField.column;
    const int rowDiff = newField.row - currentField.row;
    const bool isMoveOneHorizontally = abs(currentField.column - newField.column) == 1;

    if (isWhite) {
        const bool doesDrawOneFieldForward = rowDiff == 1;

        if (doesNotChangeColumn && doesDrawOneFieldForward) {
            // pawn draws one field forward
            return true;
        }

        const bool isOnInitialRow = currentField.row == INITIAL_ROW_WHITE;
        const bool isNewRowTwoBeforeInitial = newField.row == INITIAL_ROW_WHITE + 2;

        if (doesNotChangeColumn && isOnInitialRow && isNewRowTwoBeforeInitial) {
            // pawn did not move yet, enters with two field move forward
            return true;
        }
        if (isMoveOneHorizontally && doesDrawOneFieldForward) {
            // pawn is capturing, moves diagonally
            return true;
        }
    } else {
        const bool doesDrawOneFieldForward = rowDiff == -1;

        if (doesNotChangeColumn && doesDrawOneFieldForward) {
            // pawn draws one field forward
            return true;
        }

        const bool isOnInitialRow = currentField.row == INITIAL_ROW_BLACK;
        const bool isNewRowTwoBeforeInitial = newField.row == INITIAL_ROW_BLACK - 2;

        if (doesNotChangeColumn && isOnInitialRow && isNewRowTwoBeforeInitial) {
            // pawn did not move yet, enters with two field move forward
            return true;
        }
        if (isMoveOneHorizontally && doesDrawOneFieldForward) {
            // pawn is capturing, moves diagonally
            return true;
        }
    }

    return false;
};

void ECPPawn::drawFigureToDisplay() const {
    dezibot.display.clear();
    
    dezibot.display.println("                ");
    dezibot.display.println(" _     __       ");
    dezibot.display.println("| n___/  \\      ");
    dezibot.display.println("| |  H    |     ");
    dezibot.display.println("| |__H    |     ");
    dezibot.display.println("|_u   \\__/      ");
    dezibot.display.println("                ");
    dezibot.display.println("                ");
}
