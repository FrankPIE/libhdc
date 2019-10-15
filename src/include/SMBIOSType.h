/*
* Copyright (C) 2019 MadStrawberry
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this
* software and associated documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* ¡¡¡¡
* The above copyright notice and this permission notice shall be included in all copies or substantial
* portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#ifndef _HDC_SMBIOS_TYPE_H_
#define _HDC_SMBIOS_TYPE_H_

#include <stdint.h>

#define SMBIOS_BIOS_TYPE0		0x00
#define SMBIOS_SYSTEM_TYPE1		0x01
#define SMBIOS_BASEBOARD_TYPE2	0x02
#define SMBIOS_ENCLOSURE_TYPE3	0x03
#define SMBIOS_PROCESSOR_TYPE4	0x04
#define SMBIOS_CACHE_TYPE7		0x07
#define SMBIOS_SLOTS_TYPE9		0x09
#define SMBIOS_MEMARRAY_TYPE16	0x10
#define SMBIOS_MEMDEVIC_TYPE17	0x11

//---------------------------------------------------------------------------------------------//
/************************************************************************/
/*				TYPE	0 TABLE BIOS INFO                               */
/************************************************************************/
struct BIOSType0
{
	char*		vendor;						//0x04 BIOS Vendor's Name
	char*		version;					//0x05 Free form version info
	uint16_t	start_addr_segment;			//0x06 Segment location of BIOS starting address
	char*		release_date;				//0x08 mm/dd/yy or mm/dd/yyyy
	uint8_t		rom_size;					//0x09 Size(n) where 64k*(n+1) is size of physical device device containing bios in uint8_ts
	uint64_t	characteristics;			//0x0A See characteristics table (0.0) below
	uint8_t		extension1;					//0x12 Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
	uint8_t	    extension2;					//0x13 Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
	uint8_t		major;						//0x14 Major release for system bios (e.g. bios = 10.2, sys_bios_major = 0x0A)
	uint8_t		minor;						//0x15 Minor release for system bios (e.g. bios = 10.2, sys_bios_minor = 0x02)
	uint8_t		firmware_major;				//0x16 Major release for embedded firmware
	uint8_t		firmware_minor;				//0x17 Minor release for embedded firmware
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	0.0		TABLE                                   */
/************************************************************************/
enum Table00
{
	RESERVED1 = 0x0001,
	RESERVED2 = 0x0002,
	UNKNOWN = 0x0004,
	NOT_SUPPORTED8 = 0x0008,
	ISA_SUPPORTED = 0x0010,
	MCS_SUPPORTED = 0x0020,
	ESIA_SUPPORTED = 0x0040,
	PCI_SUPPORTED = 0x0080,
	PCMCIA_SUPPORTED = 0x0100,
	PNP_SUPPORTED = 0x0200,
	APM_SUPPORTED = 0x0400,
	BIOS_FLASHABLE = 0x0800,
	BIOS_SHADOW_SUPPORTED = 0x00001000,
	VL_VESA_SUPPORTED = 0x00002000,
	ESCD_SUPPORTED = 0x00004000,
	CD_BOOT_SUPPORTED = 0x00008000,
	SELECT_BOOT_SUPPORTED = 0x00010000,
	BIOS_ROM_SOCKETED = 0x00020000,
	PCCARD_BOOT_SUPPORTED = 0x00040000,
	EDD_SUPPORTED = 0x00080000,
	INT_13H_JAP_FLOPPY_NEC_SUPPORTED = 0x00100000,
	INT_13H_JAP_FLOPPY_TOSHIBA_SUPPORTED = 0x00200000,
	INT_13H_525_360KB_FLOPPY_SUPPORTED = 0x00400000,
	INT_13H_525_12MB_FLOPPY_SUPPORTED = 0x00800000,
	INT_13H_35_720KB_FLOPPY_SUPPORTED = 0x01000000,
	INT_13H_35_288MB_FLOPPY_SUPPORTED = 0x02000000,
	INT_5H_PRINT_SCREEN_SUPPORTED = 0x04000000,
	INT_9H_842_KEYBD_SUPPORTED = 0x08000000,
	INT_14H_SERIAL_SUPPORTED = 0x10000000,
	INT_17H_PRINTER_SUPPORTED = 0x20000000,
	INT_10H_CGA_MONO_VIDEO_SUPPORTED = 0x40000000,
	NEC_PC_98 = 0x80000000
	//32bit ~ 47bit  Reserved for BIOS   Vendor
	//48bit ~ 63bit  Reserved for System Vendor
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	0.1		TABLE                                   */
/************************************************************************/
enum Table01
{
	ACPI_SUPPORTED = 0x01,
	USB_LEGACY_SUPPORTED = 0x02,
	AGP_SUPPORTED = 0x04,
	I20_SUPPORTED = 0x08,
	LS120_SUPPORTED = 0x10,
	ATAPI_ZIP_BOOT_SUPPORTED = 0x20,
	BOOT_1394_SUPPORTED = 0x40,
	SMART_BATTERY_SUPPORTED = 0x80
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	0.2		TABLE                                   */
/************************************************************************/
enum Table02
{
	BIOS_BOOT_SPEC_SUPPORTED = 0x01,
	FUNC_KEY_INIT_NET_BOOT_SUPPORTED = 0x02,
	ENABLE_TARGETED_CONTENT_DISTRI = 0x04,
	UEFI_SPEC_SUPPORTED = 0x08,
	SMBIOS_VIRTUAL_MACHINE = 0x10
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
	char*		manufacturer;									//0x04 base board manufacturer name
	char*		product;										//0x05 base board product name
	char*		version;										//0x06 string representation of base board version
	char*		serial_num;										//0x07 base board serial number
	char*		asset_tag;										//0x08 base board asset tag 
	uint8_t		feature_flag;		  							//0x09 base board feature flags see 2.1
	char*		location_within_chassis;						//0x0A describes this board's location within the chassis referenced by the Chassis Handle below.
	uint16_t	chas_handler;								    //0x0B the handle, or instance number, associated with the chassis in which this board resides
	uint8_t		board_type;										//0x0D identifies the type of board; see 2.2
	uint8_t		contain_object_handler_num;						//0x0E identifies the number (0 to 255) of Contained Object Handles that follow.
	uint16_t*	contain_object_handler;							//0x0F a list of handles of other structures 
};

/************************************************************************/
/*				TYPE	2.1 TABLE  Feature Flags                        */
/************************************************************************/
enum Table21
{
	HOSTINGBOARD = 0x01,
	HAVEOTHERBOARD = 0x02,
	REMOVEABLE = 0x04,
	REPLACEABLE = 0x08,
	HOTSWAPPABLE = 0x10
	//5bit ~ 7bit Reserved for future
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	2.2 TABLE  Board  Flags                         */
/************************************************************************/
enum Table22
{
	UNKNOWN_22 = 0x01,
	OTHER = 0x02,
	SERVER_BLADE = 0x03,
	CONNECTIVITY_SWITCH = 0x04,
	SYSTEMMANAGEMENT_MODULE = 0x05,
	PROCESSOR_MODULE = 0x06,
	IO_MODULE = 0x07,
	MEMORY_MODULE = 0x08,
	DAUGHTER_BOARD = 0x09,
	MOTHER_BOARD = 0x0A,
	PROCESSOR_MEMORYM_MODULE = 0x0B,
	PROCESSOR_IO_MODULE = 0x0C,
	INTERCONNECT_BOARD = 0x0D
};
//////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------//
struct MemoryArrayType16
{
	uint8_t		location;
	uint8_t		use;
	uint8_t		mem_error_corect;
	uint32_t	max_capacity;
	uint16_t	mem_error_info_handle;
	uint16_t	number_of_memory_dev;
	uint64_t	extended_max_capacity;
};
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	16.1 TABLE  Location Field						*/
/************************************************************************/
enum Table161
{
	LOCATION_OTHER = 0x01,
	LOCATION_UNKNOWN = 0x02,
	LOCATION_SYS_OR_MOTHER = 0x03,
	LOCATION_ISA_ADD = 0x04,
	LOCATION_EISA_ADD = 0x05,
	LOCATION_PCI_ADD = 0x06,
	LOCATION_MCA_ADD = 0x07,
	LOCATION_PCMCIA_ADD = 0x08,
	LOCATION_PROPRIETY_ADD = 0x09,
	LOCATION_NUBUS = 0x0A,
	LOCATION_PC98_C20_ADD = 0xA0,
	LOCATION_PC98_C24_ADD = 0xA1,
	LOCATION_PC98_E_ADD = 0xA2,
	LOCATION_PC98_LOCALBUS_ADD = 0xA3
};

//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	16.2 TABLE  Use Field							*/
/************************************************************************/
enum Table162
{
	USE_OTHER = 0x01,
	USE_UNKNOWN = 0x02,
	USE_SYS_MEM = 0x03,
	USE_VEDIO_MEM = 0x04,
	USE_FLASH_MEM = 0x05,
	USE_NON_VOLATILE_RAM = 0x06,
	USE_CHCHE_MEMORY = 0x07
};

//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	16.3 TABLE  Error Collection Types Field		*/
/************************************************************************/
enum Table163
{
	ERRC_OTHER = 0x01,
	ERRC_UNKNOWN = 0x02,
	ERRC_NONE = 0x03,
	ERRC_PARITY = 0x04,
	ERRC_SIG_B_ECC = 0x05,
	ERRC_MULT_B_ECC = 0x06,
	ERRC_CRC = 0x07
};
//////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------//
struct MemoryDeviceType17
{
	uint16_t		physical_memory_array_handle;
	uint16_t		mem_error_info_handle;
	uint16_t		total_width;
	uint16_t		data_width;
	uint16_t		size;
	uint8_t			form_factor;
	uint8_t			device_set;
	char*			device_locator;
	char*			bank_locator;
	uint8_t			memory_type;
	uint16_t		type_detail;
	uint16_t		speed;
	char*			manufacturer;
	char*			serial_num;
	char*			asset_tag;
	char*			part_number;
	uint8_t			attributes;
	uint32_t		extended_size;
	uint16_t		configured_memory_clk_speed;
	uint16_t		min_voltage;
	uint16_t		max_voltage;
	uint16_t		configured_voltage;
};


//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	17.1 TABLE  Form Factor Field					*/
/************************************************************************/
enum Table171
{
	FF_OTHER = 0x01,
	FF_UNKOWN = 0x02,
	FF_SIMM = 0x03,
	FF_SIP = 0x04,
	FF_CHIP = 0x05,
	FF_DIP = 0x06,
	FF_ZIP = 0x07,
	FF_PROCARD = 0x08,
	FF_DIMM = 0x09,
	FF_TSOP = 0x0A,
	FF_ROW_OF_CHIPS = 0x0B,
	FF_RIMM = 0x0C,
	FF_SODIMM = 0x0D,
	FF_SRIMM = 0x0E,
	FF_FB_DIMM = 0x0F
};

//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	17.2 TABLE  Type								*/
/************************************************************************/
enum Table172
{
	TYPE_OTHER = 0x01,
	TYPE_UNKNOWN = 0x02,
	TYPE_DRAM = 0x03,
	TYPE_EDRAM = 0x04,
	TYPE_VRAM = 0x05,
	TYPE_SRAM = 0x06,
	TYPE_RAM = 0x07,
	TYPE_ROM = 0x08,
	TYPE_FLASH = 0x09,
	TYPE_EEPROM = 0x0A,
	TYPE_FEPROM = 0x0B,
	TYPE_EPROM = 0x0C,
	TYPE_CDRAM = 0x0D,
	TYPE_3DRAM = 0x0E,
	TYPE_SDRAM = 0x0F,
	TYPE_SGRAM = 0x10,
	TYPE_RDRAM = 0x11,
	TYPE_DDR = 0x12,
	TYPE_DDR2 = 0x13,
	TYPE_DDR2_FB_DIMM = 0x14,
	TYPE_RESERVED1 = 0x15,
	TYPE_RESERVED2 = 0x16,
	TYPE_RESERVED3 = 0x17,
	TYPE_DDR3 = 0x18,
	TYPE_FBD2 = 0x19
};

//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*				TYPE	17.3 TABLE  Type Detail Field					*/
/************************************************************************/
enum Table173
{
	TD_RESERVED = 0x00,
	TD_OTHER = 0x02,
	TD_UNKNOWN = 0x04,
	TD_FAST_PAGED = 0x08,
	TD_STATIC_COLUMN = 0x10,
	TD_PSEUDO_STATIC = 0x20,
	TD_RAMBUS = 0x40,
	TD_SYNCHRONOUS = 0x80,
	TD_CMOS = 0x100,
	TD_EDO = 0x200,
	TD_WINDOW_DRAM = 0x400,
	TD_CACHE_DRAM = 0x800,
	TD_NON_VOLATILE = 0x1000,
	TD_REGISTERED = 0x2000,
	TD_UNBUFFERED = 0x4000,
	TD_LRDIMM = 0x8000
};
#endif // !_SMBIOS_TABLE_H_
