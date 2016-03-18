#include <stdlib.h>
#include <cocos2d.h>

#include "ds_scene.h"
#include "ds_tile_map.h"
#include "ds_tile_layer.h"
#include "ui\animation\animation_library.h"
#include "..\..\base\ds_resource_storage.h"
#include "..\..\definition\definition_library.h"
#include "..\..\definition\data_definition.h"

USING_NS_CC;

DsScene::DsScene(int stageId, int typeId)
{
    _stageId = stageId;
    _typeId = typeId;
}

DsScene::~DsScene()
{

}

Size DsScene::getSize()
{
    return Size(_width, _height);
}

void DsScene::initializeData()
{
    void* ptr = _buffer;
    this->init_basic(_resourceKey, &ptr);
    this->init_tilemap(&ptr);
    this->init_objects(&ptr);
    this->init_groups(&ptr, _buffer, _buffer_len);
    this->init_npc_pathes(&ptr, _buffer, _buffer_len);
    this->fill_tile_cell(_stageId, _typeId);
}

void DsScene::init_basic(const char * ds1name, void ** currentPtr)
{
    // take file name without path
    int x = strlen(ds1name) - 1;
    _filename = new char[255];

    while ((x >= 0) && (ds1name[x] != '\\') && (ds1name[x] != '/') && (ds1name[x] != ':'))
        x--;
    if (x == 0)
        strcpy(this->_filename, ds1name);
    else
        strcpy(this->_filename, ds1name + x + 1);
    // strcpy(this->name, ds1name);

    // initialise max number of objects
    this->current_obj_max = OBJ_MAX_START;

    // drawing_order
    int size = this->current_obj_max * sizeof(int);
    this->drawing_order = (int *)calloc(this->current_obj_max, sizeof(int));

    // obj
    size = this->current_obj_max * sizeof(OBJ_S);
    this->obj = (OBJ_S *)calloc(this->current_obj_max, sizeof(OBJ_S));

    // obj_undo
    this->obj_undo = (OBJ_S *)calloc(this->current_obj_max, sizeof(OBJ_S));

    // layers mask
    for (x = 0; x < WALL_MAX_LAYER; x++)
        this->wall_layer_mask[x] = 1;

    for (x = 0; x < FLOOR_MAX_LAYER; x++)
        this->floor_layer_mask[x] = 1;

    for (x = 0; x < SHADOW_MAX_LAYER; x++)
        this->shadow_layer_mask[x] = 3; // transparent is default

    this->objects_layer_mask = OL_NONE;
    this->paths_layer_mask = 1;
    this->walkable_layer_mask = 0;
    // this->subtile_help_display = 1;
    this->animations_layer_mask = 1;
    this->special_layer_mask = 1;

    // inits
    this->tag_num = 0; // # of tag layer
    long *ptr = (long *)(*currentPtr);

    // copy datas from buffer into ds1 struct :

    // version
    this->_version = *ptr;
    ptr++;

    // widht
    this->_width = *ptr + 1;
    ptr++;

    // height
    this->_height = *ptr + 1;
    ptr++;

    // act
    this->_act = 1;
    if (this->_version >= 8)
    {
        this->_act = *ptr + 1;
        ptr++;
        if (this->_act > 5)
            this->_act = 5;
    }

    // tag_type
    this->tag_type = 0;
    if (this->_version >= 10)
    {
        this->tag_type = *ptr;
        ptr++;

        // adjust eventually the # of tag layer
        if ((this->tag_type == 1) || (this->tag_type == 2))
            this->tag_num = 1;
    }

    // debug
    log("\nversion         : %li\n", this->_version);
    log("width           : %li\n", this->_width);
    log("height          : %li\n", this->_height);
    log("act             : %li\n", this->_act);
    log("tag_type        : %li\n", this->tag_type);

    // filenames, it's not used by the game
    long  file_num = 0;
    char* file_buff;
    int   file_len;
    if (this->_version >= 3)
    {
        file_num = *ptr;
        // nb_dt1 = file_num;
        ptr++;
        int n = 0;
        log("filenames       : %li\n", file_num);

        for (x = 0; x < file_num; x++)
        {
            log("   %2i : %s\n", x + 1, ((char *)ptr) + n);
            n += (strlen(((char *)ptr) + n) + 1);
        }

        file_buff = (char *)malloc(n);

        file_len = n;
        memcpy(file_buff, ptr, n);
        ptr = (long *)(((char *)ptr) + n);
    }
    else
        log("no filenames\n");

    // skip 2 dwords ?
    if ((this->_version >= 9) && (this->_version <= 13))
        ptr += 2;

    *currentPtr = ptr;
}

