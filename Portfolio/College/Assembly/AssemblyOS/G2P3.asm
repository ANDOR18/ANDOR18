title: Assembly Language Programming Project 3 Operating System
; Group 2 Members-Nathaniel DeHart, Kevin Andor, and Matt Oblock

include Irvine32.inc

.data
INPUTLENGTH	equ 50
RECORDLENGTH equ 14 ; Record data is stored in the following order: (job, priority, runtime, starttime, status)
JOBLENGTH equ 8
PRIORITYLENGTH equ 1
RUNTIMELENGTH equ 2
STARTTIMELENGTH equ 2
STATUSLENGTH equ 1
RECORDNUM equ 10
; TOTALRECORDSLENGTH should always be equal to RECORDLENGTH times RECORDNUM
TOTALRECORDSLENGTH equ 140
ENTRYLENGTH equ 10
STEPPRINTLENGTH equ 20
temp1 dword 0
temp2 dword 0
temp3 dword 0
temp4 dword 0
temp5 dword 0
inputTime dword 0
recIndex dword 0
QUIT byte "quit", 0
HELP byte "help", 0
LOAD byte "load", 0
RUN byte "run", 0
HOLD byte "hold", 0
KILL byte "kill", 0
SHOW byte "show", 0
STEP byte "step", 0
CHANGE byte "change", 0
newline byte 13, 10, 0
welcome byte "Assembly OS Version 1.0", 13, 10, 0
menuPrompt byte "-----------------------MENU (Type ", 22h, "help", 22h, " for command list)-----------------------", 13, 10, 0
blankLine byte "             ", 0

input byte INPUTLENGTH dup(' ')
endofinput byte 0
records byte TOTALRECORDSLENGTH dup(' ')
endofrecord byte 0
entry byte ENTRYLENGTH dup(' ')
endofentry byte 0
curJobIndex dword 0
curPriSearch dword 0
stepPrintBuffer dword STEPPRINTLENGTH dup(0)
endofstepprint byte 0
stepPrintIndex dword 0

tempResult sdword 0
wordLength dword 0
power dword 0
jobLabels byte "Name      Priority  Runtime   Starttime Status", 13, 10, 0
startPriority byte "0"
startRuntime byte "35"
startStarttime byte "35"
holdStatus byte "H"
availStatus byte "A"
runStatus byte "R"
systemClock dword 0
digits dword 0
loadTemp1 dword 0
loadTemp2 dword 0
loadTemp3 dword 0
curNameLngth dword 0
maxChars dword 0

pJob byte "No job name was entered", 13, 10, 0
pPri byte "An invalid priority was entered", 13, 10, 0
pRun byte "An invalid runtime was entered", 13, 10, 0
pLoad byte "Please enter the load parameters, (job) (priority) (run-time): ", 0

helpQuit byte "QUIT: Quits the program", 13, 10, 0
helpHelp byte "HELP: Gives list of commands", 13, 10, 0
helpShow byte "SHOW: Displays every job that is currently in the queue", 13, 10, 0
helpRun byte "RUN (job): Takes the name of a current job and changes its status from hold to run", 13, 10, 0
helpHold byte "HOLD (job): Takes the name of a current job and changes its staus from run to hold", 13, 10, 0
helpKill byte "KILL (job): Terminates the job, the jobs status must be hold", 13, 10, 0
helpStep byte "STEP (integer): Takes an integer and processes the jobs that many of steps", 13, 10, 0
helpChange byte "CHANGE (job) (priority): Changes priority of the job entered to the integer value entered of 0 - 7", 13, 10, 0
helpLoad byte "LOAD (job) (priority) (run-time): Queues a job, job must be less than 9 characters, priority 0 - 7, and run-time 1 - 50", 13, 10, 0

NoJobsR byte "No jobs are currenty in the run mode", 13, 10, 0
jobNotFound byte "Job does not exist", 13, 10, 0
tooManyP byte "There were too many entries. EX: (job) (priority) (run-time)", 13, 10, 0
noRecords byte "There are no jobs in the queue", 13, 10, 0
notUnique byte "Job already exists", 13, 10, 0
notAvailable byte "No jobs are available", 13, 10, 0
notInHold byte "A job must be in the hold mode to kill", 13, 10, 0
notPriority byte "Not a valid priority, must be between 0 - 7", 13, 10, 0 
notRunTime byte "Not a valid run-times, must be between 1- 50", 13, 10 , 0
notStatus byte "Not a valid status, must be either H = (HOLD), or R = (RUN)", 13, 10, 0
notCommand byte "Please enter a valid command", 13, 10, 0
jobTooLong byte "Job has too many characters, please enter a job with less than 9 characters", 13, 10, 0
jobListFull byte "There are no more job slots available", 13, 10, 0
notStep byte "Not a valid step, must be and integer greater than 0", 13, 10, 0
finishedRun byte " has finished running", 13, 10, 0

