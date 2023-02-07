#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);

	}

	throw (errno);


}

Shader::Shader(const char* vertexFile, const char* fragFile)

{
	//taking the vertext code from vertex file and string in vertex code  and fragent code
	std::string vertexcode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragFile);

	// setting vertex source and fragment source -from string to char 
	const char* vertexSource = vertexcode.c_str();
	const char* fragmentSource = fragmentCode.c_str();


    // CREATE VERTEX SHADER
    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vertexSource, NULL);
    glCompileShader(VertexShader);

    // CREATE FRAGMENT SHAADER
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(FragmentShader);

    // CREATE SHADER PROGRAM
   ID = glCreateProgram();

    // ATTACH SHADER WITH PROGRAM 
    glAttachShader(ID, VertexShader);
    glAttachShader(ID, FragmentShader);

    // LINK PROGRAM
    glLinkProgram(ID);

    // DELETE VERTEXAND FRAGMENT SHADER
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);


}

void Shader::Activate()
{

    glUseProgram(ID);

}
void Shader::Delete()
{
    glDeleteProgram(ID);

}
