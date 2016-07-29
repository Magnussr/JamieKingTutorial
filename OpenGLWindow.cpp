/*Using glew to glew likes to be the first libery to be initialized */
#include <gl\glew.h>
/*Using input output stream*/
#include <iostream>
/*Using to acces the <OpenGLWindow.h> libery*/
#include <OpenGLWindow.h>
#include <glm\glm.hpp>
#include <Vertex.h>
#include <ShapeGenerator.h>
#include <FileReader.h>
#include <StatusCheck.h>

GLuint programID;

void sendDatatoOpenGL(){

	ShapeData tri = ShapeGenerator::makeTriangle();

	/*Glfloat is OpenGLs float*/
	
	/*Copies the vertices to the GPU we create a buffer object*/

	/*GLuint creates a buffer name/ID*/
	GLuint verticesBufferID;

	/*glGenBuffers Creates a BufferObject(Is how meny buffer objects you want, the &ID of the bufferObject that is going to be used is stored) */
	glGenBuffers(1, &verticesBufferID);
	/*glBindBuffer binds verticesBufferID to a bufferbindingpoint.(the type of bufferbindingpoint, ID of the bufferObject)*/
	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferID);
	/*glBufferData sends the data down to the GPU and tells it how the data looks(where to send the data,the sizeof data,The address of the data,what to do with the data)*/
	glBufferData(GL_ARRAY_BUFFER, tri.vertexBufferSize(), tri.vertices, GL_STATIC_DRAW);
	/*glEnableVertexAttribArray = 0. Zero desribes (posision)*/
	glEnableVertexAttribArray(0);
	/*glVertexAttribPointer describs the data(Attributs, Floats per verteks, what type of data, what to do with the data, Distens in bytes between the vertecs attributs,)*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	/*glEnableVertexAttribArray = 1. Zero desribes (color)*/
	glEnableVertexAttribArray(1);
	/*glVertexAttribPointer describs the data*/						//most be sendt in as a pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	/*Max value of an unsigned byte GLubyte = 255*/
	/*Max value of an unsigned short GLushort = 65,535*/
	/*Max value of an unsigned int GLuint = 4,294,967,295*/

	/*GLuint creates a buffer name/ID*/
	GLuint shapeBufferID;

	/*glGenBuffers Creates a BufferObject(Is how meny buffer objects you want, the &ID of the bufferObject that is going to be used) */
	glGenBuffers(1, &shapeBufferID);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.indexBufferSize() , tri.indices , GL_STATIC_DRAW);
	tri.cleanup();
}
	
/*Runs each time we draw*/
void OpenGLWindow::paintGL() {

	/*glClear clears the GL_DEPTH_BUFFER_BIT and GL_COLOR_BUFFER_BIT each frame*/
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	/*glViewport where to start to render(horizontal,vertical, width, height) */
	glViewport(0, 0, width(), height());

	glm::vec3 dominatingColor(5.0f, 5.0f, 0.5f);
	GLint dominatingColorUniformLOcater = glGetUniformLocation(programID, "dominatingColor");
	glUniform3fv(dominatingColorUniformLOcater, 1, &dominatingColor[0]);




	/*glDrawArrays (what type of data, wher to start drawing, how many vertices )*/
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	/*glClearColor takes in 4 values between 1 and 0. Where 1 is all the way on and 0 being all the way off.
	First is Red, Secund is Green, Theird is Blue and the Fourt is the transparency*/
	//glClearColor(1, 0, 0, 1);

	/*glDrawElements*/
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void installShaders(){

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	std::string temporary = FileReader::readShaderCode("VertexShader.glsl");
	adapter[0] = temporary.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temporary = FileReader::readShaderCode("FragmentShader.glsl");
	adapter[0] = temporary.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!StatusCheck::checkShaderStatus(vertexShaderID) || !StatusCheck::checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	
	if (!StatusCheck::checkProgramStatus(programID))
		return;

	glUseProgram(programID);
}

/*initializeGl runs only once during the duration of the window
That is why it's god to give the vertices her so the GPU only get the vertices once*/

void OpenGLWindow::initializeGL(){

	/*Sets up the function pointer to all the GLfuntions and returns an error code*/
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDatatoOpenGL();
	installShaders();
}