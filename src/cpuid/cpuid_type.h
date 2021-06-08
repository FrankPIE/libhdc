/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_CPUID_DEF_H_
#define _HDC_CPUID_DEF_H_

typedef struct _hdc_cpu_register_t
{
	union
	{
		struct
		{
			unsigned int eax;
			unsigned int ebx;
			unsigned int ecx;
			unsigned int edx;
		};

		unsigned int registers[4];
	};
} hdc_cpu_register_t;

#define HDC_CPUID_INTEL_SSE3_FLAG		  0x1
#define HDC_CPUID_INTEL_PCLMULDQ_FLAG     0x2
#define HDC_CPUID_INTEL_DTES64_FLAG       0x4
#define HDC_CPUID_INTEL_MONITOR_FLAG      0x8
#define HDC_CPUID_INTEL_DS_CPL_FLAG       0x10
#define HDC_CPUID_INTEL_VMX_FLAG          0x20
#define HDC_CPUID_INTEL_SMX_FLAG          0x40
#define HDC_CPUID_INTEL_EIST_FLAG         0x80
#define HDC_CPUID_INTEL_TM2_FLAG          0x100
#define HDC_CPUID_INTEL_SSSE3_FLAG        0x200
#define HDC_CPUID_INTEL_CNXT_1D_FLAG      0x400
#define HDC_CPUID_INTEL_SDBG_FLAG         0x800
#define HDC_CPUID_INTEL_FMA_FLAG          0x1000
#define HDC_CPUID_INTEL_CX16_FLAG         0x2000
#define HDC_CPUID_INTEL_XTPR_FLAG         0x4000
#define HDC_CPUID_INTEL_PDCM_FLAG         0x8000
#define HDC_CPUID_INTEL_PCID_FLAG         0x20000
#define HDC_CPUID_INTEL_DCA_FLAG          0x40000
#define HDC_CPUID_INTEL_SSE4_1_FLAG       0x80000
#define HDC_CPUID_INTEL_SSE4_2_FLAG       0x100000
#define HDC_CPUID_INTEL_X2APIC_FLAG       0x200000
#define HDC_CPUID_INTEL_MOVBE_FLAG        0x400000
#define HDC_CPUID_INTEL_POPCNT_FLAG       0x800000
#define HDC_CPUID_INTEL_TSC_DEADLINE_FLAG 0x1000000
#define HDC_CPUID_INTEL_AES_FLAG          0x2000000
#define HDC_CPUID_INTEL_XSAVE_FLAG        0x4000000
#define HDC_CPUID_INTEL_OSXSAVE_FLAG      0x8000000
#define HDC_CPUID_INTEL_AVX_FLAG          0x10000000
#define HDC_CPUID_INTEL_F16C_FLAG         0x20000000
#define HDC_CPUID_INTEL_RDRAND_FLAG       0x40000000

#define HDC_CPUID_INTEL_FPU_FLAG	      0x1
#define HDC_CPUID_INTEL_VME_FLAG          0x2
#define HDC_CPUID_INTEL_DE_FLAG           0x4
#define HDC_CPUID_INTEL_PSE_FLAG          0x8
#define HDC_CPUID_INTEL_TSC_FLAG          0x10
#define HDC_CPUID_INTEL_MSR_FLAG          0x20
#define HDC_CPUID_INTEL_PAE_FLAG          0x40
#define HDC_CPUID_INTEL_MCE_FLAG          0x80
#define HDC_CPUID_INTEL_CX8_FLAG          0x100
#define HDC_CPUID_INTEL_APIC_FLAG         0x200
#define HDC_CPUID_INTEL_SEP_FLAG          0x800
#define HDC_CPUID_INTEL_MTRR_FLAG         0x1000
#define HDC_CPUID_INTEL_PGE_FLAG          0x2000
#define HDC_CPUID_INTEL_MCA_FLAG          0x4000
#define HDC_CPUID_INTEL_CMOV_FLAG         0x8000
#define HDC_CPUID_INTEL_PAT_FLAG          0x10000
#define HDC_CPUID_INTEL_PSE36_FLAG        0x20000
#define HDC_CPUID_INTEL_PSN_FLAG          0x40000
#define HDC_CPUID_INTEL_CLFSH_FLAG        0x80000
#define HDC_CPUID_INTEL_DS_FLAG           0x200000
#define HDC_CPUID_INTEL_ACPI_FLAG         0x400000
#define HDC_CPUID_INTEL_MMX_FLAG          0x800000
#define HDC_CPUID_INTEL_FXSR_FLAG         0x1000000
#define HDC_CPUID_INTEL_SSE_FLAG          0x2000000
#define HDC_CPUID_INTEL_SSE2_FLAG         0x4000000
#define HDC_CPUID_INTEL_SS_FLAG           0x8000000
#define HDC_CPUID_INTEL_HTT_FLAG          0x10000000
#define HDC_CPUID_INTEL_TM_FLAG           0x20000000
#define HDC_CPUID_INTEL_PBE_FLAG          0x80000000

#endif