Title: Program 2 Assembly Calculator
; Group 2 Members: Nathaniel DeHart, Kevin Andor, Matt Oblock

include Irvine32.inc

.data
STACKSIZE equ 8
MyStack sdword STACKSIZE dup(' ')
Prompt1 byte "Assembly Calculator", 13, 10, 0
OvFlowMsg byte "STACK OVERFLOW!", 13, 10, 0
InvalidMsg byte "INVALID ENTRY", 13, 10, 0
ValueTooLarge byte "THE ENTERED NUMBER WAS TOO LARGE", 13, 10, 0
InvalidSize byte "THE STACK IS TOO SMALL FOR THE SELECTED OPERATION!", 13, 10, 0
Newline byte " ", 13, 10, 0
BUFFERSIZE equ 16
InpIndex dword 0
StackIndex sdword -1
Input byte BUFFERSIZE dup(' ')
Negative byte 0
TempResult dword 0
TempIndex dword 0
Power dword 0

.code
Main proc
jmp PrintTop
; Gets the user input and hides entered spaces
Menu:
	call ClearInput
	mov Negative, 0
	mov InpIndex, 0
	mov esi, 0
	mov ecx, BufferSize
	mov edx, offset Input
	call ReadString
	mov edx, 0
	mov edi, InpIndex
	movzx ebx, [Input + edi]
	cmp ebx, ' '
	je SkipSpace
	cmp ebx, 09h
	je SkipSpace
	jmp NoSpaces
; 
ClearInput:
	mov ecx, 0
	ClearLoop:
		mov [input + ecx], ' '
		inc ecx
		cmp ecx, BUFFERSIZE
		jl ClearLoop
		ret
; Increments the input index until a value other than a space was entered
SkipSpace:
	inc InpIndex
	mov edi, InpIndex
	movzx ebx, [Input + edi]
	cmp ebx, ' '
	je SkipSpace
	cmp ebx, 09h
	je SkipSpace
	jmp NoSpaces
; Determines what the kind of the data that was entered
NoSpaces:
	mov edi, InpIndex
	movzx ebx, [Input + edi]
	cmp ebx, '-'
	je SignOrSubtract
	cmp ebx, '0'
	jl IsSymbol
	mov [Input + edi], bl
	cmp ebx, '9'
	jg IsSymbol
	jmp Digit
; Determines whether an entered minus sign for negation or subtraction
SignOrSubtract:
	; Looks at the character after '-'
	movzx ecx, [Input + edi + 1]
	cmp ecx, '0'
	jl IsSymbol
	cmp ecx, '9'
	jg IsSymbol
	mov Negative, 1
	jmp Digit

; Negates the value stored in edx
IsNegative:
	mov esi, StackIndex
	imul esi, 4
	mov eax, [MyStack + esi]
	neg eax
	mov [MyStack + esi], eax
	jmp PrintTop
; Jumps to the function corresponding to the character that was entered
IsSymbol:
	cmp ebx, 'n'   
	je IsNegative
	cmp ebx, 'N'
	je IsNegative
	cmp ebx, 'v'
	je ViewAll
	cmp ebx, 'V'
	je ViewAll
	cmp ebx, 'c'
	je ClearStack
	cmp ebx, 'C'
	je ClearStack
	cmp ebx, 'q'
	je Quit
	cmp ebx, 'Q'
	je Quit
	cmp ebx, 'u'
	je RollUp
	cmp ebx, 'U'
	je RollUp
	cmp ebx, 'd'
	je RollDown
	cmp ebx, 'D'
	je RollDown
	cmp ebx, '-'
	je SubtractNum
	cmp ebx, '+'
	je AddNum
	cmp ebx, '/'
	je DivideNum
	cmp ebx, '*'
	je MultiplyNum
	cmp ebx, 'x'
	je XChng
	cmp ebx, 'X'
	je XChng
	jmp InputError

; Subtracts the top element of the stack from the second highest element of the stack
SubtractNum:
	cmp StackIndex, 1
	jl StackTooSmall
	call PopStack
	mov eax, [MyStack + esi]
	sub eax, edx
	mov [MyStack + esi], eax
	jmp PrintTop

; Adds the top element of the stack from the second highest element of the stack
AddNum:
	cmp StackIndex, 1
	jl StackTooSmall
	call PopStack
	mov eax, [MyStack + esi]
	add eax, edx
	mov [MyStack + esi], eax
	jmp PrintTop

; Divides the top element of the stack from the second highest element of the stack
DivideNum:
	cmp StackIndex, 1
	jl StackTooSmall
	call PopStack
	mov ebx, edx
	mov eax, [MyStack + esi]
	cdq
	idiv ebx
	mov [MyStack + esi], eax
	jmp PrintTop

; Multiplies the top two elements of the stack 
MultiplyNum:
	cmp StackIndex, 1
	jl StackTooSmall
	call PopStack
	mov ebx, [Mystack + esi]
	imul edx, ebx
	mov [Mystack + esi], edx
	jmp PrintTop
; Clears all of the values in the stack
ClearStack:
	cmp StackIndex, -1
	je PrintTop
	call PopStack
	jmp ClearStack
