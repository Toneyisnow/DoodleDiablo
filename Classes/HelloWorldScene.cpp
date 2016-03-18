#include <string.h>

#include <cocos2d.h>

#include "HelloWorldScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\tilemap\ds_scene.h"
#include "ui\object\character.h"
#include "ui\object\monster.h"
#include "ui\object\static_object.h"
#include "ui\animation\animation_library.h"
#include "definition\data_definition.h"
#include "definition\definition_library.h"


USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log(origin.x);
	log(origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height * 2));
	
	auto actionItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuActionCallback, this));

	actionItem->setPosition(Vec2(origin.x + visibleSize.width - actionItem->getContentSize().width / 2,
		origin.y + actionItem->getContentSize().height / 2));

	auto b1 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::b1Callback, this));
	b1->setPosition(Vec2(50,100));

	auto b2 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::b2Callback, this));
	b2->setPosition(Vec2(100, 150));

	auto b3 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::b3Callback, this));
	b3->setPosition(Vec2(100, 50));

	auto b4 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::b4Callback, this));
	b4->setPosition(Vec2(150, 100));

	auto b5 = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::b5Callback, this));
	b5->setPosition(Vec2(250, 100));




    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, actionItem, b1, b2, b3, b4, b5, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	// position the sprite on the center of the screen
	middleScreen = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	middleDown = Vec2(visibleSize.width / 2 + origin.x, 100);

    // add "HelloWorld" splash screen"
    // auto sprite = Sprite::create("HelloWorld.png");
	SpriteFrame* ss = SpriteFrame::create("100_100_2.png", Rect(0, 0, 100, 100));
	ss->setOffsetInPixels(Vec2(50, 50));


	map = Sprite::createWithSpriteFrame(ss);
	//map->setFlippedY(true);
	map->setAnchorPoint(Vec2(0, 0));
	this->addChild(map, 0);
    

	Point vertices2[3] = { Point(1,1), Point(50,50), Point(50,0)};
	Color4F colors2[3] = { Color4F(25, 125, 125, 125), Color4F(25, 1, 125, 125), Color4F(25, 125, 125, 125) };
	////glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	////glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
	////glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	////glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)3);

	registerMouseEvents();
	
	///////////////////


	/*//////
	
	CC_NODE_DRAW_SETUP();

	// 3: Draw into the texture
	float gradientAlpha = 0.7f;
	Point vertices[4];
	ccColor4F colors[4];
	int nVertices = 0;

	vertices[nVertices] = Point(0, 0);
	colors[nVertices++] = Color4F( 0, 0, 0, 0);
	vertices[nVertices] = Point(100, 0);
	colors[nVertices++] = Color4F(0, 0, 0, 0);
	vertices[nVertices] = Point(0, 100);
	colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
	vertices[nVertices] = Point(100, 100);
	colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
	///////
	*/

	//dumpStageToFile(301, 2);		//Duriel
	//dumpStageToFile(301, 3);		//Duriel

	
	//// prepare_pal("D:\\Toney\\Personal\\Software\\GameTools\\DCC_Related\\cv52_DC6Viewer\\cv52\\pal.DAT");
	// prepare_pal("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2data\\data\\global\\palette\\ACT2\\pal.DAT");
	//////////// Read DS1 File /////////////////////

	//loadCofFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\COF\\BATN1HS.cof");
	//loadCofFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\COF\\BAA11HS.cof");
	//loadCofFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\COF\\BAA21HS.cof");
	//loadCofFile2("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2data\\data\\global\\monsters\\DU\\COF\\DUA1HTH.cof");
	//loadCofFile2("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\COF\\BAA21HS.cof");

	// loadStage(481, 1);

	// schedule(CC_SCHEDULE_SELECTOR(HelloWorld::tick1), (1.0f / 50));


	// loadScene("data\\global\\tiles\\ACT2\\Tomb\\duriel.ds1");
	// loadTileMap("data\\global\\tiles\\Act2\\Tomb\\Duriel.dt1");
	// loadTileMap("Act2\\Tomb\\Duriel.dt1");


	for (int i = 849; i <= 862; i++)
	{
		for (int j = 1; j <= 1; j++)
		{
			//dumpStageToFile(i, j);
		}
	}

	//loadStage(301, 2);		//Scene2 Town
	//loadStage(529, 1);			//Scene3 Town
	loadStage(1, 2);

	//

	/////////  Try 3

	defaultPalette = Palette::loadForAct(2);

	loadRealPlayer();

	//loadExcelFile();

	/// loadBMP("D:\\Toney\\Personal\\MyProjects\\PixelPoem\\Resources\\diagrams\\poem_jingyesi.bmp");

	return true;
}

