#pragma once

#include <exception>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>

namespace util {

	class Vao {
	public:
		Vao();
		~Vao();

		GLuint vaoID;
		std::vector<GLuint> vboIDs;

		void bind();
		void unbind();

		void loadFloatArrayInAttribList(int AttribNumber, float data[], long dataSize, long dataStride);
		void loadIntegerArrayInAttribList(int AttribNumber, int data[], long dataSize, long dataStride);

		void unload();
	};
}