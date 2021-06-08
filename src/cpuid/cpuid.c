/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <cpuid/cpuid.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <cpuid/cpuid_type.h>
#include <cpuid/cpuid_handle.h>

#include <common/errorc.h>
#include <common/hashmap.h>

extern bool		   cpuid_flag_check();
extern void		   cpuid(uint32_t registers[4], uint32_t function_id);

extern const char* error_information(int error_code);

/* ***********************implement*********************** */

hash_map_t* cpuid_vendor_table()
{
	hash_map_t* hash_map = NULL;

	const int intel_flag = HDC_CPU_VENDOR_INTEL;
	const int amd_flag = HDC_CPU_VENDOR_AMD;

	hash_map_item_t table[] =
	{
		make_pair(make_string_key("GenuineIntel"), make_buffer_value((void*)&intel_flag, sizeof(int))),
		make_pair(make_string_key("AuthenticAMD"), make_buffer_value((void*)&amd_flag, sizeof(int))),
	};

	hash_map_init(&hash_map, table, sizeof(table) / sizeof(hash_map_item_t));

	return hash_map;
}

int hdc_cpuid_init(cpuid_handle_t** handle)
{
	assert(*handle == NULL);

	char vendor[13] = { '\0' };

	hdc_cpu_register_t cpu_info = { 0u };
	hash_map_item_t    item = { 0 };

	hash_map_t* vendor_map = cpuid_vendor_table();

	if (!cpuid_flag_check())
		return HDC_EC_CPUID_NOT_SUPPORT;

	cpuid(cpu_info.registers, 0);

	memcpy(vendor, &cpu_info.ebx, 4);
	memcpy(vendor + 8, &cpu_info.ecx, 4);
	memcpy(vendor + 4, &cpu_info.edx, 4);

	item.key = make_string_key(vendor);

	hash_map_find(vendor_map, item.key, (value_t*)&item.value);

	switch (*(int*)item.value)
	{
	case HDC_CPU_VENDOR_INTEL:
		*handle = intel_cpuid_handle_init();
		break;

	default:
		break;
	}

	if (*handle == NULL)
		return HDC_EC_BAD_ALLOC;

	if (vendor_map)
		hash_map_destroy(vendor_map);

	return HDC_SUCCESS;
}

int hdc_cpuid_standard_function_number(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (handle->cpuid_support)
		return handle->vptrt.get_cpuid_standard_function_number(handle);
	
	return HDC_EC_CPUID_NOT_SUPPORT;
}

int hdc_cpuid_cpu_vendor(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (handle->cpuid_support)
		return handle->vendor_type;

	return HDC_EC_CPUID_NOT_SUPPORT;
}

int hdc_cpuid_cpu_family(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (handle->cpuid_support)
		return handle->vptrt.get_cpuid_family(handle);

	return HDC_EC_CPUID_NOT_SUPPORT;
}

int hdc_cpuid_cpu_model(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (handle->cpuid_support)
		return handle->vptrt.get_cpuid_model(handle);

	return HDC_EC_CPUID_NOT_SUPPORT;
}

int hdc_cpuid_cpu_stepping(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (handle->cpuid_support)
		return handle->vptrt.get_cpuid_stepping(handle);

	return HDC_EC_CPUID_NOT_SUPPORT;
}

int hdc_cpuid_cpu_extended_family(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (handle->cpuid_support)
		return handle->vptrt.get_cpuid_extended_family(handle);

	return HDC_EC_CPUID_NOT_SUPPORT;
}

int hdc_cpuid_cpu_extended_model(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (handle->cpuid_support)
		return handle->vptrt.get_cpuid_extended_model(handle);

	return HDC_EC_CPUID_NOT_SUPPORT;
}

const char* hdc_cpuid_cpu_identify(cpuid_handle_t* handle)
{
	if(strlen(handle->identify) == 0)
	{
		const int error_code = handle->vptrt.get_cpuid_identify_string(handle, handle->identify);
		
		if (error_code == HDC_SUCCESS)
			return handle->identify;

		return error_information(error_code);
	}
	
	return handle->identify;
}

const char* hdc_cpuid_processor_type(cpuid_handle_t* handle)
{
	return handle->vptrt.get_cpuid_processor_type(handle);
}

bool hdc_cpuid_cpu_psn_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_psn_support(handle);
}

bool hdc_cpuid_cpu_clfsh_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_clfsh_support(handle);
}

bool hdc_cpuid_cpu_ds_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_ds_support(handle);
}

bool hdc_cpuid_cpu_acpi_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_acpi_support(handle);
}

bool hdc_cpuid_cpu_mmx_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_mmx_support(handle);
}

bool hdc_cpuid_cpu_fxsr_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_fxsr_support(handle);
}

bool hdc_cpuid_cpu_sse_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_sse_support(handle);
}

bool hdc_cpuid_cpu_sse2_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_sse2_support(handle);
}

bool hdc_cpuid_cpu_ss_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_ss_support(handle);
}

