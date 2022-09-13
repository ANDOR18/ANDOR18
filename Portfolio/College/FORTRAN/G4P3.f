c PROGRAM 3 - MATRIX ADD
c Group 4 - Kevin Andor, Nathaniel DeHart, Daniel Hentosz
	  PROGRAM MAIN

	  IMPLICIT none
	  INTEGER :: status, st
	  LOGICAL :: exists
	  LOGICAL :: files_open = .FALSE.
	  LOGICAL :: quit
	  INTEGER :: selection
	  CHARACTER*20 :: file_name
	  INTEGER :: mat_count
	  INTEGER :: row_count
	  INTEGER :: col_count
	  REAL, DIMENSION(10, 10) :: sum_mat = 0
	  REAL, DIMENSION(10, 10) :: cur_mat = 0
	  INTEGER :: r, c, m
	  
	  
1	  FORMAT('', 3A)
2	  FORMAT('', '---------------------------------------')
3	  FORMAT(F10.1)
4	  FORMAT('', A,I2,A)

	  quit = .FALSE.
	  
c Prompts the user to enter an input file, then checks to see if the file exists
c If it doesn't, alert the user and prompt to enter another file name or quit
	  PRINT *
	  WRITE(*,2)
	  
	  WRITE(*,1)'Please enter the input file: '
	  PRINT *
	  READ(*,'(A)')file_name
	  INQUIRE(FILE=file_name, EXIST=exists)
	  DO WHILE((.NOT. exists) .AND. (.NOT. quit))
	  	WRITE(*,2)
		WRITE(*,1)"Please enter a valid name or enter 'QUIT' to quit: "
		PRINT *
		READ(*, '(A)')file_name
		IF(file_name .EQ. 'QUIT') THEN
			quit = .TRUE.
		ELSE
			INQUIRE(FILE=file_name, EXIST=exists)
		ENDIF
	  END DO

	  
c IF the user chose not to quit, proceed with the program
	  If(.NOT. quit) THEN
	  
c When the in-file exists, open it
	  OPEN(UNIT=1, FILE=file_name, STATUS='OLD', IOSTAT=status)
	  
c If there is no issue opening the in-file, prompt for the out-file
	  IF(status .EQ. 0) THEN
	  	WRITE(*,2)
		WRITE(*,1)'Please enter the output file: '
		PRINT *
		READ(*,'(A)')file_name
		INQUIRE(FILE=file_name, EXIST=exists)
		
c If the out-file already exists
c Prompt the user to either re-enter the name, overwrite the file, or quit
		IF(exists) THEN
			WRITE(*,2)
			WRITE(*,1)'The file already exists.'
			DO WHILE(exists .AND. (.NOT. quit))
			WRITE(*,1)'Please make a selection (1-3): '
			WRITE(*,1)'1. Overwrite "', TRIM(file_name),'"'
			WRITE(*,1)'2. Re-enter file name'
			WRITE(*,1)'3. Quit'
			PRINT *
			READ(*,*)selection
			
			SELECT CASE (selection)
			
			CASE(1)
			OPEN(UNIT=2, FILE=file_name, STATUS='OLD', IOSTAT=status)
			IF(status .EQ. 0) THEN
				files_open = .TRUE.
			ELSE
				WRITE(*,2)
				WRITE(*,1)'Error opening output file "', TRIM(file_name),'".'
			ENDIF
			exists = .FALSE.
			
			
			CASE(2)
			WRITE(*,2)
			WRITE(*,1)'Re-enter output file name:'
			PRINT *
			READ(*,'(A)')file_name
			INQUIRE(FILE=file_name, EXIST=exists)
			IF(.NOT. exists) THEN
			  OPEN(UNIT=2, FILE=file_name, STATUS='NEW', IOSTAT=status)
			  IF(status .EQ. 0) THEN
				files_open = .TRUE.
			  ELSE
			  WRITE(*,2)
		  WRITE(*,1)'Error opening output file "', TRIM(file_name),'".'
			  ENDIF
			ELSE
				WRITE(*,2)
				WRITE(*,1)'The file already exists.'
			ENDIF
			
			CASE(3)
			quit = .TRUE.
			
			CASE DEFAULT
			WRITE(*,2)
			WRITE(*,1) 'Invalid Selection.'
			
			END SELECT
			END DO
		
		ELSE
			OPEN(UNIT=2, FILE=file_name, STATUS='NEW', IOSTAT=status)
			IF(status .EQ. 0) THEN
			 files_open = .TRUE.
			ELSE
			WRITE(*,2)
		 WRITE(*,1)'Error opening output file "', TRIM(file_name), '".'
			ENDIF
		ENDIF

