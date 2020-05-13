.data

.code 

; This function seems like it does nothing when first viewed :
; but looking at the bytes of these two instructuions which are :
; 3B FF E0 00 
; we notice the middle two bytes is the machine code for a
; jmp rax instruction.

unique_function proc
	cmp edi, edi ; So if we jump to the start of this address + 1 byte
	loopne test_label ; we end up executing the instruction jmp rax
test_label:
	ret
unique_function endp

; This function does absolutely nothing besides allocate some space on the
; stack then moves 0x1000 into rbx (which shortly gets overwritten).
; but something unique about this function is that before it returns
; it pops the value at the top of the stack into rbx.
; We can use this to manipulate the value of rbx.
; We want to jump to this location (unique_function_two + 0x10 bytes)
; which is the instruction pop rbx.
; We can simulate a mov rbx, some_value by pushing a value onto the stack
; then jumping to this location.

unique_function_two proc
	push rbx
	sub rsp, 28h

	mov rbx, 1000h

	add rsp, 28h
	pop rbx ; We pop the value we pushed off the top of the stack into rbx
	ret ; return back to normal execution flow.
unique_function_two endp


unique_jump proc
	mov rax, rcx ; move our jump location into rax
	push rdx ; push our new return address onto the stack
	ret ; return to rdx
unique_jump endp


unique_mov proc
	push rdx ; push our value onto the stack that rbx will hold after the call
	push rcx ; push our return value onto the stack
	ret
unique_mov endp


end