void HelloWorld::registerMouseEvents()
{
	//  Create a "one by one" touch event listener
	// (processes one touch at a time)
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void HelloWorld::prepare_pal(const char * file)
{
	char    tmp[30];
	
	FILE    * in;
	int     i;

	///in = fopen("D:\\Toney\\Personal\\Software\\GameTools\\DCC_Related\\d2imdev-master\\dcc\\dcc_doc\\simple_dcc_decoder\\act1.dat", "rb");
	in = fopen(file, "rb");
	if (in != NULL)
	{
		for (i = 0; i<256; i++)
		{
			RGB rgb;
			rgb.r = (UBYTE)fgetc(in) >> 2;
			rgb.b = (UBYTE)fgetc(in) >> 2;
			rgb.g = (UBYTE)fgetc(in) >> 2;
		}
		fclose(in);
	}
}

void HelloWorld::loadExcelFile()
{
	DefinitionLibrary::getInstance()->loadResources();

	ExcelDefinition * levelPrest = DefinitionLibrary::getInstance()->getLevelPrestDefinition(827);
	log("%s", levelPrest->getStringValue(LevelPrestColumns::LevelPrest_File4));
	log("%d", levelPrest->getIntValue(LevelPrestColumns::LevelPrest_SizeX));

	ExcelDefinition * object = DefinitionLibrary::getInstance()->getObjectDefinition(397);
	log("%s", object->getStringValue(ObjectsColumns::ObjectsColumns_Description));
	log("%d", object->getIntValue(ObjectsColumns::ObjectsColumns_TrapProb));

}

void HelloWorld::loadStage(int stageId, int indexId)
{
	DefinitionLibrary::getInstance()->loadResources();
	DsScene * scene = AnimationLibrary::getInstance()->retrieveScene(stageId, indexId);

	// Show Scene

	int unitWidth = 160;
	int unitHeight = 80;
	int baseX = 800;
	int baseY = 2000;

	map = Sprite::create();
	log("Scene Map:");
	Size size = scene->getSize();
	for (int j = 0; j < size.height; j++)
	{
		for (int i = 0; i < size.width; i++)
		{
			Sprite* s = scene->generateSprite(i, j);
			if (s == NULL)
				continue;

			int jj = j + 1;
			int posX = (i - j) * unitWidth / 2;
			int posY = - (i + j) * unitHeight / 2;

			s->setPosition(Vec2(posX, posY));
			map->addChild(s, 100);
		}
	}

	// map->setScale(0.3f);


	this->addChild(map);
	map->setPosition(baseX, baseY);
	target = map;

}

void HelloWorld::dumpStageToFile(int stageId, int indexId)
{
	DefinitionLibrary::getInstance()->loadResources();
	DsScene * scene = AnimationLibrary::getInstance()->retrieveScene(stageId, indexId);

	// Show Scene

	int unitWidth = 160;
	int unitHeight = 80;
	int baseX = 800;
	int baseY = 2000;

	map = Sprite::create();
	Size size = scene->getSize();
	int fullWidth = unitHeight * (size.height + size.width + 1);
	int fullHeight = fullWidth / 2;
	int screenWidth = MIN(fullWidth, 6000);
	int screenHeight = MIN(fullHeight, 4000);


	Vec2 originPos = Vec2(((size.height + 1) * unitWidth - fullWidth + screenWidth )/ 2, (fullHeight + screenHeight) / 2);
	// originPos = Vec2(0, screenHeight / 2);

	// Save to file
	char filename[255];
	sprintf(filename, "map_%d_%d.JPG", stageId, indexId);
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(screenWidth, screenHeight, ResolutionPolicy::NO_BORDER);
	RenderTexture* renderTexture = RenderTexture::create(screenWidth, screenHeight, Texture2D::PixelFormat::RGBA8888);
	renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	for (int j = 0; j < size.height; j++)
	{
		for (int i = 0; i < size.width; i++)
		{
			Sprite* s = scene->generateSprite(i, j);
			if (s == NULL)
				continue;

			int jj = j + 1;
			int posX = (i - j) * unitWidth / 2;
			int posY = -(i + j) * unitHeight / 2;
			s->setPosition(Vec2(originPos.x  + posX, originPos.y + posY));
			
			s->visit();
		}
	}

	renderTexture->end();
	bool result = renderTexture->saveToFile(filename, Image::Format::JPG);
}

void HelloWorld::loadScene(const char * file)
{
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("");
	texture->getContentSizeInPixels();


	/*
	DefinitionLibrary::getInstance()->loadResources();
	DsScene * scene = DsSceneWarehouse::getInstance()->loadByName(file);

	scene->debugLayer();

	// Show Scene

	int unitWidth = 160;
	int unitHeight = 80;
	int baseX = 1200;
	int baseY = 300;

	map = Sprite::create();
	log("Scene Map:");
	for (int j = 0; j < scene->height; j++)
	{
		for (int i = 0; i < scene->width; i++)
		{
			Sprite* s = scene->generateSprite(i, j);
			if (s == NULL)
				continue;
			
			int posX = baseX + (i - j) * unitWidth / 2;
			int posY = baseY - (i + j) * unitHeight / 2;
			
			s->setPosition(Vec2(posX, posY));
			map->addChild(s, 100);
		}
	}

	//map->setScale(0.);

	this->addChild(map);
	
	*/
}

void HelloWorld::loadTileMap(const char * filename)
{
	DsTileMap * map = AnimationLibrary::getInstance()->retrieveTileMap(filename);
	map->render(defaultPalette);

	for (int k = 0; k < map->block_num; k++)
	{
		Texture2D* texture = map->getBlock(k)->getTexture();
		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, 100, 100));
		Sprite* sprite = Sprite::createWithSpriteFrame(frame);
		sprite->setPosition(Vec2(80 + (k % 5) * 160, 40 + (k / 5) * 80));
		this->addChild(sprite, 100);
	}

	map->debug();
}

