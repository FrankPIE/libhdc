/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <stdint.h>
#include <stdbool.h>

/* ***********************interface*********************** */

extern unsigned int kCPUIDFlag = 0u;

extern void _cpuid_check();

extern void _cpuid(uint32_t[4]);

extern void _cpuidex(uint32_t[4]);

/* ***********************implement*********************** */

extern bool cpuid_flag_check()
{
	_cpuid_check();
	
	return (kCPUIDFlag == 0x200000);
}

extern void cpuid(uint32_t registers[4], uint32_t function_id)
{
	registers[0] = function_id;
	
	_cpuid(registers);
}

extern void cpuidex(uint32_t registers[4], uint32_t function_id, uint32_t sub_function_id)
{
	registers[0] = function_id;
	registers[2] = sub_function_id;
	
	_cpuidex(registers);
}
