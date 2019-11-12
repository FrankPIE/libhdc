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
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#ifndef _HDC_SMBIOS_TYPE_H_
#define _HDC_SMBIOS_TYPE_H_

#define SMBIOS_TYPE0_BIOS           0x00
#define SMBIOS_TYPE1_SYSTEM         0x01
#define SMBIOS_TYPE2_BASEBOARD      0x02
#define SMBIOS_TYPE3_ENCLOSURE      0x03
#define SMBIOS_TYPE4_PROCESSOR      0x04
#define SMBIOS_TYPE7_CACHE	        0x07
#define SMBIOS_TYPE9_SLOTS          0x09
#define SMBIOS_TYPE16_MEMORY_ARRAY  0x10
#define SMBIOS_TYPE17_MEMORY_DEVICE 0x11

/************************************************************************/
/*				TYPE	0 TABLE BIOS INFO                               */
/************************************************************************/
#define SMBIOS_TYPE0_VENDOR_STRING               0x04 // BIOS Vendor's Name
#define SMBIOS_TYPE0_VERSION_STRING              0x05 // Free form version info
#define SMBIOS_TYPE0_START_ADDRESS_SEGMENT_2BYTE 0x06 // Segment location of BIOS starting address
#define SMBIOS_TYPE0_RELEASE_DATE_STRING		 0x08 // mm/dd/yy or mm/dd/yyyy
#define SMBIOS_TYPE0_ROM_SIZE_1BYTE				 0x09 // Size(n) where 64k*(n+1) is size of physical device device containing bios in uint8_ts
#define SMBIOS_TYPE0_CHARACTERISTICS_8BYTE		 0x0A // See characteristics table (0.0) below
#define	SMBIOS_TYPE0_EXTENSION1_1BYTE			 0x12 // Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
#define	SMBIOS_TYPE0_EXTENSION2_1BYTE			 0x13 // Optional space reserved for extensions. (Length in offset 1 - 0x12) tables 0.1 and 0.2
#define	SMBIOS_TYPE0_MAJOR_1BYTE				 0x14 // Major release for system bios (e.g. bios = 10.2, sys_bios_major = 0x0A)
#define	SMBIOS_TYPE0_MINOR_1BYTE				 0x15 // Minor release for system bios (e.g. bios = 10.2, sys_bios_minor = 0x02)
#define	SMBIOS_TYPE0_FIRMWARE_MAJOR_1BYTE		 0x16 // Major release for embedded firmware
#define	SMBIOS_TYPE0_FIRMWARE_MINOR_1BYTE		 0x17 // Minor release for embedded firmware

/************************************************************************/
/*				BIOS Characteristics                                    */
/************************************************************************/
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_RESERVED1                            0x0001
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_RESERVED2                            0x0002
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_UNKNOWN                              0x0004
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_NOT_SUPPORTED                        0x0008
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_ISA_SUPPORTED                        0x0010
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_MCS_SUPPORTED                        0x0020
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_ESIA_SUPPORTED                       0x0040
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_PCI_SUPPORTED                        0x0080
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_PCMCIA_SUPPORTED                     0x0100
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_PNP_SUPPORTED                        0x0200
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_APM_SUPPORTED                        0x0400
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_BIOS_UPGRADEABLE                     0x0800
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_BIOS_SHADOW_SUPPORTED                0x00001000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_VL_VESA_SUPPORTED                    0x00002000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_ESCD_SUPPORTED                       0x00004000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_CD_BOOT_SUPPORTED                    0x00008000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_SELECT_BOOT_SUPPORTED                0x00010000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_BIOS_ROM_SOCKETED                    0x00020000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_PCCARD_BOOT_SUPPORTED                0x00040000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_EDD_SUPPORTED                        0x00080000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_13H_JAP_FLOPPY_NEC_SUPPORTED     0x00100000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_13H_JAP_FLOPPY_TOSHIBA_SUPPORTED 0x00200000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_13H_525_360KB_FLOPPY_SUPPORTED   0x00400000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_13H_525_12MB_FLOPPY_SUPPORTED    0x00800000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_13H_35_720KB_FLOPPY_SUPPORTED    0x01000000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_13H_35_288MB_FLOPPY_SUPPORTED    0x02000000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_5H_PRINT_SCREEN_SUPPORTED        0x04000000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_9H_842_KEYBD_SUPPORTED           0x08000000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_14H_SERIAL_SUPPORTED             0x10000000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_17H_PRINTER_SUPPORTED            0x20000000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_INT_10H_CGA_MONO_VIDEO_SUPPORTED     0x40000000
#define SMBIOS_TABLE6_BIOS_CHARACTERISTICS_NEC_PC_98                            0x80000000
//32bit ~ 47bit  Reserved for BIOS   Vendor
//48bit ~ 63bit  Reserved for System Vendor

