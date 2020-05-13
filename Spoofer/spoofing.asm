.data 

.code

simple_jump PROC

	jmp rcx ; Illustrates a simple jump to an address in memory, this works because 
			; our return address is pushed onto the stack from our call to simple_jump

simple_jump ENDP

;------------------------------------------------------

SPEC_SEG segment read write execute ; Declare are segment as writable aswell so we can modify it dynamically.

; RCX will hold the value of our gadget, while RDX holds our funtion.

spoof_return PROC
	
	mov dword ptr [jmp_label], 0e2ff51h ; The opcodes for our instruction
jmp_label:
	nop ; Allocate 3 bytes to overwrite with :
	nop ; Push rcx
	nop ; Jmp rdx

spoof_return ENDP

SPEC_SEG ends

;------------------------------------------------------

; 4 PARAMS MAX 
; This can be changed by addressing the last two parameters moved onto the stack.
; Example 5 arguments would move our stack up 8 bytes
; So our jump address is now at [rsp + 30h]

spoof_return_params PROC 
	pop rax ; pop our return address off the stack into rax
	mov r10, [rsp + 28h] ; jump address
	mov r11, [rsp + 20h] ; address of gadget
	push rax ; push our actual return address back onto the stack
	push r11 ; push our gadget onto the stack
	jmp r10 ; jump to the function we want to call

spoof_return_params ENDP


;------------------------------------------------------

get_image_base PROC

	mov rcx, gs:[60h] ; Obtain the PEB
	mov rax, [rcx + 10h] ; The image base address is at offset 0x10
	ret

get_image_base ENDP


END