void DsScene::init_tilemap(void ** currentPtr)
{
    int lay_stream[14],
        dir_lookup[25] = {
        0x00, 0x01, 0x02, 0x01, 0x02, 0x03, 0x03, 0x05, 0x05, 0x06,
        0x06, 0x07, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
        0x0F, 0x10, 0x11, 0x12, 0x14
    };

    long* ptr = (long *)(*currentPtr);
    this->wall_num = 0;   // # of wall & orientation layers
    this->floor_num = 0;  // # of floor layer
    this->shadow_num = 1; // # of shadow layer, always here
    int nb_layer;

    // number of wall, floor and tag layers
    if (this->_version >= 4)
    {
        // number of wall (and orientation) layers
        this->wall_num = *ptr;
        ptr++;

        // number of floor layers
        if (this->_version >= 16)
        {
            this->floor_num = *ptr;
            ptr++;
        }
        else
            this->floor_num = 1; // default # of floor layer
    }
    else // in version < 4
    {
        // # of layers hardcoded
        this->wall_num = 1;
        this->floor_num = 1;
        this->tag_num = 1;
    }
    // which order ?
    if (this->_version < 4)
    {
        lay_stream[0] = 1; // wall 1
        lay_stream[1] = 9; // floor 1
        lay_stream[2] = 5; // orientation 1
        lay_stream[3] = 12; // tag
        lay_stream[4] = 11; // shadow
        nb_layer = 5;
    }
    else
    {
        nb_layer = 0;
        for (int x = 0; x < this->wall_num; x++)
        {
            lay_stream[nb_layer++] = 1 + x; // wall x
            lay_stream[nb_layer++] = 5 + x; // orientation x
        }
        for (int x = 0; x < this->floor_num; x++)
            lay_stream[nb_layer++] = 9 + x; // floor x
        if (this->shadow_num)
            lay_stream[nb_layer++] = 11;    // shadow
        if (this->tag_num)
            lay_stream[nb_layer++] = 12;    // tag
    }
    log("layers          : (2 * %li walls) + %li floors + %li shadow"
        " + %li tag\n", this->wall_num, this->floor_num, this->shadow_num, this->tag_num);

    ////if (glb_config.always_max_layers)
    if (true)
    {
        ////f_num = FLOOR_MAX_LAYER;
        ////this->wall_num = WALL_MAX_LAYER;
    }

    // read tiles of layers
    for (int i = 0; i < this->floor_num; i++)
    {
        this->_floorLayers[i] = new DsTileLayer<DsFloorTile>(this->_width, this->_height);
    }
    for (int i = 0; i < this->shadow_num; i++)
    {
        this->_shadowLayers[i] = new DsTileLayer<DsShadowTile>(this->_width, this->_height);
    }
    for (int i = 0; i < this->wall_num; i++)
    {
        this->_wallLayers[i] = new DsTileLayer<DsWallTile>(this->_width, this->_height);
    }

    // set pointers
    UBYTE * bptr = (UBYTE *)ptr;
    for (int n = 0; n < nb_layer; n++)
    {
        for (int y = 0; y < this->_height; y++)
        {
            for (int x = 0; x < this->_width; x++)
            {
                switch (lay_stream[n])
                {
                    // walls
                case  1:
                case  2:
                case  3:
                case  4:
                    if ((x < this->_width) && (y < this->_height))
                    {
                        DsWallTile * tile = this->_wallLayers[lay_stream[n] - 1]->getTile(x, y);
                        tile->set_prop(bptr);
                    }
                    break;

                    // orientations
                case  5:
                case  6:
                case  7:
                case  8:
                    if ((x < this->_width) && (y < this->_height))
                    {
                        UBYTE orientation = 0;
                        if (this->_version < 7)
                            orientation = dir_lookup[*bptr];
                        else
                            orientation = *bptr;

                        this->_wallLayers[lay_stream[n] - 5]->getTile(x, y)->set_orientation(orientation);
                    }
                    break;

                    // floors
                case  9:
                case 10:
                    if ((x < this->_width) && (y < this->_height))
                    {
                        this->_floorLayers[lay_stream[n] - 9]->getTile(x, y)->set_prop(bptr);
                    }
                    break;

                    // shadow
                case 11:
                    if ((x < this->_width) && (y < this->_height))
                    {
                        this->_shadowLayers[lay_stream[n] - 11]->getTile(x, y)->set_prop(bptr);
                    }
                    break;

                    // tag
                case 12:
                    if ((x < this->_width) && (y < this->_height))
                    {
                        /// TODO: Add tags later
                        ///p = lay_stream[n] - 12;
                        ///t_ptr[p]->num = (UDWORD)* ((UDWORD *)bptr);
                        ///t_ptr[p] += t_num;
                    }
                    break;
                }
                bptr += 4;
            }
        }
    }

    *currentPtr = bptr;
}

