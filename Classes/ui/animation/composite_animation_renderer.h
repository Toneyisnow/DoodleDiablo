#ifndef __COMPOSITE_ANIMATION_RENDERER_H_
#define __COMPOSITE_ANIMATION_RENDERER_H_


#include <cocos2d.h>
#include "ui\animation\composite_animation.h"
USING_NS_CC;

class CompositeObject;

class CompositeAnimationRenderer : public Ref
{
private:

	CompositeObject* _object;
	Palette * _defaultPalette;	// We could add more palettes in future

	int _directionCount;
	CompositeAnimation* _current;
	int _lastDirection;
	AnimationAction _lastAction;
	AnimationFigure _lastFigure;

	AnimationLevelHD _lastLevelHD;
	AnimationLevelBody _lastLevelBody;
	AnimationLevelRH _lastLevelRH;
	AnimationLevelLH _lastLevelLH;
	AnimationLevelSH _lastLevelSH;

	Vector<RepeatForever*> _baseAnimates;
	Vector<RepeatForever*> _sketchAnimates;
	Vector<RepeatForever*> _shadowAnimates;

	void forceRefresh();


public:

	// static CharacterAnimation* create(const Character * character);
	CompositeAnimationRenderer(CompositeObject * obj);
	~CompositeAnimationRenderer();

	void initialize();

	void reload();
	void updateDirection();
	
	// CompositeAnimation* getCurrent();

};


#endif