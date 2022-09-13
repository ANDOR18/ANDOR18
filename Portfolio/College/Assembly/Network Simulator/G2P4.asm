title: Network Simulator
; Group 2 members: Nathaniel DeHart, Kevin Andor, Matt Oblock

include Irvine32.inc

.data
; Immediates
QUEUESIZE equ 10
PACKETSIZE equ 6
CONNECTSIZE equ 12
NODECONNECT equ 0
TRANSOFFSET equ 4
RECEIVEOFFSET equ 8
NAMEOFFSET equ 0
CONNECTOFFSET equ 1
QUEUEOFFSET equ 2
INPUTOFFSET equ 6
OUTPUTOFFSET equ 10
NODESTRUCTSIZE equ 14
FULLQUEUE equ QUEUESIZE * PACKETSIZE
DESTINATION equ 0
SENDER equ 1
ORIGIN equ 2
TIMEOUT equ 3
RECEIVED equ 4
FILEBUFFSIZE equ 100
NUMBUFFSIZE equ 10
; Node Data
QueueA byte QUEUESIZE * PACKETSIZE dup(0)
ATransB label byte
BRcvA byte PACKETSIZE dup(0)
ATransF label byte
FRcvA byte PACKETSIZE dup(0)
QueueB byte QUEUESIZE * PACKETSIZE dup(0)
BTransA label byte
ARcvB byte PACKETSIZE dup(0)
BTransC label byte
CRcvB byte PACKETSIZE dup(0)
BTransE label byte
ERcvB byte PACKETSIZE dup(0)
QueueC byte QUEUESIZE * PACKETSIZE dup(0)
CTransB label byte
BRcvC byte PACKETSIZE dup(0)
CTransD label byte
DRcvC byte PACKETSIZE dup(0)
CTransF label byte
FRcvC byte PACKETSIZE dup(0)
QueueD byte QUEUESIZE * PACKETSIZE dup(0)
DTransC label byte
CRcvD byte PACKETSIZE dup(0)
DTransE label byte
ERcvD byte PACKETSIZE dup(0)
QueueE byte QUEUESIZE * PACKETSIZE dup(0)
ETransD label byte
DRcvE byte PACKETSIZE dup(0)
ETransB label byte
BRcvE byte PACKETSIZE dup(0)
ETransF label byte
FRcvE byte PACKETSIZE dup(0)
QueueF byte QUEUESIZE * PACKETSIZE dup(0)
FTransE label byte
ERcvF byte PACKETSIZE dup(0)
FTransA label byte
ARcvF byte PACKETSIZE dup(0)
FTransC label byte
CRcvF byte PACKETSIZE dup(0)
; Node A Structure
NodeA byte 'A'
AC byte 2
PQueueA dword QueueA
QueueAIn dword QueueA
QueueAOut dword QueueA
; End of fixed portion
APointB dword NodeB
PATransB dword ATransB
PARcvB dword ARcvB
APointF dword NodeF
PATransF dword ATransF
PARcvF dword ARcvF
; End of variable portion
; Node B Structure
NodeB byte 'B'
BC byte 3
PQueueB dword QueueB
QueueBIn dword QueueB
QueueBOut dword QueueB
; End of fixed portion
BPointA dword NodeA
PBTransA dword BTransA
PBRcvA dword BRcvA
BPointC dword NodeC
PBTransC dword BTransC
PBRcvC dword BRcvC
BPointE dword NodeE
PBTransE dword BTransE
PBRcvE dword BRcvE
; End of variable portion
; Node C Structure
NodeC byte 'C'
CC byte 3
PQueueC dword QueueC
QueueCIn dword QueueC
QueueCOut dword QueueC
; End of fixed portion
CPointB dword NodeB
PCTransB dword CTransB
PCRcvB dword CRcvB
CPointD dword NodeD
PCTransD dword CTransD
PCRcvD dword CRcvD
CPointF dword NodeF
PCTransF dword CTransF
PCRcvF dword CRcvF
; End of variable portion
; Node D Structure
NodeD byte 'D'
DC byte 2
PQueueD dword QueueD
QueueDIn dword QueueD
QueueDOut dword QueueD
; End of fixed portion
DPointC dword NodeC
PDTransC dword DTransC
PDRcvC dword DRcvC
DPointE dword NodeE
PDTransE dword DTransE
PDRcvE dword DRcvE
; End of variable portion
; Node E Structure
NodeE byte 'E'
EC byte 3
PQueueE dword QueueE
QueueEIn dword QueueE
QueueEOut dword QueueE
; End of fixed portion
EPointD dword NodeD
PETransD dword ETransD
PERcvD dword ERcvD
EPointF dword NodeF
PETransF dword ETransF
PERcvF dword ERcvF
EPointB dword NodeB
PETransB dword ETransB
PERcvB dword ERcvB
; End of variable portion
; Node F Structure
NodeF byte 'F'
FC byte 3
PQueueF dword QueueF
QueueFIn dword QueueF
QueueFOut dword QueueF
; End of fixed portion
FPointA dword NodeA
PFTransA dword FTransA
PFRcvA dword FRcvA
FPointE dword NodeE
PFTransE dword FTransE
PFRcvE dword FRcvE
FPointC dword NodeC
PFTransC dword FTransC
PFRcvC dword FRcvC
; End of variable portion
EndOfNodes dword EndOfNodes
; Other data
InitPacket byte PACKETSIZE - 2 dup(0) ; (Destination, Sender, Origin, Timeout counter,...
InitRecTime word 0 ; ...Receive time)
NodeTag byte "Node: ", 0
ConnectTag byte "Connection: ", 0
SourceMsg byte "	Source Node: ", 0
PacketInfoMsg byte "Initial Message Settings", 0
TTLMsg byte "	TTL:", 0
EchoMsg byte "	Echo", 0
NoEchoMsg byte "	NoEcho", 0
DestMsg byte "	Destination Node: ", 0
ProcMsg byte "	Processing  ", 0
ErrorWriteMsg byte "There was an error writing to the file!", 0
FileName byte "NodeOutputData.txt", 0
TimeMsg byte "Time is:", 0
AtTimeMsg byte "		At time ", 0
ReceiveMsg byte " a message was received from  ", 0
GeneratedMsg byte "			A message was generated for  ", 0
MsgSentMsg byte "				The message was sent", 0
MsgNotSentMsg byte "				The message was not sent", 0
ThereMsg byte "There are ", 0
MsgsActiveMsg byte " messages active, ", 0
MsgsHaveMsg byte " messages have been generated at this time, and a total of ", 0
MsgsExistMsg byte " messages existed in the network", 0
ProcRcvMsg byte "'s receivers", 0
MsgRcvdMsg byte "		A message was received from  ", 0
MsgReachedMsg byte "			The message has reached its destination from  ", 0
TotTimeMsg1 byte "The process took a total of ", 0
TotTimeMsg2 byte " cycles", 0
TotMsgsGenMsg1 byte "There was a total of ", 0
TotMsgsGenMsg2 byte " messages generated", 0
AboutMsg byte "About ", 0
PercentRcvdMsg byte " percent of the messages were received", 0
ActiveMsgsMsg1 byte "There are ", 0
ActiveMsgsMsg2 byte " active messages", 0
AverageHopMsg1 byte "There was an average of ", 0
AverageHopMsg2 byte " hops done to reach the destination", 0
AverageTimeMsg1 byte "It took an average of ", 0
AverageTimeMsg2 byte " cycles for each packet to reach the destination", 0
CreateOutErrorMsg byte "There was an error creating an output file", 0
MsgDiedMsg byte "			The message died", 0
QueueFullMsg byte "			Queue is full", 13, 10, 0
QueueEmptyMsg byte "		Queue is empty", 13, 10, 0
QueueSizeMsg1 byte "	Each node's message queue can hold ", 0
QueueSizeMsg2 byte " packets", 0
NumberBuffer byte NUMBUFFSIZE dup(0)
BytesRead dword 0
InFileHandle dword 0
OutFileHandle dword 0
NewLine byte 13, 10, 0
NodePointer dword NodeA
NodeName byte 0 
NodeFrom byte 0
MessagePointer dword 0
TempPacket byte PACKETSIZE dup(0)
Time word 0
NewPacks word 0
GenPacks word 0
TotPacks word 0
ActPacks word 0
RecPacks word 0
TotalTime word 0
OutputNum dword 0
TotalHops word 0
AvgHops dword 0
AvgTime dword 0
MaxHops byte 0
Temp1 dword 0
Temp2 dword 0
Temp3 dword 0
Temp4 dword 0
Temp5 dword 0
Power dword 0
Digits dword 0
Result dword 0
Float100 Real4 100.0
EchoBool byte 0

