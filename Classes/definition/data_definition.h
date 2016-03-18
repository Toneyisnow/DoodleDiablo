#ifndef _LEVEL_PREST_DEFINITION_H_
#define _LEVEL_PREST_DEFINITION_H_


#include <cocos2d.h>
#include "excel_definition.h"

USING_NS_CC;

typedef enum LevelPrestColumns
{
    LevelPrest_Name,
    LevelPrest_Def,
    LevelPrest_LevelId,
    LevelPrest_Populate,
    LevelPrest_Logicals,
    LevelPrest_Outdoors,
    LevelPrest_Animate,
    LevelPrest_KillEdge,
    LevelPrest_FillBlanks,
    LevelPrest_SizeX,
    LevelPrest_SizeY,
    LevelPrest_AutoMap,
    LevelPrest_Scan,
    LevelPrest_Pops,
    LevelPrest_PopPad,
    LevelPrest_Files,
    LevelPrest_File1,
    LevelPrest_File2,
    LevelPrest_File3,
    LevelPrest_File4,
    LevelPrest_File5,
    LevelPrest_File6,
    LevelPrest_Dt1Mask,
    LevelPrest_Beta

} LevelPrestColumns;


const int LevelPrestColumnCount = 24;
const ExcelCellType LevelPrestTypes[24] = { Cell_String, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_Int, Cell_Int };

class LevelPrestDefinition : public ExcelDefinition
{
public:
    static Map<int, ExcelDefinition*>* load(const char * resourceKey);
    static int getFileIndex(int fileNumber);

};


typedef enum LevelTypeColumns
{
    LevelType_Name = 0,
    LevelType_Id = 1,
    // 2 ~ 33 is File
    LevelType_Beta = 34,
    LevelType_Act = 35

} LevelTypeColumns;


const int LevelTypeColumnCount = 36;
const ExcelCellType LevelTypeTypes[36] = { Cell_String, Cell_Int, 
    Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, 
    Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String,
    Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String,
    Cell_String, Cell_String, 
    Cell_Int, Cell_Int };

class LevelTypeDefinition : public ExcelDefinition
{
public:
    static Map<int, ExcelDefinition*>* load(const char * resourceKey);

    static int getFileIndex(int fileNumber);

};

