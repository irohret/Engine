#pragma once
#include <vector>
#include <string>

#include "../math/Quaternion.h"

class Bone {
	std::string name;
	std::string ParentName;

	Bone* Parent;
	
};