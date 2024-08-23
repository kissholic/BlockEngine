/*
 * File: Main.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */


#include <filesystem>
#include "glad/glad.h"
#define GLFW_INCLUDE_OPENGL
#include "GLFW/glfw3.h"
#include <spdlog/spdlog.h>
#include "Graphics/GraphicsContext.h"
#include "Graphics/ShaderLoader.h"
#include "Path.h"

#include "BEConfig.h"


float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};


int main(int, char**)
{
	be::GraphicsContext Context(1280, 720, "BeEngine");
	
	if (!Context.Init()) {
		spdlog::error("Failed to initialize graphics context");
		return -1;
	}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	std::filesystem::path vertexPath = be::Path::ShaderPath() / "DummyVertex.glsl";
	std::filesystem::path fragShaderPath = be::Path::ShaderPath() / "DummyFrag.glsl";
	auto shaderProgram = be::CreateShaderProgram(vertexPath, fragShaderPath);

	shaderProgram.Use();
	glBindVertexArray(VBO);

	while (!Context.ShouldExit()) {
		glClearColor(0.3f, 0.6f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Context.Step(1.0 / 60.0);
	}

	return 0;
}