mesgRUN byte "'s mode has been set to RUN at Time: ", 0
mesgHOLD byte "'s mode has been set to HOLD at Time: ", 0
mesgKILL byte " has been removed from the job queue at Time: ", 0
mesgCHNG1 byte "'s priority has been changed to: ", 0
mesgCHNG2 byte " at Time: ", 0
mesgLOAD byte " has been added to the job queue at Time: ", 0
mesgSTEP1 byte " has gone through ", 0
mesgSTEP2 byte " cycles at Time: ", 0 

.code
Main proc
	call JobInit
	mov edx, offset welcome
	call WriteString
	; Takes text inputs and passes them on to CommandHandler
	Menu:
		mov edx, offset newline
		call WriteString
		mov edx, offset menuPrompt
		call WriteString
		mov edx, offset newline
		call WriteString
		mov eax, offset input
		mov ecx, INPUTLENGTH
		call ClearBuffer
		mov eax, offset entry
		mov ecx, ENTRYLENGTH
		call ClearBuffer
		mov edx, offset blankline
		call WriteString
		mov edx, offset input
		mov ecx, INPUTLENGTH
		call ReadString
		mov esi, edx
		mov ecx, eax
		mov edi, offset entry
		call SkipSpace
		mov maxChars, ENTRYLENGTH
		call GetString
		call LowerCase
		call CommandHandler
		jmp Menu

	; "records" and gives each record starting values
	; Sets the status to 'A' for available
	JobInit:
		mov recIndex, 0
		mov edi, offset records
		JobInitLoop:
			cmp recIndex, TOTALRECORDSLENGTH
			jge JobInitDone
			mov eax, offset availStatus
			call SetStatus
			add recIndex, RECORDLENGTH
			add edi, RECORDLENGTH
			jmp JobInitLoop
		JobInitDone:
			ret

	; Calls the function that corresponds to the inputted command
	CommandHandler:
		mov curNameLngth, ecx
		StepCheck:
			mov ecx, LENGTHOF step - 1
			cmp ecx, curNameLngth
			jne RunCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset step
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je StepCommand
		RunCheck:
			mov ecx, LENGTHOF run - 1
			cmp ecx, curNameLngth
			jne LoadCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset run
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je RunCommand
		LoadCheck:
			mov ecx, LENGTHOF load - 1
			cmp ecx, curNameLngth
			jne ShowCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset load
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je LoadCommand
		ShowCheck:
			mov ecx, LENGTHOF show - 1
			cmp ecx, curNameLngth
			jne HelpCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset show
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je ShowCommand
		HelpCheck:
			mov ecx, LENGTHOF help - 1
			cmp ecx, curNameLngth
			jne HoldCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset help
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je HelpCommand
		HoldCheck:
			mov ecx, LENGTHOF hold - 1
			cmp ecx, curNameLngth
			jne ChangeCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset hold
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je HoldCommand
		ChangeCheck:
			mov ecx, LENGTHOF change - 1
			cmp ecx, curNameLngth
			jne KillCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset change
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je ChangeCommand
		KillCheck:
			mov ecx, LENGTHOF kill - 1
			cmp ecx, curNameLngth
			jne QuitCheck
			mov ebx, esi
			mov eax, edi
			mov esi, offset kill
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je KillCommand
		QuitCheck:	
			mov ecx, LENGTHOF quit - 1
			cmp ecx, curNameLngth
			jne InvalidCommand
			mov ebx, esi
			mov eax, edi
			mov esi, offset quit
			cld
			repe cmpsb
			mov esi, ebx
			mov edi, eax
			je QuitCommand
		InvalidCommand:
			mov edx, offset notCommand
			call WriteString
			ret
	
	; Prompts the user to re-enter the load parameters and re-checks if the entered jobname already exists
	InvalidLoad:
		mov edx, offset pLoad
		call WriteString
		mov eax, offset input
		mov ecx, INPUTLENGTH
		call ClearBuffer
		mov edx, offset input
		mov ecx, INPUTLENGTH
		call ReadString
		mov ecx, RECORDLENGTH
		mov esi, offset blankLine
		mov edi, loadTemp1
		rep movsb
		mov esi, offset input
		mov eax, offset entry
		mov ecx, ENTRYLENGTH
		call ClearBuffer
		mov edi, offset entry
		call SkipSpace
		mov loadTemp2, esi
		call GetString
		call LowerCase
		mov esi, loadTemp2
		mov edi, offset entry
		call FindJob
		cmp edx, -1
		jne NotUniqueJob
		jmp ContinueLoad

	; Writes a statement about an invalid job name and jumps back to the menu
	PromptJob:
		mov edx, offset pJob
		call WriteString
		jmp Menu

	; Writes a statement about an invalid priority and jumps back to the menu
	PromptPri:
		mov edx, offset pPri
		call WriteString
		jmp Menu
	
	; Decrements the highest priority job's runtime until it has cycled the number of steps entered
	; If a job's runtime hits 0 StepCommand loops to the next highest priority job
	StepCommand:
		mov edx, offset newline
		call WriteString
		call SkipSpace
		call GetString
		mov curJobIndex, 0
		mov curPriSearch, 0
		mov stepPrintIndex, 0
		mov eax, edi
		mov bl, [edi]
		cmp bl, 's'
		je OneStep
		cmp bl, 31h
		jl InvalidStep
		cmp bl, 39h
		jg InvalidStep
		call ConvertToInt
		mov inputTime, edx
		cmp edx, 0
		jg StepLoop
		jmp OneStep
		InvalidStep:
			mov edx, offset notStep
			call WriteString
			ret
		OneStep:
			mov inputTime, 1
		StepLoop:
			cmp inputTime, 0
			mov temp3, 0
			mov ebx, 0
			jle PrintStepping
			call FindHighPriority
			mov ebx, RECORDLENGTH
			mov edx, 0
			idiv ebx
			mov edx, 0
			mov ebx, 8
			mul ebx
			mov stepPrintIndex, eax
			cmp esi, 0
			je NoValidJobs
			inc systemClock
			dec inputTime
			mov edi, offset entry
			mov temp5, esi
			call GetString
			mov curNameLngth, ecx
			mov esi, temp5
			mov edi, esi
			call GetRuntime
			mov eax, edx
			mov ecx, RUNTIMELENGTH
			call ConvertToInt
			mov temp3, eax
			dec edx
			mov ecx, 1
			mov eax, stepPrintIndex
			add [stepPrintBuffer + eax], ecx
			mov ecx, systemClock
			mov [stepPrintBuffer + eax + 4], ecx
			cmp edx, 0
			jle JobDone
			mov ecx, 2
			mov eax, temp3
			call ClearBuffer
			mov eax, temp3
			call ConvertToString
			jmp StepLoop
		JobDone:
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer
			mov esi, offset records
			mov edx, 0
			mov eax, stepPrintIndex
			mov ebx, 8
			idiv ebx
			mov edx, 0
			mov ebx, RECORDLENGTH
			mul ebx
			mov temp4, eax
			add esi, eax

			mov edi, offset entry
			mov ecx, JOBLENGTH
			call GetString
			mov bl, 0
			mov [edi + ecx], bl

			mov edx, offset entry
			call WriteString
			mov edi, offset entry
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			rep movsb
			mov esi, temp5
			mov edx, offset finishedRun
			call WriteString
			mov edi, esi
			mov eax, offset holdStatus
			call SetStatus
			call KillCommand
			mov edx, offset newline
			call WriteString

			mov esi, offset stepPrintBuffer
			add esi, stepPrintIndex
			mov ecx, 0
			mov [esi], ecx
			mov [esi + 4], ecx

			jmp StepLoop
		NoValidJobs:
			mov temp3, 0
			call PrintStepping
			mov edx, offset noJobsR
			call WriteString
			ret
		PrintStepping:
			mov esi, offset stepPrintBuffer
			add esi, temp3
			mov eax, [esi]
			cmp eax, 0
			jle SkipPrint
			mov temp4, eax
			mov eax, [esi + 4]
			mov temp5, eax

			mov esi, offset records
			mov edx, 0
			mov eax, temp3
			mov ebx, 8
			idiv ebx
			mov edx, 0
			mov ebx, RECORDLENGTH
			mul ebx
			add esi, eax

			mov edi, offset entry
			mov ecx, JOBLENGTH
			call GetString
			mov bl, 0
			mov [edi + ecx], bl
			mov edx, edi
			call WriteString
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			rep movsb
			mov edx, offset mesgSTEP1
			call WriteString

			mov eax, temp4
			call WriteInt
			mov edx, offset mesgSTEP2
			call WriteString
			mov eax, temp5
			call WriteInt
			mov edx, offset newline
			call WriteString
		SkipPrint:
			mov esi, offset stepPrintBuffer
			add esi, temp3
			mov ecx, 0
			mov [esi], ecx
			mov [esi + 4], ecx
			add temp3, 8
			cmp temp3, sizeof stepPrintBuffer
			jl PrintStepping
			ret

	; Searches for the current job with the highest priority that's in run mode
	; If at least one job was in run mode then it puts the address of the one with the highest priority into esi
	FindHighPriority:
		mov edi, offset records
		mov eax, curJobIndex
		add eax, RECORDLENGTH
		mov curPriSearch, 0
		add edi, eax
		mov esi, edi
		mov ebx, 0
		FindPriLoop:
			cmp eax, TOTALRECORDSLENGTH
			jl ContinuePriLoop
			mov eax, 0
		ContinuePriLoop:
			cmp eax, curJobIndex
			je NoRunsFoundSoFar
			mov esi, offset records
			add esi, eax
			mov edi, esi
			call GetStatus
			mov bl, [edx]
			cmp bl, 'R'
			jne SkipPriCheck
			call GetPriority
			mov bl, [edx]
			movzx ecx, bl
			sub ecx, 30h
			cmp ecx, curPriSearch
			je FoundPri
			add eax, RECORDLENGTH
			jmp FindPriLoop
		FoundPri:
			mov curJobIndex, eax
			ret
		SkipPriCheck:
			add eax, RECORDLENGTH
			jmp FindPriLoop
		MaybeFoundPri:
			call GetPriority
			mov bl, [edx]
			movzx ecx, bl
			sub ecx, 30h
			cmp ecx, curPriSearch
			je FoundPri
			jmp KeepLooking
		NoRunsFoundSoFar:
			mov edi, offset records
			add edi, curJobIndex
			call GetStatus
			mov bl, [edx]
			mov esi, edi
			cmp bl, 'R'
			je MaybeFoundPri
		KeepLooking:
			cmp curPriSearch, 7
			jge NoRunModes
			inc curPriSearch
			mov eax, curJobIndex
			add eax, RECORDLENGTH
			add edi, eax
			mov esi, edi
			jmp FindPriLoop
		NoRunModes:
			mov edi, offset records
			add edi, curJobIndex
			call GetStatus
			mov bl, [edx]
			mov esi, edi
			cmp bl, 'R'
			je FoundPri
			mov esi, 0
			ret
			
	; Searches for the entered job name amongst the records and sets it's status to run mode ('R') if it finds it
	RunCommand:
		mov eax, offset entry
		mov ecx, ENTRYLENGTH
		call ClearBuffer
		call SkipSpace
		call GetString
		mov curNameLngth, ecx
		mov bl, ' '
		cmp [edi], bl
		je PromptJob
		call LowerCase
		call FindJob
		cmp edx, -1
		jne ContinueRun
		mov edx, offset jobNotFound
		call WriteString
		ret
		ContinueRun:
			mov edi, edx
			mov eax, offset runStatus
			call SetStatus
			mov bl, 0
			mov ecx, curNameLngth
			mov edx, offset entry
			mov [edx + ecx], bl
			call WriteString
			mov edx, offset mesgRUN
			call WriteString
			mov eax, systemClock
			call WriteInt
			mov edx, offset newline
			call WriteString
			mov edi, offset entry
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			rep movsb
			ret
				
	; Initializes the next available job slot with the given parameterized values entered by the user
	; Restricts the user to 8 characters for the jobname, priority to integers (0-7), and runtime to integers (1-50)
	LoadCommand:
		mov eax, offset entry
		mov ecx, ENTRYLENGTH
		call ClearBuffer
		call SkipSpace
		mov loadTemp2, esi
		mov maxChars, JOBLENGTH
		call GetString
		call LowerCase
		mov edx, edi
		call FindAvailable
		cmp edi, -1
		je NoJobsAvailable
		mov loadTemp1, edi
		xchg esi, loadTemp2
		mov bl, [esi]
		xchg esi, loadTemp2
		cmp bl, ' '
		je InvalidLoad
		cmp bl, 0
		je InvalidLoad
		mov esi, loadTemp2
		mov edi, offset entry
		call FindJob
		cmp edx, -1
		jne NotUniqueJob
		ContinueLoad:
			call SkipSpace
			mov edi, loadTemp1
			mov bl, ' '
			cmp [esi], bl
			je InvalidLoad
			call GetString
			cmp ecx, JOBLENGTH
			jg NameTooLong
			call LowerCase	
			add	edi, JOBLENGTH
			call SkipSpace
			mov bl, " "
			cmp [esi], bl
			je InvalidLoad
			mov bl, 0
			cmp [esi], bl
			je InvalidLoad
			call GetString
			cmp ecx, 1
			jg InvalidLoadPri
			mov bl, [edi]
			cmp bl, 30h
			jl InvalidLoadPri
			cmp bl, 37h
			jg InvalidLoadPri
			add edi, PRIORITYLENGTH
			call SkipSpace
			mov loadTemp3, esi
			mov bl, " "
			cmp [esi], bl
			je InvalidLoad
			mov bl, 0
			cmp [esi], bl
			je InvalidLoad
			call GetString
			cmp ecx, 2
			jg InvalidLoadRun
			mov eax, edi
			mov ecx, RUNTIMELENGTH
			call ConvertToInt
			cmp edx, 1
			jl InvalidLoadRun
			cmp edx, 50
			jg InvalidLoadRun
			mov esi, loadTemp3
			add edi, RUNTIMELENGTH
			call GetString
			add edi, STARTTIMELENGTH
			mov bl, 'H'
			mov [edi], bl
			call SkipSpace
			call GetString
			cmp ecx, 0
			jg TooManyParams
			mov esi, loadTemp2
			mov edi, offset entry
			call GetString
			call LowerCase
			mov bl, 0
			mov [edi + ecx], bl
			mov edx, edi
			call WriteString
			mov edx, offset mesgLOAD
			call WriteString
			mov eax, systemClock
			call WriteInt
			mov edx, offset newline
			call WriteString
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			rep movsb
			ret
		TooManyParams:
			mov edx, offset tooManyP
			call WriteString
			jmp InvalidLoad
		InvalidLoadPri:
			mov edx, offset notPriority
			call WriteString
			jmp InvalidLoad
		InvalidLoadRun:
			mov edx, offset notRunTime
			call WriteString
			jmp InvalidLoad
		NoJobsAvailable:
			ret
		NameTooLong:
			mov edx, edi
			call WriteString
			mov edx, offset jobTooLong
			call WriteString
			jmp InvalidLoad
		NotUniqueJob:
			mov edx, offset notUnique
			call WriteString
			jmp InvalidLoad

	; Loops through the individual records until it reaches the end or finds one with the available ('A') status
	; Puts the address of the first available record into edi if it finds one
	FindAvailable:
		mov edi, offset records
		mov temp1, ebx
		mov temp2, eax
		mov ebx, 0
		mov eax, 0
		FindAvailLoop:
			cmp eax, TOTALRECORDSLENGTH
			jge NoAvailRecords
			add eax, JOBLENGTH
			add eax, PRIORITYLENGTH
			add eax, RUNTIMELENGTH
			add eax, STARTTIMELENGTH
			mov bl, [edi + eax]
			add eax, PRIORITYLENGTH
			cmp bl, 'A'
			jne FindAvailLoop
			sub eax, RECORDLENGTH
			add edi, eax
			mov ebx, temp1
			mov eax, temp2
			ret
		NoAvailRecords:
			mov edx, offset jobListFull
			call WriteString
			mov edi, -1
			mov ebx, temp1
			mov eax, temp2
			ret

	; Shows the entire contents of records (i.e. the job's name, priority, runtime, starttime, and status
	ShowCommand:
		mov edx, offset newline
		call WriteString
		mov edx, offset jobLabels
		call WriteString
		mov edx, offset newline
		call WriteString
		mov ebx, 0
		mov ecx, 0
		mov esi, offset records
		ShowLoop:
			cmp ebx, TOTALRECORDSLENGTH
			jge ShowDone
			mov eax, esi
			add eax, JOBLENGTH
			add eax, PRIORITYLENGTH
			add eax, RUNTIMELENGTH
			add eax, STARTTIMELENGTH
			mov dl, 'A'
			cmp [eax], dl
			je SkipShowJob
				
			mov edi, offset entry
			mov ecx, JOBLENGTH
			rep movsb
			mov edx, offset entry
			call WriteString
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer

			mov edi, offset entry
			mov ecx, PRIORITYLENGTH
			rep movsb
			mov edx, offset entry
			call WriteString
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer
	
			mov edi, offset entry
			mov ecx, RUNTIMELENGTH
			rep movsb
			mov edx, offset entry
			call WriteString
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer
	
			mov edi, offset entry
			mov ecx, STARTTIMElENGTH
			rep movsb
			mov edx, offset entry
			call WriteString
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer
	
			mov edi, offset entry
			mov ecx, STATUSLENGTH
			rep movsb
			mov edx, offset entry
			call WriteString
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer
	
			mov edx, offset newline
			call WriteString
			add ebx, RECORDLENGTH
			jmp ShowLoop
		SkipShowJob:
			add ebx, RECORDLENGTH
			add esi, RECORDLENGTH
			jmp ShowLoop
		ShowDone:
			cmp ecx, 0
			jne JobExists
			mov edx, offset noRecords
			call WriteString
		JobExists:
			mov edx, offset newline
			call WriteString
			ret
	
	; Prints out command information for the user
	HelpCommand:
		mov edx, offset helpQuit
		call WriteString
		mov edx, offset helpHelp
		call WriteString
		mov edx, offset helpShow
		call WriteString
		mov edx, offset helpRun
		call WriteString
		mov edx, offset helpHold
		call WriteString
		mov edx, offset helpKill
		call WriteString
		mov edx, offset helpStep
		call WriteString
		mov edx, offset helpChange
		call WriteString
		mov edx, offset helpLoad
		call WriteString
		ret

	; Searches for the entered job name amongst the records and sets it's status to hold mode ('H') if it finds it
	HoldCommand:
		mov eax, offset entry
		mov ecx, ENTRYLENGTH
		call ClearBuffer
		call SkipSpace
		call GetString
		mov curNameLngth, ecx
		mov bl, ' '
		cmp [edi], bl
		je PromptJob
		call LowerCase
		call FindJob
		cmp edx, -1
		jne ContinueHold
		mov edx, offset jobNotFound
		call WriteString
		ret
		ContinueHold:
			mov edi, edx
			mov eax, offset holdStatus
			call SetStatus
			mov bl, 0
			mov ecx, curNameLngth
			mov edx, offset entry
			mov [edx + ecx], bl
			call WriteString
			mov edx, offset mesgHOLD
			call WriteString
			mov eax, systemClock
			call WriteInt
			mov edx, offset newline
			call WriteString
			mov edi, offset entry
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			rep movsb
			ret

	; Searches for the entered job name amongst the records and sets it's priority equal to the next parameter if it was a valid priority
	ChangeCommand:
		mov eax, offset entry
		mov ecx, ENTRYLENGTH
		call ClearBuffer
		call SkipSpace
		mov temp5, esi
		call GetString
		mov bl, ' '
		cmp [edi], bl
		je PromptJob
		call LowerCase
		call FindJob
		cmp edx, -1
		jne ContinueChange
		mov edx, offset jobNotFound
		call WriteString
		ret
		ContinueChange:
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer
			call SkipSpace
			call GetString
			cmp ecx, PRIORITYLENGTH
			jg PromptPri
			mov bl, [edi]
			cmp bl, 30h
			jl PromptPri
			cmp bl, 37h
			jg PromptPri
			mov eax, edi
			mov edi, edx
			call SetPriority
			mov esi, temp5
			mov ebx, eax
			mov eax, offset entry
			mov ecx, ENTRYLENGTH
			call ClearBuffer
			mov edi, offset entry
			call GetString
			mov bl, 0
			mov [edi + ecx], bl
			mov edx, edi
			call WriteString
			mov edx, offset mesgCHNG1
			call WriteString
			mov ebx, esi
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			rep movsb
			mov esi, ebx
			mov edi, offset entry
			call SkipSpace
			call GetString
			mov bl, 0
			mov [edi + ecx], bl
			mov edx, edi
			call WriteString
			mov edx, offset mesgCHNG2
			call WriteString
			mov eax, systemClock
			call WriteInt
			mov edx, offset newline
			call WriteString
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			mov edi, offset entry
			rep movsb
			ret

	; Searches for the entered job name amongst the records and clears it out if it was in hold mode ('H')
	; Reads the name of the job to kill from an address stored in esi
	KillCommand:
		mov eax, offset entry
		mov ecx, ENTRYLENGTH
		call ClearBuffer
		mov edi, offset entry
		call SkipSpace
		call GetString
		mov curNameLngth, ecx
		mov bl, ' '
		cmp [edi], bl
		je PromptJob
		call LowerCase
		call FindJob
		cmp edx, -1
		jne ContinueKill1
		mov edx, offset jobNotFound
		call WriteString
		ret
		ContinueKill1:
			mov eax, edx
			mov edi, edx
			call GetStatus
			mov bl, 'H'
			cmp [edx], bl
			je ContinueKill2
			mov bl, 'A'
			cmp [edx], bl
			je ContinueKill2
			mov edx, offset notInHold
			call WriteString
			ret
		ContinueKill2:
			mov ecx, RECORDLENGTH
			call ClearBuffer
			mov eax, offset availStatus
			call SetStatus
			mov edx, offset newline
			call WriteString
			mov bl, 0
			mov ecx, curNameLngth
			mov edx, offset entry
			mov [edx + ecx], bl
			call WriteString
			mov edx, offset mesgKILL
			call WriteString
			mov eax, systemClock
			call WriteInt
			mov edx, offset newline
			call WriteString
			mov edi, offset entry
			mov esi, offset blankline
			mov ecx, ENTRYLENGTH
			rep movsb
			ret

	; Reads from a memory address stored in edi
	; If an address of edi is an uppercase letter then it converts it to lowercase
	; Uses ecx as the length of the buffer in edi
	LowerCase:
		mov eax, ecx
		jmp ToLower
		LowerCaseLoop:
			cmp ecx, 0
			jle LowerReturn
			inc edi
			dec ecx
			jmp ToLower
		ToLower:
			mov bl, [edi]
			cmp bl, 41h
			jl LowerCaseLoop
			cmp bl, 5Ah
			jg LowerCaseLoop 
			add bl, 20h
			mov [edi], bl
			jmp LowerCaseLoop
		LowerReturn:
			mov ecx, eax
			sub edi, ecx
			ret
	
	; Requires the beginning of the job address to be stored in edi
	; Puts the starting address of the priority into edx
	GetPriority:
		mov edx, edi
		add edx, JOBLENGTH
		ret

	; Requires the beginning of the job address to be stored in edi
	GetRuntime:
		mov edx, edi
		add edx, JOBLENGTH
		add edx, PRIORITYLENGTH
		ret

	; Requires the beginning of the job address to be stored in edi
	GetStatus:
		mov edx, edi
		add edx, JOBLENGTH
		add edx, RUNTIMELENGTH
		add edx, STARTTIMELENGTH
		add edx, PRIORITYLENGTH
		ret

	; Requires the beginning of the job address to be stored in edi
	; Stores the integer value of eax into the priority of the current record
	SetPriority:
		mov ecx, PRIORITYLENGTH
		call ConvertToInt
		cmp edx, 7
		jg InvalidPriority
		cmp edx, 0
		jl InvalidPriority
		mov temp1, edi
		mov temp2, esi
		add edi, JOBLENGTH
		mov esi, eax
		rep movsb
		mov edi, temp1
		mov esi, temp2
		ret
		InvalidPriority:
			mov edx, offset notPriority
			call WriteString	
			ret

	; Requires the beginning of the job address to be stored in edi
	; Stores the integer value of eax into the priority of the current record
	SetRuntime:
		mov ecx, RUNTIMELENGTH
		call ConvertToInt
		cmp edx, 50
		jg InvalidRuntime
		cmp edx, 1
		jl InvalidRuntime
		mov temp1, edi
		mov temp2, esi
		add edi, JOBLENGTH
		add edi, PRIORITYLENGTH
		mov esi, eax
		rep movsb
		mov edi, temp1
		mov esi, temp2
		ret
		InvalidRuntime:
			mov edx, offset notRunTime
			call WriteString
			ret

	; Requires the beginning of the job address to be stored in edi
	; Stores the integer value of eax into the priority of the current record
	SetStarttime:
		mov ecx, STARTTIMELENGTH
		call ConvertToInt
		cmp edx, 50
		jg InvalidStarttime
		cmp edx, 1
		jl InvalidStarttime
		mov temp1, edi
		mov temp2, esi
		add edi, JOBLENGTH
		add edi, PRIORITYLENGTH
		add edi, RUNTIMELENGTH
		mov esi, eax
		rep movsb
		mov edi, temp1
		mov esi, temp2
		ret
		InvalidStarttime:
			; Print something
			ret

	; Requires the beginning of the job address to be stored in edi
	; Stores the value stored in eax into the priority of the current record
	SetStatus:
		mov temp1, edi
		mov temp2, ebx
		mov temp3, esi
		add edi, JOBLENGTH
		add edi, PRIORITYLENGTH
		add edi, RUNTIMELENGTH
		add edi, STARTTIMELENGTH
		mov bl, 'A'
		cmp [eax], bl
		je ChangeStatus
		mov bl, 'H'
		cmp [eax], bl
		je ChangeStatus
		mov bl, 'R'
		cmp [eax], bl
		je ChangeStatus
		jmp InvalidStatus
		ChangeStatus:
			mov ecx, STATUSLENGTH
			mov esi, eax
			rep movsb
			jmp ReturnStatus
		InvalidStatus:
			mov edx, offset notStatus
			call WriteString
	ReturnStatus:
		mov edi, temp1
		mov ebx, temp2
		mov esi, temp3
		ret

	; Requires a pointer to some string to be stored in eax and the max size stored in ecx
	; Stores the integer in edx
	ConvertToInt:
	    mov temp1, esi
		mov temp2, ecx
		mov temp3, eax
		mov temp4, ebx
		mov esi, 0
		mov edx, 0
		mov ebx, 0
		mov ecx, 0
		mov power, 0
		NumOfCharLoop:
			add eax, ecx
			mov bl, [eax]
			mov eax, temp3
			cmp bl, 39h
			jg ConvertPrep
			cmp bl, 30h
			jl ConvertPrep
			inc ecx
			cmp ecx, temp2
			je ConvertPrep
			jmp NumOfCharLoop
		ConvertPrep:
			add eax, ecx
			dec eax
		IntLoop:
			cmp ecx, 0
			jle ReturnInt
			jmp Convert
		ReturnInt:
			mov esi, temp1
			mov ecx, temp2
			mov eax, temp3
			mov ebx, temp4
			ret
		Convert:
			mov ebx, 0
			dec ecx
			inc power
			mov bl, [eax]
			dec eax
			sub bl, 30h
			call PowerTen
			add dx, bx
			jmp IntLoop

	; Multiplies ebx by 10 esi times
	PowerTen:
		mov esi, power
		cmp power, 1
		jg PowerTenLoop
		ret
		PowerTenLoop:
			dec esi
			imul bx, 10
			cmp esi, 1
			jg PowerTenLoop
			ret

	; Converts an integer stored in edx into a character string that gets stored in a buffer whose start address is in eax
	; Make sure the buffer has enough space to store the integer!
	; Can't convert negative numbers!
	ConvertToString:
		mov temp1, eax
		mov temp2, edx
		mov temp3, edx
		mov edi, eax
		mov power, 10
		mov digits, 0
		GetNumOfDigits:
			; Check if there is another digit
			mov edx, 0
			mov eax, temp3
			mov ebx, power
			div ebx
			sub temp3, edx
			cmp temp3, 0
			jle ConvertDigit
			inc digits
			mov eax, power
			mov ebx, 10
			mul ebx
			mov power, eax
			jmp GetNumOfDigits
		ConvertDigit:
			mov edx, 0
			mov eax, power
			mov ebx, 10
			div ebx
			mov power, eax
			mov edx, 0
			mov eax, temp2
			mov ebx, power
			div ebx
			mov temp2, edx
			mov edi, temp1
			add al, 30h
			mov [edi], al
			inc temp1
			dec digits
			cmp digits, 0
			jge ConvertDigit
			ret

	; Compares each job name stored in records with the character buffer in edi
	; If it finds an equal job name, then it sets edx equal to the starting address of the job
	; If it doesn't find an equal job name, then it sets edx equal to -1
	FindJob:
		mov edx, esi
		mov esi, offset records
		mov ebx, 0
		FindJobLoop:
			mov eax, edi
			cmp ebx, TOTALRECORDSLENGTH
			jge NoJobFound
			mov ecx, JOBLENGTH
			cld
			repe cmpsb
			mov edi, eax
			je FoundJob
			add ebx, RECORDLENGTH
			mov esi, offset records
			add esi, ebx
			jmp FindJobLoop
		FoundJob:
			mov esi, offset records
			add esi, ebx
			xchg esi, edx
			ret
		NoJobFound:
			mov esi, -1
			xchg esi, edx
			ret

	; Reads from a memory address stored in esi and copies into a buffer in edi, and puts the number of chars copied into ecx
	GetString:
		mov ecx, 0
		GetStringLoop:
			mov bl, [esi]
			cmp bl, 0
			je CopyDone
			cmp bl, ' '
			je CopyDone
			mov bl, [esi]
			mov [edi + ecx], bl
			inc esi
			inc ecx
			dec maxChars
			cmp maxChars, 0
			je CopyDone
			jmp GetStringLoop
		CopyDone:
			mov maxChars, 0
			ret

	; Reads from a memory address stored in esi and sets esi equal to the address of the first non space character
	; Each element in the buffer must be only 1 byte
	SkipSpace:
		mov temp1, ebx
		SkipLoop:
			mov bl, [esi]
			cmp bl, 0
			je SkipDone
			cmp bl, ' '
			je Skip
			cmp bl, 09h
			je Skip
		SkipDone:
			mov ebx, temp1
			ret
		Skip:
			inc esi
			jmp SkipLoop

	; Reads a buffer address from eax and the length of the buffer in ecx
	; Sets every element in the buffer to ' '
	ClearBuffer:
		mov temp1, ecx
		mov temp2, ebx
		ClearBuffLoop:
			cmp ecx, 0
			jg ClearChar
			mov ecx, temp1
			mov ebx, temp2
			ret
		ClearChar:
			mov bl, ' '
			mov [eax], bl
			inc eax
			dec ecx
			mov bl, [eax]
			cmp bl, 0
			jne ClearBuffLoop
			mov ecx, temp1
			mov ebx, temp2
			ret

	; Ends the program
	QuitCommand:
		exit
		Main endp
end Main