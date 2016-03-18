#ifndef __CHARACTER_DEFINITION_H_
#define __CHARACTER_DEFINITION_H_


#include <cocos2d.h>


USING_NS_CC;


class CharacterDefinition : public Ref
{

private:

	char * _defId;

public:

	CharacterDefinition();
	~CharacterDefinition();

	static CharacterDefinition * load(char * defId);

	char * getId();


};

#endif