void HelloWorld::loadRealPlayer()
{
	AnimationLibrary::getInstance()->loadResources();

	//character = new Character("SO");
	//character->sendToGround(this, middleScreen);
	
	//character = new StaticObject(0, 37, Vec2(0, 0));
	//character->changeToAction(AnimationAction::Animation_OP);
	//character->sendToGround(this, middleScreen);
	
	//CompositeObject *cc = new StaticObject(0, 0, Vec2(0, 0));
	//cc->changeToAction(AnimationAction::Animation_OP);
	//cc->sendToGround(this, Vec2(middleScreen.x, middleScreen.y - 200));

	/*
	Character * character2 = new Character("AM");
	character2->sendToGround(map, Point(middleScreen.x, middleScreen.y - 100));
	character2->deem(200);
	Character * character3 = new Character("BA");
	character3->sendToGround(map, Point(middleScreen.x, middleScreen.y - 200));
	character3->deem(150);
	Character * character4 = new Character("NE");
	character4->sendToGround(map, Point(middleScreen.x, middleScreen.y - 300));
	character4->deem(120);
	*/

	//Monster* m = new Monster("DI");
	//m->sendToGround(this, middleDown);
	
}

void HelloWorld::loadPlayer()
{
	loadCofFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\COF\\BAA21HS.cof");

	Sprite *player = Sprite::create();
	// Bench mark
	Sprite* point = Sprite::create("Point.png", Rect(0, 0, 4, 4));
	player->addChild(point, 5000);
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
		{
		if ((i + j) % 2 == 0)
		{
			continue;
		}
		Sprite* as = Sprite::create("10_10.png", Rect(50, 50, 10, 10));
		as->setPosition(Vec2(10 * i - 150, 10 * j - 150));
		as->setAnchorPoint(Vec2(0, 0));
		/// player->addChild(as);
		}


	HD = loadDccFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\HD\\BAHDBHMA21HS.dcc", Vec2(0, 0));
	TR = loadDccFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\TR\\BATRHVYA21HS.dcc", Vec2(0, 0));
	LG = loadDccFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\LG\\BALGHVYA21HS.dcc", Vec2(0, 0));

	LA = loadDccFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\LA\\BALAHVYA21HS.dcc", Vec2(0, 0));
	RA = loadDccFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\RA\\BARAHVYA21HS.dcc", Vec2(0, 0));
	RH = loadDccFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\BA\\RH\\BARHAXEA21HS.dcc", Vec2(0, 0));

	player->addChild(HD);
	player->addChild(TR);
	player->addChild(LG);
	player->addChild(LA);
	player->addChild(RA);
	// loadDccFile("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2char\\data\\global\\CHARS\\SO\\LH\\SOLHSBWA1BOW.dcc", Vec2(middleScreen.x, middleScreen.y - 10));
	player->addChild(RH);

	player->setPosition(middleDown);
	// player->setScale(3);
	this->addChild(player, 200);

	target = LG;
}
Sprite* HelloWorld::loadDccFile(const char *filename, Vec2 pos)
{
	DCC_S * dcc_ptr;
	DccDecoder * decoder = new DccDecoder();
	Texture2D *texture = new Texture2D();
	static Color4B Data[500 * 500];

	dcc_ptr = decoder->dcc_disk_load(filename);

	if (dcc_ptr == NULL)
		return NULL;

	/// dcc_ptr = decoder->dcc_disk_load("D:\\Toney\\Personal\\Software\\GameTools\\MPQRelated\\==Extracted==\\d2data\\data\\global\\objects\\rb\\TR\\rbtrlitonhth.dcc");

	decoder->dcc_decode(dcc_ptr, -1);

	//// decoder->dcc_debug(dcc_ptr);

	///// Debug infor:

	log("\nbox                = (%li, %li)  --->  (%li, %li)  =  %li * %li\n",
		dcc_ptr->box.xmin, dcc_ptr->box.ymin,
		dcc_ptr->box.xmax, dcc_ptr->box.ymax,
		dcc_ptr->box.width, dcc_ptr->box.height
		);
	/*
	for (int d = 0; d < dcc_ptr->header.directions; d++)
	{
		log("\ndirection [%li] box                = (%li, %li)  --->  (%li, %li)  =  %li * %li\n",
			d,
			dcc_ptr->direction[d].box.xmin, dcc_ptr->direction[d].box.ymin,
			dcc_ptr->direction[d].box.xmax, dcc_ptr->direction[d].box.ymax,
			dcc_ptr->direction[d].box.width, dcc_ptr->direction[d].box.height
			);
	}*/
	
	// Texture2D *texture;
	int nb_frame = dcc_ptr->header.frames_per_dir;
	Vector<SpriteFrame*> animFrames(nb_frame);
	for (int d = 0; d < dcc_ptr->header.directions; d++)
	{
		DCC_DIRECTION_S direction = dcc_ptr->direction[d];
		//float anchorX = -(width + direction.xoffset_bits) / width;
		//float anchorY = -(height + direction.yoffset_bits) / height;

		log("\ndirection [%li] box                = (%li, %li)  --->  (%li, %li)  =  %li * %li\n",
			d,
			direction.box.xmin, direction.box.ymin,
			direction.box.xmax, direction.box.ymax,
			direction.box.width, direction.box.height
			);

		for (int f = 0; f < nb_frame; f++)
		{
			DCC_FRAME_S frame = dcc_ptr->frame[d][f];
			int width = frame.bmp->getWidth();
			int height = frame.bmp->getHeight();
			log("frame [%li, %li] box (%li, %li) (%li, %li)  --->  (%li, %li) \n",
				d,
				f,
				frame.box.xmin, frame.box.ymin,
				frame.box.width, frame.box.height,
				width, height
				);

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					UBYTE b = frame.bmp->getByte(i, j);
					int index = j * width + i;
					if (b != 0)
					{
						int colorIndex = (int)b;
						if (colorIndex < 256 && colorIndex >= 0)
						{
							RGB clr = defaultPalette->getColor(colorIndex);
							Data[index] = Color4B(clr.r, clr.g, clr.b, 255);
							//// Data[j * frame.bmp->width + i] = Color4B(clr.r * 8, clr.g * 8, clr.b * 8, clr.filler);
							// log("%d, %d", i, j);
						}
						else
						{
							Data[index] = Color4B(0, 0, 0, 0);
						}
					}
					else
					{
						Data[index] = Color4B(0, 0, 0, 0);
					}
				}
			}

			texture = new Texture2D();
			texture->initWithData(Data, sizeof(Color4B) * width * height, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(width, height));
			
			SpriteFrame * sf = SpriteFrame::createWithTexture(texture, Rect(0, 0, width, height));
			sf->setOffsetInPixels(Vec2(direction.box.xmin, -direction.box.ymax));

			animFrames.pushBack(sf);

			
		}
	}

	//////////////////

	Sprite *myNew = Sprite::createWithSpriteFrame(animFrames.at(0));
	myNew->setAnchorPoint(Vec2(0, 0));
	
	
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	auto seq = RepeatForever::create(animate);
	myNew->runAction(seq);
	

	decoder->dcc_destroy(dcc_ptr);

	
	return myNew;
}

