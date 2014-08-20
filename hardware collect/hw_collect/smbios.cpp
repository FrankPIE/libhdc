#include "smbios.h"
#include <assert.h>
#include "wmi.h"

SMBIOS::SMBIOS()
	: smbios_pointer_(nullptr), smbios_data_size_(0), smbios_version_major_(0), smbios_version_minor_(0)
{}

SMBIOS::~SMBIOS()
{}

bool SMBIOS::Initialize()
{
	if (!GetVersionAndData())
		return false;

	EnumEachTable();

	return true;
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

void SMBIOS::EnumEachTable()
{
	assert(smbios_pointer_ != nullptr);

	DWORD index = 0;
	TableInfo table;

	while (index < smbios_data_size_)
	{
		table.offset	= index;
		table.type		= smbios_pointer_[index];
		table.data_size = smbios_pointer_[index + 1];
		table.real_size = GetTableRealSize(&smbios_pointer_[index], table.data_size);

		index += table.real_size;

		smbios_table_.push_back(table);
	}
}

WORD SMBIOS::GetTableRealSize(const BYTE *data, const BYTE data_size)
{
	WORD res_size = data_size;

	while (*(LPWORD(data + res_size)) != 0)
		res_size += 1;

	return res_size + 2;
}
