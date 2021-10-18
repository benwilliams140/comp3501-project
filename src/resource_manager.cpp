#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SOIL/SOIL.h>

#include "resource_manager.h"
#include "model_loader.h"

namespace game {

ResourceManager::ResourceManager(void){}
ResourceManager::~ResourceManager(){}

void ResourceManager::AddResource(ResourceType type, const std::string name, GLuint resource, GLsizei size){
    Resource *res;
    res = new Resource(type, name, resource, size);

    resource_.push_back(res);
}

void ResourceManager::AddResource(ResourceType type, const std::string name, util::Vao* array_buffer, util::Ebo* element_array_buffer, GLsizei size){
    Resource *res;
    res = new Resource(type, name, array_buffer, element_array_buffer, size);

    resource_.push_back(res);
}

void ResourceManager::LoadResource(ResourceType type, const std::string name, const char *filename){
    // Call appropriate method depending on type of resource
    if (type == Material){
        LoadMaterial(name, filename);
    } else if (type == Texture){
        LoadTexture(name, filename);
    } else if (type == Mesh){
        LoadMesh(name, filename);
    } else {
        throw(std::invalid_argument(std::string("Invalid type of resource")));
    }
}

Resource *ResourceManager::GetResource(const std::string name) const {
    // Find resource with the specified name
    for (int i = 0; i < resource_.size(); i++){
        if (resource_[i]->GetName() == name){
            return resource_[i];
        }
    }
    return NULL;
}

void ResourceManager::LoadMaterial(const std::string name, const char *prefix){
    // Load vertex program source code
    std::string filename = std::string(prefix) + std::string(VERTEX_PROGRAM_EXTENSION);
    std::string vp = LoadTextFile(filename.c_str());

    // Load fragment program source code
    filename = std::string(prefix) + std::string(FRAGMENT_PROGRAM_EXTENSION);
    std::string fp = LoadTextFile(filename.c_str());

    // Create a shader from the vertex program source code
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char *source_vp = vp.c_str();
    glShaderSource(vs, 1, &source_vp, NULL);
    glCompileShader(vs);

    // Check if shader compiled successfully
    GLint status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE){
        char buffer[512];
        glGetShaderInfoLog(vs, 512, NULL, buffer);
        throw(std::ios_base::failure(std::string("Error compiling vertex shader: ")+std::string(buffer)));
    }

    // Create a shader from the fragment program source code
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char *source_fp = fp.c_str();
    glShaderSource(fs, 1, &source_fp, NULL);
    glCompileShader(fs);

    // Check if shader compiled successfully
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE){
        char buffer[512];
        glGetShaderInfoLog(fs, 512, NULL, buffer);
        throw(std::ios_base::failure(std::string("Error compiling fragment shader: ")+std::string(buffer)));
    }

    // Create a shader program linking both vertex and fragment shaders
    // together
    GLuint sp = glCreateProgram();
    glAttachShader(sp, vs);
    glAttachShader(sp, fs);
    glLinkProgram(sp);

    // Check if shaders were linked successfully
    glGetProgramiv(sp, GL_LINK_STATUS, &status);
    if (status != GL_TRUE){
        char buffer[512];
        glGetShaderInfoLog(sp, 512, NULL, buffer);
        throw(std::ios_base::failure(std::string("Error linking shaders: ")+std::string(buffer)));
    }

    // Delete memory used by shaders, since they were already compiled
    // and linked
    glDeleteShader(vs);
    glDeleteShader(fs);

    // Add a resource for the shader program
    AddResource(Material, name, sp, 0);
}

std::string ResourceManager::LoadTextFile(const char *filename){
    // Open file
    std::ifstream f;
    f.open(filename);
    if (f.fail()){
        throw(std::ios_base::failure(std::string("Error opening file ")+std::string(filename)));
    }

    // Read file
    std::string content;
    std::string line;
    while(std::getline(f, line)){
        content += line + "\n";
    }

    // Close file
    f.close();

    return content;
}

