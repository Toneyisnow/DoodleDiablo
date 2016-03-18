

#include "base\ds_resource_storage.h"
#include "dcc_decoder.h"
#include "animation_library.h"
#include "composite_animation_config.h"
#include "definition\definition_library.h"

AnimationLibrary *AnimationLibrary::_instance = NULL;



AnimationLibrary * AnimationLibrary::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new AnimationLibrary();
	}

	return _instance;
}

AnimationLibrary::AnimationLibrary()
{
	this->_characterAniDictionary = new Map<std::string, DirectedAnimation*>();
	this->_compositeAnimations = new Map<std::string, CompositeAnimation*>();
	this->_compositeAnimationConfigs = new Map<std::string, CompositeAnimationConfig*>();
	this->_pieceAnimations = new Map<std::string, DirectedAnimation*>();

	this->_paletteManager = new DsResourceManager();
	this->_tileMapManager = new DsResourceManager();
	this->_sceneManager = new DsResourceManager();

}

AnimationLibrary::~AnimationLibrary()
{
	this->_characterAniDictionary->clear();
	this->_compositeAnimations->clear();
	this->_compositeAnimationConfigs->clear();
	this->_pieceAnimations->clear();

	this->_tileMapManager->release();
	this->_sceneManager->release();

}

void AnimationLibrary::recycle()
{
	std::string key;
	for (Map<std::string, CompositeAnimation*>::const_iterator iter = _compositeAnimations->begin(); iter != _compositeAnimations->end(); iter++)
	{
		CompositeAnimation *ani = iter->second;
		if (ani->myreferenceCount <= 0)
		{
			key = iter->first;
			log("Recycling for key %s", key);
			break;
		}
	}

	_compositeAnimations->erase(key);

	//_pieceAnimations->clear();
}

void AnimationLibrary::loadResources()
{
	_defaultPalette = retrievePalette(1);
	_defaultPalette->retain();

	// this->loadCompositeAnimationConfig(CreatureDefinition::Creature_BA, AnimationAction::Animation_A1, AnimationFigure::_1HS);
	//this->loadCompositeAnimationConfig(CreatureDefinition::Creature_BA, AnimationAction::Animation_A2, AnimationFigure::_1HS);
	//this->loadCompositeAnimationConfig(CreatureDefinition::Creature_BA, AnimationAction::Animation_NU, AnimationFigure::_1HS);
	//this->loadCompositeAnimationConfig(CreatureDefinition::Creature_BA, AnimationAction::Animation_KK, AnimationFigure::_1HS);

	/*
	this->loadCharacterComponentAnimation("BA", "HD", "1HS", "A2", "HLM");
	this->loadCharacterComponentAnimation("BA", "HD", "1HS", "A2", "MSK");
	this->loadCharacterComponentAnimation("BA", "TR", "1HS", "A2", "HVY");
	this->loadCharacterComponentAnimation("BA", "LG", "1HS", "A2", "HVY");
	this->loadCharacterComponentAnimation("BA", "LA", "1HS", "A2", "HVY");
	this->loadCharacterComponentAnimation("BA", "RA", "1HS", "A2", "HVY");
	this->loadCharacterComponentAnimation("BA", "RA", "1HS", "A2", "LIT");
	
	this->loadCharacterComponentAnimation("BA", "HD", "1HS", "KK", "HLM");
	this->loadCharacterComponentAnimation("BA", "HD", "1HS", "KK", "MSK");
	this->loadCharacterComponentAnimation("BA", "TR", "1HS", "KK", "HVY");
	this->loadCharacterComponentAnimation("BA", "LG", "1HS", "KK", "HVY");
	this->loadCharacterComponentAnimation("BA", "LA", "1HS", "KK", "HVY");
	this->loadCharacterComponentAnimation("BA", "RA", "1HS", "KK", "HVY");
	this->loadCharacterComponentAnimation("BA", "RA", "1HS", "KK", "LIT");
	*/

}

void AnimationLibrary::loadResources2()
{
	this->loadCompositeAnimationConfig(CreatureDefinition::Creature_BA, AnimationAction::Animation_A2, AnimationFigure::_1HS);
	this->loadCompositeAnimationConfig(CreatureDefinition::Creature_BA, AnimationAction::Animation_NU, AnimationFigure::_1HS);
	this->loadCompositeAnimationConfig(CreatureDefinition::Creature_BA, AnimationAction::Animation_KK, AnimationFigure::_1HS);

}
void AnimationLibrary::loadCompositeAnimationConfig(CreatureDefinition creatureDef, AnimationAction action, AnimationFigure figure)
{
	/*
	CompositeAnimationId * comId = CompositeAnimationId::create(creatureDef, action, figure);
	std::string key = comId->toString();

	if (this->_compositeAnimationConfigs->at(key) != NULL)
	{
		return;
	}

	char * filename = new char[255];
	sprintf(filename, "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\d2char\\data\\global\\CHARS\\%s\\COF\\%s.cof", CreatureDefinitionStrings[creatureDef], key.c_str());

	CompositeAnimationConfig *config = new CompositeAnimationConfig();
	config->initFromCof(comId, filename);
	this->_compositeAnimationConfigs->insert(key, config);

	// Foreach of the Piece animations in this config, load it from file
	Vector<PiecedMotionId *> *piecedMotions = config->getAllPiecedMotions();
	int count = 0;
	for (Vector<PiecedMotionId *>::iterator p = piecedMotions->begin(); p != piecedMotions->end(); p++)
	{
		if (count++ > 5)
			break;

		Vector<PiecedAnimationId *>* piecedAnimations = PiecedAnimationId::retrieveAllByPiecedMotion(*p);
		for (Vector<PiecedAnimationId *>::iterator pA = piecedAnimations->begin(); pA != piecedAnimations->end(); pA++)
		{
			PiecedAnimationId *pAnimationId = *pA;
			this->loadPiecedAnimation(pAnimationId);
		}
		piecedAnimations->clear();
	}

	config->release();

	*/
}

