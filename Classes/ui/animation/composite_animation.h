#ifndef _COMPOSITE_ANIMATION_H_
#define _COMPOSITE_ANIMATION_H_

#include <cocos2d.h>
#include "composite_animation_config.h"
#include "pieced_animation_id.h"
#include "directed_animation.h"
#include "base\memory_object.h"

USING_NS_CC;

const int COMPOSITE_ANIMATION_TAG = 111;

class CompositeObject;

class CompositeAnimation : public MemoryObject
{

private:

	CompositeAnimationConfig* _animationConfig;
	CompositeAnimationId* _animationId;

	int _pieceCount;
	int _directionCount;

	Animation* _compositeAnimation[MaxDirectionCount];
	Animation* _compositeSketchAnimation[MaxDirectionCount];
	Animation* _compositeShadowAnimation[MaxDirectionCount];
	
	AnimationLevel _pieceLevel[MaxPieceCount];
	Vector<PiecedMotionId *>* _allPiecedMotions;

	Palette * _lastRenderPalette;
	DirectedAnimation * _piecedAnimation[16];


	/*
	DirectedAnimation *_headAnimation;
	DirectedAnimation *_bodyAnimation;
	DirectedAnimation *_legAnimation;
	DirectedAnimation *_leftarmAnimation;
	DirectedAnimation *_rightarmAnimation;
	DirectedAnimation *_lefthandAnimation;
	DirectedAnimation *_righthandAnimation;
	*/
	/*
	Sprite * newComponentSprite();
	void reloadAnimationForAllActions();
	void reloadAnimationAction();

	CompositeAnimationConfig * _animationConfigs[AnimationActionCount];
	CompositeAnimationConfig * _currentAnimationConfig;
	
	int _currentFrameCount;

	RepeatForever *_compositeAnimationCache[AnimationActionCount][MaxDirectionCount];

	*/
public:

	static int convert_direction(int direction, int totaldirection);
	static int calculateDirection_8(Vec2 dirVector);
	static int calculateDirection_16(Vec2 dirVector);
	static int calculateDirection_32(Vec2 dirVector);

	int myreferenceCount;

	CompositeAnimation(CompositeAnimationId* id);
	CompositeAnimation(CompositeAnimationId* id, AnimationLevelHD hd, AnimationLevelBody body, AnimationLevelRH rh, AnimationLevelLH lh, AnimationLevelSH sh);

	// static CharacterAnimation* create(const Character * character);
	//CompositeAnimation(Character * character);
	~CompositeAnimation();

	void initialize();
	void render(Palette * palette);

	Animation* getAnimation(int direction);
	Animation* getSketchAnimation(int direction);
	Animation* getShadowAnimation(int direction);
	
	/// Refresh the current animation according to character's status/direction/equipment/gesture
	void refresh();
	void updateFromCache();

	////void updateDirection(Vec2 direction);
	int calculateDirection(Vec2 dirVector);
	int getDirectionCount();

	AnimationAction calculateAnimationAction();
	AnimationFigure calculateAnimationFigure();
	/// DirectedAnimation *refreshPieceAnimation(PiecedMotionId *pieceId, AnimationLevel level);
	//// TargetedAction* updatePieceDirection(Sprite *obj, Animation * animation);


	AnimationLevel getEquipLevel(AnimationPiece p);

	AnimationLevel getHDEquipLevel();
	AnimationLevel getTREquipLevel();
	AnimationLevel getLGEquipLevel();
	AnimationLevel getLAEquipLevel();
	AnimationLevel getRAEquipLevel();
	AnimationLevel getLHEquipLevel();
	AnimationLevel getRHEquipLevel();
	AnimationLevel getSHEquipLevel();
	AnimationLevel getS1EquipLevel();
	AnimationLevel getS2EquipLevel();

	void callback_0();

};



#endif