void HelloWorld::loadBMP(const char * filename)
{
	int temp_int;
	short temp_short;
	char temp_char;

	FILE  * in;
	in = fopen(filename, "rb");

	char * outfilename = new char[255];
	sprintf(outfilename, "%s.pp", filename);
	FILE  * out;
	out = fopen(outfilename, "w");

	int width;
	int height;
	short bitsPerPixel;
	short compressionType;
	int dataSize;

	fread(&temp_short, sizeof(short), 1, in);
	fread(&temp_int, sizeof(int), 1, in);
	fread(&temp_short, sizeof(short), 1, in);
	fread(&temp_short, sizeof(short), 1, in);
	fread(&temp_int, sizeof(int), 1, in);
	fread(&temp_int, sizeof(int), 1, in);
	fread(&width, sizeof(int), 1, in);
	fread(&height, sizeof(int), 1, in);
	fread(&temp_short, sizeof(short), 1, in);
	fread(&bitsPerPixel, sizeof(short), 1, in);
	fread(&compressionType, sizeof(short), 1, in);
	fread(&dataSize, sizeof(int), 1, in);
	fread(&temp_int, sizeof(int), 1, in);
	fread(&temp_int, sizeof(int), 1, in);
	fread(&temp_int, sizeof(int), 1, in);
	fread(&temp_int, sizeof(int), 1, in);


	fputc(width, out);
	fputc(height, out);
	for (int i = 0; i < width; i++)
	for (int j = 0; j < height; j++)
	{
		fputc((char)i, out);
	}

	fclose(in);
	fclose(out);
}

