/*Using glew to glew likes to be the first libery to be initialized */
#include <gl\glew.h>
/*Using input output stream*/
#include <iostream>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
/*Using to acces the <OpenGLWindow.h> libery*/
#include <OpenGLWindow.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <Vertex.h>
#include <ShapeGenerator.h>
#include <FileReader.h>
#include <StatusCheck.h>
#include <Camera.h>

using namespace std;
using glm::vec3;
using glm::mat4;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

/*Glfloat is OpenGLs float*/
/*Max value of an unsigned byte GLubyte = 255*/
/*Max value of an unsigned short GLushort = 65,535*/
/*GLuint is openGLs unsigned int that goes from 0 to 4,294,967,295 and it 32 bit*/
GLuint programID;
GLuint theBufferID;
GLuint cubeNumIndices;
GLuint arrowNumIndices;
GLuint cubeIndexByteOffset;
GLuint arrowIndexByteOffset;
GLuint cubeVertexArrayObjectID;
GLuint arrowVertexArrayObjectID;
GLuint fullTransformationUniformLocation;

Camera camera;

void OpenGLWindow::sendDataToOpenGL(){

	ShapeData cube = ShapeGenerator::makeCube();
	ShapeData arrow = ShapeGenerator::makeArrow();

	/*Copies the vertices to the GPU we create a buffer object*/

	/*glGenBuffers Creates a BufferObject(Is how meny buffer objects you want, the &ID of the bufferObject that is going to be used is stored) */
	glGenBuffers(1, &theBufferID);

	/*glBindBuffer binds verticesBufferID to a bufferbindingpoint.(the type of bufferbindingpoint, ID of the bufferObject)*/
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);

	/*glBufferData sends the data down to the GPU and tells it how the data looks(where to send the data,the sizeof data,The address of the data,what to do with the data)*/
	glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize() + cube.indexBufferSize() + arrow.vertexBufferSize() + arrow.indexBufferSize(), 0, GL_STATIC_DRAW);
	
	GLsizeiptr currentOffset = 0;

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.vertexBufferSize(), cube.vertices);
	
	currentOffset += cube.vertexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.indexBufferSize(), cube.indices);

	currentOffset += cube.indexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), arrow.vertices);

	currentOffset += arrow.vertexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), arrow.indices);

	cubeNumIndices = cube.numIndices;
	arrowNumIndices = arrow.numIndices;

	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);

	glBindVertexArray(cubeVertexArrayObjectID);

	/*glEnableVertexAttribArray = 0. Zero desribes (posision)*/
	glEnableVertexAttribArray(0);
	/*glEnableVertexAttribArray = 1. Zero desribes (color)*/
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);

	/*glVertexAttribPointer describs the data(Attributs, Floats per verteks, what type of data, what to do with the data, Distens in bytes between the vertecs attributs,)*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	/*glVertexAttribPointer describs the data*/						//most be sendt in as a pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	glBindVertexArray(arrowVertexArrayObjectID);

	/*glEnableVertexAttribArray = 0. Zero desribes (posision)*/
	glEnableVertexAttribArray(0);
	/*glEnableVertexAttribArray = 1. Zero desribes (color)*/
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint arrowByteOffset = cube.vertexBufferSize() + cube.indexBufferSize();
	/*glVertexAttribPointer describs the data(Attributs, Floats per verteks, what type of data, what to do with the data, Distens in bytes between the vertecs attributs,)*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)arrowByteOffset);
	/*glVertexAttribPointer describs the data*/						//most be sendt in as a pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(arrowByteOffset + sizeof(float) * 3));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	cubeIndexByteOffset = cube.vertexBufferSize();
	arrowIndexByteOffset = arrowByteOffset + arrow.vertexBufferSize();
	
	cube.cleanup();
	arrow.cleanup();
}
	