/************************************************************************/
/*				BIOS Characteristics Extension Byte1                    */
/************************************************************************/
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_ACPI_SUPPORTED			0x01
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_USB_LEGACY_SUPPORTED		0x02
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_AGP_SUPPORTED			0x04
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_I20_SUPPORTED			0x08
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_LS120_SUPPORTED			0x10
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_ATAPI_ZIP_BOOT_SUPPORTED 0x20
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_BOOT_1394_SUPPORTED		0x40
#define SMBIOS_TABLE7_BIOS_CHARACTERISTICS_EXTENSION_BYTE1_SMART_BATTERY_SUPPORTED	0x80

/************************************************************************/
/*				BIOS Characteristics Extension Byte2                    */
/************************************************************************/
#define SMBIOS_TABLE8_BIOS_CHARACTERISTICS_EXTENSION_BYTE2_BIOS_BOOT_SPEC_SUPPORTED			0x01
#define SMBIOS_TABLE8_BIOS_CHARACTERISTICS_EXTENSION_BYTE2_FUNC_KEY_INIT_NET_BOOT_SUPPORTED 0x02
#define SMBIOS_TABLE8_BIOS_CHARACTERISTICS_EXTENSION_BYTE2_ENABLE_TARGETED_CONTENT_DISTRI	0x04
#define SMBIOS_TABLE8_BIOS_CHARACTERISTICS_EXTENSION_BYTE2_UEFI_SPEC_SUPPORTED				0x08
#define SMBIOS_TABLE8_BIOS_CHARACTERISTICS_EXTENSION_BYTE2_SMBIOS_VIRTUAL_MACHINE			0x10
//5bit ~ 7bit Reserved

/************************************************************************/
/*				TYPE	1 TABLE SYSTEM INFO								*/
/************************************************************************/
#define SMBIOS_TYPE1_MANUFACTURER_STRING 0x04   
#define SMBIOS_TYPE1_PRODUCT_STRING		 0x05  
#define SMBIOS_TYPE1_VERSION_STRING		 0x06  
#define SMBIOS_TYPE1_UUID_16BYTE		 0x08  
#define SMBIOS_TYPE1_WAKEUP_TYPE_1BYTE	 0x18  
#define SMBIOS_TYPE1_SKU_NUMBER_STRING	 0x19  
#define SMBIOS_TYPE1_FAMILY_1BYTE		 0x1A  

/************************************************************************/
/*				Wake up type field										*/
/************************************************************************/
#define SMBIOS_TABLE11_WAKE_UP_TYPE_RESERVED          0x00
#define SMBIOS_TABLE11_WAKE_UP_TYPE_OTHER             0x01
#define SMBIOS_TABLE11_WAKE_UP_TYPE_UNKNOWN           0x02
#define SMBIOS_TABLE11_WAKE_UP_TYPE_APM_TIMER         0x03
#define SMBIOS_TABLE11_WAKE_UP_TYPE_MODEM_RING        0x04
#define SMBIOS_TABLE11_WAKE_UP_TYPE_LAN_REMOTE        0x05
#define SMBIOS_TABLE11_WAKE_UP_TYPE_POWER_SWITCH      0x06
#define SMBIOS_TABLE11_WAKE_UP_TYPE_PCI_PME_SHARP     0x07
#define SMBIOS_TABLE11_WAKE_UP_TYPE_AC_POWER_RESTORED 0x08

