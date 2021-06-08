/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include <cpuid/cpuid.h>
#include <cpuid/cpuid_type.h>
#include <cpuid/cpuid_handle.h>

#include <common/hashmap.h>
#include <common/errorc.h>

/* ***********************interface*********************** */

/* cpuid_instructs */
extern void cpuid(uint32_t registers[4], uint32_t function_id);

extern void cpuidex(uint32_t registers[4], uint32_t function_id, uint32_t sub_function_id);

/* ***********************implement*********************** */
hash_map_t* intel_cpuid_brand_index_table()
{
#define MakeIndexIncrement (++index, sizeof(int))
	hash_map_t* hash_map = NULL;

	int index = 0x01;

	hash_map_item_t table[] =
	{
		//index == 01h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		//index == 02h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III processor")),

		//index == 03h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III Xeon(R) processor")),

		//index == 04h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) III processor")),

		// index == 05h, equal index == 03h and signature = 0x06B1
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 06h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Pentium(R) III processor-M")),

		// index == 07h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 08h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) 4 processor")),

		// index == 09h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) 4 processor")),

		// index == 0Ah
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 0Bh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor")),

		// index == 0Ch
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor MP")),

		// index == 0Dh, equal index == 0Bh and signature = 0x0F13
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor MP")),

		// index == 0Eh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Pentium(R) 4 processor-M")),

		// index == 0Fh
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 10h, equal index == 0Eh and signature = 0x0F13
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Xeon(R) processor")),

		// index == 11h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Genuine Intel(R) processor")),

		// index == 12h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron M processor")),

		// index == 13h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),

		// index == 14h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Celeron(R) processor")),

		// index == 15h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Genuine Intel(R) processor")),

		// index == 16h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Intel(R) Pentium(R) M processor")),

		// index == 17h
		make_pair(make_buffer_key((unsigned char*)&index, MakeIndexIncrement), make_string_value("Mobile Intel(R) Celeron(R) processor")),
	};

	hash_map_init(&hash_map, table, sizeof(table) / sizeof(hash_map_item_t));

#undef MakeIndexIncrement
	return hash_map;
}

hash_map_t* intel_cpuid_processor_type_table()
{
	hash_map_t* hash_map = NULL;

	int oem = 0;
	int over_drive = 1;
	int dual = 2;

	hash_map_item_t items[] = 
	{
		make_pair(make_buffer_key((unsigned char*)&oem, sizeof(int)), make_string_value("Original OEM Processor")),
		make_pair(make_buffer_key((unsigned char*)&over_drive, sizeof(int)), make_string_value("Intel OverDrive Processor")),
		make_pair(make_buffer_key((unsigned char*)&dual, sizeof(int)), make_string_value("Dual Processor")),
	};

	hash_map_init(&hash_map, items, sizeof(items) / sizeof(hash_map_item_t));

	return hash_map;
}

int intel_cpuid_cache_information(struct _intel_cpuid_handle_t* handle, cpu_cache_t* caches, uint32_t* size)
{
	uint32_t index = 0;
	uint32_t type = 0;
	hdc_cpu_register_t cpu_register = { 0U };

	assert(handle->super.cpuid_support);

	if (caches == NULL)
	{
		do
		{
			cpuidex(cpu_register.registers, 4, index);

			type = cpu_register.eax & 0XF;
			
			++index;
		}
		while (type != 0);

		if (size)
			*size = index - 1;

		return (int)index - 1;
	}
	
	assert(size != NULL && caches != NULL);

	while (index < *size)
	{
		cpuidex(cpu_register.registers, 4, index);

		caches[index].cache_type  = cpu_register.eax & 0X1F;
		caches[index].cache_level = (cpu_register.eax & 0XE0) >> 5;
		
		++index;
	}
	
	return *size;
}

bool intel_cpuid_feature_flag_ecx(cpuid_handle_t* handle, int flag)
{
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	assert(handle->cpuid_support);
	assert(intel_handle->ecx_feature_flags != 0);
	
	return (intel_handle->ecx_feature_flags & flag);
}

bool intel_cpuid_feature_flag_edx(cpuid_handle_t* handle, int flag)
{
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	assert(handle->cpuid_support);
	assert(intel_handle->edx_feature_flags != 0);

	return (intel_handle->edx_feature_flags & flag);
}

