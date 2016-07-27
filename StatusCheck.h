#ifndef STATUS_CHECK
#define STATUS_CHECK

class StatusCheck{
public:
	 static bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
		PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);

	 static bool checkShaderStatus(GLuint shaderID);

	 static bool checkProgramStatus(GLuint programID);
};

#endif
