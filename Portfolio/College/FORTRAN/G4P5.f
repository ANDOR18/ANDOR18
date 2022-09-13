! PROGRAM 5: The Grapher
! GROUP 4: Nathaniel DeHart, Kevin Andor, Daniel Hentosz
      
! START OF MODULE, FILEHANDLER
      module fileHandler
        implicit none
        contains
      ! Returns: .true. if a valid input filename was entered, else .false.
      ! fileHandle: This will be set equal to the input file's handle if a valid one is entered
      function getValidInFile(fileHandle)
        integer, intent(out) :: fileHandle
        logical :: quit, valid, getValidInFile
        character :: filename * 255
 1      format('', 'Please enter the in file or type "quit" to quit:')
 3      format('', 'A file with that name does not exist!')
        quit = .false.
        valid = .false.
        do while ((valid .or. quit) .eqv. .false.)
          print 1
          read(*, *) filename
          if (filename .eq. 'QUIT' .or. filename .eq. 'quit') then
            quit = .true.
            filename = ""
          else
            inquire(file = filename, exist = valid)
            if (valid) then
              open(file = filename,newunit=fileHandle,status = 'old')
            else
              print 3
            end if
          end if
        end do
        getValidInFile = quit
      end function getValidInFile
      
      ! Returns: .true. if a valid output filename was entered, else .false.
      ! filename: This will be set equal to the output file's name if a valid on is entered
      function getValidOutFile(fileHandle)
        logical :: quit, invalid, getValidOutFile
        integer, intent(out) :: fileHandle
        character :: filename * 255
        character :: tempString * 255
 1      format('', 'Please enter the out file or type "quit" to quit:')
 3      format('', 'An output file with that name already exists')
 5      format('','Type new file name,"O" to overwrite,"quit" to quit')
        invalid = .true.
        quit = .false.
        print 1
        read(*, *) filename
        do while (((.not. invalid) .or. quit) .eqv. .false.)
          if (filename .eq. 'quit' .or. filename .eq. 'quit') then
            quit = .true.
            filename = ""
          else
            inquire(file = filename, exist = invalid)
            if (invalid) then
                print 3
                print 5
                read(*, *) tempString
                if (tempString .eq. 'O' .or. tempString .eq. 'o') then
                  invalid = .false.
                else
                  filename = tempString
                end if
            else
              invalid = .false.
            end if
          end if 
        end do
        if (.not. invalid) then
          open(file = filename, newunit = fileHandle,
     +		status = 'replace')
        end if
        getValidOutFile = quit
      end function getValidOutFile
      end module fileHandler
! END OF MODULE, FILEHANDLER

