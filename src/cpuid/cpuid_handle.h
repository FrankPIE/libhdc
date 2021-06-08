/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_CPUID_HANDLE_H_
#define _HDC_CPUID_HANDLE_H_

#include <cpuid/cpuid.h>

#include <common/hashmap.h>

struct _cpuid_handle_virtual_table_ptr_t
{
	int (*get_cpuid_identify_string)(cpuid_handle_t* handle, char* buffer);

	int (*get_cpuid_serial_number)(cpuid_handle_t* handle, hdc_uuid_t* buffer);

	int  (*get_cpuid_standard_function_number)(cpuid_handle_t* handle);

	int  (*get_cpuid_family)(cpuid_handle_t* handle);

	int  (*get_cpuid_model)(cpuid_handle_t* handle);

	int  (*get_cpuid_stepping)(cpuid_handle_t* handle);

	int  (*get_cpuid_extended_family)(cpuid_handle_t* handle);

	int  (*get_cpuid_extended_model)(cpuid_handle_t* handle);

	bool (*is_cpuid_sse3_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pclmuldq_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_dtes64_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_monitor_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_ds_cpl_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_vmx_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_smx_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_eist_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_tm2_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_ssse3_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_cnxt_id_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_sdbg_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_fma_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_cx16_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_xtpr_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pdcm_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pcid_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_dca_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_sse4_1_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_sse4_2_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_x2apic_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_movbe_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_popcnt_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_tsc_deadline_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_aes_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_xsave_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_osxsave_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_avx_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_f16c_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_rdrand_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_fpu_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_vme_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_de_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pse_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_tsc_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_msr_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pae_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_mce_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_cx8_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_apic_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_sep_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_mtrr_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pge_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_mca_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_cmov_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pat_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pse_36_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_psn_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_clfsh_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_ds_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_acpi_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_mmx_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_fxsr_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_sse_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_sse2_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_ss_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_htt_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_tm_support)(cpuid_handle_t* handle);

	bool (*is_cpuid_pbe_support)(cpuid_handle_t* handle);

	const char* (*get_cpuid_processor_type)(cpuid_handle_t* handle);
};

struct _cpuid_handle_t
{
	struct _cpuid_handle_virtual_table_ptr_t vptrt;

	bool cpuid_support;
	int  vendor_type;
	char identify[49];

	cpu_cache_t* caches;
	uint32_t     cache_size;
};

struct _intel_cpuid_handle_t
{
	struct _cpuid_handle_t super;

	hash_map_t*  brand_index_map;
	hash_map_t*  processor_type_map;

	uint32_t	 brand_index;
	uint32_t	 clflush_line_size;
	uint32_t	 logical_core_number;
	uint32_t	 apic_id;
	uint32_t     stepping;
	uint32_t     model;
	uint32_t     family;
	uint32_t     processor_type;

	uint32_t     extended_model;
	uint32_t     extended_family;

	uint32_t     ecx_feature_flags;
	uint32_t     edx_feature_flags;
};

struct _amd_cpuid_handle_t
{
	struct _cpuid_handle_t super;
};

struct _arm_cpuid_handle_t
{
	struct _cpuid_handle_t super;
};

cpuid_handle_t* intel_cpuid_handle_init();

cpuid_handle_t* amd_cpuid_handle_init();

cpuid_handle_t* arm_cpuid_handle_init();

void			intel_cpuid_handle_destroy(cpuid_handle_t* handle);

#endif