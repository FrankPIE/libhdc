TITLE CPUID Operator

.model flat, c
 	
.data
    extern kCPUIDFlag:DWORD

.code
.686p
    _cpuid_check proc
        pushfd                            ; push original EFLAGS 
        pop eax                           ; get original EFLAGS
        mov ecx, eax                      ; copy original EFLAGS
        xor eax, 200000h                  ; flip ID bit in EFLAGS
        push eax                          ; save new EFLAGS value on stack
        popfd                             ; replace current EFLAGS value
        pushfd                            ; get new EFLAGS
        pop eax                           ; get new EFLAGS
        xor eax, ecx                      ; ID bit check, can't toggle
        and eax, 200000h                  
        mov kCPUIDFlag, eax
        ret
    _cpuid_check endp

    _cpuid proc array:PTR DWORD
        push esi

        mov esi, array
        mov eax, dword ptr [esi]
        cpuid

        mov dword ptr [esi], eax
        mov dword ptr [esi + 4], ebx
        mov dword ptr [esi + 8], ecx
        mov dword ptr [esi + 12], edx

        pop esi
 
        ret
    _cpuid endp

    _cpuidex proc array:PTR DWORD
        push esi

        mov esi, array
        mov eax, dword ptr [esi]
        mov ecx, dword ptr [esi + 8]
        cpuid

        mov dword ptr [esi], eax
        mov dword ptr [esi + 4], ebx
        mov dword ptr [esi + 8], ecx
        mov dword ptr [esi + 12], edx

        pop esi
 
        ret
    _cpuidex endp

end