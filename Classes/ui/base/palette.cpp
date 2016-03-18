
#include "palette.h"
#include "..\..\base\ds_types.h"
#include "base\ds_resource_storage.h"

Palette* Palette::loadForAct(int actNum)
{
	char paletteFullFile[50];
	sprintf(paletteFullFile, "data\\global\\palette\\ACT%d\\pal.DAT", actNum);

	Palette* p = new Palette();
	p->initFromStorage(paletteFullFile);

	p->autorelease();

	return p;
}

Palette::Palette()
{


}

void Palette::initializeData()
{
	UBYTE* ptr = (UBYTE*)_buffer;
	for (int i = 0; i<256; i++)
	{
		rgb[i].b = (*ptr);
		ptr++;
		rgb[i].g = (*ptr);
		ptr++;
		rgb[i].r = (*ptr);
		ptr++;
	}
}
/*
Palette::Palette(void* buffer)
{
	UBYTE* ptr = (UBYTE*)buffer;
	for (int i = 0; i<256; i++)
	{
		rgb[i].b = (*ptr);
		ptr++;
		rgb[i].g = (*ptr);
		ptr++;
		rgb[i].r = (*ptr);
		ptr++;
	}
}
*/

Palette::~Palette()
{

}

RGB Palette::getColor(int index) const 
{
	return rgb[index];
}