; More Immediates
NTAGOFFSET equ sizeof NodeTag - 2
CTAGOFFSET equ sizeof ConnectTag - 2

.code
main proc
; Gives the inital packet values
; Also Outputs the initial packet information and the mode of echo
Initialize:
	mov EchoBool, 0 ; 0-No Echo, 1-Echo
	mov edi, offset InitPacket
	mov al, 'D'
	mov DESTINATION[edi], al
	mov al, 6
	mov TIMEOUT[edi], al
	mov al, 'A'
	mov SENDER[edi], al
	mov ORIGIN[edi], al

	mov al, TIMEOUT[edi]
	mov MaxHops, al
	mov Time, 0
	mov TotPacks, 1
	mov ActPacks, 1
	mov RecPacks, 0
	mov TotalHops, 0
	mov TotalTime, 0
	mov NodePointer, offset NodeA
	mov MessagePointer, offset InitPacket
	call OpenOutFile
	mov edx, offset PacketInfoMsg
	mov ecx, sizeof PacketInfoMsg
	call OutputMsg
	call OutputNewLine
	mov edx, offset QueueSizeMsg1
	mov ecx, sizeof QueueSizeMsg1
	mov OutputNum, QUEUESIZE
	call OutputMsgAndNum
	mov edx, offset QueueSizeMsg2
	mov ecx, sizeof QueueSizeMsg2
	call OutputMsg
	call OutputNewLine
	call PrintSourceNode
	call PrintDestNode
	call PrintTimeToLive
	call PrintEchoMode
	call PrintConnections
	call OutputNewLine
