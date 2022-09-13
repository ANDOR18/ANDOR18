! PROGRAM 7: Linked Lists
! GROUP 4: Nathaniel DeHart, Kevin Andor, Daniel Hentosz
      
! START OF MODULE, FILE_HANDLER
      module fileHandler
        implicit none
        contains
        
      ! Returns: .true. if a valid input filename was entered, else 
      !.false.
      ! fileHandle: This will be set equal to the input file's handle 
      ! if a valid one is entered
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
              open(file = filename, newunit = fileHandle, status = 'old')
            else
              print 3
            end if
          end if
        end do
        getValidInFile = quit
      end function getValidInFile
      
      ! Returns: .true. if a valid output filename was entered, else 
      ! .false.
      ! filename: This will be set equal to the output file's name if a
      ! valid one is entered
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
          open(file = filename, newunit = fileHandle, status = 'replace')
        end if
        getValidOutFile = quit
      end function getValidOutFile
      end module fileHandler
! END OF MODULE, FILE_HANDLER

! START OF MODULE, LINKED_LIST_HELPER
      module linkedListHelper
        type :: node
          character :: name * 20
          integer :: value
          type(node), pointer :: next, prev
        end type node
		
		type(node), pointer :: head, tail, current
        contains
        
        logical function doesContain(name)
        	character, intent(in) :: name * 20
        	integer :: i
        	doesContain = .false.
        	current => head
        	do while(associated(current))
        		if (current%name == name) then
        			doesContain = .true.
        		end if
        		current => current%next
        	end do
        	return
        end function doesContain
        
        ! Summary: Moves current node pointer forward or backward from the current 
        ! node, current. The output file handle is also passed in.
        subroutine moveCurrent(outFD)
			implicit none
			integer :: i, cur_count, status
			integer, intent(in) :: outFD
			character :: cur_name * 20
			logical :: negative
			type(node), pointer :: temp
			
			write(*,*)
			
			current => head
			cur_count = current%value
			cur_name = current%name
			do while(associated(current%next) .or. associated(current%prev))
				write(*,'("Starting at ", A, " with a count of ")', advance='no') trim(cur_name)
				write(*,'(I3, ".")') cur_count
				write(outFD,'("Starting at ", A, " with a count of ")', advance='no') trim(cur_name)
				write(outFD,'(I3, ".")') cur_count
				if (cur_count < 0) then
					cur_count = cur_count*(-1)
					negative = .TRUE.
				end if
				
				do i = 1, cur_count
					if (negative) then
						if (associated(current, head)) then
							current => tail
						else
							current => current%prev
						end if
					else if (.not. negative) then
						if (associated(current, tail))then
							current => head
						else
							current => current%next
						end if
					end if
				end do
				

				if (associated(current%prev)) then
					current%prev%next => current%next
				else
					head => current%next
				end if
							
				if (associated(current%next)) then
					current%next%prev => current%prev
				else
					tail => current%prev
				end if
				

				if (negative) then
					temp => current%next
					if(.not. associated(temp)) then
						temp => head
					end if
					negative = .FALSE.
				else
					temp => current%prev
					if (.not. associated(temp)) then
						temp => tail
					end if
				end if
				
				cur_count = current%value
				cur_name = current%name
				deallocate(current, stat = status)
				if(status /= 0) then
					write(*,*) 'dealloc failed'
				else
					write(*,'(A, " has been removed. They had a count of ")', advance='no') trim(cur_name)
					write(*,'(I3, ".", /)') cur_count
					write(outFD, '(A, " has been removed. They had a count of ")', advance='no') trim(cur_name)
					write(outFD,'(I3, ".", /)') cur_count
				end if
				
				current => temp
				cur_name = current%name
			end do
			
			cur_count = current%value
			write(*,'("The remaining person is ", A, ". They have a count of ")', advance='no') trim(cur_name)
			write(*,'(I3, ".")') cur_count
			write(outFD,'("The remaining person is ", A, ". They have a count of ")', advance='no') trim(cur_name)
			write(outFD,'(I3, ".")') cur_count
			deallocate(current, stat = status)
			if(status /= 0) then
				write(*,*) 'dealloc failed'
			end if
			
		end subroutine moveCurrent
            
        ! Summary: Adds a new tail node to the linked list
        subroutine appendNode(newNodeName, newNodeVal)
        	implicit none
          	character, intent(in) :: newNodeName * 20
          	integer, intent(in) :: newNodeVal
			integer :: status
          	allocate(current, stat = status)
			if(status .eq. 0) then
				nullify(current%next)
				nullify(current%prev)
				current%name = newNodeName
				current%value = newNodeVal
			else
				write(*,*) 'No memory can be allocated'
			end if
			
			if(associated(head)) then
				tail%next => current
				current%prev => tail
				tail => current
			else
				head => current
				tail => current
			endif
		end subroutine appendNode
        
		!Prints the linked list (for debugging purposes)
        subroutine printNodes()
			implicit none
			current => head
			do while(associated(current))
				write(*,*) current%name
				write(*,*) current%value
				current => current%next
			end do
		end subroutine printNodes
        
      end module linkedListHelper
! END OF MODULE, LINKED_LIST_HELPER
      
! START OF PROGRAM, LINKED_PEOPLE
      program linkedPeople
  	    use fileHandler
      	use linkedListHelper
        implicit none
        
        integer, parameter :: MAX_LIST_LEN = 25
        character :: curName * 20
		character :: bakEntry * 20
        integer :: inFD, outFD, curVal, status, totalRec
        logical :: quit = .false.
        status = 0
        totalRec = 0
        ! Just to get an extra new line
        print *
        quit = getValidInFile(inFD)
        if (.not. quit) then
        	print *
        	quit = getValidOutFile(outFD)
        	if (quit) then
            	close(inFD)
          	end if
        end if
        if (.not. quit) then
        	
        	! Reads in all the data to the linked list
        	do while(status == 0 .and. totalRec .le. MAX_LIST_LEN)
        		read(inFD, *, iostat = status) curName
        		if (status == 0) then
					if(verify(curName,"-1234567890 ") /= 0) then
						read(inFD, *, iostat = status) curVal
						if (status == 0) then
							if(curVal == 0) then
								print '("Warning: Ignoring entry: 0 count for ", A)', curName
							else
								totalRec = totalRec + 1
								if (totalRec .le. MAX_LIST_LEN) then
									call appendNode(curName, curVal)
								else
									print '("Warning: More than ", I3, " people were entered! Only using first ", I3)',& 
									&MAX_LIST_LEN, MAX_LIST_LEN
								end if
							end if
						else
							print '("Warning: Ignoring entry: Missing count for ", A)', curName
							backspace(inFD)
							status = 0
						end if
					else
						print '("Warning: Ignoring entry: Missing name with a count of ",A)', curName
					end if
				end if
        	end do
            
        	if (totalRec .gt. 0) then
        		!call printNodes()
				call moveCurrent(outFD)
			else
				print '("Error: No people were read from the input file!")'
			end if
        	close(inFD)
        	close(outFD)
        end if
        stop
      end program linkedPeople
! END OF PROGRAM, LINKED_PEOPLE