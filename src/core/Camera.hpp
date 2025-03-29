#pragma once
#include "Vector.hpp"
class Camera
{
public:
	Camera();
	~Camera();

	void LookAt();
private:
	Vec3 pos;
	Vec3 target;
	Vec3 up;
};
// TODO

