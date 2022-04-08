#include "pch.h"
#include "collisions.h"
#include "utils.h"

bool collisions::PointRect(Vector2f p, Rectf rect)
{
	return p.x > rect.left && p.x < rect.left + rect.width && p.y > rect.bottom && p.y < rect.bottom + rect.height;
}

bool collisions::LineLine(Vector2f p1, Vector2f p2, Vector2f p3, Vector2f p4)
{
	float uA = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
	float uB = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}
	return false;
}

bool collisions::LineRect(Vector2f p1, Vector2f p2, Rectf rect)
{
	// Check if the line has hit any of the rectangle's sides
	bool left = LineLine(p1, p2, Vector2f(rect.left, rect.bottom), Vector2f(rect.left, rect.bottom + rect.height));
	bool right = LineLine(p1, p2, Vector2f(rect.left + rect.width, rect.bottom), Vector2f(rect.left + rect.width, rect.bottom + rect.height));
	bool top = LineLine(p1, p2, Vector2f(rect.left, rect.bottom + rect.height), Vector2f(rect.left + rect.width, rect.bottom + rect.height));
	bool bottom = LineLine(p1, p2, Vector2f(rect.left, rect.bottom), Vector2f(rect.left + rect.width, rect.bottom));

	// If any sides are colliding or p1 is in the rect already
	return (left || right || top || bottom) || PointRect(p1, rect);
}
