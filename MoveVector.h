#ifndef MOVEVECTOR_H
#define MOVEVECTOR_H


class MoveVector: public sf::Vector2f
{
    public:
        MoveVector();
        int distance;
        int possibleDirections[9];
    protected:
    private:
};

#endif // MOVEVECTOR_H
