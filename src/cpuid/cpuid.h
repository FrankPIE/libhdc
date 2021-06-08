/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_CPUID_H_
#define _HDC_CPUID_H_

#include <stdbool.h>
#include <common/uuid.h>

#define HDC_CPU_VENDOR_UNKNOWN 0
#define HDC_CPU_VENDOR_INTEL   1
#define HDC_CPU_VENDOR_AMD	   2
#define HDC_CPU_VENDOR_ARM     3

#define HDC_CPU_UNKNOWN_CACHE     0
#define HDC_CPU_DATA_CACHE        1
#define HDC_CPU_INSTRUCTION_CACHE 2
#define HDC_CPU_UNIFIED_CACHE     3

typedef struct _cpu_cache_t
{
	bool		self_initializing_cache_level;
	bool	    fully_associative_cache;
	uint32_t	cache_type;
	uint32_t	cache_level;
} cpu_cache_t;

typedef struct _cpuid_handle_t cpuid_handle_t;

int  hdc_cpuid_init(cpuid_handle_t** handle);

int  hdc_cpuid_standard_function_number(cpuid_handle_t* handle);

int  hdc_cpuid_cpu_vendor(cpuid_handle_t* handle);

int  hdc_cpuid_cpu_family(cpuid_handle_t* handle);

int  hdc_cpuid_cpu_model(cpuid_handle_t* handle);

int  hdc_cpuid_cpu_stepping(cpuid_handle_t* handle);

int  hdc_cpuid_cpu_extended_family(cpuid_handle_t* handle);

int  hdc_cpuid_cpu_extended_model(cpuid_handle_t* handle);

int  hdc_cpuid_cpu_serial_number(cpuid_handle_t* handle, hdc_uuid_t* uuid);

bool hdc_cpuid_cpu_sse3_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pclmuldq_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_dtes64_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_monitor_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_ds_cpl_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_vmx_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_smx_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_eist_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_tm2_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_ssse3_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_cnxt_id_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_sdbg_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_fma_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_cx16_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_xtpr_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pdcm_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pcid_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_dca_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_sse4_1_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_sse4_2_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_x2apic_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_movbe_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_popcnt_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_tsc_deadline_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_aes_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_xsave_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_osxsave_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_avx_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_f16c_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_rdrand_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_fpu_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_vme_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_de_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pse_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_tsc_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_msr_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pae_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_mce_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_cx8_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_apic_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_sep_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_mtrr_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pge_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_mca_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_cmov_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pat_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pse_36_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_psn_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_clfsh_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_ds_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_acpi_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_mmx_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_fxsr_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_sse_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_sse2_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_ss_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_htt_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_tm_support(cpuid_handle_t* handle);

bool hdc_cpuid_cpu_pbe_support(cpuid_handle_t* handle);

const char* hdc_cpuid_cpu_identify(cpuid_handle_t* handle);

const char* hdc_cpuid_processor_type(cpuid_handle_t* handle);

void hdc_cpuid_destroy(cpuid_handle_t* handle);

#endif