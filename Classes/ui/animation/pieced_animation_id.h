#ifndef __PIECED_ANIMATION_ID_H_
#define __PIECED_ANIMATION_ID_H_

#include <cocos2d.h>

#include "..\..\base\global_definition.h"
#include "composite_animation_id.h"
#include "pieced_motion_id.h"

USING_NS_CC;

typedef enum AnimationLevel
{
	AnimationLevel_LIT = 0 ,
	AnimationLevel_AXE = 1 ,
	AnimationLevel_BHM = 2 ,
	AnimationLevel_BRN = 3 ,
	AnimationLevel_BSD = 4 ,
	AnimationLevel_BST = 5 ,
	AnimationLevel_BTX = 6 ,
	AnimationLevel_BWN = 7 ,
	AnimationLevel_CAP = 8 ,
	AnimationLevel_CLB = 9 ,
	AnimationLevel_CLM = 10,
	AnimationLevel_CRN = 11,
	AnimationLevel_CRS = 12,
	AnimationLevel_CST = 13,
	AnimationLevel_DGR = 14,
	AnimationLevel_DIR = 15,
	AnimationLevel_FHL = 16,
	AnimationLevel_FLA = 17,
	AnimationLevel_FLC = 18,
	AnimationLevel_GHM = 19,
	AnimationLevel_GIX = 20,
	AnimationLevel_GLV = 21,
	AnimationLevel_GPL = 22,
	AnimationLevel_GPS = 23,
	AnimationLevel_GSD = 24,
	AnimationLevel_HAL = 25,
	AnimationLevel_HAX = 26,
	AnimationLevel_HLM = 27,
	AnimationLevel_HVY = 28,
	AnimationLevel_HXB = 29,
	AnimationLevel_JAV = 30,
	AnimationLevel_LAX = 31,
	AnimationLevel_LBB = 32,
	AnimationLevel_LBW = 33,
	AnimationLevel_LSD = 34,
	AnimationLevel_LST = 35,
	AnimationLevel_LXB = 36,
	AnimationLevel_MAC = 37,
	AnimationLevel_MAU = 38,
	AnimationLevel_MED = 39,
	AnimationLevel_MSK = 40,
	AnimationLevel_OPL = 41,
	AnimationLevel_OPS = 42,
	AnimationLevel_PAX = 43,
	AnimationLevel_PIK = 44,
	AnimationLevel_PIL = 45,
	AnimationLevel_SBB = 46,
	AnimationLevel_SBW = 47,
	AnimationLevel_SCM = 48,
	AnimationLevel_SCY = 49,
	AnimationLevel_SKP = 50,
	AnimationLevel_SPR = 51,
	AnimationLevel_SSD = 52,
	AnimationLevel_SST = 53,
	AnimationLevel_TRI = 54,
	AnimationLevel_WHM = 55,
	AnimationLevel_WND = 56,
	AnimationLevel_YWN = 57,
	AnimationLevel_BSH = 58,
	AnimationLevel_BUC = 59,
	AnimationLevel_KIT = 60,
	AnimationLevel_LRG = 61,
	AnimationLevel_SPK = 62,
	AnimationLevel_TOW = 63

} AnimationLevel;

static const char * AnimationLevelStrings[] =
{
	"LIT",
	"AXE",
	"BHM",
	"BRN",
	"BSD",
	"BST",
	"BTX",
	"BWN",
	"CAP",
	"CLB",
	"CLM",
	"CRN",
	"CRS",
	"CST",
	"DGR",
	"DIR",
	"FHL",
	"FLA",
	"FLC",
	"GHM",
	"GIX",
	"GLV",
	"GPL",
	"GPS",
	"GSD",
	"HAL",
	"HAX",
	"HLM",
	"HVY",
	"HXB",
	"JAV",
	"LAX",
	"LBB",
	"LBW",
	"LSD",
	"LST",
	"LXB",
	"MAC",
	"MAU",
	"MED",
	"MSK",
	"OPL",
	"OPS",
	"PAX",
	"PIK",
	"PIL",
	"SBB",
	"SBW",
	"SCM",
	"SCY",
	"SKP",
	"SPR",
	"SSD",
	"SST",
	"TRI",
	"WHM",
	"WND",
	"YWN",
	"BSH",		// These are the Shell's level
	"BUC",
	"KIT",
	"LRG",
	"SPK",
	"TOW"
};

typedef enum AnimationLevelHD
{
	AnimationLevelHD_LIT,
	AnimationLevelHD_BHM,
	AnimationLevelHD_CAP,
	AnimationLevelHD_CRN,
	AnimationLevelHD_FHL,
	AnimationLevelHD_GHM,
	AnimationLevelHD_HLM,
	AnimationLevelHD_MSK,
	AnimationLevelHD_SKP

} AnimationLevelHD;

static const int AnimationLevelHDCount = 9;
static const int AnimationLevelHDConvert[9] = { 0, 2, 8, 11, 16, 19, 27, 40, 50 };

//// Note: Body is representing: TR, LG, RH, LH, S1, S2
typedef enum AnimationLevelBody
{
	AnimationLevelBody_LIT,
	AnimationLevelBody_HVY,
	AnimationLevelBody_MED

} AnimationLevelBody;

static const int AnimationLevelBodyCount = 3;
static const int AnimationLevelBodyConvert[3] = { 0, 28, 39 };