c If there is an issue opening the in-file, alert the user
	  ELSE
	  	WRITE(*,2)
		WRITE(*,1)'Error opening input file "', TRIM(file_name),'".'
	  ENDIF
	  
c If the out-file was unable to be opened, close the open in-file
	  IF(.NOT. files_open) THEN
		CLOSE(1)
	  ENDIF
	  
c If both files were able to be opened
c Read the number, size, and contents of the matricies, and calculate the sum
c Write the results to the out-file (including errors)
	  IF(files_open) THEN
		READ(1,'(I2)', IOSTAT=status) mat_count
		IF(status .NE. 0) THEN
			WRITE(*, 2)
			WRITE(*, 1)'Operation failed. EOF Reached.'
			WRITE(2, 1)'Operation failed. EOF Reached.'
		
		ELSE IF(mat_count > 10) THEN
			WRITE(*,2)
			WRITE(*,1)'Operation failed. Over 10 matricies specified.'
			WRITE(2,1)'Operation failed. Over 10 matricies specified.'
		
		ELSE
			READ(1, '(I2, I2)', IOSTAT=status) row_count, col_count
			
			IF(status .NE. 0) THEN
				WRITE(*, 2)
				WRITE(*, 1)'Operation failed. EOF Reached.'
				WRITE(2, 1)'Operation failed. EOF Reached.'
		
			ELSE IF((row_count .GT. 10) .OR. (col_count .GT. 10)) THEN
				WRITE(*,2)
				WRITE(*,1)'Operation failed. Matrix larger than 10x10.'
				WRITE(2,1)'Operation failed. Matrix larger than 10x10.'
				
			ELSE
				DO m=1, mat_count
		 READ(1,*,IOSTAT=st)((cur_mat(r,c),c=1,col_count),r=1,row_count)
				  	IF (st .EQ. 0) THEN
						WRITE(2,4)'MATRIX ', m
						DO r=1, row_count
							DO c=1, col_count
							 sum_mat(r,c) = sum_mat(r,c) + cur_mat(r,c)
							END DO
						WRITE(2,*) (cur_mat(r,c), c=1, col_count)
						END DO
						WRITE(2,*)
					ENDIF
				END DO
		
				IF(st .EQ. 0) THEN
					WRITE(2,4)'SUM OF ALL', mat_count, ' MATRIX'
					DO r=1, row_count
						WRITE(2,*) (sum_mat(r,c),c=1, col_count)
					END DO
		
					WRITE(*,2)
					WRITE(*,1)'Operation successfully completed.'
					
				ELSE
					WRITE(*, 2)
					WRITE(*, 1)'Operation failed. EOF Reached.'
					WRITE(2, 1)'Operation failed. EOF Reached.'
					
				ENDIF
			ENDIF
		ENDIF
		
		CLOSE(1)
		CLOSE(2)

	  ENDIF

c This end if is for the IF(.NOT. quit) statement
	  ENDIF
	  
c If the user quit, print a message
	  IF(quit) THEN
		WRITE(*,2)
		WRITE(*,1)'You have quit the program.'
	  ENDIF
	  
	  END PROGRAM MAIN
		