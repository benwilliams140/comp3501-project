#include "Objects/terrain.h"
#include "Control/game.h"
#include "Control/scene_node.h"
#include "Control/scene_graph.h"

using namespace Math;


namespace game {
	Terrain::Terrain(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {}
	Terrain::~Terrain() {}

	void Terrain::Update(void) {

	}

	float Terrain::GetHeightAt(int x, int z) {
		return geometry_->GetTerrainData()->heightMatrix[(x * geometry_->GetTerrainData()->length) + z];
	}

	Point3 Terrain::GetPointAt(int x, int z) {
		Vector3 scale = geometry_->GetTerrainData()->scale;
		return GetPosition() + Vector3(x * scale.x, GetHeightAt(x, z), z * scale.z);;
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

	void Terrain::UpdateShaderUniform(GLuint program) {}

} // namespace game