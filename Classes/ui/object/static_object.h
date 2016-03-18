#ifndef _STATIC_OBJECT_H_
#define _STATIC_OBJECT_H_


#include <cocos2d.h>
#include "composite_object.h"
#include "static_object_label.h"

USING_NS_CC;

class StaticObject : public CompositeObject
{
private:

	int _act;
	long _type;
	long _id;
	long _ds1_flags;

	int _unique_object_id;

	Vec2 _subtile_position;

	////PATH_S      path[WINDS1EDIT_PATH_MAX];
	long        _path_num;
	int         _desc_idx;
	int         _flags;

	// random starting animation frame
	UBYTE       _frame_delta;


	StaticObjectLabel * _label;


public:

	StaticObject(int act, long type, long id, Vec2 pos);
	virtual ~StaticObject();

	virtual AnimationGenera getGenera() override;
	Vec2 getSubtilePosition();

	long getId();

	void setType(long t);
	void setId(long id);
	void setSubtilePosition(Vec2 subtilepos);

	void setDsFlags(long flags);

};


#endif