org 100h
%include "garystdlib.asm"
jmp _skip0
_sub1:
jmp _skip2
__sub1_ip: dw 0
_skip2:
pop word [__sub1_ip]
jmp _skip3
__sub1_numa: dw 0
__sub1_numa_ptr: dw __sub1_numa
__sub1_numb: dw 0
__sub1_numb_ptr: dw __sub1_numb
_skip3:
pop word [__sub1_numb]
pop word [__sub1_numa]
push word [__sub1_numa_ptr]
jmp _skip4
__sub1_literal5: dw 4 
_skip4:
push __sub1_literal5
call __gary_equals
push ax
pop ax
cmp ax, 1
jne __gary_conditional6
jmp _skip7
__sub1_literal8: dw "The parameter numa is 4!", 0
_skip7:
push __sub1_literal8
call __gary_print
push ax
__gary_conditional6:
jmp _skip9
__sub1_return: dw 0
__sub1_return_ptr: dw __sub1_return
_skip9:
push __sub1_return_ptr
push word [__sub1_numa_ptr]
push word [__sub1_numb_ptr]
call __gary_addition
push ax
jmp _skip10
__sub1_literal11: dw 3 
_skip10:
push __sub1_literal11
call __gary_addition
push ax
call __gary_assignment
push ax
mov ax, word [__sub1_return_ptr]
push word [__sub1_ip]
ret
_skip0:
push _sub1
jmp _skip12
__sub0_myfunction: dw 0
__sub0_myfunction_ptr: dw __sub0_myfunction
_skip12:
push __sub0_myfunction_ptr
call __gary_assignment
push ax
jmp _skip13
__sub0_myresult: dw 0
__sub0_myresult_ptr: dw __sub0_myresult
_skip13:
push __sub0_myresult_ptr
jmp _skip14
__sub0_literal15: dw 4 
_skip14:
push __sub0_literal15
jmp _skip16
__sub0_literal17: dw 5 
_skip16:
push __sub0_literal17
call __sub0_myfunction
push ax
call __gary_assignment
push ax
jmp _skip18
__sub0_literal19: dw "The result is ", 0
_skip18:
push __sub0_literal19
call __gary_print
push ax
push word [__sub0_myresult_ptr]
call __gary_printint
push ax
