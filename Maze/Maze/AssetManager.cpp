#include "stdafx.h"
#include "AssetManager.h"
//#include "Animation.h"
//#include "LogManager.h"
#include <iostream>
#include <thread>

using namespace std;

AssetManager::AssetManager(){}

void AssetManager::loadAnimation(std::string resource, int index, int frames)
{
	//Animation *an = new Animation(resource, 50);
	//_animations[index] = an;
}

void AssetManager::loadInBackground()
{
	_mutex.lock();

	_bThread[1] = std::thread(&AssetManager::loadAnimation, this, "../res/Enemy/MiniKnightAnimation/mini_knight", 0, 50);
	_bThread[2] = std::thread(&AssetManager::loadAnimation, this, "../res/Enemy/MiniKnightAnimationEnemy/mini_knight", 2, 50);
	_bThread[3] = std::thread(&AssetManager::loadAnimation, this, "../res/Ally/archer/archer", 1, 50);
	_bThread[4] = std::thread(&AssetManager::loadAnimation, this, "../res/Enemy/MiniArcherAnimationEnemy/mini_knight", 3, 50);

	_bThread[1].join();
	_bThread[2].join();
	_bThread[3].join();
	_bThread[4].join();
	_working = false;
	_mutex.unlock();
}

void AssetManager::loadAssets()
{
	_bThread[0] = std::thread(&AssetManager::loadInBackground, this);

	allyKnight.isAlly = true;
	allyKnight.hp = 250;
	allyKnight.power = 15;

	enemyKnight.isAlly = false;
	enemyKnight.hp = 100;
	enemyKnight.power = 10;

	allyArcher.isAlly = true;
	allyArcher.hp = 30;
	allyArcher.power = 1;

	enemyArcher.isAlly = false;
	enemyArcher.hp = 250;
	enemyArcher.power = 5;
}

void AssetManager::lockWhileLoading()
{
	while (_working)
		Sleep(10);

	return;
}
//
//Animation* AssetManager::getAnimation(int type)
//{
//	Animation* result = NULL;
//	_mutex.lock();
//	result = _animations[type];
//	_mutex.unlock();
//	return result;
//}

Texture* AssetManager::getTexture(std::string name)
{
	Texture* result = NULL;
	bool textureExists = false;

	for (int i = 0; i < _textures.size(); i++){
		if (_textures[i].first == name) {
			textureExists = true;
			result = _textures[i].second;

			if (_debug)
				//LogManager::Instance().logDebug("AssetManager: Texture already loaded returning pointer.");
				cout << "AssetManager: Texture already loaded returning pointer." << endl;
		}
	}

	/* Als texture nog niet ingeladen is laadt hem in*/
	if (!textureExists){
		result = new Texture(name);

		std::pair<std::string, Texture*> texturePair(name, result);
		_textures.push_back(texturePair);

		if (_debug)
			//LogManager::Instance().logDebug("AssetManager:: Loaded new texture");
			cout << "AssetManager:: Loaded new texture" << endl;
	}
	return result;
}