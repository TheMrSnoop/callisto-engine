#pragma once
#include "dependencies.h"
#include "render.h"

class star
{
public:
    //default is the radius of the sun in megameters.
    star(float size = 695.7f);

    void render();
private:
    float radius;
    sphere mesh;
};