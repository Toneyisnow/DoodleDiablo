#include "ds_resource_storage.h"


char * DsResourceStorage::path_missles = "data\\global\\missles\\";
char * DsResourceStorage::path_monsters = "data\\global\\monsters\\";
char * DsResourceStorage::path_objects = "data\\global\\objects\\";
char * DsResourceStorage::path_chars = "data\\global\\CHARS\\";

char * DsResourceStorage::path_composite_animation_config = "%s%s\\COF\\%s.cof";
char * DsResourceStorage::path_pieced_animation = "%s%s\\%s\\%s.dcc";



int DsResourceStorage::load(const char * filename, void ** buffer, long * buf_len)
{
	return DsResourceStorage::load_from_file(filename, buffer, buf_len);
}


int DsResourceStorage::load_from_file(const char * filename, void ** buffer, long * buf_len)
{
	char * datadir = "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\d2data\\";
	char * chardir = "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\d2char\\";
	char * customizedir = "D:\\Toney\\Personal\\DiabloII\\==ExtractedMPQ==\\customized\\";
	FILE * in = NULL;
	long size = 0;
	char strtmp[256] = "";


	// init
	* buffer = (void *)NULL;
	*buf_len = 0;

	// open file
	sprintf(strtmp, "%s%s", datadir, filename);
	in = fopen(strtmp, "rb");
	if (in == NULL)
	{
		sprintf(strtmp, "%s%s", chardir, filename);
		in = fopen(strtmp, "rb");
		if (in == NULL)
		{
			sprintf(strtmp, "%s%s", customizedir, filename);
			in = fopen(strtmp, "rb");
		}
	}

	if (in == NULL)
	{
		return -1; // not read
	}

	// get size, for malloc()
	fseek(in, 0, SEEK_END);
	size = ftell(in) + 1;
	fseek(in, 0, SEEK_SET);
	*buffer = (void *)malloc(size);
	if (*buffer == NULL)
	{
		fclose(in);
		sprintf(strtmp, "not enough mem (%li bytes) for %s (from Mod Directory)",
			size, filename);
		/// ds1edit_error(strtmp);
		return -1;
	}
	size--;
	*buf_len = size;

	// copy the file in mem
	fread(*buffer, size, 1, in);
	*(((char *)(*buffer)) + size) = 0;

	//end
	fclose(in);
	return 0; // not equal to -1 means it's ok
}
