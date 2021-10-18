#pragma once

#include <exception>
#define GLEW_STATIC
#include <GL/glew.h>

namespace util {

	class Ebo {
	public:
		Ebo();
		~Ebo();

		GLuint eboID;

		void bind();
		void unbind();

		void load(long data[], long dataSize);
		void unload();
	};
}