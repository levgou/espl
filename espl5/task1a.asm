section .text

global _start
global read
global write
global open
global close
global strlen

extern main

_start:

    mov eax, [esp]     ; argc
    mov ebx, esp       ; argv @esp+4
    add ebx, 4h

    push ebx
    push eax

    call	main
    mov     ebx,eax
    mov	eax,1
    int 0x80

%define FDESCRIPTOR dword [ebp + 8]
%define BUFFER_P dword [ebp + 12]
%define BUF_SIZE dword [ebp + 16]
read:
    enter 0, 0
    push ebx
    push ecx
    push edx

    mov eax, 3         ; read sys call
    mov ebx, FDESCRIPTOR
    mov ecx, BUFFER_P
    mov edx, BUF_SIZE

    int 0x80           ; sys call

    pop edx
    pop ecx
    pop ebx
    leave
    ret


write:
    enter 0, 0
    push ebx
    push ecx
    push edx

    mov eax, 4         ; write sys call
    mov ebx, FDESCRIPTOR
    mov ecx, BUFFER_P
    mov edx, BUF_SIZE

    int 0x80           ; sys call

    pop edx
    pop ecx
    pop ebx
    leave
    ret

%define FILE_PATH dword [ebp + 8]
%define FILE_MODE dword [ebp + 12]
open:
    enter 0, 0

    push ebx           ; save regs
    push ecx           ; save regs

    mov eax, 5h        ; setup system call
    mov ebx, FILE_PATH ; setup system call
    mov ecx, FILE_MODE ; setup system call

    int 0x80           ; sys call

    pop ecx            ; restore regs
    pop ebx            ; restore regs

    leave
    ret


%define FD dword [ebp + 8]
close:
    enter 0, 0

    push ebx           ; save regs

    mov eax, 6h        ; setup system call
    mov ebx, FD

    int 0x80           ; sys call

    pop ebx            ; restore regs

    leave
    ret                ; clear args from stack and return


strlen:
    enter 0, 0
    push ebx

    mov eax, -1

.comp_len:
    inc eax            ; calc offset
    mov ebx, eax
    add ebx, [ebp+8]   ; take str from stack
    mov bl, BYTE [ebx] ; get byte at adress of ebx
    test bl, bl        ; check if byte is \0

    jne .comp_len      ; if not \0 cont to next byte

    pop ebx
    leave
    ret
