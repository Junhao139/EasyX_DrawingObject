#pragma once

#include <chrono>

enum OBJ_TYPES { Obj_Object };
struct ObjectProps {
	int TYPE;
	std::chrono::time_point<std::chrono::steady_clock> startPoint;
	bool Valid;
	void* Obj;
	void* next;
};