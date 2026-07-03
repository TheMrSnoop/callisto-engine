#pragma once

#include "dependencies.h"

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
    void initialize(float Radius, glm::vec3 OriginPoint, int Resolution = 64, glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    void createMesh();

    void render();
private:
    float radius;
    glm::vec3 originPoint; //in world space;
    glm::vec4 color;
    int resolution; 

    GLuint vertexBuffer, indexBuffer, vertexLayout;
    std::vector<glm::vec3> vertices;

    glm::vec3 generateSphericalCoordinates(int index);
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