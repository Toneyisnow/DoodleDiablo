#include "ds_image.h"
#include "base\ds_shared_memory.h"

DsImage::DsImage(DsBitMapData *data)
{
	this->_width = data->getWidth();
	this->_height = data->getHeight();
	UBYTE* temp = DsSharedMemory::getInstance()->directedAnimationTempMemory();

	UBYTE lastByte = 0;
	UBYTE lastCount = 0;
	int index = 0;

	clear_memory_usage();
	for (int j = 0; j < _height; j++)
	{
		for (int i = 0; i < _width; i++)
		{
			UBYTE cur = data->getByte(i, j);
			if (lastCount > 0 && (cur != lastByte || lastCount == 255))
			{
				temp[index++] = lastByte;
				temp[index++] = lastCount;
				lastCount = 1;
			}
			else
			{
				lastCount++;
			}
			lastByte = cur;
		}
	}

	if (lastCount > 0)
	{
		temp[index++] = lastByte;
		temp[index++] = lastCount;
	}

	_dataLength = sizeof(UBYTE) * index;
	this->_data = (UBYTE*)malloc(_dataLength);
	memcpy(this->_data, temp, _dataLength);

	claim_memory_usage(_dataLength);

	//int total = 0;
	//for (int k = 0; k < index; k += 2)
	{
		//log("%d * %d", _data[k], _data[k + 1]);
		//total += _data[k + 1];
	}

}

DsImage::~DsImage()
{
	free(this->_data);
}

void DsImage::setBoxAnchor(float x, float y)
{
	this->_boxminX = x;
	this->_boxminY = y;
}

Vec2 DsImage::getBoxAnchor()
{
	return Vec2(_boxminX, _boxminY);
}

Size DsImage::getOriginalSizeInPixels()
{
	return Size(_width, _height);
}

SpriteFrame * DsImage::render(Palette * palette)
{
	UBYTE* data = DsSharedMemory::getInstance()->directedAnimationTempMemory();

	resetReader();
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			UBYTE b = readNext();
			int index = j * _width + i;
			if (b != 0)
			{
				int colorIndex = (int)b;
				if (colorIndex < 256 && colorIndex >= 0)
				{
					RGB clr = palette->getColor(colorIndex);
					data[index * 2 + 1] = (UBYTE)((clr.r / 16) * 16 + (clr.g / 16));
					data[index * 2] = (UBYTE)((clr.b / 16) * 16 + 15);
				}
				else
				{
					data[index * 2] = data[index * 2 + 1] = 0;
				}
			}
			else
			{
				data[index * 2] = data[index * 2 + 1] = 0;
			}
		}
	}

	Texture2D * texture = new Texture2D();
	texture->initWithData(data, sizeof(Color4B) * _width * _height / 2, kCCTexture2DPixelFormat_RGBA4444, _width, _height, CCSize(_width, _height));

	SpriteFrame * frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, _width, _height));
	frame->setOffsetInPixels(Vec2(this->_boxminX, 1 - this->_boxminY - _height));

	texture->release();

	return frame;
}

SpriteFrame * DsImage::render()
{
	UBYTE* data = DsSharedMemory::getInstance()->directedAnimationTempMemory();

	resetReader();
	for (int i = 0; i < _width; i++)
	{
		for (int j = 0; j < _height; j++)
		{
			UBYTE b = readNext();
			int index = j * _width + i;
			if (b != 0)
			{
				int colorIndex = (int)b;
				if (colorIndex < 256 && colorIndex >= 0)
				{
					data[index] = (UBYTE)(255);
				}
				else
				{
					data[index] = 0;
				}
			}
			else
			{
				data[index] = 0;
			}
		}
	}

	Texture2D * texture = new Texture2D();
	texture->initWithData(data, sizeof(UBYTE) * _width * _height, kCCTexture2DPixelFormat_A8, _width, _height, CCSize(_width, _height));

	SpriteFrame * frame = SpriteFrame::createWithTexture(texture, Rect(0, 0, _width, _height));
	frame->setOffsetInPixels(Vec2(this->_boxminX, this->_boxminY));

	texture->release();

	return frame;
}

void DsImage::resetReader()
{
	this->_readerPointer = 0;
	this->_readCount = 0;
}

UBYTE DsImage::readNext()
{
	UBYTE result = (this->_readerPointer < this->_dataLength) ? _data[this->_readerPointer] : 0;
	if (this->_readCount < _data[this->_readerPointer + 1] - 1)
	{
		this->_readCount++;
	}
	else
	{
		if (this->_readerPointer + 2 < this->_dataLength)
		{
			this->_readerPointer += 2;
			this->_readCount = 0;
		}
	}

	return result;
}