void HelloWorld::loadCofFile2(const char * filename)
{
	FILE  * in;
		UBYTE layers, frames_per_dir, directions, c, comp_idx;
		int   total_frames, i, x, y;
		long  dword;
		char  composit[16][3] = {
				{ "HD" }, { "TR" }, { "LG" }, { "RA" }, { "LA" }, { "RH" }, { "LH" }, { "SH" },
				{ "S1" }, { "S2" }, { "S3" }, { "S4" }, { "S5" }, { "S6" }, { "S7" }, { "S8" }
		};

		in = fopen(filename, "rb");
		

		// read it
		layers = fgetc(in);
		frames_per_dir = fgetc(in);
		directions = fgetc(in);

		printf("==============\n%s\n==============\n", filename);
		printf("# layers         = %u\n", layers);
		printf("# frames_per_dir = %u\n", frames_per_dir);
		printf("# directions     = %u\n", directions);

		printf("\ntotal frames     = %i\n", directions * frames_per_dir);

		// unknown
		printf("\nunknown :\n   ");
		for (i = 0; i<5; i++)
		{
			c = fgetc(in);
			printf(" %02X", c);
		}
		printf("\n");

		for (i = 0; i<4; i++)
		{
			printf("   ");
			for (x = 0; x<4; x++)
			{
				c = fgetc(in);
				printf(" %02X", c);
			}
			fseek(in, -4, SEEK_CUR);
			fread(&dword, 4, 1, in);
			printf("     (%5li if signed, else 1st byte = %3u)\n", dword, dword & 0xFF);
		}
		printf("   ");
		for (i = 0; i<4; i++)
		{
			c = fgetc(in);
			printf(" %02X", c);
		}
		printf("\n\n");


		// 9 bytes strings
		for (i = 0; i<layers; i++)
		{
			printf("layer %2i data : ", i);
			for (x = 0; x<9; x++)
			{
				c = fgetc(in);
				printf(" %02X", c);
				if (x == 0)
					comp_idx = c;
			}

			printf("  (");
			fseek(in, -9, SEEK_CUR);
			for (x = 0; x<9; x++)
			{
				c = fgetc(in);
				printf("%c", c > 32 ? c : 32);
			}
			printf(")  --> %s\n", composit[comp_idx]);
		}

		// unknown frames_per_dir data
		printf("\nframes per direction unknown data (frame that hurt ?) :\n ");
		for (i = 0; i<frames_per_dir; i++)
		{
			c = fgetc(in);
			printf(" %02X", c);
		}
		printf("\n\n");

		// layers priority
		printf("\nlayers priority for all frames of all directions :\n", i);
		for (i = 0; i<directions; i++)
		{
			log("\ndirection %i\n", i);
			for (x = 0; x<frames_per_dir; x++)
			{
				log("   frame %3i : ", x);
				std::string message;
				for (y = 0; y<layers; y++)
				{
					c = fgetc(in);
					char s[3];
					sprintf(s, "%s", composit[c]);
					message.append(" ");
					message.append(s);
				}
				log(" %s", message.c_str());


				//printf(" =");
				fseek(in, -layers, SEEK_CUR);
				for (y = 0; y<layers; y++)
				{
					c = fgetc(in);
					//printf(" %s", composit[c]);
				}
				//printf("\n");
			}
		}

		// end
		printf("\n");
		fclose(in);
}

