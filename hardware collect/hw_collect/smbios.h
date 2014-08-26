#ifndef _SMBIOS_H_
#define _SMBIOS_H_

#include <vector>
#include "smbios_table.h"

class TableInfo
{
public:
	TableInfo() {}
	TableInfo(const BYTE type) : _type(type) {}

	bool operator()(const TableInfo& table) { return (table._type == _type); }

public:
	BYTE	_type;
	BYTE	_data_size;
	WORD	_real_size;
	DWORD	_offset;
};

class SMBIOS
{
public:
	static SMBIOS& Intance();

public:
	const BYTE GetTypeCount(const BYTE type) const;

	bool FindFirstTargetType(const BYTE type);

	bool FindNextTargetType();

	void FillDataFeild(void *dst, const size_t size, const BYTE id);

	void FilStringFeild(void **dst, const BYTE id);

public:
	BYTE   smbios_version_major_;
	BYTE   smbios_version_minor_;

private:
	SMBIOS();
	~SMBIOS();
	SMBIOS(const SMBIOS&);
	void operator=(const SMBIOS&);

private:
	void Initialize();

	bool GetVersionAndData();

	void EnumEachTable();

	WORD GetTableRealSize(const BYTE *data, const BYTE data_size);

private:
	BYTE  *smbios_pointer_;
	DWORD  smbios_data_size_;

	std::vector<TableInfo>	smbios_table_;
	std::vector<TableInfo>::iterator smbios_index_iter_;
};

#endif // !_SMBIOS_H_
