#ifndef _DS_SCENE_H_
#define _DS_SCENE_H_

#include <stdio.h>
#include <string.h>
#include "ds_tile_map.h"
#include "ds_tile_layer.h"
#include "base/ds_resource_object.h"
#include "ui/object/static_object.h"
static const char* SCENE_RELATIVE_PATH = "data\\global\\tiles\\";
static const int DT1_IN_DS1_MAX = 33;

class DsScene : public DsResourceObject
{
private:

	Palette* _defaultPalette;

	int _stageId;
	int _typeId;

	// from file
	long          _version;
	long          _tag_type;
	long          _width;    // from file, +1
	long          _height;   // from file, +1
	long          _act;      // from file, +1

	char* _filename;

	// objects and npc paths (paths are in obj struct)
	Vector<StaticObject *>* _objects;


	int           * drawing_order;
	OBJ_S         * obj;
	OBJ_S         * obj_undo;
	long          obj_num;


	// save count
	//UDWORD save_count;

	// current number of objects
	long current_obj_max;
	//int			  nb_dt1;
	int           txt_act;
	//char          dt1_idx[DT1_IN_DS1_MAX];
	int           dt1_mask[DT1_IN_DS1_MAX];


	
	DsTileLayer<DsFloorTile>*  _floorLayers[2];
	DsTileLayer<DsWallTile>*   _wallLayers[4];
	DsTileLayer<DsShadowTile>* _shadowLayers[1];
	Vector<DsTileMap *>* _tileMaps;
	Map<int, DsTileCell *>* _cellDictionary;

	// Left and need to clean up

	UBYTE         wall_layer_mask[WALL_MAX_LAYER];
	UBYTE         floor_layer_mask[FLOOR_MAX_LAYER];
	char          shadow_layer_mask[SHADOW_MAX_LAYER];
	OL_ENUM       objects_layer_mask;
	UBYTE         paths_layer_mask;
	UBYTE         walkable_layer_mask;
	UBYTE         animations_layer_mask;
	UBYTE         special_layer_mask;
	long		  tag_type;
	int           tag_num;      // # of layers in unk buffer
	int           floor_num;      // # of layers in floor buffer
	int			  wall_num;
	int			  shadow_num;


public:

	////////////////////////////////////////////////////////////////////
	// static DsScene * load(const char * ds1name);
	static DsScene * load(const char * ds1name, int stageId, int typeId);
	DsScene(int stageId, int typeId);
	~DsScene();
	Size getSize();

	// static DsScene * ds1_read(const char * ds1name, int new_width, int new_height);

	//// void initialize(const char * ds1name, int stageId, int typeId);
	void initializeData();
	void init_basic(const char * ds1name, void ** buffer);
	void init_tilemap(void ** buffer);
	void init_objects(void ** buffer);
	void init_groups(void ** currentPtr, void * buffer, int buffer_len);
	void init_npc_pathes(void ** currentPtr, void * buffer, int buffer_len);
	void fill_tile_cell(int stageId, int typeId);

	Sprite* generateSprite(int x, int y);

	void debugLayer();

	
	//DsTileMap *   dt1_list[DT1_IN_DS1_MAX];
	//BLOCK_TABLE_S * block_table;
	//int           bt_num;
	//UBYTE         wall_layer_mask[WALL_MAX_LAYER];
	//UBYTE         floor_layer_mask[FLOOR_MAX_LAYER];
	//char          shadow_layer_mask[SHADOW_MAX_LAYER];
	//int           subtile_help_display;
	//char          name[256];    // long filename with paths
	//char          filename[50]; // short filename
	//int			  usage_count;
	
	
	// files in the ds1 (not used by the game)
	//long          file_num;
	//char          * file_buff;
	//int           file_len;

	//// floors
	//CELL_F_S      * floor_buff,   // buffer for all floor layers
	//	*floor_buff2;  // 2nd buffer, for copy/paste
	//int           floor_buff_len; // sizeof the floor buffer (in bytes)
	//int           floor_num;      // # of layers in floor buffer
	//int           floor_line;     // width * floor_num
	//int           floor_len;      // floor_line * height

	//// shadow
	//CELL_S_S      * shadow_buff,   // buffer for all shadow layers
	//	*shadow_buff2;  // 2nd buffer, for copy/paste
	//int           shadow_buff_len; // sizeof the shadow buffer (in bytes)
	//int           shadow_num;      // # of layers in shadow buffer
	//int           shadow_line;     // width * shadow_num
	//int           shadow_len;      // shadow_line * height

	//// walls
	//CELL_W_S      * wall_buff,    // buffer for all wall layers
	//	*wall_buff2;   // 2nd buffer, for copy/paste
	//int           wall_buff_len;  // sizeof the wall buffer (in bytes)
	//int           wall_num;       // # of layers in wall buffer
	//int           wall_line;      // width * wall_num
	//int           wall_len;       // wall_line * height

	//// tag
	//CELL_T_S      * tag_buff,   // buffer for all unk layers
	//	*tag_buff2;  // 2nd buffer, for copy/paste
	//int           tag_buff_len; // sizeof the unk buffer (in bytes)
	//int           tag_num;      // # of layers in unk buffer
	//int           tag_line;     // width * unk_num
	//int           tag_len;      // unk_line * height

	// groups for tag layer
	long          group_num;
	int           group_size;
	GROUP_S       * group;

	// internal
	//ZOOM_E        cur_zoom;
	//int           tile_w;
	//int           tile_h;
	//int           height_mul;
	//int           height_div;
	//SCROLL_S      cur_scroll;

	// screen position and size for this ds1
	//WIN_PREVIEW_S own_wpreview;

	//long          obj_num_undo;
	//int           can_undo_obj;
	//int           draw_edit_obj; // edit Type-Id of objects, FALSE / TRUE
	//WIN_EDT_OBJ_S win_edt_obj;

	//// current animated floor frame
	//int           cur_anim_floor_frame;

	//// path editing window of this ds1
	//PATH_EDIT_WIN_S path_edit_win;

	

	// Texture2D *getTexture(int x, int y, int layer);
	
	//void wprop_2_block(CELL_W_S * w_ptr);
	//void fprop_2_block(CELL_F_S * f_ptr);
	//void sprop_2_block(CELL_S_S * s_ptr);
	//void ds1_init_data(int type, int def);
	//void ds1_make_prop_2_block();
	//void ds1_save(int is_tmp_file);
	//int read_lvltypes_txt(int type);
	//void misc_make_block_table();

	//// int misc_increase_ds1_objects_max(long nb_objects);

	//void misc_check_tiles_conflicts();

};



#endif