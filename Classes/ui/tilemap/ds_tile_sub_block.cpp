#include "ds_tile_sub_block.h"


DsTileSubBlock::DsTileSubBlock()
{
}
DsTileSubBlock::~DsTileSubBlock()
{
}


/// This should be deperated
void DsTileSubBlock::read_data(UBYTE * st_ptr)
{
	x_pos = *(DS_WORD *)st_ptr;
	y_pos = *(DS_WORD *)(st_ptr + 2);
	// skip 2 bytes : unknown1
	x_grid = *(UBYTE *)(st_ptr + 6);
	y_grid = *(UBYTE *)(st_ptr + 7);
	format = *(DS_WORD *)(st_ptr + 8);
	length = *(long *)(st_ptr + 10);
	// skip 2 bytes : unknown2
	data_offset = *(long *)((UBYTE *)st_ptr + 16);
}

void DsTileSubBlock::set_flag(UBYTE * ptr)
{
	this->_flag = *ptr;
}

bool DsTileSubBlock::is_block_walk()
{
	return (this->_flag & 1);
}

bool DsTileSubBlock::is_block_teleport()
{
	return (this->_flag & 4);
}
