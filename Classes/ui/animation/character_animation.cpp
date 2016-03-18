
#include "character_animation.h"
#include "ui\object\character.h"
#include "animation_library.h"



CompositeAnimationConfig2::CompositeAnimationConfig2()
{
	_directionCount = 0;
	_frameCount = 0;
	_layerCount = 0;
}
CompositeAnimationConfig2::~CompositeAnimationConfig2()
{

}

void CompositeAnimationConfig2::initFromFile(const char * filename)
{
	FILE  * in;
	//UBYTE layers, frames_per_dir, directions, c, comp_idx;
	UBYTE c, comp_idx;
	int   total_frames, i, x, y;
	long  dword;
	char  composit[16][3] = {
			{ "HD" }, { "TR" }, { "LG" }, { "RA" }, { "LA" }, { "RH" }, { "LH" }, { "SH" },
			{ "S1" }, { "S2" }, { "S3" }, { "S4" }, { "S5" }, { "S6" }, { "S7" }, { "S8" }
	};

	int layerindex[16];

	in = fopen(filename, "rb");
	if (in == NULL)
	{
		return;
	}

	// read it
	_layerCount = fgetc(in);
	_frameCount = fgetc(in);
	_directionCount = fgetc(in);

	// unknown
	for (i = 0; i<5; i++)
	{
		c = fgetc(in);
	}
	
	for (i = 0; i<4; i++)
	{
		for (x = 0; x<4; x++)
		{
			c = fgetc(in);
		}
		fseek(in, -4, SEEK_CUR);
		fread(&dword, 4, 1, in);
	}
	for (i = 0; i<4; i++)
	{
		c = fgetc(in);
	}


	// 9 bytes strings
	for (i = 0; i < _layerCount; i++)
	{
		for (x = 0; x < 9; x++)
		{
			c = fgetc(in);
			if (x == 0)
			{
				comp_idx = c;
				layerindex[i] = (int)c;
			}
		}
	}

	// unknown frames_per_dir data
	for (i = 0; i < _frameCount; i++)
	{
		c = fgetc(in);
	}

	// layers priority
	for (i = 0; i < _directionCount; i++)
	{
		for (x = 0; x < _frameCount; x++)
		{
			int zOrder = 100;
			for (y = 0; y < _layerCount; y++)
			{
				c = fgetc(in);
				int index = (int)c;
				_zOrder[i][x][index] = zOrder++;
			}

		}
	}

	std::string s;
	char msg[255];
	for (y = 0; y < 16; y++)
	{
		sprintf(msg, " %i", _zOrder[14][0][y]);
		s += msg;
	}
	log(s.c_str());

	// end
	fclose(in);
}

int* CompositeAnimationConfig2::getLayerZOrders(int direction, int frame)
{
	return _zOrder[direction][frame];
}

int CompositeAnimationConfig2::getFrameCount()
{
	return _frameCount;
}

CharacterAnimation::CharacterAnimation(Character * character)
{
	this->_character = character;
	//_animationConfig = new CompositeAnimationConfig2();

}

CharacterAnimation::~CharacterAnimation()
{
	_animationConfig->release();

	if (this->_head != NULL)
	{
		this->_head->release();
		this->_head = NULL;
	}
	if (this->_body != NULL)
	{
		this->_body->release();
		this->_body = NULL;
	}
	if (this->_leg != NULL)
	{
		this->_leg->release();
		this->_leg = NULL;
	}
	if (this->_leftarm != NULL)
	{
		this->_leftarm->release();
		this->_leftarm = NULL;
	}
	if (this->_rightarm != NULL)
	{
		this->_rightarm->release();
		this->_rightarm = NULL;
	}
	if (this->_lefthand != NULL)
	{
		this->_lefthand->release();
		this->_lefthand = NULL;
	}
	if (this->_righthand != NULL)
	{
		this->_righthand->release();
		this->_righthand = NULL;
	}
	if (this->_shield != NULL)
	{
		this->_shield->release();
		this->_shield = NULL;
	}
	if (this->_special1 != NULL)
	{
		this->_special1->release();
		this->_special1 = NULL;
	}
	if (this->_special2 != NULL)
	{
		this->_special2->release();
		this->_special2 = NULL;
	}
}

void CharacterAnimation::initialize()
{
	this->_head = newComponentSprite();
	this->_body = newComponentSprite();
	this->_leg = newComponentSprite();
	this->_leftarm = newComponentSprite();
	this->_rightarm = newComponentSprite();
	this->_lefthand = newComponentSprite();
	this->_righthand = newComponentSprite();
	this->_shield = newComponentSprite();
	this->_special1 = newComponentSprite();
	this->_special2 = newComponentSprite();
	
}

Sprite * CharacterAnimation::newComponentSprite()
{
	Sprite* obj = Sprite::create();
	obj->setAnchorPoint(Vec2(0, 0));
	this->_character->getBaseSprite()->addChild(obj);

	return obj;
}

