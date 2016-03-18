#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "ui\animation\dcc_decoder.h"
#include "ui\object\character.h"
#include "ui\base\palette.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:

	Sprite* map;
	Sprite * player;
	
	Sprite* object;
	Palette * defaultPalette;



	Vec2 middleScreen;
	Vec2 middleDown;

	Sprite *HD;
	Sprite *TR;
	Sprite *LG;
	Sprite *LA;
	Sprite *RA;
	Sprite *RH;
	Sprite *target;
	 
	CompositeObject *character;


	DsBitMapData* bitMaps[1000];


public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuActionCallback(cocos2d::Ref* pSender);
	void b1Callback(cocos2d::Ref* pSender);
	void b2Callback(cocos2d::Ref* pSender);
	void b3Callback(cocos2d::Ref* pSender);
	void b4Callback(cocos2d::Ref* pSender);
	void b5Callback(cocos2d::Ref* pSender);
	void registerMouseEvents();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);

	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void tick1(float dt);

	void prepare_pal(const char * file);
	void loadScene(const char * file);
	void loadStage(int stageId, int indexId);
	void dumpStageToFile(int stageId, int indexId);

	void loadTileMap(const char * file);
	void loadCofFile(const char * filename);
	void loadCofFile2(const char * filename);
	Sprite* loadDccFile(const char *filename, Vec2 pos);
	void testSpriteFrame();
	void loadPlayer();
	void loadRealPlayer();
	void loadExcelFile();

	void renderDcc(const char * token);
	void renderOverlays(const char * name);

	void loadBMP(const char * filename);

	////////////////////////////////////////////////////////////////////////////////////
	/*
	void mpq_batch_open(char * mpqname);
	int test_prepare_archive(FILE* fpMpq);
	void BuildBaseMassive();
	int InitializeLocals();
	DWORD Crc(char *string, DWORD *massive_base, DWORD massive_base_offset);
	void Decode(DWORD *data_in, DWORD *massive_base, DWORD crc, DWORD lenght);
	void animdata_load(void);
	UBYTE animdata_hash_value(char * name);
	int misc_load_mpq_file(char * filename, char ** buffer, long * buf_len, int output);
	int mpq_batch_load_in_mem(char * filename, char ** buffer, long * buf_len,
		int output);
	DWORD test_tell_entry(char * filename);
	int ExtractToMem(void * mp_new, DWORD entry);
	DWORD GetUnknowCrc(DWORD entry);
	//UInt16 read_data(UInt8 *buffer, UInt16 size, void *crap);
	//void write_data(UInt8 *buffer, UInt16 size, void *crap);


	DWORD offset_mpq;
	DWORD lenght_mpq_part;
	DWORD offset_htbl;
	DWORD offset_btbl;
	DWORD lenght_htbl;
	DWORD lenght_btbl;

	DWORD	*hash_table;
	DWORD	*block_table;		// Block table
	DWORD	count_files;		// Number of files in MPQ (calculated from size of block_table)
	DWORD	massive_base[0x500];// This massive is used to calculate crc and decode files
	char	*filename_table;	// Array of MPQ filenames
	char	*identify_table;	// Bitmap table of MPQ filenames 1 - if file name for this entry is known, 0 - if is not

	char	file_name[257];		// Name of archive
	char	work_dir[MPQTYPES_MAX_PATH];	// Work directory
	char	prnbuf[MPQTYPES_MAX_PATH + 100];	// Buffer
	char	default_list[MPQTYPES_MAX_PATH];// Path to list file
	FILE	*fpMpq;

	// This is used to decompress DCL-compressed and WAVE files
	DWORD	 avail_metods[4];//={0x08,0x01,0x40,0x80};
	DWORD	 lenght_write;
	UInt8  * global_buffer, *read_buffer_start, *write_buffer_start, *explode_buffer;
	UInt32 * file_header;

	ANIM_DATA_S   anim_data;
	*/
};

#endif // __HELLOWORLD_SCENE_H__
