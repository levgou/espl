%include "cmpstr.asm"
%include "task1b.asm"

section .data
    num_lines_str: db 'Number of lines: ', 0
    num_lines_str_len: equ  $ - num_lines_str        ; calc string size
    l_opt: db '-l', 0
    endl: db 10, 0

    open_file_err: db 'Failed to open the file', 10, 0
    open_file_err_len: equ  $ - open_file_err

    close_file_err: db 'Failed to close the file', 10, 0
    close_file_err_len: equ  $ - close_file_err

    read_from_file_err: db 'Failed to read from file', 10, 0
    read_from_file_err_len: equ  $ - read_from_file_err

    write_to_File_err: db 'Failed to write to file', 10, 0
    write_to_File_err_len: equ  $ -  write_to_File_err


section .bss
    int_str_repr: resb 11                            ; save place for convertion of int to str

section .text
    global _start

_start:

    mov eax, [esp]                                   ; argc
    mov ebx, esp                                     ; argv @esp+4
    add ebx, 4h

    push ebx
    push eax

    call	main

.exit:
    mov     ebx,eax
    mov	eax,1
    int 0x80

%define ARGC dword [ebp + 8]
%define ARGV dword [ebp + 12]
%define BUFFER_SIZE dword 100
%define O_RDONLY dword 0
%define LINE_NUM dword [ebp - 108]
%define IS_COUNT_LINES byte [ebp - 109]
%define PATH_TO_F dword [ebp - 113]
main:
    enter 113, 0                                     ; reserve 100 bytes fro buffer starting at ebp-100
                                                     ; 4 to save fd, 4 to save num of lines
                                                     ; 1 for is '-l' option flag, and 4 for path to file pointer

    mov LINE_NUM, 0                                  ; put 0 in stack in case we need to count lines
    mov IS_COUNT_LINES, 0                            ; flag for -l option

parse_cmd_args:
    mov ecx, ARGC
    sub ecx, 1                                       ; now ecx number of cmd args

    mov ebx, ARGV

.move_ebx:
    add ebx, 4                                       ; now ebx points at argv[1] or argv[1] - which is the file arg

    push l_opt
    push dword [ebx]

    call cmpstr

    pop edx
    pop edx                                          ; clean stack from args

    cmp eax, 0
    je .found_l
    jmp .fount_not_l

.found_l:
    mov IS_COUNT_LINES, 1
    jmp .cont

.fount_not_l:
    mov edx, [ebx]
    mov PATH_TO_F, edx

.cont:
    loop .move_ebx


open_the_file:
    mov ebx, PATH_TO_F                               ; pointer to str
    push O_RDONLY
    push ebx

    call open                                        ; now if all good we have the fd at eax

    pop ebx
    pop ebx                                          ; clean the stack

    mov [ebp - 104], eax                             ; save fd on stack

read_from_file:
    push BUFFER_SIZE                                 ; prep arguments for read
    mov ebx, ebp
    sub ebx, 100
    push ebx
    push dword [ebp - 104]

    call read
    pop ebx
    pop ebx
    pop ebx                                          ; clean the stack of argumetns

    cmp eax, 0
    jg .handle_buf
    jmp .finished_reading

.handle_buf:
    mov bl, IS_COUNT_LINES                           ; check if in -l mode
    cmp bl, 1

    jne .print_buf_to_screen                         ; if read more than 0 bytes print to screen
    jmp .count_lines_in_buf                          ; if read more than 0 count lines

.finished_reading:
    push dword [ebp - 104]                           ; close the file
    call close
    pop ebx

    mov bl, IS_COUNT_LINES                           ; check if in -l mode
    cmp bl, 1

    je .print_line_num

    jmp good_ret

%define STDOUT dword 1
.print_line_num:
    mov ebx, LINE_NUM
    mov eax, int_str_repr

    push eax
    push ebx

    call utoa_s

    pop ebx
    pop ebx                                          ; clear stack of arguments

                                                     ; -------------- print 'Number of lines: '
    push dword  num_lines_str_len                    ; number of bytes read to buffer
    push dword  num_lines_str                        ; buffer pointer
    push STDOUT                                      ; fd to stdout
    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments
                                                     ; -------------- print the number
    push dword 11                                    ; number of bytes read to buffer
    push dword int_str_repr                          ; buffer pointer
    push STDOUT                                      ; fd to stdout
    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments
                                                     ; -------------- print \n
    push dword 2                                     ; number of bytes read to buffer
    push dword endl                                  ; buffer pointer
    push STDOUT                                      ; fd to stdout
    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments

    jmp good_ret

