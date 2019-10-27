jmp __gary_end

; The arguments are pointers to the pointers to memory

__gary_assignment:
    jmp .mem
    .source: dw 0
    .dest: dw 0
    .instp: dw 0
    .mem:

    pop word [.instp]
    pop word [.dest]
    pop word [.source]

    mov ax, [.source]           ; the pointer to the value is now in ax
    mov bx, [.dest]

    ; we want to pass the pointers around so the actual memory is modified
    ; this assignment simply assigns pointers, not values

    mov [bx], ax

    push word [.instp]
    ret

__gary_addition:
    jmp .mem
    .a: dw 0
    .b: dw 0
    .instp: dw 0
    .mem:

    pop word [.instp]
    pop word [.b]
    pop word [.a]

    mov ax, [.a]
    add ax, [.b]

    push word [.instp]
    ret

__gary_subtraction:
    jmp .mem
    .a: dw 0
    .b: dw 0
    .instp: dw 0
    .mem:

    pop word [.instp]
    pop word [.b]
    pop word [.a]

    mov ax, [.a]
    sub ax, [.b]

    push word [.instp]
    ret

__gary_multiplication:
    ret

__gary_division:
    ret

__gary_exponent:
    ret

__gary_print:
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
    .instp: dw 0
    .mem:

    push word [.instp]
    ret

__gary_debug:
    push ax
    mov al, 48
    mov ah, 0Eh
    int 10h
    pop ax
    ret

__gary_end:
