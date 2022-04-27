#pragma once
#include <vector>
#include "Vector2f.h"

namespace collisions
{
	struct CollisionHitInfo
	{
		bool hit = false;
		float depth = 0.f;
		Vector2f normal = Vector2f();

		explicit CollisionHitInfo(bool hit, float depth, Vector2f normal)
			: hit{ hit }, depth{ depth }, normal{ normal } {}
	};

	// Polygon Intersection using SAT (Seperating Axis Theorem)
	CollisionHitInfo IntersectPolygons(const std::vector<Vector2f>& verticesA, const std::vector<Vector2f>& verticesB);
	Vector2f FindArithmeticMean(const std::vector<Vector2f> vertices);
	void ProjectVertices(const std::vector<Vector2f>& vertices, Vector2f axis, float& min, float& max);

	bool IntersectLinePolygon(Vector2f p1, Vector2f p2, const std::vector<Vector2f>& vertices);
	bool IntersectLines(Vector2f p1, Vector2f p2, Vector2f p3, Vector2f p4);
	bool IntersectPointPolygon(Vector2f p1, const std::vector<Vector2f>& vertices);
}