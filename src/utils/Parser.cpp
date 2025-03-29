#include "Parser.hpp"

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::PrintModel(ModelMesh& mesh)
{
	if (mesh.f.empty()) return;

	std::cout << "Model\n";
	for (int i = 0; i < mesh.f.size(); i++)
	{
		std::cout << "Face f" << i + 1 << ": \n";
		std::cout << "	v1: "
			<< mesh.f[i].v1.x << " | "
			<< mesh.f[i].v1.y << " | "
			<< mesh.f[i].v1.z << "\n";
		std::cout << "	v2: "
			<< mesh.f[i].v2.x << " | "
			<< mesh.f[i].v2.y << " | "
			<< mesh.f[i].v2.z << "\n";
		std::cout << "	v3: "
			<< mesh.f[i].v3.x << " | "
			<< mesh.f[i].v3.y << " | "
			<< mesh.f[i].v3.z << "\n";
	}
	std::cout << std::endl;
}

ModelMesh Parser::ParseFile(const std::string& fileName)
{
	if (fileName.empty())
	{
		std::cerr << "Please provide correct file name." << std::endl;
		exit(-1);
	}

	std::ifstream file(fileName, std::ios::in);
	std::string line;

	if (!file.is_open())
	{
		std::cerr << "Failed to open file." << std::endl;
		exit(-1);
	}

	ModelMesh mesh{};

	std::cout << "Parsing file: " << fileName << std::endl;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "v")
		{
			//std::cout << "Parsing vertices: " << line << "\n";
			Vec3 v{};
			iss >> v.x >> v.y >> v.z;
			//printf("%f %f %f\n", v.x, v.y, v.z);
			mesh.v.push_back(v);
		}
		else if (type == "f")
		{
			//std::cout << "Parsing faces: " << line << "\n";
			Face f{};
			int v1, v2, v3;
			std::string token;

			iss >> token;
			std::istringstream(token) >> v1;
			iss >> token;
			std::istringstream(token) >> v2;
			iss >> token;
			std::istringstream(token) >> v3;

			f.v1 = mesh.v[v1 - 1];
			f.v2 = mesh.v[v2 - 1];
			f.v3 = mesh.v[v3 - 1];

			mesh.f.push_back(f);
		}
	}

	std::cout << "Parsing finished" << std::endl;
	file.close();
	return mesh;
}
