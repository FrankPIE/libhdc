#ifndef _SMBIOS_H_
#define _SMBIOS_H_

#include <vector>
#include "smbios_table.h"

class SMBIOS
{
public:
	SMBIOS();
   ~SMBIOS();

public:
	bool Initialize();

	bool FindFirstTargetType(size_t *index, const BYTE type) const;

	bool FindNextTargetType(size_t *index, const BYTE type)  const;

private:
	SMBIOS(const SMBIOS&);
	void operator=(const SMBIOS&);

private:
	bool GetVersionAndData();

	void EnumEachTable();

	WORD GetTableRealSize(const BYTE *data, const BYTE data_size);

private:
	BYTE  *smbios_pointer_;
	DWORD  smbios_data_size_;
	BYTE   smbios_version_major_;
	BYTE   smbios_version_minor_;

	std::vector<TableInfo>	smbios_table_;
};

#endif // !_SMBIOS_H_
