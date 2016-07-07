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

	int sizeUBYTE = sizeof(UBYTE);
	int sizeDS_WORD = sizeof(DS_WORD);
	int sizeUWORD = sizeof(UWORD);
	int sizeUDWORD = sizeof(UDWORD);


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

	//// character = new Character("SO");
	//// scene->addPlayer(character);

	//// defaultPalette = Palette::loadForAct(2);
	registerMouseEvents();
	schedule(CC_SCHEDULE_SELECTOR(MainGameLayer::gameTick), 0.06f);

	

	return true;
}

void MainGameLayer::gameTick(float dt)
{
	scene->mainTick(dt);

}

void MainGameLayer::loadRealPlayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 middleScreen = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	
	AnimationLibrary::getInstance()->loadResources();

	Character* character = new Character("SO");
	scene->addPlayer(character);
}

void MainGameLayer::loadStage(int stageId, int indexId)
{
	///SpriteFrame* ss = SpriteFrame::create("100_100_2.png", Rect(0, 0, 100, 100));
	///ss->setOffsetInPixels(Vec2(50, 50));


	///map = Sprite::createWithSpriteFrame(ss);
	
	DefinitionLibrary::getInstance()->loadResources();
	AnimationLibrary::getInstance()->loadResources();
	
	scene = AnimationLibrary::getInstance()->retrieveScene(stageId, indexId);

	map = scene->generateMap();
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(800, 2000);
	this->addChild(map);
	controlTarget = map;

	/*
	// Show Scene

	int unitWidth = 160;
	int unitHeight = 80;
	
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
	*/
	// map->setScale(0.3f);
	
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
		map->setPositionX(map->getPositionX() - 50);
		break;
	default:
		break;

	}
}

void MainGameLayer::registerMouseEvents()
{
	//  Create a "one by one" touch event listener
	// (processes one touch at a time)
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainGameLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainGameLayer::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainGameLayer::onTouchMoved, this);

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool MainGameLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* even)
{
	log("onTouchBegan");
	character->changeToAction(AnimationAction::Animation_RN);

	auto target = static_cast<Sprite*>(even->getCurrentTarget());
	Point p = touch->getLocation();
	log("%f, %f", p.x, p.y);

	if (isTouchInGameActiveArea(p))
	{
		Vec2 mapPoint = convertScreenPointToMapPoint(p);
		scene->onClickOnPoint(mapPoint);
	}

	////character->turnDirection(p.x - 100, p.y - 100);
	return true;
}
void MainGameLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* even)
{
	//// character->changeToAction(AnimationAction::Animation_NU);

}
void MainGameLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* even)
{
	auto target = static_cast<Sprite*>(even->getCurrentTarget());
	Point p = touch->getLocation();
	//log("%f, %f", p.x, p.y);

	//// character->turnDirection(p.x - 100, p.y - 100);
	if (isTouchInGameActiveArea(p))
	{
		Vec2 mapPoint = convertScreenPointToMapPoint(p);
		scene->onClickOnPoint(mapPoint);
	}
}

Vec2 MainGameLayer::convertScreenPointToMapPoint(Vec2 point)
{
	return Vec2(point.x - map->getPosition().x, point.y - map->getPosition().y);
}

bool MainGameLayer::isTouchInGameActiveArea(Vec2 point)
{
	return true;
}