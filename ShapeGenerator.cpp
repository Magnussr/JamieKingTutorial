#include "ShapeGenerator.h"
#include <glm\glm.hpp>
#include <Vertex.h>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

/*OpenGL Coordinate system works as 0.0, 0.0 is in the center, +1.0 , +1.0 is in the top right corner
and -1.0, -1.0 is in the button right corner. */

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


