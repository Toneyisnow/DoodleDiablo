
#include "composite_animation.h"
#include "animation_library.h"
#include "pieced_animation_id.h"
#include "base\global_definition.h"
#include "ui\object\composite_object.h"
#include "base\ds_shared_memory.h"

//////////////////////// Static Methods ///////////////////////

int CompositeAnimation::calculateDirection_8(Vec2 dirVector)
{
	float dx = dirVector.x;
	float dy = dirVector.y;
	if (dx < -0.7)
	{
		return 5;
	}
	else if (dx >= -0.7 && dx < -0.3)
	{
		return (dy > 0) ? 1 : 0;
	}
	else if (dx >= -0.3 && dx < 0.3)
	{
		return (dy > 0) ? 6 : 4;
	}
	else if (dx >= 0.3 && dx < 0.7)
	{
		return (dy > 0) ? 2 : 3;
	}
	else
	{
		return 7;
	}
}

int CompositeAnimation::calculateDirection_16(Vec2 dirVector)
{
	return 0;
}

int CompositeAnimation::calculateDirection_32(Vec2 dirVector)
{
	return 0;
}

//////////////////////////////////////////////


CompositeAnimation::CompositeAnimation(CompositeAnimationId* id)
	: CompositeAnimation(id, AnimationLevelHD_LIT, AnimationLevelBody_LIT, AnimationLevelRH_NA, AnimationLevelLH_NA, AnimationLevelSH_NA)
{
}

CompositeAnimation::CompositeAnimation(CompositeAnimationId* id, AnimationLevelHD hd, AnimationLevelBody body, AnimationLevelRH rh, AnimationLevelLH lh, AnimationLevelSH sh)
{
	myreferenceCount = 1;

	this->_animationId = id;

	// By default, set all levels to LIT
	for (int i = 0; i < MaxPieceCount; i++)
	{
		this->_pieceLevel[i] = AnimationLevel::AnimationLevel_LIT;
	}

	AnimationLevel bodyLevel = (AnimationLevel)AnimationLevelBodyConvert[body];

	this->_pieceLevel[Piece_HD] = (AnimationLevel)AnimationLevelHDConvert[hd];
	this->_pieceLevel[Piece_TR] = bodyLevel;
	this->_pieceLevel[Piece_LG] = bodyLevel;
	this->_pieceLevel[Piece_RA] = bodyLevel;
	this->_pieceLevel[Piece_LA] = bodyLevel;
	this->_pieceLevel[Piece_RH] = (AnimationLevel)AnimationLevelRHConvert[rh];
	this->_pieceLevel[Piece_LH] = (AnimationLevel)AnimationLevelLHConvert[lh];
	this->_pieceLevel[Piece_S1] = bodyLevel;
	this->_pieceLevel[Piece_S2] = bodyLevel;
	this->_pieceLevel[Piece_SH] = (AnimationLevel)AnimationLevelSHConvert[sh];

	for (int i = 0; i < MaxDirectionCount; i++)
	{
		this->_compositeAnimation[i] = NULL;
	}
}

CompositeAnimation::~CompositeAnimation()
{
	/// This is temp code to calculate the memory
	
	if (_animationConfig != NULL)
			_animationConfig->release();

	/*
	for (int i = 0; i < _pieceCount; i++)
	{
		if (this->_pieceSprite[i] != NULL)
		{
			this->_pieceSprite[i]->release();
			this->_pieceSprite[i] = NULL;
		}
	}
	*/

	for (int i = 0; i < _directionCount; i++)
	{
		this->_compositeAnimation[i]->release();
	}


}

