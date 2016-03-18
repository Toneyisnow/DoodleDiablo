
#include "ds_tile_cell.h"


DsTileCell::DsTileCell(int mapIndex, int imageIndex, DsTileImage * image)
{
	this->_mapIndex = mapIndex;
	this->_imageIndex = imageIndex;

	this->_tileTextureList = new Vector<Texture2D *>();
	if (image != NULL && image->getTexture() != NULL)
	{
		this->_tileTextureList->pushBack(image->getTexture());
	}

	// Only assign the sub blocks for the first assign of TileImage
	for (int t = 0; t < 25; t++)
	{
		this->_subBlocks[t] = image->getSubBlock(t);
		this->_subBlocks[t]->retain();
	}

	// sort-key
	this->setIdentity(image);

	rarity = image->rarity;

	// datas
	roof_y = 0;
	zero_line = 0;

	// type
	if (_orientation == 0)
	{
		// floor
		zero_line = 0;
		if (image->animated == 0x01)
		{
			// animated
			type = BT_ANIMATED;
		}
		else
		{
			// static
			type = BT_STATIC;
		}
	}
	else if (_orientation == 13)
	{
		// shadow
		type = BT_SHADOW;
		zero_line = -image->size_y;
	}
	else
	{
		// walls
		if ((_orientation == 10) || (_orientation == 11))
		{
			// special
			type = BT_SPECIAL;
			zero_line = -image->size_y;
		}
		else if (_orientation == 15)
		{
			// roof
			type = BT_ROOF;
			roof_y = image->roof_y;
			zero_line = 0;
		}
		else if (_orientation < 15)
		{
			// wall up
			type = BT_WALL_UP;
			zero_line = -image->size_y;
		}
		else if (_orientation > 15)
		{
			// wall down
			type = BT_WALL_DOWN;
			zero_line = 96;
		}
	}


	///image->getImage()->setOffsetInPixels(Vec2(0, zero_line));
}

DsTileCell::DsTileCell()
{
	for (int t = 0; t < 25; t++)
	{
		this->_subBlocks[t] = NULL;
	}
}
DsTileCell::~DsTileCell()
{
	for (int t = 0; t < 25; t++)
	{
		if (this->_subBlocks[t] != NULL)
		{
			this->_subBlocks[t]->release();
			this->_subBlocks[t] = NULL;
		}
	}
}

void DsTileCell::addImage(DsTileImage *image)
{
	this->_tileTextureList->pushBack(image->getTexture());\
}

DsTileSubBlock * DsTileCell::getSubBlock(int t)
{
	if (t < 0 || t > 25)
		return NULL;

	return this->_subBlocks[t];
}

Sprite* DsTileCell::createSprite()
{
	if (this->_tileTextureList->size() <= 0)
		return NULL;

	Sprite* sprite = NULL;
	
	if (type == BT_ANIMATED)
	{
		sprite = Sprite::create();

		Vector<SpriteFrame *> frames;
		for (int i = 0; i < this->_tileTextureList->size(); i++)
		{
			frames.pushBack(this->generateFrame(i));
		}

		Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
		Animate *animate = Animate::create(animation);
		sprite->runAction(RepeatForever::create(animate));
	}
	else
	{
		SpriteFrame *frame = this->generateRandomFrame();
		sprite = Sprite::createWithSpriteFrame(frame);
	}
	
	sprite->setAnchorPoint(Vec2(0, 0));
	return sprite;
}

SpriteFrame* DsTileCell::generateFrame(int index)
{
	Texture2D* texture = this->_tileTextureList->at(index);
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSizeInPixels().width, texture->getContentSizeInPixels().height));
	
	// TODO
	////frame->setOffsetInPixels(Vec2(0, zero_line));



	return frame;
}

// Get random texture according to the rarity
SpriteFrame* DsTileCell::generateRandomFrame()
{
	if (this->_tileTextureList->size() <= 0)
		return NULL;

	int random = 0;

	return this->generateFrame(0);
}