bool intel_cpuid_brand_string(char* buffer)
{
	hdc_cpu_register_t cpu_register = { 0U };

	cpuid(cpu_register.registers, 0x80000000);

	if (cpu_register.eax >= 0x80000004)
	{
		cpuid(cpu_register.registers, 0x80000002);
		memcpy(buffer, cpu_register.registers, 16);

		cpuid(cpu_register.registers, 0x80000003);
		memcpy(buffer + 16, cpu_register.registers, 16);

		cpuid(cpu_register.registers, 0x80000004);
		memcpy(buffer + 32, cpu_register.registers, 16);

		return true;
	}

	return false;
}

bool intel_cpuid_brand_id(char* buffer, hash_map_t* brand_id_map)
{
	unsigned int flag = 0;
	hdc_cpu_register_t cpu_register = { 0U };

	cpuid(cpu_register.registers, 1);

	flag = cpu_register.ebx & 0xFF;

	if (flag != 0)
	{
		if (flag == 0x03 && cpu_register.eax == 0x06B1)
			flag = 0x05;

		if (flag == 0x0b && cpu_register.eax == 0x0F13)
			flag = 0x0d;

		if (flag == 0x0e && cpu_register.eax == 0x0F13)
			flag = 0x10;

		if (brand_id_map)
		{
			char* brand_string = NULL;

			hash_map_find(brand_id_map, make_buffer_key((unsigned char*)&flag, sizeof(flag)), (void**)&brand_string);

			memcpy(buffer, brand_string, strlen(brand_string));
		}

		return true;
	}

	return false;
}

int intel_cpuid_identify_string(cpuid_handle_t* handle, char* buffer)
{
	assert(handle->cpuid_support);

	if (strlen(buffer) != 0)
		return HDC_EC_ERROR_PARAMETER;

	if (intel_cpuid_brand_string(buffer))
		return HDC_SUCCESS;

	if (intel_cpuid_brand_id(buffer, ((struct _intel_cpuid_handle_t*)handle)->brand_index_map))
		return HDC_SUCCESS;
	
	return HDC_EC_TOO_OLD_CPU_PRODUCT;
}

const char* intel_cpuid_processor_type(cpuid_handle_t* handle)
{
	char* value;
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	const key_t key = make_buffer_key((unsigned char*)&intel_handle->processor_type, sizeof(intel_handle->processor_type));

	assert(handle->cpuid_support);

	hash_map_find(intel_handle->processor_type_map, key, (void**)&value);

	if (value == NULL)
		return "Not Support";

	return value;
}

bool intel_cpuid_sse3_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_SSE3_FLAG);
}

bool intel_cpuid_pclmuldq_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_PCLMULDQ_FLAG);
}

bool intel_cpuid_dtes64_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_DTES64_FLAG);
}

bool intel_cpuid_monitor_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_MONITOR_FLAG);
}

bool intel_cpuid_ds_cpl_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_DS_CPL_FLAG);
}

bool intel_cpuid_vmx_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_VMX_FLAG);
}

bool intel_cpuid_smx_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_SMX_FLAG);
}

bool intel_cpuid_eist_support(cpuid_handle_t* handle)
{	
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_EIST_FLAG);
}

bool intel_cpuid_tm2_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_TM2_FLAG);
}

bool intel_cpuid_ssse3_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_SSSE3_FLAG);
}

bool intel_cpuid_cnxt_id_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_CNXT_1D_FLAG);
}

bool intel_cpuid_sdbg_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_SDBG_FLAG);
}

bool intel_cpuid_fma_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_FMA_FLAG);
}

bool intel_cpuid_cx16_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_CX16_FLAG);
}

bool intel_cpuid_xtpr_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_XTPR_FLAG);
}

bool intel_cpuid_pdcm_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_PDCM_FLAG);
}

bool intel_cpuid_pcid_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_PCID_FLAG);
}

bool intel_cpuid_dca_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_DCA_FLAG);
}

bool intel_cpuid_sse4_1_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_SSE4_1_FLAG);
}

bool intel_cpuid_sse4_2_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_SSE4_2_FLAG);
}

bool intel_cpuid_x2apic_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_X2APIC_FLAG);
}

bool intel_cpuid_movbe_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_MOVBE_FLAG);
}

bool intel_cpuid_popcnt_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_POPCNT_FLAG);
}

bool intel_cpuid_tsc_deadline_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_TSC_DEADLINE_FLAG);
}

bool intel_cpuid_aes_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_AES_FLAG);
}

bool intel_cpuid_xsave_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_XSAVE_FLAG);
}

bool intel_cpuid_osxsave_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_OSXSAVE_FLAG);
}

bool intel_cpuid_avx_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_AVX_FLAG);
}

