#include "ImageHandler.h"

ImageHandler::ImageHandler()
{

}

void ImageHandler::addImage(int index, std::string file){

    sf::Image image;

    if (image.LoadFromFile(file))
    {
        images[index] = image;
    }
}

sf::Image ImageHandler::getImage(int index){
    return images[index];
}
