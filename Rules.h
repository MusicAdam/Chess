#ifndef RULES_H
#define RULES_H

#include "GamePiece.h"

class Rules
{

    public:

        Rules();
        int placement(int type);
        const sf::Vector2f movePawn(int direction=1);
        int movementTurns(int pieceType);
        const sf::Vector2f movementAction(int pieceType);

    protected:
    private:

};

#endif // RULES_H