void CompositeAnimation::initialize()
{
	AnimationLibrary * library = AnimationLibrary::getInstance();

	// Should read from the config
	_animationConfig = AnimationLibrary::getInstance()->retrieveCompositeAnimationConfig(_animationId->getGenera(), _animationId->getToken(), _animationId->getAction(), _animationId->getFigure());
	_allPiecedMotions = _animationConfig->getAllPiecedMotions();
	this->_pieceCount = _allPiecedMotions->size();
	this->_directionCount = _animationConfig->getDirectionCount();
	
	for (int piece = 0; piece < this->_pieceCount; piece++)
	{
		PiecedMotionId * mId = _allPiecedMotions->at(piece);
		AnimationPiece pieceIndex = mId->getPiece();
		_piecedAnimation[pieceIndex] = library->retrievePiecedAnimation(PiecedAnimationId::create(mId, _pieceLevel[pieceIndex]));
	}

	_lastRenderPalette = NULL;


		/*
		Vector<FiniteTimeAction *> actionList(this->_pieceCount + 2);
		int aCount = 0;
		for (int piece = 0; piece < this->_pieceCount; piece++)
		{
			if (piecedAnimation[piece] == NULL)
			{
				continue;
			}

			Animation * ani = piecedAnimation[piece]->getAnimation(direction);
			TargetedAction *targetedAction = TargetedAction::create(this->_pieceSprite[piece], Animate::create(ani));
			actionList.insert(aCount++, targetedAction);
		}
		auto a0 = Repeat::create(Sequence::create(CallFunc::create(CC_CALLBACK_0(CompositeAnimation::callback_0, this)), DelayTime::create(0.1f), nullptr), _animationConfig[action]->getFrameCount());
		actionList.insert(aCount++, a0);

		Spawn *spawn = Spawn::create(actionList);
		this->_compositeAnimationCache[action][direction] = RepeatForever::create(spawn);
		this->_compositeAnimationCache[action][direction]->retain();
		


	this->_pieceType[0] = AnimationPiece::Piece_HD;
	this->_pieceType[1] = AnimationPiece::Piece_TR;
	this->_pieceType[2] = AnimationPiece::Piece_LG;
	this->_pieceType[3] = AnimationPiece::Piece_RA;
	this->_pieceType[4] = AnimationPiece::Piece_LA;

	for (int i = 0; i < _pieceCount; i++)
	{

		this->_pieceSprite[i] = Sprite::create();
		this->_pieceSprite[i]->setAnchorPoint(Vec2(0, 0));
		this->_character->getBaseSprite()->addChild(this->_pieceSprite[i]);
		this->_pieceSprite[i]->retain();
	}

	AnimationAction actions[] = { AnimationAction::Animation_NU, AnimationAction::Animation_A1, AnimationAction::Animation_A2, AnimationAction::Animation_KK };

	for (int aIndex = 0; aIndex < 4; aIndex++)
	{
		_animationConfig[aIndex] = AnimationLibrary::getInstance()->getCompositeAnimationConfig(_character->getCreatureDefinition(), (AnimationAction)aIndex, AnimationFigure::_HTH);
		
		for (int i = 0; i < 16; i++)
		{
			this->_compositeAnimationCache[actions[aIndex]][i] = NULL;
		}
	}
	*/

}