// Create the geometry for a cylinder
void ResourceManager::CreateCylinder(std::string object_name, float height, float circle_radius, int num_height_samples, int num_circle_samples) {
	// Create a cylinder

	// Number of vertices and faces to be created
	const GLuint vertex_num = num_height_samples * num_circle_samples + 2; // plus two for top and bottom
	const GLuint face_num = num_height_samples * (num_circle_samples - 1) * 2 + 2 * num_circle_samples; // two extra rings worth for top and bottom

																										// Number of attributes for vertices and faces
	const int vertex_att = 11;  // 11 attributes per vertex: 3D position (3), 3D normal (3), RGB color (3), 2D texture coordinates (2)
	const int face_att = 3; // Vertex indices (3)

							// Data buffers for the shape
	GLfloat *vertex = NULL;
	GLuint *face = NULL;

	GLuint vbo, ebo;

	// Allocate memory for buffers
	try {
		vertex = new GLfloat[vertex_num * vertex_att];
		face = new GLuint[face_num * face_att];
	}
	catch (std::exception &e) {
		throw e;
	}

	// Create vertices 
	float theta; // Angle for circle
	float h; // height
	float s, t; // parameters zero to one
	glm::vec3 loop_center;
	glm::vec3 vertex_position;
	glm::vec3 vertex_normal;
	glm::vec3 vertex_color;
	glm::vec2 vertex_coord;

	for (int i = 0; i < num_height_samples; i++) { // along the side

		s = i / (float)num_height_samples; // parameter s (vertical)
		h = (-0.5 + s)*height;
		for (int j = 0; j < num_circle_samples; j++) { // small circle
			t = j / (float)num_circle_samples;
			theta = 2.0*glm::pi<GLfloat>()*t; // circle sample (angle theta)

											  // Define position, normal and color of vertex
			vertex_normal = glm::vec3(cos(theta), 0.0f, sin(theta));
			vertex_position = glm::vec3(cos(theta)*circle_radius, h, sin(theta)*circle_radius);
			vertex_color = glm::vec3(1.0 - s,
				t,
				s);
			vertex_coord = glm::vec2(s, t);

			// Add vectors to the data buffer
			for (int k = 0; k < 3; k++) {
				vertex[(i*num_circle_samples + j)*vertex_att + k] = vertex_position[k];
				vertex[(i*num_circle_samples + j)*vertex_att + k + 3] = vertex_normal[k];
				vertex[(i*num_circle_samples + j)*vertex_att + k + 6] = vertex_color[k];
			}
			vertex[(i*num_circle_samples + j)*vertex_att + 9] = vertex_coord[0];
			vertex[(i*num_circle_samples + j)*vertex_att + 10] = vertex_coord[1];
		}
	}

	int topvertex = num_circle_samples * num_height_samples;
	int bottomvertex = num_circle_samples * num_height_samples + 1; // indices for top and bottom vertex

	vertex_position = glm::vec3(0, (-0.5+(num_height_samples-1.0f)/num_height_samples)*height, 0); // location of top middle of cylinder
	vertex_normal = glm::vec3(0, 1, 0);
	vertex_color = glm::vec3(1, 0.6, 0.4);
	vertex_coord = glm::vec2(0, 0); // no good way to texture top and bottom

	for (int k = 0; k < 3; k++) {
		vertex[topvertex*vertex_att + k] = vertex_position[k];
		vertex[topvertex*vertex_att + k + 3] = vertex_normal[k];
		vertex[topvertex*vertex_att + k + 6] = vertex_color[k];
	}
	vertex[(topvertex)*vertex_att + 9] = vertex_coord[0];
	vertex[(topvertex)*vertex_att + 10] = vertex_coord[1];

	//================== bottom vertex
	vertex_position = glm::vec3(0, (-0.5)*height, 0); // location of bottom middle of cylinder
	vertex_normal = glm::vec3(0, -1, 0);
	// leave the color and uv alone

	for (int k = 0; k < 3; k++) {
		vertex[bottomvertex*vertex_att + k] = vertex_position[k];
		vertex[bottomvertex*vertex_att + k + 3] = vertex_normal[k];
		vertex[bottomvertex*vertex_att + k + 6] = vertex_color[k];
	}
	vertex[(bottomvertex)*vertex_att + 9] = vertex_coord[0];
	vertex[(bottomvertex)*vertex_att + 10] = vertex_coord[1];

	//===================== end of vertices

	// Create triangles
	for (int i = 0; i < num_height_samples - 1; i++) {
		for (int j = 0; j < num_circle_samples; j++) {
			// Two triangles per quad
			glm::vec3 t1(((i + 1) % num_height_samples)*num_circle_samples + j,
				i*num_circle_samples + ((j + 1) % num_circle_samples),
				i*num_circle_samples + j);
			glm::vec3 t2(((i + 1) % num_height_samples)*num_circle_samples + j,
				((i + 1) % num_height_samples)*num_circle_samples + ((j + 1) % num_circle_samples),
				i*num_circle_samples + ((j + 1) % num_circle_samples));
			// Add two triangles to the data buffer
			for (int k = 0; k < 3; k++) {
				face[(i*num_circle_samples + j)*face_att * 2 + k] = (GLuint)t1[k];
				face[(i*num_circle_samples + j)*face_att * 2 + k + face_att] = (GLuint)t2[k];
			}
		}
	}
	int cylbodysize = num_circle_samples * (num_height_samples - 1) * 2; // amount of array filled so far, start adding from here
																		 // triangles for top disc (fan shape)
	int i = num_height_samples - 1;
	for (int j = 0; j < num_circle_samples; j++) {
		// Bunch of wedges pointing to the centre
		glm::vec3 topwedge(
			i*num_circle_samples + j,
			topvertex,
			i*num_circle_samples + (j + 1) % num_circle_samples
		);

		// note order reversed so that all triangles point outward
		glm::vec3 botwedge(
			0 + (j + 1) % num_circle_samples,
			bottomvertex,
			0 + j
		);

		// Add the triangles to the data buffer
		for (int k = 0; k < 3; k++) {
			face[(cylbodysize + j)*face_att + k] = (GLuint)topwedge[k];
			face[(cylbodysize + j + num_circle_samples)*face_att + k] = (GLuint)botwedge[k];
		}
	}

	// Create OpenGL buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_num * vertex_att * sizeof(GLfloat), vertex, GL_STATIC_DRAW);

	// Create OpenGL buffer for faces
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_num * face_att * sizeof(GLuint), face, GL_STATIC_DRAW);

	// Free data buffers
	delete[] vertex;
	delete[] face;

	// Create resource
    // TODO - fix resource
	//AddResource(Mesh, object_name, vbo, ebo, face_num * face_att);
}

