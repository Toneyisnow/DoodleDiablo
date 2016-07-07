#include "composite_object.h"
#include "ui\animation\composite_animation_renderer.h"

CompositeObject::CompositeObject()
	: CompositeObject("")
{
}

CompositeObject::CompositeObject(const char * token)
{
	_token = token;
	_direction = Vec2(1, 0);
	_action = AnimationAction::Animation_NU;
	_compositeAnimationRenderer = new CompositeAnimationRenderer(this);
	_calculatedSpeed = 5;

	this->_baseSprite = Sprite::create();
	this->_baseSprite->setAnchorPoint(Vec2(0, 0));

	Sprite* indicator = Sprite::create("Point.png");
	this->_baseSprite->addChild(indicator, 500);

	this->_shadowSprite = Sprite::create();
	this->_shadowSprite->setAnchorPoint(Vec2(0, 0));
	this->_sketchSprite = Sprite::create();
	this->_sketchSprite->setAnchorPoint(Vec2(0, 0));
}

CompositeObject::~CompositeObject()
{
	_compositeAnimationRenderer->release();
}

AnimationAction CompositeObject::parseAnimationAction(const char * actionString)
{
	for (int i = 0; i < AnimationActionCount; i++)
	{
		if (strcmp(actionString, AnimationActionStrings[i]) == 0)
		{
			return (AnimationAction)i;
		}
	}

	return AnimationAction::Animation_NU;
}

const char* CompositeObject::getToken() const
{
	return _token;
}

Vec2 CompositeObject::getDirection()
{
	return _direction;
}

Vec2 CompositeObject::getPosition()
{
	return _baseSprite->getPosition();
}

Sprite* CompositeObject::getBaseSprite()
{
	return _baseSprite;
}

Sprite* CompositeObject::getShadowSprite()
{
	return _shadowSprite;
}
Sprite* CompositeObject::getSketchSprite()
{
	return _sketchSprite;
}

void CompositeObject::sendToGround(Node *node, Point pos)
{
	_compositeAnimationRenderer->initialize();

	this->_baseSprite->setPosition(pos);
	this->_sketchSprite->setPosition(pos);
	this->_shadowSprite->setPosition(pos);

	node->addChild(this->_shadowSprite, 290);
	node->addChild(this->_sketchSprite, 290);
	node->addChild(this->_baseSprite, 300);

	_compositeAnimationRenderer->reload();
	
}

void CompositeObject::deem(int val)
{
	this->_baseSprite->setOpacity(val);
}

int getAmbisexualent()
{
	return 100;
}

int getLuminance()
{
	return 100;
}


void CompositeObject::removeFromGround()
{
	this->_baseSprite->removeFromParent();
}

void CompositeObject::changeToAction(AnimationAction action)
{
	this->_action = action;
	_compositeAnimationRenderer->reload();
}

void CompositeObject::turnDirection(int direction)
{
	//this->_direction = direction;
	//_compositeAnimationLoader->reload();
}

void CompositeObject::turnDirection(int dx, int dy)
{
	float dir = sqrt(dx * dx + dy * dy);
	this->_direction = Vec2(dx / dir, dy / dir);

	_compositeAnimationRenderer->updateDirection();
}

AnimationAction CompositeObject::getAnimationAction()
{
	return _action;
}
AnimationFigure CompositeObject::getFigure()
{
	return AnimationFigure::_HTH;
}

AnimationLevelHD CompositeObject::getHDLevel()
{
	return AnimationLevelHD::AnimationLevelHD_LIT;
}
AnimationLevelBody CompositeObject::getBodyLevel()
{
	return AnimationLevelBody::AnimationLevelBody_LIT;
}
AnimationLevelRH CompositeObject::getRHLevel()
{
	return AnimationLevelRH::AnimationLevelRH_GSD;
}
AnimationLevelLH CompositeObject::getLHLevel()
{
	return AnimationLevelLH::AnimationLevelLH_BSD;
}
AnimationLevelSH CompositeObject::getSHLevel()
{
	return AnimationLevelSH::AnimationLevelSH_BSH;
}

AnimationGenera CompositeObject::getGenera()
{
	// This should be overridden by sub class
	return AnimationGenera::AnimationGenera_Object;
}

void CompositeObject::mainTick(float delta)
{
	if (_action == AnimationAction::Animation_RN)
	{
		float dx = _calculatedSpeed * _direction.x;
		float dy = _calculatedSpeed * _direction.y;

		Point pos = this->_baseSprite->getPosition();
		this->_baseSprite->setPosition(pos.x + dx, pos.y + dy);
		this->_sketchSprite->setPosition(pos.x + dx, pos.y + dy);
		this->_shadowSprite->setPosition(pos.x + dx, pos.y + dy);
	}
}