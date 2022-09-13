#include <stdio.h>
#include <stdlib.h>
int read_flight(int flight_num[], char flight_origin[][20], char flight_destination[][20], char flight_date[][20], char flight_time[][20], int flight_seats[], int fcount);	
int read_reservation(int res_code[], int rflight_num[], int rcount, double seat_cost[], char last_name[][20], char first_name[][20], char seat_type[][20]);
int menu();
void modify_flight();
void modify_reservation();
void report(int flight_num[], char flight_origin[][20], char flight_destination[][20], char flight_date[][20], char flight_time[][20],
int flight_seats[], int fcount, int res_code[], int rflight_num[], int rcount, double seat_cost[], char last_name[][20], char first_name[][20], char seat_type[][20]);
void exit_program();
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() 
{
	int selection;
	
	//read_flight
	int flight_num[100];
	char flight_origin[100][20],flight_destination[100][20],flight_date[100][20],flight_time[100][20],flight_seats[100];
	int fcount = -1;
	
	//read_reservation
	int res_code[100], rflight_num[100];
	char last_name[100][20], first_name[100][20], seat_type[100][20];
	double seat_cost[100];
	int rcount = -1;

	fcount = read_flight(flight_num, flight_origin, flight_destination, flight_date, flight_time, flight_seats, fcount);
	rcount = read_reservation(res_code, rflight_num, rcount, seat_cost, last_name, first_name, seat_type);
	selection = menu();
	
	while (selection != 4)
	{
		if (selection == 1)
			modify_flight();
		
		else
			if (selection == 2)
				modify_reservation();
			else
				if (selection == 3)
					report(flight_num, flight_origin, flight_destination, flight_date, flight_time, flight_seats, fcount, res_code, rflight_num, rcount, seat_cost, last_name, first_name, seat_type);
		
		selection = menu();
	}
	
	exit_program();
	return 0;
}



int read_flight(int flight_num[], char flight_origin[][20], char flight_destination[][20], char flight_date[][20], char flight_time[][20], int flight_seats[], int fcount)
{
	FILE * input;
	int fnum, fseats;
	char forigin[20], fdestination[20], fdate[20], ftime[20];
	
	input = fopen("flightc.txt", "r");
	if (!input)
		return 1;
	
	while (fscanf(input,"%d %s %s %s %s %d", &fnum, forigin, fdestination, fdate, ftime, &fseats)!=EOF)
		{
			fcount = fcount + 1;
			strcpy(flight_origin[fcount], forigin);
			strcpy(flight_destination[fcount], fdestination);
			strcpy(flight_date[fcount], fdate);
			strcpy(flight_time[fcount], ftime);
			flight_num[fcount] = fnum;
			flight_seats[fcount] = fseats;
		}
	fclose(input);
	printf("Successfuly ran read_flight\n");
	return fcount;
}

int read_reservation(int res_code[], int rflight_num[], int rcount, double seat_cost[], char last_name[][20], char first_name[][20], char seat_type[][20])
{
	FILE *input;
	int rcode, rf_num;
	double scost;
	char lname[20], fname[20], stype[20];
	
	input = fopen("reservationc.txt", "r");
	if (!input)
		return 1;
	
	while (fscanf(input, "%d %d %s %s %s %lf", &rcode, &rf_num, lname, fname, stype, &scost)!=EOF)
	{
		rcount = rcount + 1;
		strcpy(last_name[rcount], lname);
		strcpy(first_name[rcount], fname);
		strcpy(seat_type[rcount], stype);
		res_code[rcount] = rcode;
		rflight_num[rcount] = rf_num;
		seat_cost[rcount] = scost;
	}
	fclose(input);
	printf("Successfuly ran read_reservation\n");
	return rcount;
}