void ResourceManager::CreateTorus(std::string object_name, float loop_radius, float circle_radius, int num_loop_samples, int num_circle_samples) {

	// Create a torus
	// The torus is built from a large loop with small circles around the loop

	// Number of vertices and faces to be created
	// Check the construction algorithm below to understand the numbers
	// specified below
	const GLuint vertex_num = num_loop_samples * num_circle_samples;
	const GLuint face_num = num_loop_samples * num_circle_samples * 2;

	// Number of attributes for vertices and faces
	const int vertex_att = 11;
	const int face_att = 3;

	// Data buffers for the torus
	GLfloat *vertex = NULL;
	GLuint *face = NULL;

	// Allocate memory for buffers
	try {
		vertex = new GLfloat[vertex_num * vertex_att]; // 11 attributes per vertex: 3D position (3), 3D normal (3), RGB color (3), 2D texture coordinates (2)
		face = new GLuint[face_num * face_att]; // 3 indices per face
	}
	catch (std::exception &e) {
		throw e;
	}

	// Create vertices 
	float theta, phi; // Angles for circles
	glm::vec3 loop_center;
	glm::vec3 vertex_position;
	glm::vec3 vertex_normal;
	glm::vec3 vertex_color;
	glm::vec2 vertex_coord;

	for (int i = 0; i < num_loop_samples; i++) { // large loop

		theta = 2.0*glm::pi<GLfloat>()*i / num_loop_samples; // loop sample (angle theta)
		loop_center = glm::vec3(loop_radius*cos(theta), loop_radius*sin(theta), 0); // centre of a small circle

		for (int j = 0; j < num_circle_samples; j++) { // small circle

			phi = 2.0*glm::pi<GLfloat>()*j / num_circle_samples; // circle sample (angle phi)

																 // Define position, normal and color of vertex
			vertex_normal = glm::vec3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));
			vertex_position = loop_center + vertex_normal * circle_radius;
			vertex_color = glm::vec3(1.0 - ((float)i / (float)num_loop_samples),
				(float)i / (float)num_loop_samples,
				(float)j / (float)num_circle_samples);
			vertex_coord = glm::vec2(theta / (2.0*glm::pi<GLfloat>()),
				phi / (2.0*glm::pi<GLfloat>()));

			// Add vectors to the data buffer
			for (int k = 0; k < 3; k++) {
				vertex[(i*num_circle_samples + j)*vertex_att + k] = vertex_position[k];
				vertex[(i*num_circle_samples + j)*vertex_att + k + 3] = vertex_normal[k];
				vertex[(i*num_circle_samples + j)*vertex_att + k + 6] = vertex_color[k];
			}
			vertex[(i*num_circle_samples + j)*vertex_att + 9] = vertex_coord[0];
			vertex[(i*num_circle_samples + j)*vertex_att + 10] = vertex_coord[1];
		}
	}

	// Create triangles
	for (int i = 0; i < num_loop_samples; i++) {
		for (int j = 0; j < num_circle_samples; j++) {
			// Two triangles per quad
			glm::vec3 t1(((i + 1) % num_loop_samples)*num_circle_samples + j,
				i*num_circle_samples + ((j + 1) % num_circle_samples),
				i*num_circle_samples + j);
			glm::vec3 t2(((i + 1) % num_loop_samples)*num_circle_samples + j,
				((i + 1) % num_loop_samples)*num_circle_samples + ((j + 1) % num_circle_samples),
				i*num_circle_samples + ((j + 1) % num_circle_samples));
			// Add two triangles to the data buffer
			for (int k = 0; k < 3; k++) {
				face[(i*num_circle_samples + j)*face_att * 2 + k] = (GLuint)t1[k];
				face[(i*num_circle_samples + j)*face_att * 2 + k + face_att] = (GLuint)t2[k];
			}
		}
	}

	// Create OpenGL buffers and copy data
	GLuint vbo, ebo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_num * vertex_att * sizeof(GLfloat), vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_num * face_att * sizeof(GLuint), face, GL_STATIC_DRAW);

	// Free data buffers
	delete[] vertex;
	delete[] face;

	// Create resource
    // TODO - fix resource
	//AddResource(Mesh, object_name, vbo, ebo, face_num * face_att);
}

