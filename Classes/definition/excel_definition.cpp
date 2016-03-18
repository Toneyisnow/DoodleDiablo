
#include "excel_definition.h"
#include "..\base\ds_resource_storage.h"

Map<int, ExcelDefinition*>* ExcelDefinition::load(const char * resourceKey, int columnCount, const ExcelCellType* columnTypes, int keyIndex)
{
	return load(resourceKey, columnCount, columnTypes, keyIndex, ExcelDefinition::generateNullKey);
}

Map<int, ExcelDefinition*>* ExcelDefinition::load(const char * resourceKey, int columnCount, const ExcelCellType* columnTypes, int keyIndex, int(&generateKey)(ExcelDefinition*))
{
	Map<int, ExcelDefinition*>* map = new Map<int, ExcelDefinition*>();

	void * buffer;
	long buf_len;
	int result = DsResourceStorage::load(resourceKey, &buffer, &buf_len);

	if ((result == -1) || (buffer == NULL))
	{
		return map;
	}

	char * cur_pos = (char *)buffer;
	getheader(&cur_pos);
	
	while (cur_pos != NULL && *cur_pos != '\0')
	{
		ExcelDefinition * def = new ExcelDefinition(columnCount);
		bool is_new_line;
		
		for (int index = 0; index < columnCount; index++)
		{
			char * val = getstring(&cur_pos, &is_new_line);
			if (index < columnCount - 1 && is_new_line || index == columnCount - 1 && !is_new_line)
			{
				log("Format is not correct");
				return map;
			}

			def->set_value(index, columnTypes[index], val);
		}

		int key = -1;
		if (keyIndex >= 0)
		{
			key = def->getIntValue(keyIndex);
		}
		else if (generateKey != ExcelDefinition::generateNullKey)
		{
			key = generateKey(def);
		}
		else
		{
			log("Failed to load ExcelDefinition: Either keyIndex or generateKey should be defined.");
		}

		if (key >= 0)
		{
			map->insert(key, def);
		}
	}

	delete(buffer);

	return map;
}

char * ExcelDefinition::getstring(char** pos, bool * is_new_line)
{
	char * result = *pos;
	for (;;)
	{
		if (**pos == 0)
		{
			// end of file
			return NULL;
		}
		else if (**pos == '\t')
		{
			// tab
			*is_new_line = FALSE;
			**pos = '\0';
			(*pos)++;
			return result;
		}
		else if (**pos == 0x0A)
		{
			// end of LF line
			*is_new_line = TRUE;
			**pos = '\0';
			(*pos)++;
			return result;
		}
		else if (**pos == 0x0D)
		{
			// end of CR / LF line
			*is_new_line = TRUE;
			(*pos)++;
			**pos = '\0';
			(*pos)++;
			return result;
		}
		else
			(*pos)++;
	}

	return NULL;
}

char * ExcelDefinition::getheader(char** pos)
{
	char * result = *pos;
	for (;;)
	{
		if (**pos == 0)
		{
			// end of file
			return NULL;
		}
		else if (**pos == 0x0A)
		{
			// end of LF line
			**pos = '\0';
			(*pos)++;
			return result;
		}
		else if (**pos == 0x0D)
		{
			// end of CR / LF line
			(*pos)++;
			**pos = '\0';
			(*pos)++;
			return result;
		}
		else
			(*pos)++;
	}

	return result;
}

ExcelDefinition::ExcelDefinition(int columnCount)
{
	this->_columnCount = columnCount;
}

ExcelDefinition::~ExcelDefinition()
{

}

void ExcelDefinition::set_value(int columnIndex, ExcelCellType columnType, const char * val)
{
	if (columnIndex < 0 || columnIndex >= this->_columnCount)
	{
		return;
	}

	char * str;
	int *intval;

	switch (columnType)
	{
	case Cell_String:
		str = new char[strlen(val) + 1];
		strcpy(str, val);
		_data[columnIndex] = (void*)str;
		break;
	case Cell_Int:
		intval = new int();
		*intval = atoi(val);
		_data[columnIndex] = (void*)intval;
		break;
	}
}

int ExcelDefinition::generateNullKey(ExcelDefinition* def)
{
	// This should be implemented by sub class, when the keyIndex is -1
	return 0;
}

int ExcelDefinition::getIntValue(int colIndex)
{
	int * val = (int *)this->_data[colIndex];
	return *val;
}

char * ExcelDefinition::getStringValue(int colIndex)
{
	char * val = (char *)this->_data[colIndex];
	return val;
}