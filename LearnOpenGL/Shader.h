#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		// Read Shader Files

		string vertexCode;
		string fragmentCode;

		ifstream vertexShaderFile;
		ifstream fragmentShaderFile;

		ofstream test;

		vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try
		{
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragmentPath);

			stringstream vertexShaderStream;
			stringstream fragmentShaderStream;

			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();

			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();
		}
		catch(ifstream::failure error)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}

		const char* vertexShaderCode = vertexCode.c_str();
		const char* fragmentShaderCode = fragmentCode.c_str();

		// Compile Shaders

		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexShaderCode, NULL); // Attach shader source code to the shader object
		glCompileShader(vertex);							// Compile shader

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);	// Checks for compile errors
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);	// Retrieves compile errors
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentShaderCode, NULL); // Attach shader source code to the shader object
		glCompileShader(fragment);								// Compile shader

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);	// Checks for compile errors
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);	// Retrieves compile errors
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// Shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);		// Attach compiled shaders to the shader program
		glAttachShader(ID, fragment);
		glLinkProgram(ID); // Link attached shaders

		glGetProgramiv(ID, GL_LINK_STATUS, &success); // Checks for linking errors
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog); // Retrieves linking errors
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}

		// Delete Shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
};

#endif