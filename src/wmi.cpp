#include "wmi.h"
#include <assert.h>

#define COM_RELEASE(com_object) \
	if (com_object) { (com_object)->Release(); (com_object) = nullptr; }

WMI::WMI() 
	: wbem_object_pointer_(nullptr),  wbem_enum_result_pointer_(nullptr),
	  wbem_locator_pointer_(nullptr), wbem_services_pointer_(nullptr)
{}

WMI::~WMI()
{
	COM_RELEASE(wbem_object_pointer_)
	COM_RELEASE(wbem_enum_result_pointer_)
	COM_RELEASE(wbem_services_pointer_)
	COM_RELEASE(wbem_locator_pointer_)
}

//public////////////////////////////////////////////////////////////////////
bool WMI::Initialize()
{
	if (!(InitComponent() && InitSecurity() && CreateInstance()))
		return false;

	return true;
}

bool WMI::ConnectServer(const BSTR network_resource, const BSTR username /*= nullptr*/, const BSTR password /*= nullptr*/)
{
	assert(wbem_locator_pointer_ != nullptr);

	HRESULT hr = wbem_locator_pointer_->ConnectServer(network_resource, username, password, 0, NULL, 0, 0, &wbem_services_pointer_);

	if (FAILED(hr) || !SetProxyBlanket())
	{
		COM_RELEASE(wbem_services_pointer_)

		return false;
	}

	return true;
}

bool WMI::ExecuteQuery(const BSTR wql)
{
	assert(wbem_services_pointer_ != nullptr);

	HRESULT hr = wbem_services_pointer_->ExecQuery(bstr_t("WQL"), wql,
				WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &wbem_enum_result_pointer_);

	if (FAILED(hr))
	{
		COM_RELEASE(wbem_enum_result_pointer_)
		return false;
	}

	return true;
}

bool WMI::GetEnumerate()
{
	HRESULT hr = S_OK;
	ULONG result = 0;

	if (wbem_enum_result_pointer_)
		hr = wbem_enum_result_pointer_->Next(WBEM_INFINITE, 1, &wbem_object_pointer_, &result);

	if (FAILED(hr) || 0 == result || wbem_object_pointer_ == nullptr)
	{
		COM_RELEASE(wbem_object_pointer_)
		return false;
	}

	return true;
}

bool WMI::GetResult(LPCWSTR field, VARIANT& result, CIMTYPE *type /*= nullptr*/)
{
	assert(wbem_object_pointer_ != nullptr);

	HRESULT hr = wbem_object_pointer_->Get(field, 0, &result, type, 0);

	if (FAILED(hr))
	{
		VariantClear(&result);
		return false;
	}

	return true;
}

//private///////////////////////////////////////////////////////////////////
bool WMI::InitComponent()
{
	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	if (FAILED(hr))
	{
		hr = CoInitialize(NULL);
	}

	return SUCCEEDED(hr);
}

bool WMI::InitSecurity()
{
	HRESULT hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT,
								RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

	return (SUCCEEDED(hr) || hr == RPC_E_TOO_LATE);
}

bool WMI::CreateInstance()
{
	HRESULT hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast<LPVOID *>(&wbem_locator_pointer_));

	if (SUCCEEDED(hr))
		return true;

	COM_RELEASE(wbem_locator_pointer_)

	return false;
}

bool WMI::SetProxyBlanket()
{
	assert(wbem_services_pointer_ != nullptr);

	HRESULT hr = CoSetProxyBlanket(wbem_services_pointer_, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
						RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	return SUCCEEDED(hr);
}
