.686P
.xmm

.MODEL FLAT, STDCALL

OPTION CASEMAP:NONE

INCLUDE C:\masm32\include\windows.inc

.DATA
i DWORD ?
j DWORD ?
k DWORD ?

a_value real8 ?
b_value real8 ?

.CODE

DllEntry PROC hInstDLL:HINSTANCE, reason:DWORD, reserved1:DWORD

mov eax, TRUE
ret

DllEntry ENDP

Multiply proc matrixA : real8, matrixB : real8, matrixC : real8, n: DWORD, m: DWORD, p: DWORD
	
	mov eax, 0
	mov i, eax
	mov j, eax
	mov k, eax
Loop_j:
	mov eax, p				;przes�anie zawarto�ci argumentu do akumulatora
	cmp j, eax					;por�wnanie licznika zewn�trznego z wysoko�ci�
	jge End_j
Loop_k:
	mov eax, p				;przes�anie zawarto�ci argumentu do akumulatora
	cmp k, eax					;por�wnanie licznika zewn�trznego z wysoko�ci�
	jge End_k
Loop_i:
	mov eax, p				;przes�anie zawarto�ci argumentu do akumulatora
	cmp i, eax					;por�wnanie licznika zewn�trznego z wysoko�ci�
	jge End_i
	
	mov ebx, matrixA
	mov eax, i
	mul m
	add eax, k
	mul 8			
	fld [ebx+eax]			;�adowanie do rejestru jednostki zmiennoprzecinkowej
	
	mov ebx, matrixB
	mov eax, k
	mul p
	add eax, j
	mul 8	
	fld [ebx+eax]		
	
	fmul ST(0), ST(i)
	
	mov ebx, matrixC
	mov eax, i
	mul p
	add eax, j
	mul 8	
	fld [ebx+eax]
	
	fadd ST(0), ST(i)+
	fstp [ebx+eax]
	
	inc i
	jmp Loop_i					;skok na pocz�tek wewn�trznej p�tli
End_i:
	mov i, 0					;zerowanie licznika wewn�trznego
	inc k						;inkrementacja licznika
	jmp Loop_k					;skok na pocz�tek zewn�trznej p�tli
End_k:
	mov k, 0					;zerowanie licznika wewn�trznego
	inc j						;inkrementacja licznika
	jmp Loop_j					;skok na pocz�tek zewn�trznej p�tli
End_j:
	ret							;powr�t z podprogramu

	

	