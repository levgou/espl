section .text
    global open_file
    global close_file

%define FILE_PATH dword [ebp + 8]
%define FILE_MODE dword [ebp + 12]
open_file:
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
    ret                ; clear args from stack and return


%define FD dword [ebp + 8]
close_file:
    enter 0, 0

    push ebx           ; save regs

    mov eax, 6h        ; setup system call
    mov ebx, FD

    int 0x80           ; sys call

    pop ebx            ; restore regs

    leave
    ret                ; clear args from stack and return
