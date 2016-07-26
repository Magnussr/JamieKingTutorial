/*Using glew to glew likes to be the first libery to be initialized */
#include <gl\glew.h>
/*Using to acces the <OpenGLWindow.h> libery*/
#include <OpenGLWindow.h>

/*initializeGl runs only once during the duration of the window
That is why it's god to give the vertices her so the GPU only get the vertices once*/

void OpenGLWindow::initializeGL()
{
	/*Sets up the function pointer to all the GLfuntions and returns an error code*/
	glewInit();


	/*OpenGL Coordinate system works as 0.0, 0.0 is in the center, +1.0 , +1.0 is in the top right corner 
	and -1.0, -1.0 is in the button right corner. */

	/*Glfloat is OpenGLs float*/
	GLfloat  vertices[] =
	{
		+1.0f, +0.0f,
		+0.0f, +1.0f,
		+0.0f, -1.0f,

		-1.0f, +0.0f,
		+0.0f, -1.0f,
		+0.0f, +1.0f,
	};

	/*Copies the vertices to the GPU we create a buffer object*/

	/*GLuint creates a buffer name/ID*/
	GLuint verticesBufferID;

	/*glGenBuffers Creates a BufferObject(Is how meny buffer objects you want, the &ID of the bufferObject that is going to be used is stored) */
	glGenBuffers(1, &verticesBufferID);
	/*glBindBuffer binds verticesBufferID to a bufferbindingpoint.(the type of bufferbindingpoint, ID of the bufferObject)*/
	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferID);
	/*glBufferData sends the data down to the GPU and tells it how the data looks(where to send the data,the sizeof data,The address of the data,what to do with the data)*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/*glEnableVertexAttribArray (posision)*/
	glEnableVertexAttribArray(0);
	/*glVertexAttribPointer describs the data(Attributs, Floats per verteks, what type of data, what to do with the data, ,)*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	GLushort shapes[] =
	{
		3,1,2, 0,3,4
	};

	/*GLuint creates a buffer name/ID*/
	GLuint shapeBufferID;

	/*glGenBuffers Creates a BufferObject(Is how meny buffer objects you want, the &ID of the bufferObject that is going to be used) */
	glGenBuffers(1, &shapeBufferID);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapes), shapes, GL_STATIC_DRAW);
}

/*Runs each time we draw*/
void OpenGLWindow::paintGL()
{
	glViewport(0, 0, width(), height());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	/*glClearColor takes in 4 values between 1 and 0. Where 1 is all the way on and 0 being all the way off. 
	First is Red, Secund is Green, Theird is Blue and the Fourt is the transparency*/
	//glClearColor(1, 0, 0, 1);
	
	/*glClear clears the GL_COLOR_BUFFER_BIT each frame*/
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}


