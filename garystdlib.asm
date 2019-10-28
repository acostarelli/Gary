jmp __gary_end


__gary_assignment:
    pop dx

    pop bx
    pop ax

    mov [bx], ax

    push dx
    ret

__gary_addition:
    jmp .mem
    .a: dw 0
    .b: dw 0
    .mem:

    pop dx
    pop word [.b]
    pop word [.a]

    mov ax, [.a]
    add ax, [.b]

    push dx
    ret

__gary_subtraction:
    jmp .mem
    .a: dw 0
    .b: dw 0
    .mem:

    pop dx
    pop word [.b]
    pop word [.a]

    mov ax, [.a]
    sub ax, [.b]

    push dx
    ret

__gary_multiplication:
    ret

__gary_division:
    ret

__gary_exponent:
    ret

__gary_print:
    jmp .mem
    .a: dw 0
    .mem:

    pop dx

    pop si
    mov ah, 0Eh
    .run:
        lodsb
        cmp al, 0

        je .done

        int 10h
        jmp .run

    .done:

    push dx
    ret

__gary_tostr:
    jmp .mem
    .a: dw 0
    .mem:

    pop dx

    pop ax
    add ax, 48

    push dx
    ret

__gary_input:
    ret

__gary_debug:
    push ax
    mov al, 48
    mov ah, 0Eh
    int 10h
    pop ax
    ret

__gary_end:
