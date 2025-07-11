#include "Shaders.h"



//Static initializations
GLfloat Shaders::lightblue[4] = { 0.5f, 0.8f, 1.0f, 1.0f };      // Light blue
GLfloat Shaders::yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };    // Yellow
GLfloat Shaders::white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Shaders::pink[4] = { 1.0f, 0.75f, 0.8f, 1.0f };
GLfloat Shaders::red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };


GLfloat* Shaders::Colors[5] = { Shaders::lightblue, Shaders::yellow, Shaders::white, Shaders::pink, Shaders::red };



Shaders::Shaders(const char* vertexFile, const char* fragmentFile) {
	


	//Read vertex shader file and fragment shader file
	std::string vertexShaderCode = get_file_contents(vertexFile);
	std::string fragmentShaderCode = get_file_contents(fragmentFile);

	//const char* ptrs
	const char * vertexSource = vertexShaderCode.c_str();
	const char* fragmentSource = fragmentShaderCode.c_str();

	//Creating and combiling vertex shader
	GLuint vertextShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertextShader, 1, &vertexSource, NULL);
	glCompileShader(vertextShader);


	//Creating and combiling fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);



	//Set ID of shader for accessability from outside
	ID = glCreateProgram();

	//Wrap them in a shader program
	glAttachShader(ID, vertextShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	//Init uniform locations
	u_Color_location = glGetUniformLocation(ID, "u_Color");
	u_Center_location = glGetUniformLocation(ID, "u_Center");


	//Deallocate memory
	glDeleteShader(vertextShader);
	glDeleteShader(fragmentShader);

}
void Shaders::Activate() {
	glUseProgram(ID);
}
void Shaders::Delete() {
	glUseProgram(ID);
}


//Utilities 
std::string Shaders::get_file_contents(const char* filename)
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
		return contents;
	}
	throw(errno);
}


void Shaders::LoadColor(short numColor) {
	
	 glUniform4f(u_Color_location,
		Shaders::Colors[numColor][0],
		Shaders::Colors[numColor][1],
		Shaders::Colors[numColor][2],
		Shaders::Colors[numColor][3]);
}

void Shaders::LoadPosition(GLfloat x, GLfloat y) {
	glUniform2f(u_Center_location, x , y);
}

void Shaders::DrawPrimitive() {
	// Draw the triangle using the GL_TRIANGLES primitive
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Shaders::LoadCirclePositionToBackBuffer(Circle *Circle1) {

		LoadColor(Circle1->getColor());
		LoadPosition(Circle1->getPosition().x, Circle1->getPosition().y);
		DrawPrimitive();
	

}
