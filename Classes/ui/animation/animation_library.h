#ifndef __ANIMATION_LIBRARY_H_
#define __ANIMATION_LIBRARY_H_

#include <stdlib.h>
#include <string.h>
#include <cocos2d.h>
#include "base\ds_structs.h"
#include "base\global_definition.h"
#include "base\ds_resource_manager.h"
#include "directed_animation.h"
#include "composite_animation_config.h"
#include "pieced_animation_id.h"
#include "composite_animation.h"
#include "ui\tilemap\ds_tile_map.h"
#include "ui\tilemap\ds_scene.h"

USING_NS_CC;

class AnimationLibrary : public Ref
{

private:

	Map<std::string, DirectedAnimation*> * _characterAniDictionary;
	
	Map<std::string, CompositeAnimation*> * _compositeAnimations;
	Map<std::string, CompositeAnimationConfig*> * _compositeAnimationConfigs;
	Map<std::string, DirectedAnimation*> * _pieceAnimations;

	DsResourceManager* _paletteManager;
	DsResourceManager* _tileMapManager;
	DsResourceManager* _sceneManager;

	std::string generateKey(const char * charDefId, const char * component, const char * figure, const char * action, const char * level);

	AnimationLibrary();
	
	static AnimationLibrary * _instance;

	Palette * _defaultPalette;

public:

	static AnimationLibrary * getInstance();
	~AnimationLibrary();

	void loadResources();
	void loadResources2();

	static char* getRootPath(AnimationGenera g);

	Palette* retrievePalette(int actId);
	DsTileMap* retrieveTileMap(const char* filename);
	DsScene*  retrieveScene(int stageId, int indexId);
	CompositeAnimation* retrieveCompositeAnimation(CompositeAnimationId* comId, AnimationLevelHD hd, AnimationLevelBody tr, AnimationLevelRH rh, AnimationLevelLH lh, AnimationLevelSH sh);
	CompositeAnimationConfig* retrieveCompositeAnimationConfig(AnimationGenera g, char* token, AnimationAction action, AnimationFigure figure);
	DirectedAnimation* retrievePiecedAnimation(PiecedAnimationId *aniId);

	void recycle();





	void loadCompositeAnimationConfig(CreatureDefinition creatureDef, AnimationAction action, AnimationFigure figure);
	CompositeAnimationConfig* getCompositeAnimationConfig(CreatureDefinition creatureDef, AnimationAction action, AnimationFigure figure);

	void loadCharacterComponentAnimation(const char * charDefId, const char * component, const char * figure, const char * action, const char * level);
	Animation* getCharacterComponentAnimation(const char * charDefId, const char * component, const char * figure, const char * action, const char * level, int direction);


	void loadCharacterAnimation(const char * charDefId, const char * figure, const char * action);


};

#endif