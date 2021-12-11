.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/YVA_LIBRARY.lib
ExitProcess PROTO : DWORD
_compare PROTO : DWORD, :DWORD
_converter PROTO : DWORD
_strln PROTO : DWORD
_out PROTO : DWORD
_outInt PROTO : DWORD


.stack 4096
.const
	_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0
	_OVERFLOW_ERROR BYTE 'Ошибка выполнения: переполнение', 0
	L0 BYTE 'e', 0
	L1 BYTE '111', 0
	L2 DWORD 10
	L3 DWORD 0
.data
	_fiz		DWORD 0 ; pin
	_fipp		DWORD 0 ; str
	_mainret		DWORD 0 ; pin
	_mainstr		DWORD 0 ; str

.code
_fi PROC _x: DWORD
	push		offset L0
	pop			_fiz

	push		offset L1
	pop			_fipp



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
	mov		eax, offset L0
	ret		4
_fi ENDP

main PROC
	push		L2
	call		_fi
	push		eax
	pop			_mainret



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
	push		L3
	call		ExitProcess

main ENDP
end main
