#pragma once
#include "Vector2f.h"

namespace collisions
{
	bool PointRect(Vector2f p, Rectf rect);
	bool LineLine(Vector2f p1, Vector2f p2, Vector2f p3, Vector2f p4);
	bool LineRect(Vector2f p1, Vector2f p2, Rectf rect);
}