typedef enum ObjectsColumns
{
    ObjectsColumns_Name,
    ObjectsColumns_Description,
    ObjectsColumns_Id,
    ObjectsColumns_Token,
    ObjectsColumns_SpawnMax,
    ObjectsColumns_Selectable0,
    ObjectsColumns_Selectable1,
    ObjectsColumns_Selectable2,
    ObjectsColumns_Selectable3,
    ObjectsColumns_Selectable4,
    ObjectsColumns_Selectable5,
    ObjectsColumns_Selectable6,
    ObjectsColumns_Selectable7,
    ObjectsColumns_TrapProb,
    ObjectsColumns_SizeX,
    ObjectsColumns_SizeY,
    ObjectsColumns_nTgtFX,
    ObjectsColumns_nTgtFY,
    ObjectsColumns_nTgtBX,
    ObjectsColumns_nTgtBY,
    ObjectsColumns_FrameCnt0,
    ObjectsColumns_FrameCnt1,
    ObjectsColumns_FrameCnt2,
    ObjectsColumns_FrameCnt3,
    ObjectsColumns_FrameCnt4,
    ObjectsColumns_FrameCnt5,
    ObjectsColumns_FrameCnt6,
    ObjectsColumns_FrameCnt7,
    ObjectsColumns_FrameDelta0,
    ObjectsColumns_FrameDelta1,
    ObjectsColumns_FrameDelta2,
    ObjectsColumns_FrameDelta3,
    ObjectsColumns_FrameDelta4,
    ObjectsColumns_FrameDelta5,
    ObjectsColumns_FrameDelta6,
    ObjectsColumns_FrameDelta7,
    ObjectsColumns_CycleAnim0,
    ObjectsColumns_CycleAnim1,
    ObjectsColumns_CycleAnim2,
    ObjectsColumns_CycleAnim3,
    ObjectsColumns_CycleAnim4,
    ObjectsColumns_CycleAnim5,
    ObjectsColumns_CycleAnim6,
    ObjectsColumns_CycleAnim7,
    ObjectsColumns_Lit0,
    ObjectsColumns_Lit1,
    ObjectsColumns_Lit2,
    ObjectsColumns_Lit3,
    ObjectsColumns_Lit4,
    ObjectsColumns_Lit5,
    ObjectsColumns_Lit6,
    ObjectsColumns_Lit7,
    ObjectsColumns_BlocksLight0,
    ObjectsColumns_BlocksLight1,
    ObjectsColumns_BlocksLight2,
    ObjectsColumns_BlocksLight3,
    ObjectsColumns_BlocksLight4,
    ObjectsColumns_BlocksLight5,
    ObjectsColumns_BlocksLight6,
    ObjectsColumns_BlocksLight7,
    ObjectsColumns_HasCollision0,
    ObjectsColumns_HasCollision1,
    ObjectsColumns_HasCollision2,
    ObjectsColumns_HasCollision3,
    ObjectsColumns_HasCollision4,
    ObjectsColumns_HasCollision5,
    ObjectsColumns_HasCollision6,
    ObjectsColumns_HasCollision7,
    ObjectsColumns_IsAttackable0,
    ObjectsColumns_Start0,
    ObjectsColumns_Start1,
    ObjectsColumns_Start2,
    ObjectsColumns_Start3,
    ObjectsColumns_Start4,
    ObjectsColumns_Start5,
    ObjectsColumns_Start6,
    ObjectsColumns_Start7,
    ObjectsColumns_EnvEffect,
    ObjectsColumns_IsDoor,
    ObjectsColumns_BlocksVis,
    ObjectsColumns_Orientation,
    ObjectsColumns_Trans,
    ObjectsColumns_OrderFlag0,
    ObjectsColumns_OrderFlag1,
    ObjectsColumns_OrderFlag2,
    ObjectsColumns_OrderFlag3,
    ObjectsColumns_OrderFlag4,
    ObjectsColumns_OrderFlag5,
    ObjectsColumns_OrderFlag6,
    ObjectsColumns_OrderFlag7,
    ObjectsColumns_PreOperate,
    ObjectsColumns_Mode0,
    ObjectsColumns_Mode1,
    ObjectsColumns_Mode2,
    ObjectsColumns_Mode3,
    ObjectsColumns_Mode4,
    ObjectsColumns_Mode5,
    ObjectsColumns_Mode6,
    ObjectsColumns_Mode7,
    ObjectsColumns_Yoffset,
    ObjectsColumns_Xoffset,
    ObjectsColumns_Draw,
    ObjectsColumns_Red,
    ObjectsColumns_Green,
    ObjectsColumns_Blue,
    ObjectsColumns_HD,
    ObjectsColumns_TR,
    ObjectsColumns_LG,
    ObjectsColumns_RA,
    ObjectsColumns_LA,
    ObjectsColumns_RH,
    ObjectsColumns_LH,
    ObjectsColumns_SH,
    ObjectsColumns_S1,
    ObjectsColumns_S2,
    ObjectsColumns_S3,
    ObjectsColumns_S4,
    ObjectsColumns_S5,
    ObjectsColumns_S6,
    ObjectsColumns_S7,
    ObjectsColumns_S8,
    ObjectsColumns_TotalPieces,
    ObjectsColumns_SubClass,
    ObjectsColumns_Xspace,
    ObjectsColumns_Yspace,
    ObjectsColumns_NameOffset,
    ObjectsColumns_MonsterOK,
    ObjectsColumns_OperateRange,
    ObjectsColumns_ShrineFunction,
    ObjectsColumns_Restore,
    ObjectsColumns_Parm0,
    ObjectsColumns_Parm1,
    ObjectsColumns_Parm2,
    ObjectsColumns_Parm3,
    ObjectsColumns_Parm4,
    ObjectsColumns_Parm5,
    ObjectsColumns_Parm6,
    ObjectsColumns_Parm7,
    ObjectsColumns_Act,
    ObjectsColumns_Lockable,
    ObjectsColumns_Gore,
    ObjectsColumns_Sync,
    ObjectsColumns_Flicker,
    ObjectsColumns_Damage,
    ObjectsColumns_Beta,
    ObjectsColumns_Overlay,
    ObjectsColumns_CollisionSubst,
    ObjectsColumns_Left,
    ObjectsColumns_Top,
    ObjectsColumns_Width,
    ObjectsColumns_Height,
    ObjectsColumns_OperateFn,
    ObjectsColumns_PopulateFn,
    ObjectsColumns_InitFn,
    ObjectsColumns_ClientFn,
    ObjectsColumns_RestoreVirgins,
    ObjectsColumns_BlockMissile,
    ObjectsColumns_DrawUnder,
    ObjectsColumns_OpenWarp,
    ObjectsColumns_AutoMap

} ObjectsColumns;


const int ObjectsColumnCount = 160;
const ExcelCellType ObjectsTypes[160] = {
	Cell_String, Cell_String, Cell_Int, Cell_String, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int,
	Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int, Cell_Int
};

class ObjectsDefinition : public ExcelDefinition
{
public:
    static Map<int, ExcelDefinition*>* load(const char * resourceKey);
};


typedef enum ObjectInstanceColumns
{
	ObjectInstance_Act,
	ObjectInstance_Type,
	ObjectInstance_Id,
	ObjectInstance_Description,
	ObjectInstance_ObjectId,
	ObjectInstance_MonstatsId,
	ObjectInstance_Direction,
	ObjectInstance_Base,
	ObjectInstance_Token,
	ObjectInstance_Mode,
	ObjectInstance_Class,
	ObjectInstance_HD,
	ObjectInstance_TR,
	ObjectInstance_LG,
	ObjectInstance_RA,
	ObjectInstance_LA,
	ObjectInstance_RH,
	ObjectInstance_LH,
	ObjectInstance_SH,
	ObjectInstance_S1,
	ObjectInstance_S2,
	ObjectInstance_S3,
	ObjectInstance_S4,
	ObjectInstance_S5,
	ObjectInstance_S6,
	ObjectInstance_S7,
	ObjectInstance_S8,
	ObjectInstance_ColorMap,
	ObjectInstance_Index,
	ObjectInstance_EOL

} ObjectInstanceColumns;


const int ObjectInstanceColumnCount = 30;
const ExcelCellType ObjectInstanceTypes[30] = { 
	Cell_Int, Cell_Int, Cell_Int, Cell_String, Cell_Int, Cell_Int, Cell_Int, Cell_String, Cell_String, Cell_String,
	Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String,
	Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_String, Cell_Int, Cell_Int
};

class ObjectInstanceDefinition : public ExcelDefinition
{
public:
	static Map<int, ExcelDefinition*>* load(const char * resourceKey);

	static int generateKey(ExcelDefinition* def);
	static int generateKey(int act, int type, int id);
};

#endif