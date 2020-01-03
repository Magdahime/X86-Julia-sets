
;julia.asm
;juliafunc(double real_part, double imagine_part, double zoom, U32* pixels, int width, int height, int limit, int * palette, double x_offset/zoom, double y_offset/zoom)
;	 		XMM0	            XMM1	            XMM2	      RDI	  		RSI       RDX  	    RCX	             R8      	  	XMM3	               XMM4
; R10 ----> x counter
; R11 ----> y counter	
section .text
global juliafunc

;        for(int y =0; y<height; y++){
;            for (int x = 0; x<width; x++){
;                double new_Re =x/ (zoom * width) + x_offset/zoom;
;                double new_Im =y/ (zoom * height) + y_offset/zoom;
;                int iterations;
;                for (iterations = 0; iterations< ITERATIONS; iterations++){
;                    double old_Re = new_Re;
;                    double old_Im = new_Im;
;                    new_Re = old_Re*old_Re - old_Im*old_Im +real_part;
;                    new_Im = 2*old_Re*old_Im +imaginary_part;
;                    //CHECKING IF WE REACHED 2
;                    if((new_Re*new_Re +new_Im*new_Im>4)){
;                        break;
;                    }
;                }
;               sf::Uint8 red = iterations * PALETTE[0] % 256;
;				sf::Uint8 green = iterations * PALETTE[1] % 256;
;				sf::Uint8 blue = iterations * PALETTE[2] % 256;
;                //COLOURING
;                pixels[(y*width + x)*4] =      red;
;                pixels[(y*width + x)*4 + 1 ] = blue;
;                pixels[(y*width + x)*4 + 2 ] = green;
;                pixels[(y*width + x)*4 + 3 ] = 255;
;            }
;        }


;***************************************************************************************
;XMM0 ----> double real_part
;XMM1 ----> double imagine_part
;XMM2 ----> double zoom
;RDI ----> U32* pixels
;RSI ----> int width
;RDX ----> int height
;RCX ----> int limit
;R8  ----> int * palette
;XMM3 ----> double x_offset/zoom
;XMM4 ----> double y_offset/zoom
;***************************************************************************************
juliafunc:
    ;registers that must be saved : RBX, RBP, R12-R15
	push rbp
	push r12
	push r13
	push r14
	mov rbp, rsp

    ; xmm9 = 2.0 
	mov r13, 2
	cvtsi2sd xmm9, r13

	; xmm10 = 4.0
	mov r13, 4
	cvtsi2sd xmm10, r13

    ; R10 ----> x counter
    ; R11 ----> y counter	
    xor r10, r10
    xor r11, r11

define_variables:
;   double new_Re =x/(zoom * width) + x_offset/zoom;
;   double new_Im =y/(zoom * height) + y_offset/zoom;
    ;xmm5 =x
    cvtsi2sd xmm5, r10
    ;xmm6 = width
    cvtsi2sd xmm6, rsi 
    ;xmm6 = zoom* width
    mulsd xmm6, xmm2
    ;xmm5 = x/(zoom*width)
    divsd xmm5, xmm6
    ;xmm5 = x/(zoom*width) + x_offset/zoom
    addsd xmm5, xmm3 
    ;xmm5 ----> NEW_RE

    ;xmm6 = y
    cvtsi2sd xmm6, r11
    ;xmm7 = height
    cvtsi2sd xmm7, rdx
    ;xmm7 = height *zoom
    mulsd xmm7, xmm2
    ;xmm6 = y/(zoom*height)
    divsd xmm6, xmm7 
    ;xmm6 = y/(zoom*height) + y_offset/zoom
    addsd xmm6, xmm4 
    ;xmm6 ----->NEW_IM

    ;R12 ---> iterations counter
    mov r12, -1


julia_iteration:
;***************************************************************************************
   ;xmm5 ----> NEW_RE
   ;xmm6 ----->NEW_IM
;***************************************************************************************
	add r12, 1
	cmp r12, rcx
	je colour_pixel

;   new_Re = old_Re*old_Re - old_Im*old_Im +real_part;
;   new_Im = 2*old_Re*old_Im +imaginary_part;

;   xmm7 = old_im
    movsd xmm7, xmm6

    mulsd xmm6, xmm5
    mulsd xmm6, xmm9
    addsd xmm6, xmm1

;   xmm6 =  2*old_Re*old_Im +imaginary_part
;   new_im is in xmm6

    mulsd xmm5,xmm5
    mulsd xmm7, xmm7
    subsd xmm5, xmm7
    addsd xmm5, xmm0 

;   xmm5 = old_Re*old_Re - old_Im*old_Im +real_part
;   new_re is in xmm5

;   if((new_Re*new_Re +new_Im*new_Im>4))
;   break;
    movsd xmm8, xmm5
    mulsd xmm8, xmm8
;   new_re^2 is in xmm8
    movsd xmm11, xmm6
	mulsd xmm11, xmm11
;   new_im^2 is in xmm11
	addsd xmm8, xmm11

    comisd xmm8, xmm10
	jb julia_iteration

colour_pixel:
;   const int PALETTE[] ={40,90,30};
;   iterations in R12
;   RDI ----> U32* pixels
;   R8  ----> int * palette
;   pixels[(y*width + x)*4] =      iterations * PALETTE[0];
;   pixels[(y*width + x)*4 + 1 ] = iterations * PALETTE[1];
;   pixels[(y*width + x)*4 + 2 ] = iterations * PALETTE[2];
;   pixels[(y*width + x)*4 + 3 ] = 255;

;   make a copy of the pointer 
    mov r13, r8
;           RED
    mov r14, [r13]
    imul r14, r12
    mov [rdi], r14b
;           GREEN
	add r13, 4
	add rdi, 1
    mov r14, [r13]
    imul r14, r12
    mov [rdi], r14b
;           BLUE
	add r13, 4
	add rdi, 1
    mov r14, [r13]
    imul r14, r12
	mov [rdi], r14b
;           ALPHA
	add rdi, 1
    mov byte[rdi], 255

	add rdi, 1

x_loop:
    ;for (int x = 0; x<width; x++)
    add r10, 1
    cmp r10, rsi 
    jl define_variables


y_loop:
    ;for(int y =0; y<height; y++)
    mov r10, 0
    add r11, 1
    cmp r11, rdx
    jl define_variables

end:
    ;restoring registers
	pop r14
	pop r13
	pop r12
	pop rbp
	ret