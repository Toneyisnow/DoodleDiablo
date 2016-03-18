#ifndef _DS_RESOURCE_STORAGE_H_
#define _DS_RESOURCE_STORAGE_H_


#include <cocos2d.h>

USING_NS_CC;

class DsResourceStorage : public Ref
{
private:

public:

	static int load(const char * filename, void ** buffer, long * buf_len);
	static int load_from_file(const char * filename, void ** buffer, long * buf_len);

	static char * path_composite_animation_config;
	static char * path_pieced_animation;

	static char * path_missles;
	static char * path_monsters;
	static char * path_objects;
	static char * path_chars;
	

};


#endif