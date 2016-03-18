
#include "scene_builder.h"
#include "main_game_layer.h"

using namespace DoodleDiablo::Scenes;

Scene* SceneBuilder::buildTestScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGameLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}