void DsScene::init_objects(void ** currentPtr)
{
    //now we're on the objects data
    long* ptr = (long *)(*currentPtr);
    int current_valid_obj_idx = 0;

    this->_objects = new Vector<StaticObject *>();

    this->obj_num = 0;
    if (this->_version < 2)
    {
        log("no objects\n");
        return;
    }

    this->obj_num = *ptr;
    ptr++;
    log("objects         : %li\n", this->obj_num);

    int max_subtile_width = this->_width * 5;
    int max_subtile_height = this->_height * 5;

    for (int n = 0; n < this->obj_num; n++)
    {
        long type = *ptr;
        ptr++;
        long id = *ptr;
        ptr++;
        long x = *ptr;
        ptr++;
        long y = *ptr;
        ptr++;
        long ds1_flags = 0;

        if (this->_version > 5)
        {
            // flags
            ds1_flags = *ptr;
            ptr++;
        }
        
        log("object %d type: %d. id: %d. x:%d y:%d", n, type, id, x, y);
        if ((x < 0) || (x >= max_subtile_width) || (y < 0) || (y >= max_subtile_height))
        {
            // don't use that object, skip it
            continue;
        }

        StaticObject *obj = new StaticObject(_act, type, id, Vec2(x, y));
        if (this->_version > 5)
        {
            obj->setDsFlags(ds1_flags);
        }

        this->_objects->pushBack(obj);
    }

    *currentPtr = ptr;
}

void DsScene::init_groups(void ** currentPtr, void * buffer, int buffer_len)
{
    long* ptr = (long *)(*currentPtr);

    /* groups for tag layer

    warning : in fact there can be less groups than expected
    like in data\global\tiles\act1\outdoors\trees.ds1, where the file
    stop right after the last tile_x group data, leaving the other
    datas unknown (tile_y, width, height), and npc paths unknown */

    if ((this->_version >= 12) &&
        ((this->tag_type == 1) || (this->tag_type == 2))
        )
    {
        long n;
        // skip 1 dword ?
        if (this->_version >= 18)
            ptr++;

        this->group_num = n = *ptr;
        ptr++;
        log("groups          : %li\n", n);

        // malloc
        this->group_size = n * sizeof(GROUP_S);
        this->group = (GROUP_S *)malloc(this->group_size);

        memset(this->group, 0, this->group_size);

        // fill it
        for (int x = 0; x < n; x++)
        {
            if ((UDWORD)ptr < (((UDWORD)buffer) + buffer_len))
                this->group[x].tile_x = *ptr;
            ptr++;
            if ((UDWORD)ptr < (((UDWORD)buffer) + buffer_len))
                this->group[x].tile_y = *ptr;
            ptr++;
            if ((UDWORD)ptr < (((UDWORD)buffer) + buffer_len))
                this->group[x].width = *ptr;
            ptr++;
            if ((UDWORD)ptr < (((UDWORD)buffer) + buffer_len))
                this->group[x].height = *ptr;
            ptr++;
            if (this->_version >= 13)
            {
                if ((UDWORD)ptr < (((UDWORD)buffer) + buffer_len))
                    this->group[x].unk = *ptr;
                ptr++;
            }
        }
    }
    else
        log("no groups\n");

    *currentPtr = ptr;
}