; Swaps the data stored in the top two elements of the stack
XChng:
	cmp StackIndex, 1
	jl StackTooSmall
	mov esi, StackIndex
	imul esi, 4
	mov eax, [MyStack + esi]
	mov ebx, [MyStack + esi - 4]
	mov [MyStack + esi], ebx
	mov [MyStack + esi - 4], eax
	jmp PrintTop
; Prints that the stack is too small for the selected operation
StackTooSmall:
	mov edx, offset InvalidSize
	call WriteString
	jmp PrintTop

; Requires a pointer to some string to be stored in eax, the starting index in edi, and the max size stored in ecx
; Stores the integer in edx
ConvertToInt:
	mov TempResult, 0
	mov TempIndex, ecx
	mov esi, 0
	mov ebx, 0
	mov edx, 0
	add eax, TempIndex
	cmp TempIndex, edi
	jge IntLoop
	; No numbers entered
	jmp InputError
	IntLoop:
		dec TempIndex
		dec eax
		cmp TempIndex, edi
		jge IntContinue
		mov edx, TempResult
		ret
	IntContinue:
		mov ebx, 0
		mov bl, [eax]
		movzx ebx, bl
		sub ebx, 30h
		cmp ebx, 0
		jl IntLoop
		cmp ebx, 9
		jg IntLoop
		inc esi
		cmp esi, 10
		jg NumTooBig
		call PowerTen
		add TempResult, ebx
		jmp IntLoop
; Prints that the number that was entered is too large
NumTooBig:
	mov edx, offset ValueTooLarge
	call WriteString
	jmp PrintTop
; Multiplies ebx by 10 esi times
PowerTen:
	mov Power, esi
	cmp Power, 1
	jg PowerTenLoop
	ret
	PowerTenLoop:
		dec Power
		imul ebx, 10
		cmp Power, 1
		jg PowerTenLoop
		ret
; Increments the index of the stack and then enters the data stored in eax into the top of the stack
PushStack:
	cmp StackIndex, STACKSIZE - 1
	jge StackOverflow
	inc StackIndex
	mov esi, StackIndex
	; Multiplies the index by four because each element of the stack is four bytes
	imul esi, 4
	mov [MyStack + esi], eax
	ret
; Moves the value stored at the top of the stack into edx and decrements the stack index
PopStack:
	mov esi, StackIndex
	imul esi, 4
	mov edx, [MyStack + esi]
	dec StackIndex
	mov esi, StackIndex
	imul esi, 4
	ret 
; Prints that the stack is already full
StackOverflow:
	mov edx, offset OvFlowMsg
	call WriteString
	jmp PrintTop
; Converts the string into an integer and places it on the stack
Digit:
	mov edi, InpIndex
	mov edx, 0
	mov eax, offset Input
	mov ecx, BUFFERSIZE
	call ConvertToInt
	mov eax, 0
	mov eax, edx
	call PushStack
	cmp Negative, 1
	je IsNegative
	jmp PrintTop
; Prints the top element in the stack if one exists and prints "Assembly Calculator"
PrintTop:
	mov edx, offset Prompt1
	call WriteString
	cmp StackIndex, 0
	jl Menu
	mov esi, StackIndex
	imul esi, 4
	mov eax, [MyStack + esi]
	call WriteInt
	mov edx, offset Newline
	call WriteString
	jmp Menu
; Moves every existing element in the stack up a slot and places the top element into the bottom of the stack
RollUp:
	cmp StackIndex, 1
	jl StackTooSmall
	mov esi, StackIndex
	mov TempIndex, esi
	imul esi, 4
	mov ebx, [MyStack + esi]
	RollUpLoop:
		cmp esi, 0
		jl RollUpDone
		call PopStack
		mov [MyStack + esi + 8], edx
		jmp RollUpLoop
	RollUpDone:
		mov [MyStack], ebx
		mov esi, TempIndex
		mov StackIndex, esi
		jmp PrintTop
; Moves every existing element in the stack down a slot and places the bottom element into the top of the stack
RollDown:
	cmp StackIndex, 1
	jl StackTooSmall
	mov esi, StackIndex
	mov TempIndex, esi
	imul esi, 4
	mov ebx, [MyStack]
	mov esi, -4
	mov StackIndex, -1
	RollDownLoop:
		mov edi, StackIndex
		cmp edi, TempIndex
		jge RollDownDone
		mov eax, [MyStack + esi + 8]
		call PushStack
		jmp RollDownLoop
	RollDownDone:
		mov esi, TempIndex
		mov StackIndex, esi
		imul esi, 4
		mov [MyStack + esi], ebx
		jmp PrintTop
; Prints all of the values stored in the stack
ViewAll:
	cmp StackIndex, 0
	jl StackTooSmall
	mov esi, StackIndex
	imul esi, 4
	ViewLoop:
		mov eax, [MyStack + esi]
		call WriteInt
		mov edx, offset Newline
		call WriteString
		sub esi, 4
		cmp esi, 0
		jl PrintTop
		jmp ViewLoop
; Prints when the user enters an invalid character
InputError:
	mov edx, offset InvalidMsg
	call WriteString
	jmp PrintTop

Quit:
Main endp
end Main