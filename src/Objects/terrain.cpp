#include "Objects/terrain.h"
#include "Control/game.h"
#include "Control/scene_node.h"
#include "Control/scene_graph.h"

using namespace Math;


namespace game {
	Terrain::Terrain(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material) {}
	Terrain::~Terrain() {}

	void Terrain::Update(void) {}

	float Terrain::GetHeightAt(float x, float z) {
		// Initial variables
		Vector3 offset = GetPosition(); // translation of the terrain
		Vector3 scale = geometry_->GetTerrainData()->scale; // scale of the terrain

		// Reverse point at
		int xIndex = (long)((x - offset.x) / scale.x); // (long) truncates
		int zIndex = (long)((z - offset.z) / scale.z); // (long) truncates

		// Find all 4 vertices on terrain
		Point3 p0 = GetPointAt(xIndex, zIndex);
		Point3 p1 = GetPointAt(xIndex + 1, zIndex);
		Point3 p2 = GetPointAt(xIndex + 1, zIndex + 1);
		Point3 p3 = GetPointAt(xIndex, zIndex + 1);

		// Calculate interpolation factors
		float interpFactorX = (x - p0.x) / scale.x;
		float interpFactorZ = (z - p0.z) / scale.z;

		// Calculate interpolation for each edge
		float interpX1 = glm::mix( p0.y, p1.y, interpFactorX);
		float interpX2 = glm::mix( p3.y, p2.y, interpFactorX);
		float interpZ1 = glm::mix( p0.y, p3.y, interpFactorZ);
		float interpZ2 = glm::mix( p1.y, p2.y, interpFactorZ);

		// Average interpolations and return
		float finalInterp = (interpX1 + interpX2 + interpZ1 + interpZ2) / 4.0f;
		return finalInterp;
	}

	float Terrain::GetVertexHeightAt(int x, int z) {
		// Check for index out of bound
		if (x >= geometry_->GetTerrainData()->width || x < 0 || z >= geometry_->GetTerrainData()->length || z < 0) 
			return NULL;

		return geometry_->GetTerrainData()->heightMatrix[(x * geometry_->GetTerrainData()->length) + z];
	}

	Point3 Terrain::GetPointAt(int x, int z) {
		Vector3 scale = geometry_->GetTerrainData()->scale;
		return GetPosition() + Vector3(x * scale.x, GetVertexHeightAt(x, z), z * scale.z);;
	}

	Normal Terrain::GetNormalAt(float x, float z) {
		// Initial variables
		Vector3 offset = GetPosition(); // translation of the terrain
		Vector3 scale = geometry_->GetTerrainData()->scale; // scale of the terrain

		// Reverse point at
		int xIndex = (long)((x - offset.x) / scale.x); // (long) truncates
		int zIndex = (long)((z - offset.z) / scale.z); // (long) truncates

		// Find all 4 vertices on terrain
		Normal p0 = GetVertexNormalAt(xIndex, zIndex);
		Normal p1 = GetVertexNormalAt(xIndex + 1, zIndex);
		Normal p2 = GetVertexNormalAt(xIndex + 1, zIndex + 1);
		Normal p3 = GetVertexNormalAt(xIndex, zIndex + 1);

		// Calculate interpolation factors
		float interpFactorX = (x - p0.x) / scale.x;
		float interpFactorZ = (z - p0.z) / scale.z;

		// Calculate interpolation for each edge
		Normal interpX1 = glm::mix(p0, p1, interpFactorX);
		Normal interpX2 = glm::mix(p3, p2, interpFactorX);
		Normal interpZ1 = glm::mix(p0, p3, interpFactorZ);
		Normal interpZ2 = glm::mix(p1, p2, interpFactorZ);

		// Average interpolations and return
		Normal finalInterp = glm::normalize(interpX1 + interpX2 + interpZ1 + interpZ2);
		return finalInterp;
	}

	Normal Terrain::GetVertexNormalAt(int x, int z) {
		// Check for index out of bound
		if (x >= geometry_->GetTerrainData()->width || x < 0 || z >= geometry_->GetTerrainData()->length || z < 0) 
			return Vector3(0.0f);

		return geometry_->GetTerrainData()->normalMatrix[(x * geometry_->GetTerrainData()->length) + z];
	}