bool hdc_cpuid_cpu_htt_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_htt_support(handle);
}

bool hdc_cpuid_cpu_tm_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_tm_support(handle);
}

bool hdc_cpuid_cpu_pbe_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pbe_support(handle);
}

bool hdc_cpuid_cpu_sse3_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_sse3_support(handle);
}

bool hdc_cpuid_cpu_pclmuldq_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pclmuldq_support(handle);
}

bool hdc_cpuid_cpu_dtes64_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_dtes64_support(handle);
}

bool hdc_cpuid_cpu_monitor_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_monitor_support(handle);
}

bool hdc_cpuid_cpu_ds_cpl_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_ds_cpl_support(handle);
}

bool hdc_cpuid_cpu_vmx_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_vmx_support(handle);
}

bool hdc_cpuid_cpu_smx_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_smx_support(handle);
}

bool hdc_cpuid_cpu_eist_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_eist_support(handle);
}

bool hdc_cpuid_cpu_tm2_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_tm2_support(handle);
}

bool hdc_cpuid_cpu_ssse3_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_ssse3_support(handle);
}

bool hdc_cpuid_cpu_cnxt_id_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_cnxt_id_support(handle);
}

bool hdc_cpuid_cpu_fma_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_fma_support(handle);
}

bool hdc_cpuid_cpu_sdbg_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_sdbg_support(handle);
}

bool hdc_cpuid_cpu_cx16_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_cx16_support(handle);
}

bool hdc_cpuid_cpu_xtpr_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_xtpr_support(handle);
}

bool hdc_cpuid_cpu_pdcm_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pdcm_support(handle);
}

bool hdc_cpuid_cpu_pcid_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pcid_support(handle);
}

bool hdc_cpuid_cpu_dca_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_dca_support(handle);
}

bool hdc_cpuid_cpu_sse4_1_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_sse4_1_support(handle);
}

bool hdc_cpuid_cpu_sse4_2_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_sse4_2_support(handle);
}

bool hdc_cpuid_cpu_x2apic_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_x2apic_support(handle);
}

bool hdc_cpuid_cpu_movbe_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_movbe_support(handle);
}

bool hdc_cpuid_cpu_popcnt_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_popcnt_support(handle);
}

bool hdc_cpuid_cpu_tsc_deadline_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_tsc_deadline_support(handle);
}

bool hdc_cpuid_cpu_aes_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_aes_support(handle);
}

bool hdc_cpuid_cpu_xsave_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_xsave_support(handle);
}

bool hdc_cpuid_cpu_osxsave_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_osxsave_support(handle);
}

bool hdc_cpuid_cpu_avx_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_avx_support(handle);
}

bool hdc_cpuid_cpu_f16c_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_f16c_support(handle);
}

bool hdc_cpuid_cpu_rdrand_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_rdrand_support(handle);
}

bool hdc_cpuid_cpu_fpu_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_fpu_support(handle);
}

bool hdc_cpuid_cpu_vme_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_vme_support(handle);
}

bool hdc_cpuid_cpu_de_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_de_support(handle);
}

bool hdc_cpuid_cpu_pse_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pse_support(handle);
}

bool hdc_cpuid_cpu_tsc_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_tsc_support(handle);
}

bool hdc_cpuid_cpu_msr_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_msr_support(handle);
}

bool hdc_cpuid_cpu_pae_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pae_support(handle);
}

bool hdc_cpuid_cpu_mce_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_mce_support(handle);
}

bool hdc_cpuid_cpu_cx8_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_cx8_support(handle);
}

bool hdc_cpuid_cpu_apic_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_apic_support(handle);
}

bool hdc_cpuid_cpu_sep_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_sep_support(handle);
}

bool hdc_cpuid_cpu_mtrr_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_mtrr_support(handle);
}

bool hdc_cpuid_cpu_pge_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pge_support(handle);
}

bool hdc_cpuid_cpu_mca_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_mca_support(handle);
}

bool hdc_cpuid_cpu_cmov_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_cmov_support(handle);
}

bool hdc_cpuid_cpu_pat_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pat_support(handle);
}

bool hdc_cpuid_cpu_pse_36_support(cpuid_handle_t* handle)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return false;

	return handle->vptrt.is_cpuid_pse_36_support(handle);
}

int hdc_cpuid_cpu_serial_number(cpuid_handle_t* handle, hdc_uuid_t* uuid)
{
	assert(handle->cpuid_support);

	if (!handle->cpuid_support)
		return HDC_EC_CPUID_NOT_SUPPORT;

	return handle->vptrt.get_cpuid_serial_number(handle, uuid);
}

void hdc_cpuid_destroy(cpuid_handle_t* handle)
{
	if (handle)
	{
		switch (handle->vendor_type)
		{
		case HDC_CPU_VENDOR_INTEL:
			intel_cpuid_handle_destroy(handle);
			break;

		default:
			break;
		}
	}
}
