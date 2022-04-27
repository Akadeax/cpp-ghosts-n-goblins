#include "pch.h"

#include "collisions.h"
#include "utils.h"
#include <iostream>

collisions::CollisionHitInfo collisions::IntersectPolygons(const std::vector<Vector2f>& verticesA, const std::vector<Vector2f>& verticesB)
{
	size_t aSize = verticesA.size();
	size_t bSize = verticesB.size();

	float depth = FLT_MAX;
	Vector2f normal = Vector2f();

	for (size_t i{ 0 }; i < aSize; i++)
	{
		Vector2f vA = verticesA[i];
		Vector2f vB = verticesA[(i + 1) % aSize];

		Vector2f edge = vB - vA;

		Vector2f axis = Vector2f(-edge.y, edge.x).Normalized();
		//utils::SetColor(Color4f(0, 1, 0, 1));
		//utils::DrawLine(axis, 1);

		//utils::SetColor(Color4f(0, 1, 0, 1));
		//utils::DrawLine(axis * 1000, 2);
		//utils::DrawLine(-axis * 1000, 2);
		float minA, maxA, minB, maxB;
		ProjectVertices(verticesA, axis, minA, maxA);
		ProjectVertices(verticesB, axis, minB, maxB);

		bool hasGap = minA >= maxB || minB >= maxA;
		if (hasGap) return CollisionHitInfo(false, 0, Vector2f());

		float axisDepth = std::min(maxB - minA, maxA - minB);
		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}

	for (size_t i{ 0 }; i < bSize; i++)
	{
		Vector2f vA = verticesB[i];
		Vector2f vB = verticesB[(i + 1) % bSize];

		Vector2f edge = vB - vA;

		Vector2f axis = Vector2f(-edge.y, edge.x).Normalized();
		//utils::SetColor(Color4f(0, 1, 0, 1));
		//utils::DrawLine(axis, 1);

		//utils::SetColor(Color4f(0, 1, 0, 1));
		//utils::DrawLine(axis * 1000, 2);
		//utils::DrawLine(-axis * 1000, 2);
		float minA, maxA, minB, maxB;
		ProjectVertices(verticesA, axis, minA, maxA);
		ProjectVertices(verticesB, axis, minB, maxB);

		bool hasGap = minA >= maxB || minB >= maxA;
		if (hasGap) return CollisionHitInfo(false, 0, Vector2f());

		float axisDepth = std::min(maxB - minA, maxA - minB);
		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}

	Vector2f centerA = FindArithmeticMean(verticesA);
	Vector2f centerB = FindArithmeticMean(verticesB);

	Vector2f dir = centerB - centerA;

	if (dir.DotProduct(normal) < 0.f)
	{
		normal *= -1;
	}

	return CollisionHitInfo(true, depth, normal);
}

Vector2f collisions::FindArithmeticMean(const std::vector<Vector2f> vertices)
{
	float sumX = 0.f;
	float sumY = 0.f;

	size_t vertexAmount = vertices.size();
	for (size_t i{ 0 }; i < vertexAmount; i++)
	{
		sumX += vertices[i].x;
		sumY += vertices[i].y;
	}

	return Vector2f(sumX / vertexAmount, sumY / vertexAmount);
}

void collisions::ProjectVertices(const std::vector<Vector2f>& vertices, Vector2f axis, float& min, float& max)
{
	min = FLT_MAX;
	max = -FLT_MAX;

	size_t vertexAmount = vertices.size();
	for (size_t i{ 0 }; i < vertexAmount; i++)
	{
		Vector2f v = vertices[i];
		float proj = v.DotProduct(axis);

		//utils::SetColor(Color4f(1, 0, 1, 1));
		//utils::DrawLine(vertices[i].ToPoint2f(), (axis * proj).ToPoint2f(), 2);
		//utils::DrawLine(vertices[i].ToPoint2f(), (axis * proj).ToPoint2f(), 2);

		if (proj < min) min = proj;
		if (proj > max) max = proj;
	}
}

bool collisions::IntersectLinePolygon(Vector2f p1, Vector2f p2, const std::vector<Vector2f>& vertices)
{
	if (IntersectPointPolygon(p1, vertices)) return true;

	// http://jeffreythompson.org/collision-detection/poly-line.php
	size_t vertexAmount = vertices.size();
	for (size_t i{ 0 }; i < vertexAmount; i++)
	{
		Vector2f vA = vertices[i];
		Vector2f vB = vertices[(i + 1) % vertexAmount];

		bool hit = IntersectLines(p1, p2, vA, vB);
		if (hit) return true;
	}

	return false;
}

bool collisions::IntersectLines(Vector2f p1, Vector2f p2, Vector2f p3, Vector2f p4)
{
	// http://jeffreythompson.org/collision-detection/line-line.php
	float uA = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
	float uB = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}
	return false;
}

bool collisions::IntersectPointPolygon(Vector2f p1, const std::vector<Vector2f>& vertices)
{
	// http://jeffreythompson.org/collision-detection/poly-point.php
	bool collision = false;

	size_t vertexAmount = vertices.size();
	for (size_t i{ 0 }; i < vertexAmount; i++)
	{
		Vector2f vCurrent = vertices[i];
		Vector2f vNext = vertices[(i + 1) % vertexAmount];

		// compare position, flip 'collision' variable back and forth
		if (((vCurrent.y >= p1.y && vNext.y < p1.y) || (vCurrent.y < p1.y && vNext.y >= p1.y)) &&
			(p1.x < (vNext.x - vCurrent.x) * (p1.y - vCurrent.y) / (vNext.y - vCurrent.y) + vCurrent.x)) {
			collision = !collision;
		}
	}

	return collision;
}
