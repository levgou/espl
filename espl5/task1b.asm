section .text
    global utoa_s

utoa_s:
    enter 8, 0

    push ebx               ; save regs
    push edx
    push ecx

    mov [ebp -4], dword 10 ; this is the divisor

    mov eax, [ebp + 8]     ; get argument number
    mov ebx, [ebp + 12]    ; get argument buffer
    mov [ebp - 8], ebx     ; save buf adress

    call clear_ebx_buf
    mov ebx, [ebp -8]      ; restore buffer pointer to start

.div_into_buf:
    mov edx, 0             ; construct the devised number
    div dword [ebp -4]     ; after this -> Quotient @ eax, remainder @ edx
    mov cl, dl             ; get remainder

    or edx, eax            ; check if finished dividing

    jne .save_byte
    jmp .finish_convert

.save_byte:
    add cl, '0'            ; convert to char
    mov [ebx], cl          ; write remainder to buf
    inc ebx                ; move buf pointer
    jmp .div_into_buf

.finish_convert:
    mov [ebx], byte 0      ; close the str with an \0

reverse_buf:
    dec ebx                ; now ebx points one behind \0
    mov ecx, [ebp - 8]     ; point ecx to start of buf

.do_reverse:
    cmp ecx, ebx           ; check if ecx is pointing after ebx, or @ ebx
    jge .finish_reverse

.exchange_chars:
    mov al, [ebx]          ; exchange the bytes
    xchg al, [ecx]
    mov [ebx], al

    dec ebx                ; move pointers
    inc ecx
    jmp .do_reverse

.finish_reverse:
    pop ecx                ; restore regs
    pop edx
    pop ebx

    leave
    ret                    

clear_ebx_buf:
    mov dl, [ebx]
    test dl, dl            ; check if \0
    jne .rem_byte
    jmp .ret_func

.rem_byte:
    mov [ebx], byte 0      ; remove one byte
    inc ebx                ; move pointer
    jmp clear_ebx_buf

.ret_func:
    ret
