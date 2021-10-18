#include "vao.h"

namespace util {

	Vao::Vao() {
		glGenVertexArrays(1, &vaoID); //Create vao. All VertexAttribArray are disabled upon creation.
	}
	Vao::~Vao() {
		unload();
	}

	void Vao::bind() {
		glBindVertexArray(vaoID);
	}

	void Vao::unbind() {
		glBindVertexArray(0);
	}

	void Vao::loadFloatArrayInAttribList(int AttribNumber, float data[], long dataSize, long dataStride) {
		glBindVertexArray(vaoID);
		GLuint buffer = -1; //If we don't get one, it will remain -1.
		glGenBuffers(1, &buffer); //Create buffer

		if (buffer == -1) { std::bad_alloc::exception("\n[OpenGL Warning] Failed to generate new vertex buffer object.");  return; }
		vboIDs.push_back(buffer);

		GLsizeiptr dataByteSize = sizeof(float) * dataSize;
		glBindBuffer(GL_ARRAY_BUFFER, buffer); //Select
		glBufferData(GL_ARRAY_BUFFER, dataByteSize, ((void*)0), GL_STATIC_DRAW); //Describe
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataByteSize, data); //Upload

		glEnableVertexAttribArray(AttribNumber);
		glVertexAttribPointer(AttribNumber, dataStride, GL_FLOAT, GL_FALSE, sizeof(float) * dataStride, (void*)(long long)0);
	}

	void Vao::loadIntegerArrayInAttribList(int AttribNumber, int data[], long dataSize, long dataStride) {
		glBindVertexArray(vaoID);
		GLuint buffer = -1; //If we don't get one, it will remain -1.
		glGenBuffers(1, &buffer); //Create buffer

		if (buffer == -1) { std::bad_alloc::exception("\n[OpenGL Warning] Failed to generate new vertex buffer object.");  return; }
		vboIDs.push_back(buffer);

		GLsizeiptr dataByteSize = sizeof(float) * dataSize;
		glBindBuffer(GL_ARRAY_BUFFER, buffer); //Select
		glBufferData(GL_ARRAY_BUFFER, dataByteSize, ((void*)0), GL_STATIC_DRAW); //Describe
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataByteSize, data); //Upload

		glEnableVertexAttribArray(AttribNumber);
		glVertexAttribIPointer(AttribNumber, dataStride, GL_INT, sizeof(int) * dataStride, (void*)(long long)0);
	}

	void Vao::unload() {
		GLuint* vbos = vboIDs.data();
		glDeleteBuffers((GLsizei)vboIDs.size(), vbos); // Delete vbos
		delete vbos;
		glDeleteVertexArrays(1, &vaoID); // Delete vao
	}
}