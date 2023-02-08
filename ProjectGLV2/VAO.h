#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<GL/glew.h>
#include"VBO.h"

class VAO
{

public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO& VBO, GLuint Layout , GLuint numcomponent ,GLenum type , GLsizeiptr stride , void* offset  );
	void Bind();
	void UnBind();
	void Delete();


};

#endif