int menu()
{
	int selection;
	printf("*******************************\n");
	printf("\nACME Airline System\n\n");
	
	printf("1. Add/modify Flight information\n");
	printf("2. Add/modify Reservation information\n");
	printf("3. Report Section\n");
	printf("4. Exit Airline System\n\n");
	printf("*******************************\n");
	
	printf("Please make your selection > ");
	scanf("%d", &selection);
	printf("\n");
	return selection;	
}

void modify_flight()
{
	printf("Executing modify_flight\n\n");
}

void modify_reservation()
{
	printf("Executing modify_reservation\n\n");
}

void report(int flight_num[], char flight_origin[][20], char flight_destination[][20], char flight_date[][20],
char flight_time[][20], int flight_seats[], int fcount, int res_code[], int rflight_num[], int rcount, double seat_cost[], char last_name[][20], char first_name[][20], char seat_type[][20])
{
	int selection;
	int i;
	int string_comp;
	char type_selection[20];
	double total_value;
	int input_number;
	
	while (selection != 9)
	{

		printf("*******************************\n");
		printf("\nACME Airlines\n\n");
	
		printf("1. All flight info\n");
		printf("2. All reservation info\n");
		printf("3. Value of reservations of a specific type\n");
		printf("4. All reservations on a specific flight\n");
		printf("5. Report 5 \n");
		printf("6. Report 6 \n");
		printf("7. Report 7 \n");
		printf("8. Report 8 \n");
		printf("9. Exit Report Menu\n\n");
		printf("*******************************\n");
		
		printf("Please make your selection > ");
		scanf("%d", &selection);
		printf("\n");
	
	
		while ((selection != 9)&&(selection != 0))
		{
			if (selection == 1)
			{
				printf("*******************************\n");
				printf("Flight Info\n\n");
				for (i = 0; i<=fcount; ++i)
				{
					printf("%d %s %s %s %s %d\n", flight_num[i], flight_origin[i], flight_destination[i], flight_date[i], flight_time[i], flight_seats[i]);
				}
				printf("*******************************\n");
			}
			
			else
				if (selection == 2)
				{
					printf("*******************************\n");
					printf("Reservation Info\n\n");
					for (i = 0; i<rcount; ++i)
					{
						printf("%d %d %s %s %s $%lf\n", res_code[i], rflight_num[i], last_name[i], first_name[i], seat_type[i], seat_cost[i]);
					}
					printf("*******************************\n");
				}
				else
					if (selection == 3)
					{
						printf("Enter the reservation type (business, coach, first): ");
						scanf("%s", &type_selection);
						
						printf("*******************************\n");
						for (i = 0; i<rcount; ++i)
						{
							string_comp = strcmp(seat_type[i], type_selection);
							if (string_comp == 0)
							{	
								total_value = total_value + seat_cost[i];
								printf("%d %d %s %s %s $%lf\n", res_code[i], rflight_num[i], last_name[i], first_name[i], seat_type[i], seat_cost[i]);
							}
						}
						fflush(stdin);
						printf("\nTotal value of reservation type: $%lf\n", total_value);
						printf("*******************************\n");
					}
					else
						if (selection == 4)
						{
							printf("Enter the flight number: \n");
							scanf("%d", &input_number);
							printf("*******************************\n");
							for (i = 0; i<rcount; ++i)
							{
								if (rflight_num[i] == input_number)
								{
									printf("%d %d %s %s %s $%lf\n", res_code[i], rflight_num[i], last_name[i], first_name[i], seat_type[i], seat_cost[i]);
								}
							}
							printf("*******************************\n");
						}
						else
							if (selection == 5)
							{
								printf("Executing selection 5\n");
							}
							else
								if(selection == 6)
								{
									printf("Executing selection 6\n");
								}
								else
									if(selection == 7)
									{
										printf("Executing selection 7\n");
									}
									else
										if(selection == 8)
										{
											printf("Executing selection 8\n");
										}
			selection = 0;								
		}
	}
}
void exit_program()
{
	printf("Executing exit_program\n");
}
