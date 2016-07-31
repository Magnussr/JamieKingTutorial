#include "ShapeGenerator.h"
#include <glm\glm.hpp>
#include <Vertex.h>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

/*OpenGL Coordinate system works as 0.0, 0.0 is in the center, +1.0 , +1.0 is in the top right corner
and -1.0, -1.0 is in the button right corner. */
//ShapeData data;

ShapeData ShapeGenerator::makeTriangle(){

	ShapeData data;

	Vertex triangle[] =
	{
		/*First 3 is Position(X,Y,Z)   ,Next 3 is the RGB Color RED, GREEN, BLUE*/
		glm::vec3(-1.0f, +1.0f, +0.99f), glm::vec3(+1.0f, +0.0f, +0.0f), //vertice 0
		glm::vec3(+0.0f, -1.0f, -0.99f), glm::vec3(+0.0f, +0.0f, +1.0f), //vertice 1  
		glm::vec3(+1.0f, +1.0f, +0.99f), glm::vec3(+1.0f, +0.0f, +0.0f), //vertice 2
		
	};
	
	data.numVertices = NUM_ARRAY_ELEMENTS(triangle);
	data.vertices = new Vertex[data.numVertices];
	memcpy(data.vertices, triangle, sizeof(triangle));

	GLushort shapes[] =
	{
		0,1,2, 3,4,5,
	};
	data.numIndices = NUM_ARRAY_ELEMENTS(shapes);
	data.indices = new GLushort[data.numIndices];
	memcpy(data.indices, shapes, sizeof(shapes));


	return data;
}

ShapeData ShapeGenerator::makeCube()
{
	ShapeData data;
	Vertex cube[] = {
		glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(+1.0f, +1.0f, +1.0f),

		glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(+1.0f, +0.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(+0.0f, +0.5f, +0.2f),
		glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(+0.8f, +0.6f, +0.4f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(+0.3f, +1.0f, +0.5f),

		glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec3(+0.2f, +0.5f, +0.2f),
		glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(+0.9f, +0.3f, +0.7f),
		glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(+0.3f, +0.7f, +0.5f),
		glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(+0.5f, +0.7f, +0.5f),

		glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(+0.7f, +0.8f, +0.2f),
		glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec3(+0.5f, +0.7f, +0.3f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(+0.4f, +0.7f, +0.7f),
		glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(+0.2f, +0.5f, +1.0f),

		glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec3(+0.6f, +1.0f, +0.7f),
		glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec3(+0.6f, +0.4f, +0.8f),
		glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(+0.2f, +0.8f, +0.7f),
		glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(+0.2f, +0.7f, +1.0f),

		glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec3(+0.8f, +0.3f, +0.7f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(+0.8f, +0.9f, +0.5f),
		glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec3(+0.5f, +0.8f, +0.5f),
		glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec3(+0.9f, +1.0f, +0.2f),
	};

	data.numVertices = NUM_ARRAY_ELEMENTS(cube);
	data.vertices = new Vertex[data.numVertices];
	memcpy(data.vertices, cube, sizeof(cube));

	unsigned short stackIndices[] = {
		0,	 1,	 2,	 0,	 2,	 3,
		4,	 5,	 6,	 4,	 6,	 7,
		8,	 9, 10,  8, 10, 11,
		12, 13,	14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 22, 21, 20, 23, 22,
	};
	data.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	data.indices = new GLushort[data.numIndices];
	memcpy(data.indices, stackIndices, sizeof(stackIndices));


	return data;
	

}