void HelloWorld::loadCofFile(const char * filename)
{
	FILE  * in;
	UBYTE layers, frames_per_dir, directions, c, comp_idx;
	int   total_frames, i, x, y;
	long  dword;
	char  composit[16][3] = {
			{ "HD" }, { "TR" }, { "LG" }, { "RA" }, { "LA" }, { "RH" }, { "LH" }, { "SH" },
			{ "S1" }, { "S2" }, { "S3" }, { "S4" }, { "S5" }, { "S6" }, { "S7" }, { "S8" }
	};

	in = fopen(filename, "rb");
	if (in == NULL)
	{
		log("can't open %s\n", filename);
		exit(0);
	}

	// read it
	layers = fgetc(in);
	frames_per_dir = fgetc(in);
	directions = fgetc(in);

	log("==============\n%s\n==============\n", filename);
	log("# layers         = %u\n", layers);
	log("# frames_per_dir = %u\n", frames_per_dir);
	log("# directions     = %u\n", directions);

	log("\ntotal frames     = %i\n", directions * frames_per_dir);

	// unknown
	log("\nunknown :\n   ");
	for (i = 0; i<5; i++)
	{
		c = fgetc(in);
		log(" %02X", c);
	}
	log("\n");

	for (i = 0; i<4; i++)
	{
		printf("   ");
		for (x = 0; x<4; x++)
		{
			c = fgetc(in);
			log(" %02X", c);
		}
		fseek(in, -4, SEEK_CUR);
		fread(&dword, 4, 1, in);
		log("     (%5li if signed, else 1st byte = %3u)\n", dword, dword & 0xFF);
	}
	log("   ");
	for (i = 0; i<4; i++)
	{
		c = fgetc(in);
		log(" %02X", c);
	}
	
	// 9 bytes strings
	for (i = 0; i<layers; i++)
	{
		log("layer %2i data : ", i);
		for (x = 0; x<9; x++)
		{
			c = fgetc(in);
			log(" %02X", c);
			if (x == 0)
				comp_idx = c;
		}
		
		log(")  --> %s", composit[comp_idx]);
	}

	// unknown frames_per_dir data
	log("frames per direction unknown data (frame that hurt ?) : ");
	for (i = 0; i<frames_per_dir; i++)
	{
		c = fgetc(in);
		log(" %02X", c);
	}
	
	// layers priority
	log("layers priority for all frames of all directions: %i", i);

	for (i = 0; i< directions; i++)
	{
		log("direction %i", i);
		for (x = 0; x<frames_per_dir; x++)
		{
			log("   frame %3i : ", x);
			std::string message;
			for (y = 0; y<layers; y++)
			{
				c = fgetc(in);
				char s[3];
				sprintf(s, "%s", composit[c]);
				message.append(" ");
				message.append(s);
			}
			log(" %s", message.c_str());
		}
	}

	// end
	fclose(in);
}

void HelloWorld::testSpriteFrame()
{
	// Bench mark
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			if ((i + j) % 2 == 0)
			{
				continue;
			}
			Sprite* as = Sprite::create("100_100.png", Rect(0, 0, 100, 100));
			as->setPosition(Vec2(100 * i, 100 * j));
			this->addChild(as);
		}
	
	SpriteFrame * sf = SpriteFrame::create("100_100.png", Rect(0, 0, 100, 100));
	sf->setOffsetInPixels(Vec2(-50, -50));
	SpriteFrame * sf2 = SpriteFrame::create("100_100.png", Rect(0, 0, 100, 100));
	//sf2->setOffsetInPixels(Vec2(-50, -50));

	Vector<SpriteFrame*> animFrames(3);
	animFrames.pushBack(sf);
	animFrames.pushBack(sf2);

	Sprite* s = Sprite::create();
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	auto animate = Animate::create(animation);
	auto seq = RepeatForever::create(animate);
	s->runAction(seq);

	///s->setAnchorPoint(Vec2(-1,-1));
	s->setPosition(Vec2(100, 100));
	this->addChild(s);

	s->getPosition();
}

void HelloWorld::renderDcc(const char * token)
{
	char inputfile[255];
	char outputfile[255];
	sprintf(outputfile, "%strlitnuhth.png", token);
	
	sprintf(inputfile, "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\\d2data\\data\\global\\monsters\\%s\\TR\\%sTRLITNUHTH.dcc", token, token);
	object = loadDccFile(inputfile, middleScreen);

	if (object == NULL)
	{
		sprintf(inputfile, "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\\d2data\\data\\global\\monsters\\%s\\Tr\\%sTRLITNUHTH.dcc", token, token);
		object = loadDccFile(inputfile, middleScreen);
	}
	if (object == NULL)
	{
		sprintf(inputfile, "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\\d2data\\data\\global\\monsters\\%s\\tr\\%sTRLITNUHTH.dcc", token, token);
		object = loadDccFile(inputfile, middleScreen);
	}
	if (object == NULL)
		return;

	Size size = object->getTexture()->getContentSizeInPixels();
	//object->setAnchorPoint(Vec2(0, 0));
	object->setPosition(Vec2(size.width, size.height));

	auto renderTexture = RenderTexture::create(size.width * 2, size.height * 2, Texture2D::PixelFormat::RGBA8888);
	renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	object->visit();
	renderTexture->end();
	renderTexture->saveToFile(outputfile, kCCImageFormatPNG);
}

