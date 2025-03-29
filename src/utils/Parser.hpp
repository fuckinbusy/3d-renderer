#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Model.hpp"

class Parser
{
public:
	Parser();
	~Parser();

	void PrintModel(ModelMesh& model);
	ModelMesh ParseFile(const std::string& fileName);

private:
};