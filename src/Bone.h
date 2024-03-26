#pragma once
#include <vector>
#include <string>

#include "Quaternion.h"

class Bone {
	std::string name;
	std::string ParentName;

	Bone* Parent;
	
};