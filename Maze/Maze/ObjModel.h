#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include <string>
#include <vector>
#include <list>

#include <Windows.h>
#include <GL\GL.h>

#include "Texture.h"

class Vec3f
{
public:
	union
	{
		struct{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(Vec3f &other);
	Vec3f(float, float, float);
	float& operator [](int);
};

class Vec2f
{
public:
	union
	{
		struct{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float, float);
	Vec2f(Vec2f &other);
	float& operator [](int);
};

class ObjModel
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		bool hasTexture;
		Texture *texture = NULL;
		int illum;
		float diffuseColor[3];
		float ambientColor[3];
		float transmissionFilter[3];
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
	};
	std::vector<::Vec3f> vertices;
	std::vector<::Vec3f> normals;
	std::vector<::Vec2f> texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;
	bool _debug = false;
	void loadMaterialFile(std::string filename, std::string dirname);

public:
	ObjModel(std::string filename);
	~ObjModel(void);

	void draw();
};
#endif