/*Runs each time we draw*/
void OpenGLWindow::paintGL() {

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	mat4 fullTransformMatrix;
	mat4 viewToProjectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	// Cube
	glBindVertexArray(cubeVertexArrayObjectID);
	mat4 cube1ModelToWorldMatrix =
		glm::translate(vec3(-2.0f, 0.0f, -3.0f)) *
		glm::rotate(36.0f, vec3(1.0f, 0.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexByteOffset);

	mat4 cube2ModelToWorldMatrix =
		glm::translate(vec3(2.0f, 0.0f, -3.75f)) *
		glm::rotate(126.0f, vec3(0.0f, 1.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * cube2ModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexByteOffset);

	// Arrow
	glBindVertexArray(arrowVertexArrayObjectID);
	mat4 arrowModelToWorldMatrix = glm::translate(0.0f, 0.0f, -3.0f);
	fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexByteOffset);

	///*glClear clears the GL_DEPTH_BUFFER_BIT and GL_COLOR_BUFFER_BIT each frame*/
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	///*glViewport where to start to render(horizontal,vertical, width, height) */
	//glViewport(0, 0, width(), height());

	//mat4 fullTransformMatrix;

	//glm::mat4 viewToProjectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f);
	//glm::mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	//glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	////GLint fullTransformMatrixUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");

	//

	///* Thired         Second      First    * Vertex*/  
	///*projection * translation * rotation  * Vertex*/

	//

	//
	///*Cube 1*/
	//glBindVertexArray(cubeVertexArrayObjectID);

	//glm::mat4 cube1ModelToWorldMatrix = glm::translate(vec3(-2.0f, 0.0f, -3.0f));
	///*The rotationMatrix is used to rotate the object(It's a 4x4 Matrix, THe Degress you want to rotate, 3x3 Vector(That thakes inn 3 values(X, Y, Z))) */
	//								   glm::rotate(36.0f, vec3(1.0f, 0.0f, 0.0f));
	//
	//fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;
	///*Sends the fullTransformMatrix in to the VertexShader*/
	//glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	//
	///*glm::vec3 dominatingColor(5.0f, 5.0f, 0.5f);
	//GLint dominatingColorUniformLOcater = glGetUniformLocation(programID, "dominatingColor");
	//glUniform3fv(dominatingColorUniformLOcater, 1, &dominatingColor[0]);*/




	///*glDrawArrays (what type of data, wher to start drawing, how many vertices )*/
	////glDrawArrays(GL_TRIANGLES, 0, 6);

	///*glClearColor takes in 4 values between 1 and 0. Where 1 is all the way on and 0 being all the way off.
	//First is Red, Secund is Green, Theird is Blue and the Fourt is the transparency*/
	////glClearColor(1, 0, 0, 1);

	///*glDrawElements*/
	//glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexByteOffset);


	///*Cube 2*/
	//glm::mat4 cube2ModelToWorldMatrix = glm::translate(vec3(2.0f, 0.0f, -3.75f)) *
	///*The rotationMatrix is used to rotate the object(It's a 4x4 Matrix, THe Degress you want to rotate, 3x3 Vector(That thakes inn 3 values(X, Y, Z))) */
	//									glm::rotate(126.0f, vec3(0.0f, 1.0f, 0.0f));

	//fullTransformMatrix = worldToProjectionMatrix * cube2ModelToWorldMatrix;
	///*Sends the fullTransformMatrix in to the VertexShader*/
	//glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	///*glDrawElements*/
	//glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexByteOffset);

	//// Arrow 

	//glBindVertexArray(arrowVertexArrayObjectID);
	//mat4 arrowModelToWorldMatrix = glm::translate(0.0f, 0.0f, -3.0f);
	//fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;
	//glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	//glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexByteOffset);

}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* e){
	camera.mouseUpdate(glm::vec2(e->x(), e->y()));
	repaint();
}

void OpenGLWindow::keyPressEvent(QKeyEvent* e){

	switch (e->key()){
	case Qt::Key_W:
		camera.moveForward();
		break;
	case Qt::Key_S:
		camera.moveBackward();
		break;
	case Qt::Key_A:
		camera.strafeLeft();
		break;
	case Qt::Key_D:
		camera.strafeRight();
		break;
	case Qt::Key_R:
		camera.moveUp();
		break;
	case Qt::Key_F:
		camera.moveDown();
		break;
	}
	repaint();
	
}
void OpenGLWindow::installShaders(){

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

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);


}


/*initializeGl runs only once during the duration of the window
That is why it's god to give the vertices her so the GPU only get the vertices once*/

void OpenGLWindow::initializeGL(){


	/*Sets up the function pointer to all the GLfuntions and returns an error code*/
	setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	installShaders();
	fullTransformationUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
}
OpenGLWindow::~OpenGLWindow()
{
	glDeleteBuffers(1, &theBufferID);
	glUseProgram(0);
	glDeleteProgram(programID);
}