#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <glfw3.h>
#include <glew.h>
#include <glm.hpp>


int main() {
	if (!glfwInit()) {
		printf("GLFW init fail\n");
		glfwTerminate();
	}
	glTexCoord1d(5.0);
	glm::abs(10);
	printf("Hello Uwuorld\n");
	glfwTerminate();
	return 0;
}