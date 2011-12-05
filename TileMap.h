#ifndef TILEMAP_H
#define TILEMAP_H

#include<SFML/Graphics.hpp>
#include<map>
#include<string>

using std::map;

class Cell;

class TileMap
{
    public:
        struct TMapException{
            static const int NULL_CELL = 0;
            static const int NO_SELECTION = 1;

            sf::Vector2i c;
            int type;
            std::string why;
        };

        /** Default constructor */
        TileMap(int size, int cellSize);
        /** Default destructor */
        virtual ~TileMap();

        /*********************************************************
                "Load cells into the map"
        *********************************************************/
        void load(void);
        void unload();

        /*********************************************************
            "Gets the map size in pixels"
        *********************************************************/
        int MapSize();

        /*********************************************************
            "Gets a cell inside the map"

            returns a reference to the Cell

            PARAMS: coords -    an sf::Vector2i that hold the grid x
                                and grid y of the cell to get

            throws a NULL_CELL exception if the cell doesn't exist
        ***********************************************************/
        Cell& GetCell(sf::Vector2i coords) throw(TMapException);

        /*********************************************************
            "Calculates the pixel position of a cell relative to
                the window given the grid coordinates"

            returns an sf::Vector2f with pixel coordinates

            PARAMS: coords -    an sf::Vector2i that hold the grid x
                                and grid y of the cell to get

        ***********************************************************/
        sf::Vector2f getCellPosition(sf::Vector2i coords);

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

        Cell& GetSelection() throw(TMapException);

        sf::Vector2i GetGridFromPixel(sf::Vector2f coord);

        void SetPosition(float x, float y);
    protected:
    private:
        int m_cellCount;
        int m_cellSize;
        int m_size;
        sf::Vector2i m_clickCoord;

        float m_x, m_y;
        map<int, map<int, Cell> > cells;
};

#endif // TILEMAP_H
