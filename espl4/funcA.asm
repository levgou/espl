section .text
    global funcA

; iterates over given pointer until 0x00 is found, return index of it - similar to - strlen(<some str>)
funcA:
    push ebp                   ; save caller's ebp
    mov	ebp, esp               ; let ebp hold the stack pointer address
    mov	eax,-1                 ; put -1 in eax

.L2:
    add eax, 1                 ; add 1 to eax
    mov ebx, eax               ; move eax to ebx
    add ebx, [ebp+8]           ; add 1 to user arg
    movzx	ebx, BYTE [ebx]      ; put last 8 bits of ebx to ebx and pad with zeroes (arg is char)
    test bl , bl               ; perform bitwise AND on the last 8 bits in ebx,
                               ; but dont store the result - results is in FLAGS

    jne .L2                    ; if not all the bits are '0' (otherwise the zero FLAG would be on) jump to .L2
    mov esp, ebp               ; move stack pointer to where it was before exe funcA
    pop ebp                    ; return ebp to caller's state
    ret                        ; return to caller