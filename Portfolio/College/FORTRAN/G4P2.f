c CSC 306, Program 2, Group 4: Kevin Andor, Nathaniel DeHart, Daniel Hentosz

      PROGRAM MAIN

c Inits the variables that will be used with the program
	  INTEGER count
      REAL grade, grade_sum, grade_avg
	  DIMENSION grade(10)
      CHARACTER*15 name
	  
c Inits the fomatting that will be used to display the data
1	  FORMAT('', /A, F6.1)
2	  FORMAT('----------------------------------------')
3	  FORMAT('', /A, I3A)
4	  FORMAT('', /AA)
5	  FORMAT(I3)
6	  FORMAT('', /A, I3A, F6.1)

c Prompt the user for a name 
      PRINT *
	  WRITE(*,2)
	  WRITE(*,4) 'Please enter your name:'
      READ(*,*) name
	  PRINT *

c Prompts for each grade n times and add that value to the sum
	  WRITE(*, 2)
	  i = 1
	  count = 10
	  DO WHILE (i .LE. count)
	   WRITE(*,3) 'Please enter grade ', i, ':'
	   READ(*,*) grade(i)
	   PRINT *
	   IF((grade(i) .GT. 100) .OR. (grade(i) .LT. 0)) THEN
		count = i-1
		i = 11
	   ELSE
		i = i+1
	   END IF
      END DO
	  WRITE(*, 2)
c Calculates the average using the sum and counter if grades were entered
	  WRITE(*, 2)
	  IF (count .NE. 0) THEN
		DO i = 1, count
			grade_sum = grade(i) + grade_sum
		END DO
		grade_avg = grade_sum/REAL(count)
	  
c Prints the name, sum, average, and grades entered with formatting if grades were entered
		WRITE(*,4) 'Hello, ', name
		WRITE(*,1) 'The sum of the grades entered is: ', grade_sum
		WRITE(*,1) 'The average of the grades is: ', grade_avg
		DO i = 1, count
		 WRITE(*, 6) 'Grade #', i, ': ', grade(i)
		END DO
c Otherwise, the program tells the user that no grades were entered, along with their name
	  ELSE
		WRITE(*,4) 'No grades were entered, ', name, '.'
	  END IF
	  PRINT *
	  WRITE(*, 2)

      END PROGRAM MAIN