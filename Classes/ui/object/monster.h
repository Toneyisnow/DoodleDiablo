#ifndef __MONSTER_H_
#define __MONSTER_H_


#include <cocos2d.h>
#include "composite_object.h"

USING_NS_CC;

class Monster : public CompositeObject
{
private:

public:

	Monster(char * token);

	AnimationGenera getGenera();


};


#endif