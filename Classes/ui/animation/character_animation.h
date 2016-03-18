#ifndef _CHARACTER_ANIMATION_H_
#define _CHARACTER_ANIMATION_H_

#include <cocos2d.h>
#include "composite_animation_config.h"

USING_NS_CC;

class Character;

class CompositeAnimationConfig2 : public Ref
{
private:

	int _layerCount;
	int _frameCount;
	int _directionCount;
	float _speed;

	int _zOrder[32][32][16];

public:

	CompositeAnimationConfig2();
	~CompositeAnimationConfig2();

	void initFromFile(const char * filename);

	int* getLayerZOrders(int direction, int frame);
	int getFrameCount();

};


class CharacterAnimation : public Ref
{

private:

	Character * _character;
	Sprite * _head;
	Sprite * _body;
	Sprite * _leg;
	Sprite * _leftarm;
	Sprite * _rightarm;
	Sprite * _lefthand;
	Sprite * _righthand;
	Sprite * _shield;
	Sprite * _special1;
	Sprite * _special2;

	Sprite * newComponentSprite();
	TargetedAction* refreshComponentAnimation(Sprite *obj, const char * component, const char * figure, const char * action, const char * level);

	CompositeAnimationConfig * _animationConfig;

	int _currentFrameCount;

public:

	// static CharacterAnimation* create(const Character * character);
	CharacterAnimation(Character * character);
	~CharacterAnimation();

	void initialize();

	/// Refresh the current animation according to character's status/direction/equipment/gesture
	void refresh();

	char * getFigureString();	// HTH, 1HS, 1HT, 2HS, 2HT, ...
	char * getActionString();

	char * getHDEquipLevel();
	char * getTREquipLevel();
	char * getLGEquipLevel();
	char * getLAEquipLevel();
	char * getRAEquipLevel();
	char * getLHEquipLevel();
	char * getRHEquipLevel();
	char * getSHEquipLevel();
	char * getS1EquipLevel();
	char * getS2EquipLevel();

	void callback_0();

};



#endif