Palette* AnimationLibrary::retrievePalette(int actId)
{
	char key[2];
	itoa(actId, key, 10);

	if (!_paletteManager->contains(key))
	{
		Palette* pal = Palette::loadForAct(actId);
		_paletteManager->insert(key, pal);
	}

	return (Palette*)(_paletteManager->load(key));
}

CompositeAnimation* AnimationLibrary::retrieveCompositeAnimation(CompositeAnimationId* comId, AnimationLevelHD hd, AnimationLevelBody body, AnimationLevelRH rh, AnimationLevelLH lh, AnimationLevelSH sh)
{
	char key[100];
	sprintf(key, "%s-%s", comId->toString().c_str(), PiecedAnimationId::getFullPieceLevelStrings(hd, body, rh, lh, sh).c_str());

	if (_compositeAnimations->at(key) == NULL)
	{
		// Load that animation
		CompositeAnimation* animation = new CompositeAnimation(comId, hd, body, rh, lh, sh);
		animation->initialize();
		_compositeAnimations->insert(key, animation);

		animation->release();
	}

	return _compositeAnimations->at(key);
}

CompositeAnimationConfig* AnimationLibrary::retrieveCompositeAnimationConfig(AnimationGenera g, char* token, AnimationAction action, AnimationFigure figure)
{
	CompositeAnimationId * comId = CompositeAnimationId::create(g, token, action, figure);
	std::string key = comId->toString();

	if (this->_compositeAnimationConfigs->at(key) == NULL)
	{
		CompositeAnimationConfig* config = CompositeAnimationConfig::load(comId);
		this->_compositeAnimationConfigs->insert(key, config);
	}

	return this->_compositeAnimationConfigs->at(key);
}

DsTileMap* AnimationLibrary::retrieveTileMap(const char* filename)
{
	std::string key = filename;
	if (!this->_tileMapManager->contains(key))
	{
		DsTileMap* map = DsTileMap::load(filename);
		this->_tileMapManager->insert(key, map);
	}

	return (DsTileMap*)(this->_tileMapManager->load(key));
}

DsScene* AnimationLibrary::retrieveScene(int stageId, int indexId)
{
	ExcelDefinition * levelPrest = DefinitionLibrary::getInstance()->getLevelPrestDefinition(stageId);
	char * ds1name = levelPrest->getStringValue(LevelPrestDefinition::getFileIndex(indexId));

	int typeId = 0;
	if (stageId <= 3)
		typeId = 1;
	else if (stageId <= 23)
		typeId = 2;
	else if (stageId <= 25)
		typeId = 3;
	else if (stageId <= 107)
		typeId = 4;
	else if (stageId <= 107)
		typeId = 5;
	else if (stageId == 481)
		typeId = 17;
	else if (stageId == 301)
		typeId = 12;
	else if (stageId == 529)
		typeId = 20;
	else if (stageId <= 798)
		typeId = 26;
	else if (stageId <= 835)
		typeId = 27;
	else if (stageId <= 848)
		typeId = 28;
	else if (stageId <= 862)
		typeId = 26;

	std::string key = ds1name;
	if (!this->_sceneManager->contains(key))
	{
		DsScene* scene = DsScene::load(ds1name, stageId, typeId);
		this->_sceneManager->insert(key, scene);
	}

	return (DsScene*)(this->_sceneManager->load(key));
}

DirectedAnimation* AnimationLibrary::retrievePiecedAnimation(PiecedAnimationId *pId)
{
	std::string key = pId->toString();
	if (this->_pieceAnimations->at(key) == NULL)
	{
		//char* filename = new char[255];
		//char* pathname = getRootPath(pId->getCompositeId()->getGenera());

		//sprintf(filename, "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\d2char\\data\\global\\CHARS\\%s\\%s\\%s.dcc", CreatureDefinitionStrings[pId->getCreature()], AnimationPieceStrings[pId->getPiece()], key.c_str());
		//sprintf(filename, "%s%s\\%s\\%s.dcc", pathname, pId->getCompositeId()->getToken(), AnimationPieceStrings[pId->getPiece()], key.c_str());
		
		DirectedAnimation* directedAnimation = DirectedAnimation::load(pId);
		//DirectedAnimation *directedAnimation = new DirectedAnimation();
		//directedAnimation->loadFromDcc(filename, _defaultPalette);

		this->_pieceAnimations->insert(key, directedAnimation);
		directedAnimation->release();

		//delete(filename);
		//delete(pathname);
	}

	return this->_pieceAnimations->at(key);
}

