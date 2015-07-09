#include "stdafx.h"
#include "ObjModel.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "Texture.h"
#include <string>
#include <stdio.h>
#include <sstream>
//#include "LogManager.h"
#include "AssetManager.h"

using namespace std;

std::string replace(std::string str, std::string toReplace, std::string replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

std::vector<std::string> split(std::string str, std::string sep)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(sep);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

ObjModel::ObjModel(std::string fileName)
{
	std::string dirName = fileName;
	if (dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if (dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if (fileName == dirName)
		dirName = "";

	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open()){
		printf("Impossible to open the file !\n");
	}

	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);

		line = replace(line, "\t", " ");
		while (line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");

		if (line == "")
			continue;
		if (line[0] == ' ')
			line = line.substr(1);
		if (line == "")
			continue;
		if (line[line.length() - 1] == ' ')
			line = line.substr(0, line.length() - 1);
		if (line == "")
			continue;
		if (line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "v")
			vertices.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vn")
			normals.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vt")
			texcoords.push_back(Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for (size_t i = ii - 3; i < ii; i++)	//magische forlus om van quads triangles te maken ;)
				{
					Vertex vertex;
					std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
					if (indices.size() >= 1)	//er is een positie
						vertex.position = atoi(indices[0].c_str()) - 1;
					if (indices.size() == 2)		//alleen texture
						vertex.texcoord = atoi(indices[1].c_str()) - 1;
					if (indices.size() == 3)		//v/t/n of t//n
					{
						if (indices[1] != "")
							vertex.texcoord = atoi(indices[1].c_str()) - 1;
						vertex.normal = atoi(indices[2].c_str()) - 1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if (params[0] == "s")
		{//smoothing
		}
		else if (params[0] == "mtllib")
		{
			loadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for (size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if (currentGroup->materialIndex == -1) {
				//std::stringstream ss;
				cout << "Could not find material name " << params[1] << endl;
				//LogManager::Instance().logError(ss.str());
			}
		}
	}
	groups.push_back(currentGroup);
}


ObjModel::~ObjModel(void)
{
	groups.clear();
}

void ObjModel::loadMaterialFile(std::string fileName, std::string dirName)
{
	std::ifstream pFile(fileName.c_str());
	MaterialInfo* currentMaterial = NULL;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);

		line = replace(line, "\t", " ");
		while (line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
		if (line == "")
			continue;
		if (line[0] == ' ')
			line = line.substr(1);
		if (line == "")
			continue;
		if (line[line.length() - 1] == ' ')
			line = line.substr(0, line.length() - 1);
		if (line == "")
			continue;
		if (line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "newmtl")
		{
			if (currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if (params[0] == "map_kd")
		{
			currentMaterial->hasTexture = true;

			currentMaterial->texture = AssetManager::Instance().getTexture(dirName + "/" + params[1]);
		}
		else if (params[0] == "illum") {
			currentMaterial->illum = stoi(params[1]);
		}
		else if (params[0] == "kd"){
			currentMaterial->diffuseColor[0] = stof(params[1]);
			currentMaterial->diffuseColor[1] = stof(params[2]);
			currentMaterial->diffuseColor[2] = stof(params[3]);
		}
		else if (params[0] == "ka"){
			currentMaterial->ambientColor[0] = stof(params[1]);
			currentMaterial->ambientColor[1] = stof(params[2]);
			currentMaterial->ambientColor[2] = stof(params[3]);
		}
		else if (params[0] == "tf"){
			currentMaterial->transmissionFilter[0] = stof(params[1]);
			currentMaterial->transmissionFilter[1] = stof(params[2]);
			currentMaterial->transmissionFilter[2] = stof(params[3]);
		}
		else{

			if (_debug) {
				//std::stringstream ss;
				cout << "Didn't parse " << params[0] << " in material file " << endl;
				//LogManager::Instance().logDebug(ss.str());
			}
		}
	}
	if (currentMaterial != NULL)
		materials.push_back(currentMaterial);

}

ObjModel::MaterialInfo::MaterialInfo()
{
	hasTexture = false;
}


Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3f::Vec3f(Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}

Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}

Vec2f::Vec2f(Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}

void ObjModel::draw()
{
	glNormal3f(0, 0, 1);
	for (ObjGroup *group : groups){

		bool drawTexture = false;
		MaterialInfo *material = materials[group->materialIndex];
		if (material->texture != NULL) {
			drawTexture = true;
			material->texture->enableTexture();
		}

		glBegin(GL_TRIANGLES);

		//Materiaal zetten.
		for (const Face &face : group->faces){
			// voor iedere face de vertice:
			for (const Vertex &vertice : face.vertices){

				if (drawTexture)
					glTexCoord2f(texcoords.at(vertice.texcoord).x, texcoords.at(vertice.texcoord).y);

				glVertex3f(vertices[vertice.position].x, vertices[vertice.position].y, vertices[vertice.position].z);
			}
		}
		glEnd();

		if (drawTexture)
			material->texture->disableTexture();
	}

}