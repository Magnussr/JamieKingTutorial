/*Using glew to glew likes to be the first libery to be initialized */
#include <gl\glew.h>
/*Using input output stream*/
#include <iostream>
/*Using to read from file*/
#include <fstream>
/*Using to acces the <OpenGLWindow.h> libery*/
#include <OpenGLWindow.h>
#include <filesystem>

using namespace std;

void sendDatatoOpenGL(){
	/*OpenGL Coordinate system works as 0.0, 0.0 is in the center, +1.0 , +1.0 is in the top right corner
	and -1.0, -1.0 is in the button right corner. */

	/*Glfloat is OpenGLs float*/
	GLfloat  vertices[] =
	{
		/*First 2 is Position, Next 3 is the RGB Color RED, GREEN, BLUE*/
		+1.0f, +0.0f, +1.0f, +0.0f, +0.0f, //vertice 0
		+0.0f, +1.0f, +0.0f, +1.0f, +0.0f, //vertice 1  
		+0.0f, -1.0f, +0.0f, +0.0f, +1.0f, //vertice 2
		-1.0f, +0.0f, +1.0f, +0.0f, +0.0f, //vertice 3
										   //+0.0f, -1.0f, +0.0, +0.0, +0.0, //vertice 4 Er lik vertice 2 
										   //+0.0f, +1.0f, +0.0, +0.0, +0.0,//vertice 5 Er lik vertice 1
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
	/*glEnableVertexAttribArray = 0. Zero desribes (posision)*/
	glEnableVertexAttribArray(0);
	/*glVertexAttribPointer describs the data(Attributs, Floats per verteks, what type of data, what to do with the data, Distens in bytes between the vertecs attributs,)*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	/*glEnableVertexAttribArray = 1. Zero desribes (color)*/
	glEnableVertexAttribArray(1);
	/*glVertexAttribPointer describs the data*/						//most be sendt in as a pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

	/*Max value of an unsigned byte GLubyte = 255*/
	/*Max value of an unsigned short GLushort = 65,535*/
	/*Max value of an unsigned int GLuint = 4,294,967,295*/

	GLushort shapes[] =
	{
		3,2,1, 0,1,2
	};

	/*GLuint creates a buffer name/ID*/
	GLuint shapeBufferID;

	/*glGenBuffers Creates a BufferObject(Is how meny buffer objects you want, the &ID of the bufferObject that is going to be used) */
	glGenBuffers(1, &shapeBufferID);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapes), shapes, GL_STATIC_DRAW);
}

bool checkStatus(GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if(status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete [] buffer;
		return false;
	}
	return true;
}
	
bool checkShaderStatus(GLuint shaderID){
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}
	return true;
}

bool checkProgramStatus(GLuint programID){
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if(linkStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete [] buffer;
		return false;
	}
	return true;
	
}
	
string readShaderCode(const char* fileName)
{
	ifstream input(fileName);
	if( ! input.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>());
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	string temporary = readShaderCode("VertexShader.glsl");
	adapter[0] = temporary.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temporary = readShaderCode("FragmentShader.glsl");
	adapter[0] = temporary.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;


	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	
	if (!checkProgramStatus(programID))
		return;

	glUseProgram(programID);
}




/*initializeGl runs only once during the duration of the window
That is why it's god to give the vertices her so the GPU only get the vertices once*/

void OpenGLWindow::initializeGL()
{
	/*Sets up the function pointer to all the GLfuntions and returns an error code*/
	glewInit();
	sendDatatoOpenGL();
	installShaders();


}

/*Runs each time we draw*/
void OpenGLWindow::paintGL()
{
	/*glViewport where to start to render(horizontal,vertical, width, height) */
	glViewport(0, 0, width(), height());
	/*glDrawArrays (what type of data, wher to start drawing, how many vertices )*/
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	/*glClearColor takes in 4 values between 1 and 0. Where 1 is all the way on and 0 being all the way off. 
	First is Red, Secund is Green, Theird is Blue and the Fourt is the transparency*/
	//glClearColor(1, 0, 0, 1);
	
	/*glClear clears the GL_COLOR_BUFFER_BIT each frame*/
	glClear(GL_COLOR_BUFFER_BIT);

	/*glDrawElements*/
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}


