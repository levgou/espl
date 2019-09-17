extern printf

section .data
    some_str: db 'at least 3 letters', 0  ; init string
    some_str_size: equ  $ - some_str      ; calc string size

section .bss
    rev_str: resb some_str_size           ; reserve place for reversed string


section .text
    global _start



_start:
    mov ecx, some_str_size - 1            ; init loop counter
    mov eax, some_str + some_str_size - 2 ; init str offset behind \0
    mov ebx, rev_str                      ; init rev str offset

reverse_string:
    mov dl, [eax]                         ; take char from org str
    mov [ebx], dl                         ; put char to rev str

    sub eax, 1                            ; move pointer back
    add ebx, 1                            ; move pointer

    loop reverse_string

    mov [ebx], byte 10
    mov [ebx + 1], byte 0

    push dword rev_str
    call printf

    add     esp, 4                        ; pop stack

_exit:
    mov	ebx,0                             ; exit code, 0=normal
    mov	eax,1                             ; exit command to kernel
    int	0x80                              ; interrupt 80 hex, call kernel