MainLoop:
	call Transmit
	
	call OutputNewLine
	mov edx, offset ThereMsg
	mov ecx, sizeof ThereMsg
	mov eax, 0
	mov ax, ActPacks
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset MsgsActiveMsg
	mov ecx, sizeof MsgsActiveMsg
	mov eax, 0
	mov ax, GenPacks
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset MsgsHaveMsg
	mov ecx, sizeof MsgsHaveMsg
	mov eax, 0
	mov ax, TotPacks
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset MsgsExistMsg
	mov ecx, sizeof MsgsExistMsg
	call OutputMsg
	call OutputNewLine
	call OutputNewLine

	add Time, 1
	call Receive

	call OutputNewLine
	mov edx, offset ActiveMsgsMsg1
	mov ecx, sizeof ActiveMsgsMsg1
	mov eax, 0
	mov ax, ActPacks
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset ActiveMsgsMsg2
	mov ecx, sizeof ActiveMsgsMsg2
	call OutputMsg
	call OutputNewLine
	call OutputNewLine

	mov ax, ActPacks
	cmp ax, 0
	jg MainLoop
	jmp FinishUp

; Prints out the total time, the average time taken to reach the destination node, the percentage of the messages received,...
; ...and the average hops used to reach the destination node
FinishUp:
	mov edx, offset TotTimeMsg1
	mov ecx, sizeof TotTimeMsg1
	mov eax, 0
	mov ax, Time
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset TotTimeMsg2
	mov ecx, sizeof TotTimeMsg2
	call OutputMsg
	call OutputNewLine

	mov edx, offset TotMsgsGenMsg1
	mov ecx, sizeof TotMsgsGenMsg1
	mov eax, 0
	mov ax, TotPacks
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset TotMsgsGenMsg2
	mov ecx, sizeof TotMsgsGenMsg2
	call OutputMsg
	call OutputNewLine

	mov edx, offset AboutMsg
	mov ecx, sizeof AboutMsg
	fild TotPacks
	fild RecPacks
	fdiv st(0), st(1)
	fmul Float100
	fisttp Result
	mov eax, Result
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset PercentRcvdMsg
	mov ecx, sizeof PercentRcvdMsg
	call OutputMsg
	call OutputNewLine

	mov edx, offset AverageHopMsg1
	mov ecx, sizeof AverageHopMsg1
	fild RecPacks
	fild TotalHops
	fdiv st(0), st(1)
	fisttp AvgHops
	mov eax, AvgHops
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset AverageHopMsg2
	mov ecx, sizeof AverageHopMsg2
	call OutputMsg
	call OutputNewLine

	mov edx, offset AverageTimeMsg1
	mov ecx, sizeof AverageTimeMsg1
	fild RecPacks
	fild TotalTime
	fdiv st(0), st(1)
	fisttp AvgTime
	mov eax, AvgTime
	mov OutputNum, eax
	call OutputMsgAndNum
	mov edx, offset AverageTimeMsg2
	mov ecx, sizeof AverageTimeMsg2
	call OutputMsg
	call OutputNewLine

	jmp Quit