void DsScene::init_npc_pathes(void ** currentPtr, void * buffer, int buffer_len)
{
    long* ptr = (long *)(*currentPtr);

    // now we're on the npc's paths datas
    long npc;
    long path;
    int  o, last_o, nb;
    bool obj_path_warn_wrote = FALSE;
    if (this->_version >= 14)
    {
        if ((UDWORD)ptr < (((UDWORD)buffer) + buffer_len))
            npc = *ptr;
        else
            npc = 0;
        ptr++;
        log("npc paths       : %li\n", npc);
        for (int n = 0; n < npc; n++)
        {
            long x, y;
            path = *ptr;
            ptr++;
            x = *ptr;
            ptr++;
            y = *ptr;
            ptr++;

            // search of which object are these paths datas
            o = last_o = nb = 0;
            bool done = FALSE;
            while (!done)
            {
                if (o < this->obj_num)
                {
                    if ((this->obj[o].x == x) && (this->obj[o].y == y))
                    {
                        last_o = o;
                        nb++;
                        if (nb >= 2)
                            done = TRUE;
                    }
                    o++; // next object
                }
                else
                    done = TRUE;
            }

            if (nb >= 2)
            {
                // there are a least 2 objects at the same coordinates

                // put a warning
                if (obj_path_warn_wrote != TRUE)
                {
                    obj_path_warn_wrote = TRUE;
                    log("\n"
                        "ds1_read() : WARNING, there are at least 2 objects at the same coordinates for some paths datas.\n"
                        );
                }
                log("   * Removing %i paths points of 1 object at coordinates (%i, %i)\n",
                    path, x, y);
                fflush(stdout);

                // first, delete already assigned paths
                for (o = 0; o < this->obj_num; o++)
                {
                    if ((this->obj[o].x == x) && (this->obj[o].y == y) &&
                        (this->obj[o].path_num != 0))
                    {
                        for (int p = 0; p < this->obj[o].path_num; p++)
                        {
                            this->obj[o].path[p].x = 0;
                            this->obj[o].path[p].y = 0;
                            this->obj[o].path[p].action = 0;
                            this->obj[o].path[p].flags = 0;
                        }
                        this->obj[o].path_num = 0;
                    }
                }

                // now, skip these paths
                if (this->_version >= 15)
                {
                    for (int p = 0; p < path; p++)
                        ptr += 3; // skip 3 dwords per path
                }
                else
                {
                    for (int p = 0; p < path; p++)
                        ptr += 2; // skip 2 dwords only per path, no 'action'
                }
            }
            else
            {
                // only 1 object at these coordinates for paths, it's ok
                o = last_o;

                // does these paths are pointing to a valid object position ?
                if (o >= this->obj_num)
                {
                    // nope
                    // the game don't alert the user, so why me ?
                    // but we'll skip them
                    if (this->_version >= 15)
                    {
                        for (int p = 0; p < path; p++)
                            ptr += 3; // skip 3 dwords per path
                    }
                    else
                    {
                        for (int p = 0; p < path; p++)
                            ptr += 2; // skip 2 dwords only per path, no 'action'
                    }
                }
                else
                {
                    // yep, valid object
                    if (path > WINDS1EDIT_PATH_MAX)
                    {
                        free(buffer);
                    }

                    // all ok for assigning the paths to this object
                    this->obj[o].path_num = path;
                    for (int p = 0; p < path; p++)
                    {
                        this->obj[o].path[p].x = *ptr;
                        ptr++;
                        this->obj[o].path[p].y = *ptr;
                        ptr++;
                        if (this->_version >= 15)
                        {
                            this->obj[o].path[p].action = *ptr;
                            ptr++;
                        }
                        else
                            this->obj[o].path[p].action = 1; // default action
                    }
                }
            }
        }
        //// editobj_make_obj_label(ds1_idx);
    }
    else
        log("no npc paths\n");

    *currentPtr = ptr;
}

