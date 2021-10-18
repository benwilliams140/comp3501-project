#include "Renderer/ebo.h"

namespace util {

	Ebo::Ebo() {
		glGenBuffers(1, &eboID);
	}

	Ebo::~Ebo() {
		unload();
	}

	void Ebo::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	}

	void Ebo::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Ebo::load(long data[], long dataSize) {
		if (eboID == -1) { std::exception("\n[OpenGL Warning] Failed to load EBO.");  return; }

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID); //Select
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(long) * dataSize, ((void*)0), GL_STATIC_DRAW); //Describe
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(long) * dataSize, data); //Upload
	}

	void Ebo::unload() {
		glDeleteBuffers(1, &eboID); // Delete ebo
	}
}