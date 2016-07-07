#include "directed_animation.h"

#include "ui\animation\dcc_decoder.h"
#include "ui\base\palette.h"
#include "ui\base\ds_image.h"
#include "base\ds_resource_storage.h"

DirectedAnimation::DirectedAnimation(PiecedAnimationId *pId)
{
	for (int d = 0; d < 16; d++)
	{
		//this->_animation[d] = NULL;
		this->_spriteFrames[d] = NULL;
	}

	this->_piecedId = pId;
	this->_piecedId->retain();

	// this->_defaultPalette = palette;
}

DirectedAnimation::~DirectedAnimation()
{
	for (int i = 0; i < _directionCount; i++)
	{
		//if (this->_animation[i] != NULL)
		{
		//	this->_animation[i]->release();
		//	this->_animation[i] = NULL;
		}
		if (this->_spriteFrames[i] != NULL)
		{
			this->_spriteFrames[i]->clear();
			this->_spriteFrames[i] = NULL;
		}
	}

	this->_piecedId->release();
}

void DirectedAnimation::setAnimation(int direction, Animation * ani)
{
	if (direction < 0 || direction >= _directionCount)
	{
		return;
	}

	//if (this->_animation[direction] != NULL)
	{
	//	this->_animation[direction]->release();
	}

	//this->_animation[direction] = ani;
	//this->_animation[direction]->retain();
}

void DirectedAnimation::setFrames(int direction, Vector<DsImage *>* frames)
{
	if (direction < 0 || direction >= _directionCount)
	{
		return;
	}

	if (this->_spriteFrames[direction] != NULL)
	{
		this->_spriteFrames[direction]->clear();
	}

	this->_spriteFrames[direction] = frames;
}

//Animation * DirectedAnimation::getAnimation(int direction)
//{
//	return NULL;  // (direction < 0 || direction >= _directionCount) ? NULL : this->_animation[direction];
//}

Vector<DsImage *>* DirectedAnimation::getFrames(int direction)
{
	return (direction < 0 || direction >= _directionCount) ? NULL : this->_spriteFrames[direction];
}


int DirectedAnimation::getFrameCount()
{
	return this->_spriteFrames[0]->size();
}

DirectedAnimation* DirectedAnimation::load(PiecedAnimationId *pId)
{
	DirectedAnimation *animation = new DirectedAnimation(pId);

	char* filename = new char[255];
	char* pathname = NULL;
	switch (pId->getCompositeId()->getGenera())
	{
	case AnimationGenera_Missle:
		pathname = DsResourceStorage::path_missles;
		break;
	case AnimationGenera_Monster:
		pathname = DsResourceStorage::path_monsters;
		break;
	case AnimationGenera_Object:
		pathname = DsResourceStorage::path_objects;
		break;
	case AnimationGenera_Character:
		pathname = DsResourceStorage::path_chars;
		break;
	default:
		break;
	}
	//sprintf(filename, "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\d2char\\data\\global\\CHARS\\%s\\%s\\%s.dcc", CreatureDefinitionStrings[pId->getCreature()], AnimationPieceStrings[pId->getPiece()], key.c_str());
	sprintf(filename, DsResourceStorage::path_pieced_animation, pathname, pId->getCompositeId()->getToken(), AnimationPieceStrings[pId->getPiece()], pId->toString().c_str());

	animation->loadFromDcc(filename);


	return animation;
}

