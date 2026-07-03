#include "star.h"

star::star(float size)
{
    radius = size;

    mesh.initialize(radius, glm::vec3(0.0f, 0.0f, 0.0f), 16, 32);
    mesh.createMesh();
}

void star::render()
{
    mesh.render();
}