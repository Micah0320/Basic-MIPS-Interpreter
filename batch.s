	.text
	.globl main
main: 
	li	$s0, 1
	add $a0, $s0, $s0
	add $a0, $a0, $a0
	li	$v0, 0
	syscall
	li	$v0, 10
	syscall

	.data
	Hello:	.word 72,101,108,108,111,32,87,111,114,108,100