void AnimationLibrary::loadCharacterComponentAnimation(const char * charDefId, const char * component, const char * figure, const char * action, const char * level)
{
	std::string key = generateKey(charDefId, component, figure, action, level);
	if (this->_characterAniDictionary->at(key) != NULL)
	{
		return;
	}
	
	DCC_S * dcc_ptr;
	DccDecoder * decoder = new DccDecoder();
	Texture2D *texture = new Texture2D();
	Color4B Data[255 * 255];

	char * filename = new char[255];
	sprintf(filename, "D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\%s\\%s\\%s.dcc", charDefId, component, key.c_str());
	dcc_ptr = decoder->dcc_disk_load(filename);
	decoder->dcc_decode(dcc_ptr, -1);

	int nb_frame = dcc_ptr->header.frames_per_dir;
	DirectedAnimation *directedAnimation = NULL; // new DirectedAnimation();

	for (int d = 0; d < dcc_ptr->header.directions; d++)
	{
		Vector<SpriteFrame*> animFrames(nb_frame);
		DCC_DIRECTION_S direction = dcc_ptr->direction[d];
		for (int f = 0; f < nb_frame; f++)
		{
			DCC_FRAME_S frame = dcc_ptr->frame[d][f];
			int width = frame.bmp->getWidth();
			int height = frame.bmp->getHeight();
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					UBYTE b = frame.bmp->getByte(i, j);
					int index = j * width + i;
					if (b != 0)
					{
						int colorIndex = (int)b;
						if (colorIndex < 256 && colorIndex >= 0)
						{
							RGB clr = _defaultPalette->getColor(colorIndex);
							Data[index] = Color4B(clr.r * 4, clr.g * 4, clr.b * 4, 255);
						}
						else
						{
							Data[index] = Color4B(0, 0, 0, 0);
						}
					}
					else
					{
						Data[index] = Color4B(0, 0, 0, 0);
					}
				}
			}

			texture = new Texture2D();
			texture->initWithData(Data, sizeof(Color4B) * width * height, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(width, height));

			SpriteFrame * sf = SpriteFrame::createWithTexture(texture, Rect(0, 0, width, height));
			sf->setOffsetInPixels(Vec2(direction.box.xmin, -direction.box.ymax));

			animFrames.pushBack(sf);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
		directedAnimation->setAnimation(d, animation);
	}

	decoder->dcc_destroy(dcc_ptr);

	this->_characterAniDictionary->insert(key, directedAnimation);
}

CompositeAnimationConfig * AnimationLibrary::getCompositeAnimationConfig(CreatureDefinition creatureDef, AnimationAction action, AnimationFigure figure)
{
	return NULL;
}

//
// Sample: BA   HD   1HS   MSK   A1   1
// 
Animation * AnimationLibrary::getCharacterComponentAnimation(const char * charDefId, const char * component, const char * figure, const char * action, const char * level, int direction)
{
	std::string key = generateKey(charDefId, component, figure, action, level);
	if (this->_characterAniDictionary->at(key) == NULL)
	{
		return NULL;
	}

	DirectedAnimation * dAni = this->_characterAniDictionary->at(key);
	///return dAni->getAnimation(direction);

	return NULL;
}


std::string AnimationLibrary::generateKey(const char * charDefId, const char * component, const char * figure, const char * action, const char * level)
{
	char * key = new char[255];
	sprintf(key, "%s%s%s%s%s", charDefId, component, level, action, figure);

	if (strcmp(key, "BAHDHLMKK1HS") == 0)
	{
		key = "BAHDHLMKKHTH";
	}
	if (strcmp(key, "BAHDMSKKK1HS") == 0)
	{
		key = "BAHDMSKKKHTH";
	}
	if (strcmp(key, "BALGHVYKK1HS") == 0)
	{
		key = "BALGHVYKKHTH";
	}
	if (strcmp(key, "BATRHVYKK1HS") == 0)
	{
		key = "BATRHVYKKHTH";
	}
	if (strcmp(key, "BALAHVYKK1HS") == 0)
	{
		key = "BALAHVYKKHTH";
	}


	return key;
}

char* AnimationLibrary::getRootPath(AnimationGenera g)
{
	// char* pathname = new char[255];
	switch (g)
	{
	case AnimationGenera_Missle:
		return DsResourceStorage::path_missles;
	case AnimationGenera_Monster:
		return DsResourceStorage::path_monsters;
	case AnimationGenera_Object:
		return DsResourceStorage::path_objects;
	case AnimationGenera_Character:
		return DsResourceStorage::path_chars;
	default:
		break;
	}
	
	return NULL;
}