; Prints out each node along with it's connections
PrintConnections:
	mov NodePointer, offset NodeA
	mov esi, NodePointer
	PrintConnectLoop:
		call OutputNewLine
		mov al, NAMEOFFSET[esi]
		mov edx, offset NodeTag
		mov ecx, sizeof NodeTag
		add edx, ecx
		sub edx, 2
		mov [edx], al
		mov edx, offset NodeTag
		call OutputMsg
		call OutputNewLine
		mov bl, CONNECTOFFSET[esi]
		add esi, NODESTRUCTSIZE
		NextConnect:
			mov edi, NODECONNECT[esi]
			mov al, NAMEOFFSET[edi]
			mov edx, offset ConnectTag
			mov ecx, sizeof ConnectTag
			add edx, ecx
			sub edx, 2
			mov [edx], al
			mov edx, offset ConnectTag
			call OutputMsg
			call OutputNewLine
			dec bl
			add esi, CONNECTSIZE
			cmp bl, 0
			jg NextConnect
			NextNode:
				mov esi, NodePointer
				mov bl, CONNECTOFFSET[esi]
				mov eax, CONNECTSIZE
				mul bl
				add esi, NODESTRUCTSIZE
				add esi, eax
				mov NodePointer, esi
				cmp esi, EndOfNodes
				jl PrintConnectLoop
				mov NodePointer, offset NodeA
				ret

; Reads from each node's receivers, and puts any packets found into the respective node's queue
Receive:
	mov edx, offset TimeMsg
	mov ecx, sizeof TimeMsg
	mov eax, 0
	mov ax, Time
	mov OutputNum, eax
	call OutputMsgAndNum
	mov NodePointer, offset NodeA
	mov esi, NodePointer
	ReceiveLoop:
		call OutputNewLine
		mov edx, offset ProcMsg
		mov ecx, sizeof ProcMsg
		add edx, ecx
		sub edx, 2
		mov al, NAMEOFFSET[esi]
		mov [edx], al
		mov edx, offset ProcMsg
		call OutputMsg
		mov edx, offset ProcRcvMsg
		mov ecx, sizeof ProcRcvMsg
		call OutputMsg
		call OutputNewLine

		mov bl, CONNECTOFFSET[esi]
		mov NewPacks, 0
		add esi, NODESTRUCTSIZE
		RcvConnectLoop:
			mov edi, RECEIVEOFFSET[esi]
			mov al, DESTINATION[edi]
			cmp al, 0
			je RcvNextConnect
			mov edx, offset MsgRcvdMsg
			mov ecx, sizeof MsgRcvdMsg
			add edx, ecx
			sub edx, 2
			mov al, SENDER[edi]
			mov [edx], al
			mov edx, offset MsgRcvdMsg
			call OutputMsg
			call OutputNewLine
			mov al, DESTINATION[edi]
			mov edx, NodePointer
			mov ah, NAMEOFFSET[edx]
			cmp al, ah
			je DestReached

			mov MessagePointer, edi
			mov al, TIMEOUT[edi]
			dec al
			mov TIMEOUT[edi], al
			cmp al, 0
			jg ContinueReceive
			; Message died
			dec ActPacks
			mov edx, offset MsgDiedMsg
			mov ecx, sizeof MsgDiedMsg
			call OutputMsg
			call OutputNewLine
			mov al, 0
			mov DESTINATION[edi], al
			jmp RcvNextConnect

			ContinueReceive:
				mov ax, Time
				mov RECEIVED[edi], ax
				call PutPacket
				jc FinishUp
				mov al, 0
				mov DESTINATION[edi], al
				RcvNextConnect:
					add esi, CONNECTSIZE
					dec ebx
					cmp ebx, 0
					jg RcvConnectLoop
					RcvNextNode:
						mov esi, NodePointer
						mov eax, CONNECTSIZE
						mov bl, CONNECTOFFSET[esi]
						mul bl
						add esi, eax
						add esi, NODESTRUCTSIZE
						mov NodePointer, esi
						cmp esi, EndOfNodes
						jl ReceiveLoop
						; All the nodes have been processed
						ret
			DestReached:
				dec ActPacks
				inc RecPacks
				mov eax, 0
				mov DESTINATION[edi], al
				mov al, MaxHops
				mov cl, TIMEOUT[edi]
				sub al, cl
				add TotalHops, ax
				mov eax, 0
				mov ax, RECEIVED[edi]
				add TotalTime, ax
				mov edx, offset MsgReachedMsg
				mov ecx, sizeof MsgReachedMsg
				add edx, ecx
				sub edx, 2
				mov al, ORIGIN[edi]
				mov [edx], al
				mov edx, offset MsgReachedMsg
				call OutputMsg
				call OutputNewLine
				jmp RcvNextConnect

