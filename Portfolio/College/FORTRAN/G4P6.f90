!CSC475 Program 6 - Complex Solver
!Group 4 - Kevin Andor, Nathaniel, DeHart, Daniel Hentosz
!--------------------------------------------------------

	  module solver
	  implicit none
	  contains
		!Reads the data in; outputs the 2d array of equation coefficients, constant vector, and equation amount
		subroutine read_eqtns(eqtns, eqtn_cons, eqtn_amt)
			integer, parameter :: DBL = selected_real_kind(p=13)
			complex(kind=DBL), dimension(10,10), intent(out) :: eqtns
			complex(kind=DBL), dimension(10), intent(out) :: eqtn_cons
			real(kind=DBL) :: rel, img
			integer :: i, j
			integer, intent(out) :: eqtn_amt
			logical :: valid_num, redo
			character(len=10) :: selection
			
		2	format("************************************")
		3	format(A)
		4	format(A, I2, A, I2, A)
		5	format(2G14.4)
		6	format(2(A, G14.4), A, I2)
		7	format(A, I2, 2(A, G14.4) A)
		
			!Flag to restart if incorrect data is entered
			redo = .true.
			do while (redo)
				!Flag to restart if an invalid equation amount is specified
				valid_num = .false.
				do while (.not. valid_num)
					write(*,2)
					write(*,3) "Enter the amount of equations (max 10):"
					read(*,*) eqtn_amt
					if(eqtn_amt <= 10 .and. eqtn_amt > 0) then 
						valid_num = .true.
					else if (eqtn_amt > 10) then
						write(*,2)
						write(*,3) "More than 10 equations specified."
					else
						write(*,2)
						write(*,3) "No equations specified."
					end if
				end do
			
				!For each equation and constant in the system, read the complex coefficients
				do i = 1, eqtn_amt
					write(*,2)
					do j = 1, eqtn_amt
						write(*,4) "Enter the complex number for equation(",i,",",j,")"
						write(*,3) "(Separate real and imaginary part with a space):"
						read(*,*) rel, img
						eqtns(i,j) = cmplx(rel,img,DBL)
						print *
					end do
					
					write(*,4) "Enter the complex number for constant(",i,")"
					write(*,3)"(Separate real and imaginary part with a space):"
					read(*,*) rel, img
					eqtn_cons(i) = cmplx(rel,img,DBL)
				end do
				
				!Print the entered data and prompt the user to validate their entry. Proceed if valid, restart data entry otherwise. 
				write(*,2)
				write(*,4) "Number of equations: ", eqtn_amt
				print *
				
				do i=1, eqtn_amt
					do j=1, eqtn_amt
						write(*,6,advance='no') "(",real(eqtns(i,j))," + i",aimag(eqtns(i,j)),")X",j
						if (j /= eqtn_amt) then
							write(*,3,advance='no') " + "
						else
							write(*,*)
						end if
					end do
				end do
				print *
				
				do i=1, eqtn_amt
					write(*,7) "Constant(",i,") = (", real(eqtn_cons(i))," + i",aimag(eqtn_cons(i)),")"
				end do
				print *
				
				write(*,3) "Is the data above correct? (Y/else):"
				read(*,*) selection

				if (selection == 'Y' .or. selection == 'y') then
					redo = .false.
				end if
			end do
			write(*,2)
			end subroutine read_eqtns
		
		!Performs Gauss-Jordan elimination on the system of equations entered, modified from the textbook
		!Takes the equations, constands, max array size, and the amount of data entered and outputs the solution vector and pivot error flag
		subroutine dsimul (a, b, soln, ndim, n, error)
			integer, parameter :: DBL = selected_real_kind(p=13)
			real(kind=DBL), parameter :: epsi = 1.0E-12
			integer, intent(in) :: ndim
			complex(kind=DBL), intent(in), dimension(ndim,ndim) :: a !equations
			complex(kind=DBL), intent(in), dimension(ndim) :: b !constants
			complex(kind=DBL), intent(out), dimension(ndim) :: soln !solutions
			
			integer, intent(in) :: n
			integer, intent(out) :: error
			
			complex(kind=DBL), dimension(n,n) :: a1
		
			complex(kind=DBL) :: factor
			integer :: irow
			integer :: ipeak
			integer :: jrow

			complex(kind=DBL) :: temp
			complex(kind=DBL), dimension(n) :: temp1
			
			a1 = a(1:n, 1:n)
			soln = b(1:n)
			
			!Main loop for the Gauss-Jordan elimination method, checks equations 1 to n
			mainloop: DO irow = 1, n
				ipeak = irow
				
				!Find the peak pivot for column irow  in rows irow to n
				max_pivot: DO jrow = irow+1, n
					if (abs(a1(jrow,irow)) > abs(a1(ipeak,irow))) then
						ipeak = jrow
					end if
				end do max_pivot
				
				!Check single equations and tick pivot error if necessary
				singular: if(abs(a1(ipeak,irow)) < epsi) then	
					error = 1
					return
				end if singular
				
				!If the peak is not equal to the current row, swap equations irow and ipeak
				swap_eqn: if(ipeak/=irow) then
					temp1 = a1(ipeak, 1:n)
					a1(ipeak, 1:n) = a1(irow,1:n)
					a1(irow,1:n) = temp1
					temp = soln(ipeak)
					soln(ipeak) = soln(irow)
					soln(irow) = temp
				end if swap_eqn
				
				!Factor irow and add it to jrow
				eliminate: do jrow = 1, n
					if(jrow/=irow) then
						factor = -a1(jrow,irow)/a1(irow,irow)
						a1(jrow,1:n) = a1(irow,1:n)*factor + a1(jrow,1:n)
						soln(jrow) = soln(irow)*factor + soln(jrow)
					end if
				end do eliminate
			end do mainloop
			
			!Off-diagonal terms are now 0
			!Divide each equation by the coefficient of it's own on-diagonal term
			divide: do irow = 1, n
				soln(irow) = soln(irow)/a1(irow,irow)
			end do divide
			
			!Tick error flag to 0
			error = 0
		end subroutine dsimul
	  end module solver
		
	  program main
		use solver
		integer, parameter :: DBL = selected_real_kind(p=13)
		complex(kind=DBL), dimension(10,10) :: eqtns = (0.,0.)
		complex(kind=DBL), dimension(10) :: eqtn_cons = (0.,0.)
		complex(kind=DBL), dimension(10) :: eqtn_sols = (0., 0.)
		integer :: eqtn_amt, error_flag, i
		character(len=10) :: selection
		integer :: EQTN_MAX = 10
	7	format(A, I2, 2(A, G14.4) A)
			
		!Call the reading subroutine, then the processing subroutine
		call read_eqtns(eqtns, eqtn_cons, eqtn_amt)	
		call dsimul(eqtns, eqtn_cons, eqtn_sols, EQTN_MAX, eqtn_amt, error_flag)
			
		!If zero pivot flag was ticked on, display the appropriate error message, else display the solutions
		if(error_flag /= 0) then
			write(*, 1)
	1		format(/, 'Zero pivot encountered.' &
			//, 'There is no unique solution to this system.')
		else
			do i = 1, eqtn_amt
				write(*,7) "X",i,": (", real(eqtn_sols(i)) ,"+ i", aimag(eqtn_sols(i)),")"
			end do
		end if
	  end program main