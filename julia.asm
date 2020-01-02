
;julia.asm
;juliafunc(double real_part, double imagine_part, double zoom, U32* pixels, int width, int height, int limit, int x_offset/zoom, int y_offset/zoom)
;	 		XMM0	            XMM1	            XMM2	      RDI	  		RSI       RDX  	    RCX		  	R8	                R9
	section .text
	global juliafunc

juliafunc:
    ;registers that must be saved : RBX, RBP, R12-R15
	push rbp
	push r12
	push r13
	push r14
	mov rbp, rsp	


end:
    ;restoring registers
	pop r14
	pop r13
	pop r12
	pop rbp
	ret