/// Refresh the current animation according to character's status/direction/equipment/gesture
void CharacterAnimation::refresh()
{
	char * figure = getFigureString();
	char * action = getActionString();
	
	this->_character->getBaseSprite()->stopAllActions();

	_animationConfig = NULL; // new CompositeAnimationConfig()
	//_animationConfig->initFromFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\COF\\BAKK1HS.cof");
	_currentFrameCount = 0;

	TargetedAction *h1 = refreshComponentAnimation(this->_head, "HD", figure, action, getHDEquipLevel());
	TargetedAction *h2 = refreshComponentAnimation(this->_body, "TR", figure, action, getTREquipLevel());
	TargetedAction *h3 = refreshComponentAnimation(this->_leg, "LG", figure, action, getLGEquipLevel());
	TargetedAction *h4 = refreshComponentAnimation(this->_leftarm, "LA", figure, action, getLAEquipLevel());
	TargetedAction *h5 = refreshComponentAnimation(this->_rightarm, "RA", figure, action, getRAEquipLevel());
	//refreshComponentAnimation(this->_lefthand, "LH", figure, action, getLHEquipLevel());
	//refreshComponentAnimation(this->_righthand, "RH", figure, action, getRHEquipLevel());

	auto a0 = Repeat::create(Sequence::create(CallFunc::create(CC_CALLBACK_0(CharacterAnimation::callback_0, this)), DelayTime::create(0.1f), nullptr), _animationConfig->getFrameCount());
	Spawn *groupAction = Spawn::create(h1, h2, h3, h4, h5, a0, nullptr);
	this->_character->getBaseSprite()->runAction(RepeatForever::create(groupAction));
}

TargetedAction* CharacterAnimation::refreshComponentAnimation(Sprite *obj, const char * component, const char * figure, const char * action, const char * level)
{
	return NULL;
}

char * CharacterAnimation::getFigureString()	// HTH, 1HS, 1HT, 2HS, 2HT, ...
{
	return "1HS";
}
char * CharacterAnimation::getActionString()	// HTH, 1HS, 1HT, 2HS, 2HT, ...
{
	return "TN";
}
char * CharacterAnimation::getHDEquipLevel()
{
	// Return the string of HD level according to the current equipment
	return "HLM";
}
char * CharacterAnimation::getTREquipLevel()
{
	// Return the string of HD level according to the current equipment
	return "HVY";
}
char * CharacterAnimation::getLGEquipLevel()
{
	// Return the string of HD level according to the current equipment
	return "HVY";
}
char * CharacterAnimation::getLAEquipLevel()
{
	return "HVY";
}
char * CharacterAnimation::getRAEquipLevel()
{
	return "HVY";
}
char * CharacterAnimation::getLHEquipLevel()
{
	return "HVY";
}
char * CharacterAnimation::getRHEquipLevel()
{
	return "HVY";
}
char * CharacterAnimation::getSHEquipLevel()
{
	return "HVY";
}
char * CharacterAnimation::getS1EquipLevel()
{
	return "HVY";
}
char * CharacterAnimation::getS2EquipLevel()
{
	return "HVY";
}

void CharacterAnimation::callback_0()
{
	
	int cDirection = 0;
	switch (this->_character->getDirection())
	{
	case 0: cDirection = 10; break;
	case 1: cDirection = 14; break;
	case 2: cDirection = 3; break;
	case 3: cDirection = 6; break;
	case 4: cDirection = 8; break;
	case 5: cDirection = 12; break;
	case 6: cDirection = 0; break;
	case 7: cDirection = 4; break;
	case 8: cDirection = 9; break;
	case 9: cDirection = 11; break;
	case 10: cDirection = 13; break;
	case 11: cDirection = 15; break;
	case 12: cDirection = 1; break;
	case 13: cDirection = 3; break;
	case 14: cDirection = 5; break;
	case 15: cDirection = 7; break;

	default:
		break;
	}

	//cDirection = 14;	// if direction = 3
	//cDirection = 9;	// if direction = 1
	//cDirection = 10;	// if direction = 2
	//cDirection = 2;	// if direction = 4

	
	cDirection = (cDirection + 8) % 16;

	int * zorders = 0; ////this->_animationConfig->getLayerZOrders(cDirection, _currentFrameCount);

	log("direction: %d frame: %d zorders : head %d, body %d, leg %d, ra %d, la %d", cDirection, _currentFrameCount, zorders[0], zorders[1], zorders[2], zorders[3], zorders[5]);

	this->_head->setGlobalZOrder(zorders[0]);
	this->_body->setGlobalZOrder(zorders[1]);
	this->_leg->setGlobalZOrder(zorders[2]);
	this->_rightarm->setGlobalZOrder(zorders[3]);
	this->_leftarm->setGlobalZOrder(zorders[4]);
	
	/*
	this->_leg->setGlobalZOrder(zorders[0]);
	this->_body->setGlobalZOrder(zorders[1]);
	this->_rightarm->setGlobalZOrder(zorders[2]);
	this->_leftarm->setGlobalZOrder(zorders[3]);
	this->_head->setGlobalZOrder(zorders[5]);
	*/

	_currentFrameCount = (_currentFrameCount + 1) % this->_animationConfig->getFrameCount();
}