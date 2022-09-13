!GROUP 4 || FORTRAN || The Matrix Calculator Program
!Dehart, Nathaniel || deh5850@calu.edu
!Scutaru, Kevin || and3256@calu.edu
!Hentosz, Daniel || hen3883@calu.edu
      module saystuff
	  implicit none
      save
	  character(len=50)::msg1='Enter 1 for addition:'
	  character(len=50)::msg2='Enter 2 for subtraction:'
	  character(len=50)::msg3='Enter 3 for multiplication:'
	  character(len=50)::msg4='Enter 4 to transpose:'
	  character(len=50)::msg5='Enter 5 for termination:'
	  character(len=12), parameter::matFormat = '(10(A3, X))'
	  character(len=7), parameter::intElement = '(i3, X)'
	  integer::r1,c1,r2,c2,pick1
	  integer, dimension(10,10)::m1=0,m2=0,outMat=0
	  contains
	  subroutine start()
	    write(*,'(/a/a/a/a/a//)')msg1,msg2,msg3,msg4,msg5
	    read(*,*)pick1
	  end subroutine start
	  
	  subroutine matrixRead()
	  	implicit none
	    integer::i,j
	    if (pick1 .LT. 5) then
	      print *,'Enter matrix 1''s number of rows:'
		  read(*,*)r1
		  print *,'Enter matrix 1''s number of columns:'
		  read(*,*)c1
		  
		  print *,'Enter the elements of matrix 1 (one row at a time):'
	      do i=1,r1
		    read(*,*) (m1(i,j), j = 1, c1)
	      end do
	      
		  if (pick1 .LT. 4) then
	        print *,'Enter matrix 2''s number of rows:'
		    read(*,*)r2
		    print *,'Enter matrix 2''s number of columns:'
		    read(*,*)c2
		    
		    print *,'Enter the elements of matrix 2 (one row at a time):'
	        do i=1,r2
		      read(*,*) (m2(i,j), j = 1, c2)
	        end do
		  end if
	    end if
	  end subroutine matrixRead
	  
	  subroutine printMatrix(mat, rows, cols)
	    integer, intent(in) :: mat(10, 10), rows, cols
	    integer::i, j
	    character(len=4), dimension(cols)::charMat
	    do i = 1, rows
	      do j = 1, cols
	        write(charMat(j), intElement) mat(i,j)
	      end do
	      print matFormat, charMat
	    end do
	  end subroutine
	  
	  end module saystuff
	  
	  module matrixMath
	  contains
      ! Adds the matrices, m1 and m2, together
      ! Precondition: m1 and m2 must be the same dimensions
      ! Output: outMat
	  subroutine addMatrices(m1, m2, outMat, rows, cols)
	  	implicit none
	    integer, intent(inout) :: outMat(10, 10)
	    integer, intent(in) :: m1(10, 10), m2(10, 10), rows, cols
	    integer::i, j
	    do i = 1, rows
	      do j = 1, cols
	        outMat(i, j) = m1(i, j) + m2(i, j)
	      end do
	    end do
	  end subroutine addMatrices
	  
	  ! Subtracts the matrix m2 from the matrix m1
	  ! Precondition: m1 and m2 must be the same dimensions
	  ! Output: outMat
	  subroutine subMatrices(m1, m2, outMat, rows, cols)
	    implicit none
	    integer, intent(inout) :: outMat(10, 10)
	    integer, intent(in) :: m1(10, 10), m2(10, 10), rows, cols
	    integer i, j
	    do i = 1, rows
	      do j = 1, cols
	        outMat(i, j) = m1(i, j) - m2(i, j)
	      end do
	    end do
	  end subroutine subMatrices
	  
	  ! Multiplies matrices 1 and 2, m1 and m2
	  ! Precondition: cols1 must be equal to rows2
	  ! Output: outMat
	  subroutine dotMatrices(m1, m2, outMat, rows1, commonDim, cols2)
	    implicit none
		integer, intent(out) :: outMat(10, 10)
	    integer, intent(in) :: m1(10, 10), m2(10, 10)
        integer, intent(in) :: rows1, commonDim, cols2
	    integer::i, j, k
	    do i = 1, rows1
	      do j = 1, cols2
	        do k = 1, commonDim
	          outMat(i, j) = outMat(i, j) + m1(i, k) * m2(k, j)
	        end do
	      end do
	    end do
	  end subroutine dotMatrices
	  
	  
	  subroutine transMatrix(m1, outMat, r1, c1)
		implicit none
		integer, intent(out) :: outMat(10, 10)
		integer, intent(in) :: m1(10, 10)
		integer, intent(in) :: r1, c1
		integer :: rows, cols
		integer r, c
		do r = 1, cols
			do c = 1, rows
				outMat(r,c) = m1(c,r)
			end do
		end do
	  end subroutine transMatrix
		
	  end module matrixMath
	  
	  program calc
	  use saystuff
	  use matrixMath
	  logical::processing = .true.
	  
	  do while (processing)
	    call start
	    call matrixRead
	    
	    select case(pick1)
	    case(1)!Addition
		  if((r1 .EQ. r2).AND.(c1 .EQ. c2)) then
			call addMatrices(m1, m2, outMat, r1, c1)
			print *, 'Matrix 1 is:'
			call printMatrix(m1, r1, c1)
			print *, 'Matrix 2 is:'
			call printMatrix(m2, r2, c2)
			print *, 'The result of Matrix 1 + Matrix 2 is:'
			call printMatrix(outMat, r1, c1)
		  else
			write(*,*) 'Error, size of matrices not the same'
		  endif
		
	    case(2)!Subtraction
		  if((r1 .EQ. r2).AND.(c1 .EQ. c2)) then
		  	call subMatrices(m1, m2, outMat, r1, c1)
		  	print *, 'Matrix 1 is:'
			call printMatrix(m1, r1, c1)
			print *, 'Matrix 2 is:'
			call printMatrix(m2, r2, c2)
			print *, 'The result of Matrix 1 - Matrix 2 is:'
			call printMatrix(outMat, r1, c1)
		  else
		  	write(*,*) 'Error, size of matrices not the same'
		  endif
		
	    case(3)!Multiplication
		  if(c1 .EQ. r2) then
	        call dotMatrices(m1, m2, outMat, r1, c1, c2)
	        print *, 'Matrix 1 is:'
			call printMatrix(m1, r1, c1)
			print *, 'Matrix 2 is:'
			call printMatrix(m2, r2, c2)
			print *, 'The result of Matrix 1 * Matrix 2 is:'
			call printMatrix(outMat, r1, c2)
		  else
		    write(*,*)'Size of mat1 columns and mat2 rows not the same'
		  endif
		
	    case(4)!Transpose
		  call transMatrix(m1, outMat, r1, c1)
		  print *, 'The Matrix is:'
	      call printMatrix(m1, r1, c1)
	      print *, 'The Transposed Matrix is:'
	      call printMatrix(outMat, c1, r1)
	      
		case(5)!Quit
	      processing = .false.
	      
	    case default
		  print*,'Only enter numbers 1-5'
		  
	    end select
	    m1 = 0
	    m2 = 0
	    outMat = 0
	  end do
	  
	  stop
	  end program calc