void CompositeAnimation::render(Palette * palette)
{
	if (_lastRenderPalette == palette)
	{
		// Already rendered, just return
		return;
	}

	clear_memory_usage();

	// Combine all of the pieces
	for (int direction = 0; direction < _directionCount; direction++)
	{
		if (this->_compositeAnimation[direction] != NULL)
		{
			this->_compositeAnimation[direction]->release();
			this->_compositeAnimation[direction] = NULL;
		}

		int cDirection = convert_direction(direction, this->_directionCount);

		Vector<SpriteFrame *> spriteFrames;
		Vector<SpriteFrame *> spriteFramesSketch;
		Vector<SpriteFrame *> spriteFramesShadow;
		int frameCount = _piecedAnimation[Piece_TR]->getFrameCount();
		for (int frameIndex = 0; frameIndex < frameCount; frameIndex++)
		{
			int * drawingOrder = _animationConfig->getDrawingOrders(cDirection, frameIndex);
			int xmin = INT_MAX, ymin = INT_MAX, xmax = INT_MIN, ymax = INT_MIN;

			for (int piece = 0; piece < this->_pieceCount; piece++)
			{
				int maxFrame = _piecedAnimation[drawingOrder[piece]]->getFrameCount() - 1;
				DsImage* image = _piecedAnimation[drawingOrder[piece]]->getFrames(direction)->at(MIN(maxFrame, frameIndex));
				Vec2 mpoint = image->getBoxAnchor();
				Size size = image->getOriginalSizeInPixels();
				xmin = (xmin < mpoint.x) ? xmin : mpoint.x;
				ymin = (ymin < mpoint.y) ? ymin : mpoint.y;
				xmax = (xmax > mpoint.x + size.width) ? xmax : mpoint.x + size.width;
				ymax = (ymax > mpoint.y + size.height) ? ymax : mpoint.y + size.height;
			}

			// Draw each of the bit data
			// DsBitMapData * cache = DsBitMapData::create_bitmap(xmax - xmin + 1, ymax - ymin + 1);

			int frameWidth = xmax - xmin + 1;
			int frameHeight = ymax - ymin + 1;
			UBYTE* dataCache = DsSharedMemory::getInstance()->compositeAnimationTempMemory();
			UBYTE* dataCache2 = DsSharedMemory::getInstance()->compositeAnimationTempMemory2();
			memset(dataCache, 0, sizeof(UBYTE) * frameWidth * frameHeight * 2);
			memset(dataCache2, 0, sizeof(UBYTE) * frameWidth * frameHeight);

			for (int piece = 0; piece < this->_pieceCount; piece++)
			{
				// Visit the pieces according to the order
				DsImage* image = _piecedAnimation[drawingOrder[piece]]->getFrames(direction)->at(frameIndex);
				image->resetReader();
				Vec2 mpoint = image->getBoxAnchor();
				Size size = image->getOriginalSizeInPixels();
				for (int j = 0; j < size.height; j++)
				{
					for (int i = 0; i < size.width; i++)
					{
						int colorIndex = (UBYTE)image->readNext();
						if (colorIndex != 0)
						{
							RGB clr = palette->getColor(colorIndex);
							int index = mpoint.x - xmin + i + frameWidth * (mpoint.y - ymin + j);
							dataCache[index * 2] = (UBYTE)((clr.b / 16) * 16 + 15);
							dataCache[index * 2 + 1] = (UBYTE)((clr.r / 16) * 16 + (clr.g / 16));

							dataCache2[index] = (UBYTE)(255);
						}
					}
				}
			}

			Texture2D * texture = new Texture2D();
			texture->initWithData(dataCache, sizeof(UBYTE) * frameWidth * frameHeight * 2, kCCTexture2DPixelFormat_RGBA4444, frameWidth, frameHeight, Size(frameWidth, frameHeight));
			SpriteFrame * frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, frameWidth, frameHeight));
			frame->setOffsetInPixels(Vec2(xmin, 1 - ymin - frameHeight));
			texture->release();
			spriteFrames.pushBack(frame);

			Texture2D * texture2 = new Texture2D();
			texture2->initWithData(dataCache2, sizeof(UBYTE) * frameWidth * frameHeight, kCCTexture2DPixelFormat_A8, frameWidth, frameHeight, Size(frameWidth, frameHeight));
			SpriteFrame * frame2 = SpriteFrame::createWithTexture(texture2, Rect(0, 0, frameWidth, frameHeight));
			frame2->setOffsetInPixels(Vec2(xmin, 1 - ymin - frameHeight));
			texture2->release();
			spriteFramesSketch.pushBack(frame2);

			// Adding the real shadow
			UBYTE* dataCache3 = DsSharedMemory::getInstance()->compositeAnimationTempMemory();
			/*
			int shadowButtom = (ymax > 0) ? 0 : ymax;
			int shadowHeight = (shadowButtom - ymin) / 2;
			int shadowWidth = frameWidth - ymin / 2;
			memset(dataCache3, 0, sizeof(UBYTE) * shadowHeight * shadowWidth);
			int index = 0;
			for (int j = 0; j < shadowHeight; j++)
			{
				for (int i = 0; i < shadowWidth; i++)
				{
					if (i <= j || i >= j + frameWidth)
					{
						dataCache3[index++] = 0;
					}
					else
					{
						dataCache3[index++] = dataCache2[j * 2 * frameWidth + i - j];
					}
				}
			}
			*/
			int shadowButtom = ymax;
			int shadowHeight = (shadowButtom - ymin + 1) / 2;		// NOTE: +1 here is to make sure the Height is not zero
			int shadowWidth = frameWidth - ymin / 2;
			memset(dataCache3, 0, sizeof(UBYTE) * shadowHeight * shadowWidth);
			int index = 0;
			for (int j = 0; j < shadowHeight; j++)
			{
				for (int i = 0; i < shadowWidth; i++)
				{
					if (i <= j || i >= j + frameWidth)
					{
						dataCache3[index++] = 0;
					}
					else
					{
						dataCache3[index++] = dataCache2[j * 2 * frameWidth + i - j];
					}
				}
			}

			Texture2D * texture3 = new Texture2D();
			texture3->initWithData(dataCache3, sizeof(UBYTE) * shadowWidth * shadowHeight, kCCTexture2DPixelFormat_A8, shadowWidth, shadowHeight, Size(shadowWidth, shadowHeight));
			SpriteFrame * frame3 = SpriteFrame::createWithTexture(texture3, Rect(0, 0, shadowWidth, shadowHeight));
			frame3->setOffsetInPixels(Vec2(xmin + ymin / 2, - shadowButtom));
			texture3->release();
			spriteFramesShadow.pushBack(frame3);

			// Add memory statistic
			claim_memory_usage(sizeof(UBYTE) * frameWidth * frameHeight * 3);
			claim_memory_usage(sizeof(UBYTE) * shadowHeight * shadowWidth);
		}

		this->_compositeAnimation[direction] = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
		this->_compositeAnimation[direction]->retain();

		this->_compositeSketchAnimation[direction] = Animation::createWithSpriteFrames(spriteFramesSketch, 0.1f);
		this->_compositeSketchAnimation[direction]->retain();

		this->_compositeShadowAnimation[direction] = Animation::createWithSpriteFrames(spriteFramesShadow, 0.1f);
		this->_compositeShadowAnimation[direction]->retain();
	}

	log("Render animation completed. Memory Used: %dKB.", get_memory_used() / 1024);
	_lastRenderPalette = palette;
}

