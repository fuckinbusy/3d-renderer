#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "SDL3/SDL.h"
#include "Vector.hpp"
#include "Matrix.hpp"

struct Face
{
	Vec3 v1, v2, v3;
};

struct ModelMesh
{
	std::vector<Face> f;
	std::vector<Vec3> v;
};

class Model
{
public:
	Model(ModelMesh mesh);
	~Model();

	void WorldToScreen(Mat4Projection& mat);
	void Rotate(Mat4& rmat, float angleX, float angleY, float angleZ);
	void Scale(float scale);
	void Translate(float posX, float posY, float posZ);
	void ToCenter(int centerX, int centerY);
	void CalculateDepth();
	Vec3 ComputeNormal(const Face& face);

	const float GetModelScale() const { return scale; }
	const std::vector<Vec3>& GetVertices() const { return mesh.v; }
	const std::vector<Face>& GetFaces() const { return mesh.f; }
	const std::vector<Face>& GetScreenPos() const { return screenPos; }
	const ModelMesh& GetMesh() { return mesh; }
	const int GetVerticesAmt() const { return mesh.v.size(); }
	const int GetFacesAmt() const { return mesh.f.size(); }
	const float GetScaleFactor() const { return scaleFactor; }
	const float GetAngleX() const { return angleX; }
	const float GetAngleY() const { return angleY; }
	const float GetAngleZ() const { return angleZ; }
	const float GetPosX() const { return posX; }
	const float GetPosY() const { return posY; }
	const float GetPosZ() const { return posZ; }
	const float GetModelDepth() const { return modelDepth; }
	Mat4Translate& GetTranslationMatrix() { return translateMat; }
	Mat4Scale& GetScaleMatrix() { return scaleMat; }

	const float SetModelScale(float scale);
	const void SetModelAngles(float angleX, float angleY, float angleZ);
	const void SetModelPos(float posX, float posY, float posZ);

private:
	ModelMesh mesh;
	std::vector<Face> screenPos;

	Mat4Scale scaleMat;
	Mat4Translate translateMat;

	float scale, scaleFactor;
	float angleX, angleY, angleZ;
	float posX, posY, posZ;
	float modelDepth;
};

