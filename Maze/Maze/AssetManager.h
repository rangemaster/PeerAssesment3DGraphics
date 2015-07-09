#ifndef ASSET_MANAGER_H 
#define ASSET_MANAGER_H 

//#include "Animation.h"
#include "ObjModel.h"
#include "Texture.h"
#include <string>
#include <mutex>
#include <thread>
#define ENEMYKNIGHTMODEL "../res/Enemy/MiniKnightAnimation/mini_knight"
#define ALLYKNIGHTMODEL "../res/Enemy/MiniKnightAnimation/mini_knight"
#define ENEMYARCHERMODEL "../res/Enemy/MiniKnightAnimation/mini_knight"
#define ALLYARCHERMODEL "../res/Enemy/MiniKnightAnimation/mini_knight"
typedef struct unit
{
	bool isAlly;
	int hp;
	int power;
};

class AssetManager
{
private:
	//Animation* _animations[10];
	std::vector<std::pair<std::string, Texture*>> _textures;
	bool _debug = false;
	void loadInBackground();
	std::mutex _mutex;
	std::thread _bThread[10];
	void loadAnimation(std::string resource, int index, int frames);
	bool _working = true;
public:
	unit allyKnight, enemyKnight, allyArcher, enemyArcher;
	static AssetManager& Instance()
	{
		static AssetManager _instance;
		return _instance;
	}
	AssetManager();
	void loadAssets();
	//Animation* getAnimation(int type);
	Texture* getTexture(std::string name);
	void lockWhileLoading();
};

#endif