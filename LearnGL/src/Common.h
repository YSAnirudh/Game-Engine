#ifndef COMMON_H
#define COMMON_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "../stb_image.h"

const int MAX_DIR_LIGHTS = 8;
const int MAX_POINT_LIGHTS = 8;
const int MAX_SPOT_LIGHTS = 8;
#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_CALL(x) \
	GLClearErrors();\
	x;\
	ASSERT(GLLogCall())

static void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall() {
	while (GLenum error = glGetError()) {
		printf("OpenGL Error: (%d)\n", error);
		return false;
	}
	return true;
}

static bool FindString(std::string FullStr, std::string SubStrToFind) {
	size_t found = FullStr.find(SubStrToFind);
	if (found != std::string::npos) {
		return true;
	}
	return false;
}

#define ARRAY_SIZE_IN_ELEM(a) (sizeof(a)/sizeof(a[0]))

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

#define SAFE_DELETE(p) if (p) {delete p; p = nullptr;}

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

//#ifndef PRINT_MATRIX(a)
//#define PRINT_MATRIX(a) {\
//	for (int i = 0; i < 4; i++) {\
//		for (int j = 0; j < 4; j++) {\
//			printf("%f ", a[i][j]);\
//		}\
//		printf("\n");\
//	}\
//}
//#endif

#endif