void ResourceManager::CreateSeamlessTorus(std::string object_name, float loop_radius, float circle_radius, int num_loop_samples, int num_circle_samples){
    // Create a torus
    // The torus is built from a large loop with small circles around the loop

    // Number of vertices and faces to be created
    // Check the construction algorithm below to understand the numbers
    // specified below
    const GLuint vertex_num = (num_loop_samples+1)*(num_circle_samples+1);
    const GLuint face_num = num_loop_samples*num_circle_samples*2;

    // Number of attributes for vertices and faces
    const int vertex_att = 11;
    const int face_att = 3;

    // Data buffers for the torus
    GLfloat *vertex = NULL;
    GLuint *face = NULL;

    // Allocate memory for buffers
    try {
        vertex = new GLfloat[vertex_num * vertex_att]; // 11 attributes per vertex: 3D position (3), 3D normal (3), RGB color (3), 2D texture coordinates (2)
        face = new GLuint[face_num * face_att]; // 3 indices per face
    }
    catch  (std::exception &e){
        throw e;
    }

    // Create vertices 
    float theta, phi; // Angles for circles
    glm::vec3 loop_center;
    glm::vec3 vertex_position;
    glm::vec3 vertex_normal;
    glm::vec3 vertex_color;
    glm::vec2 vertex_coord;
	float s, t;
    for (int i = 0; i < num_loop_samples+1; i++){ // large loop
        
        theta = 2.0*glm::pi<GLfloat>()*i/num_loop_samples; // loop sample (angle theta)
        loop_center = glm::vec3(loop_radius*cos(theta), loop_radius*sin(theta), 0); // centre of a small circle

        for (int j = 0; j < num_circle_samples+1; j++){ // small circle
            
            phi = 2.0*glm::pi<GLfloat>()*j/num_circle_samples; // circle sample (angle phi)
			s = theta / (2.0*glm::pi<GLfloat>());
			t = ((phi) / (2.0*glm::pi<GLfloat>()));

			phi += glm::pi<GLfloat>();

            // Define position, normal and color of vertex
            vertex_normal = glm::vec3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));
            vertex_position = loop_center + vertex_normal*circle_radius;
            vertex_color = glm::vec3(1.0 - ((float) i / (float) num_loop_samples), 
                                            (float) i / (float) num_loop_samples, 
                                            (float) j / (float) num_circle_samples);
		
			vertex_coord = glm::vec2(s, t); // good parameterization but seam at last triangle
//			vertex_coord = glm::vec2(fabs(1-2*s),fabs(1-2*t)); // made seamless through mirroring
//			vertex_coord = glm::vec2((rand() % 2000) / 2000.0, (rand() % 2000) / 2000.0);
            // Add vectors to the data buffer
            for (int k = 0; k < 3; k++){
                vertex[(i*(num_circle_samples+1)+j)*vertex_att + k] = vertex_position[k];
                vertex[(i*(num_circle_samples+1)+j)*vertex_att + k + 3] = vertex_normal[k];
                vertex[(i*(num_circle_samples+1)+j)*vertex_att + k + 6] = vertex_color[k];
            }
            vertex[(i*(num_circle_samples+1)+j)*vertex_att + 9] = vertex_coord[0];
            vertex[(i*(num_circle_samples+1)+j)*vertex_att + 10] = vertex_coord[1];
        }
    }

    // Create triangles
    for (int i = 0; i < num_loop_samples; i++){
        for (int j = 0; j < num_circle_samples; j++){
            // Two triangles per quad
			glm::vec3 t1((i + 1)*(num_circle_samples + 1) + j,
				i*(num_circle_samples + 1) + (j + 1),
				i*(num_circle_samples + 1) + j);
			glm::vec3 t2((i + 1)*(num_circle_samples + 1) + j,
				(i + 1)*(num_circle_samples + 1) + (j + 1),
				i*(num_circle_samples + 1) + (j + 1));
            // Add two triangles to the data buffer
            for (int k = 0; k < 3; k++){
                face[(i*(num_circle_samples)+j)*face_att*2 + k] = (GLuint) t1[k];
                face[(i*(num_circle_samples)+j)*face_att*2 + k + face_att] = (GLuint) t2[k];
            }
        }
    }

    // Create OpenGL buffers and copy data
    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_num * vertex_att * sizeof(GLfloat), vertex, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_num * face_att * sizeof(GLuint), face, GL_STATIC_DRAW);

    // Free data buffers
    delete [] vertex;
    delete [] face;

    // Create resource
    // TODO - fix resource
    //AddResource(Mesh, object_name, vbo, ebo, face_num * face_att);
}

