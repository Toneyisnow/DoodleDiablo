#ifndef __COMPOSITE_OBJECT_H_
#define __COMPOSITE_OBJECT_H_


#include <cocos2d.h>
#include "ui\animation\pieced_animation_id.h"
#include "ui\animation\composite_animation_id.h"
#include "ui\animation\composite_animation_renderer.h"

USING_NS_CC;

class CompositeObject : public Ref
{
protected:

	Sprite* _baseSprite;
	Sprite* _sketchSprite;
	Sprite* _shadowSprite;

	const char* _token;
	Vec2 _direction;
	int _totalDirectionCount;

	float _calculatedSpeed;

	AnimationAction _action;
	CompositeAnimationRenderer* _compositeAnimationRenderer;

	/// void refreshAnimation();

public:

	CompositeObject();
	CompositeObject(const char * token);
	~CompositeObject();

	static AnimationAction parseAnimationAction(const char * actionString);

	virtual AnimationGenera getGenera();
	Sprite* getBaseSprite();
	Sprite* getSketchSprite();
	Sprite* getShadowSprite();
	const char * getToken() const;

	// Direction
	Vec2 getDirection();		// TODO: do we need this?
	virtual void turnDirection(int direction);
	virtual void turnDirection(int dx, int dy);
	
	
	Vec2 getPosition();
	
	void deem(int val);

	int getAmbisexualent();
	int getLuminance();

	virtual void sendToGround(Node *node, Point pos);
	virtual void removeFromGround();

	virtual void changeToAction(AnimationAction action);
	
	virtual void takeTick(float delta);

	virtual AnimationAction getAnimationAction();
	virtual AnimationFigure getFigure();

	virtual AnimationLevelHD getHDLevel();
	virtual AnimationLevelBody getBodyLevel();
	virtual AnimationLevelRH getRHLevel();
	virtual AnimationLevelLH getLHLevel();
	virtual AnimationLevelSH getSHLevel();

};


#endif