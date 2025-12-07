@echo off
if exist helloLinux.map del helloLinux.map
if exist helloLinux.elf del helloLinux.elf
if exist helloLinux.obj del helloLinux.obj

cl /nologo /c /GS- /D_NO_CRT_STDIO_INLINE /D_CRT_SECURE_NO_WARNINGS helloLinux.c
link /nologo /MAP:helloLinux.map /NODEFAULTLIB /ENTRY:_cdeCRT0Linux /OUT:helloLinux.elf /SUBSYSTEM:POSIX helloLinux.obj LIB\toroC64.lib