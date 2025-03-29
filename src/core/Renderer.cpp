#include "Renderer.hpp"

Renderer::Renderer(int width, int height, float scale, int delay)
	: window(nullptr), renderer(nullptr), width(width), height(height),
	scale(scale), delay(delay), winBgColor(SDL_Color(43, 41, 51, 255))
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL_Init(SDL_INIT_VIDEO) error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	
	SDL_CreateWindowAndRenderer(
		"CubeSDL",
		width * scale,
		height * scale,
		0,
		&window, &renderer
	);

	if (!window || !renderer)
	{
		std::cerr << "SDL_CreateWindowAndRenderer error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_SetRenderScale(renderer, scale, scale);

	zBuffer.resize(width * height, std::numeric_limits<float>::max());
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::Clear()
{
	ClearZBuffer();
	SDL_SetRenderDrawColor(renderer, winBgColor.r, winBgColor.g, winBgColor.b, winBgColor.a);
	SDL_RenderClear(renderer);
}

void Renderer::ClearZBuffer()
{
	std::fill(zBuffer.begin(), zBuffer.end(), std::numeric_limits<float>::max());
}

void Renderer::Present()
{
	SDL_RenderPresent(renderer);
	if (delay > 0)
	{
		SDL_Delay(delay);
	}
}

void Renderer::DrawModel(const Model& model, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	std::vector<Face> faces = model.GetScreenPos();
	SortNormals(faces);

	for (const auto& face : faces)
	{
		Vec3 v1 = face.v1;
		Vec3 v2 = face.v2;
		Vec3 v3 = face.v3;

		float avgZ = (v1.z + v2.z + v3.z) / 3.0f;

		if (!isVisible(v1, v2, v3))
		{
			continue;
		}

		SDL_RenderLine(renderer, v1.x, v1.y, v2.x, v2.y);
		SDL_RenderLine(renderer, v2.x, v2.y, v3.x, v3.y);
		SDL_RenderLine(renderer, v3.x, v3.y, v1.x, v1.y);
	}
}

void Renderer::DrawGeometry(const Model& model, SDL_Color color)
{
	std::vector<SDL_Vertex> vertices{0};
	std::vector<Face> faces = model.GetScreenPos();

	float minZ = std::numeric_limits<float>::max();
	float maxZ = std::numeric_limits<float>::lowest();

	// Getting min and max Z
	for (auto& f : faces)
	{
		minZ = std::min({ minZ, f.v1.z, f.v2.z, f.v3.z });
		maxZ = std::max({ maxZ, f.v1.z, f.v2.z, f.v3.z });
	}

	// Sorting normals
	SortNormals(faces);

	// Actual rendering
	for (auto& f : faces)
	{
		float avgZ = (f.v1.z + f.v2.z + f.v3.z) / 3.0f;
		float normDepth = (avgZ - minZ) / (maxZ - minZ);

		float grayValue = (255.0f * (1.0f - normDepth));
		SDL_FColor adjColor = { grayValue / 255.0f, grayValue / 255.0f, grayValue / 255.0f, color.a };

		SDL_Vertex v1{ { f.v1.x, f.v1.y }, adjColor, { 0.0f, 0.0f } };
		SDL_Vertex v2{ { f.v2.x, f.v2.y }, adjColor, { 0.0f, 0.0f } };
		SDL_Vertex v3{ { f.v3.x, f.v3.y }, adjColor, { 0.0f, 0.0f } };
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
	}

	SDL_RenderGeometry(renderer, nullptr, vertices.data(), vertices.size(), 0, 0);
}

bool Renderer::isVisible(Vec3& v1, Vec3& v2, Vec3& v3) const
{
	float maxX = std::max({ v1.x, v2.x, v3.x });
	float minX = std::min({ v1.x, v2.x, v3.x });
	float maxY = std::max({ v1.y, v2.y, v3.y });
	float minY = std::min({ v1.y, v2.y, v3.y });

	bool onScreen = (maxX >= 0 && minX <= width && maxY >= 0 && minY <= height);

	return onScreen;
}

void Renderer::SortNormals(std::vector<Face>& faces)
{
	std::sort(faces.begin(), faces.end(), [](const Face& a, const Face& b) 
		{
		float avgZA = (a.v1.z + a.v2.z + a.v3.z) / 3.0f;
		float avgZB = (b.v1.z + b.v2.z + b.v3.z) / 3.0f;

		return avgZA > avgZB;
		}
	);
}
