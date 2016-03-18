#ifndef _STATIC_OBJECT_LABEL_H_
#define _STATIC_OBJECT_LABEL_H_


#include <cocos2d.h>

USING_NS_CC;

class StaticObjectLabel : public Ref
{
private:

	int rx, ry; // upper/left corner of the label, relative to the sub-cell
	// (in pixels, at zoom of 1:1)
	int w, h;   // width & height (pixels)
	int x0, y0; // pixels position on screen
	int flags;

	// for moving
	int old_rx;
	int old_ry;

public:

	StaticObjectLabel();
	virtual ~StaticObjectLabel();


};


#endif