#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "creature.h"
#include "ui\animation\composite_animation_renderer.h"
#include "definition\character_definition.h"
#include "equipment.h"

class Character : public Creature
{

private:

	CharacterDefinition * _charDefinition;
	//CompositeAnimation * _charAnimation;

	//Sprite * _baseSprite;

	//CreatureAction _action;
	//int _direction;

	Equipment * _head;
	Equipment * _body;
	Equipment * _shoe;
	Equipment * _lefthand;
	Equipment * _righthand;

	///Point _positionInPixel;

public:

	Character(char * defId);
	virtual ~Character();

	CreatureDefinition getCreatureDefinition();
	CharacterDefinition * getDefinition();

	AnimationGenera getGenera();

	//Sprite* getBaseSprite();

	// void sendToGround(Node *node, Point pos);

	//void setAction(CreatureAction action);
	//void turnDirection(int direction);

	//CreatureAction getAction();
	//int getDirection();

	Equipment * getEquipHead();
	Equipment * getEquipBody();
	Equipment * getEquipShoe();
	Equipment * getEquipLeftHand();
	Equipment * getEquipRightHand();

	// Animation
	//void refreshAnimation();

	// AnimationAction getAnimationAction();

};

#endif