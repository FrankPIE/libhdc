#ifndef _SMBIOS_TABLE_H_
#define _SMBIOS_TABLE_H_

#include <windows.h>

struct TableInfo
{
	BYTE	type;
	BYTE	data_size;
	WORD	real_size;
	DWORD	offset;
};

#endif // !_SMBIOS_TABLE_H_