.print_buf_to_screen:
    push eax                                         ; number of bytes read to buffer
    mov ebx, ebp
    sub ebx, 100
    push ebx                                         ; buffer pointer
    push STDOUT                                      ; fd for stdout

    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments

    jmp read_from_file

.count_lines_in_buf:
    push eax                                         ; amount read from buffer
    mov ebx, ebp
    sub ebx, 100
    push ebx                                         ; buffer address
    mov ebx, ebp
    sub ebx, 108
    push ebx                                         ; counter adress

    call count_endl
    pop ebx
    pop ebx
    pop ebx                                          ; clean stack from args

    jmp read_from_file

bad_ret:
    mov eax, 1
    jmp _start.exit

good_ret:
    mov eax, 0

do_ret:
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

    mov eax, 3                                       ; read sys call
    mov ebx, FDESCRIPTOR
    mov ecx, BUFFER_P
    mov edx, BUF_SIZE

    int 0x80                                         ; sys call

    cmp eax, -1
    jle .read_failed

    pop edx
    pop ecx
    pop ebx
    leave
    ret

.read_failed:

    push dword  read_from_file_err_len               ; buffer pointer
    push dword  read_from_file_err                   ; number of bytes read to buffer
    push STDOUT                                      ; fd to stdout
    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments
    jmp bad_ret

write:
    enter 0, 0
    push ebx
    push ecx
    push edx

    mov eax, 4                                       ; write sys call
    mov ebx, FDESCRIPTOR
    mov ecx, BUFFER_P
    mov edx, BUF_SIZE

    int 0x80                                         ; sys call

    cmp eax, -1
    jle .write_failed

    pop edx
    pop ecx
    pop ebx
    leave
    ret

.write_failed:

    push dword  write_to_File_err_len                ; buffer pointer
    push dword  write_to_File_err                    ; number of bytes read to buffer
    push STDOUT                                      ; fd to stdout
    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments

    jmp bad_ret


%define FILE_PATH dword [ebp + 8]
%define FILE_MODE dword [ebp + 12]
open:
    enter 0, 0

    push ebx                                         ; save regs
    push ecx                                         ; save regs

    mov eax, 5h                                      ; setup system call
    mov ebx, FILE_PATH                               ; setup system call
    mov ecx, FILE_MODE                               ; setup system call

    int 0x80                                         ; sys call

    cmp eax, -1
    jle .open_failed

    pop ecx                                          ; restore regs
    pop ebx                                          ; restore regs

    leave
    ret

.open_failed:

    mov ebx, open_file_err

    push dword  open_file_err_len                    ; buffer pointer
    push dword  open_file_err                        ; number of bytes read to buffer
    push STDOUT                                      ; fd to stdout
    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments

    jmp bad_ret


%define FD dword [ebp + 8]
close:
    enter 0, 0

    push ebx                                         ; save regs

    mov eax, 6h                                      ; setup system call
    mov ebx, FD

    int 0x80                                         ; sys call

    cmp eax, -1
    jle .close_failed

    pop ebx                                          ; restore regs

    leave
    ret                                              ; clear args from stack and return

.close_failed:

    push dword  close_file_err_len                   ; buffer pointer
    push dword  close_file_err                       ; number of bytes read to buffer
    push STDOUT                                      ; fd to stdout
    call write

    pop ebx
    pop ebx
    pop ebx                                          ; clean stack of arguments

    jmp bad_ret


strlen:
    enter 0, 0
    push ebx

    mov eax, -1

.comp_len:
    mov ebx, 0

%define COUNTER dword [ebp + 8]
%define BUFFER_P dword [ebp + 12]
%define BUF_SIZE dword [ebp + 16]
count_endl:
    enter 0,0
    push ecx
    push ebx
    push eax

    mov ecx, BUF_SIZE
    mov ebx, BUFFER_P

.do_count:
    call .maybe_raise_count
    inc ebx                                          ; move pointer
    loop .do_count
    jmp .finish_count

.maybe_raise_count:
    cmp [ebx], byte 10
    je .raise_count
    ret

.raise_count:
    mov eax, COUNTER                                 ; get counter adress
    inc dword [eax]
    ret

.finish_count:
    pop eax
    pop ebx
    pop ecx
    leave
    ret