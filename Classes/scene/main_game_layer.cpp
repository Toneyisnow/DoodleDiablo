#include "main_game_layer.h"


#include "cocostudio\CocoStudio.h"
#include "ui\tilemap\ds_scene.h"
#include "ui\object\character.h"
#include "ui\object\monster.h"
#include "ui\object\static_object.h"
#include "ui\animation\animation_library.h"
#include "definition\data_definition.h"
#include "definition\definition_library.h"

using namespace DoodleDiablo::Scenes;




bool MainGameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log(origin.x);
	log(origin.y);

	auto b1 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGameLayer::b1Callback, this));
	b1->setPosition(Vec2(50, 100));

	auto b2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGameLayer::b2Callback, this));
	b2->setPosition(Vec2(100, 150));

	auto b3 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGameLayer::b3Callback, this));
	b3->setPosition(Vec2(100, 50));

	auto b4 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGameLayer::b4Callback, this));
	b4->setPosition(Vec2(150, 100));

	auto b5 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGameLayer::b5Callback, this));
	b5->setPosition(Vec2(250, 100));




	// create menu, it's an autorelease object
	auto menu = Menu::create(b1, b2, b3, b4, b5, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	
	// position the sprite on the center of the screen
	Vec2 middleScreen = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	Vec2 middleDown = Vec2(visibleSize.width / 2 + origin.x, 100);


	loadStage(1, 2);


	//// defaultPalette = Palette::loadForAct(2);

	

	return true;
}

void MainGameLayer::loadStage(int stageId, int indexId)
{
	///SpriteFrame* ss = SpriteFrame::create("100_100_2.png", Rect(0, 0, 100, 100));
	///ss->setOffsetInPixels(Vec2(50, 50));


	///map = Sprite::createWithSpriteFrame(ss);
	map = Sprite::create();
	map->setAnchorPoint(Vec2(0, 0));
	this->addChild(map, 0);


	DefinitionLibrary::getInstance()->loadResources();
	DsScene * scene = AnimationLibrary::getInstance()->retrieveScene(stageId, indexId);

	// Show Scene

	int unitWidth = 160;
	int unitHeight = 80;
	int baseX = 800;
	int baseY = 2000;

	map = Sprite::create();
	log("Scene Map:");
	Size size = scene->getSize();
	for (int j = 0; j < size.height; j++)
	{
		for (int i = 0; i < size.width; i++)
		{
			Sprite* s = scene->generateSprite(i, j);
			if (s == NULL)
				continue;

			int jj = j + 1;
			int posX = (i - j) * unitWidth / 2;
			int posY = -(i + j) * unitHeight / 2;

			s->setPosition(Vec2(posX, posY));
			map->addChild(s, 100);
		}
	}

	// map->setScale(0.3f);


	this->addChild(map);
	map->setPosition(baseX, baseY);
	controlTarget = map;

}

void MainGameLayer::b1Callback(Ref* pSender)
{
	moveMap(1);
}

void MainGameLayer::b2Callback(Ref* pSender)
{
	moveMap(2);

}

void MainGameLayer::b3Callback(Ref* pSender)
{
	moveMap(3);

}

void MainGameLayer::b4Callback(Ref* pSender)
{
	moveMap(4);


}

void MainGameLayer::b5Callback(Ref* pSender)
{
	/// character->changeToAction(AnimationAction::Animation_NU);


}


void MainGameLayer::moveMap(int direction)
{
	if (map == NULL)
	{
		return;
	}

	switch (direction)
	{
	case 1:
		map->setPositionX(map->getPositionX() + 50);
		break;
	case 2:
		map->setPositionY(map->getPositionY() - 50);
		break;
	case 3:
		map->setPositionY(map->getPositionY() + 50);
		break;
	case 4:
		map->setPositionY(map->getPositionX() - 50);
		break;
	default:
		break;

	}
}
