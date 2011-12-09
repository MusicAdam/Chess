#ifndef TILEMAP_H
#define TILEMAP_H

#include<SFML/Graphics.hpp>
#include<map>
#include<string>

using std::map;

class Square;

class TileMap
{
    public:
        struct TMapException{
            static const int NULL_SQUARE = 0;
            static const int NO_SELECTION = 1;

            sf::Vector2i c;
            int type;
            std::string why;
        };

        /** Default constructor */
        TileMap(int size, int SquareSize);
        /** Default destructor */
        virtual ~TileMap();

        /*********************************************************
                "Load Squares into the map"
        *********************************************************/
        void load(void);
        void unload();

        /*********************************************************
            "Gets the map size in pixels"
        *********************************************************/
        int MapSize();

        /*********************************************************
            "Gets a Square inside the map"

            returns a reference to the Square

            PARAMS: coords -    an sf::Vector2i that hold the grid x
                                and grid y of the Square to get

            throws a NULL_Square exception if the Square doesn't exist
        ***********************************************************/
        Square* GetSquare(sf::Vector2i coords) throw(TMapException);

        /*********************************************************
            "Calculates the pixel position of a Square relative to
                the window given the grid coordinates"

            returns an sf::Vector2f with pixel coordinates

            PARAMS: coords -    an sf::Vector2i that hold the grid x
                                and grid y of the Square to get

        ***********************************************************/
        sf::Vector2f getSquarePosition(sf::Vector2i coords);

        /********************
            Checks if a grid position
            is in bounds
        ********************/
        bool CheckGridBounds(sf::Vector2i coord);
        /************************
            Checks if a pixel position is in bounds
        **************************/
        bool CheckPixelBounds(sf::Vector2f coord);

        bool Click(sf::Vector2f mCoord);
        void Select(sf::Vector2i c);
        void Deselect()throw();

        Square* GetSelection() throw(TMapException);

        sf::Vector2i GetGridFromPixel(sf::Vector2f coord);

        void SetPosition(float x, float y);
    protected:
    private:
        int m_SquareCount;
        int m_SquareSize;
        int m_size;
        sf::Vector2i m_clickCoord;

        float m_x, m_y;
        map<int, map<int, Square*> > Squares;
};

#endif // TILEMAP_H
