	.globl _syscall,_main,_exit,auto_start
        .globl _getcs
auto_start:		
         call _main
! if ever return, exit(0)
	push  #0
        call  _exit

_syscall:
        int    80
        ret
_getcs:
	mov   ax,cs
	ret

!main was main0 in KC's u.s online, why?
