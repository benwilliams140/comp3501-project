#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

namespace Math {
	// General aliases
	using Point2 = glm::vec3;
	using Point3 = glm::vec3;
	using Vector2 = glm::vec2;
	using Vector3 = glm::vec3;
	using Vector4 = glm::vec4;
	using Normal = glm::vec3;

	// Collider Objects
	struct SphereCollider {
		Point3 position;
		float radius;
	};
	struct AABBCollider { // Axis aligned bounding box collider
		Point3 min;
		Point3 max;
	};

	// Random Generation Functions
	inline float randRangeFloat(float min, float max) { return min + ((float)std::rand() / (float)RAND_MAX) * (max - min); }
	inline int randRangeInt(int min, int max) { return min + std::rand() * (max - min); }

	// Collision Detection Functions
	inline bool isCollidingPointToSphere(Point3 point, SphereCollider sphere) {
		float distance = sqrt(pow((point.x - sphere.position.x), 2.0f) + 
			                  pow((point.y - sphere.position.y), 2.0f) + 
			                  pow((point.z - sphere.position.z), 2.0f));
		return distance < sphere.radius;
	}

	inline bool isCollidingPointToAABB(Point3 point, AABBCollider box) {
		return (point.x >= box.min.x && point.x <= box.max.x) && 
			   (point.y >= box.min.y && point.y <= box.max.y) &&
			   (point.z >= box.min.z && point.z <= box.max.z);
	}

	inline bool isCollidingSphereToSphere(SphereCollider sphereA, SphereCollider sphereB) {
		float distance = sqrt(pow((sphereA.position.x - sphereB.position.x), 2.0f) + 
			                  pow((sphereA.position.y - sphereB.position.y), 2.0f) + 
			                  pow((sphereA.position.z - sphereB.position.z), 2.0f));
		return distance < (sphereA.radius + sphereB.radius);
	}

	inline bool isCollidingSphereToAABB(SphereCollider sphere, AABBCollider box) {
		// Find the closest point of the AABB to the sphere's center
		Point3 point = glm::max(box.min, glm::min(sphere.position, box.max));
		return isCollidingPointToSphere(point, sphere);
	}

	inline bool isCollidingAABBToAABB(AABBCollider boxA, AABBCollider boxB) {
		return (boxA.min.x <= boxB.max.x && boxA.max.x >= boxB.min.x) && 
			   (boxA.min.y <= boxB.max.y && boxA.max.y >= boxB.min.y) &&
			   (boxA.min.z <= boxB.max.z && boxA.max.z >= boxB.min.z);
	}

	// Plane Class definition
	class Plane { // [a, b, c, d] = [Nx, Ny, Nz, -N.p0]
	public:
		Plane(Normal normal, Point3 p0) {
			this->normal = normal;
			this->p0 = p0;
		}
		~Plane() {}

		Normal normal; Point3 p0;

		float DistanceTo(Point3& point) { 
			return glm::dot(normal, (point - p0)); 
		}

		float d() { 
			return -glm::dot(normal, p0); 
		}

		Point3 AnyPoint() { 
			return normal * glm::dot(normal, p0); 
		}

		static bool CanHit(Point3 A, Point3 B, Plane aPlane, float& t, Point3& hitPoint) {
			Normal N = aPlane.normal; t = 2.0;

			float denominator = glm::dot(N, (A - B));
			if (denominator < 1.0e-10) return false;
			float numerator = glm::dot(N, A) + aPlane.d();

			t = numerator / denominator;
			hitPoint = A + (B - A) * t;

			return true;
		}
	};
}
