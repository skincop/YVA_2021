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
	_DIVISION_BY_ZERO_ERROR BYTE '������ ����������: ������� �� ����', 0
	_OVERFLOW_ERROR BYTE '������ ����������: ������������', 0
	L0 BYTE 'c', 0
	L1 BYTE 'main', 0
	L2 BYTE '11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111251', 0
	L3 DWORD 10
	L4 DWORD 15
.data
	_sumabsum		DWORD 0 ; int
	_mainstr		DWORD 0 ; str
	_mainfunc		DWORD 0 ; int

.code
_sum PROC _sumb: DWORD, _sumc: DWORD, _suma: DWORD
	push		_sumc
	call		_out

	push		_suma
	push		_sumb

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_sumabsum



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
	mov		eax, _sumabsum
	ret		12
_sum ENDP

_char PROC _chara: DWORD


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
_char ENDP

main PROC
	push		offset L1
	call		_out

	push		offset L2
	pop			_mainstr

	push		L3
	push		_mainstr
	push		L4
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
	push		L3
	call		ExitProcess

main ENDP
end main
