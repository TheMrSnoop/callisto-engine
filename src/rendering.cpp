#include "render.h"
#include <fstream>
#include <sstream>

#include "celestialBody.h"


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

void sphere::initialize(float Radius, glm::vec3 OriginPoint, int Rings, int Vertices, glm::vec4 Color)
{
	radius = Radius; originPoint = OriginPoint; verticalRings = Rings; verticesPerRing = Vertices;  color = Color;
}


glm::vec3 sphere::generateUVSphereCoordinates(int ringIndex, int vertexIndex)
{
	float phi = static_cast<float>(ringIndex) / static_cast<float>(verticalRings - 1) * pi;
	float theta = ((static_cast<float>(vertexIndex) / verticesPerRing) * 2.0f * pi);

	float x = glm::sin(phi) * glm::cos(theta) * radius + originPoint.x;
	float y = glm::cos(phi) * radius + originPoint.y;
	float z = glm::sin(phi) * glm::sin(theta) * radius + originPoint.z;

	return glm::vec3(x, y, z);
}

void sphere::createMesh()
{
	vertices.clear();
    for (int r = 0; r < verticalRings; r++)
    {
		for (int v = 0; v < verticesPerRing; v++)
		{
			//vertex calculation
			glm::vec tl = generateUVSphereCoordinates(r, v);
			glm::vec tr = generateUVSphereCoordinates(r, v + 1);

			glm::vec bl = generateUVSphereCoordinates(r + 1, v);
			glm::vec br = generateUVSphereCoordinates(r + 1, v + 1);

			//triangle creation

			//triangle 1
            vertices.push_back(tl);
            vertices.push_back(bl);
            vertices.push_back(tr);

            //triangle 2
            vertices.push_back(tr);
            vertices.push_back(bl);
            vertices.push_back(br);
		}
    }

    //Create the vertex buffer object, then set it as the current buffer, then copy the vertex data onto it.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
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





//GRID GENERATION

void grid::initialize(std::vector<celestialBody> objects, short resolution)
{
	for (celestialBody world : objects)
	{
		glm::vec3 worldPosition = world.location;

        float previousRadius   = 0.0f;
        float previousY        = 0.0f;
        int   previousSegments = 0;

		//std::cout << "Spawning a vertex on a plane on " << worldPosition.x << ", " << worldPosition.z << std::endl;
		//std::cout << "with a resolution of " << resolution << " and a total triangle count of " << resolution * resolutionConstant << std::endl;
		for (int i = resolution; i > 0; i--)
		{
			int segments = resolutionConstant * (1 << (i - 1));
			float radius = calculateLayerRadius((resolution - i) + 1);


			//ALWAYS the y
			//I know the vertex position input is a bit off.
			float vertexDisplacement = math::calculateSpaceTimeDisplacement(world.mass, world.radius); 

			std::cout << "y: " << vertexDisplacement << std::endl;


			if (i == resolution)
			{
				for (int r = 1; r <= segments; r++)
				{
					float theta1 = (static_cast<float>(r) / static_cast<float>(segments)) * 2.0f * pi;
					float theta2 = (static_cast<float>(r + 1) / static_cast<float>(segments)) * 2.0f * pi;

					float x1 = glm::cos(theta1) * radius + worldPosition.x;
					float z1 = glm::sin(theta1) * radius + worldPosition.z;

					float x2 = glm::cos(theta2) * radius + worldPosition.x;
					float z2 = glm::sin(theta2) * radius + worldPosition.z;


					//then you gotta just like draw the triangle from (origin) -> (x1, y1) -> (x2, y2) -> back to origin
					vertices.push_back(glm::vec3(x1, vertexDisplacement, z1));
					vertices.push_back(glm::vec3(x2, vertexDisplacement, z2));
					vertices.push_back(glm::vec3(worldPosition.x, vertexDisplacement, worldPosition.z));

				}
			}
			else
			{
				for (int o = 1; o <= segments; o++)
				{
					//inner segments

					float innerTheta1 = (static_cast<float>(o * 2) / static_cast<float>(previousSegments)) * 2.0f * pi;
					float innerTheta2 = (static_cast<float>((o * 2) + 1) / static_cast<float>(previousSegments)) * 2.0f * pi;
					float innerTheta3 = (static_cast<float>((o * 2) + 2) / static_cast<float>(previousSegments)) * 2.0f * pi;


					float Ax = worldPosition.x + glm::cos(innerTheta1) * previousRadius;
					float Az = worldPosition.z + glm::sin(innerTheta1) * previousRadius;


					//triangle creation

                    glm::vec3 innerA(Ax, previousY, Az);
                    glm::vec3 innerM(worldPosition.x + glm::cos(innerTheta2) * segments, previousY, worldPosition.z + glm::sin(innerTheta2) * segments);
                    glm::vec3 innerB(worldPosition.x + glm::cos(innerTheta3) * segments, previousY, worldPosition.z + glm::sin(innerTheta3) * segments);


					//outer segments
					float outerTheta1 = (static_cast<float>(o) / static_cast<float>(segments)) * 2.0f * pi;
					float outerTheta2 = (static_cast<float>(o + 1) / static_cast<float>(segments)) * 2.0f * pi;

                    glm::vec3 outerA(worldPosition.x + glm::cos(outerTheta1) * radius, vertexDisplacement, worldPosition.z + glm::sin(outerTheta1) * radius);
                    glm::vec3 outerB(worldPosition.x + glm::cos(outerTheta2) * radius, vertexDisplacement, worldPosition.z + glm::sin(outerTheta2) * radius);

                    vertices.push_back(outerA); vertices.push_back(innerA); vertices.push_back(innerM);
                    vertices.push_back(outerA); vertices.push_back(innerM); vertices.push_back(outerB);
                    vertices.push_back(innerM); vertices.push_back(innerB); vertices.push_back(outerB);






				}
			}

            previousRadius   = radius;
            previousY        = vertexDisplacement;
            previousSegments = segments;
		}
	}


    //Create the vertex buffer object, then set it as the current buffer, then copy the vertex data onto it.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
}



void grid::render()
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