/************************************************************************/
/*				TYPE	2 TABLE BASE BOARD INFO                         */
/************************************************************************/
#define SMBIOS_TYPE2_MANUFACTURER_STRING					0x04 // base board manufacturer name
#define SMBIOS_TYPE2_PRODUCT_STRING							0x05 // base board product name
#define SMBIOS_TYPE2_VERSION_STRING							0x06 // string representation of base board version
#define SMBIOS_TYPE2_SERIAL_NUM_STRING						0x07 // base board serial number
#define SMBIOS_TYPE2_ASSET_TAG_STRING						0x08 // base board asset tag 
#define SMBIOS_TYPE2_FEATURE_FLAG_1BYTE		  				0x09 // base board feature flags see 2.1
#define SMBIOS_TYPE2_LOCATION_WITHIN_CHASSIS_STRING			0x0A // describes this board's location within the chassis referenced by the Chassis Handle below.
#define SMBIOS_TYPE2_CHAS_HANDLER_2BYTE						0x0B // the handle, or instance number, associated with the chassis in which this board resides
#define SMBIOS_TYPE2_BOARD_TYPE_1BYTE						0x0D // identifies the type of board; see 2.2
#define SMBIOS_TYPE2_CONTAIN_OBJECT_HANDLER_NUM_1BYTE		0x0E // identifies the number (0 to 255) of Contained Object Handles that follow.
#define SMBIOS_TYPE2_CONTAIN_OBJECT_HANDLER_2BYTE_POINTER	0x0F // a list of handles of other structures

/************************************************************************/
/*				Baseboard: feature flags								*/
/************************************************************************/
#define SMBIOS_TABLE13_FEATURE_FLAGS_HOSTING_BOARD		0x01
#define SMBIOS_TABLE13_FEATURE_FLAGS_HAVE_OTHER_BOARD	0x02
#define SMBIOS_TABLE13_FEATURE_FLAGS_REMOVABLE			0x04
#define SMBIOS_TABLE13_FEATURE_FLAGS_REPLACEABLE		0x08
#define SMBIOS_TABLE13_FEATURE_FLAGS_HOT_SWAPPABLE		0x10
//5bit ~ 7bit Reserved for future

/************************************************************************/
/*				Baseboard: Board Type  								    */
/************************************************************************/
#define SMBIOS_TABLE14_BOARD_TYPE_UNKNOWN			       0X01
#define SMBIOS_TABLE14_BOARD_TYPE_OTHER				       0X02
#define SMBIOS_TABLE14_BOARD_TYPE_SERVER_BLADE		       0X03
#define SMBIOS_TABLE14_BOARD_TYPE_CONNECTIVITY_SWITCH      0X04
#define SMBIOS_TABLE14_BOARD_TYPE_SYSTEM_MANAGEMENT_MODULE 0x05
#define SMBIOS_TABLE14_BOARD_TYPE_PROCESSOR_MODULE		   0X06
#define SMBIOS_TABLE14_BOARD_TYPE_IO_MODULE				   0X07
#define SMBIOS_TABLE14_BOARD_TYPE_MEMORY_MODULE			   0X08
#define SMBIOS_TABLE14_BOARD_TYPE_DAUGHTER_BOARD		   0X09
#define SMBIOS_TABLE14_BOARD_TYPE_MOTHER_BOARD			   0X0A
#define SMBIOS_TABLE14_BOARD_TYPE_PROCESSOR_MEMORY_MODULE  0X0B
#define SMBIOS_TABLE14_BOARD_TYPE_PROCESSOR_IO_MODULE	   0X0C
#define SMBIOS_TABLE14_BOARD_TYPE_INTERCONNECT_BOARD	   0X0D

