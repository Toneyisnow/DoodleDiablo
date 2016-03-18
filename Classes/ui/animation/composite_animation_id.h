#ifndef __COMPOSITE_ANIMATION_ID_H_
#define __COMPOSITE_ANIMATION_ID_H_

#include <cocos2d.h>

#include "base\global_definition.h"


USING_NS_CC;


typedef enum AnimationGenera
{
	AnimationGenera_Missle,
	AnimationGenera_Monster,
	AnimationGenera_Object,
	AnimationGenera_Character,

} AnimationGenera;

typedef enum AnimationFigure
{
	_HTH,
	_1HS,
	_1HT,
	_2HS,
	_2HT,

} AnimationFigure;

static const char * AnimationFigureStrings[] =
{
	"HTH",
	"1HS",
	"1HT",
	"2HS",
	"2HT",

};

typedef enum AnimationAction
{
	Animation_A1,
	Animation_A2,
	Animation_BL,
	Animation_GH,
	Animation_KK,
	Animation_NU,
	Animation_TN,
	Animation_RN,
	Animation_S1,
	Animation_S3,
	Animation_S4,
	Animation_SC,
	Animation_TH,
	Animation_TW,
	Animation_WL,
	Animation_DH,
	Animation_DD,
	Animation_ON,
	Animation_OP,
	Animation_DT

} AnimationAction;

static const char * AnimationActionStrings[] =
{
	"A1",
	"A2",
	"BL",
	"GH",
	"KK",
	"NU",
	"TN",
	"RN",
	"S1",
	"S3",
	"S4",
	"SC",
	"TH",
	"TW",
	"WL",
	"DH",
	"DD",
	"ON",
	"OP",
	"DT"
};

static const int AnimationActionCount = 20;

class CompositeAnimationId : public Ref
{

private:

	AnimationGenera _genera;
	char* _token;
	AnimationAction _action;
	AnimationFigure _figure;
	

public:

	static CompositeAnimationId * create(AnimationGenera g, char* token, AnimationAction a, AnimationFigure f);
	CompositeAnimationId * clone();


	CompositeAnimationId(AnimationGenera g, char* token, AnimationAction a, AnimationFigure f);
	~CompositeAnimationId();

	AnimationGenera getGenera();
	char* getToken();
	AnimationFigure getFigure();
	AnimationAction getAction();

	std::string toString();
	std::string generateKey();
};

#endif