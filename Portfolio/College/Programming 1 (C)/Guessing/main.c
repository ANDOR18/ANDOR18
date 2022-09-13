#include <stdio.h>
#include <stdlib.h>

/* Kevin Andor Scutaru */

int main(void) {
	int loop; //decision to loop
	int lower = 1; // lowest number
    int upper = 5; // Greatest number 
    int guess, number; // guess will be the value the user "guesses"
    // number will be the number produced below
 
 
	Loop: //point where the loop starts
    srand(time(0)); // seed the random number generator
    number = (rand() % (upper - lower + 1)) + lower; // generate the number


	printf("Guess a number between 1 and 5:\n"); //Prompts the user for a number
	scanf("%d", &guess); //Takes the input
	
	if (guess == number){ //If the guess matches the number, print winner prompt
		printf("Congratulations, you win!\n");
	}
	
	else{ //else, print loser prompt
		printf("Sorry, you lose.\n");
	}
	
	printf("Press 1 to play again or any other key to quit.\n"); //Asks the user if they wish to play again
	scanf("%d", &loop); //Takes the input
	if (loop == 1){ //If user decides to play again, loop the program. Otherwise, it ends.
		goto Loop;
	}
	
	return 0;
}
