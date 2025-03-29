#pragma once
#include <iostream>
#include <algorithm>
#include "SDL3/SDL.h"
#include "Model.hpp"

#define RENDERER_DELAY_DEFAULT 16

enum DrawType
{
	DRAW_SOLID,
	DRAW_WIREFRAME
};

class Renderer
{
public:
	Renderer(int width, int height, float scale, int delay);
	~Renderer();

	void Present();
	void Clear();
	void ClearZBuffer();
	void DrawModel(const Model& model, SDL_Color color);
	void DrawGeometry(const Model& model, SDL_Color color);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Color winBgColor;
	std::vector<float> zBuffer;
	int width, height, delay;
	float scale;

	bool isVisible(Vec3& v1, Vec3& v2, Vec3& v3) const;
	void SortNormals(std::vector<Face>& faces);
};

