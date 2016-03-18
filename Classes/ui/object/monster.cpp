#include "monster.h"

AnimationGenera Monster::getGenera()
{
	return AnimationGenera::AnimationGenera_Monster;
}

Monster::Monster(char * token)
	: CompositeObject(token)
{

}

