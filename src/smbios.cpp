#include "smbios.h"
#include <algorithm>
#include <assert.h>
#include "wmi.h"


SMBIOS& SMBIOS::Intance()
{
	static SMBIOS smbios;
	return smbios;
}

SMBIOS::SMBIOS()
	: smbios_pointer_(nullptr), smbios_data_size_(0),
	  smbios_version_major_(0), smbios_version_minor_(0)
{
	Initialize();
}

SMBIOS::~SMBIOS()
{}

void SMBIOS::Initialize()
{
	if (!GetVersionAndData())
		return;

	EnumEachTable();
}

bool SMBIOS::GetVersionAndData()
{
	WMI wmi;

	if (!wmi.Initialize())
		return false;

	if (!wmi.ConnectServer(bstr_t(L"root\\WMI")))
		return false;

	if (!wmi.ExecuteQuery(bstr_t("select * from MSSMBios_RawSMBiosTables")))
		return false;

	if (wmi.GetEnumerate())
	{
		VARIANT val;
		wmi.GetResult(L"SmbiosMajorVersion", val);
		smbios_version_major_ = val.bVal;

		wmi.GetResult(L"SmbiosMinorVersion", val);
		smbios_version_minor_ = val.bVal;

		wmi.GetResult(L"SMBiosData", val);
		assert((VT_UI1 | VT_ARRAY) == val.vt);

		SAFEARRAY* safe_array = V_ARRAY(&val);

		smbios_pointer_	  = reinterpret_cast<BYTE*>(safe_array->pvData);
		smbios_data_size_ = safe_array->rgsabound[0].cElements;

		return true;
	}

	return false;
}

const BYTE SMBIOS::GetTypeCount(const BYTE type) const
{
	return count_if(smbios_table_.begin(), smbios_table_.end(), TableInfo(type));
}

void SMBIOS::EnumEachTable()
{
	assert(smbios_pointer_ != nullptr);

	DWORD index = 0;
	TableInfo table;

	while (index < smbios_data_size_)
	{
		table._offset	 = index;
		table._type		 = smbios_pointer_[index];
		table._data_size = smbios_pointer_[index + 1];
		table._real_size = GetTableRealSize(&smbios_pointer_[index], table._data_size);

		index += table._real_size;

		smbios_table_.push_back(table);
	}
}

WORD SMBIOS::GetTableRealSize(const BYTE *data, const BYTE data_size)
{
	WORD res_size = data_size;

	while (*(LPWORD(data + res_size)) != 0)
		++res_size;

	return res_size + 2;
}

bool SMBIOS::FindFirstTargetType(const BYTE type)
{
	assert(smbios_pointer_ != nullptr);

	smbios_index_iter_ = find_if(smbios_table_.begin(), smbios_table_.end(), TableInfo(type));

	return (smbios_index_iter_ != smbios_table_.end());
}

bool SMBIOS::FindNextTargetType()
{
	assert(smbios_pointer_ != nullptr);

	if (smbios_index_iter_ == smbios_table_.end())
		return false;

	smbios_index_iter_ = find_if(smbios_index_iter_ + 1, smbios_table_.end(), TableInfo(smbios_index_iter_->_type));

	return (smbios_index_iter_ != smbios_table_.end());
}

void SMBIOS::FillDataFeild(void *dst, const size_t size, const BYTE id)
{
	BYTE *pointer = smbios_pointer_ + smbios_index_iter_->_offset;

	assert(id > 0 && id < smbios_index_iter_->_data_size);

	memcpy(dst, pointer + id, size);
}

void SMBIOS::FilStringFeild(void **dst, const BYTE id)
{
	BYTE *pointer = smbios_pointer_ + smbios_index_iter_->_offset;

	assert(id > 0 && id < smbios_index_iter_->_data_size);

	BYTE index = 1;
	BYTE str_index = pointer[id];
	BYTE *str_index_pointer = pointer + smbios_index_iter_->_data_size;

	while (str_index_pointer != pointer + smbios_index_iter_->_real_size)
	{
		if (index == str_index)
		{
			*dst = str_index_pointer;
			return;
		}

		if (*str_index_pointer == '\0')
			++index;

		++str_index_pointer;
	}
}