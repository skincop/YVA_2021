ml /c /coff /Zi asm.asm
link /OPT:NOREF /DEBUG YVA_LIBRARY.lib asm.obj  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
call asm.exe