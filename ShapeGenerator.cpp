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

	GLushort indices[] =
	{
		0,1,2
	};
	data.numIndices = NUM_ARRAY_ELEMENTS(indices);
	data.indices = new GLushort[data.numIndices];
	memcpy(data.indices, indices, sizeof(indices));


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

ShapeData ShapeGenerator::makeArrow() {
	ShapeData data;
	Vertex stackVerts[] =
	{
	// Top side of arrow head
	glm::vec3(+0.00f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 0		 
	glm::vec3(+0.50f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 1	  
	glm::vec3(+0.00f, +0.25f, -1.00f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 2	  
	glm::vec3(-0.50f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 3

	// Bottom side of arrow head
	glm::vec3(+0.00f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 4	  
	glm::vec3(+0.50f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 5	 
	glm::vec3(+0.00f, -0.25f, -1.00f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 6	  
	glm::vec3(-0.50f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 7

	// Right side of arrow tip
	glm::vec3(+0.50f, +0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 8	  
	glm::vec3(+0.00f, +0.25f, -1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 9	  
	glm::vec3(+0.00f, -0.25f, -1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 10  
	glm::vec3(+0.50f, -0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 11

	// Left side of arrow tip
	glm::vec3(+0.00f, +0.25f, -1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 12	  
	glm::vec3(-0.50f, +0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 13  
	glm::vec3(+0.00f, -0.25f, -1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 14  
	glm::vec3(-0.50f, -0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 15

	// Back side of arrow tip
	glm::vec3(-0.50f, +0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 16 		  
	glm::vec3(+0.50f, +0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 17  
	glm::vec3(-0.50f, -0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 18  
	glm::vec3(+0.50f, -0.25f, -0.25f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 19

	// Top side of back of arrow
	glm::vec3(+0.25f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 20	  
	glm::vec3(+0.25f, +0.25f, +1.00f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 21  
	glm::vec3(-0.25f, +0.25f, +1.00f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 22  
	glm::vec3(-0.25f, +0.25f, -0.25f), glm::vec3(+1.00f, +0.00f, +0.00f), //vertice 23 

	// Bottom side of back of arrow
	glm::vec3(+0.25f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 24	  
	glm::vec3(+0.25f, -0.25f, +1.00f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 25 
	glm::vec3(-0.25f, -0.25f, +1.00f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 26 
	glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(+0.00f, +0.00f, +1.00f), //vertice 27

	// Right side of back of arrow
	glm::vec3(+0.25f, +0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 28	  
	glm::vec3(+0.25f, -0.25f, -0.25f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 29  
	glm::vec3(+0.25f, -0.25f, +1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 30  
	glm::vec3(+0.25f, +0.25f, +1.00f), glm::vec3(+0.60f, +1.00f, +0.00f), //vertice 31

	// Left side of back of arrow
	glm::vec3(-0.25f, +0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 32		  
	glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 33	 
	glm::vec3(-0.25f, -0.25f, +1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 34  
	glm::vec3(-0.25f, +0.25f, +1.00f), glm::vec3(+0.00f, +1.00f, +0.00f), //vertice 35  
	
	// Back side of back of arrow
	glm::vec3(-0.25f, +0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 36  
	glm::vec3(+0.25f, +0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 37  
	glm::vec3(-0.25f, -0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 38 
	glm::vec3(+0.25f, -0.25f, +1.00f), glm::vec3(+0.50f, +0.50f, +0.50f), //vertice 39  
	};

	GLushort stackIndices[] = {
	0, 1, 2, // Top
	0, 2, 3,
	4, 6, 5, // Bottom
	4, 7, 6,
	8, 10, 9, // Right side of arrow tip
	8, 11, 10,
	12, 15, 13, // Left side of arrow tip
	12, 14, 15,
	16, 19, 17, // Back side of arrow tip
	16, 18, 19,
	20, 22, 21, // Top side of back of arrow
	20, 23, 22,
	24, 25, 26, // Bottom side of back of arrow
	24, 26, 27,
	28, 30, 29, // Right side of back of arrow
	28, 31, 30,
	32, 33, 34, // Left side of back of arrow
	32, 34, 35,
	36, 39, 37, // Back side of back of arrow
	36, 38, 39,
	};

	data.numVertices = sizeof(stackVerts) / sizeof(*stackVerts);
	data.vertices = new Vertex[data.numVertices];
	memcpy(data.vertices, stackVerts, sizeof(stackVerts));

	data.numIndices = sizeof(stackIndices) / sizeof(*stackIndices);
	data.indices = new GLushort[data.numIndices];
	memcpy(data.indices, stackIndices, sizeof(stackIndices));
	return data;
}