/************************************************************************/
/*				TYPE	16 TABLE MEMORY ARRAY INFO                      */
/************************************************************************/
#define SMBIOS_TYPE16_LOCATION_1BYTE					0x04  
#define SMBIOS_TYPE16_USE_1BYTE							0x05  
#define SMBIOS_TYPE16_MEMORY_ERROR_CORRECTION_1BYTE		0x06  
#define SMBIOS_TYPE16_MAX_CAPACITY_4BYTE				0x07  
#define SMBIOS_TYPE16_MEMORY_ERROR_INFO_HANDLE_2BYTE	0x0B  
#define SMBIOS_TYPE16_NUMBER_OF_MEMORY_DEV_2BYTE		0x0D  
#define SMBIOS_TYPE16_EXTENDED_MAX_CAPACITY_8BYTE		0x0F

/************************************************************************/
/*				Memory Array: Location Field						    */
/************************************************************************/
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_OTHER              0x01
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_UNKNOWN            0x02
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_SYS_OR_MOTHER      0x03
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_ISA_ADD            0x04
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_EISA_ADD           0x05
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_PCI_ADD            0x06
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_MCA_ADD            0x07
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_PCMCIA_ADD         0x08
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_PROPRIETY_ADD      0x09
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_NUBUS              0x0A
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_PC98_C20_ADD       0xA0
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_PC98_C24_ADD       0xA1
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_PC98_E_ADD         0xA2
#define SMBIOS_TABLE68_MEMORY_ARRAY_LOCATION_FIELD_PC98_LOCAL_BUS_ADD 0xA3

/************************************************************************/
/*				Memory Array: Use Field						            */
/************************************************************************/
#define SMBIOS_TABLE69_MEMORY_ARRAY_USE_FIELD_OTHER            0x01              
#define SMBIOS_TABLE69_MEMORY_ARRAY_USE_FIELD_UNKNOWN          0x02            
#define SMBIOS_TABLE69_MEMORY_ARRAY_USE_FIELD_SYS_MEM          0x03            
#define SMBIOS_TABLE69_MEMORY_ARRAY_USE_FIELD_VIDEO_MEM        0x04          
#define SMBIOS_TABLE69_MEMORY_ARRAY_USE_FIELD_FLASH_MEM        0x05          
#define SMBIOS_TABLE69_MEMORY_ARRAY_USE_FIELD_NON_VOLATILE_RAM 0x06   
#define SMBIOS_TABLE69_MEMORY_ARRAY_USE_FIELD_CACHE_MEMORY     0x07       

/************************************************************************/
/*				Memory Array:  Error Collection Types Field		        */
/************************************************************************/
#define SMBIOS_TABLE69_MEMORY_ARRAY_ECT_FIELD_OTHER         0x01
#define SMBIOS_TABLE69_MEMORY_ARRAY_ECT_FIELD_UNKNOWN       0x02
#define SMBIOS_TABLE69_MEMORY_ARRAY_ECT_FIELD_NONE          0x03
#define SMBIOS_TABLE69_MEMORY_ARRAY_ECT_FIELD_PARITY        0x04
#define SMBIOS_TABLE69_MEMORY_ARRAY_ECT_FIELD_SIG_BIT_ECC   0x05
#define SMBIOS_TABLE69_MEMORY_ARRAY_ECT_FIELD_MULTI_BIT_ECC 0x06
#define SMBIOS_TABLE69_MEMORY_ARRAY_ECT_FIELD_CRC           0x07

