#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

namespace Math {
	using Point2 = glm::vec3;
	using Point3 = glm::vec3;
	using Vector2 = glm::vec2;
	using Vector3 = glm::vec3;
	using Vector4 = glm::vec4;
	using Normal = glm::vec3;
	//using Ray = struct { Point3 A; Point3 B; }

	// AxB = [A2B3 - A3B2, A3B1 - A1B3, A1B2 - A2B1]
	inline Vector3 cross(Vector3 A, Vector3 B) { return Vector3((A.y * B.z) - (A.z * B.y), (A.z * B.x) - (A.x * B.z), (A.x * B.y) - (A.y * B.x)); }

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
