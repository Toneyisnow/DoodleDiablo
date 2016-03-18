#include "composite_animation_config.h"
#include "pieced_motion_id.h"
#include "..\..\base\ds_types.h"
#include "base\ds_resource_storage.h"

CompositeAnimationConfig* CompositeAnimationConfig::load(CompositeAnimationId * comId)
{
	CompositeAnimationConfig *config = new CompositeAnimationConfig(comId);

	char* filename = new char[255];
	char* pathname = NULL;
	switch (comId->getGenera())
	{
		case AnimationGenera_Missle:
			pathname = DsResourceStorage::path_missles;
			break;
		case AnimationGenera_Monster:
			pathname = DsResourceStorage::path_monsters;
			break;
		case AnimationGenera_Object:
			pathname = DsResourceStorage::path_objects;
			break;
		case AnimationGenera_Character:
			pathname = DsResourceStorage::path_chars;
			break;
		default:
			break;
	}

	sprintf(filename, DsResourceStorage::path_composite_animation_config, pathname, comId->getToken(), comId->toString().c_str());
	config->initFromStorage(filename);

	config->autorelease();

	return config;
}

CompositeAnimationConfig::CompositeAnimationConfig(CompositeAnimationId * aniId)
{
	this->_animationId = aniId;
	this->_animationId->retain();
	_pieceMotionIds = new Vector<PiecedMotionId *>();

}
CompositeAnimationConfig::~CompositeAnimationConfig()
{
	this->_animationId->release();
}

void CompositeAnimationConfig::initFromCof(AnimationGenera g, char* token, AnimationAction action, AnimationFigure figure, const char *filename)
{
	//CompositeAnimationId * aniId = CompositeAnimationId::create(g, token, action, figure);
	//return initFromCof(aniId, filename);
}

void CompositeAnimationConfig::initializeData()
{
	if (_buffer == NULL)
	{
		return;
	}

	// FILE  * in;
	// UBYTE layers, frames_per_dir, directions, c, comp_idx;
	UBYTE c, comp_idx;
	UBYTE* ptr = (UBYTE*)_buffer;
	int   total_frames, i, x, y;
	long  dword;
	char  composit[16][3] = {
			{ "HD" }, { "TR" }, { "LG" }, { "RA" }, { "LA" }, { "RH" }, { "LH" }, { "SH" },
			{ "S1" }, { "S2" }, { "S3" }, { "S4" }, { "S5" }, { "S6" }, { "S7" }, { "S8" }
	};

	int layerindex[16];

	// read it
	_layerCount = *(ptr++);
	_frameCount = *(ptr++);
	_directionCount = *(ptr++);

	// unknown
	for (i = 0; i < 5; i++)
	{
		c = *(ptr++);
	}

	for (i = 0; i < 4; i++)
	{
		for (x = 0; x < 4; x++)
		{
			c = *(ptr++);
		}
		//fseek(in, -4, SEEK_CUR);
		//fread(&dword, 4, 1, in);
	}
	for (i = 0; i < 4; i++)
	{
		c = *(ptr++);
	}

	
	// 9 bytes strings
	for (i = 0; i < _layerCount; i++)
	{
		c = *(ptr++);
		int pieceId = (int)c;
		for (x = 1; x < 5; x++) { c = *(ptr++); }

		int figureCode = 1;
		for (x = 5; x < 8; x++)
		{
			c = *(ptr++);
			int val = (c >= '0' && c <= '9') ? c - '0' : (c >= 'a' && c <= 'z') ? c - 'a' : (c >= 'A' && c <= 'Z') ? c - 'A' : 0;
			figureCode = figureCode * 100 + val;
		}
		c = *(ptr++);

		AnimationFigure figure = AnimationFigure::_HTH;
		switch (figureCode)		// @Toney: This will affect the "1hs" "2hs" etc
		{
			case 1071907: figure = AnimationFigure::_HTH; break;
			case 1010718: figure = AnimationFigure::_1HS; break;
			case 1010719: figure = AnimationFigure::_1HT; break;
			case 1020718: figure = AnimationFigure::_2HS; break;
			case 1020719: figure = AnimationFigure::_2HT; break;
			default: figure = AnimationFigure::_HTH; break;
		}

		AnimationPiece piece = (AnimationPiece)pieceId;
		_pieceMotionIds->insert(i, PiecedMotionId::create(this->_animationId, piece, figure));
	}

	// unknown frames_per_dir data
	for (i = 0; i < _frameCount; i++)
	{
		c = *(ptr++);
	}

	// layers priority
	for (i = 0; i < _directionCount; i++)
	{
		for (x = 0; x < _frameCount; x++)
		{
			int zOrder = 100;
			for (y = 0; y < _layerCount; y++)
			{
				c = *(ptr++);
				int index = (int)c;
				_zOrder[i][x][index] = zOrder++;
				_drawingOrder[i][x][y] = index;
			}
		}
	}

}

int * CompositeAnimationConfig::getLayerZOrders(int direction, int frame)
{
	return _zOrder[direction][frame];
}
int * CompositeAnimationConfig::getDrawingOrders(int direction, int frame)
{
	return _drawingOrder[direction][frame];
}

int CompositeAnimationConfig::getFrameCount()
{
	return _frameCount;
}

int CompositeAnimationConfig::getLayerCount()
{
	return _layerCount;
}

int CompositeAnimationConfig::getDirectionCount()
{
	return _directionCount;
}

Vector<PiecedMotionId *> * CompositeAnimationConfig::getAllPiecedMotions()
{
	return this->_pieceMotionIds;
}

PiecedMotionId * CompositeAnimationConfig::getPiecedMotionId(AnimationPiece piece)
{
	for (Vector<PiecedMotionId *>::iterator pi = _pieceMotionIds->begin(); pi != _pieceMotionIds->end(); pi++)
	{
		if ((*pi)->getPiece() == piece)
		{
			return (*pi);
		}
	}

	return NULL;
}