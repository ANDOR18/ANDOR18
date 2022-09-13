title: Grade Averaging Program
; Assembly Language Programming-Section 
; Group 2 Members: Nathaniel DeHart-deh5850@calu.edu, Kevin Andor-AND3256@calu.edu, and - Matt Oblock obl2109@calu.edu

include Irvine32.inc

.data
null equ 0
count sdword null
sum sdword null
indata sdword null
average sdword null
remainder sdword null
bufferSize equ 41
buffer byte bufferSize dup(null)
quitbuffer byte 1 dup(null)
newline byte " ", 13, 10, null
prompt byte "Enter a grade [0-100] (enter nothing to get the average): ", null
error byte "ERROR: Invalid grade entered", null
sumis byte "The sum is: ", null
countis byte "Count is: ", null
i_avgis byte "Average is: ", null
r_avgis byte "Average remainder is: ", null

.code
main proc
	MOV count, null
restart:
	MOV edx, offset prompt
	CALL writestring
	MOV edx, offset buffer
	MOV ecx, bufferSize
	CALL readstring
	; Compares the number of characters read into edx with null
	CMP eax, null
	JNZ firstcheck
	JMP endofloop

firstcheck:
	CALL ParseInteger32
	CMP eax, 0
	JAE secondcheck
	; A number less than zero was entered
	MOV edx, offset error
	CALL writestring
	; Begins a new line in the console
	MOV edx, offset newline
	CALL writestring
	JMP restart

secondcheck:
	CMP eax, 100
	JBE ok
	; A number greater than 100 was entered
	MOV edx, offset error
	CALL writestring
	; Begins a new line in the console
	MOV edx, offset newline
	CALL writestring
	JMP restart

ok:
	INC count
	ADD sum, eax
	JMP	restart

endofloop:
	MOV eax, sum
	MOV edx, null
	IDIV count
	MOV average, eax
	MOV remainder, edx
	; PRINTING
	MOV edx, offset countis
	CALL writestring
	MOV eax, count
	CALL writeint
	; Begins a new line in the console
	MOV edx, offset newline
	CALL writestring
	MOV edx, offset sumis
	CALL writestring
	MOV eax, sum
	CALL writeint
	; Begins a new line in the console
	MOV edx, offset newline
	CALL writestring
	MOV edx, offset i_avgis
	CALL writestring
	MOV eax, average
	CALL writeint
	; Begins a new line in the console
	MOV edx, offset newline
	CALL writestring
	MOV edx, offset r_avgis
	CALL writestring
	MOV eax, remainder
	CALL writeint

	MOV edx, offset quitbuffer
	MOV ecx, 1
	CALL readstring

	main endp
end main