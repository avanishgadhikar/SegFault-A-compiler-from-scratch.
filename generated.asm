section .text
  global _start

_start:
  push 1
  pop rsi
  push 5
  push 4
  push 4
  push QWORD [rsp + 0]
  pop rax
  push rax
  pop rax
  push QWORD [rsp + 8]
  pop rbx
  mul rbx
  push rax
  pop rax
  push QWORD [rsp + 8]
  pop rbx
  div rbx
  push rax
  pop rax
  push QWORD [rsp + 16]
  pop rbx
  add rax, rbx
  push rax
  mov rax, 60
  pop rdi
  syscall
  pop rsi
  pop rsi
  pop rsi
  pop rsi