void HelloWorld::renderOverlays(const char * name)
{
	char inputfile[255];
	char outputfile[255];
	sprintf(outputfile, "%s.png", name);

	sprintf(inputfile, "data\\global\\overlays\\%s.dcc", name);
	object = loadDccFile(inputfile, middleScreen);

	Sprite* p = Sprite::create("Point.png");
	Size size = object->getTexture()->getContentSizeInPixels();
	//object->setAnchorPoint(Vec2(0, 0));
	object->setPosition(middleScreen);
	p->setPosition(middleScreen);
	this->addChild(object);
	this->addChild(p);

	auto renderTexture = RenderTexture::create(size.width * 2, size.height * 2, Texture2D::PixelFormat::RGBA8888);
	renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	object->visit();
	renderTexture->end();
	renderTexture->saveToFile(outputfile, kCCImageFormatPNG);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* even)
{
	log("onTouchBegan");
	character->changeToAction(AnimationAction::Animation_RN);

	auto target = static_cast<Sprite*>(even->getCurrentTarget());
	Point p = touch->getLocation();
	log("%f, %f", p.x, p.y);
	character->turnDirection(p.x - 100, p.y - 100);


	return true;
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* even)
{
	character->changeToAction(AnimationAction::Animation_NU);

}
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* even)
{
	auto target = static_cast<Sprite*>(even->getCurrentTarget());
	Point p = touch->getLocation();
	//log("%f, %f", p.x, p.y);

	character->turnDirection(p.x - 100, p.y - 100);

}

void HelloWorld::menuActionCallback(Ref* pSender)
{
}


void HelloWorld::b1Callback(Ref* pSender)
{
	/*
	PiecedAnimationId* piece = PiecedAnimationId::create(CompositeAnimationId::create(AnimationGenera::AnimationGenera_Monster, "YE", AnimationAction::Animation_NU, AnimationFigure::_HTH), AnimationFigure::_HTH, AnimationPiece::Piece_TR, AnimationLevel::AnimationLevel_LIT);

	DirectedAnimation* ani = AnimationLibrary::getInstance()->retrievePiecedAnimation(piece);
	Animate* animate[8];
	for (int d = 0; d < 8; d++)
	{
		Vector<SpriteFrame*>* frames = ani->getFrames(d);
		Animation* animation = Animation::createWithSpriteFrames(*frames, 0.1f);
		animate[d] = Animate::create(animation);
		animate[d]->retain();
	}

	Sprite* ye = Sprite::create();
	ye->setPosition(Vec2(500, 300));
	ye->runAction(RepeatForever::create(animate[0]));
	this->addChild(ye, 0);
	*/

	// Animation* animation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
	// Animate* animate = Animate::create(animation);

	//Sprite* ye = loadDccFile("data\\global\\monsters\\YE\\tr\\YETRLITNUHTH.dcc", middleScreen);
	//ye->setPosition(Vec2(100, 100));
	//this->addChild(ye, 0);


	//for (int i = 0; i < 1000; i++)
	//{
		//bitMaps[i] = DsBitMapData::create_bitmap(256, 256);
	//}

	/*
	character = new Monster("YE");
	character->sendToGround(this, middleScreen);
	// character->changeToAction(AnimationAction::Animation_A1);

	Sprite* anchor = Sprite::create("Point.png", Rect(0, 0, 4, 4));
	anchor->setPosition(middleScreen);
	this->addChild(anchor);
	*/


	//Monster* m = new Monster("HP");
	//m->sendToGround(this, middleDown);

	//target->setPositionX(target->getPositionX() - 1);

	// character->turnDirection((character->getDirection() + 1 ) % 8);

	//AnimationLibrary::getInstance()->loadResources2();

	
	if (target != NULL)
	{
		target->setPositionX(target->getPositionX() + 50);
	}
	

	//character->changeToAction(AnimationAction::Animation_RN);
	//character->turnDirection(30, 70);


}

