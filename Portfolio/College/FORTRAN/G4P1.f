
c CSC 306, Program 1, Group 4: Kevin Andor, Nathaniel DeHart, Daniel Hentosz

      PROGRAM MAIN

c Inits the variables that will be used with the program
      INTEGER count
      REAL grade, grade_sum, grade_avg
      CHARACTER*15 name
	  
c Inits the fomatting that will be used to display the data
1	  FORMAT('', /A, F6.1)
2	  FORMAT('----------------------------------------')
3	  FORMAT('', /A, I3A)
4	  FORMAT('', /AA)
5	  FORMAT(I3)

c Prompt the user for a name and the amount of grades to enter
c PRINT * is used throughout the program to create blank lines
      PRINT *
	  WRITE(*,2)
	  WRITE(*,4) 'Please enter your name:'
      READ(*,*) name
	  PRINT *
	  
      WRITE(*,4) 'Please specify how many grades you wish to enter:'
      READ(*,5) count
	  PRINT *
	  WRITE(*,2)
	  
c Checks to see if the count entered is a valid value above 0
	  IF(count .GT. 0) THEN
c Prompts for each grade n times and add that value to the sum
	  WRITE(*, 2)
	  DO i = 1, count
	   WRITE(*,3) 'Please enter grade ', i, ':'
	   READ(*,*) grade
	   PRINT *
	   grade_sum = grade + grade_sum
      END DO
	  WRITE(*, 2)
c Calculates the average using the sum and counter
      grade_avg = grade_sum/REAL(count)
	  
c Prints the name, sum, and average with formatting
	  WRITE(*, 2)
	  WRITE(*,4) 'Hello, ', name
	  WRITE(*,3) 'The number of grades entered is: ', count
	  WRITE(*,1) 'The sum of the grades entered is: ', grade_sum
      WRITE(*,1) 'The average of the grades is: ', grade_avg
	  PRINT *
	  WRITE(*, 2)
	  
c If the user entered a value less than or equal to 0
	  ELSE
c Alerts the user that no grades will be taken
	  	WRITE(*, 2)
		WRITE(*, 4) 'No grades will be entered, ', name
		PRINT *
		WRITE(*, 2)
	  END IF

      END PROGRAM MAIN