void DsScene::fill_tile_cell(int stageId, int typeId)
{
    // Read the DT1Mask
    ExcelDefinition * levelPrest = DefinitionLibrary::getInstance()->getLevelPrestDefinition(stageId);
    int mask = levelPrest->getIntValue(LevelPrestColumns::LevelPrest_Dt1Mask);
    for (int b = 0; b < DT1_IN_DS1_MAX; b++)
    {
        this->dt1_mask[b] = mask & 1;
        mask >>= 1;
    }

    // Load requested DT1 files
    this->_tileMaps = new Vector<DsTileMap *>();
    ExcelDefinition * levelTypes = DefinitionLibrary::getInstance()->getLevelTypeDefinition(typeId);
    int act = levelTypes->getIntValue(LevelTypeColumns::LevelType_Act);

    this->_defaultPalette = AnimationLibrary::getInstance()->retrievePalette(act);

    //ExcelDefinition * levelTypes = DefinitionLibrary::getInstance()->getLevelTypeDefinition(17);
    for (int f = 0; f < 33; f++)
    {
        if (this->dt1_mask[f])
        {
            char * dt1name = levelTypes->getStringValue(LevelTypeDefinition::getFileIndex(f));
            for (int i = 0; i < strlen(dt1name); i++)
            {
                if (dt1name[i] == '/')
                    dt1name[i] = '\\';
            }

            log("Loading DT1 file: %s ...", dt1name);
            DsTileMap * map = AnimationLibrary::getInstance()->retrieveTileMap(dt1name);
            map->render(this->_defaultPalette);

            this->_tileMaps->pushBack(map);
            log("Loaded DT1 file: %s ", dt1name);
        }
    }

    // Load the Cell Table
    this->_cellDictionary = new Map<int, DsTileCell *>();
    for (int m = 0; m < this->_tileMaps->size(); m++)
    {
        DsTileMap * map = this->_tileMaps->at(m);
        for (int i = 0; i < map->getBlockCount(); i++)
        {
            DsTileImage * image = map->getBlock(i);
            int key = image->getIdentityKey();

            if (this->_cellDictionary->at(key) == NULL)
            {
                DsTileCell * cell = new DsTileCell(m, i, image);
                this->_cellDictionary->insert(key, cell);
                cell->release();
            }
            else
            {
                DsTileCell * cell = this->_cellDictionary->at(key);
                cell->addImage(image);
            }
        }

        log("Loaded %d images from DT1.", map->getBlockCount());
    }

    log("Totally %d cells loaded to table.", this->_cellDictionary->size());

    // Connect the cell buffers to the Cell Table
    for (int y = 0; y < this->_height; y++)
    {
        for (int x = 0; x < this->_width; x++)
        {
            for (int n = 0; n < this->wall_num; n++)
            {
                DsWallTile * wall = this->_wallLayers[n]->getTile(x, y);
                if (wall != NULL)
                {
                    wall->find_matching_cell(this->_cellDictionary);
                }
            }
            for (int n = 0; n < this->floor_num; n++)
            {
                DsFloorTile * floor = this->_floorLayers[n]->getTile(x, y);
                if (floor != NULL)
                {
                    floor->find_matching_cell(this->_cellDictionary);
                }
            }
            for (int n = 0; n < this->shadow_num; n++)
            {
                DsShadowTile * shadow = this->_shadowLayers[n]->getTile(x, y);
                if (shadow != NULL)
                {
                    shadow->find_matching_cell(this->_cellDictionary);
                }
            }
        }
    }
}

// ==========================================================================
// read a ds1
//    load the file into memory, then copy the datas into the right structures
//    init some var, to prepare its display (zoom, center, layer mask...)
// if new_width OR new_height is <= 0, then no change to the size of the ds1, else
// it'll crop or add necessary Tiles 
DsScene * DsScene::load(const char * ds1name, int stageId, int typeId)
{
    char file[255];
    sprintf(file, "%s%s", SCENE_RELATIVE_PATH, ds1name);

    DsScene * scene = new DsScene(stageId, typeId);
    scene->initFromStorage(file);
    scene->autorelease();

    return scene;
}