; Transmits packets into the transmit/receive buffers to nearby nodes for each node
; Will not send a message if the receiving node's receiver buffer already contains a packet
; If Echo mode is turned off then the each node will avoid sending the packet to subsequent nodes 
Transmit:
	mov edx, offset TimeMsg
	mov ecx, sizeof TimeMsg
	mov eax, 0
	mov ax, Time
	mov OutputNum, eax
	call OutputMsgAndNum
	mov NodePointer, offset NodeA
	mov GenPacks, 0
	mov esi, NodePointer
	TransmitLoop:
		call OutputNewLine
		mov edx, offset ProcMsg
		mov ecx, sizeof ProcMsg
		add edx, ecx
		sub edx, 2
		mov eax, 0
		mov al, NAMEOFFSET[esi]
		mov [edx], al
		mov NodeName, al
		mov edx, offset ProcMsg
		call OutputMsg
		call OutputNewLine
		mov MessagePointer, offset TempPacket
		call GetPacket
		jc TransNextNode

		mov edi, MessagePointer
		mov ebx, 0
		mov bl, CONNECTOFFSET[esi]
		mov edx, offset AtTimeMsg
		mov ecx, sizeof AtTimeMsg
		mov eax, 0
		mov ax, RECEIVED[edi]
		mov OutputNum, eax
		call OutputMsgAndNum

		mov edi, MessagePointer
		mov edx, offset ReceiveMsg
		mov ecx, sizeof ReceiveMsg
		add edx, ecx
		sub edx, 2
		mov al, SENDER[edi]
		mov [edx], al
		mov NodeFrom, al
		mov al, NodeName
		mov SENDER[edi], al
		mov edx, offset ReceiveMsg
		mov ecx, sizeof ReceiveMsg
		call OutputMsg
		call OutputNewLine

		mov NewPacks, -1
		dec GenPacks
		dec TotPacks
		dec ActPacks

		add esi, NODESTRUCTSIZE
		TransConnectLoop:
			mov edx, offset GeneratedMsg
			mov ecx, sizeof GeneratedMsg
			add edx, ecx
			sub edx, 2
			mov edi, NODECONNECT[esi]
			mov al, NAMEOFFSET[edi]
			mov [edx], al
			mov edx, offset GeneratedMsg
			call OutputMsg
			call OutputNewLine
			mov eax, TRANSOFFSET[esi]
			mov cl, DESTINATION[eax]
			cmp cl, 0
			jne SkipSendPacket
			cmp EchoBool, 1
			je SendPacket
			mov al, NAMEOFFSET[edi]
			cmp NodeFrom, al
			je SkipSendPacket
			SendPacket:
				inc ActPacks
				inc NewPacks
				inc GenPacks
				inc TotPacks
				mov eax, TRANSOFFSET[esi]
				call CopyPacket
				mov ecx, PACKETSIZE
				mov edx, offset MsgSentMsg
				mov ecx, sizeof MsgSentMsg
				call OutputMsg
				call OutputNewLine
				jmp TransNextConnect
		SkipSendPacket:
			mov edx, offset MsgNotSentMsg
			mov ecx, sizeof MsgNotSentMsg
			call OutputMsg
			call OutputNewLine
			TransNextConnect:
				add esi, CONNECTSIZE
				dec bl
				cmp bl, 0
				jg TransConnectLoop
				TransNextNode:
					mov esi, NodePointer
					mov bl, CONNECTOFFSET[esi]
					mov eax, CONNECTSIZE
					mul bl
					add esi, NODESTRUCTSIZE
					add esi, eax
					mov NodePointer, esi
					cmp esi, EndOfNodes
					jl TransmitLoop
					; All of the nodes have been processed
					ret