void ResourceManager::CreateSphere(std::string object_name, float radius, int num_samples_theta, int num_samples_phi){
    // Create a sphere using a well-known parameterization

    // Number of vertices and faces to be created
    const GLuint vertex_num = num_samples_theta*num_samples_phi;
    const GLuint face_num = num_samples_theta*(num_samples_phi-1)*2;

    // Number of attributes for vertices and faces
    const int vertex_att = 11;
    const int face_att = 3;

    // Data buffers 
    GLfloat *vertex = NULL;
    GLuint *face = NULL;

    // Allocate memory for buffers
    try {
        vertex = new GLfloat[vertex_num * vertex_att]; // 11 attributes per vertex: 3D position (3), 3D normal (3), RGB color (3), 2D texture coordinates (2)
        face = new GLuint[face_num * face_att]; // 3 indices per face
    }
    catch  (std::exception &e){
        throw e;
    }

    // Create vertices 
    float theta, phi; // Angles for parametric equation
    glm::vec3 vertex_position;
    glm::vec3 vertex_normal;
    glm::vec3 vertex_color;
    glm::vec2 vertex_coord;
   
    for (int i = 0; i < num_samples_theta; i++){
            
        theta = 2.0*glm::pi<GLfloat>()*i/(num_samples_theta-1); // angle theta
            
        for (int j = 0; j < num_samples_phi; j++){
                    
            phi = glm::pi<GLfloat>()*j/(num_samples_phi-1); // angle phi

            // Define position, normal and color of vertex
            vertex_normal = glm::vec3(cos(theta)*sin(phi), sin(theta)*sin(phi), -cos(phi));
            // We need z = -cos(phi) to make sure that the z coordinate runs from -1 to 1 as phi runs from 0 to pi
            // Otherwise, the normal will be inverted
            vertex_position = glm::vec3(vertex_normal.x*radius, 
                                        vertex_normal.y*radius, 
                                        vertex_normal.z*radius),
            vertex_color = glm::vec3(((float)i)/((float)num_samples_theta), 1.0-((float)j)/((float)num_samples_phi), ((float)j)/((float)num_samples_phi));
            vertex_coord = glm::vec2(((float)i)/((float)num_samples_theta), 1.0-((float)j)/((float)num_samples_phi));

            // Add vectors to the data buffer
            for (int k = 0; k < 3; k++){
                vertex[(i*num_samples_phi+j)*vertex_att + k] = vertex_position[k];
                vertex[(i*num_samples_phi+j)*vertex_att + k + 3] = vertex_normal[k];
                vertex[(i*num_samples_phi+j)*vertex_att + k + 6] = vertex_color[k];
            }
            vertex[(i*num_samples_phi+j)*vertex_att + 9] = vertex_coord[0];
            vertex[(i*num_samples_phi+j)*vertex_att + 10] = vertex_coord[1];
        }
    }

    // Create faces
    for (int i = 0; i < num_samples_theta; i++){
        for (int j = 0; j < (num_samples_phi-1); j++){
            // Two triangles per quad
            glm::vec3 t1(((i + 1) % num_samples_theta)*num_samples_phi + j, 
                         i*num_samples_phi + (j + 1),
                         i*num_samples_phi + j);
            glm::vec3 t2(((i + 1) % num_samples_theta)*num_samples_phi + j, 
                         ((i + 1) % num_samples_theta)*num_samples_phi + (j + 1), 
                         i*num_samples_phi + (j + 1));
            // Add two triangles to the data buffer
            for (int k = 0; k < 3; k++){
                face[(i*(num_samples_phi-1)+j)*face_att*2 + k] = (GLuint) t1[k];
                face[(i*(num_samples_phi-1)+j)*face_att*2 + k + face_att] = (GLuint) t2[k];
            }
        }
    }

    // Create OpenGL buffers and copy data
    //GLuint vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);

    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_num * vertex_att * sizeof(GLfloat), vertex, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_num * face_att * sizeof(GLuint), face, GL_STATIC_DRAW);

    // Free data buffers
    delete [] vertex;
    delete [] face;

    // Create resource
    // TODO - fix resource
    //AddResource(Mesh, object_name, vbo, ebo, face_num * face_att);
}

