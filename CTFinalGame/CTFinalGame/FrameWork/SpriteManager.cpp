﻿/*
	HOW TO USE:
	spritemanager is basic class to manage load and release sprite and texture.
	It load all image you have, if you want to use sprite any where, just getSprite from SpriteManager.
	if you dont want you use this image any more, you can call release.

	everytime use this, you have to call SpriteManager::getInstance() first.
	this is Singleton format.
	Seemore about Singleton: http://www.stdio.vn/articles/read/224/singleton-pattern

	you can call directly: SpriteManager::getInstance()->DOSOMETHING()
	or reference it:
		 	SpriteManager* _spritemanager;
			...
			_spritemanager = SpriteManager::getInstance();
			...
			_spritemanager->DOSOMETHING()

	Next, you should call loadresource(LPD3DXSPRITE spriteHandle) in Game::loadresource().
	It will load all your image from file to memory.
	Remember: Insert your code to loadresource to load image from file.

	If you want object reference to Sprite. call:
		SpriteManager::getInstance()->getSprite(eID::OBJECT_ID)
		what is eID::OBJECT_ID ?  
		in define.h you can insert element to eID.

	OK. Now you have sprite to draw.

	If you dont want to use this sprite any more, call releaseSprite or releaseTexture
	they often are called in object::release
		
	Call SpriteManager::release() in game:release() to clean all memory.
*/
#include "SpriteManager.h"
US_FRAMEWORK

SpriteManager* SpriteManager::_instance = nullptr;
SpriteManager::SpriteManager(void)
{
	// do nothing.
}

SpriteManager::~SpriteManager(void)
{
	for (auto spr = _listSprite.begin(); spr != _listSprite.end(); ++spr)
	{
		spr->second->release();		// release image
		delete spr->second;			// delete sprite
	}
	if (_listSprite.empty() == false)
		_listSprite.clear();		// remove all from MAP
}

void SpriteManager::loadResource(LPD3DXSPRITE spriteHandle)
{
	/* if you have any image, load them with this format */
	// [psedue code]
	// sp = new SPRITE(...)
	// this->_listSprite.insert(pair<eID, Sprite*>(eID::ENUMOBJECT, sp));

	Sprite* sp = NULL;
	sp = new Sprite(spriteHandle, L"Resource//Images//Soldier.png",10,10);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::SOLDIER, sp));
	this->loadSpriteInfo(eID::SOLDIER, "Resource//Images//soldier_animation.txt");

	sp = new Sprite(spriteHandle, L"Resource//Images//rifleman.png", 10, 10);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::RIFLEMAN, sp));
	this->loadSpriteInfo(eID::RIFLEMAN, "Resource//Images//rifleman_animation.txt");
	Sprite* bill = new Sprite(spriteHandle, L"Resource//Images//bill_animation.png");
	this->_listSprite[eID::BILL] = bill;
<<<<<<< HEAD
	this->loadSpriteInfo(eID::BILL, "Resource//Images//bill_animation.txt");
=======
	this->loadSpriteInfo(eID::BILL, "Resource//bill_animation.txt");

	//sp = new Sprite(spriteHandle, L"Resource//standing.png",1,1);
	//this->_listSprite.insert(pair<eID, Sprite*>(eID::BILL, sp));
	//RECT rexct
	//this->_sourceRectList[id][string(name)] = rect;
	//sp = new Sprite(spriteHandle, L"Resources//Images//Falcon.png");
	//this->_listSprite.insert(pair<eID, Sprite*>(eID::FALCON, sp));
	//this->loadSpriteInfo(eID::FALCON, "Resources//Images//falcon_animation.txt");

	sp = new Sprite(spriteHandle, L"Resource//Images//Cannon_all.png", 15, 5);
	//this->_listSprite.insert(pair<eID, Sprite*>(eID::REDCANON, sp));
	this->_listSprite[eID::REDCANNON] = sp;
	this->loadSpriteInfo(eID::REDCANNON, "Resource//Images//cannon_animation.txt");


>>>>>>> origin/master
	sp = new Sprite(spriteHandle, L"Resource//Images//wall_turret_all.png", 42, 9);
	this->_listSprite[eID::WALL_TURRET] = sp;
	this->loadSpriteInfo(eID::WALL_TURRET, "Resource//Images//Wall_turret_animation.txt");

	sp = new Sprite(spriteHandle, L"Resource//Images//explosion.png");
	this->_listSprite[eID::EXPLOSION] = sp;
	this->loadSpriteInfo(eID::EXPLOSION, "Resource//Images//explosion_animation.txt");
	sp = new Sprite(spriteHandle, L"Resource//Images//rifleman.png");
	this->_listSprite[eID::RIFLEMAN] = sp;
	this->loadSpriteInfo(eID::RIFLEMAN, "Resource//Images//rifleman_animation.txt");

	auto bl = new Sprite(spriteHandle, L"Resource//Images//Bullets.png");
	this->_listSprite[eID::BULLET] = bl;
	this->loadSpriteInfo(eID::BULLET, "Resource//Images//bullets_type.txt");

	sp = new Sprite(spriteHandle, L"Resource//Map//stage1.png", 120, 10);
	sp->setOrigin(VECTOR2ZERO);
	this->_listSprite[eID::MAP1] = sp;
}

Sprite* SpriteManager::getSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	
	return new Sprite(*it);			// get the copy version of Sprite
}

RECT SpriteManager::getSourceRect(eID id, string name)
{
	//return _sourceRectList[id].at(name);
	return _sourceRectList[id][name]; 
}



void SpriteManager::releaseSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	delete it;							// delete the sprite only, dont relase image
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
void SpriteManager::releaseTexture(eID id)
{
	Sprite *spr = this->_listSprite.find(id)->second;
	spr->release();						// release image
	delete spr;							
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
SpriteManager* SpriteManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteManager();
	return _instance;
}

void SpriteManager::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}
void SpriteManager::loadSpriteInfo(eID id, const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom);

			_sourceRectList[id][string(name)] = rect;
		}
	}

	fclose(file);
}