; Copies the packet data from TempPacket to a memory address in eax
CopyPacket:
	mov Temp1, esi
	mov Temp2, edi
	mov esi, MessagePointer
	mov edi, eax
	mov ecx, PACKETSIZE
	rep movsb
	mov esi, Temp1
	mov edi, Temp2
	ret

; Outputs the message in edx to the console and a file
OutputMsg:
	call WriteString
	mov eax, OutFileHandle
	call WriteToFile
	cmp eax, 0
	je ErrorWriting
	ret

; Outputs the message in edx onto the console and a file
; Outputs a carriage return and line feed if the carry flag is set
OutputNewLine:
	clc
	mov eax, OutFileHandle
	mov edx, offset NewLine
	mov ecx, sizeof NewLine - 1
	call WriteString
	call WriteToFile
	cmp eax, 0
	je ErrorWriting
	ret

; Outputs the message in edx onto the console and a file
; Then outputs a number stored in ebx onto the console and file
; Outputs a carriage return and line feed if the carry flag is set
OutputMsgAndNum:
	call WriteString
	mov eax, OutFileHandle
	call WriteToFile
	cmp eax, 0
	je ErrorWriting
	mov edx, OutputNum
	mov eax, offset NumberBuffer
	call ConvertToString
	mov edx, offset NumberBuffer
	call WriteString
	mov eax, OutFileHandle
	call WriteToFile
	cmp eax, 0
	je ErrorWriting
	mov eax, offset NumberBuffer
	mov Temp1, ecx
	mov Temp2, ebx
	call ClearBuffer
	mov ecx, Temp1
	mov ebx, Temp2
	ret

; Converts an integer stored in edx into a character string that gets stored in a buffer whose start address is in eax
; Make sure the buffer has enough space to store the digits!
; Can't convert negative numbers!	
ConvertToString:
	mov Temp1, eax	
	mov Temp2, edx
	mov Temp3, edx
	mov Temp4, edi
	mov Temp5, ebx
	mov edi, eax
	mov Power, 10
	mov Digits, 0
	mov ecx, 0
	GetNumOfDigits:
		; Check if there is another digit
		mov edx, 0
		mov eax, Temp3
		mov ebx, Power
		div ebx
		sub Temp3, edx
		cmp Temp3, 0
		jle ConvertDigit
		inc Digits
		mov eax, Power
		mov ebx, 10
		mul ebx
		mov Power, eax
		jmp GetNumOfDigits
	ConvertDigit:
		inc ecx
		mov edx, 0
		mov eax, Power
		mov ebx, 10
		div ebx
		mov Power, eax
		mov edx, 0
		mov eax, Temp2
		mov ebx, Power
		div ebx
		mov Temp2, edx
		mov edi, Temp1
		add al, 30h
		mov [edi], al
		inc Temp1
		dec Digits
		cmp Digits, 0
		jge ConvertDigit
		mov edi, Temp4
		mov ebx, Temp5
		ret

; Prints MessagePointer's source node name
PrintSourceNode:
	mov edx, offset SourceMsg
	mov ecx, sizeof SourceMsg
	add edx, ecx
	sub edx, 2
	mov edi, MessagePointer
	mov al, SENDER[edi]
	mov bl, al
	mov [edx], al
	mov edx, offset SourceMsg
	call OutputMsg
	call OutputNewLine
	call FindSource
	ret

; Prints MessagePointer's Time To Live
PrintTimeToLive:
	mov edx, offset TTLMsg
	mov ecx, sizeof TTLMsg
	mov eax, 0
	mov edi, MessagePointer
	mov al, TIMEOUT[edi]
	mov OutputNum, eax
	call OutputMsgAndNum
	call OutputNewLine
	ret

; Prints MessagePointer's destination node name
PrintDestNode:
	mov edx, offset DestMsg
	mov ecx, sizeof DestMsg
	add edx, ecx
	sub edx, 2
	mov eax, 0
	mov edi, MessagePointer
	mov al, DESTINATION[edi]
	mov [edx], al
	mov edx, offset DestMsg
	call OutputMsg
	CALL OutputNewLine
	ret

