#pragma once
#include <iostream>
#include <vector>

#include "Model.hpp"
#include "Parser.hpp"
#include "Renderer.hpp"

class Scene
{
public:
	Scene(Renderer* renderer, int width, int height);
	~Scene();

	void LoadMesh(std::string meshFileName);
	void Update();

	Model& GetModel();
	Mat4Scale& GetScaleMatrix() { return scaleMat; }

private:
	Renderer* renderer;
	Parser parser;
	Model model;
	Mat4Scale scaleMat;
	Mat4Projection projectionMat;

	int width, height;
	float aspect, fov, near, far;
};