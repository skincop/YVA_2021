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
	L0 BYTE '10', 0
	L1 DWORD 20
	L2 DWORD 25
	L3 BYTE '123', 0
	L4 DWORD 5
	L5 DWORD 10
	L6 DWORD 15
	L7 DWORD 0
.data
	_sumabsum		DWORD 0 ; int
	_mainavg		DWORD 0 ; int
	_mainx		DWORD 0 ; int

.code
_sum PROC _sumb: DWORD, _suma: DWORD
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
	ret		8
_sum ENDP

main PROC
	push		offset L0
	call		_out

	push		L1
	push		L2
	call		_sum
	push		eax
	pop			_mainavg

	push		_mainavg
	call		_outInt

	push		offset L3
	call		_out

	push		L4
	push		L5

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	push		L6

	pop		eax
	pop		ebx
	and		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainx

	push		_mainx
	call		_outInt

	push		L4
	push		L5
	push		L6

	pop		eax
	pop		ebx
	and		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax


	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainx

	push		_mainx
	call		_outInt

	push		L6
	push		L6

	pop		eax
	pop		ebx
	and		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainx

	push		_mainx
	call		_outInt

	push		L6
	push		L6

	pop		eax
	pop		ebx
	and		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainx

	push		_mainx
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
	push		L7
	call		ExitProcess

main ENDP
end main