; Prints the current echo mode
PrintEchoMode:
	mov edx, offset EchoMsg
	mov ecx, sizeof EchoMsg
	cmp EchoBool, 1
	je PrintEcho
	mov edx, offset NoEchoMsg
	mov ecx, sizeof NoEchoMsg
	PrintEcho:
		call OutputMsg
		call OutputNewLine
		ret

; Requires the sender name to be stored in bl
FindSource:
	mov edi, NodePointer
	cmp NAMEOFFSET[edi], bl
	je FinishFind
	mov ecx, 0
	mov cl, CONNECTOFFSET[edi]
	add edi, NODESTRUCTSIZE
	mov eax, CONNECTSIZE
	mul ecx
	add edi, eax
	mov NodePointer, edi
	cmp edi, EndOfNodes
	jl FindSource
	mov NodePointer, offset NodeA
	FinishFind:
		call PutPacket
		jc FinishUp
		ret

; Prints to the console that there was an error writing to the file
ErrorWriting:
	mov edx, offset ErrorWriteMsg
	mov ecx, sizeof ErrorWriteMsg
	call WriteString
	jmp Quit

; Creates an output file
OpenOutFile:
	mov edx, offset FileName
	mov ecx, sizeof FileName
	call CreateOutputFile
	mov OutFileHandle, eax
	cmp eax, INVALID_HANDLE_VALUE
	je OutFileError
	ret

; Sets ecx bytes of the buffer in eax equal to 0
ClearBuffer:
	mov bl, 0
	cmp [eax], bl
	je ClearDone
	cmp ecx, 0
	je ClearDone
	mov [eax], bl
	inc eax
	dec ecx
	jmp ClearBuffer
ClearDone:
	ret

; Prints to the console that there was an error opening the file
OutFileError:
	mov edx, offset CreateOutErrorMsg
	mov ecx, sizeof CreateOutErrorMsg
	call WriteString
	jmp Quit

; Puts a packet into the queue of the node in NodePointer and increments the node's output pointer
PutPacket:
	mov Temp1, esi
	mov Temp2, edi
	mov Temp3, ebx
	mov edx, NodePointer
	mov eax, INPUTOFFSET[edx]
	add eax, PACKETSIZE
	mov ebx, QUEUEOFFSET[edx]
	add ebx, FULLQUEUE
	cmp eax, ebx
	jl PutIt
	mov eax, QUEUEOFFSET[edx]
	PutIt:
		mov ebx, OUTPUTOFFSET[edx]
		cmp eax, ebx
		je QueueFull
		cld
		mov esi, MessagePointer
		mov edi, INPUTOFFSET[edx]
		mov ecx, PACKETSIZE
		rep movsb
		mov INPUTOFFSET[edx], eax
		mov esi, Temp1
		mov edi, Temp2
		mov ebx, Temp3
		clc
		ret

; Puts the address of NodePointer's output queue packet into MessagePointer 
; Then increments NodePointer's OutPointer so that it points at the next packet
GetPacket:
	mov Temp1, eax
	mov Temp2, ebx
	mov edx, NodePointer	
	mov ebx, INPUTOFFSET[edx]
	mov eax, OUTPUTOFFSET[edx]
	cmp eax, ebx
	je QueueEmpty
	mov MessagePointer, eax
	add eax, PACKETSIZE
	mov ebx, QUEUEOFFSET[edx]
	add ebx, FULLQUEUE
	cmp eax, ebx
	jl GetPContinued
	mov eax, QUEUEOFFSET[edx]
	GetPContinued:
		mov OUTPUTOFFSET[edx], eax
		mov eax, Temp1
		mov ebx, Temp2
		clc
		ret

; Prints that the queue was full and sets the carry flag
QueueFull:
	mov edx, offset QueueFullMsg
	mov ecx, sizeof QueueFullMsg
	call OutputMsg
	call OutputNewLine
	stc
	mov esi, Temp1
	mov edi, Temp2
	mov ebx, Temp3
	ret

; Sets the carry flag
QueueEmpty:
	;mov edx, offset QueueEmptyMsg
	;mov ecx, sizeof QueueEmptyMsg
	;call WriteString
	stc
	mov eax, Temp1
	mov ebx, Temp2
	ret

; Prints a carriage return and line feed to the console
NextLine:
	mov Temp1, edx
	mov edx, offset NewLine
	call WriteString
	mov edx, Temp1
	ret

; Ends the program
Quit:
	mov eax, OutFileHandle
	call CloseFile
	exit
main endp
end main