void DirectedAnimation::loadFromDcc(const char * filename)
{
	DCC_S * dcc_ptr;
	DccDecoder * decoder = new DccDecoder();

	clear_memory_usage();

	dcc_ptr = decoder->dcc_disk_load(filename);
	decoder->dcc_decode(dcc_ptr, -1);

	this->_frameCount = dcc_ptr->header.frames_per_dir;
	this->_directionCount = dcc_ptr->header.directions;

	for (int d = 0; d < dcc_ptr->header.directions; d++)
	{
		Vector<DsImage*>* frames = new Vector<DsImage*>(this->_frameCount);
		DCC_DIRECTION_S direction = dcc_ptr->direction[d];
		for (int f = 0; f < this->_frameCount; f++)
		{
			DCC_FRAME_S frame = dcc_ptr->frame[d][f];
			DsImage * t = new DsImage(frame.bmp);
			t->setBoxAnchor(direction.box.xmin, direction.box.ymin);
			claim_memory_usage(t->get_memory_used());

			frames->pushBack(t);
			t->release();
		}

		this->setFrames(d, frames);
	}

	log("Total memory used: %d KB. (File: %s)", get_memory_used() / 1024, filename);

	decoder->dcc_destroy(dcc_ptr);
}

/*
void DirectedAnimation::loadFromDcc2(const char * filename)
{
	Texture2D *texture = NULL;
	UBYTE* data2 = new UBYTE[255 * 255 * 2];

	for (int d = 0; d < this->_directionCount; d++)
	{
		Vector<SpriteFrame*>* animFrames = new Vector<SpriteFrame*>(nb_frame);
		DCC_DIRECTION_S direction = dcc_ptr->direction[d];
		for (int f = 0; f < nb_frame; f++)
		{
			DCC_FRAME_S frame = dcc_ptr->frame[d][f];
			int width = frame.bmp->getWidth();
			int height = frame.bmp->getHeight();
			
			///Color4B *data = new Color4B[width * height];
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
							RGB clr = _defaultPalette->getColor(colorIndex);
							//data[index] = Color4B(clr.r, clr.g, clr.b, 255);
							data2[index * 2 + 1] = (UBYTE)((clr.r / 16) * 16 + (clr.g / 16));
							data2[index * 2] = (UBYTE)((clr.b / 16) * 16 + 15);
							//data2[index * 2] = (UBYTE)(0 + 15);

						}
						else
						{
							//data[index] = Color4B(0, 0, 0, 0);
							data2[index * 2] = data2[index * 2 + 1] = 0;
						}
					}
					else
					{
						//data[index] = Color4B(0, 0, 0, 0);
						data2[index * 2] = data2[index * 2 + 1] = 0;
					}
				}
			}

			texture = new Texture2D();
			//texture->initWithData(data, sizeof(Color4B) * width * height, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(width, height));
			texture->initWithData(data2, sizeof(Color4B) * width * height / 2, kCCTexture2DPixelFormat_RGBA4444, width, height, CCSize(width, height));
			
			SpriteFrame * sf = SpriteFrame::createWithTexture(texture, Rect(0, 0, width, height));
			sf->setOffsetInPixels(Vec2(direction.box.xmin, -direction.box.ymax));

			animFrames->pushBack(sf);			
			debugTexture(texture);

			texture->release();

		}

		this->setFrames(d, animFrames);
	}

	log("Total memory used: %d KB", totalMemoryKB);

	//delete[] data;
	delete[] data2;
	decoder->dcc_destroy(dcc_ptr);
}
*/

void DirectedAnimation::debugTexture(Texture2D * texture)
{
	unsigned int bpp = texture->getBitsPerPixelForFormat();
	auto bytes = texture->getPixelsWide() * texture->getPixelsHigh() * bpp / 8;
	// totalMemoryKB += (long)bytes / 1024;
	
	
	/*
	count++;
	snprintf(buftmp, sizeof(buftmp) - 1, "\"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB\n",
		"[]",
		(long)tex->getReferenceCount(),
		(long)tex->getName(),
		(long)tex->getPixelsWide(),
		(long)tex->getPixelsHigh(),
		(long)bpp,
		(long)bytes / 1024);


	totalMemoryKB += (long)bytes / 1024;
	std::string buffer;
	char buftmp[4096];

	unsigned int count = 0;
	unsigned int totalBytes = 0;

	memset(buftmp, 0, sizeof(buftmp));
	buffer += buftmp;
	
	snprintf(buftmp, sizeof(buftmp) - 1, "TextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)\n", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
	buffer += buftmp;
	*/
	// log("%s", buffer.c_str());
}