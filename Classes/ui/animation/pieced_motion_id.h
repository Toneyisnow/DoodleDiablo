#ifndef __PIECED_MOTION_ID_H_
#define __PIECED_MOTION_ID_H_

#include <cocos2d.h>

#include "..\..\base\global_definition.h"
#include "composite_animation_id.h"

USING_NS_CC;

typedef enum AnimationPiece
{
	Piece_HD = 0,
	Piece_TR = 1,
	Piece_LG = 2,
	Piece_RA = 3,
	Piece_LA = 4,
	Piece_RH = 5,
	Piece_LH = 6,
	Piece_SH = 7,
	Piece_S1 = 8,
	Piece_S2 = 9,
	Piece_S3 = 10,
	Piece_S4 = 11,
	Piece_S5 = 12,
	Piece_S6 = 13,
	Piece_S7 = 14,
	Piece_S8 = 15

} AnimationPiece;

static const int AnimationPieceCount = 16;

static const char * AnimationPieceStrings[] =
{
	"HD",
	"TR",
	"LG",
	"RA",
	"LA",
	"RH",
	"LH",
	"SH",
	"S1",
	"S2",
	"S3",
	"S4",
	"S5",
	"S6",
	"S7",
	"S8"
};

class PiecedMotionId : public Ref
{

private:

	CompositeAnimationId * _compositeId;
	AnimationPiece _piece;
	AnimationFigure _figure;

public:

	static PiecedMotionId * create(CompositeAnimationId * compositeId, AnimationPiece p, AnimationFigure f);
	PiecedMotionId * clone();

	PiecedMotionId(CompositeAnimationId * compositeId, AnimationPiece p, AnimationFigure f);
	~PiecedMotionId();

	CompositeAnimationId * getCompositeId();
	//CreatureDefinition getCreature();

	AnimationGenera getGenera();
	char* getToken();
	AnimationPiece getPiece();
	AnimationFigure getFigure();	// Tihs figure will point to the target piece's figure, not the compositeAnimation figure
	AnimationAction getAction();

	
	std::string toString();
	std::string generateKey();
};

#endif