int CompositeAnimation::getDirectionCount()
{
	return _directionCount;
}

Animation* CompositeAnimation::getAnimation(int direction)
{
	return this->_compositeAnimation[direction];
}

Animation* CompositeAnimation::getSketchAnimation(int direction)
{
	return this->_compositeSketchAnimation[direction];
}

Animation* CompositeAnimation::getShadowAnimation(int direction)
{
	return this->_compositeShadowAnimation[direction];
}


int CompositeAnimation::calculateDirection(Vec2 dirVector)
{
	return calculateDirection_8(dirVector) % _directionCount;
}

/*
void CompositeAnimation::updateFromCache()
{
	_currentFrameCount = 0;
	int direction = this->_character->getDirection();
	AnimationAction action = calculateAnimationAction();
	_currentAnimationConfig = this->_animationConfig[action];

	this->_character->getBaseSprite()->stopAllActions();
	this->_character->getBaseSprite()->runAction(this->_compositeAnimationCache[action][direction]);
}
*/

/// Refresh the current animation according to character's status/direction/equipment/gesture
void CompositeAnimation::refresh()
{
	//reloadAnimationForAllActions();
	//updateFromCache();
}


/*
void CompositeAnimation::reloadAnimationForAllActions()
{
	AnimationLibrary * library = AnimationLibrary::getInstance();
	AnimationAction actions[] = { AnimationAction::Animation_NU, AnimationAction::Animation_A1, AnimationAction::Animation_A2, AnimationAction::Animation_KK };
	
	for (int index = 0; index < 4; index++)
	{
		AnimationAction action = (AnimationAction)actions[index];

		_animationConfig[action] = AnimationLibrary::getInstance()->getCompositeAnimationConfig(_character->getCreatureDefinition(), action, calculateAnimationFigure());

		DirectedAnimation * piecedAnimation[16];
		for (int piece = 0; piece < this->_pieceCount; piece++)
		{
			PiecedMotionId * mId = _animationConfig[action]->getPiecedMotionId(this->_pieceType[piece]);
			piecedAnimation[piece] = library->getPiecedAnimation(PiecedAnimationId::create(mId, getEquipLevel(this->_pieceType[piece])));
		}

		for (int direction = 0; direction < _directionCount; direction++)
		{
			if (this->_compositeAnimationCache[action][direction] != NULL)
			{
				this->_compositeAnimationCache[action][direction]->release();
				this->_compositeAnimationCache[action][direction] = NULL;
			}

			Vector<FiniteTimeAction *> actionList(this->_pieceCount + 2);
			int aCount = 0;
			for (int piece = 0; piece < this->_pieceCount; piece++)
			{
				if (piecedAnimation[piece] == NULL)
				{
					continue;
				}

				Animation * ani = piecedAnimation[piece]->getAnimation(direction);
				TargetedAction *targetedAction = TargetedAction::create(this->_pieceSprite[piece], Animate::create(ani));
				actionList.insert(aCount++, targetedAction);
			}
			auto a0 = Repeat::create(Sequence::create(CallFunc::create(CC_CALLBACK_0(CompositeAnimation::callback_0, this)), DelayTime::create(0.1f), nullptr), _animationConfig[action]->getFrameCount());
			actionList.insert(aCount++, a0);

			Spawn *spawn = Spawn::create(actionList);
			this->_compositeAnimationCache[action][direction] = RepeatForever::create(spawn);
			this->_compositeAnimationCache[action][direction]->retain();
		}
	}
}
*/