void DsScene::debugLayer()
{

    DsFloorTile* wall1 = this->_floorLayers[0]->getTile(14, 0);
    DsFloorTile* wall2 = this->_floorLayers[0]->getTile(14, 5);

    for (int w = 0; w < 1; w++)
    {
        log("Debug for Wall Layer %d", w);
        for (int y = 0; y < this->_height; y++)
        {
            std::string ou;
            for (int x = 0; x < this->_width; x++)
            {
                DsWallTile* wall = this->_wallLayers[w]->getTile(x, y);
                if (wall == NULL)
                {
                    ou.append("(N,N,N)");
                    //sprintf(output, " -1");
                }
                else
                {
                    char output[255];
                    sprintf(output, "(%Ld,%Ld,%Ld)", wall->getMainIndex(), wall->getSubIndex(), wall->getOrientation());
                    ou.append(output);
                }
            }
            log(ou.c_str());
        }
    }
}

Sprite* DsScene::generateSprite(int x, int y)
{
    Sprite *base = Sprite::create();
    base->setAnchorPoint(Vec2(0, 0));

    DsTile * tile;

    // Floor
    for (int layer = 0; layer < this->floor_num; layer++)
    {
        tile = this->_floorLayers[layer]->getTile(x, y);
        if (tile == NULL || tile->getCell() == NULL)
            continue;
        Sprite * sub = tile->getCell()->createSprite();
        if (sub != NULL)
        {
            sub->setPosition(-80, -40);
            base->addChild(sub);
        }

        // Adding the blocking indicate
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 5; i++)
            {
                int t = 20 - j * 5 + i;
                //int t = 20 - j * 5 + i;
                DsTileSubBlock * sub = tile->getCell()->getSubBlock(t);
                if (sub != NULL && sub->is_block_walk())
                {
                    Sprite* indicator = Sprite::create("Point.png");
                    int posX = (i - j) * 16;
                    int posY = 32 - (i + j) * 8;
                    indicator->setPosition(posX, posY);
                    base->addChild(indicator, 500);
                }
            }
        }
    }

    // Shadow
    for (int layer = 0; layer < this->shadow_num; layer++)
    {
        tile = this->_shadowLayers[layer]->getTile(x, y);
        if (tile == NULL || tile->getCell() == NULL)
            continue;
        Sprite * sub = tile->getCell()->createSprite();
        if (sub != NULL)
        {
            sub->setPosition(-80, -40);
            sub->setOpacity(127);
            base->addChild(sub);
        }
    }

    // Walls
    for (int layer = 0; layer < this->wall_num; layer++)
    {
        tile = this->_wallLayers[layer]->getTile(x, y);
        if (tile == NULL || tile->getCell() == NULL)
            continue;
        Sprite * sub = tile->getCell()->createSprite();
        if (sub != NULL)
        {
            sub->setPosition(-80, -40);
            sub->setOpacity(127);
            base->addChild(sub);
        }

        // Adding the blocking indicate
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                int t = 20 - j * 5 + i;
                DsTileSubBlock * sub = tile->getCell()->getSubBlock(t);
                if (sub != NULL && sub->is_block_walk())
                {
                    Sprite* indicator = Sprite::create("Point.png");
                    int posX = (i - j) * 16;
                    int posY = 32 - (i + j) * 8;
                    indicator->setPosition(posX, posY);
                    base->addChild(indicator, 500);
                }
            }
        }
    }

	// Adding objects
	// TODO: Improve Performance
	for (int o = 0; o < _objects->size(); o++)
	{
		StaticObject* obj = this->_objects->at(o);
		if (obj->getId() == 94 || obj->getId() == 93)
		{
			continue;
		}

		Vec2 pos = obj->getSubtilePosition();
		if ((int)pos.x / 5 == x && (int)pos.y / 5 == y)
		{
			log("Showing object at: (%f, %f)", pos.x, pos.y);
			int i = (int)pos.x % 5;
			int j = (int)pos.y % 5;

			int posX = (i - j) * 16;
			int posY = 32 - (i + j) * 8;
			obj->sendToGround(base, Vec2(posX, posY));
		}
	}

    return base;
}

