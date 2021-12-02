#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Control/resource.h"

// Default extensions for different shader source files
#define VERTEX_PROGRAM_EXTENSION "_vp.glsl"
#define FRAGMENT_PROGRAM_EXTENSION "_fp.glsl"

namespace game {

    // Class that manages all resources
    class ResourceManager {
    public:
        // Constructor and destructor
        ResourceManager(void);
        ~ResourceManager();
        // Add a resource that was already loaded and allocated to memory
        void AddResource(ResourceType type, const std::string name, GLuint resource, GLsizei size);
        void AddResource(ResourceType type, const std::string name, util::Vao* vao, util::Ebo* ebo, GLsizei size);
        void AddResource(ResourceType type, const std::string name, util::Vao* vao, util::Ebo* ebo, GLsizei size, TerrainData* terrainData);
        // Load a resource from a file, according to the specified type
        void LoadResource(ResourceType type, const std::string name, const char* filename, glm::vec3 scale = glm::vec3(1.0f));
        // Get the resource with the specified name
        Resource* GetResource(const std::string name) const;

        // Methods to create specific resources
        // Create the geometry for a terrain from perlin noise
        void CreateTerrain(std::string object_name, glm::vec3 scale);
        // Create the geometry for a torus and add it to the list of resources
        void CreateTorus(std::string object_name, float loop_radius = 0.6, float circle_radius = 0.2, int num_loop_samples = 90, int num_circle_samples = 30);
        void CreateSeamlessTorus(std::string object_name, float loop_radius = 0.6, float circle_radius = 0.2, int num_loop_samples = 90, int num_circle_samples = 30);
        // Create the geometry for a sphere
        void CreateSphere(std::string object_name, float radius = 0.6, int num_samples_theta = 90, int num_samples_phi = 45);
        void CreateCylinder(std::string object_name, float height = 1.0, float circle_radius = 0.6, int num_loop_samples = 90, int num_circle_samples = 30);

        // "Wall", a flat object
        void CreateQuad(std::string object_name);

    private:
        // List storing all resources
        std::vector<Resource*> resource_;

        // Methods to load specific types of resources
        // Load shaders programs
        void LoadMaterial(const std::string name, const char* prefix);
        // Load a text file into memory (could be source code)
        std::string LoadTextFile(const char* filename);
        // Load a texture from an image file: png, jpg, etc.
        void LoadTexture(const std::string name, const char* filename);
        // Loads a mesh from .mesh format
        void LoadMesh(const std::string name, const char* filename);
        // Loads a terrain from height map image
        void LoadTerrain(const std::string name, const char* filename, glm::vec3 scale);

        // Generates the terrain from input data
        void GenerateTerrain(std::string object_name, int width, int length, glm::vec3 scale, float* heightMatrix, glm::vec3* normalMatrix, float minHeight, float maxHeight);

    }; // class ResourceManager

} // namespace game

#endif // RESOURCE_MANAGER_H_