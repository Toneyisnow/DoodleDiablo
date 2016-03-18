#ifndef _EXCEL_DEFINITION_H_
#define _EXCEL_DEFINITION_H_


#include <cocos2d.h>

USING_NS_CC;

typedef enum ExcelCellType
{
	Cell_String,
	Cell_Int
} ExcelCellType;


class ExcelDefinition : public Ref
{
private:

	void * _data[255];
	static char * getstring(char** pos, bool * is_new_line);
	static char * getheader(char** pos);
	void set_value(int columnIndex, ExcelCellType columnType, const char * val);


protected:

	int _columnCount;
	ExcelCellType* _columnTypes;

	
public:

	// For the keyIndex and generateKey function, select one to use
	static Map<int, ExcelDefinition*>* load(const char * resourceKey, int columnCount, const ExcelCellType* columnTypes, int keyIndex);
	static Map<int, ExcelDefinition*>* load(const char * resourceKey, int columnCount, const ExcelCellType* columnTypes, int keyIndex, int(&generateKey)(ExcelDefinition*));
	static int generateNullKey(ExcelDefinition*);

	/// static Map<int, ExcelDefinition*>* load_from_excel(const char * file);
	// static Map<int, ExcelDefinition*>* load_levelprest_from_excel(const char * file);

	ExcelDefinition(int columnCount);
	~ExcelDefinition();

	
	int getIntValue(int colIndex);
	char * getStringValue(int colIndex);

};


#endif