AnimationAction CompositeAnimation::calculateAnimationAction()
{
	return AnimationAction::Animation_NU;
	/*
	switch (this->_character->getAction())
	{
		case CreatureAction::Action_A1:
			return (rand() % 2 == 0) ? AnimationAction::Animation_A1 : AnimationAction::Animation_A2;
		case CreatureAction::Action_WL:
			return AnimationAction::Animation_WL;
		case CreatureAction::Action_RN:
			return AnimationAction::Animation_RN;
		case CreatureAction::Action_KK:
			return AnimationAction::Animation_KK;
		default:
			return AnimationAction::Animation_NU;
	}
	*/
}

AnimationFigure CompositeAnimation::calculateAnimationFigure()
{
	return AnimationFigure::_1HS;
}

AnimationLevel CompositeAnimation::getEquipLevel(AnimationPiece p)
{
	switch (p)
	{
	case AnimationPiece::Piece_HD: return getHDEquipLevel(); break;
	case AnimationPiece::Piece_TR: return getTREquipLevel(); break;
	case AnimationPiece::Piece_LG: return getLGEquipLevel(); break;
	}
	return AnimationLevel::AnimationLevel_LIT;
}

AnimationLevel CompositeAnimation::getHDEquipLevel()
{
	// Return the string of HD level according to the current equipment
	return AnimationLevel::AnimationLevel_HLM;
}
AnimationLevel CompositeAnimation::getTREquipLevel()
{
	// Return the string of HD level according to the current equipment
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getLGEquipLevel()
{
	// Return the string of HD level according to the current equipment
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getLAEquipLevel()
{
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getRAEquipLevel()
{
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getLHEquipLevel()
{
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getRHEquipLevel()
{
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getSHEquipLevel()
{
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getS1EquipLevel()
{
	return AnimationLevel::AnimationLevel_HVY;
}
AnimationLevel CompositeAnimation::getS2EquipLevel()
{
	return AnimationLevel::AnimationLevel_HVY;
}

void CompositeAnimation::callback_0()
{
	int cDirection = 0;
	
	/*
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
	*/

	//cDirection = 14;	// if direction = 3
	//cDirection = 9;	// if direction = 1
	//cDirection = 10;	// if direction = 2
	//cDirection = 2;	// if direction = 4

	/*
	cDirection = (cDirection + 8) % 16;

	int * zorders = this->_currentAnimationConfig->getLayerZOrders(cDirection, _currentFrameCount);

	log("direction: %d frame: %d zorders : head %d, body %d, leg %d, ra %d, la %d", cDirection, _currentFrameCount, zorders[0], zorders[1], zorders[2], zorders[3], zorders[4]);

	for (int layer = 0; layer < 5; layer++)
	{
		int zOrder = zorders[this->_pieceType[layer]];
		this->_pieceSprite[layer]->setGlobalZOrder(zOrder);
	}
	*/

	/*
	
	this->_head->setGlobalZOrder(zorders[0]);
	this->_body->setGlobalZOrder(zorders[1]);
	this->_leg->setGlobalZOrder(zorders[2]);
	this->_rightarm->setGlobalZOrder(zorders[3]);
	this->_leftarm->setGlobalZOrder(zorders[4]);
	this->_leg->setGlobalZOrder(zorders[0]);
	this->_body->setGlobalZOrder(zorders[1]);
	this->_rightarm->setGlobalZOrder(zorders[2]);
	this->_leftarm->setGlobalZOrder(zorders[3]);
	this->_head->setGlobalZOrder(zorders[5]);
	*/

	/// _currentFrameCount = (_currentFrameCount + 1) % this->_currentAnimationConfig->getFrameCount();
}

int CompositeAnimation::convert_direction(int direction, int totaldirection)
{
	int cDirection = 0;

	if (totaldirection == 16)
	{
		switch (direction)
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

		cDirection = (cDirection + 8) % 16;

		return cDirection;
	}
	else if (totaldirection == 8)
	{
		return direction;
	}

	return direction;
}
