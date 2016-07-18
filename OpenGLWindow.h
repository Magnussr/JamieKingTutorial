#ifndef OPEN_GL_WINDOW
#define OPEN_GL_WINDOW
#include <QtOpenGL\qglwidget>

class OpenGLWindow : public QGLWidget{
protected: 
	void initializeGL();
	void paintGL();

public:
	
};

#endif
