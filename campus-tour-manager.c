// GMUTT Campus Tour Manager
// Author: Yousef Alhuraibi
// Description: A C program using linked lists to manage interactive campus tours with file I/O, ordered insertion, and CLI navigation.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 100
#define starting_kopeks 10
#define FINALSCORE 132

int roll_pass(int *banked_points, int *round_points, int is_player);
int horn_system();
int point_calculator(int *player_banked_points, int *computer_banked_points, int is_player);
int play_game(int *player_kopeks, int *computer_kopeks);

int main()
{
	int player_kopeks = starting_kopeks;
	int computer_kopeks = starting_kopeks;
	char choice;
	int seed;
	char buffer[size];

	printf("Welcome to The Game of Sarlagiin Evriig\n");

	printf("Please enter a random number seed:\n");
	fgets(buffer,size,stdin); 
	sscanf(buffer,"%d", &seed);
	srand(seed);

	while (player_kopeks > 0 && computer_kopeks > 0)
	{
		printf("\nWould you like to play? (Y/N):\n");
		char buffer[size];
		fgets(buffer, size, stdin);
		sscanf(buffer, "%c", &choice);

		if (choice == 'Y' || choice == 'y')
 		{
			

			int result = play_game(&player_kopeks, &computer_kopeks);
			if (result == 0)
			{
				break;
			}	
	

		}
		else
		{
			break;

		}


	}


	return 0;



}
int horn_system()
{
	
	return rand() % 100;

}
int point_calculator(int *player_banked_points,int *computer_banked_points, int is_player)
{
	int round_points = 0;
	int random_number;
	int *banked_points; 
	
	if (is_player == 1)
	{
		banked_points = player_banked_points;
	}
	else
	{
		banked_points = computer_banked_points;
	}

	
	while(1)
	{
		random_number = horn_system();
		if (random_number < 17)
		{
		printf("Rolled a number from 0-16, all points for the round are lost!\n");
		round_points = 0;
		break;

		}
		else if (random_number < 33)
		{
		printf("Rolled a number from 17-32, You gain all points gained from the round!\n");
		*banked_points += round_points;
		break;
	
		}
		else if (random_number < 56)
		{
		printf("Rolled a number from 33-55, You gain two points!\n");

		round_points += 2; 

		}
		else if (random_number < 69)
		{
		printf("Rolled a number from 56-68, You gain three points!\n");

                round_points += 3;
		


		}
		else if (random_number < 84)
		{

		printf("Rolled a number from 69-83, You gain 5 points!\n");
                round_points += 5;




		}
		else if (random_number < 93)
		{
		printf("Rolled a number from 84-92, You gain ten points!\n"); 
		round_points += 10;
		


		}
		else if (random_number <= 99)
		{
		printf("Rolled a number from 93-99, You gain fifteen points!\n");
				
		round_points += 15;

		}

	
		if (*banked_points + round_points >= FINALSCORE)
		{
			*banked_points += round_points;
			printf("The score of 132 was reached and the game will now end. Thank you for playing\n");
			return 1;

		}


		if (roll_pass(banked_points,&round_points, is_player) == 0)
		{
			break;
		}

		

	
	}
	return 0;
}
int roll_pass(int *banked_points, int *round_points, int is_player)
{
	
	char choice;
	
		if (is_player)
		{
			printf("Would you like to roll again or pass? (Y/N) --> \n");
			char buffer[size];
			if(fgets(buffer,size,stdin) == NULL) 
			{
				*banked_points += *round_points;
				return 0;
			}
			sscanf(buffer,"%c", &choice);

			if (choice == 'N' || choice == 'n')
			{
				*banked_points += *round_points;
				printf("%d points have been added to your account. Your new total is now: %d\n",  *round_points, *banked_points);
				return 0;
			}
			else if (choice == 'Y' || choice == 'y')
			{
				return 1;
			}
			else
			{
				*banked_points += *round_points;
				printf("Passing turn, %d points have been added to your account. Total: %d \n", *round_points, *banked_points);
				return 0;
			}
		}
		else
		{
			if(*round_points >= 25 || (*banked_points + *round_points) >= FINALSCORE)
			{
				*banked_points += *round_points;
				printf("%d points have been added to the computers account. New computer total: %d \n", *round_points, *banked_points);
				return 0;
			}
			return 1;
		}
	
}
int play_game(int *player_kopeks, int *computer_kopeks)
{
	int player_banked_points = 0;
	int computer_banked_points = 0;
	
	char choice;
	int player_turn;

	printf("Would you like to throw first? (Y/N): \n");
	char buffer[size];
	if (fgets(buffer,size,stdin) == NULL)
	{
		player_turn = 0;
	}
	else
	{
		sscanf(buffer, "%c", &choice);
	
		if (choice == 'Y' || choice == 'y')
		{
			player_turn = 1;
		}
		else
		{
			player_turn = 0;
		}
	}

	while (player_banked_points < FINALSCORE && computer_banked_points < FINALSCORE)
	{
		if (player_turn == 1)
		{
			printf("\n It is now the Player's turn\n");
			if (point_calculator(&player_banked_points, &computer_banked_points, 1) == 1)
			{
				break;
			}
		}
		else
		{
			printf("\n It is now the Computers turn\n");
			if (point_calculator(&player_banked_points, &computer_banked_points, 0) == 1)
			{
				break;
			}
		}
		if (player_banked_points >= FINALSCORE || computer_banked_points >= FINALSCORE)
		{	
			break;
		}


		if (player_turn == 1)
		{
			player_turn = 0;
		}
		else
		{
			player_turn = 1;
		}
	}

	if (player_banked_points >= FINALSCORE)
	{
		printf("\nSCORE! Player wins +1 kopek! nice.\n");
		*player_kopeks += 1;
		*computer_kopeks -= 1;
		
		printf("Thank you for playing, Your final score was: Player: %d kopeks, Computer: %d kopeks\n",*player_kopeks, *computer_kopeks);
		return 1;

	}
	if (computer_banked_points >= FINALSCORE)
	{
		printf("\nComputer scores +1 kopek\n");
		*player_kopeks -= 1;
		*computer_kopeks += 1;

		printf("Thank you for playing, Your final score was: Player: %d kopeks, Computer: %d kopeks\n", *player_kopeks, *computer_kopeks);
		return 0;
	}
	
	
		
	return -1;
}

			












