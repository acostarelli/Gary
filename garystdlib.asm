jmp __gary_end


__gary_assignment:
;    pop dx
;
;    pop bx
;    pop ax
;
;    mov [bx], ax
;
;    push dx
    ret

__gary_addition:
;    pop dx
;
;    pop bx
;    mov ax, [bx]
;
;    pop bx
;    mov cx, [bx]
;
;    add ax, cx
;
;    push dx
    ret

__gary_subtraction:
;    pop dx
;
;    pop bx
;    mov ax, [bx] ;;;;; WHAT IF YOU WROTE THE FUNCTIONS ALL IN C??? LINK THE OBJECT FILES OR SOMETHING... THEN FLESH OUT MORE OF THE COMPILER PART (DON'T WORRY ABOUT STDLIB) -- LIKE ADD DECIMAL SUPPORT
;
;    ;;; WHAT IF YOU CREATED A TOOL THAT GENERATED CSTDLIB FUNCTION CALLS FOR THE STDLIB. SO LIKE YOU TYPE IN PRINTF, IT SEARCHES FOR WHAT PRINTF NEEDS, AND THEN IT CREATES __GARY_PRINTF FOR YOU THAT HANDLES THE PUSHES AND POPS
;
;    ;; gcc 16 bit?
;    ;; WHAT IF YOU JUST HAD IT COMPILE TO 32 BIT?
;
;    pop bx
;    mov cx, [bx]
;
;    sub ax, cx
;
;    push dx
    ret

__gary_multiplication:
    ret

__gary_division:
    ret

__gary_exponent:
    ret

__gary_print:
;    jmp .mem
;    .a: dw 0
;    .mem:
;
;    pop dx
;
;    pop si
;    mov ah, 0Eh
;    .run:
;        lodsb
;        cmp al, 0
;
;        je .done
;
;        int 10h
;        jmp .run
;
;    .done:
;
;    push dx
    ret

__gary_printint:
;    pop dx
;
;    pop bx
;    mov ax, [bx]
;
;    push 0
;
;    mov cl, 10
;    .load_stack:
;        div cl
;        call __gary_debug
;
;
;        cmp al, 0
;        je .spill_stack
;
;        add ah, 48
;        push ax
;        jmp .load_stack
;
;    .spill_stack:
;        pop ax
;
;        cmp al, 0
;        je .end
;
;        mov ah, 0eh
;        int 10h
;        jmp .spill_stack
;
;    .end:
;
;
;    push dx
    ret

__gary_equals:
;    jmp .mem
;    .a: dw 0
;    .b: dw 0
;    .mem:
;    pop dx
;
;    pop word [.a]
;    pop word [.b]
;
;    mov ax, [.a]
;    mov bx, [.b]
;
;    mov ah, 0Eh
;    mov al, 'h'
;    int 10h
;
;    mov ah, 0Eh
;    mov al, bl
;    ;add al, 48
;    int 10h
;
;    cmp ax, bx
;        jne .unequal
;
;        xor ax, ax
;        mov ax, 1
;        jmp .end
;
;    .unequal:
;        mov ax, 0
;
;    .end:
;
;    push dx
    ret

__gary_and:
;    pop dx
;
;    pop ax
;    pop bx
;
;    cmp ax, 1
;        je .next
;
;        jmp .unequal
;
;    .next:
;        cmp bx, 1
;        je .equal
;
;        jmp .unequal
;
;    .equal:
;        xor ax, ax
;        mov ax, 1
;        jmp .end
;
;    .unequal:
;        mov ax, 0
;
;    .end:
;
;    push dx
    ret


__gary_input:
    ret

__gary_debug:
;;    push ax
;    mov al, 48
;    mov ah, 0Eh
;    int 10h
;    pop ax
    ret

__gary_end: