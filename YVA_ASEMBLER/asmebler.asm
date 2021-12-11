.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/YVA_Lib.lib
ExitProcess PROTO : DWORD
_compare PROTO : DWORD, :DWORD
_strln PROTO : DWORD
_out PROTO : DWORD
_outInt PROTO : DWORD


.stack 4096
.const
	_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0
	_OVERFLOW_ERROR BYTE 'Ошибка выполнения: переполнение', 0
	L0 DWORD 123
	L1 DWORD 83
	L2 DWORD 45
	L3 DWORD 10
	L4 DWORD 10
	L5 DWORD 10
	L6 DWORD 0
.data
	_suma		DWORD 0 ; int
	_sumb		DWORD 0 ; int
	_sumc		DWORD 0 ; int
	_mainfunc		DWORD 0 ; int

.code
_sum PROC _y: DWORD, _x: DWORD
	push		L0
	pop			_suma

	push		L1
	pop			_sumb

	push		L2
	pop			_sumc

	push		_suma
	call		_outInt

	push		_sumb
	call		_outInt

	push		_sumc
	call		_outInt



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	mov		eax, L3
	ret		8
_sum ENDP

main PROC
	push		L4
	push		L5
	call		_sum
	push		eax
	pop			_mainfunc

	push		_mainfunc
	call		_outInt



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	push		L6
	call		ExitProcess

main ENDP
end main