bool intel_cpuid_f16c_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_F16C_FLAG);
}

bool intel_cpuid_rdrand_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_ecx(handle, HDC_CPUID_INTEL_RDRAND_FLAG);
}

bool intel_cpuid_fpu_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_FPU_FLAG);
}

bool intel_cpuid_vme_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_VME_FLAG);
}

bool intel_cpuid_de_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_DE_FLAG);
}

bool intel_cpuid_pse_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_PSE_FLAG);
}

bool intel_cpuid_tsc_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_TSC_FLAG);
}

bool intel_cpuid_msr_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_MSR_FLAG);
}

bool intel_cpuid_pae_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_PAE_FLAG);
}

bool intel_cpuid_mce_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_MCE_FLAG);
}

bool intel_cpuid_cx8_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_CX8_FLAG);
}

bool intel_cpuid_apic_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_APIC_FLAG);
}

bool intel_cpuid_sep_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_SEP_FLAG);
}

bool intel_cpuid_mtrr_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_MTRR_FLAG);
}

bool intel_cpuid_pge_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_PGE_FLAG);
}

bool intel_cpuid_mca_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_MCA_FLAG);
}

bool intel_cpuid_cmov_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_CMOV_FLAG);
}

bool intel_cpuid_pat_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_PAT_FLAG);
}

bool intel_cpuid_pse_36_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_PSE36_FLAG);
}

bool intel_cpuid_psn_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_PSN_FLAG);
}

bool intel_cpuid_clfsh_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_CLFSH_FLAG);
}

bool intel_cpuid_ds_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_DS_FLAG);
}

bool intel_cpuid_acpi_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_ACPI_FLAG);
}

bool intel_cpuid_mmx_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_MMX_FLAG);
}

bool intel_cpuid_fxsr_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_FXSR_FLAG);
}

bool intel_cpuid_sse_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_SSE_FLAG);
}

bool intel_cpuid_sse2_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_SSE2_FLAG);
}

bool intel_cpuid_ss_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_SS_FLAG);
}

bool intel_cpuid_htt_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_HTT_FLAG);
}

bool intel_cpuid_tm_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_TM_FLAG);
}

bool intel_cpuid_pbe_support(cpuid_handle_t* handle)
{
	return intel_cpuid_feature_flag_edx(handle, HDC_CPUID_INTEL_PBE_FLAG);
}

int intel_cpuid_serial_number(cpuid_handle_t* handle, hdc_uuid_t* uuid)
{
	hdc_cpu_register_t cpu_register = { 0U };

	assert(handle->cpuid_support);

	memset(uuid->uuid, 0, 16);

	cpuid(cpu_register.registers, 1);
	
	if (intel_cpuid_psn_support(handle))
	{
		memcpy(uuid->uuid + 4, &cpu_register.eax, 4);

		cpuid(cpu_register.registers, 3);

		memcpy(uuid->uuid + 8, &cpu_register.edx, 4);

		memcpy(uuid->uuid + 12, &cpu_register.ecx, 4);

		return HDC_SUCCESS;
	}

	return HDC_EC_CPUID_SERIAL_NUMBER_NOT_SUPPORT;
}

int intel_get_cpuid_processor_family(cpuid_handle_t* handle)
{
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	assert(handle->cpuid_support);

	return (int)(intel_handle->family);
}

int intel_get_cpuid_processor_model(cpuid_handle_t* handle)
{
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	assert(handle->cpuid_support);

	return (int)(intel_handle->model);
}

int intel_get_cpuid_processor_stepping(cpuid_handle_t* handle)
{
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	assert(handle->cpuid_support);

	return (int)(intel_handle->stepping);
}

int intel_get_cpuid_processor_extended_family(cpuid_handle_t* handle)
{
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	assert(handle->cpuid_support);

	return (int)(intel_handle->family != 0xF ? intel_handle->family : intel_handle->family + intel_handle->extended_family);
}

int intel_get_cpuid_processor_extended_model(cpuid_handle_t* handle)
{
	struct _intel_cpuid_handle_t* intel_handle = (struct _intel_cpuid_handle_t*)handle;

	assert(handle->cpuid_support);

	return (int)((intel_handle->family == 0xF || intel_handle->family == 0x6) ? (intel_handle->extended_model << 4) + intel_handle->model : intel_handle->model);
}

int intel_get_cpuid_standard_function_number(cpuid_handle_t* handle)
{
	hdc_cpu_register_t cpu_register = { 0U };

	assert(handle->cpuid_support);

	cpuid(cpu_register.registers, 0);

	return (int)cpu_register.eax;
}

