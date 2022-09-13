include Irvine32.inc

.data
; Immediates
DATASIZE equ 100
FILENAMELENGTH equ 81
FILEBUFFERSIZE equ 100
INPUTBUFFSIZE equ 10
; File data
Data byte DATASIZE dup(0)
InFileHandle dword 0
OutFileHandle dword 0
BytesRead dword 0
FileName byte FILENAMELENGTH dup(0)
FileBuffer byte FILEBUFFERSIZE dup(0)
EndOfFileBuffer byte 0
InputBuff byte INPUTBUFFSIZE dup(0)
EndOfInputBuff byte 0
Prompt byte "Please enter the data that you wish to be placed in a file", 13, 10, 0
PromptFile byte "Would you like to create (C) or input (I) a file?", 13, 10, 0 
PromptName byte "Enter the name of the file: ", 0
FileErrorMessage byte "Error opening file.", 0
FileReadMessage byte "Error reading file.", 0
FileWriteMessage byte "Error writing file.", 0

.code
main proc
MainProcess:
	;mov edx, offset PromptFile
	;call WriteString
	;mov edx, offset InputBuff
	;mov ecx, INPUTBUFFSIZE
	;call ReadString
	;mov al, [edx]
	call InputFile
	call CreateOFile
	jmp ReadWriteLoop
; Sets ecx bytes of a buffer whose address is in eax to 0
ClearBuffer:
	cmp ecx, 0
	jg ClearByte
	ret
	ClearByte:
		mov bl, 0
		mov [eax + ecx], bl
		dec ecx
		jmp ClearBuffer
; 
CreateOFile:
	call GetFileName
	mov edx, offset FileName
	call CreateOutputFile
	mov OutFileHandle, eax
	cmp eax, INVALID_HANDLE_VALUE
	je OutFileError
	ret
;
InputFile:
	call GetFileName
	mov edx, offset FileName
	call OpenInputFile
	mov InFileHandle, eax
	cmp eax, INVALID_HANDLE_VALUE
	je InFileError
	ret
; 
InFileError:
	mov edx, offset FileErrorMessage
	mov ecx, sizeof FileErrorMessage
	call WriteString
	jmp Quit
; 
OutFileError:
	mov edx, offset FileErrorMessage
	mov ecx, sizeof FileErrorMessage
	call WriteString
	mov eax, InFileHandle
	call CloseFile
	jmp Quit
; 
ReadError:
	mov edx, offset FileReadMessage
	mov ecx, sizeof FileReadMessage
	call WriteString
	jmp CloseFiles
	
; 
WriteError:
	mov edx, offset FileWriteMessage
	mov ecx, sizeof FileWriteMessage
	call WriteString
	jmp CloseFiles
; 
GetFileName:
	mov edx, offset PromptName
	call WriteString
	mov edx, offset FileName
	mov ecx, FILENAMELENGTH
	call ReadString
	ret
; 
ReadWriteLoop:
	;Reading file to buffer
	mov eax, InFileHandle
	mov edx, offset FileBuffer
	mov ecx, FILEBUFFERSIZE
	call ReadFromFile
	jc ReadError
	mov BytesRead, eax
	cmp eax, 0
	jle DoneLoop
	mov FileBuffer[eax], 0

	;Writing buffer to file
	mov eax, OutFileHandle
	mov edx, offset FileBuffer
	mov ecx, BytesRead
	call WriteToFile
	cmp eax, 0
	je WriteError
	jmp ReadWriteLoop

	DoneLoop:
		jmp CloseFiles
; 
CloseFiles:
	mov eax, InFileHandle
	call CloseFile
	mov eax, OutFileHandle
	call CloseFile
	jmp Quit

; 
Quit:
	exit
main endp
end main