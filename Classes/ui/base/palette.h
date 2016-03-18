#ifndef _PALETTE_H_
#define _PALETTE_H_


#include <cocos2d.h>
#include "base\ds_resource_object.h"

USING_NS_CC;

typedef struct RGB
{
	unsigned char r, g, b;
	unsigned char filler;
} RGB;

#define PAL_SIZE 256



class Palette : public DsResourceObject
{
private:

	RGB rgb[PAL_SIZE];

public:

	static Palette* loadForAct(int actNum);

	Palette();
	//Palette(void* buffer);
	~Palette();

	void initializeData();

	RGB getColor(int index) const;

};


#endif