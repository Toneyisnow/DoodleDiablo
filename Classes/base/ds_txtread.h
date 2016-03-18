#ifndef _DS_TXTREAD_H_
#define _DS_TXTREAD_H_

#include "ds_structs.h"


class DsTxtRead
{
public:
	static char  * txt_gets(char * bptr, int * nb_char, int * is_new_line, int del_char);
	static void  txt_count_header_cols(char * cur_col, int * col_count);
	static char  * txt_read_header(char * cur_col, TXT_S * txt);
	static int   txt_check_type_and_size(char * cur_col, TXT_S * txt);
	static int   txt_fill_data(char * cur_col, TXT_S * txt);
	static TXT_S * txt_destroy(TXT_S * txt);
	static void  txt_get_user_filter_cols(char * cur_col, TXT_S * txt);
	static TXT_S * txt_load(char * mem, RQ_ENUM enum_txt, char * filename);
	static void  * txt_read_in_mem(char * txtname);
	static void  txt_convert_slash(char * str);
	static void  txt_debug(char * file_path_mem, char * file_path_def, TXT_S * txt);
	static int   read_lvltypes_txt(int ds1_idx, int type);
	static int   read_lvlprest_txt(int ds1_idx, int def);
	static int   read_obj_txt(void);
	static int   read_objects_txt(void);
	static int    misc_get_txt_column_num(RQ_ENUM txt_idx, char * col_name);

}

#endif
