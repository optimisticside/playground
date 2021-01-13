section.text:
    global _start

_start:
    mov eax, 2  ; syscall number for fork
    int 0x80    ; issue a syscall and call kernel
    jmp _start  ; jump back to start and repeat