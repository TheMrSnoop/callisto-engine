#include "render.h"
#include <fstream>
#include <sstream>


//piiii
constexpr double pi = 3.14159265358979323846;
constexpr double goldenRatio = 1.61803398875;

GLuint shader::createShader(const char * vertex_file_path,const char * fragment_file_path)
{
    //gets shader code and stff

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);


	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory ?\n", vertex_file_path);
		getchar();
		return 0;
	}




	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &VertexSourcePointer , NULL);
	glCompileShader(vertexShader);

	// Check Vertex Shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragShader, 1, &FragmentSourcePointer , NULL);
	glCompileShader(fragShader);

	// Check Fragment Shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(fragShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShader);
	glAttachShader(ProgramID, fragShader);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	glDetachShader(ProgramID, vertexShader);
	glDetachShader(ProgramID, fragShader);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	return ProgramID;
}



void shader::compileShader()
{
    glCompileShader(vertexShader);
    glCompileShader(fragShader);
}



//CIRCLE

void circle::initialize(float Radius, glm::vec3 OriginPoint, int Resolution, glm::vec4 Color)
{
	radius = Radius; originPoint = OriginPoint; resolution = Resolution; color = Color;
}

void circle::createMesh()
{

    //short = smaller int range
    std::vector<unsigned short> indices;


    //generates circle mesh
    for (int i = 0; i < resolution; i++)
    {
        float theta1 = (static_cast<float>(i) / static_cast<float>(resolution)) * 2.0f * pi;
        float x1 = (glm::cos(theta1) * radius) + originPoint.x;
        float y1 = (glm::sin(theta1) * radius) + originPoint.y;


		int next = (i + 1);
        float theta2 = (static_cast<float>(next)/ static_cast<float>(resolution)) * 2.0f * pi;
        float x2 = (glm::cos(theta2) * radius) + originPoint.x;
        float y2 = (glm::sin(theta2) * radius) + originPoint.y;


        //then you gotta just like draw the triangle from (origin) -> (x1, y1) -> (x2, y2) -> back to origin
        vertices.push_back(glm::vec3(x1, y1, originPoint.z));
        vertices.push_back(glm::vec3(x2, y2, originPoint.z));
        vertices.push_back(glm::vec3(originPoint));


        if (!vertices.empty()) indices.push_back(vertices.size() - 1);

		std::cout << "theta1: " << theta1 / (2 * pi) << std::endl;
		std::cout << "theta2: " << theta2 / (2 * pi) << std::endl;
    }


	for (const auto& v : vertices)
	{
		std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
	}
	std::cout << "with a resolution of " << resolution << std::endl;




    //Create the vertex buffer object, then set it as the current buffer, then copy the vertex data onto it.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    //Create the index buffer object, set it as the current index buffer, then copy index data to it.
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);



}

void circle::render()
{
	GLsizei totalVertices = vertices.size();

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, totalVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
	
}






//SPHERE

void sphere::initialize(float Radius, glm::vec3 OriginPoint, int Resolution, glm::vec4 Color)
{
	radius = Radius; originPoint = OriginPoint; resolution = Resolution; color = Color;
}

glm::vec3 sphere::generateSphericalCoordinates(int index)
{
	float theta = ((2.0f * pi * index) / goldenRatio);
	float phi = glm::acos(1.0f - ((2.0f * index) / resolution));

	float x = glm::cos(theta) * glm::sin(phi) + originPoint.x;
	float y = glm::sin(theta) * glm::sin(phi) + originPoint.y;
	float z = glm::cos(phi) + originPoint.z;

	return glm::vec3(x, y, z);
}

void sphere::createMesh()
{
    //short = smaller int range
    std::vector<unsigned short> indices;


    //generates sphere mesh using the fibancci sphere formula
    for (int i = 0; i < resolution; i++)
    {
		glm::vec3 coordinates1 = generateSphericalCoordinates(i);
		glm::vec3 coordinates2 = generateSphericalCoordinates(i + 1);
		glm::vec3 coordinates3 = generateSphericalCoordinates(i + 2);
		


        //then you gotta just like draw the triangle from (origin) -> (x1, y1) -> (x2, y2) -> back to origin
        vertices.push_back(coordinates1);
        vertices.push_back(coordinates2);
        vertices.push_back(coordinates3);


        if (!vertices.empty()) indices.push_back(vertices.size() - 1);
    }


	for (const auto& v : vertices)
	{
		std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
	}
	std::cout << "with a resolution of " << resolution << std::endl;




    //Create the vertex buffer object, then set it as the current buffer, then copy the vertex data onto it.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    //Create the index buffer object, set it as the current index buffer, then copy index data to it.
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);



}

void sphere::render()
{
	GLsizei totalVertices = vertices.size();

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, totalVertices); 
    glDisableVertexAttribArray(0);
	
}