! START OF MODULE, GRAPHPLOTTER
      module graphPlotter
      contains
      
      ! Reads x, y points in from a file 
      subroutine readPoints(inHandle, nPoints, xArray, yArray, status)
		integer, intent(in) :: inHandle
		integer, intent(inout) :: nPoints
		integer, intent(out) :: status
        real, dimension(nPoints), intent(out) :: xArray, yArray
 1      format('', 'Warning: Less points were read than expected')
		xArray = 0
		yArray = 0
		i = 0
		do while (i .lt. nPoints .and. status .eq. 0)
		    i = i + 1
			read(inHandle, *, iostat=status) xArray(i), yArray(i)
		end do
		if (nPoints .ne. i) then
		  nPoints = i
		  print 1
        end if
      end subroutine readPoints
      
      ! Sorts the points from smallest x-value to largest x-value
      ! xMin: Will be set to the smallest x-value
      ! xMax: Will be set to the largest x-value
      ! yMin: Will be set to the smallest y-value
      ! yMax: Will be set to the largest y-value
      subroutine sortPoints(nPoints, xArray, yArray, xMin, xMax, yMin,
     + yMax)
        integer, intent(in) :: nPoints
        real, intent(out) :: xMin, xMax, yMin, yMax
        real, dimension(nPoints), intent(out) :: xArray, yArray
		integer :: endc
		logical :: swap
		real :: temp
		
		!sort the data into descending order
		endc = nPoints - 1
		swap = .TRUE.
		do while(swap)
			swap = .FALSE.
			do i = 1, endc
				if(xArray(i) .GT. xArray(i+1)) then
					swap = .TRUE.
					temp = xArray(i)
					xArray(i) = xArray(i+1)
					xArray(i+1) = temp
					
					temp = yArray(i)
					yArray(i) = yArray(i+1)
					yArray(i+1) = temp
				end if
			end do
			endc = endc - 1
		end do
		
		do i = 1, nPoints
		! find the min and max x-value
		if(i .EQ. 1) then
			xMin = xArray(i)
			xMax = xMin
			yMin = yArray(i)
			yMax = yMin
		else
			if(xArray(i) .GT. xMax) then
				xMax = xArray(i)
			else if(xArray(i) .LT. xMin) then
				xMin = xArray(i)
			end if
			
			if(yArray(i) .GT. yMax) then
				yMax = yArray(i)
			else if(yArray(i) .LT. yMin) then
				yMin = yArray(i)
			end if
		end if
		end do
			
      end subroutine sortPoints
      
      function getRow(value, minValue, dx)
        integer :: getRow
        real, intent(in) :: value, minValue, dx
        real remainder
        getRow = (value - minValue) / dx
        remainder = mod(value - minValue, dx)
        if (remainder .ge. dx / 2) then
          getRow = getRow + 1
        end if
      end function getRow
      
      ! Writes data and the graph to the out file
      subroutine plotPoints(outHandle, nPoints, xArray, yArray, xMin,
     + xMax, yMin, yMax, minRows, maxRows)
        integer, intent(in) :: outHandle, nPoints, minRows, maxRows
        real, dimension(nPoints), intent(in) :: xArray, yArray
        integer, parameter :: MAX_COLS = 71, COL_OFFSET = 10
        character(len=MAX_COLS) :: curRow
		integer :: nLines, pointI = 1
		real :: DX, curDiff, yStep DY
 1		format('', A)
 2		format('', F10.4, "		",F10.4)
 3		format('', A, F10.4)
 4      format(' ', f10.6, f10.6, f10.6, f10.6, f10.6, f10.6, f10.6)
 5      format('', A, I3)
        ! Finds Y step
		yStep = (yMax-yMin)/6
		DY = yStep / 10
		
		!Finds the DX
		DX = xArray(2)-xArray(1)
		do i = 2, nPoints-1
			curDiff = xArray(i+1)-xArray(i)
			if(DX .EQ. 0) then
				DX = curDiff
			else if((curDiff .LT. DX) .AND. (curDiff .GT. 0)) then
				DX = curDiff
			end if
		end do
		
	    nLines = (xMax - xMin) / DX + 1
		
		!If x is less than 20 or greater than 200, set nLines to min/max
		!and recalculate DX
		if (nLines .LT. minRows) then
			nLines = minRows
			DX = (xMax-xMin)/(nLines - 1)
		else if (nLines .GT. maxRows) then
			nLines = maxRows
			DX = (xMax-xMin)/(nLines - 1)
		end if
		
		!Print the data to file and screen
		write(outHandle, 1) "SORTED DATA"
		
		do i = 1, nPoints
			write(outHandle, 2) xArray(i), yArray(i)
		end do
		
		write(outHandle, *)
		write(outHandle, 3) "XMIN  = ", xMin
		write(outHandle, 3) "XMAX  = ", xMax
		write(outHandle, 3) "DX    = ", DX
		write(outHandle, *)
		write(outHandle, 3)	"YMIN  = ", yMin
		write(outHandle, 3) "YMAX  = ", yMax
		write(outHandle, 3) "YSTEP = ", yStep
        write(outHandle, *)
		write(outHandle, 5) "Lines to Plot = ", nLines
		write(outHandle, *)
		write(outHandle, 4) (yMin + yStep * real(i), i = 0, 6)
		
		do i = 11, MAX_COLS
		  if (mod(i - 1, 10) .eq. 0) then
		    curRow(i:i) = '+'
		  else
		    curRow(i:i) = '-'
	      end if
		end do
	    if (getRow(xArray(pointI), xMin, DX) .eq. 0) then
          j = getRow(yArray(pointI), yMin, DY) + COL_OFFSET + 1
	      curRow(j:j) = 'O'
	      pointI = pointI + 1
	    end if
		write(outHandle, 1) curRow
	    
		! Prints the graph out row by row (offset by 1 because i = 2 corresponds to row 1)
		do i = 2, nLines + 1
		  curRow(1:MAX_COLS) = ' '
		  if (mod(i - 1, 5) .eq. 0) then
		    write(curRow, '(f10.6)') xMin + DX * real(i)
		    curRow(11:11) = '+'
		  else
		    curRow(11:11) = '|'
		  end if
		  if (pointI .le. nPoints) then
		    if (getRow(xArray(pointI), xMin, DX) .eq. i) then
		      print *, 'Putting point in row, ', i, ', column, ', 
     +        getRow(yArray(pointI), yMin, DY) + COL_OFFSET + 1
		      j = getRow(yArray(pointI), yMin, DY) + COL_OFFSET + 1
		      curRow(j:j) = 'O'
		      pointI = pointI + 1
		    end if
		  end if
	      write(outHandle, 1) curRow
		end do
		
      end subroutine plotPoints
      end module graphPlotter
! END OF MODULE, GRAPHPLOTTER
      
! START OF PROGRAM, GRAPHER
      program grapher
        use fileHandler
        use graphPlotter
        implicit none
        integer, parameter :: MIN_ROWS = 20, MAX_ROWS = 200
        real, dimension(100) :: xArray, yArray
        real :: xMin, xMax, yMin, yMax
        integer :: inFile, outFile, nPoints, status
        logical :: quit = .false.
 1      format('', 'ERROR: No points were entered')
 2      format('', 'ERROR: Too many points were entered')
        quit = getValidInFile(inFile)
        if (.not. quit) then
          print *
          quit = getValidOutFile(outFile)
          if (quit) then
            close(inFile)
          end if
        end if
        if (.not. quit) then
          ! Read a number for the points
          print *
		  read(inFile, '(I3)', iostat=status) nPoints
          if (nPoints .gt. 0) then
            if (nPoints .le. 100) then
              call readPoints(inFile, nPoints, xArray, yArray, status)
              call sortPoints(nPoints, xArray, yArray, xMin, xMax, yMin,
     + 		  yMax)
              call plotPoints(outFile, nPoints, xArray, yArray, xMin,
     +		  xMax, yMin, yMax, MIN_ROWS, MAX_ROWS)
            else
              print 2
            end if
          else
            print 1
          end if
          close(inFile)
          close(outFile)
        end if
        stop
      end program grapher
! END OF PROGRAM, GRAPHER