typedef enum AnimationLevelRH
{
	AnimationLevelRH_NA,		// This is only a place holder and should not be used
	AnimationLevelRH_AXE,
	AnimationLevelRH_BRN,
	AnimationLevelRH_BSD,
	AnimationLevelRH_BST,
	AnimationLevelRH_BTX,
	AnimationLevelRH_BWN,
	AnimationLevelRH_CLB,
	AnimationLevelRH_CLM,
	AnimationLevelRH_CRS,
	AnimationLevelRH_CST,
	AnimationLevelRH_DGR,
	AnimationLevelRH_DIR,
	AnimationLevelRH_FLA,
	AnimationLevelRH_FLC,
	AnimationLevelRH_GIX,
	AnimationLevelRH_GLV,
	AnimationLevelRH_GPL,
	AnimationLevelRH_GPS,
	AnimationLevelRH_GSD,
	AnimationLevelRH_HAL,
	AnimationLevelRH_HAX,
	AnimationLevelRH_HXB,
	AnimationLevelRH_JAV,
	AnimationLevelRH_LAX,
	AnimationLevelRH_LSD,
	AnimationLevelRH_LST,
	AnimationLevelRH_LXB,
	AnimationLevelRH_MAC,
	AnimationLevelRH_MAU,
	AnimationLevelRH_OPL,
	AnimationLevelRH_OPS,
	AnimationLevelRH_PAX,
	AnimationLevelRH_PIK,
	AnimationLevelRH_PIL,
	AnimationLevelRH_SCM,
	AnimationLevelRH_SCY,
	AnimationLevelRH_SPR,
	AnimationLevelRH_SSD,
	AnimationLevelRH_SST,
	AnimationLevelRH_TRI,
	AnimationLevelRH_WHM,
	AnimationLevelRH_WND,
	AnimationLevelRH_YWN

} AnimationLevelRH;

static const int AnimationLevelRHCount = 44;
static const int AnimationLevelRHConvert[44] = { 0, 1, 3, 4, 5, 6, 7, 9, 10, 12, 13, 
												14, 15, 17, 18, 20, 21, 22, 23, 24, 25, 
												26, 29, 30, 31, 34, 35, 36, 37, 38, 41, 
												42, 43, 44, 45, 48, 49, 51, 52, 53, 54, 
												55, 56, 57 };

typedef enum AnimationLevelLH
{
	AnimationLevelLH_NA,		// This is only a place holder and should not be used
	AnimationLevelLH_AXE,
	AnimationLevelLH_BSD,
	AnimationLevelLH_BWN,
	AnimationLevelLH_CLB,
	AnimationLevelLH_CLM,
	AnimationLevelLH_CRS,
	AnimationLevelLH_DGR,
	AnimationLevelLH_DIR,
	AnimationLevelLH_FLA,
	AnimationLevelLH_FLC,
	AnimationLevelLH_GLV,
	AnimationLevelLH_GPL,
	AnimationLevelLH_GPS,
	AnimationLevelLH_GSD,
	AnimationLevelLH_HAX,
	AnimationLevelLH_JAV,
	AnimationLevelLH_LBB,
	AnimationLevelLH_LBW,
	AnimationLevelLH_LSD,
	AnimationLevelLH_MAC,
	AnimationLevelLH_OPL,
	AnimationLevelLH_OPS,
	AnimationLevelLH_PIL,
	AnimationLevelLH_SBB,
	AnimationLevelLH_SBW,
	AnimationLevelLH_SCM,
	AnimationLevelLH_SSD,
	AnimationLevelLH_WHM,
	AnimationLevelLH_WND,
	AnimationLevelLH_YWN

} AnimationLevelLH;

static const int AnimationLevelLHCount = 31;
static const int AnimationLevelLHConvert[31] = { 0, 1, 4, 7, 9, 10, 12, 14, 15, 17, 18, 
											    21, 22, 23, 24, 26, 30, 32, 33, 34, 37, 
												41, 42, 45, 46, 47, 48, 52, 55, 56, 57 };

typedef enum AnimationLevelSH
{
	AnimationLevelSH_NA,
	AnimationLevelSH_BSH,
	AnimationLevelSH_BUC,
	AnimationLevelSH_KIT,
	AnimationLevelSH_LRG,
	AnimationLevelSH_SPK,
	AnimationLevelSH_TOW

} AnimationLevelSH;

static const int AnimationLevelSHCount = 7;
static const int AnimationLevelSHConvert[7] = { 0, 58, 59, 60, 61, 62, 63 };



class PiecedAnimationId : public Ref
{

private:

	CompositeAnimationId * _compositeId;
	AnimationPiece _piece;
	AnimationFigure _figure;
	AnimationLevel _level;

public:

	static PiecedAnimationId * create(CompositeAnimationId * com, AnimationFigure f, AnimationPiece p, AnimationLevel l);
	static PiecedAnimationId * create(PiecedMotionId *p, AnimationLevel l);

	static std::string getFullPieceLevelStrings(AnimationLevelHD hd, AnimationLevelBody body, AnimationLevelRH rh, AnimationLevelLH lh, AnimationLevelSH sh);

	//// static Vector<PiecedAnimationId *>* retrieveAllByPiecedMotion(PiecedMotionId *pMotion);
	//// static AnimationLevel* getAllPieceLevels(AnimationPiece piece);

	PiecedAnimationId * clone();
	
	PiecedAnimationId(CompositeAnimationId * com, AnimationFigure f, AnimationPiece p, AnimationLevel l);
	PiecedAnimationId(PiecedMotionId * p, AnimationLevel l);
	~PiecedAnimationId();

	CompositeAnimationId * getCompositeId();
	AnimationPiece getPiece();
	AnimationFigure getFigure();
	AnimationLevel getLevel();

	std::string toString();
	std::string generateKey();
};

#endif