void ResourceManager::LoadTexture(const std::string name, const char *filename){
    // Load texture from file
    GLuint texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
    if (!texture){
        throw(std::ios_base::failure(std::string("Error loading texture ")+std::string(filename)+std::string(": ")+std::string(SOIL_last_result())));
    }

    // Create resource
    AddResource(Texture, name, texture, 0);
}

void ResourceManager::CreateQuad(std::string object_name){
    long numVert = 4;
	float* vertices = new float[numVert * 3]{-0.5f,  0.0f, 0.5f,  0.5f,  0.0f, 0.5f,  0.5f,  0.0f,  -0.5f, -0.5f,  0.0f,  -0.5f};
	float* uvs = new float[numVert * 2]{0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.0f,  1.0f};
	float* normals = new float[numVert * 3]{0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f};
	float* tangents = new float[numVert * 3]{1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f};
	float* bitangents = new float[numVert * 3]{0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f};

    long numInd = 4;
	long* indices = new long[numInd] { 0, 1, 3, 2 };

    util::Vao* vao = new util::Vao();
    vao->bind();
    vao->loadFloatArrayInAttribList(0, vertices, numVert * 3, 3);
    vao->loadFloatArrayInAttribList(2, uvs, numVert * 2, 2);
    vao->loadFloatArrayInAttribList(3, normals, numVert * 3, 3);
    vao->loadFloatArrayInAttribList(4, tangents, numVert * 3, 3);
    vao->loadFloatArrayInAttribList(5, bitangents, numVert * 3, 3);

    util::Ebo* ebo = new util::Ebo();
    ebo->bind();
    ebo->load(indices, numInd);

    // Create resource
    AddResource(Mesh, object_name, vao, ebo, numInd);
}

