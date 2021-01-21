#pragma once

//#include "Component.h"

class GameObject;

class Transform// : public Component
{
public:
	Transform();
	~Transform();

	void Update();
	float* GetTransform();

public:
	float positionX, positionY, positionZ;
	float scaleX, scaleY;
	float angle;

private:
	glm::mat4 Rotate(const int i, const float theta);
	glm::mat4 Scale(const float x, const float y, const float z);
	glm::mat4 Translate(const float x, const float y, const float z);
private:
	glm::mat4 transformationMatrix;

};