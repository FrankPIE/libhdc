#ifndef _WMI_H_
#define _WMI_H_

#include <comdef.h>
#include <WbemIdl.h>

#pragma comment(lib, "WbemUuid.lib")

class WMI
{
public:
	WMI();
	~WMI();

public:
	bool Initialize();

	bool ConnectServer(const BSTR network_resource, const BSTR username = nullptr, const BSTR password = nullptr);

	bool ExecuteQuery(const BSTR wql);

	bool GetEnumerate();

	bool GetResult(LPCWSTR field, VARIANT& result, CIMTYPE *type = nullptr);

private:
	WMI(const WMI&);
	void operator=(const WMI&);

private:
	bool InitComponent();	

	bool InitSecurity();		

	bool CreateInstance();		

	bool SetProxyBlanket();

private:
	IWbemClassObject		*wbem_object_;
	IEnumWbemClassObject	*wbem_enum_result_;
	IWbemLocator			*wbem_locator_;
	IWbemServices			*wbem_services_;
};

#endif // !_WMI_H_
