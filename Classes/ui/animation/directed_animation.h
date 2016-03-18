#ifndef _DIRECTED_ANIMATE_H_
#define _DIRECTED_ANIMATE_H_


#include <cocos2d.h>
#include "..\base\palette.h"
#include "ui\base\ds_image.h"
#include "pieced_animation_id.h"
#include "base\ds_resource_object.h"
USING_NS_CC;

class DirectedAnimation : public DsResourceObject
{
private:

	PiecedAnimationId *_piecedId;
	Palette * _defaultPalette;

	int _directionCount;
	int _frameCount;
	// Animation * _animation[32];
	Vector<DsImage *>* _spriteFrames[32];
	// DsTexture * _dsTextures[32];


	//int totalMemoryKB;

public:

	static DirectedAnimation* load(PiecedAnimationId *pId);

	// DirectedAnimation();
	DirectedAnimation(PiecedAnimationId *pId);
	~DirectedAnimation();

	void loadFromDcc(const char * filename);
	// void loadFromDcc2(const char * filename);
	
	void setAnimation(int direction, Animation * ani);
	void setFrames(int direction, Vector<DsImage *>* frames);

	// Animation * getAnimation(int direction);
	Vector<DsImage *>* getFrames(int direction);
	int getFrameCount();

	void debugTexture(Texture2D * texture);

};


#endif