/************************************************************************/
/*				TYPE	17 TABLE MEMORY DEVICE INFO                     */
/************************************************************************/
#define SMBIOS_TYPE17_PHYSICAL_MEMORY_ARRAY_HANDLE_2BYTE 0x04
#define SMBIOS_TYPE17_MEM_ERROR_INFO_HANDLE_2BYTE        0x06
#define SMBIOS_TYPE17_TOTAL_WIDTH_2BYTE                  0x08
#define SMBIOS_TYPE17_DATA_WIDTH_2BYTE			         0x0A
#define SMBIOS_TYPE17_SIZE_2BYTE				         0x0C
#define SMBIOS_TYPE17_FORM_FACTOR_1BYTE                  0x0E
#define SMBIOS_TYPE17_DEVICE_SET_1BYTE                   0x0F
#define SMBIOS_TYPE17_DEVICE_LOCATOR_STRING              0x10
#define SMBIOS_TYPE17_BANK_LOCATOR_STRING                0x11
#define SMBIOS_TYPE17_MEMORY_TYPE_1BYTE                  0x12
#define SMBIOS_TYPE17_TYPE_DETAIL_2BYTE                  0x13
#define SMBIOS_TYPE17_SPEED_2BYTE                        0x15
#define SMBIOS_TYPE17_MANUFACTURER_STRING                0x17
#define SMBIOS_TYPE17_SERIAL_NUM_STRING                  0x18
#define SMBIOS_TYPE17_ASSET_TAG_STRING                   0x19
#define SMBIOS_TYPE17_PART_NUMBER_STRING                 0x1A
#define SMBIOS_TYPE17_ATTRIBUTES_1BYTE                   0x1B
#define SMBIOS_TYPE17_EXTENDED_SIZE_4BYTE                0x1C
#define SMBIOS_TYPE17_CONFIGURED_MEMORY_CLK_SPEED_2BYTE  0x20
#define SMBIOS_TYPE17_MIN_VOLTAGE_2BYTE                  0x22
#define SMBIOS_TYPE17_MAX_VOLTAGE_2BYTE					 0x24
#define SMBIOS_TYPE17_CONFIGURED_VOLTAGE_2BYTE           0x26

/************************************************************************/
/*				Memory Device: Form Factor field                        */
/************************************************************************/
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_OTHER        0x01
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_UNKOWN       0x02
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_SIMM         0x03
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_SIP          0x04
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_CHIP         0x05
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_DIP          0x06
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_ZIP          0x07
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_PROCARD      0x08
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_DIMM         0x09
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_TSOP         0x0A
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_ROW_OF_CHIPS 0x0B
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_RIMM         0x0C
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_SODIMM       0x0D
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_SRIMM        0x0E
#define SMBIOS_TABLE72_MEMORY_DEVICE_FF_FB_DIMM      0x0F

/************************************************************************/
/*				Memory Device: Type                                     */
/************************************************************************/
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_OTHER         0x01
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_UNKNOWN       0x02
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_DRAM          0x03
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_EDRAM         0x04
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_VRAM          0x05
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_SRAM          0x06
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_RAM           0x07
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_ROM           0x08
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_FLASH         0x09
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_EEPROM        0x0A
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_FEPROM        0x0B
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_EPROM         0x0C
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_CDRAM         0x0D
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_3DRAM         0x0E
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_SDRAM         0x0F
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_SGRAM         0x10
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_RDRAM         0x11
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_DDR           0x12
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_DDR2          0x13
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_DDR2_FB_DIMM  0x14
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_RESERVED1     0x15
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_RESERVED2     0x16
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_RESERVED3     0x17
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_DDR3          0x18
#define SMBIOS_TABLE73_MEMORY_DEVICE_TYPE_FBD2          0x19

/************************************************************************/
/*				Memory Device:  Type Detail Field					    */
/************************************************************************/
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_RESERVED      0x00
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_OTHER         0x02
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_UNKNOWN       0x04
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_FAST_PAGED    0x08
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_STATIC_COLUMN 0x10
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_PSEUDO_STATIC 0x20
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_RAMBUS        0x40
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_SYNCHRONOUS   0x80
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_CMOS          0x100
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_EDO           0x200
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_WINDOW_DRAM   0x400
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_CACHE_DRAM    0x800
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_NON_VOLATILE  0x1000
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_REGISTERED    0x2000
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_UNBUFFERED    0x4000
#define SMBIOS_TABLE73_MEMORY_DEVICE_TD_LRDIMM        0x8000

#endif // !_SMBIOS_TABLE_H_
