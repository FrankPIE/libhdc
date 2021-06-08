TITLE CPUID Operator

ifndef MASM64
.model flat, c
.686p
endif
 	
.data
ifndef MASM64
    extern kCPUIDFlag:DWORD
else
    extern kCPUIDFlag:QWORD
endif

.code
ifndef MASM64
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
else
    _cpuid_check proc
        pushfq                            ; push original EFLAGS 
        pop rax                           ; get original EFLAGS
        mov rcx, rax                      ; copy original EFLAGS
        xor rax, 200000h                  ; flip ID bit in EFLAGS
        push rax                          ; save new EFLAGS value on stack
        popfq                             ; replace current EFLAGS value
        pushfq                            ; get new EFLAGS
        pop rax                           ; get new EFLAGS
        xor rax, rcx                      ; ID bit check, can't toggle
        and rax, 200000h                  
        mov kCPUIDFlag, rax
        ret
    _cpuid_check endp

    _cpuid proc array:PTR QWORD
        push rsi

        mov rsi, array
        mov rax, qword ptr [rsi]
        cpuid

        mov qword ptr [rsi], rax
        mov qword ptr [rsi + 8], rbx
        mov qword ptr [rsi + 16], rcx
        mov qword ptr [rsi + 24], rdx

        pop rsi
 
        ret
    _cpuid endp

    _cpuidex proc array:PTR QWORD
        push rsi

        mov rsi, array
        mov rax, qword ptr [rsi]
        mov rcx, qword ptr [rsi + 16]
        cpuid

        mov qword ptr [rsi], rax
        mov qword ptr [rsi + 8], rbx
        mov qword ptr [rsi + 16], rcx
        mov qword ptr [rsi + 24], rdx

        pop rsi
 
        ret
    _cpuidex endp
endif
end