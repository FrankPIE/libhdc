#include "baseboard.h"
#include "smbios.h"

BaseBoard::BaseBoard()
{
	memset(&base_board_, 0, sizeof(BaseBoardType2));
	GetBaseBoard();
	GetBIOS();
}

BaseBoard::~BaseBoard()
{}

bool BaseBoard::GetBaseBoard()
{
	if (SMBIOS::Intance().FindFirstTargetType(BASEBOARD_TYPE2))
	{
		SetBoardType();
		DoDataFill(&base_board_);		
		return true;
	}

	return false;
}

bool BaseBoard::GetBIOS()
{
	if (SMBIOS::Intance().FindFirstTargetType(BIOS_TYPE0))
	{
		DoDataFill(&bios_);
		return true;
	}

	return false;
}

void BaseBoard::SetBoardType()
{
	board_type_[UNKNOWN_22]				  = "Unknown";
	board_type_[OTHER]					  = "Other";
	board_type_[SERVER_BLADE]		      = "ServerBlade";
	board_type_[CONNECTIVITY_SWITCH]      = "ConnectivitySwitch";
	board_type_[SYSTEMMANAGEMENT_MODULE]  = "SystemManagementModule";
	board_type_[PROCESSOR_MODULE]		  = "ProcessorModule";
	board_type_[IO_MODULE]				  = "IOModule";
	board_type_[MEMORY_MODULE]			  = "MemoryModule";
	board_type_[DAUGHTER_BOARD]			  = "DaughterBoard";
	board_type_[MOTHER_BOARD]			  = "MotherBoard";
	board_type_[PROCESSOR_MEMORYM_MODULE] = "ProcessorMemorymModule";
	board_type_[PROCESSOR_IO_MODULE]	  = "ProcessorIOModule";
	board_type_[INTERCONNECT_BOARD]		  = "InterconnectBoard";
}
   
void BaseBoard::DoDataFill(BaseBoardType2 *bb)
{   
	SMBIOS::Intance().FillDataFeild(&bb->feature_flag, sizeof(BYTE), 0x09);
	SMBIOS::Intance().FillDataFeild(&bb->board_type,	sizeof(BYTE), 0x0D);
	SMBIOS::Intance().FillDataFeild(&bb->contain_object_handler_num, sizeof(BYTE), 0x0E);

	SMBIOS::Intance().FillDataFeild(&bb->chas_handler, sizeof(WORD), 0x0B);

	SMBIOS::Intance().FilStringFeild((void**)&bb->manufacturer,	0x04);
	SMBIOS::Intance().FilStringFeild((void**)&bb->product,			0x05);
	SMBIOS::Intance().FilStringFeild((void**)&bb->version,			0x06);
	SMBIOS::Intance().FilStringFeild((void**)&bb->serial_num,		0x07);
	SMBIOS::Intance().FilStringFeild((void**)&bb->asset_tag,		0x08);
	SMBIOS::Intance().FilStringFeild((void**)&bb->location_within_chassis, 0x0A);
}

void BaseBoard::DoDataFill(BIOSType0 *bios)
{
	SMBIOS::Intance().FilStringFeild((void**)&bios->vendor,		  0x04);
	SMBIOS::Intance().FilStringFeild((void**)&bios->version,	  0x05);
	SMBIOS::Intance().FilStringFeild((void**)&bios->release_date, 0x08);

	SMBIOS::Intance().FillDataFeild(&bios->start_addr_segment, sizeof(WORD),	0x06);
	SMBIOS::Intance().FillDataFeild(&bios->rom_size,		   sizeof(BYTE),	0x09);
	SMBIOS::Intance().FillDataFeild(&bios->characteristics,	   sizeof(UINT64),  0x0A);
	SMBIOS::Intance().FillDataFeild(&bios->extension1,		   sizeof(BYTE),	0x12);
	SMBIOS::Intance().FillDataFeild(&bios->extension2,		   sizeof(BYTE),	0x13);
	SMBIOS::Intance().FillDataFeild(&bios->major,			   sizeof(BYTE),	0x14);
	SMBIOS::Intance().FillDataFeild(&bios->minor,			   sizeof(BYTE),	0x15);
	SMBIOS::Intance().FillDataFeild(&bios->firmware_major,	   sizeof(BYTE),	0x16);
	SMBIOS::Intance().FillDataFeild(&bios->firmware_minor,     sizeof(BYTE),	0x17);
}

LPCSTR BaseBoard::GetManufacturer() const
{
	return base_board_.manufacturer;
}

LPCSTR BaseBoard::GetProduct() const
{
	return base_board_.product;
}

LPCSTR BaseBoard::GetBIOSVendor() const
{
	return bios_.vendor;
}

LPCSTR BaseBoard::GetBIOSVersion() const
{
	return bios_.version;
}

LPCSTR BaseBoard::GetBIOSDate() const
{
	return bios_.release_date;
}

// LPCSTR BaseBoard::GetVersion() const
// {
// 	return base_board_.version;
// }
// 
// LPCSTR BaseBoard::GetBoardType()
// {
// 	return board_type_[base_board_.board_type];
// }
