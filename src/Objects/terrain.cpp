#include "Objects/terrain.h"

namespace game {
	Terrain::Terrain(const std::string name, const Resource* geometry, const Resource* material) : SceneNode(name, geometry, material) {}
	Terrain::~Terrain() {}

	float Terrain::GetHeightAt(float x, float z) {
		// TODO - find height of terrain at specific x, z coordinate
		return NULL;
	}

	void Terrain::Update(void) {

	}


} // namespace game