   /**
	*   Checks if a ray collides with the terrain and return the hitPoint if it does
	* 
	*	@param[in]
	*	P = position of the object.
	*	d = half of the length of the ray.
	*	@param[out]
	*   hitPoint = point where the ray collided.
	*	@return a boolean representing whether the ray collided with the terrain or not.
	*/
	bool Terrain::Collision(Point3 P, float d, Point3& hitPoint) {
		// Ray represented by two points
		Point3 A = Point3(P.x, P.y + d, P.z);
		Point3 B = Point3(P.x, P.y - d, P.z);

		// Initial variables
		Vector3 offset = GetPosition(); // translation of the terrain
		Vector3 scale = geometry_->GetTerrainData()->scale; // scale of the terrain

		// Reverse point at
		int x = (long)((P.x - offset.x) / scale.x); // (long) truncates
		int z = (long)((P.z - offset.z) / scale.z); // (long) truncates

		// Find all 4 vertices on terrain
		Point3 p0 = GetPointAt(x, z);
		Point3 p1 = GetPointAt(x + 1, z);
		Point3 p2 = GetPointAt(x + 1, z + 1);
		Point3 p3 = GetPointAt(x, z + 1);

		float t;
		// Check both triangles for hits
		if (Terrain::CanHit(A, B, p0, p2, p1, t, hitPoint)) return true;
		if (Terrain::CanHit(A, B, p0, p3, p2, t, hitPoint)) return true;

		return false;
	}

	bool Terrain::CanHit(Point3 A, Point3 B, Point3 p0, Point3 p1, Point3 p2, float& t, Point3& hitPoint) {
		Normal N = glm::cross((p1 - p0), (p2 - p0));
		N = glm::normalize(N);

		// Check if floor plane can be hit
		Plane F = Plane(N, p0);
		if (!Plane::CanHit(A, B, F, t, hitPoint)) return false;

		// Check if hitpoint is on the correct side of side plane 1
		Normal sN1 = glm::cross(N, (p1 - p0)); Plane sP1 = Plane(sN1, p0);
		if (sP1.DistanceTo(hitPoint) < -0.001f) return false;

		// Check if hitpoint is on the correct side of side plane 2
		Normal sN2 = glm::cross(N, (p2 - p1)); Plane sP2 = Plane(sN2, p1);
		if (sP2.DistanceTo(hitPoint) < -0.001f) return false;

		// Check if hitpoint is on the correct side of side plane 3
		Normal sN3 = glm::cross(N, (p0 - p2)); Plane sP3 = Plane(sN3, p2);
		if (sP3.DistanceTo(hitPoint) < -0.001f) return false;
		
		return true;
	}

	void Terrain::InitShaderUniform(GLuint program) {
		TerrainData* terrainData = geometry_->GetTerrainData();
		GLint terrain_bounds_var = glGetUniformLocation(program, "terrain_bounds");
		glUniform2f(terrain_bounds_var, terrainData->minHeight + this->GetPosition().y, terrainData->maxHeight + GetPosition().y);
	}

	void Terrain::UpdateShaderUniform(GLuint program) {
		for (int i = 0; i < 4; i++) {
			// Texture
			GLuint texture = textures_[i]->GetResource();
			if (texture) {
				GLint tex = glGetUniformLocation(program, std::string("terrain_texture_" + std::to_string(i + 1)).c_str());
				glUniform1i(tex, i + 1); // Assign the first texture to the map
				glActiveTexture(GL_TEXTURE0 + i + 1);
				glBindTexture(GL_TEXTURE_2D, texture); // First texture we bind
				// Define texture interpolation
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}
		}
	}

	float Terrain::GetWidth(void) const {
		return ((float)geometry_->GetTerrainData()->width) * geometry_->GetTerrainData()->scale.x;
	}

	float Terrain::GetLength(void) const {
		return ((float)geometry_->GetTerrainData()->length) * geometry_->GetTerrainData()->scale.z;
	}

	void Terrain::SetTextures(const std::string tex1, const std::string tex2, const std::string tex3, const std::string tex4) {
		textures_.push_back(Game::GetInstance().GetResource(tex1));
		textures_.push_back(Game::GetInstance().GetResource(tex2));
		textures_.push_back(Game::GetInstance().GetResource(tex3));
		textures_.push_back(Game::GetInstance().GetResource(tex4));
	}

} // namespace game