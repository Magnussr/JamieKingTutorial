/*Using HEADER GUARDS so that the Libary dos not get included/define multipul timese*/
#ifndef OPEN_GL_WINDOW
#define OPEN_GL_WINDOW
/*Using <QtOpenGL\qglwidget> to use OpenGL*/
#include <QtOpenGL\qglwidget>

/*Class Name that inherit from QGLWidget*/
class OpenGLWindow : public QGLWidget{

/*protected functions that can ony be used by classes that inherit from ther Class */
protected: 
	/*Qt functions that we override*/
	/* */
	void initializeGL();
	/*funtion Qt calls whenevery it expect rendering or drawing calling commands*/
	void paintGL();
/*public functions can be used by all classes*/
public:
	
};
/*Ends the HEADER GUARDS*/
#endif
