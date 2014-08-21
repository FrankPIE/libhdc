#ifndef _SMBIOS_TABLE_H_
#define _SMBIOS_TABLE_H_

#include <windows.h>

const BYTE BIOS_TYPE0		= 0x00;
const BYTE SYSTEM_TYPE1		= 0x01;
const BYTE BASEBOARD_TYPE2	= 0x02;
const BYTE ENCLOSURE_TYPE3	= 0x03;
const BYTE PROCESSOR_TYPE4	= 0x04;
const BYTE CACHE_TYPE7		= 0x07;
const BYTE SLOTS_TYPE9		= 0x09;
const BYTE MEMARRAY_TYPE16	= 0x10;
const BYTE MEMDEVIC_TYPE17	= 0x11;

struct TableInfo
{
	BYTE	type;
	BYTE	data_size;
	WORD	real_size;
	DWORD	offset;
};

//---------------------------------------------------------------------------------------------//
/************************************************************************/
/*				TYPE	0 TABLE BIOS INFO                               */
/************************************************************************/
struct BIOSType0
{
	LPSTR		vendor;						//0x04 BIOS Vendor's Name
	LPSTR		version;					//0x05 Free form version info
	WORD		start_addr_segment;			//0x06 Segment location of BIOS starting address
	LPSTR		release_date;				//0x08 mm/dd/yy or mm/dd/yyyy
	BYTE		rom_size;					//0x09 Size(n) where 64k*(n+1) is size of physical device device containing bios in bytes
	UINT64		characteristics;			//0x0A See characteristics table (0.0) below
	BYTE		extension1;					//0x12 Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
	BYTE	    extension2;					//0x13 Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
	BYTE		major;						//0x14 Major release for system bios (e.g. bios = 10.2, sys_bios_major = 0x0A)
	BYTE		minor;						//0x15 Minor release for system bios (e.g. bios = 10.2, sys_bios_minor = 0x02)
	BYTE		firmware_major;				//0x16 Major release for embedded firmware
	BYTE		firmware_minor;				//0x17 Minor release for embedded firmware
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	0.0		TABLE                                   */
/************************************************************************/
enum Table00
{
	RESERVED1				= 0x0001,
	RESERVED2				= 0x0002,
	UNKNOWN					= 0x0004,
	NOT_SUPPORTED8			= 0x0008,
	ISA_SUPPORTED			= 0x0010,
	MCS_SUPPORTED			= 0x0020,
	ESIA_SUPPORTED			= 0x0040,
	PCI_SUPPORTED			= 0x0080,
	PCMCIA_SUPPORTED		= 0x0100,
	PNP_SUPPORTED			= 0x0200,
	APM_SUPPORTED			= 0x0400,
	BIOS_FLASHABLE			= 0x0800,
	BIOS_SHADOW_SUPPORTED	= 0x00001000,
	VL_VESA_SUPPORTED		= 0x00002000,
	ESCD_SUPPORTED			= 0x00004000,
	CD_BOOT_SUPPORTED		= 0x00008000,
	SELECT_BOOT_SUPPORTED	= 0x00010000,
	BIOS_ROM_SOCKETED		= 0x00020000,
	PCCARD_BOOT_SUPPORTED	= 0x00040000,
	EDD_SUPPORTED			= 0x00080000,
	INT_13H_JAP_FLOPPY_NEC_SUPPORTED		= 0x00100000,
	INT_13H_JAP_FLOPPY_TOSHIBA_SUPPORTED	= 0x00200000,
	INT_13H_525_360KB_FLOPPY_SUPPORTED		= 0x00400000,
	INT_13H_525_12MB_FLOPPY_SUPPORTED		= 0x00800000,
	INT_13H_35_720KB_FLOPPY_SUPPORTED		= 0x01000000,
	INT_13H_35_288MB_FLOPPY_SUPPORTED		= 0x02000000,
	INT_5H_PRINT_SCREEN_SUPPORTED			= 0x04000000,
	INT_9H_842_KEYBD_SUPPORTED				= 0x08000000,
	INT_14H_SERIAL_SUPPORTED				= 0x10000000,
	INT_17H_PRINTER_SUPPORTED				= 0x20000000,
	INT_10H_CGA_MONO_VIDEO_SUPPORTED		= 0x40000000,
	NEC_PC_98								= 0x80000000
	//32bit ~ 47bit  Reserved for BIOS   Vendor
	//48bit ~ 63bit  Reserved for System Vendor
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	0.1		TABLE                                   */
/************************************************************************/
enum Table01
{
	ACPI_SUPPORTED				= 0x01,
	USB_LEGACY_SUPPORTED		= 0x02,
	AGP_SUPPORTED				= 0x04,
	I20_SUPPORTED				= 0x08,
	LS120_SUPPORTED				= 0x10,
	ATAPI_ZIP_BOOT_SUPPORTED	= 0x20,
	BOOT_1394_SUPPORTED			= 0x40,
	SMART_BATTERY_SUPPORTED		= 0x80
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	0.2		TABLE                                   */
/************************************************************************/
enum Table02
{
	BIOS_BOOT_SPEC_SUPPORTED		 = 0x01,
	FUNC_KEY_INIT_NET_BOOT_SUPPORTED = 0x02,
	ENABLE_TARGETED_CONTENT_DISTRI	 = 0x04,
	UEFI_SPEC_SUPPORTED				 = 0x08,
	SMBIOS_VIRTUAL_MACHINE			 = 0x10
	//5bit ~ 7bit Reserved
};
//////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------//
/************************************************************************/
/*				TYPE	2 TABLE BASE BAORD INFO                         */
/************************************************************************/
struct BaseBoardType2
{
	LPSTR		manufacturer;									//0x04 base board manufacturer name
	LPSTR		product;										//0x05 base board product name
	LPSTR		version;										//0x06 string representation of base board version
	LPSTR		serial_num;										//0x07 base board serial number
	LPSTR		asset_tag;										//0x08 base board asset tag 
	BYTE		feature_flag;		  							//0x09 base board feature flags see 2.1
	LPSTR		location_within_chassis;						//0x0A describes this board's location within the chassis referenced by the Chassis Handle below.
	WORD		chas_handler;								    //0x0B the handle, or instance number, associated with the chassis in which this board resides
	BYTE		board_type;										//0x0D identifies the type of board; see 2.2
	BYTE		contain_object_handler_num;						//0x0E identifies the number (0 to 255) of Contained Object Handles that follow.
	LPWORD		contain_object_handler;							//0x0F a list of handles of other structures 
};

/************************************************************************/
/*				TYPE	2.1 TABLE  Feature Flags                        */
/************************************************************************/
enum Table21
{
	HOSTINGBOARD	= 0x01,
	HAVEOTHERBOARD  = 0x02,
	REMOVEABLE		= 0x04,
	REPLACEABLE		= 0x08,
	HOTSWAPPABLE	= 0x10
	//5bit ~ 7bit Reserved for future
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	2.2 TABLE  Board  Flags                         */
/************************************************************************/
enum Table22
{
	UNKNOWEN				 = 0x01,
	OTHER					 = 0x02,
	SERVER_BLADE			 = 0x03,
	CONNECTIVITY_SWITCH		 = 0x04,
	SYSTEMMANAGEMENT_MODULE  = 0x05,
	PROCESSOR_MODULE		 = 0x06,
	IO_MODULE			 	 = 0x07,
	MEMORY_MODULE			 = 0x08,
	DAUGHTER_BOARD			 = 0x09,
	MOTHER_BOARD			 = 0x0A,
	PROCESSOR_MEMORYM_MODULE = 0x0B,
	PROCESSOR_IO_MODULE		 = 0x0C,
	INTERCONNECT_BOARD	     = 0x0D
};
//////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------//
#endif // !_SMBIOS_TABLE_H_
