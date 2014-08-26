// hw_collect.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "smbios.h"
#include "baseboard.h"

int _tmain(int argc, _TCHAR* argv[])
{
	printf("SMBIOS Ver:%d.%d \n", SMBIOS::Intance().smbios_version_major_, SMBIOS::Intance().smbios_version_minor_);

	BaseBoard bb;
	printf("%s ",   bb.GetManufacturer());
	printf("%s\n",  bb.GetProduct());

	printf("%s ",	bb.GetBIOSVendor());
	printf("%s\n",	bb.GetBIOSVersion());
	printf("%s\n",	bb.GetBIOSDate());

	return 0;
}

