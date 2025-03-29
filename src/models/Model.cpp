#include "Model.hpp"

Model::Model(ModelMesh mesh)
	:mesh(mesh), scale(1.0f), scaleFactor(0.05f),
	angleX(0.0f), angleY(0.0f), angleZ(0.0f), scaleMat(),
	posX(0.0f), posY(0.0f), posZ(0.0f), modelDepth(0.0f)
{
}

Model::~Model()
{
}

void Model::WorldToScreen(Mat4Projection& mat)
{
	screenPos.clear();
	Mat4Rotation rotMat;
	// (Mat4)translateMat should be here
	Mat4 modelMat = rotMat.MatrixRotation(angleX, angleY, angleZ) * scaleMat;
	
	for (auto& f : mesh.f) // Here i translate screen coordinates to move by screen x and y
	{
		Vec3 v1 = (Mat4)translateMat * (mat * (modelMat * f.v1));
		Vec3 v2 = (Mat4)translateMat * (mat * (modelMat * f.v2));
		Vec3 v3 = (Mat4)translateMat * (mat * (modelMat * f.v3));

		screenPos.emplace_back(Face(v1, v2, v3 ));
	}
	CalculateDepth();
}

void Model::Rotate(Mat4& rmat, float angleX, float angleY, float angleZ)
{
	return;
}

void Model::Scale(float scale)
{
	this->scale = scale;
	scaleMat.Update(scale, scale, scale);
}

void Model::Translate(float posX, float posY, float posZ)
{
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	translateMat.Update(posX, posY, posZ);
}

void Model::ToCenter(int centerX, int centerY)
{
	float modelCenterX = 0.0f;
	float modelCenterY = 0.0f;
	int count = 0;

	for (auto& f : screenPos)
	{
		modelCenterX += f.v1.x + f.v2.x + f.v3.x;
		modelCenterY += f.v1.y + f.v2.y + f.v3.y;
		count++;
	}

	if (count > 0)
	{
		modelCenterX /= count;
		modelCenterY /= count;
	}

	for (auto& f : screenPos)
	{
		f.v1.x = (f.v1.x - modelCenterX) * centerX + centerX;
		f.v1.y = centerY - (f.v1.y - modelCenterY) * centerY;
		f.v2.x = (f.v2.x - modelCenterX) * centerX + centerX;
		f.v2.y = centerY - (f.v2.y - modelCenterY) * centerY;
		f.v3.x = (f.v3.x - modelCenterX) * centerX + centerX;
		f.v3.y = centerY - (f.v3.y - modelCenterY) * centerY;
	}
	return; // TODO
}

void Model::CalculateDepth()
{
	float minZ = std::numeric_limits<float>::max();
	float maxZ = std::numeric_limits<float>::lowest();

	for (const auto& f : screenPos)
	{
		minZ = std::min({ minZ, f.v1.z, f.v2.z, f.v3.z });
		maxZ = std::max({ maxZ, f.v1.z, f.v2.z, f.v3.z });
	}

	this->modelDepth = maxZ - minZ;
}

const float Model::SetModelScale(float scale)
{
	this->scale = scale;
	return this->scale;
}

const void Model::SetModelAngles(float angleX, float angleY, float angleZ)
{
	this->angleX = angleX;
	this->angleY = angleY;
	this->angleZ = angleZ;
}

const void Model::SetModelPos(float posX, float posY, float posZ)
{
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
}
