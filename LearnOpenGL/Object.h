#ifndef OBJECT_H
#define OBJECT_H

#include "stb_image.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Object
{
public:
	Object(vector<float> vertices, vector<unsigned int> indices, string texturePath)
	{
		triangleCount = vertices.size() / 5;

		// Vertices
		this->vertices = new float[vertices.size()];
		for (int i = 0; i < vertices.size(); i++)
		{
			this->vertices[i] = vertices[i];
		}

		// Indices
		this->indices = new unsigned int[indices.size()];
		for (int i = 0; i < indices.size(); i++)
		{
			this->indices[i] = indices[i];
		}

		GenerateVAO();
		GenerateVBO();
		GenerateEBO();
		DefineVertexData();
		GenerateTexture(texturePath);
		Unbind();
	}

	void Draw()
	{
		Bind();
		glDrawArrays(GL_TRIANGLES, 0, triangleCount);
		Unbind();
	}
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	float* vertices;
	unsigned int* indices;
	unsigned int texture;

	int triangleCount;

	void Bind()
	{
		glBindVertexArray(VAO);
	}

	void Unbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GenerateVAO()
	{
		glGenVertexArrays(1, &VAO);
		Bind();
	}

	void GenerateVBO()
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void GenerateEBO()
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void DefineVertexData()
	{
		// Vertex Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// UV Coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void GenerateTexture(string path)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// Texture Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load Image
		stbi_set_flip_vertically_on_load(true);

		int width, height, colorChannels;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &colorChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cout << "Failed to load texture" << endl;
		}
		stbi_image_free(data);

		glActiveTexture(GL_TEXTURE0);
	}
};

#endif