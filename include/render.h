#pragma once

#include "dependencies.h"


class celestialBody; 

class circle
{
public:
    //default resolution is 8
    //default color is white.
    void initialize(float Radius, glm::vec3 OriginPoint, int Resolution = 8, glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    void createMesh();

    void render();
private:
    float radius;
    glm::vec3 originPoint; //in world space;
    glm::vec4 color;
    int resolution; 

    GLuint vertexBuffer, indexBuffer, vertexLayout;
    std::vector<glm::vec3> vertices;
};

class sphere
{
public:
    //default resolution is 64
    //default color is white.
    void initialize(float Radius, glm::vec3 OriginPoint, int Rings = 8,  int Vertices = 16, glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    void createMesh();

    void render();
private:
    float radius;
    glm::vec3 originPoint; //in world space;
    glm::vec4 color;

    int verticalRings;
    int verticesPerRing;

    GLuint vertexBuffer, indexBuffer, vertexLayout;
    std::vector<glm::vec3> vertices;

    glm::vec3 generateUVSphereCoordinates(int ringIndex, int vertexIndex);
};


class grid
{
public:
    void initialize(std::vector<celestialBody> celestialObjects, short resolution);
    void render();

private:
    GLuint vertexBuffer, indexBuffer, vertexLayout;
    std::vector<glm::vec3> vertices;

    const int resolutionConstant = 4;

    float calculateLayerRadius(int currentIteration) { return 0.05f * currentIteration; };
};



class shader
{
public:
    GLuint createShader(const char * vertex_file_path,const char * fragment_file_path);

    //same thing as creating a new shader program
    void applyShader();

    void compileShader();

    GLuint* returnShaderProgram() { return &shaderProgram; };

    GLuint* returnFragShader() { return &fragShader; };
    GLuint* returnVertexShader() { return &vertexShader; };
private:
    GLuint shaderProgram;

    GLuint fragShader;
    GLuint vertexShader;

    

};