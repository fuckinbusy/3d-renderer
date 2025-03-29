#include "Scene.hpp"

Scene::Scene(Renderer* renderer, int width, int height)
	: width(width), height(height),
	fov(60.0f), near(0.1f), far(100.0f),
	aspect(static_cast<float>(width) / static_cast<float>(height)),
	renderer(renderer), parser(), projectionMat(), model(Model(ModelMesh()))
{
	projectionMat.Update(aspect, fov, near, far);
}

Scene::~Scene()
{
}

void Scene::LoadMesh(std::string meshFileName)
{
	ModelMesh mesh = parser.ParseFile(meshFileName);
	model = Model(mesh);
	std::cout << "Loaded mesh: " << meshFileName << std::endl;
}

void Scene::Update()
{
	// Clearing last frame
	renderer->Clear();

	// Projecting and rendering every model into the scene
	model.WorldToScreen(projectionMat);
	model.ToCenter(width / 2, height / 2);
	//renderer->DrawModel(model, { 255, 255, 255, 255 });
	renderer->DrawGeometry(model, { 255, 255, 255, 255 });

	// Presenting new frame
	renderer->Present();
}

Model& Scene::GetModel()
{
	return model;
}