#ifndef _GLOBAL_DEFINITION_H_
#define _GLOBAL_DEFINITION_H_


#include <cocos2d.h>


USING_NS_CC;

static const int MaxDirectionCount = 16;
static const int MaxPieceCount = 16;

typedef enum CreatureAction
{
	Action_A1,
	Action_BL,
	Action_GH,
	Action_KK,
	Action_NU,
	Action_TN,
	Action_RN,
	Action_S1,
	Action_S3,
	Action_S4,
	Action_SC,
	Action_TH,
	Action_TW,
	Action_WL,
	Action_DH,
	Action_DD

} CreatureAction;

static const char * CreatureActionStrings[] = 
{ 
	"A1",
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
	"DD"
};

typedef enum CreatureDefinition
{
	Creature_BA,
	Creature_AM,
	Creature_DI,
	Creature_DU
} CreatureDefinition;

static const char * CreatureDefinitionStrings[] = 
{ 
	"BA", 
	"AM", 
	"DI", 
	"DU" 
};


#endif