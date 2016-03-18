
#include "character.h"
#include "base\global_definition.h"

Character::Character(char * defId)
	: Creature(defId)
{
	//_baseSprite = Sprite::create();
	//_baseSprite->retain();
	
	_totalDirectionCount = 16;

	_charDefinition = CharacterDefinition::load(defId);
	//_charAnimation = new CompositeAnimation(this);
	
	//_direction = 0; // By default is facing down
	//_action = CreatureAction::Action_KK;

	_head = NULL;
	_body = NULL;
	_shoe = NULL;
	_lefthand = NULL;
	_righthand = NULL;
}

Character::~Character()
{
	//_baseSprite->release();
	//// _charAnimation->release();
}

//
//void Character::sendToGround(Node *node, Point pos)
//{
//	_charAnimation->initialize();
//
//	this->_baseSprite->setPosition(pos);
//	node->addChild(this->_baseSprite);
//
//	this->refreshAnimation();
//}
//
//void Character::turnDirection(int dir)
//{
//	this->_direction = dir;
//	this->_charAnimation->updateFromCache();
//}
//
//void Character::setAction(CreatureAction action)
//{
//	this->_action = action;
//	this->_charAnimation->updateFromCache();
//}
//
//Sprite* Character::getBaseSprite()
//{
//	return _baseSprite;
//}

AnimationGenera Character::getGenera()
{
	return AnimationGenera::AnimationGenera_Character;
}

CharacterDefinition * Character::getDefinition()
{
	return this->_charDefinition;
}
//
//CreatureAction Character::getAction()
//{
//	return this->_action;
//}
//
//int Character::getDirection()
//{
//	return this->_direction;
//}

Equipment * Character::getEquipHead()
{
	return this->_head;
}

Equipment * Character::getEquipBody()
{
	return this->_body;
}

Equipment * Character::getEquipShoe()
{
	return this->_shoe;
}

Equipment * Character::getEquipLeftHand()
{
	return this->_lefthand;
}

Equipment * Character::getEquipRightHand()
{
	return this->_righthand;
}
//
//void Character::refreshAnimation()
//{
//	_charAnimation->refresh();
//}

CreatureDefinition Character::getCreatureDefinition()
{
	return CreatureDefinition::Creature_DU;
}
