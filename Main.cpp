/*Useing the <Qt\qapplication.h> libery to create a Qt window*/
#include <Qt\qapplication.h>

/*Useing the <OpenGLWindow.h> to draw on window*/
#include <OpenGLWindow.h>

/*Function that runs the program that takes inn 2 arguments. argc(argument count) and argv (argument vector) are how command line arguments are passed to main().
argc is an integer parameter and it is the number of arguments passed to the program.
Program name is always the first argument, so there will be at least one argument to a program and minimum value of argc will be 1.
But if a program has itself 2 arguments the value of argc will be 3.
Parameter argv points to a string array and is called the "argument vector". It is a one dimensional string array of function arguments.*/
int main(int argc, char* argv[]){

	/*Useing QApplication function and calls it app that thakes inn 2 arguments argc, argv*/
	QApplication app(argc, argv);

	/*Useing OpenGLWindow Class and call it window*/
	OpenGLWindow window;

	/*Useing .show to show openGLWindow*/
	window.show();

	/*returns app and .exec funtion execute a new executable*/
	return app.exec();
}