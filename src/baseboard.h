#ifndef _BASEBOARD_H_
#define _BASEBOARD_H_

#include <map>
#include "smbios_table.h"

class BaseBoard
{
public:
	BaseBoard();
	~BaseBoard();

public:
	LPCSTR	GetManufacturer() const;		

	LPCSTR	GetProduct()	  const;	

	LPCSTR  GetBIOSVendor()	  const;

	LPCSTR  GetBIOSVersion()  const;

	LPCSTR  GetBIOSDate()	  const;

// 	LPCSTR	GetVersion()	  const;		//不够稳定

// 	LPCSTR	GetBoardType();					//不够稳定

private:
	BaseBoard(const BaseBoard& bb);
	void operator=(const BaseBoard& bb);

private:
	bool GetBaseBoard();

	bool GetBIOS();

	void SetBoardType();

	void DoDataFill(BaseBoardType2 *bb);

	void DoDataFill(BIOSType0 *bios);

private:
	BaseBoardType2 base_board_;
	BIOSType0	   bios_;
	std::map<DWORD, LPCSTR> board_type_;
};

#endif // !_BASEBOARD_H_
