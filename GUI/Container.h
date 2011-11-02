#ifndef CONTAINER_H
#define CONTAINER_H

#include "Component.h"

class Container: public Component
{
    public:
        Container();
        virtual ~Container();

        void test();
    protected:
    private:
};

#endif // CONTAINER_H
