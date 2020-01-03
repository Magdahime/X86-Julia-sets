
;julia.asm
;juliafunc(double real_part, double imagine_part, double zoom, U32* pixels, int width, int height, int limit, int x_offset/zoom, int y_offset/zoom)
;	 		XMM0	            XMM1	            XMM2	      RDI	  		RSI       RDX  	    RCX		  	R8	                R9
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
;                sf::Uint8 red = iterations * PALETTE[0] % 256;
;				sf::Uint8 green = iterations * PALETTE[1] % 256;
;				sf::Uint8 blue = iterations * PALETTE[2] % 256;
;                //COLOURING
;                pixels[(y*width + x)*4] =      red;
;                pixels[(y*width + x)*4 + 1 ] = blue;
;                pixels[(y*width + x)*4 + 2 ] = green;
;                pixels[(y*width + x)*4 + 3 ] = 255;
;            }
;        }
juliafunc:
    ;registers that must be saved : RBX, RBP, R12-R15
	push rbp
	push r12
	push r13
	push r14
	mov rbp, rsp	

    ; R10 ----> x counter
    ; R11 ----> y counter	
    xor r10, r10
    xor r11, r11
define_variables:

julia_iteration:


x_loop:
    ;for (int x = 0; x<width; x++)
    add r10, 1
    cmp r10, rsi 
    jl define_variables


y_loop:
    ;for(int y =0; y<height; y++)
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