cpuid_handle_t* intel_cpuid_handle_init()
{
	hdc_cpu_register_t cpu_register = { 0U };

	struct _intel_cpuid_handle_t* handle = (struct _intel_cpuid_handle_t*)malloc(sizeof(struct _intel_cpuid_handle_t));

	if (handle)
	{		
		handle->super.cpuid_support = true;

		handle->super.vendor_type = HDC_CPU_VENDOR_INTEL;

		memset(handle->super.identify, '\0', sizeof(handle->super.identify));

		handle->super.cache_size = intel_cpuid_cache_information(handle, NULL, &handle->super.cache_size);

		handle->super.caches = (cpu_cache_t*)malloc(sizeof(cpu_cache_t) * handle->super.cache_size);

		intel_cpuid_cache_information(handle, handle->super.caches, &handle->super.cache_size);

		handle->brand_index_map = intel_cpuid_brand_index_table();
		handle->processor_type_map = intel_cpuid_processor_type_table();

		cpuid(cpu_register.registers, 1);

		handle->brand_index = cpu_register.ebx & 0xFF;
		handle->clflush_line_size = (cpu_register.ebx & 0xFF00) >> 8;
		handle->logical_core_number = (cpu_register.ebx & 0xFF0000) >> 16;
		handle->apic_id = (cpu_register.ebx & 0xFF000000) >> 24;

		handle->stepping = cpu_register.eax & 0xF;
		handle->model = (cpu_register.eax & 0xF0) >> 4;
		handle->family = (cpu_register.eax & 0xF00) >> 8;
		handle->processor_type = (cpu_register.eax & 0x3000) >> 12;
		handle->extended_model = (cpu_register.eax & 0xF0000) >> 16;
		handle->extended_family = (cpu_register.eax & 0xFF00000) >> 20;

		handle->ecx_feature_flags = cpu_register.ecx;
		handle->edx_feature_flags = cpu_register.edx;

		handle->super.vptrt.get_cpuid_identify_string = intel_cpuid_identify_string;
		handle->super.vptrt.get_cpuid_serial_number   = intel_cpuid_serial_number;
		handle->super.vptrt.get_cpuid_standard_function_number = intel_get_cpuid_standard_function_number;
		handle->super.vptrt.get_cpuid_processor_type = intel_cpuid_processor_type;
		handle->super.vptrt.get_cpuid_family = intel_get_cpuid_processor_family;
		handle->super.vptrt.get_cpuid_model = intel_get_cpuid_processor_model;
		handle->super.vptrt.get_cpuid_stepping = intel_get_cpuid_processor_stepping;
 		handle->super.vptrt.get_cpuid_extended_family = intel_get_cpuid_processor_extended_family;
		handle->super.vptrt.get_cpuid_extended_model = intel_get_cpuid_processor_extended_model;

		handle->super.vptrt.is_cpuid_sse3_support = intel_cpuid_sse3_support;
		handle->super.vptrt.is_cpuid_pclmuldq_support = intel_cpuid_pclmuldq_support;
		handle->super.vptrt.is_cpuid_dtes64_support = intel_cpuid_dtes64_support;
		handle->super.vptrt.is_cpuid_monitor_support = intel_cpuid_monitor_support;
		handle->super.vptrt.is_cpuid_ds_cpl_support = intel_cpuid_ds_cpl_support;
		handle->super.vptrt.is_cpuid_vmx_support = intel_cpuid_vmx_support;
		handle->super.vptrt.is_cpuid_smx_support = intel_cpuid_smx_support;
		handle->super.vptrt.is_cpuid_eist_support = intel_cpuid_eist_support;
		handle->super.vptrt.is_cpuid_tm2_support = intel_cpuid_tm2_support;
		handle->super.vptrt.is_cpuid_ssse3_support = intel_cpuid_ssse3_support;
		handle->super.vptrt.is_cpuid_cnxt_id_support = intel_cpuid_cnxt_id_support;
		handle->super.vptrt.is_cpuid_fma_support = intel_cpuid_fma_support;
		handle->super.vptrt.is_cpuid_sdbg_support = intel_cpuid_sdbg_support;
		handle->super.vptrt.is_cpuid_cx16_support = intel_cpuid_cx16_support;
		handle->super.vptrt.is_cpuid_xtpr_support = intel_cpuid_xtpr_support;
		handle->super.vptrt.is_cpuid_pdcm_support = intel_cpuid_pdcm_support;
		handle->super.vptrt.is_cpuid_pcid_support = intel_cpuid_pcid_support;
		handle->super.vptrt.is_cpuid_dca_support  = intel_cpuid_dca_support;
		handle->super.vptrt.is_cpuid_sse4_1_support = intel_cpuid_sse4_1_support;
		handle->super.vptrt.is_cpuid_sse4_2_support = intel_cpuid_sse4_2_support;
		handle->super.vptrt.is_cpuid_x2apic_support = intel_cpuid_x2apic_support;
		handle->super.vptrt.is_cpuid_movbe_support = intel_cpuid_movbe_support;
		handle->super.vptrt.is_cpuid_popcnt_support = intel_cpuid_popcnt_support;
		handle->super.vptrt.is_cpuid_tsc_deadline_support = intel_cpuid_tsc_deadline_support;
		handle->super.vptrt.is_cpuid_aes_support = intel_cpuid_aes_support;
		handle->super.vptrt.is_cpuid_xsave_support = intel_cpuid_xsave_support;
		handle->super.vptrt.is_cpuid_osxsave_support = intel_cpuid_osxsave_support;
		handle->super.vptrt.is_cpuid_avx_support = intel_cpuid_avx_support;
		handle->super.vptrt.is_cpuid_f16c_support = intel_cpuid_f16c_support;
		handle->super.vptrt.is_cpuid_rdrand_support = intel_cpuid_rdrand_support;
		handle->super.vptrt.is_cpuid_fpu_support = intel_cpuid_fpu_support;
		handle->super.vptrt.is_cpuid_vme_support = intel_cpuid_vme_support;
		handle->super.vptrt.is_cpuid_de_support = intel_cpuid_de_support;
		handle->super.vptrt.is_cpuid_pse_support = intel_cpuid_pse_support;
		handle->super.vptrt.is_cpuid_tsc_support = intel_cpuid_tsc_support;
		handle->super.vptrt.is_cpuid_msr_support = intel_cpuid_msr_support;
		handle->super.vptrt.is_cpuid_pae_support = intel_cpuid_pae_support;
		handle->super.vptrt.is_cpuid_mce_support = intel_cpuid_mce_support;
		handle->super.vptrt.is_cpuid_cx8_support = intel_cpuid_cx8_support;
		handle->super.vptrt.is_cpuid_apic_support = intel_cpuid_apic_support;
		handle->super.vptrt.is_cpuid_sep_support = intel_cpuid_sep_support;
		handle->super.vptrt.is_cpuid_mtrr_support = intel_cpuid_mtrr_support;
		handle->super.vptrt.is_cpuid_pge_support = intel_cpuid_pge_support;
		handle->super.vptrt.is_cpuid_mca_support = intel_cpuid_mca_support;
		handle->super.vptrt.is_cpuid_cmov_support = intel_cpuid_cmov_support;
		handle->super.vptrt.is_cpuid_pat_support = intel_cpuid_pat_support;
		handle->super.vptrt.is_cpuid_pse_36_support = intel_cpuid_pse_36_support;
		handle->super.vptrt.is_cpuid_psn_support = intel_cpuid_psn_support;
		handle->super.vptrt.is_cpuid_clfsh_support = intel_cpuid_clfsh_support;
		handle->super.vptrt.is_cpuid_ds_support = intel_cpuid_ds_support;
		handle->super.vptrt.is_cpuid_acpi_support = intel_cpuid_acpi_support;
		handle->super.vptrt.is_cpuid_mmx_support = intel_cpuid_mmx_support;
		handle->super.vptrt.is_cpuid_fxsr_support = intel_cpuid_fxsr_support;
		handle->super.vptrt.is_cpuid_sse_support = intel_cpuid_sse_support;
		handle->super.vptrt.is_cpuid_sse2_support = intel_cpuid_sse2_support;
		handle->super.vptrt.is_cpuid_ss_support = intel_cpuid_ss_support;
		handle->super.vptrt.is_cpuid_htt_support = intel_cpuid_htt_support;
		handle->super.vptrt.is_cpuid_tm_support = intel_cpuid_tm_support;
		handle->super.vptrt.is_cpuid_pbe_support = intel_cpuid_pbe_support;

		return (cpuid_handle_t*)handle;
	}

	return NULL;
}

void intel_cpuid_handle_destroy(cpuid_handle_t* handle)
{
	if (handle)
	{
		hash_map_destroy(((struct _intel_cpuid_handle_t*)handle)->brand_index_map);

		free(handle);
	}
}
