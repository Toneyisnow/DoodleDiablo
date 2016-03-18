#ifndef _DS_TILE_MAP_H_
#define _DS_TILE_MAP_H_

#include "base\ds_types.h"
#include "base\ds_structs.h"
#include "base\ds_resource_object.h"
#include "ui\base\ds_bitmap.h"
#include "ds_tile_image.h"

/*
typedef struct SUB_TILE_S
{
	DS_WORD  x_pos;
	DS_WORD  y_pos;
	//   WORD  unknown1;
	int   x_grid;
	int   y_grid;
	DS_WORD  format;
	long  length;
	//   WORD  unknown2;
	long  data_offset;
} SUB_TILE_S;
*/

static const char* TILE_MAP_RELATIVE_PATH = "data\\global\\tiles\\";

class DsTileMap : public DsResourceObject
{

private:

	static const int MAX_TILE_MAP_IMAGE = 512;

	char* _filename;
	int _imageCount;
	DsTileImage *_blocks[MAX_TILE_MAP_IMAGE];

	bool _hasRendered;

	

public:

	static DsTileMap* load(const char * filename);
	
	DsTileMap(const char * filename);
	DsTileMap();
	~DsTileMap();

	//void init_from_buffer(void * buffer);
	void initializeData();

	///void draw_sub_tile_isometric(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length);
	///void draw_sub_tile_normal(DsBitMapData * dst, int x0, int y0, UBYTE * data, int length);

	void debug();
	DsTileImage * getBlock(int index);
	int getBlockCount();

	// int        ds1_usage; // current number of ds1 using this dt1
	// all blocks in differents zoom format
	// DsBitMapData     * block_zoom[ZM_MAX]; // ZM_MAX tables of table of pointers

	//   to BITMAP
	//int        bz_size[ZM_MAX];


	//static int ZM_MAX;
	//static int FILE_MAX;


	char       name[80];

	//void       * buffer;
	//long       buff_len;
	// block headers : block_num structs of BLOCK_S
	//void * bh_buffer;
	//int        bh_buff_len;
	
	long       x1; // signature (7)
	long       x2; // signature (6)
	long       block_num;
	long       bh_start;


	
	///static DsTileMap *dt1_read(const char * fullfilename, bool isSpecial);

	//static DsTileMap* load_from_mod_file(const char * filename);
	//static DsTileMap* load_from_mpq(const char * filename);

	
	void render(const Palette * pal);
	bool hasRendered();

	///Texture2D * getTileTexture(int index);

	//void dt1_fill_subt(SUB_TILE_S * ptr, long tiles_ptr, int s);
	//void dt1_zoom(DsBitMapData * src, int b, int z);
	//void dt1_all_zoom_make();


	//void increase_ds1_usage();
	//void decrease_ds1_usage();
	//bool no_longer_used();


};

#endif
