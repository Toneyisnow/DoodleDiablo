#ifndef __COMPOSITE_ANIMATION_CONFIG_H_
#define __COMPOSITE_ANIMATION_CONFIG_H_

#include <cocos2d.h>
#include "pieced_motion_id.h"
#include "base/ds_resource_object.h"

USING_NS_CC;

class CompositeAnimationConfig : public DsResourceObject
{

private:

	CompositeAnimationId * _animationId;
	int _directionCount;
	int _frameCount;
	int _layerCount;

	int _zOrder[32][32][16];
	//// Should be: int* _zOrder; [32][32][16]
	int _drawingOrder[32][32][16];

	Vector<PiecedMotionId *> * _pieceMotionIds;

public:

	static CompositeAnimationConfig* load(CompositeAnimationId * aniId);
	CompositeAnimationConfig(CompositeAnimationId * aniId);
	~CompositeAnimationConfig();

	void initializeData();

	void initFromCof(AnimationGenera g, char* token, AnimationAction action, AnimationFigure figure, const char *filename);
	void initFromCof(CompositeAnimationId * aniId, void* buffer);

	int getFrameCount();
	int getLayerCount();
	int getDirectionCount();

	Vector<PiecedMotionId *> * getAllPiecedMotions();

	PiecedMotionId * getPiecedMotionId(AnimationPiece piece);

	int * getLayerZOrders(int direction, int frame);
	int * getDrawingOrders(int direction, int frame);

};

#endif