#define RASC_HEADER (('C'<<24)+('S'<<16)+('A'<<8)+'R')
void ResourceManager::LoadMesh(const std::string object_name, const char *filename) {
	// Open file
    FILE* file = fopen(filename, "rb");
	if (file == NULL) { throw std::exception(std::string(std::string("Mesh file '")+std::string(filename)+std::string("' not found.")).c_str()); }

    struct FileHeader {
		int identifier; // Used to determine byte order
		int version[2]; // Major and minor version number
	};

    // Read and verify file header
    FileHeader header;
	fread(&header, sizeof(FileHeader), 1, file);
    if (header.identifier != RASC_HEADER) { throw std::exception("Invalid Mesh Loader Identifier."); }
    if (!(header.version[0] == 0 && header.version[1] == 7)) { throw std::exception("Invalid Mesh Loader Version."); }

    // Read mesh type enum
    long meshType = 0;
	fread(&meshType, sizeof(long), 1, file);

    // Read vertex stride
    long verticesStride = 0;
	fread(&verticesStride, sizeof(long), 1, file);

    // Read amount of vertices
    long vertexCount = 0;
	fread(&vertexCount, sizeof(long), 1, file);

    // Read vertices data
    float* vertices = new float[vertexCount*3];
	fread(vertices, sizeof(float), vertexCount*3, file);

    // Read texture coordinate data
    float* uvs = nullptr;
	if (meshType == 1 || meshType == 4 || meshType == 5 || meshType == 7 || meshType == 10 || meshType == 11) {
		uvs = new float[vertexCount*2];
		fread(uvs, sizeof(float), vertexCount*2, file);
	}

    // Read normal data
    float* normals = nullptr;
	if (meshType == 2 || meshType == 3 || meshType == 4 || meshType == 5 || meshType == 8 || meshType == 9 || meshType == 10 || meshType == 11) {
		normals = new float[vertexCount*3];
		fread(normals, sizeof(float), vertexCount*3, file);
	}

    // Read tangent and bitangent data
    float* tangents = nullptr; 
    float* bitangents = nullptr;
	if (meshType == 3 || meshType == 5 || meshType == 9 || meshType == 11) {
		tangents = new float[vertexCount*3];
		fread(tangents, sizeof(float), vertexCount*3, file);
		bitangents = new float[vertexCount*3];
		fread(bitangents, sizeof(float), vertexCount*3, file);
	}

    // Read weight indices and weights data
    int* weightIndices = nullptr;
	float* weights = nullptr;
	if (meshType == 6 || meshType == 7 || meshType == 8 || meshType == 9 || meshType == 10 || meshType == 11) {
		weightIndices = new int[vertexCount*3];
		fread(weightIndices, sizeof(float), vertexCount*3, file);
		weights = new float[vertexCount*3];
		fread(weights, sizeof(float), vertexCount*3, file);
	}

    // Read amount of indices array (one array per materials)
    long indexCount = 0;
	fread(&indexCount, sizeof(long), 1, file);

    // Read size of the first indices array
    long indicesSize = 10;
    fread(&indicesSize, sizeof(long), 1, file);

    // Read first indices data
    long* indices = new long[indicesSize];
    fread(indices, sizeof(long), indicesSize, file);

    // Close file
    fclose(file);

    // Create Vao
    util::Vao* vao = new util::Vao();
    vao->bind();
    vao->loadFloatArrayInAttribList(0, vertices, vertexCount * 3, 3);
    vao->loadFloatArrayInAttribList(2, uvs, vertexCount * 2, 2);
    vao->loadFloatArrayInAttribList(3, normals, vertexCount * 3, 3);
    vao->loadFloatArrayInAttribList(4, tangents, vertexCount * 3, 3);
    vao->loadFloatArrayInAttribList(5, bitangents, vertexCount * 3, 3);

    // Create Ebo
    util::Ebo* ebo = new util::Ebo();
    ebo->bind();
    ebo->load(indices, indicesSize);

	// Free data buffers
	delete[] vertices;
	delete[] indices;

    // Create resource
    AddResource(Mesh, object_name, vao, ebo, indicesSize);
}
#undef RASC_HEADER

} // namespace game;
