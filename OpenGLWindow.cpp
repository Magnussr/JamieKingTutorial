#include <gl\glew.h>
#include <OpenGLWindow.h>


void OpenGLWindow::initializeGL()
{
	glewInit();
}


void OpenGLWindow::paintGL()
{
	
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}


