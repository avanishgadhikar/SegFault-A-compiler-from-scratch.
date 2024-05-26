.text
.align 2           ; Ensure proper alignment (2^2 = 4 bytes)
.global _start

_start:
  mov x8, #93      ; syscall number for exit
  mov x0, #12      ; exit status
  svc #0           ; make the system call
