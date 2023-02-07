#include "VAO.h"

VAO::VAO()
{

	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO VBO, GLuint Layout, GLuint numcomponent, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(Layout,numcomponent, type,GL_FALSE,stride,offset);
	glEnableVertexAttribArray(Layout);
	VBO.UnBind();

}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