void HelloWorld::b2Callback(Ref* pSender)
{
	/*
	character = new Monster("YE");
	character->sendToGround(this, middleScreen);

	for (int i = 0; i < 1000; i++)
	{
	    /// DsBitMapData::destroy_bitmap(bitMaps[i]);
		//bitMaps[i]->release();
	}

	log("Construct count: %d", DsBitMapData::referenceCount);
	log("Destruct count: %d", DsBitMapData::destructCount);
	log("AllocatedSize: %d", DsBitMapData::allocatedSize);
	log("DeallocatedSize: %d", DsBitMapData::deallocatedSize);
	*/

	//character->removeFromGround();
	//character->release();

	
	if (target != NULL)
	{
		target->setPositionY(target->getPositionY() - 50);
	}
	else if (character != NULL)
	{
		//character->changeToAction(AnimationAction::Animation_RN);
		//character->turnDirection(11);
	}

	//character->turnDirection((character->getDirection() + 15) % 8);

	//static CreatureAction actions[] = { CreatureAction::Action_A1, CreatureAction::Action_NU, CreatureAction::Action_A1, CreatureAction::Action_KK };
	//static int actionIndex = 0;

	//character->setAction(actions[(actionIndex++) % 4]);
}

void HelloWorld::b3Callback(Ref* pSender)
{
	// CompositeAnimationConfig* config = AnimationLibrary::getInstance()->retrieveCompositeAnimationConfig(AnimationGenera_Monster, "YE", AnimationAction::Animation_NU, AnimationFigure::_HTH);
	
	// character->changeToAction(AnimationAction::Animation_WL);
	
	if (target != NULL)
	{
		target->setPositionY(target->getPositionY() + 50);
	}
	

	//character->changeToAction(AnimationAction::Animation_RN);
	//character->turnDirection(15);

}

void HelloWorld::b4Callback(Ref* pSender)
{
	/*
	CompositeAnimationId* comId = CompositeAnimationId::create(AnimationGenera::AnimationGenera_Monster, "YE", AnimationAction::Animation_NU, AnimationFigure::_HTH);

	AnimationLevelHD hd = AnimationLevelHD::AnimationLevelHD_LIT;
	AnimationLevelBody body = AnimationLevelBody::AnimationLevelBody_LIT;
	AnimationLevelRH rh = AnimationLevelRH::AnimationLevelRH_NA;
	AnimationLevelLH lh = AnimationLevelLH_NA;
	AnimationLevelSH sh = AnimationLevelSH_NA;

	AnimationLibrary * library = AnimationLibrary::getInstance();
	CompositeAnimation* animation = library->retrieveCompositeAnimation(comId, hd, body, rh, lh, sh);
	
	
	Animation* ani = animation->getAnimation(0);
	Animate* animate = Animate::create(ani);
	Sprite* ye = Sprite::create();
	ye->setPosition(Vec2(500, 300));
	ye->runAction(RepeatForever::create(animate));
	this->addChild(ye, 0);
	*/

	// character->changeToAction(AnimationAction::Animation_NU);
	
	if (target != NULL)
	{
		target->setPositionX(target->getPositionX() - 50);
	}
	

	//character->changeToAction(AnimationAction::Animation_RN);
	//character->turnDirection(13);

}

void HelloWorld::b5Callback(Ref* pSender)
{
	character->changeToAction(AnimationAction::Animation_NU);

	
	//TextureCache* cache = Director::getInstance()->getTextureCache();
	//cache->addImage("", "");
	//auto ss = Director::getInstance()->getTextureCache()->getCachedTextureInfo();
	//log("%s", ss.c_str());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	player = Sprite::create("Scossor_Walking_50_84.png", Rect(0, 0, 50, 84));
	player->setPosition(2240, 1210);
	map->addChild(player);

	int height = 84;
	int width = 50;

	auto texture = Director::getInstance()->getTextureCache()->addImage("Scossor_Walking_50_84.png");
	Vector<SpriteFrame*> animFrames(8);
	for (int i = 0; i < 8; i++)
	{
		auto frame = SpriteFrame::createWithTexture(texture, Rect(width * i, height * 0, width, height));
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	player->runAction(RepeatForever::create(animate));

	Node *node = CSLoader::createNode("Player.csb");
	node->setPosition(2240, 1210);
	// map->addChild(node);

	
	schedule(CC_SCHEDULE_SELECTOR(HelloWorld::tick1), 0.03f);
	cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline("Player.csb");
	node->runAction(action);
	action->play("walk", true);
	// action->gotoFrameAndPlay(0, true);


}

void HelloWorld::tick1(float dt)
{
	character->takeTick(dt);

	Vec2 charPos = character->getPosition();
	map->setPosition(middleScreen.x - charPos.x, middleScreen.y - charPos.y);

	/*
	Point delta = Point(1, 0.8);

	Point p = player->getPosition();
	player->setPosition(Vec2(p.x + delta.x, p.y + delta.y));

	p = map->getPosition();
	map->setPosition(Vec2(p.x - delta.x, p.y - delta.y));

	*/
}
