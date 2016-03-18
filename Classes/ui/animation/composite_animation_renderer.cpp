#include "composite_animation_renderer.h"
#include "composite_animation.h"
#include "ui\object\composite_object.h"
#include "animation_library.h"

CompositeAnimationRenderer::CompositeAnimationRenderer(CompositeObject * obj)
{
	_object = obj;
	//_animationList = new Map<std::string, CompositeAnimation*>();
}

CompositeAnimationRenderer::~CompositeAnimationRenderer()
{
	if (_current != NULL)
	{
		_current->myreferenceCount--;
	}

	AnimationLibrary::getInstance()->recycle();

	//_animationList->clear();
	//delete(_animationList);
}

void CompositeAnimationRenderer::initialize()
{
	_lastDirection = -1;
	_current = NULL;
	_directionCount = 0;
}

void CompositeAnimationRenderer::reload()
{
	if (_object->getToken() == NULL)
	{
		return;
	}

	bool needUpdate = false;

	CompositeAnimationId* comId = CompositeAnimationId::create(_object->getGenera(), (char*)_object->getToken(), _object->getAnimationAction(), _object->getFigure());

	AnimationLevelHD hd = _object->getHDLevel();
	AnimationLevelBody body = _object->getBodyLevel();
	AnimationLevelRH rh = _object->getRHLevel();
	AnimationLevelLH lh = _object->getLHLevel();
	AnimationLevelSH sh = _object->getSHLevel();

	AnimationLibrary * library = AnimationLibrary::getInstance();
	CompositeAnimation* animation = library->retrieveCompositeAnimation(comId, hd, body, rh, lh, sh);
	Palette *pal = library->retrievePalette(1);
	if (animation == _current)
	{
		return;
	}
	
	_current = animation;
	animation->render(pal);

	this->_baseAnimates.clear();
	this->_sketchAnimates.clear();
	this->_shadowAnimates.clear();
	_directionCount = animation->getDirectionCount();

	for (int i = 0; i < _directionCount; i++)
	{
		Animation* ani = animation->getAnimation(i);
		RepeatForever* repeat = RepeatForever::create(Animate::create(ani));
		repeat->setTag(COMPOSITE_ANIMATION_TAG);
		this->_baseAnimates.pushBack(repeat);

		Animation* aniSketch = animation->getShadowAnimation(i);
		RepeatForever* repeatSketch = RepeatForever::create(Animate::create(aniSketch));
		repeatSketch->setTag(COMPOSITE_ANIMATION_TAG);
		this->_sketchAnimates.pushBack(repeatSketch);

		Animation* aniShadow = animation->getSketchAnimation(i);
		RepeatForever* repeatShadow = RepeatForever::create(Animate::create(aniShadow));
		repeatShadow->setTag(COMPOSITE_ANIMATION_TAG);
		this->_shadowAnimates.pushBack(repeatShadow);
	}

	_lastDirection = _current->calculateDirection(_object->getDirection());
	this->forceRefresh();
}

void CompositeAnimationRenderer::updateDirection()
{
	if (_current == NULL)
	{
		return;
	}

	int dir = _current->calculateDirection(_object->getDirection());
	if (dir == _lastDirection)
	{
		// Nothing to do here
		return;
	}

	_lastDirection = dir;
	forceRefresh();
}

void CompositeAnimationRenderer::forceRefresh()
{
	if (_lastDirection < 0 || _lastDirection >= _directionCount)
	{
		return;
	}

	_object->getBaseSprite()->stopActionByTag(COMPOSITE_ANIMATION_TAG);
	_object->getSketchSprite()->stopActionByTag(COMPOSITE_ANIMATION_TAG);
	_object->getShadowSprite()->stopActionByTag(COMPOSITE_ANIMATION_TAG);

	/*
	if (_object->getBaseSprite()->getActionByTag(COMPOSITE_ANIMATION_TAG) != NULL)
		_object->getBaseSprite()->stopActionByTag(COMPOSITE_ANIMATION_TAG);
	if (_object->getSketchSprite()->getActionByTag(COMPOSITE_ANIMATION_TAG) != NULL)
		_object->getSketchSprite()->stopActionByTag(COMPOSITE_ANIMATION_TAG);
	if (_object->getShadowSprite()->getActionByTag(COMPOSITE_ANIMATION_TAG) != NULL)
		_object->getShadowSprite()->stopActionByTag(COMPOSITE_ANIMATION_TAG);
	*/

	_object->getBaseSprite()->runAction(this->_baseAnimates.at(_lastDirection));
	_object->getSketchSprite()->runAction(this->_sketchAnimates.at(_lastDirection));
	_object->getShadowSprite()->runAction(this->_shadowAnimates.at(_lastDirection));
}