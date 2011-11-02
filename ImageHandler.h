#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class ImageHandler
{
    public:
        ImageHandler();

        void addImage(int index, std::string file);
        sf::Image getImage(int index);
    protected:
    private:
        sf::Image images[6];
};

#endif // IMAGEHANDLER_H
