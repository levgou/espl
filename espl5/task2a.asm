section .text

global _start
global read
global write
global open
global close
global strlen

_start:

    mov eax, [esp]          ; argc
    mov ebx, esp            ; argv @esp+4
    add ebx, 4h

    push ebx
    push eax

    call	main
    mov     ebx,eax
    mov	eax,1
    int 0x80

%define ARGC dword [ebp + 8]
%define ARGV dword [ebp + 12]
%define BUFFER_SIZE dword 100
%define O_RDONLY dword 0
main:
    enter 104, 0            ; reserve 100 bytes fro buffer starting at ebp-100

    mov ebx, ARGV
    add ebx, 4              ; now ebx points at argv[1] - which is the file arg

.open_the_file:
    mov ebx, [ebx]          ; pointer to str
    push O_RDONLY
    push ebx

    call open               ; now if all good we have the fd at eax

    pop ebx
    pop ebx                 ; clean the stack

    mov [ebp - 104], eax    ; save fd on stack

    cmp eax, 0
    jle .bad_ret            ; if eax <= 0 something bad happened

.read_from_file:
    push BUFFER_SIZE        ; prep arguments for read
    mov ebx, ebp
    sub ebx, 100
    push ebx
    push dword [ebp - 104]

    call read
    pop ebx
    pop ebx
    pop ebx                 ; clean the stack of argumetns

    cmp eax, -1             ; check for errors
    jle .bad_ret

    cmp eax, 0
    jg .print_buf_to_screen ; if read more than 0 bytes print to screen

.finished_reading:
    push dword [ebp - 104]  ; close the file
    call close
    pop ebx
    jmp .good_ret

%define STDOUT dword 1
.print_buf_to_screen:
    push eax                ; number of bytes read to buffer
    mov ebx, ebp
    sub ebx, 100
    push ebx                ; buffer pointer
    push STDOUT             ; fd for stdout

    call write

    pop ebx
    pop ebx
    pop ebx                 ; clean stack of arguments

    cmp eax, 0              ; check if something was written to stdout
    jle .bad_ret

    jmp .read_from_file

.bad_ret:
    mov eax, 1
    jmp .do_ret

.good_ret:
    mov eax, 0

.do_ret:
    leave
    ret

%define FDESCRIPTOR dword [ebp + 8]
%define BUFFER_P dword [ebp + 12]
%define BUF_SIZE dword [ebp + 16]
read:
    enter 0, 0
    push ebx
    push ecx
    push edx

    mov eax, 3              ; read sys call
    mov ebx, FDESCRIPTOR
    mov ecx, BUFFER_P
    mov edx, BUF_SIZE

    int 0x80                ; sys call

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

    mov eax, 4              ; write sys call
    mov ebx, FDESCRIPTOR
    mov ecx, BUFFER_P
    mov edx, BUF_SIZE

    int 0x80                ; sys call

    pop edx
    pop ecx
    pop ebx
    leave
    ret

%define FILE_PATH dword [ebp + 8]
%define FILE_MODE dword [ebp + 12]
open:
    enter 0, 0

    push ebx                ; save regs
    push ecx                ; save regs

    mov eax, 5h             ; setup system call
    mov ebx, FILE_PATH      ; setup system call
    mov ecx, FILE_MODE      ; setup system call

    int 0x80                ; sys call

    pop ecx                 ; restore regs
    pop ebx                 ; restore regs

    leave
    ret


%define FD dword [ebp + 8]
close:
    enter 0, 0

    push ebx                ; save regs

    mov eax, 6h             ; setup system call
    mov ebx, FD

    int 0x80                ; sys call

    pop ebx                 ; restore regs

    leave
    ret                     ; clear args from stack and return


strlen:
    enter 0, 0
    push ebx

    mov eax, -1

.comp_len:
    inc eax                 ; calc offset
    mov ebx, eax
    add ebx, [ebp+8]        ; take str from stack
    mov bl, BYTE [ebx]      ; get byte at adress of ebx
    test bl, bl             ; check if byte is \0

    jne .comp_len           ; if not \0 cont to next byte

    pop ebx
    leave
    ret
