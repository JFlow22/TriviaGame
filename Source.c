#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "MinUnit.h"

#define Reg_File "Registered_Users.txt"
#define Admin_File "Admins.txt"
#define Log_File "Log.txt"
#define Report_File "report.txt"
#define Daily_Winner "DWinner.txt"
#define Rank_A "Rank_A.txt"
#define Rank_B "Rank_B.txt"
#define Rank_C "Rank_C.txt"
#define Rank_D "Rank_D.txt"
#define Rank_E "Rank_E.txt"
#define Rank_F "Rank_F.txt"
#define Rank_G "Rank_G.txt"
#define Rank_H "Rank_H.txt"
#define Rank_I "Rank_I.txt"
#define Rank_J "Rank_J.txt"

//This user key is for general functions. with that key those function know how to act.
enum USER_KEY { ADMIN_KEY, REG_KEY, AN_KEY };

typedef char* String;

//Admin have password, name and ID.
typedef struct admin {
	char Password[50];
	char Name[50];
	char ID[50];
}Admin;

//Registered user have nickname, password, name, hight score, last scroe and last time
typedef struct reg_user {
	char Nickname[50];
	char Password[50];
	char Full_Name[50];
	int High_Score;
	int Last_Score;
	int Last_Time;
}Reg_User;


//Anonymous user have only high score and time. This in case he want to sign up to the game
typedef struct anonymous_user {
	int High_Score;
	int Time;
}Anonymous_User;

//Question have number, content(including 4 answers), right answer and basic time.
typedef struct question {
	int Q_Number;
	char content[256];
	int Right_Answer;
	int Basic_Time;
}Question;

//The array struct is for the list of questions. Values for the question and lenght to show the amount of questions.
typedef struct Array {
	Question ** Values;
	int length;
}Array;

//Rank have symbol, title, added time, score and list of questions.
typedef struct rank {
	char Rank_Symbol;
	char Rank_Title[100];
	int Added_Time;
	int Score;
	Array* Q_list;
}Rank;

//Global admin, registered user and anonymous user
Admin *current_admin = NULL;
Reg_User *current_reg_user = NULL;
Anonymous_User *current_anonymous_user = NULL;

//Global ranks
static Rank* A;
static Rank* B;
static Rank* C;
static Rank* D;
static Rank* E;
static Rank* F;
static Rank* G;
static Rank* H;
static Rank* I;
static Rank* J;

//////////////////////////////////// Function Declaration ////////////////////////////////////
int Edit_User_Details();
void update_score_and_time_reg(int score, int time);
void update_score_and_time_anonymous(int score, int time);
int admin_verification(String ID, String password);
Admin *get_admin(char *id);
int add_admin();
int New_Question_List_In_Ranks(Rank* R);
int Pull_Questions_From_File(Rank * R, String FileName); 
int Build_New_Rank(Rank* R, String FileName); 
int Pre_Start_Of_The_System(); 
int Check_Question_Existence_In_Ranks(Rank* R, Question* Q); 
void Delete_Question_In_Ranks(Rank* R, Question* Q);
void Add_Question(char RankSymbol, int QBasicTime, char* Qcontent, int QRightAnswer);
Question Delete_Question_For_New(char RankSymbol, int QuestionNumber);
void Delete_Question(char RankSymbol, int QuestionNumber);
void Write_Question_To_File(Rank R, int index, String FileName);
void Change_Rank_Added_Time_For_Rank(Rank* R, int Time);
void Change_Rank_Added_Time(char RankSymbol, int Time);
void Change_Question_Rank(char RankSymbolDel, char RankSymbolNew, int QuestionNumber);
void Edit_Question_For_Ranks(Rank* R, Question* Q, char * Content, int RightAnswer);
void Add_Question_To_Ranks(Rank* R, Question* Q);
void Edit_Question(char RankSymbol, int QuestionNumber, char * Content, int RightAnswer);
int Encode(char* QContent);
void Print_Question_Details(char RankSymbol, int QuestionNumber, int option);
void Print_Rank(Rank *R);
void Print_Rank_Details(char RankSymbol);
int Check_Answer(int UserInput, int QuestionNumber, char RankSymbol); 
void Print_All_Ranks();
int Menu(int user_key);
int add_user(int* hs, int*ls, int*lt, int is_anonymous);
void LogIn_Menu();
int Admin_login();
void Print_To_Log_File(char *msg);
int edit_admin_details(Admin* admin);
int Wait(int secs); 
void Print_From_Log_File(char* date);
void change_question_rank_by_admin();
char* get_date();
void print_leader_board();
void add_question_by_admin();
int Decode(char* QContent); 
void End_Of_The_System();
int User_counter();
int Admin_counter(); 
int delete_admin(char id[]);
void Print_The_Daily_Winner();
void Exit(int user_key);
int time_to_int(char* str_time, int *hour, int *minute, int *seconde); 
int Play_Level(Rank* rank, char *level, int *Score, int *question_index, int *total_time);
void Register_user(Reg_User user);
void print_total_time(int time);
void remove_user(String nickname);
void Print_to_DWinner(Reg_User user);
int user_verification(String nickname, String password); 
int change_user_info(Reg_User *u);
int delete_user(char nickname[]);
int calculate_score(Rank* rank, int time, int q_index); 
char* get_current_time();
int calculate_time_difference(char* start, char* end); 
void get_answer(int *answer);
void print_start_game();
void Starting_Game_Animation();
int Create_User(Reg_User usr);
int Admin_Menu();
int User_Menu();
int Anonymous_Menu();
void update_game_stats_to_log(int status);
void remove_admin(String ID);
void Change_admin_info(Admin * admin);
void Release_Rank_Memory(Rank *R);
void Register_Admin(Admin admin);
int Reg_user_login();
int question_counter(); 
void print_report();
void print_last_time();
void Print_from_log_file_Admin();
void Opening_Trivia();
void Opening_The();
void Opening_Game();
void BY_Triviani();
void Opening_ALL();
void Open_Animiation();
void New_Game();
int isEmpty(char* name);
int get_user(String nickname, Reg_User* ans); 
Reg_User *get_reg_user(char *nickname);
Reg_User* get_best_player();
int delete_user_from_system();
void delete_question_by_admin();
void change_question_content_by_admin();
int delete_admin_from_system();
int Create_Admin(Admin admin);
void Change_user_info(Reg_User *user);
int change_user_info(Reg_User *u);
void change_rank_time_by_admin();
int Verify_Details(char* id, char* nickname, char* pass);

////////////////////////////////////////// MinUnits //////////////////////////////////////////
MU_TEST(test_Check_Answer) {
	mu_check(Check_Answer(1, 1, 'A') == 1);
}

MU_TEST(test_user_verification) {
	mu_check(user_verification("Aviv1818", "123123") == 1);
}

MU_TEST(test_admin_verification) {
	mu_check(admin_verification("208897371", "123123") == 1);
}

MU_TEST(test_User_counter) {
	mu_check(User_counter() == 4);
}

MU_TEST(test_Admin_counter) {
	mu_check(Admin_counter() == 2);
}

MU_TEST(test_question_counter) {
	mu_check(question_counter() == 30);
}

MU_TEST(test_get_admin) {
	Admin *temp_admin = get_admin("208897371");
	mu_check(temp_admin != NULL && !strcmp(temp_admin->ID,"208897371"));
	free(temp_admin);
}

MU_TEST(test_get_reg_user) {
	Reg_User *temp_reg_user = get_reg_user("Aviv1818");
	mu_check(temp_reg_user != NULL);
	free(temp_reg_user);
}

MU_TEST(test_get_best_player) {
	Reg_User *temp_reg_user = get_best_player();
	mu_check(temp_reg_user != NULL);
	free(temp_reg_user);
}

MU_TEST(test_Encode) {
	char tmp[20] = "hello@world";
	mu_check(Encode(tmp) != 0);
}

MU_TEST(test_Decode) {
	char tmp[20] = "hello\nworld";
	mu_check(Decode(tmp) != 0);
}

MU_TEST(test_get_user) {
	Reg_User *user = (Reg_User*)malloc(sizeof(Reg_User));
	mu_check(get_user("Aviv1818", user) == 1);
	free(user);
}

MU_TEST(test_Wait) {
	mu_check(Wait(0) == 1);
}

MU_TEST(test_time_to_int) {
	int hour, minute, seconde;
	time_to_int("15:45:22", &hour, &minute, &seconde);
	mu_check(hour == 15 && minute == 45 && seconde == 22);
}

MU_TEST(test_calculate_time_difference) {
	mu_check(calculate_time_difference("15:45:22", "15:45:58") == 36);
}

MU_TEST(test_calculate_score) {
	mu_check(calculate_score(A, 10, 1) == 100);
}

MU_TEST_SUITE(test_get) {
	MU_SUITE_CONFIGURE(NULL,NULL);
	MU_RUN_TEST(test_get_admin);
	MU_RUN_TEST(test_get_reg_user);
	MU_RUN_TEST(test_get_best_player);
	MU_RUN_TEST(test_get_user);
	MU_REPORT_SUITE();
}

MU_TEST_SUITE(test_decode_encode) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_Encode);
	MU_RUN_TEST(test_Decode);
	MU_REPORT_SUITE();
}

MU_TEST_SUITE(test_counter) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_User_counter);
	MU_RUN_TEST(test_Admin_counter);
	MU_RUN_TEST(test_question_counter);
	MU_REPORT_SUITE();
}

MU_TEST_SUITE(test_check) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_Check_Answer);
	MU_RUN_TEST(test_user_verification);
	MU_RUN_TEST(test_admin_verification);
	MU_REPORT_SUITE();

}

MU_TEST_SUITE(test_time) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_Wait);
	MU_RUN_TEST(test_time_to_int);
	MU_RUN_TEST(test_calculate_time_difference);
	MU_REPORT_SUITE();
}

MU_TEST_SUITE(test_calculate) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_calculate_score);
	MU_REPORT_SUITE();
}

/////////////////////////////////// Functions //////////////////////////////////

//Run all the unit tests
void run_unit_tests() {
	MU_RUN_SUITE(test_get);
	MU_RUN_SUITE(test_decode_encode);
	MU_RUN_SUITE(test_counter);
	MU_RUN_SUITE(test_check);
	MU_RUN_SUITE(test_time);
	MU_RUN_SUITE(test_calculate);
	MU_REPORT();
}

//Calculate the score
int calculate_score(Rank* rank, int time, int q_index) {
	int total_time = rank->Added_Time + rank->Q_list->Values[q_index]->Basic_Time - time;
	//If the user answer after time, he will get only 5 points
	if (total_time <= 0)
		return 5;
	//The score is the product of the time it took him to answer and the rank score
	return (total_time * rank->Score);
}

//Return a string that show the current time
char* get_current_time() {
	time_t timer;
	char *buffer = (char*)malloc(26*sizeof(char));
	struct tm* tm_info;
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, "%X", tm_info);
	return buffer;
}

//Calculate the time difference in secondes.
int calculate_time_difference(char* start, char* end) {
	int start_hour, start_minute, start_seconde,
		end_hour, end_minute, end_seconde,
		time_difference = 0;
	time_to_int(start, &start_hour, &start_minute, &start_seconde);
	time_to_int(end, &end_hour, &end_minute, &end_seconde);
	time_difference += (end_hour - start_hour) * 3600;
	time_difference += (end_minute - start_minute) * 60;
	time_difference += end_seconde - start_seconde;
	return time_difference;
}

//Get the answer from the user
void get_answer(int *answer) {
	int valid;
	char term;
	do {
		printf("\nYour answer:");
		valid = scanf("%d%c", &(*answer), &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (*answer > 5 || *answer < 0)
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (*answer > 5 || *answer < 0));
}

//Print "starting game" for the animation before the game starts
void print_start_game() {
	printf(" _____ _             _   _             \n");
	printf("/  ___| |           | | (_)            \n");
	printf("\\ `--.| |_ __ _ _ __| |_ _ _ __   __ _ \n");
	printf(" `--. \\ __/ _` | '__| __| | '_ \\ / _` |\n");
	printf("/\\__/ / || (_| | |  | |_| | | | | (_| |\n");
	printf("\\____/ \\__\\__,_|_|   \\__|_|_| |_|\\__, |\n");
	printf("     _____                        __/ |\n");
	printf("    |  __ \\                      |___/ \n");
	printf("    | |  \\/ __ _ _ __ ___   ___ \n");
	printf("    | | __ / _` | '_ ` _ \\ / _ \\\n");
	printf("    | |_\\ \\ (_| | | | | | |  __/\n");
	printf("     \\____/\\__,_|_| |_| |_|\\___|\n");
}

//Animation that count down from three before the game starts
void Starting_Game_Animation() {
	system("cls");
	int i;
	for (i = 3; i > 0; i--) {
		print_start_game();
		if (i == 3) {
			printf("\t   _____         _____ \n");
			printf("\t  |_   _|       |____ |\n");
			printf("\t    | | _ __        / /\n");
			printf("\t    | || '_ \\       \\ \\\n");
			printf("\t   _| || | | |  .___/ /\n");
			printf("\t   \\___/_| |_|  \\____/ \n");
			Wait(2);
		}
		if (i == 2) {
			printf("\t   _____         _____ \n");
			printf("\t  |_   _|       / __  \\\n");
			printf("\t    | | _ __    `' / /'\n");
			printf("\t    | || '_ \\     / /  \n");
			printf("\t   _| || | | |  ./ /___\n");
			printf("\t   \\___/_| |_|  \\_____/\n");
			Wait(1);
		}
		if (i == 1) {
			printf("\t   _____         __  \n");
			printf("\t  |_   _|       /  | \n");
			printf("\t    | | _ __    `| | \n");
			printf("\t    | || '_ \\    | | \n");
			printf("\t   _| || | | |  _| |_\n");
			printf("\t   \\___/_| |_|  \\___/\n");
			Wait(1);
		}
		system("cls");
	}
}

//Get a string of time (HH:MM:SS) and update though pointers the hour, minute and seconde
int time_to_int(char* str_time, int *hour, int *minute, int *seconde) {
	char tmp[20];
	if (strlen(str_time) < 8)
		return 0;
	strcpy(tmp, str_time);
	//Get the hour string and convert to int
	tmp[2] = '\0';
	*hour = atoi(tmp);
	strcpy(tmp, (str_time + 3));
	//Get the minute string and convert to int
	tmp[2] = '\0';
	*minute = atoi(tmp);
	strcpy(tmp, (str_time + 6));
	//Get the seconde string and convert to int
	*seconde = atoi(tmp);
	return 1;
}

//Write the start and end time to the log file
void update_game_stats_to_log(int status) {
	//If status is 0, the game started
	//If status is 1, the game ended
	char msg[50] = "",*time = get_current_time();
	//Check the status and write to the log file
	//If there is a registered user in the system, write to the log file that a registered user started/ended a game
	//Else write that a anonymous user started/ended the game
	if (!status) {
		if (current_reg_user != NULL) {
			strcat(msg, current_reg_user->Nickname);
			strcat(msg, " started a new game at: ");
			strcat(msg, time);
			strcat(msg, ".");
		}
		else {
			strcat(msg, "Anonymous user started a new game at: ");
			strcat(msg, time);
			strcat(msg, ".");
		}
	}
	else {
		if (current_reg_user != NULL) {
			strcat(msg, current_reg_user->Nickname);
			strcat(msg, " ended the game game at: ");
			strcat(msg, time);
			strcat(msg, ".");
		}
		else {
			strcat(msg, "Anonymous user ended the game at: ");
			strcat(msg, time);
			strcat(msg, ".");
		}
	}
	free(time);
	Print_To_Log_File(msg);
}

//New game function
void New_Game() {
	//if exit =1 --> The user end the game normally
	//If exit =2 --> The user left in the middle of the game
	char current_level = 'A', exit = 0, start_time[12] = "", end_time[12] = "", content[256] = "", title[30] = "";
	int Score = 0, Total_time = 0, question_index = 1;
	//Show instructions for the player
	printf("Welcome To The Trivia Game!\n");
	printf("The subject of the game is theoretical issues in the \nfield of software engineering.\nAlso General knowledge of practical issues\n");
	printf("This game have 10 levels\n");
	printf("For each question, the time for this question will be shown\n");
	printf("Quick response will give extra points.\n");
	printf("Pay attention, If you wish to get out in the middle of the game, all the game data will be lost!.\n");
	printf("Press 5 in any question to go back to the main menu.\n");
	printf("Enjoy!\n");
	printf("\nPress any key to start the game!");
	getchar();
	//Show start game animation
	Starting_Game_Animation();
	//While loop to play each level.
	while (!exit) {
		system("cls");
		switch (current_level)
		{
		case 'A':
			if (Play_Level(A, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'B':
			if (Play_Level(B, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'C':
			if (Play_Level(C, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'D':
			if (Play_Level(D, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'E':
			if (Play_Level(E, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'F':
			if (Play_Level(F, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'G':
			if (Play_Level(G, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'H':
			if (Play_Level(H, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'I':
			if (Play_Level(I, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		case 'J':
			if (Play_Level(J, &current_level, &Score, &question_index, &Total_time) == 2)
				exit = 2;
			break;
		default:
			printf("You finished the game!");
			exit = 1;
			break;
		}
	}
	//if exit =1 --> The user end the game normally.
	//If he is registered user, his stats will be updated. If he is anonymous user, his stats will be saved if he will sign up.
	//If exit =2 --> The user left in the middle of the game and no score nor time will be saved.
	if (exit == 2)
		printf("You canceled the game!\n");
	else {
		printf("Your score: %d\n", Score);
		print_total_time(Total_time);
		if (current_reg_user != NULL) {
			update_score_and_time_reg(Score, Total_time);
			Print_to_DWinner(*current_reg_user);
		}
		else {
			current_anonymous_user->High_Score = Score;
			current_anonymous_user->Time = Total_time;
		}
	}
}

//Udate score and time to registered user.
void update_score_and_time_reg(int score, int time) {
	//First remove the user from the file
	remove_user(current_reg_user->Nickname);
	//Update last time, last score and high score to the current registered user
	current_reg_user->Last_Time = time;
	current_reg_user->Last_Score = score;
	if (current_reg_user->High_Score < score)
		current_reg_user->High_Score = score;
	//Save the updated user to the system
	Register_user(*current_reg_user);
}

//Update score and time to anonymous user
void update_score_and_time_anonymous(int score, int time) {
	current_anonymous_user->High_Score = score;
	current_anonymous_user->Time = time;
}

//Return the score
int Update_stats(int time_to_answer, Rank *rank, int question_index) {
	return calculate_score(rank, time_to_answer, question_index);
}

//Play the level
//This function get rank, current level, player's score, question index and player's time
int Play_Level(Rank* rank, char *level, int *Score, int *question_index, int *total_time) {
	int i, answer, time_to_answer, time_for_user;
	char title[50] = "", start_time[20] = "", end_time[20] = "", *time;
	strcpy(title, rank->Rank_Title);
	title[strlen(title) - 1] = '\0';
	for (i = 0; i < rank->Q_list->length; i++) {
		//Get the start time
		time = get_current_time();
		strcpy(start_time, time);
		free(time);
		//Get the time for the question by adding the basic time and the bonus rank time
		time_for_user = rank->Added_Time + rank->Q_list->Values[i]->Basic_Time;
		//Print the question
		printf("Current level: %s (Level %c)\n", title, *level);
		printf("============== Question #%d ==============\n", *question_index);
		printf("Time for this question: %d secondes\n\n", time_for_user);
		Print_Question_Details(*level, i + 1, 1);
		//Get the answer from the user
		get_answer(&answer);
		//Get the end time
		time = get_current_time();
		strcpy(end_time, time);
		free(time);
		//Calculate the time is took to the user to answer
		time_to_answer = calculate_time_difference(start_time, end_time);
		//Update the total time
		(*total_time) += time_to_answer;
		//If the user press 5, return 2
		if (answer == 5) {
			return 2;
		}
		//If the user choose the right answer, update the scsore
		else if (rank->Q_list->Values[i]->Right_Answer == answer)
			(*Score) += Update_stats(time_to_answer, rank, i);
		//If there is no more question in the level, the next level will be played
		if (i == rank->Q_list->length - 1)
			(*level)++;
		//Promote question index by 1
		(*question_index)++;
		system("cls");
	}
	return 1;
}

//Print last time in comfortable way
void print_last_time() {
	int minutes, secondes;
	if (current_reg_user->Last_Time == 0)
		printf("You didnt play any games! yet... ;)\n");
	else {
		if (current_reg_user->Last_Time < 60)
			printf("Last time is:%d secondes\n", current_reg_user->Last_Time);
		else {
			secondes = current_reg_user->Last_Time;
			secondes %= 60;
			minutes = (current_reg_user->Last_Time - secondes) / 60;
			if (!secondes) {
				if (minutes == 1)
					printf("Last time is:%d minute\n", minutes);
				else
					printf("Last time is:%d minutes\n", minutes);
			}
			else {
				if (minutes == 1)
					printf("Last time is:%d minute and %d secondes\n", minutes, secondes);
				else
					printf("Last time is:%d minutes and %d secondes\n", minutes, secondes);
			}
		}
	}
}

//Print total time in comfortable way
void print_total_time(int time) {
	int minutes, secondes;
	if (time < 60)
		printf("Total time:%d secondes\n", time);
	else {
		secondes = time;
		secondes %= 60;
		minutes = (time - secondes) / 60;
		if (!secondes) {
			if (minutes == 1)
				printf("Total time:%d minute\n", minutes);
			else
				printf("Total time:%d minutes\n", minutes);
		}
		else {
			if (minutes == 1)
				printf("Total time:%d minute and %d secondes\n", minutes, secondes);
			else
				printf("Total time:%d minutes and %d secondes\n", minutes, secondes);
		}
	}
}

//Exit funtion that print to the log file according to the user key
void Exit(int user_key) {
	char msg[50] = "";
	if (user_key == ADMIN_KEY) {
		strcat(msg, "Admin ");
		strcat(msg, current_admin->Name);
		strcat(msg, " logged out from the system.");
	}
	else if (user_key == REG_KEY) {
		strcat(msg, "User ");
		strcat(msg, current_reg_user->Nickname);
		strcat(msg, " logged out from the system.");
	}
	else
		strcat(msg, "Anonymous user logged out from the system.");
	Print_To_Log_File(msg);
}

//Get the best player (with the highest score)
Reg_User* get_best_player() {
	int i = 0, j = 0, max_score = -1, counter;
	Reg_User **temp_users, *tmp, *bestplayer;
	FILE *reg_file = fopen(Reg_File, "r");
	if (!reg_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return NULL;
	}
	counter = User_counter();
	if (counter == 0)
		return NULL;
	temp_users = (Reg_User**)malloc(counter * sizeof(Reg_User*));
	for (int i = 0; i <counter; i++) {
		while (!feof(reg_file)) {
			temp_users[j] = (Reg_User*)malloc(sizeof(Reg_User));
			fscanf(reg_file, "%s", temp_users[j]->Nickname);
			fscanf(reg_file, "%s\n", temp_users[j]->Password);
			fgets(temp_users[j]->Full_Name, 50, reg_file);
			fscanf(reg_file, "%d", &temp_users[j]->High_Score);
			fscanf(reg_file, "%d", &temp_users[j]->Last_Score);
			fscanf(reg_file, "%d\n", &temp_users[j]->Last_Time);
			j++;
		}
	}
	for (int i = 0; i < counter; i++) {
		for (j = i + 1; j < counter; j++) {
			if (temp_users[i]->High_Score < temp_users[j]->High_Score)
			{
				tmp = temp_users[i];
				temp_users[i] = temp_users[j];
				temp_users[j] = tmp;
			}
		}
	}
	bestplayer = (Reg_User*)malloc(sizeof(Reg_User));
	strcpy(bestplayer->Nickname, temp_users[0]->Nickname);
	bestplayer->High_Score = temp_users[0]->High_Score;
	for (i = 0; i < counter; i++)
		free(temp_users[i]);
	free(temp_users);
	fclose(reg_file);
	return bestplayer;
}

// A function for decoding a text from the admin's input (ment for ranks file)
int Decode(char* QContent) 
{
	int count = 0; // switching between '\n' and '@'
	while (QContent[count] != '\0')
	{
		if (QContent[count] == '\n')
		{
			QContent[count] = '@';
		}
		count++;
	}
	if (count >= 0) return 1;
	return 0;
}

//Count all the questions in all the levels
int question_counter() {
	int i = 0, counter = 0;
	counter += A->Q_list->length;
	counter += B->Q_list->length;
	counter += C->Q_list->length;
	counter += D->Q_list->length;
	counter += E->Q_list->length;
	counter += F->Q_list->length;
	counter += G->Q_list->length;
	counter += H->Q_list->length;
	counter += I->Q_list->length;
	counter += J->Q_list->length;
	return counter;
}

//Print system report
void print_report() {
	Reg_User *user = get_best_player();
	char nickname[20] = "";
	printf("=================================================\n");
	printf("|                 System Report                 |\n");
	printf("|===============================================|\n");
	printf("|%-22s |%-22d |\n", "Num of admins", Admin_counter());
	printf("|%-22s |%-22d |\n", "Num of users", User_counter());
	printf("|%-22s |%d %-21s|\n", "Rank A", A->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank B", B->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank C", C->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank D", D->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank E", E->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank F", F->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank G", G->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank H", H->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank I", I->Q_list->length, "Questions");
	printf("|%-22s |%d %-21s|\n", "Rank J", J->Q_list->length, "Questions");
	printf("|%-22s |%-22d |\n", "Total Num of questions", question_counter());
	if (user != NULL) {
		if (user->High_Score != 0) {
			printf("|%-22s |%-22s |\n", "Best Player", user->Nickname);
			printf("|%-22s |%-22d |\n", "Highest Score", user->High_Score);
		}
	}
	else
		printf("|%-22s |%-22s |\n", "Best Player", "None");
	printf("|===============================================|\n");
	free(user);
}

//Change the rank time
void change_rank_time_by_admin() {
	char rank, content[256] = "", term;
	int  valid, new_time;
	//Get the rank
	do {
		printf("Enter rank (a-j):");
		valid = scanf("%c%c", &rank, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a') || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a'));
	if (rank <= 'j' && rank >= 'a')
		rank = rank - 32;
	//Get new time
	do {
		printf("\nEnter new time:");
		valid = scanf("%d%c", &new_time, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (new_time < 0 || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (new_time < 0));
	//Change the rank time
	switch (rank)
	{
	case 'A':
		Change_Rank_Added_Time_For_Rank(A, new_time);
		break;
	case 'B':
		Change_Rank_Added_Time_For_Rank(B, new_time);
		break;
	case 'C':
		Change_Rank_Added_Time_For_Rank(C, new_time);
		break;
	case 'D':
		Change_Rank_Added_Time_For_Rank(D, new_time);
		break;
	case 'E':
		Change_Rank_Added_Time_For_Rank(E, new_time);
		break;
	case 'F':
		Change_Rank_Added_Time_For_Rank(F, new_time);
		break;
	case 'G':
		Change_Rank_Added_Time_For_Rank(G, new_time);
		break;
	case 'H':
		Change_Rank_Added_Time_For_Rank(H, new_time);
		break;
	case 'I':
		Change_Rank_Added_Time_For_Rank(I, new_time);
		break;
	case 'J':
		Change_Rank_Added_Time_For_Rank(J, new_time);
		break;
	}
	printf("Rank time was successfully changed.\n");
}

//Verify Admin/Registered user details
int Verify_Details(char * id, char * nickname, char * pass){
	//If nickname is null, then we check if the admin details are correct.
	//Else we chake if the registered user details are correct
	if (nickname == NULL) 
		return admin_verification(id, pass);
	if (id == NULL) 
		return user_verification(nickname, pass);
	return 0;
}

//Add new questiob
void add_question_by_admin() {
	char rank, line[100], content[256] = "", tmpchar, term;
	int i, valid, basic_time, correct_ans;
	//Get the rank
	do {
		printf("Enter rank for the question (a-j):");
		valid = scanf("%c%c", &rank, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a') || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a'));
	if (rank <= 'j' && rank >= 'a')
		rank = rank - 32;
	//Show instructions for the admin to how to insert the question content
	system("cls");
	printf("Enter the body of the question line by line (no more then 256 charecters) \n");
	printf("After you done enter the question, press ~ in order to enter 4 answers.\n");
	printf("After that, put the right answer\n");
	//Get the question content
	do {
		fgets(line, 100, stdin);
		if (strcmp(line, "~\n") != 0)
			strcat(content, line);
	} while (strcmp(line, "~\n") != 0);
	//Get 4 answers
	printf("Enter 4 answers:\n");
	for (i = 1; i < 5; i++) {
		tmpchar = i + 48;
		content[strlen(content)] = tmpchar;
		content[strlen(content) + 1] = '\0';
		printf("Answer %d:", i);
		fgets(line, 256, stdin);
		strcat(content, ")");
		strcat(content, line);
	}
	//Get the number of the correct answer
	do {
		printf("\nEnter number of correct answer:");
		valid = scanf("%d%c", &correct_ans, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (correct_ans > 4 || correct_ans < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (correct_ans > 4 || correct_ans < 1));
	//Get basic time
	do {
		printf("\nEnter basic time for this question (in secondes):");
		valid = scanf("%d%c", &basic_time, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (basic_time < 0 || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (basic_time < 0));
	//Update the log file and the rank file
	content[strlen(content) - 1] = '\0';
	Add_Question(rank, basic_time, content, correct_ans);
	printf("Question added successfully!\n");
}

//Delete question by admin
void delete_question_by_admin() {
	char rank, term;
	int  valid, choice, amount_of_questions, num_of_question;
	//Get the rank
	do {
		printf("Enter rank for the question (a-j):");
		valid = scanf("%c%c", &rank, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a') || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a'));
	if (rank <= 'j' && rank >= 'a')
		rank = rank - 32;
	switch (rank)
	{
	case 'A':
		amount_of_questions = A->Q_list->length;
		break;
	case 'B':
		amount_of_questions = B->Q_list->length;
		break;
	case 'C':
		amount_of_questions = C->Q_list->length;
		break;
	case 'D':
		amount_of_questions = D->Q_list->length;
		break;
	case 'E':
		amount_of_questions = E->Q_list->length;
		break;
	case 'F':
		amount_of_questions = F->Q_list->length;
		break;
	case 'G':
		amount_of_questions = G->Q_list->length;
		break;
	case 'H':
		amount_of_questions = H->Q_list->length;
		break;
	case 'I':
		amount_of_questions = I->Q_list->length;
		break;
	case 'J':
		amount_of_questions = J->Q_list->length;
		break;
	}
	//Show all the questions in the rank if the admin wants to
	system("cls");
	printf("You know the number of the question you want to delete?");
	printf("\nPress 1 if yes and 2 if you want to see all the question in rank %c.", rank);
	do {
		printf("\nYour choice:");
		valid = scanf("%d%c", &choice, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (choice > 2 || choice < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (choice > 2 || choice < 1));
	if (choice == 2) {
		system("cls");
		switch (rank)
		{
		case 'A':
			Print_Rank(A);
			break;
		case 'B':
			Print_Rank(B);
			break;
		case 'C':
			Print_Rank(C);
			break;
		case 'D':
			Print_Rank(D);
			break;
		case 'E':
			Print_Rank(E);
			break;
		case 'F':
			Print_Rank(F);
			break;
		case 'G':
			Print_Rank(G);
			break;
		case 'H':
			Print_Rank(H);
			break;
		case 'I':
			Print_Rank(I);
			break;
		case 'J':
			Print_Rank(J);
			break;
		}
	}
	//If there is no questions in the rank, return back
	if (!amount_of_questions) {
		printf("There is no questions in this rank.\n");
		return;
	}
	//Get the question's number
	do {
		printf("Enter the question number you wish do delete:");
		valid = scanf("%d%c", &num_of_question, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (valid != 2 || term != '\n' || (num_of_question > amount_of_questions || num_of_question < 1))
			printf("Worng input. Try again\nThis rank have only %d questions\n", amount_of_questions);
	} while (valid != 2 || term != '\n' || (num_of_question > amount_of_questions || num_of_question < 1));
	//Delete the question and update the log file
	Delete_Question(rank, num_of_question);
	printf("Question deleted.\n");
}

//Change question content
void change_question_content_by_admin() {
	char rank, line[50], content[256] = "", tmpchar, term;
	int i, valid, correct_ans, choice, amount_of_questions, num_of_question;
	//Get the rank
	do {
		printf("Enter rank for the question (a-j):");
		valid = scanf("%c%c", &rank, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a') || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a'));
	if (rank <= 'j' && rank >= 'a')
		rank = rank - 32;
	switch (rank)
	{
	case 'A':
		amount_of_questions = A->Q_list->length;
		break;
	case 'B':
		amount_of_questions = B->Q_list->length;
		break;
	case 'C':
		amount_of_questions = C->Q_list->length;
		break;
	case 'D':
		amount_of_questions = D->Q_list->length;
		break;
	case 'E':
		amount_of_questions = E->Q_list->length;
		break;
	case 'F':
		amount_of_questions = F->Q_list->length;
		break;
	case 'G':
		amount_of_questions = G->Q_list->length;
		break;
	case 'H':
		amount_of_questions = H->Q_list->length;
		break;
	case 'I':
		amount_of_questions = I->Q_list->length;
		break;
	case 'J':
		amount_of_questions = J->Q_list->length;
		break;
	}
	system("cls");
	//Show all the questions in the rank if the admin wants
	printf("You know the number of the question you want to edit?");
	printf("\nPress 1 if yes and 2 if you want to see all the question in rank %c.", rank);
	do {
		printf("\nYour choice:");
		valid = scanf("%d%c", &choice, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (choice > 2 || choice < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || choice > 2 || choice < 1);
	if (choice == 2) {
		system("cls");
		switch (rank)
		{
		case 'A':
			Print_Rank(A);
			break;
		case 'B':
			Print_Rank(B);
			break;
		case 'C':
			Print_Rank(C);
			break;
		case 'D':
			Print_Rank(D);
			break;
		case 'E':
			Print_Rank(E);
			break;
		case 'F':
			Print_Rank(F);
			break;
		case 'G':
			Print_Rank(G);
			break;
		case 'H':
			Print_Rank(H);
			break;
		case 'I':
			Print_Rank(I);
			break;
		case 'J':
			Print_Rank(J);
			break;
		}
	}
	//If there is no question in the rank the admin will return to the menu
	if (!amount_of_questions) {
		printf("There is no question in this rank.\n");
		return;
	}
	//Get the question number
	do {
		printf("Enter the question number you wish do edit:");
		valid = scanf("%d%c", &num_of_question, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (num_of_question > amount_of_questions || num_of_question < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again\nThis rank have only %d questions\n", amount_of_questions);
	} while (valid != 2 || term != '\n' || (num_of_question > amount_of_questions || num_of_question < 1));
	system("cls");
	//Show instructions for the admin to how to enter the new questio content
	printf("Enter the body of the question line by line (no more then 256 charecters) \n");
	printf("After you done enter the question, press ~ in order to enter 4 answers.\n");
	printf("After that, put the right answer\n");
	//Get the content
	do {
		fgets(line, 50, stdin);
		if (strcmp(line, "~\n") != 0)
			strcat(content, line);
	} while (strcmp(line, "~\n") != 0);
	//Get 4 possible answers
	printf("Enter 4 answers:\n");
	for (i = 1; i < 5; i++) {
		tmpchar = i + 48;
		content[strlen(content)] = tmpchar;
		content[strlen(content) + 1] = '\0';
		printf("Answer %d:", i);
		fgets(line, 50, stdin);
		strcat(content, ")");
		strcat(content, line);
	}
	//Get the right answer
	do {
		printf("Enter number of correct asnwer:");
		valid = scanf("%d%c", &correct_ans, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (correct_ans > 4 || correct_ans < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (correct_ans > 4 || correct_ans < 1));
	content[strlen(content) - 1] = '\0';
	content[strlen(content)] = '\n';
	//Update the rank file
	Edit_Question(rank, num_of_question, content, correct_ans);
	printf("Question edit done successfully.\n");
}

//Change question rank
void change_question_rank_by_admin() {
	char rank, new_rank, content[256] = "", term, msg[150] = "Admin ", num_of_question_string[3];
	int  valid, choice, amount_of_questions, num_of_question;
	//Print all the questions if the admin want
	printf("You know the rank of the question?");
	printf("\nPress 1 if yes and 2 if you want to see all the questions");
	do {
		printf("\nYour choice:");
		valid = scanf("%d%c", &choice, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (choice > 2 || choice < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (choice > 2 || choice < 1));
	if (choice == 2)
		Print_All_Ranks();
	//Get the rank
	do {
		printf("Enter rank (a-j):");
		valid = scanf("%c%c", &rank, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a') || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (rank > 'J' || rank < 'A') && (rank > 'j' || rank < 'a'));
	if (rank <= 'j' && rank >= 'a')
		rank = rank - 32;
	switch (rank)
	{
	case 'A':
		amount_of_questions = A->Q_list->length;
		break;
	case 'B':
		amount_of_questions = B->Q_list->length;
		break;
	case 'C':
		amount_of_questions = C->Q_list->length;
		break;
	case 'D':
		amount_of_questions = D->Q_list->length;
		break;
	case 'E':
		amount_of_questions = E->Q_list->length;
		break;
	case 'F':
		amount_of_questions = F->Q_list->length;
		break;
	case 'G':
		amount_of_questions = G->Q_list->length;
		break;
	case 'H':
		amount_of_questions = H->Q_list->length;
		break;
	case 'I':
		amount_of_questions = I->Q_list->length;
		break;
	case 'J':
		amount_of_questions = J->Q_list->length;
		break;
	}
	//If there is no questions in the rank, return back to the menu
	if (!amount_of_questions) {
		printf("There is no questions in this rank.\n");
		return;
	}
	//Get the question number
	do {
		printf("Enter the question number:");
		valid = scanf("%d%c", &num_of_question, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (num_of_question > amount_of_questions || num_of_question < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again\nThis rank have only %d questions\n", amount_of_questions);
	} while (valid != 2 || term != '\n' || (num_of_question > amount_of_questions || num_of_question < 1));
	//Get the new rank
	do {
		printf("Enter new rank (a-j):");
		valid = scanf("%c%c", &new_rank, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((new_rank > 'J' || new_rank < 'A') && (new_rank > 'j' || new_rank < 'a') || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (new_rank > 'J' || new_rank < 'A') && (new_rank > 'j' || new_rank < 'a'));
	if (new_rank <= 'j' && new_rank >= 'a')
		new_rank = new_rank - 32;
	//Update the rank file and update the log file
	Change_Question_Rank(rank, new_rank, num_of_question);
	sprintf(num_of_question_string, "%d", num_of_question);
	strcat(msg, current_admin->Name);
	strcat(msg, " changed the rank of question number ");
	strcat(msg, num_of_question_string);
	strcat(msg, " from rank ");
	msg[strlen(msg)] = rank;
	msg[strlen(msg) + 1] = '\0';
	strcat(msg, " to rank ");
	msg[strlen(msg)] = new_rank;
	msg[strlen(msg)] = '.';
	msg[strlen(msg) + 1] = '\0';
	Print_To_Log_File(msg);
	printf("Question rank successfully changed.\n");
}

//Get the date from the admin
char* get_date() {
	char term, *date, tmp[5];
	int day, month, year, valid;
	date = (char*)malloc(12 * sizeof(char));
	date[0] = '\0';
	//Get month
	do {
		printf("Enter month:");
		valid = scanf("%d%c", &month, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (month > 12 || month < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (month > 12 || month < 1));
	//Get day
	do {
		printf("Enter day:");
		valid = scanf("%d%c", &day, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (day > 31 || day < 1 || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (day > 31 || day < 1));
	//Get year
	do {
		printf("Enter year:");
		valid = scanf("%d%c", &year, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if (year > 2017 || year < 2015 || valid != 2 || term != '\n')
			printf("Worng input. Try again\n");
	} while (valid != 2 || term != '\n' || (year > 2017 || year < 2015));
	//Convert each integer to string and append it to the date string
	if (day / 10 == 0)
		strcat(date, "0");
	snprintf(tmp, 5, "%d", day);
	strcat(date, tmp);
	strcat(date, "/");
	if (month / 10 == 0)
		strcat(date, "0");
	snprintf(tmp, 5, "%d", month);
	strcat(date, tmp);
	strcat(date, "/");
	snprintf(tmp, 5, "%d", year);
	strcat(date, tmp);
	//Return the date string in this format DD/MM/YYYY
	return date;
}

//Print the leader board with the maximum amount of 10 users
void print_leader_board() {
	int i = 0, j = 0, max_score = -1, counter;
	Reg_User **temp_users, *tmp;
	FILE *reg_file = fopen(Reg_File, "r");
	if (!reg_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	printf("=================================================\n");
	printf("|                  Leader Board                 |\n");
	printf("|===============================================|\n");
	counter = User_counter();
	if (counter == 0) {
		printf("\n    There is no players in the system, yet ;) \n\n");
		return;
	}
	temp_users = (Reg_User**)malloc(counter * sizeof(Reg_User*));
	for (int i = 0; i <counter; i++) {
		while (!feof(reg_file)) {
			temp_users[j] = (Reg_User*)malloc(sizeof(Reg_User));
			fscanf(reg_file, "%s", temp_users[j]->Nickname);
			fscanf(reg_file, "%s\n", temp_users[j]->Password);
			fgets(temp_users[j]->Full_Name, 50, reg_file);
			fscanf(reg_file, "%d", &temp_users[j]->High_Score);
			fscanf(reg_file, "%d", &temp_users[j]->Last_Score);
			fscanf(reg_file, "%d\n", &temp_users[j]->Last_Time);
			j++;
		}
	}
	//Sort all the scores
	for (int i = 0; i < counter; i++) {
		for (j = i + 1; j < counter; j++) {
			if (temp_users[i]->High_Score < temp_users[j]->High_Score)
			{
				tmp = temp_users[i];
				temp_users[i] = temp_users[j];
				temp_users[j] = tmp;
			}
		}
	}
	printf("|%-15s|%-15s|%-15s|\n", "Place", "Nickname", "Score");
	printf("|-----------------------------------------------|\n");
	if (temp_users[0]->High_Score == 0) {
		printf("|\t    No users with scores... yet:)    \t|\n");
		printf("|-----------------------------------------------|\n");
	}
	else {
		for (int i = 0; i < User_counter() && i< 10 && temp_users[i]->High_Score > 0; i++) {
			printf("|%-15d|%-15s|%-15d|\n", i + 1, temp_users[i]->Nickname, temp_users[i]->High_Score);
			printf("|-----------------------------------------------|\n");
		}
	}
	for (i = 0; i < counter; i++)
		free(temp_users[i]);
	free(temp_users);
	fclose(reg_file);
}

//Get admin by ID
Admin *get_admin(char *id) {
	FILE* admin_file = fopen(Admin_File, "r");
	if (!admin_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return NULL;
	}
	Admin *admin = (Admin*)malloc(sizeof(Admin));
	//Get admin from file
	while (!feof(admin_file)) {
		fgets(admin->ID, 50, admin_file);
		strtok(admin->ID, "\n");
		fgets(admin->Name, 50, admin_file);
		strtok(admin->Name, "\n");
		fgets(admin->Password, 50, admin_file);
		strtok(admin->Password, "\n");
		//If there is an ID match, return the admin
		if (!strcmp(id, admin->ID)) {
			fclose(admin_file);
			return admin;
		}
	}
	fclose(admin_file);
	//Return null if there is no id match
	return NULL;
}

//Get registered user by nickname
Reg_User *get_reg_user(char *nickname) {
	FILE* reg_file = fopen(Reg_File, "r");
	if (!reg_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return NULL;
	}
	Reg_User *reg_user = (Reg_User*)malloc(sizeof(Reg_User));
	//Get users from the file
	while (!feof(reg_file)) {
		fgets(reg_user->Nickname, 50, reg_file);
		strtok(reg_user->Nickname, "\n");
		fgets(reg_user->Password, 50, reg_file);
		strtok(reg_user->Password, "\n");
		fgets(reg_user->Full_Name, 50, reg_file);
		strtok(reg_user->Full_Name, "\n");
		fscanf(reg_file, "%d", &reg_user->High_Score);
		fscanf(reg_file, "%d", &reg_user->Last_Score);
		fscanf(reg_file, "%d\n", &reg_user->Last_Time);
		//If there is a nickname match, return the user
		if (!strcmp(nickname, reg_user->Nickname)) {
			fclose(reg_file);
			return reg_user;
		}
	}
	fclose(reg_file);
	//Return null if there is no match to the nickname
	return NULL;
}

//Admin login
int Admin_login() {
	char id[50], pass[30], c, msg[100] = "Admin ";
	int i = 0;
	//Get id
	printf("Enter id:");
	scanf("%s", id);
	//Get password
	printf("Enter password:");
	do {
		c = _getch();
		if (c != '\r' && c != 8) {
			putchar('*');
			pass[i] = c;
			i++;
		}
		if (c == 8 && i >= 1) {
			printf("\b \b");
			--i;
		}
	} while (c != '\r');
	getchar();
	pass[i] = '\0';
	//Check if the admin exist and if pass is correct.
	//If yes update the log file and return 1.
	//If not return 0
	if (Verify_Details(id, NULL, pass)) {
		current_admin = get_admin(id);
		strcat(msg, current_admin->Name);
		strcat(msg, " logged to the system.");
		Print_To_Log_File(msg);
		return 1;
	}
	return 0;
}

//Registered user login
int Reg_user_login() {
	char nickname[50], pass[30], c, msg[100] = "User ";
	int i = 0;
	//Get nickname
	printf("Enter nickname:");
	scanf("%s", nickname);
	//Get password
	printf("Enter password:");
	do {
		c = _getch();
		if (c != '\r' && c != 8) {
			putchar('*');
			pass[i] = c;
			i++;
		}
		if (c == 8 && i >= 1) {
			printf("\b \b");
			--i;
		}
	} while (c != '\r');
	getchar();
	pass[i] = '\0';
	//Check if the user exist and if pass is correct.
	//If yes update the log file and return 1.
	//If not return 0
	if (Verify_Details(NULL,nickname, pass)) {
		current_reg_user = get_reg_user(nickname);
		strcat(msg, current_reg_user->Nickname);
		strcat(msg, " logged to the system.");
		Print_To_Log_File(msg);
		return 1;
	}
	return 0;
}

//Print from the log file
void Print_from_log_file_Admin() {
	int valid, choice;
	char term, *date;
	//The admin can see the whole log file or by specific date
	printf("1) See the whole log file\n");
	printf("2) See actions by specific date\n");
	printf("3) Go back");
	//Get the admin choice
	do {
		printf("\nYour choice:");
		valid = scanf("%d%c", &choice, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((choice > 3 || choice < 1) || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (choice > 3 || choice < 1));
	switch (choice)
	{
	case 1:
		system("cls");
		Print_From_Log_File(NULL);
		break;
	case 2:
		system("cls");
		date = get_date();
		system("cls");
		Print_From_Log_File(date);
		free(date);
		break;
	default:
		break;
	}
}

//The admin menu
int Admin_Menu() {
	int choice, valid, exit = 0;
	char term;
	while (!exit) {
		//Print the menu
		system("cls");
		printf("Admin:%s\nID:%s\n\n", current_admin->Name, current_admin->ID);
		printf("\t\x1b[4mAdmin Menu\x1b[24m");
		printf("\n\n1) Change details");
		printf("\n2) Add new admin");
		printf("\n3) Edit user details");
		printf("\n4) Delete user");
		printf("\n5) Delete admin");
		printf("\n6) View log");
		printf("\n7) View leader board");
		printf("\n8) Add question");
		printf("\n9) Delete question");
		printf("\n10) Change question content");
		printf("\n11) Change question rank");
		printf("\n12) Change rank time");
		printf("\n13) View system report");
		printf("\n14) Back to login menu");
		printf("\n15) Exit from the system and print the daily winner");
		//Get the admin choice
		do {
			printf("\nYour choice:");
			valid = scanf("%d%c", &choice, &term);
			if (valid != 2 || term != '\n')
				while (getchar() != '\n');
			if ((choice > 15 || choice < 1) || valid != 2 || term != '\n')
				printf("Worng input. Try again");
		} while (valid != 2 || term != '\n' || (choice > 15 || choice < 1));
		system("cls");
		switch (choice)
		{
		case 1:
			//Edit admin details
			if (edit_admin_details(current_admin) == 1)
				printf("\nAdmin details was changed.\n");
			else
				printf("\nAdmin details was not changed.\n");
			break;
		case 2:
			//Add new admin to the system
			if (add_admin())
				printf("Admin successfully added!\n");
			else
				printf("Admin with the same id is in the system!\n");
			break;
		case 3:
			//Change the user details
			if (Edit_User_Details())
				printf("User details changed successfully.\n");
			break;
		case 4:
			//Delete user from the system
			if (delete_user_from_system())
				printf("User deleted.\n");
			else
				printf("This user does not exist.\n");
			break;
		case 5:
			//Delete admin from the system
			if (delete_admin_from_system())
				printf("Admin successfully deleted\n");
			break;
		case 6:
			//Print from log file
			Print_from_log_file_Admin();
			break;
		case 7:
			//Print the leader board
			print_leader_board();
			break;
		case 8:
			//Add question to the system
			add_question_by_admin();
			break;
		case 9:
			//Delete question from the system
			delete_question_by_admin();
			break;
		case 10:
			//Change question content
			change_question_content_by_admin();
			break;
		case 11:
			//Change question rank
			change_question_rank_by_admin();
			break;
		case 12:
			//Change the rank time
			change_rank_time_by_admin();
			break;
		case 13:
			//Print the system report
			print_report();
			break;
		case 14:
			//Exit and return to the login mene and update the log file
			Exit(ADMIN_KEY);
			free(current_admin);
			current_admin = NULL;
			exit = 1;
			break;
		case 15:
			//Exit from the system. This option is only from the admin.
			//When this happen, first the daily winner will be printed and then the system will be closed
			Exit(ADMIN_KEY);
			free(current_admin);
			Print_The_Daily_Winner();
			return 1;
		default:
			break;
		}
		if (choice != 14 && choice != 15) {
			printf("Press any key to go back.");
			getchar();
		}
	}
	return 0;
}

//The registered user menu
int User_Menu() {
	int valid, choice;
	char term, exit = 0;
	while (!exit) {
		//Print the menu
		system("cls");
		printf("Player:%s\nNickname:%s\n", current_reg_user->Full_Name, current_reg_user->Nickname);
		printf("\n\t\x1b[4mPlayer Menu\x1b[24m");
		printf("\n\n1) Start a new game");
		printf("\n2) Change details");
		printf("\n3) View last score");
		printf("\n4) View last time");
		printf("\n5) View leader board");
		printf("\n6) Exit to log in menu\n");
		//Get the user choice
		do {
			printf("\nYour choice:");
			valid = scanf("%d%c", &choice, &term);
			if (valid != 2 || term != '\n')
				while (getchar() != '\n');
			if ((choice > 6 || choice < 1) || valid != 2 || term != '\n')
				printf("Worng input. Try again");
		} while (valid != 2 || term != '\n' || (choice > 6 || choice < 1));
		system("cls");
		switch (choice)
		{
		case 1:
			//Start a new game and update the log file
			update_game_stats_to_log(0);
			New_Game();
			update_game_stats_to_log(1);
			break;
		case 2:
			//Change user details
			if (change_user_info(current_reg_user))
				printf("Details successfully changed.\n");
			break;
		case 3:
			//Print the last game score
			if (current_reg_user->Last_Score == 0)
				printf("You didnt play any games! yet... ;)\n");
			else
				printf("Last score is:%d\n", current_reg_user->Last_Score);
			break;
		case 4:
			//Print the last game time
			print_last_time();
			break;
		case 5:
			//Print the leader board
			print_leader_board();
			break;
		case 6:
			//Exit from the menu and return to the login menu. Also update the log file
			Exit(REG_KEY);
			free(current_reg_user);
			current_reg_user = NULL;
			exit = 1;
			break;
		}
		if (choice != 6) {
			printf("Press any key to go back.");
			getchar();
		}
	}
	return 0;
}

//Anonymous user menu
int Anonymous_Menu() {
	char choice, term;
	int exit = 0, valid;
	while (!exit) {
		//Print the menu
		system("cls");
		printf("\t\x1b[4mAnonymous Menu\x1b[24m");
		printf("\n\n1) Sign up");
		printf("\n2) Start a new game");
		printf("\n3) View leader board");
		printf("\n4) Exit to log in menu\n");
		//Get the choice
		do {
			printf("\nYour choice:");
			valid = scanf("%c%c", &choice, &term);
			if (valid != 2 || term != '\n')
				while (getchar() != '\n');
			if ((choice > '4' || choice < '1') || valid != 2 || term != '\n')
				printf("Worng input. Try again");
		} while (choice > '4' || choice < '1' || valid != 2 || term != '\n');
		system("cls");
		switch (choice)
		{
		case '1':
			//Register the anonymous user to the system.
			//If he played a game, his stats will be saved into his new account.
			//If the anonymous user is trying to register with used id, a message will be printed
			if (current_anonymous_user->High_Score == 0) {
				if (add_user(NULL, NULL, NULL, 0)) {
					printf("User successfully added to the system!\n");
					printf("Go back to the login menu to login as register user!\n");
					free(current_anonymous_user);
					exit = 1;
				}
				else
					printf("This User is already in the system.\n");
			}
			else {
				printf("We see that you already played a game!\nWe will save your score and time :)\n");
				if (add_user(&current_anonymous_user->High_Score, &current_anonymous_user->High_Score, &current_anonymous_user->Time, 1)) {
					printf("User successfully added to the system!\n");
					printf("Go back to the login menu to login as register user!\n");
					exit = 1;
					free(current_anonymous_user);
				}
				else
					printf("This User is already in the system.\n");
			}
			break;
		case '2':
			//Start a new game and update the log file
			update_game_stats_to_log(0);
			New_Game();
			update_game_stats_to_log(1);
			break;
		case '3':
			//Print the leader board
			print_leader_board();
			printf("You can be in this leader board! All you got to do is to sign up!\n");
			break;
		case '4':
			//Exit from the menu to the login menu and update the log file
			Exit(AN_KEY);
			free(current_anonymous_user);
			current_anonymous_user = NULL;
			exit = 1;
			break;
		}
		if (choice != '4') {
			printf("Press any key to go back.");
			getchar();
		}
	}
	return 0;
}

//Print the trivia game in killer font
void Opening_ALL() {
	printf("\x1b[92m"" .----------------.  .----------------.  .----------------.                                                                 \n");
	printf("| .--------------. || .--------------. || .--------------. |                                                                \n");
	printf("| |  _________   | || |  ____  ____  | || |  _________   | |                                                                \n");
	printf("| | |  _   _  |  | || | |_   ||   _| | || | |_   ___  |  | |                                                                \n");
	printf("| | |_/ | | \\_|  | || |   | |__| |   | || |   | |_  \\_|  | |                                                                \n");
	printf("| |     | |      | || |   |  __  |   | || |   |  _|  _   | |                                                                \n");
	printf("| |    _| |_     | || |  _| |  | |_  | || |  _| |___/ |  | |                                                                \n");
	printf("| |   |_____|    | || | |____||____| | || | |_________|  | |       \n");
	printf("| |              | || |              | || |              | |    \n");
	printf("| '--------------' || '--------------' || '--------------' |    \n");
	printf(" '----------------'  '----------------'  '----------------'         \n");
	printf("     .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n");
	printf("    | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
	printf("    | |  _________   | || |  _______     | || |     _____    | || | ____   ____  | || |     _____    | || |      __      | |\n");
	printf("    | | |  _   _  |  | || | |_   __ \\    | || |    |_   _|   | || ||_  _| |_  _| | || |    |_   _|   | || |     /  \\     | |\n");
	printf("    | | |_/ | | \\_|  | || |   | |__) |   | || |      | |     | || |  \\ \\   / /   | || |      | |     | || |    / /\\ \\    | |\n");
	printf("    | |     | |      | || |   |  __ /    | || |      | |     | || |   \\ \\ / /    | || |      | |     | || |   / ____ \\   | |\n");
	printf("    | |    _| |_     | || |  _| |  \\ \\_  | || |     _| |_    | || |    \\ ' /     | || |     _| |_    | || | _/ /    \\ \\_ | |\n");
	printf("    | |   |_____|    | || | |____| |___| | || |    |_____|   | || |     \\_/      | || |    |_____|   | || ||____|  |____|| |\n");
	printf("    | |              | || |              | || |              | || |              | || |              | || |              | |\n");
	printf("    | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
	printf("     '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");
	printf("           .----------------.  .----------------.  .----------------.  .----------------.                                   \n");
	printf("          | .--------------. || .--------------. || .--------------. || .--------------. |                                  \n");
	printf("          | |    ______    | || |      __      | || | ____    ____ | || |  _________   | |                                  \n");
	printf("          | |  .' ___  |   | || |     /  \\     | || ||_   \\  /   _|| || | |_   ___  |  | |                                  \n");
	printf("          | | / .'   \\_|   | || |    / /\\ \\    | || |  |   \\/   |  | || |   | |_  \\_|  | |                                  \n");
	printf("          | | | |    ____  | || |   / ____ \\   | || |  | |\\  /| |  | || |   |  _|  _   | |                                  \n");
	printf("          | | \\ `.___]  _| | || | _/ /    \\ \\_ | || | _| |_\\/_| |_ | || |  _| |___/ |  | |                                  \n");
	printf("          | |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |                                  \n");
	printf("          | |              | || |              | || |              | || |              | |                                  \n");
	printf("          | '--------------' || '--------------' || '--------------' || '--------------' |                                  \n");
	printf("           '----------------'  '----------------'  '----------------'  '----------------'                                   \n");
}

//Print only "the" 
void Opening_The() {
	printf(" .----------------.  .----------------.  .----------------.                                                                 \n");
	printf("| .--------------. || .--------------. || .--------------. |                                                                \n");
	printf("| |  _________   | || |  ____  ____  | || |  _________   | |                                                                \n");
	printf("| | |  _   _  |  | || | |_   ||   _| | || | |_   ___  |  | |                                                                \n");
	printf("| | |_/ | | \\_|  | || |   | |__| |   | || |   | |_  \\_|  | |                                                                \n");
	printf("| |     | |      | || |   |  __  |   | || |   |  _|  _   | |                                                                \n");
	printf("| |    _| |_     | || |  _| |  | |_  | || |  _| |___/ |  | |                                                                \n");
	printf("| |   |_____|    | || | |____||____| | || | |_________|  | |       \n");
	printf("| |              | || |              | || |              | |    \n");
	printf("| '--------------' || '--------------' || '--------------' |    \n");
	printf(" '----------------'  '----------------'  '----------------'         \n");
}

//Print only "trivia"
void Opening_Trivia() {
	printf("     .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n");
	printf("    | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
	printf("    | |  _________   | || |  _______     | || |     _____    | || | ____   ____  | || |     _____    | || |      __      | |\n");
	printf("    | | |  _   _  |  | || | |_   __ \\    | || |    |_   _|   | || ||_  _| |_  _| | || |    |_   _|   | || |     /  \\     | |\n");
	printf("    | | |_/ | | \\_|  | || |   | |__) |   | || |      | |     | || |  \\ \\   / /   | || |      | |     | || |    / /\\ \\    | |\n");
	printf("    | |     | |      | || |   |  __ /    | || |      | |     | || |   \\ \\ / /    | || |      | |     | || |   / ____ \\   | |\n");
	printf("    | |    _| |_     | || |  _| |  \\ \\_  | || |     _| |_    | || |    \\ ' /     | || |     _| |_    | || | _/ /    \\ \\_ | |\n");
	printf("    | |   |_____|    | || | |____| |___| | || |    |_____|   | || |     \\_/      | || |    |_____|   | || ||____|  |____|| |\n");
	printf("    | |              | || |              | || |              | || |              | || |              | || |              | |\n");
	printf("    | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
	printf("     '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");
}

//Print only "game"
void Opening_Game() {
	printf("           .----------------.  .----------------.  .----------------.  .----------------.                                   \n");
	printf("          | .--------------. || .--------------. || .--------------. || .--------------. |                                  \n");
	printf("          | |    ______    | || |      __      | || | ____    ____ | || |  _________   | |                                  \n");
	printf("          | |  .' ___  |   | || |     /  \\     | || ||_   \\  /   _|| || | |_   ___  |  | |                                  \n");
	printf("          | | / .'   \\_|   | || |    / /\\ \\    | || |  |   \\/   |  | || |   | |_  \\_|  | |                                  \n");
	printf("          | | | |    ____  | || |   / ____ \\   | || |  | |\\  /| |  | || |   |  _|  _   | |                                  \n");
	printf("          | | \\ `.___]  _| | || | _/ /    \\ \\_ | || | _| |_\\/_| |_ | || |  _| |___/ |  | |                                  \n");
	printf("          | |  `._____.'   | || ||____|  |____|| || ||_____||_____|| || | |_________|  | |                                  \n");
	printf("          | |              | || |              | || |              | || |              | |                                  \n");
	printf("          | '--------------' || '--------------' || '--------------' || '--------------' |                                  \n");
	printf("           '----------------'  '----------------'  '----------------'  '----------------'                                   \n");
}

//Print "by triviani"
void BY_Triviani() {
	system("cls");
	printf("\x1b[96m""oooooooooo.                   ooooooooooooo           o8o               o8o                         o8o  \n");
	printf("`888'   `Y8b                  8'   888   `8           `\"'               `\"'                         `\"'\n");
	printf(" 888     888 oooo    ooo           888      oooo d8b oooo  oooo    ooo oooo   .oooo.   ooo. .oo.   oooo  \n");
	printf(" 888oooo888'  `88.  .8'            888      `888\"\"8P `888   `88.  .8'  `888  `P  )88b  `888P\"Y88b  `888\n");
	printf(" 888    `88b   `88..8'             888       888      888    `88..8'    888   .oP\"888   888   888   888\n");
	printf(" 888    .88P    `888'              888       888      888     `888'     888  d8(  888   888   888   888  \n");
	printf("o888bood8P'      .8'              o888o     d888b    o888o     `8'     o888o `Y888\"\"8o o888o o888o o888o \n");
	printf("             .o..P'                                                                                      \n");
	printf("             `Y8P'                                                                                       \n""\x1b[0m");

}

//Wait funtion that wait n secondes
int Wait(int secs) {
	unsigned int retTime = (unsigned int)time(0) + secs;
	while (time(0) < retTime);
	return 1;
}

//The open animation
void Open_Animiation() {
	Opening_ALL();
	Wait(4);
	system("cls");
	Opening_The();
	Opening_Trivia();
	Wait(1);
	system("cls");
	Opening_The();
	Wait(1);
	system("cls");
	BY_Triviani();
	Wait(4);
	system("cls");
}

//Main menu function that operate by the user key
int Menu(int user_key) {
	switch (user_key){
		//0 for admin menu
	case(ADMIN_KEY):
		return Admin_Menu();
		break;
		//1 for user menu
	case(REG_KEY):
		return User_Menu();
		break;
		//2 for anonymous menu
	case(AN_KEY):
		Print_To_Log_File("Anonymous user logged in to the system.");
		return Anonymous_Menu();
		break;
	default:
		break;
	}
	return 0;
}

//Login menu
void LogIn_Menu() {
	char term;
	int permission, choice, valid;
	while (1) {
		system("cls");
		permission = 0;
		//Print the menu
		printf("\t \x1b[4mWelcome to The Trivia Game\x1b[24m\n");
		printf("\t  \x1b[4mPlease login to continue\x1b[24m");
		printf("\n\n1) Log in as Admin");
		printf("\n2) Log in as regisered user");
		printf("\n3) Log in as anonymous user");
		printf("\n4) Sign Up");
		printf("\n5) Run UnitTest");
		//Get user choice
		do {
			printf("\nYour choice:");
			valid = scanf("%d%c", &choice, &term);
			if (valid != 2 || term != '\n')
				while (getchar() != '\n');
			if (choice > 5 || choice < 0 || valid != 2 || term != '\n')
				printf("Worng input. Try again");
		} while (valid != 2 || term != '\n' || (choice > 5 || choice < 0));
		switch (choice) {
			//Call to the admin/user login in order to give premission to enter to each menu
			//No login needed for the anonymous menu
		case 1:
			system("cls");
			if (Admin_login())
				permission = 1;
			else {
				printf("\nWorng id or password. You will return to the login menu in 4 seconds.");
				Wait(4);
			}
			break;
		case 2:
			system("cls");
			if (Reg_user_login())
				permission = 1;
			else {
				printf("\nWorng nickname or password. You will return to the login menu in 4 seconds.");
				Wait(4);
			}
			break;
		case 3:
			current_anonymous_user = (Anonymous_User*)malloc(sizeof(Anonymous_User));
			current_anonymous_user->High_Score = 0;
			current_anonymous_user->Time = 0;
			permission = 1;
			break;
		case 4:
			//Sign up to the system
			system("cls");
			if(add_user(NULL, NULL, NULL, 0))
				printf("User successfully added to the system!");
			printf("\nPress any key to go back.");
			getchar();
			break;
		case 5:
			//Run the unit tests
			system("cls");
			run_unit_tests();
			system("pause");
			return;
		}
		if (choice == 0) {
			return;
		}
		system("cls");
		//If the user/admin was successfully login to the system, transfer them to their menu
		if (permission)
			if ((Menu(choice - 1)) == 1)
				return;
	}
}

//check if file is empty
int isEmpty(char* name) {
	//open file to reading 
	FILE* file = fopen(name, "r");
	//if the file is not exist, the file is empty
	if (!file) return 1;
	//get file offset
	long savedOffset = ftell(file);
	//shift to the end of the file
	fseek(file, 0, SEEK_END);
	//check if the file end is like the begining
	if (ftell(file) == 0) {
		fclose(file);
		return 1;
	}
	fseek(file, savedOffset, SEEK_SET);
	fclose(file);
	return 0;
}

void Register_user(Reg_User user) {
	FILE* user_file = NULL;
	//open file to append mode
	user_file = fopen(Reg_File, "a");
	//check if the user file opened correctly
	if (!user_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	//print the user parameters to the file
	fprintf(user_file, "%s\n%s\n%s\n%d\n%d\n%d\n",
		user.Nickname,
		user.Password,
		user.Full_Name,
		user.High_Score,
		user.Last_Score,
		user.Last_Time);
	//close the file
	fclose(user_file);
}

int user_verification(String nickname, String password) {
	Reg_User user;
	FILE* user_file = NULL;
	char n[50], p[50], f[50];
	//check if the user file is empty
	if (isEmpty(Reg_File)) {
		return 0;
	}
	//oprn user file to reading
	user_file = fopen(Reg_File, "r");
	if (!user_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return 0;
	}
	//read the file to its end
	while (!feof(user_file)) {
		//get values from the file to the parameters
		fscanf(user_file, "%s\n", n);
		strcpy(user.Nickname, n);
		fscanf(user_file, "%s\n", p);
		strcpy(user.Password, p);
		fgets(f, 50, user_file);
		strcpy(user.Full_Name, f);
		fscanf(user_file, "%d", &user.High_Score);
		fscanf(user_file, "%d", &user.Last_Score);
		fscanf(user_file, "%d\n", &user.Last_Time);
		//if the password given, check if the user nickname and the password match the user
		if (password != NULL) {
			if (!(strcmp(user.Nickname, nickname) || strcmp(user.Password, password))) {
				//if yes, close the file and return 1
				fclose(user_file);
				return 1;
			}
		}
		else {
			//if the password not given, check only if the user nickname match
			if (!(strcmp(user.Nickname, nickname))) {
				//if yes, close the file and return 1
				fclose(user_file);
				return 1;
			}
		}
	}
	//if the wile loop didnt found and user that match the user id or password, return 0
	fclose(user_file);
	return 0;
}

//get user by its nickname
int get_user(String nickname, Reg_User* ans) {
	Reg_User user;
	FILE* user_file = NULL;
	char name[50], pass[50], full_name[50];
	//check if the user file is empty
	if (isEmpty(Reg_File)) {
		return 0;
	}
	//open user file to reading mode
	user_file = fopen(Reg_File, "r");
	if (!user_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return 0;
	}
	//read the file to its end
	while (!feof(user_file)) {
		//get values to the parameters of the user instance
		fscanf(user_file, "%s", name);
		strcpy(user.Nickname, name);
		fscanf(user_file, "%s\n", pass);
		strcpy(user.Password, pass);
		fgets(full_name, 50, user_file);
		full_name[strlen(full_name) - 1] = '\0';
		strcpy(user.Full_Name, full_name);
		fscanf(user_file, "%d", &user.High_Score);
		fscanf(user_file, "%d", &user.Last_Score);
		fscanf(user_file, "%d\n", &user.Last_Time);
		//if the user instance's nickname match the nickname given
		if (!(strcmp(user.Nickname, nickname))) {
			//close the file
			fclose(user_file);
			//return by ptr the user.
			*ans = user;
			return 1;
		}
	}
	//close the file.
	fclose(user_file);
	return 0;
}

//reigster admin to the system
void Register_Admin(Admin admin) {
	FILE* admins_file = NULL;
	//open admin file to append
	admins_file = fopen(Admin_File, "a");
	//check if the file opened
	if (!admins_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	//print admin details to the file
	fprintf(admins_file, "%s\n%s\n%s\n",
		admin.ID,
		admin.Name,
		admin.Password);
	fclose(admins_file);
}

//varify admin info
int admin_verification(String ID, String password) {
	//create instance for the admin
	Admin admin;
	FILE* admin_file = NULL;
	char i[50], n[50], p[50];
	//check if the admin file is empty
	if (isEmpty(Admin_File)) {
		return 0;
	}
	//open the admins file to reading
	admin_file = fopen(Admin_File, "r");
	if (!admin_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return 0;
	}
	//read the file to the end
	while (!feof(admin_file)) {
		//move parameters from the file to the admin instance
		fscanf(admin_file, "%s\n", i);
		strcpy(admin.ID, i);
		fgets(n, 50, admin_file);
		strcpy(admin.Name, n);
		fscanf(admin_file, "%s\n", p);
		strcpy(admin.Password, p);
		//if password given
		if (password != NULL) {
			//check if the admin ID and the password match the file records, return 1 
			if (!(strcmp(admin.ID, ID) || strcmp(admin.Password, password))) {
				//close the file
				fclose(admin_file);
				return 1;
			}
		}
		//if password not given
		else {
			//check if the admin ID is in the file
			if (!(strcmp(admin.ID, ID))) {
				//close file
				fclose(admin_file);
				//return 1
				return 1;
			}
		}

	}
	//the function didnt found any admin with ID or password the match the parameters
	//close the file
	fclose(admin_file);
	//return 0
	return 0;
}

//remove admin from the file
void remove_admin(String ID) {
	Admin ** admin_list;
	int indx;
	int c = 0;
	FILE* admin_file = NULL;
	char i[50], n[50], p[50];
	admin_list = (Admin**)malloc(sizeof(Admin*)*c);
	//open admins file to read mode
	admin_file = fopen(Admin_File, "r");
	if (!admin_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	//read file to its end
	while (!feof(admin_file)) {
		//get values from the file to the instance
		fscanf(admin_file, "%s\n", i);
		fgets(n, 50, admin_file);
		n[strlen(n) - 1] = '\0';
		fscanf(admin_file, "%s\n", p);
		//check if the admin id match the id we want to delete
		if (strcmp(i, ID)) {
			//if not add the admin to the temp admin array
			c++;
			admin_list = (Admin**)realloc(admin_list, c * sizeof(Admin*));
			admin_list[c - 1] = (Admin*)malloc(sizeof(Admin));
			strcpy(admin_list[c - 1]->ID, i);
			strcpy(admin_list[c - 1]->Password, p);
			strcpy(admin_list[c - 1]->Name, n);
		}
	}
	//close the file
	fclose(admin_file);
	//clean the file
	admin_file = fopen(Admin_File, "w");
	fclose(admin_file);
	//register the admins(without the admin we wanted to delete)
	for (indx = 0; indx < c; indx++) {
		Register_Admin(*admin_list[indx]);
		//after the registration, free the allocated memory of the admin
		free(admin_list[indx]);
	}
	//free allocated memory
	free(admin_list);
}

//change admin details
void Change_admin_info(Admin *admin) {
	//create dynamic array of admins
	Admin ** admin_list;
	int indx;
	int c = 0;
	FILE* admin_file = NULL;
	char i[50], n[50], p[50];
	//set the admin array
	admin_list = (Admin**)malloc(sizeof(Admin*)*c);
	//open the admin file to reading
	admin_file = fopen(Admin_File, "r");
	if (!admin_file) {//check if the admins file open correctly
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	//read the file to its end
	while (!feof(admin_file)) {
		//move values from the file to the parameters
		fscanf(admin_file, "%s\n", i);
		fgets(n, 50, admin_file);
		n[strlen(n) - 1] = '\0';
		fscanf(admin_file, "%s\n", p);
		//check if the admin id match the admin we want to change
		if (strcmp(i, admin->ID)) {
			//if the admin is not the one we want to change
			c++;
			//add the admin to the temp array with no change
			admin_list = (Admin**)realloc(admin_list, c * sizeof(Admin*));
			admin_list[c - 1] = (Admin*)malloc(sizeof(Admin));
			strcpy(admin_list[c - 1]->ID, i);
			strcpy(admin_list[c - 1]->Password, p);
			strcpy(admin_list[c - 1]->Name, n);
		}
		else {
			//if the admin id match the id we want to change, override the parametrs of the admin to the new.
			c++;
			admin_list = (Admin**)realloc(admin_list, c * sizeof(Admin*));
			admin_list[c - 1] = (Admin*)malloc(sizeof(Admin));
			strcpy(admin_list[c - 1]->ID, admin->ID);
			strcpy(admin_list[c - 1]->Password, admin->Password);
			strcpy(admin_list[c - 1]->Name, admin->Name);
		}
	}
	//clean the admin file
	fclose(admin_file);
	admin_file = fopen(Admin_File, "w");
	fclose(admin_file);
	//reregister the admins in the temp array to the admins file.
	for (indx = 0; indx < c; indx++) {
		Register_Admin(*admin_list[indx]);
		//after registration, free the allocated memory
		free(admin_list[indx]);
	}
	//free the allocated memory
	free(admin_list);
}

//change user details
void Change_user_info(Reg_User *user) {
	Reg_User ** user_list;
	int indx;
	int c = 0, hs, ls, lt;
	FILE* user_file = NULL;
	char n[50], p[50], f[50];
	user_list = (Reg_User**)malloc(sizeof(Reg_User*)*c);
	user_file = fopen(Reg_File, "r");
	if (!user_file) {
		printf("** ERROR : FILE UNWRITEABLE **\n");
	}
	while (!feof(user_file)) {
		fscanf(user_file, "%s", n);
		fscanf(user_file, "%s\n", p);
		fgets(f, 50, user_file);
		f[strlen(f) - 1] = '\0';
		fscanf(user_file, "%d", &hs);
		fscanf(user_file, "%d", &ls);
		fscanf(user_file, "%d\n", &lt);
		if (strcmp(n, user->Nickname)) {
			c++;
			user_list = (Reg_User**)realloc(user_list, c * sizeof(Reg_User*));
			user_list[c - 1] = (Reg_User*)malloc(sizeof(Reg_User));
			strcpy(user_list[c - 1]->Nickname, n);
			strcpy(user_list[c - 1]->Password, p);
			strcpy(user_list[c - 1]->Full_Name, f);
			user_list[c - 1]->High_Score = hs;
			user_list[c - 1]->Last_Score = ls;
			user_list[c - 1]->Last_Time = lt;
		}
		else {
			c++;
			user_list = (Reg_User**)realloc(user_list, c * sizeof(Reg_User*));
			user_list[c - 1] = (Reg_User*)malloc(sizeof(Reg_User));
			strcpy(user_list[c - 1]->Nickname, user->Nickname);
			strcpy(user_list[c - 1]->Password, user->Password);
			strcpy(user_list[c - 1]->Full_Name, user->Full_Name);
			user_list[c - 1]->High_Score = user->High_Score;
			user_list[c - 1]->Last_Score = user->Last_Score;
			user_list[c - 1]->Last_Time = user->Last_Time;
		}
	}
	fclose(user_file);
	user_file = fopen(Reg_File, "w");
	fclose(user_file);
	for (indx = 0; indx < c; indx++) {
		Register_user(*user_list[indx]);
		free(user_list[indx]);
	}
	free(user_list);
}

//remove user from the system by its nickname
void remove_user(String nickname) {
	Reg_User ** user_list;
	int indx;
	int c = 0, hs, ls, lt;
	FILE* user_file = NULL;
	char n[50], p[50], f[50];
	user_list = (Reg_User**)malloc(sizeof(Reg_User*)*c);
	//open users file to read mode
	user_file = fopen(Reg_File, "r");
	//check if the user file opened
	if (!user_file) {
		printf("** ERROR : FILE UNWRITEABLE **\n");
	}
	//read the file to its end
	while (!feof(user_file)) {
		//get values from the file to the instance
		fscanf(user_file, "%s", n);
		fscanf(user_file, "%s\n", p);
		fgets(f, 50, user_file);
		f[strlen(f) - 1] = '\0';
		fscanf(user_file, "%d", &hs);
		fscanf(user_file, "%d", &ls);
		fscanf(user_file, "%d\n", &lt);
		//check if the user nickname match the nickname we want to delete
		if (strcmp(n, nickname)) {
			//if not, add the user to the temp array
			c++;
			user_list = (Reg_User**)realloc(user_list, c * sizeof(Reg_User*));
			user_list[c - 1] = (Reg_User*)malloc(sizeof(Reg_User));
			strcpy(user_list[c - 1]->Nickname, n);
			strcpy(user_list[c - 1]->Password, p);
			strcpy(user_list[c - 1]->Full_Name, f);
			user_list[c - 1]->High_Score = hs;
			user_list[c - 1]->Last_Score = ls;
			user_list[c - 1]->Last_Time = lt;
		}
	}
	//close the file
	fclose(user_file);
	//clean the file
	user_file = fopen(Reg_File, "w");
	fclose(user_file);
	//register the users from the temp arrray to the system
	for (indx = 0; indx < c; indx++) {
		Register_user(*user_list[indx]);
		//after registrration,free allocated memory
		free(user_list[indx]);
	}
	//free allocated memory
	free(user_list);
}

//get how many users are in the system
int User_counter() {
	Reg_User* user = (Reg_User*)malloc(sizeof(Reg_User));
	FILE* user_file = NULL;
	int c = 0;
	char n[50], p[50], f[50];
	//check if the file is empty
	if (isEmpty(Reg_File)) {
		free(user);
		return 0;
	}
	//open file to reading
	user_file = fopen(Reg_File, "r");
	if (!user_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return -1;
	}
	//read the file to its end
	while (!feof(user_file)) {
		//get values from the file to user instance
		fscanf(user_file, "%s", n);
		strcpy(user->Nickname, n);
		fscanf(user_file, "%s\n", p);
		strcpy(user->Password, p);
		fgets(f, 50, user_file);
		f[strlen(f) - 1] = '\0';
		strcpy(user->Full_Name, f);
		fscanf(user_file, "%d", &user->High_Score);
		fscanf(user_file, "%d", &user->Last_Score);
		fscanf(user_file, "%d\n", &user->Last_Time);
		//increase the counter by 1
		c++;
	}
	//free allocated memory
	free(user);
	//close the file
	fclose(user_file);
	//return the counter
	return c;
}

//get how many admins are in the system
int Admin_counter() {
	//create admin ptr and allocate memory for it.
	Admin* admin = (Admin*)malloc(sizeof(Admin));
	FILE* admin_file = NULL;
	char i[50], p[50], n[50];
	int c = 0;
	//check if the admins file is empty
	if (isEmpty(Admin_File)) {
		return -1;
	}
	//open the file to read mode
	admin_file = fopen(Admin_File, "r");
	if (!admin_file) {
		//check if the file open correctly
		printf("** ERROR : FILE UNWRITEABLE **");
		return -1;
	}
	//read the file to the end
	while (!feof(admin_file)) {
		//read admins paramters to the admin instance
		fscanf(admin_file, "%s\n", i);
		strcpy(admin->ID, i);
		fgets(n, 50, admin_file);
		n[strlen(n) - 1] = '\0';
		strcpy(admin->Name, n);
		fscanf(admin_file, "%s\n", p);
		strcpy(admin->Password, p);
		//increase counter for every intartion in the file
		c++;
	}
	//free allocated memory and close the file.
	free(admin);
	fclose(admin_file);
	return c;
}

int New_Question_List_In_Ranks(Rank* R)
{
	R->Q_list = (Array*)malloc(sizeof(Array)); // Defining memory for Question list in every rank
	R->Q_list->Values = NULL;
	R->Q_list->length = 0;
	return 1;
}

int Pull_Questions_From_File(Rank * R, String FileName)
{
	FILE* ranks_file = NULL;
	int count = 0, num = 0, flag_matilda = 0;
	New_Question_List_In_Ranks(R);
	char s1, str[256];
	ranks_file = fopen(FileName, "r");
	do {
		s1 = getc(ranks_file);
		if (s1 == '~') // Tilde will mark the start of the question list in the database (in our case, the ranks file)
			flag_matilda = 1;
	} while (flag_matilda == 0 && !feof(ranks_file));
	while (!feof(ranks_file))
	{
		if (count == 0)
		{
			R->Q_list->Values = (Question**)malloc(sizeof(Question*));
			R->Q_list->Values[0] = (Question*)malloc(sizeof(Question));
			count = 1;
		}
		else
		{
			count++;
			R->Q_list->Values = (Question**)realloc(R->Q_list->Values, sizeof(Question*)*(count));
			R->Q_list->Values[count - 1] = (Question*)malloc(sizeof(Question));
		}
		//Pulling the question from the file to the new memory
		fscanf(ranks_file, "%d\n", &num);
		R->Q_list->Values[count - 1]->Q_Number = num;
		fscanf(ranks_file, "%d\n", &num);
		R->Q_list->Values[count - 1]->Basic_Time = num;
		fgets(str, 256, ranks_file);
		str[strlen(str) - 1] = '\0';
		strcpy(R->Q_list->Values[count - 1]->content, str);
		fscanf(ranks_file, "%d\n", &num);
		R->Q_list->Values[count - 1]->Right_Answer = num;
		s1 = getc(ranks_file);
	}
	fclose(ranks_file);
	R->Q_list->length = count;
	return 1;
}

int Build_New_Rank(Rank* R, String FileName) { // Building a rank at the start of the system
	FILE* ranks_file = NULL;
	char str[256];
	// Getting the information from the rank file about the rank details
	ranks_file = fopen(FileName, "r");
	fgets(str, 256, ranks_file);
	strcpy(R->Rank_Title, str);
	fscanf(ranks_file, "%d\n", &(R->Added_Time));
	fscanf(ranks_file, "%d\n", &(R->Score));
	fclose(ranks_file);
	return Pull_Questions_From_File(R, FileName); // Building the Question list with the information taken from the rank's file
}

int Pre_Start_Of_The_System() // Will oparate at the start of the system and will build all the ranks
{
	// Defining the memory for all the ranks at the start of the system
	A = (Rank*)malloc(sizeof(Rank));
	B = (Rank*)malloc(sizeof(Rank));
	C = (Rank*)malloc(sizeof(Rank));
	D = (Rank*)malloc(sizeof(Rank));
	E = (Rank*)malloc(sizeof(Rank));
	F = (Rank*)malloc(sizeof(Rank));
	G = (Rank*)malloc(sizeof(Rank));
	H = (Rank*)malloc(sizeof(Rank));
	I = (Rank*)malloc(sizeof(Rank));
	J = (Rank*)malloc(sizeof(Rank));
	// Defining the ranks for the system
	if (A != NULL) {
		A->Rank_Symbol = 'A';
		Build_New_Rank(A, Rank_A);
	}
	else return 0;
	if (B != NULL) {
		B->Rank_Symbol = 'B';
		Build_New_Rank(B, Rank_B);
	}
	else return 0;
	if (C != NULL) {
		C->Rank_Symbol = 'C';
		Build_New_Rank(C, Rank_C);
	}
	else return 0;
	if (D != NULL) {
		D->Rank_Symbol = 'D';
		Build_New_Rank(D, Rank_D);
	}
	else return 0;
	if (E != NULL) {
		E->Rank_Symbol = 'E';
		Build_New_Rank(E, Rank_E);
	}
	else return 0;
	if (F != NULL) {
		F->Rank_Symbol = 'F';
		Build_New_Rank(F, Rank_F);
	}
	else return 0;
	if (G != NULL) {
		G->Rank_Symbol = 'G';
		Build_New_Rank(G, Rank_G);
	}
	else return 0;
	if (H != NULL) {
		H->Rank_Symbol = 'H';
		Build_New_Rank(H, Rank_H);
	}
	else return 0;
	if (I != NULL) {
		I->Rank_Symbol = 'I';
		Build_New_Rank(I, Rank_I);
	}
	else return 0;
	if (J != NULL) {
		J->Rank_Symbol = 'J';
		Build_New_Rank(J, Rank_J);
	}
	else return 0;
	return 1;
}

void Release_Rank_Memory(Rank *R) // Releasing the rank's memory from the system
{
	for (int i = 0; i < R->Q_list->length; i++)
	{
		free(R->Q_list->Values[i]);
	}
	free(R->Q_list->Values);
	free(R->Q_list);
	free(R);
}

void End_Of_The_System() // At the end of the system, this function will release the memory located in the system
{
	Release_Rank_Memory(A);
	Release_Rank_Memory(B);
	Release_Rank_Memory(C);
	Release_Rank_Memory(D);
	Release_Rank_Memory(E);
	Release_Rank_Memory(F);
	Release_Rank_Memory(G);
	Release_Rank_Memory(H);
	Release_Rank_Memory(I);
	Release_Rank_Memory(J);
}

int Check_Question_Existence_In_Ranks(Rank* R, Question* Q) // Checking if the question given exist in rank
{
	if (R->Q_list == NULL || Q == NULL) return 0;
	for (int i = 0; i < R->Q_list->length; i++)
		if (R->Q_list->Values[i]->Q_Number == Q->Q_Number) return 1;
	return 0;
}

void Delete_Question_In_Ranks(Rank* R, Question* Q) // Deleting a question from the rank's list by getting a Rank and a Question structs
{
	FILE* ranks_file = NULL;
	String FileName = NULL;
	int tmp = 0, indx = 0;
	Question** temp = NULL;
	if (R->Q_list->Values == NULL) // checking if the rank has any questions
	{
		printf("No questions in the rank\n");
		return;
	}
	temp = (Question**)malloc(sizeof(Question*)*(R->Q_list->length - 1));
	for (int i = 0; i < R->Q_list->length; i++) // Getting the values from the original array for deleting
	{
		if (R->Q_list->Values[i]->Q_Number != Q->Q_Number)
		{
			R->Q_list->Values[i]->Q_Number = tmp + 1;
			temp[tmp] = R->Q_list->Values[i];
			tmp++;
		}
		else {
			indx = i;
		}
	}
	free(R->Q_list->Values[indx]); // Deleting the question from the system
	free(R->Q_list->Values);
	if (R->Q_list->length != 1) // If The rank had only 1 question, the Question list will be NULL
	{
		R->Q_list->Values = (Question**)malloc(sizeof(Question*)*(tmp));
		for (int i = 0; i < tmp; i++)
			R->Q_list->Values[i] = temp[i];
	}
	else R->Q_list->Values = NULL;
	free(temp);
	R->Q_list->length--;
	switch (R->Rank_Symbol) // Handeling every rank
	{
	case('A'):
		ranks_file = fopen(Rank_A, "w"); // By opening and closing the file, we delete all the information in the rank's file
		fclose(ranks_file);
		FileName = Rank_A;
		break;
	case('B'):
		ranks_file = fopen(Rank_B, "w");
		fclose(ranks_file);
		FileName = Rank_B;
		break;
	case('C'):
		ranks_file = fopen(Rank_C, "w");
		fclose(ranks_file);
		FileName = Rank_C;
		break;
	case('D'):
		ranks_file = fopen(Rank_D, "w");
		fclose(ranks_file);
		FileName = Rank_D;
		break;
	case('E'):
		ranks_file = fopen(Rank_E, "w");
		fclose(ranks_file);
		FileName = Rank_E;
		break;
	case('F'):
		ranks_file = fopen(Rank_F, "w");
		fclose(ranks_file);
		FileName = Rank_F;
		break;
	case('G'):
		ranks_file = fopen(Rank_G, "w");
		fclose(ranks_file);
		FileName = Rank_G;
		break;
	case('H'):
		ranks_file = fopen(Rank_H, "w");
		fclose(ranks_file);
		FileName = Rank_H;
		break;
	case('I'):
		ranks_file = fopen(Rank_I, "w");
		fclose(ranks_file);
		FileName = Rank_I;
		break;
	case('J'):
		ranks_file = fopen(Rank_J, "w");
		fclose(ranks_file);
		FileName = Rank_J;
		break;
	}
	ranks_file = fopen(FileName, "w"); // Writing the rank's details to his file after deleting the question
	fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
		R->Rank_Title,
		R->Added_Time,
		R->Score);
	fclose(ranks_file);
	for (int i = 0; i < tmp; i++)
	{
		Write_Question_To_File(*R, i, FileName); // Writing the questions list to the rank's file
	}
}

void Add_Question(char RankSymbol, int QBasicTime, char* Qcontent, int QRightAnswer) // Adding a question to a rank by getting the question details
{
	char msg[100] = "Admin ";
	Question* Q = (Question*)malloc(sizeof(Question));
	Q->Basic_Time = QBasicTime;
	Decode(Qcontent); // Decoding the input of the user
	strcpy(Q->content, Qcontent);
	Q->Right_Answer = QRightAnswer;
	switch (RankSymbol) // For the rank chosen, we will add the question with the Add_Question_To_Ranks function
	{
	case('A'):
		Q->Q_Number = A->Q_list->length + 1; // The number of the Question will be represented by the number of questions in the rank +1
		Add_Question_To_Ranks(A, Q);
		break;
	case('B'):
		Q->Q_Number = B->Q_list->length + 1;
		Add_Question_To_Ranks(B, Q);
		break;
	case('C'):
		Q->Q_Number = C->Q_list->length + 1;
		Add_Question_To_Ranks(C, Q);
		break;
	case('D'):
		Q->Q_Number = D->Q_list->length + 1;
		Add_Question_To_Ranks(D, Q);
		break;
	case('E'):
		Q->Q_Number = E->Q_list->length + 1;
		Add_Question_To_Ranks(E, Q);
		break;
	case('F'):
		Q->Q_Number = F->Q_list->length + 1;
		Add_Question_To_Ranks(F, Q);
		break;
	case('G'):
		Q->Q_Number = G->Q_list->length + 1;
		Add_Question_To_Ranks(G, Q);
		break;
	case('H'):
		Q->Q_Number = H->Q_list->length + 1;
		Add_Question_To_Ranks(H, Q);
		break;
	case('I'):
		Q->Q_Number = I->Q_list->length + 1;
		Add_Question_To_Ranks(I, Q);
		break;
	case('J'):
		Q->Q_Number = J->Q_list->length + 1;
		Add_Question_To_Ranks(J, Q);
		break;
	}
	free(Q);
	strcat(msg, current_admin->Name);
	strcat(msg, " added a new question to rank ");
	msg[strlen(msg)] = RankSymbol;
	msg[strlen(msg)] = '.';
	msg[strlen(msg) + 1] = '\0';
	Print_To_Log_File(msg);
}

Question Delete_Question_For_New(char RankSymbol, int QuestionNumber) // Same as Delete_Question but modefied for the Change_Question_Rank function
{
	Question* Q = NULL; // A pointer to the question who is destenyed to be deleted
	Question NewQ; // If the question dosn'et exist in the rank, the the function will return -1 at all the question values
	NewQ.Q_Number = -1;
	NewQ.Basic_Time = -1;
	NewQ.Right_Answer = -1;
	switch (RankSymbol)
	{
	case('A'):
		for (int i = 0; i < A->Q_list->length; i++)
		{
			if (A->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = A->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(A, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		// Getting the information of the deleted question to the adding of it at Change_Question_Rank function
		NewQ.Q_Number = Q->Q_Number; 
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(A, Q); // Deleting the question from the rank (the same is applied for all the ranks
		break;
	case('B'):
		for (int i = 0; i < B->Q_list->length; i++)
		{
			if (B->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = B->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(B, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(B, Q);
		break;
	case('C'):
		for (int i = 0; i < C->Q_list->length; i++)
		{
			if (C->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = C->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(C, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(C, Q);
		break;
	case('D'):
		for (int i = 0; i < D->Q_list->length; i++)
		{
			if (D->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = D->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(D, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(D, Q);
		break;
	case('E'):
		for (int i = 0; i < E->Q_list->length; i++)
		{
			if (E->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = E->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(E, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(E, Q);
		break;
	case('F'):
		for (int i = 0; i < F->Q_list->length; i++)
		{
			if (F->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = F->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(F, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(F, Q);
		break;
	case('G'):
		for (int i = 0; i < G->Q_list->length; i++)
		{
			if (G->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = G->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(G, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(G, Q);
		break;
	case('H'):
		for (int i = 0; i < H->Q_list->length; i++)
		{
			if (H->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = H->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(H, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(H, Q);
		break;
	case('I'):
		for (int i = 0; i < I->Q_list->length; i++)
		{
			if (I->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = I->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(I, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(I, Q);
		break;
	case('J'):
		for (int i = 0; i < J->Q_list->length; i++)
		{
			if (J->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = J->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(J, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return NewQ;
		}
		NewQ.Q_Number = Q->Q_Number;
		NewQ.Basic_Time = Q->Basic_Time;
		strcpy(NewQ.content, Q->content);
		NewQ.Right_Answer = Q->Right_Answer;

		Delete_Question_In_Ranks(J, Q);
		break;
	}
	return NewQ;
}

void Delete_Question(char RankSymbol, int QuestionNumber) // Deleting a Question from the rank with the information given
{
	char msg[100] = "Admin ";
	Question* Q = NULL; // Pointer for the question to delete
	switch (RankSymbol)
	{
	case('A'):
		for (int i = 0; i < A->Q_list->length; i++)
		{
			if (A->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = A->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(A, Q)) // checking if the question exist in the rank
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(A, Q); // Deleting the question
		break;
	case('B'):
		for (int i = 0; i < B->Q_list->length; i++)
		{
			if (B->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = B->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(B, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(B, Q);
		break;
	case('C'):
		for (int i = 0; i < C->Q_list->length; i++)
		{
			if (C->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = C->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(C, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(C, Q);
		break;
	case('D'):
		for (int i = 0; i < D->Q_list->length; i++)
		{
			if (D->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = D->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(D, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(D, Q);
		break;
	case('E'):
		for (int i = 0; i < E->Q_list->length; i++)
		{
			if (E->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = E->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(E, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(E, Q);
		break;
	case('F'):
		for (int i = 0; i < F->Q_list->length; i++)
		{
			if (F->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = F->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(F, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(F, Q);
		break;
	case('G'):
		for (int i = 0; i < G->Q_list->length; i++)
		{
			if (G->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = G->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(G, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(G, Q);
		break;
	case('H'):
		for (int i = 0; i < H->Q_list->length; i++)
		{
			if (H->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = H->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(H, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(H, Q);
		break;
	case('I'):
		for (int i = 0; i < I->Q_list->length; i++)
		{
			if (I->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = I->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(I, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(I, Q);
		break;
	case('J'):
		for (int i = 0; i < J->Q_list->length; i++)
		{
			if (J->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = J->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(J, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Delete_Question_In_Ranks(J, Q);
		break;
	}
	strcat(msg, current_admin->Name);
	strcat(msg, " deleted a question from rank ");
	msg[strlen(msg)] = RankSymbol;
	msg[strlen(msg)] = '.';
	msg[strlen(msg) + 1] = '\0';
	Print_To_Log_File(msg);
}

void Write_Question_To_File(Rank R, int index, String FileName) // Writing a question to the file
{
	FILE* ranks_file = NULL;
	ranks_file = fopen(FileName, "a");
	if (!ranks_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	fprintf(ranks_file, "~%d\n%d\n%s\n%d\n",
		R.Q_list->Values[index]->Q_Number,
		R.Q_list->Values[index]->Basic_Time,
		R.Q_list->Values[index]->content,
		R.Q_list->Values[index]->Right_Answer);
	fclose(ranks_file);
}

void Add_Question_To_Ranks(Rank* R, Question* Q) // Adding a question to the rank with the given rank and question structs
{
	// First adding it to the Question list in the rank
	if (R->Q_list->length == 0){
		R->Q_list->Values = (Question**)malloc(sizeof(Question*));
		R->Q_list->length = 1;
		R->Q_list->Values[R->Q_list->length - 1] = (Question*)malloc(sizeof(Question));
	}
	else{
		R->Q_list->Values = (Question**)realloc(R->Q_list->Values, sizeof(Question*)*(R->Q_list->length + 1));
		R->Q_list->Values[R->Q_list->length] = (Question*)malloc(sizeof(Question));
		(R->Q_list->length)++;
	}

	R->Q_list->Values[R->Q_list->length - 1]->Basic_Time = Q->Basic_Time;
	strcpy(R->Q_list->Values[R->Q_list->length - 1]->content, Q->content);
	R->Q_list->Values[R->Q_list->length - 1]->Q_Number = R->Q_list->length;
	R->Q_list->Values[R->Q_list->length - 1]->Right_Answer = Q->Right_Answer;
	switch (R->Rank_Symbol)
	{
	case('A'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_A); // Writing the question to the file with a specific function
		break;
	case('B'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_B);
		break;
	case('C'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_C);
		break;
	case('D'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_D);
		break;
	case('E'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_E);
		break;
	case('F'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_F);
		break;
	case('G'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_G);
		break;
	case('H'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_H);
		break;
	case('I'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_I);
		break;
	case('J'):
		Write_Question_To_File(*R, R->Q_list->length - 1, Rank_J);
		break;
	}
}

void Change_Rank_Added_Time_For_Rank(Rank* R, int Time) // Changing the rank added time
{
	FILE* ranks_file = NULL;
	R->Added_Time = Time;
	switch (R->Rank_Symbol)
	{
	case('A'): // After changing the ranks added time, we will rewrite the rank to the ranks file
		ranks_file = fopen(Rank_A, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_A, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_A);
		}
		break;
	case('B'):
		ranks_file = fopen(Rank_B, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_B, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_B);
		}
		break;
	case('C'):
		ranks_file = fopen(Rank_C, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_C, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_C);
		}
		break;
	case('D'):
		ranks_file = fopen(Rank_D, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_D, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_D);
		}
		break;
	case('E'):
		ranks_file = fopen(Rank_E, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_E, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_E);
		}
		break;
	case('F'):
		ranks_file = fopen(Rank_F, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_F, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_F);
		}
		break;
	case('G'):
		ranks_file = fopen(Rank_G, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_G, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_G);
		}
		break;
	case('H'):
		ranks_file = fopen(Rank_H, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_H, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_H);
		}
		break;
	case('I'):
		ranks_file = fopen(Rank_I, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_I, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_I);
		}
		break;
	case('J'):
		ranks_file = fopen(Rank_J, "w");
		fclose(ranks_file);
		ranks_file = fopen(Rank_J, "a");
		fprintf(ranks_file, "%s%d\n%d\n-------questions-------\n",
			R->Rank_Title,
			R->Added_Time,
			R->Score);
		fclose(ranks_file);
		for (int i = 0; i < R->Q_list->length; i++)
		{
			Write_Question_To_File(*R, i, Rank_J);
		}
		break;
	}
}

void Change_Rank_Added_Time(char RankSymbol, int Time) // modifyed Change_Rank_Added_Time for the raw input (not struct)
{
	switch (RankSymbol)
	{
	case('A'):
		Change_Rank_Added_Time_For_Rank(A, Time);
		break;
	case('B'):
		Change_Rank_Added_Time_For_Rank(B, Time);
		break;
	case('C'):
		Change_Rank_Added_Time_For_Rank(C, Time);
		break;
	case('D'):
		Change_Rank_Added_Time_For_Rank(D, Time);
		break;
	case('E'):
		Change_Rank_Added_Time_For_Rank(E, Time);
		break;
	case('F'):
		Change_Rank_Added_Time_For_Rank(F, Time);
		break;
	case('G'):
		Change_Rank_Added_Time_For_Rank(G, Time);
		break;
	case('H'):
		Change_Rank_Added_Time_For_Rank(H, Time);
		break;
	case('I'):
		Change_Rank_Added_Time_For_Rank(I, Time);
		break;
	case('J'):
		Change_Rank_Added_Time_For_Rank(J, Time);
		break;
	}
}

void Change_Question_Rank(char RankSymbolDel, char RankSymbolNew, int QuestionNumber) // Chenging a question's rank 
{
	Question Q = Delete_Question_For_New(RankSymbolDel, QuestionNumber); // Deleting the question from the previous rank
	switch (RankSymbolNew)
	{
	case('A'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('B'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('C'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('D'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('E'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('F'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('G'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('H'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('I'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	case('J'):
		Add_Question(RankSymbolNew, Q.Basic_Time, Q.content, Q.Right_Answer);
		break;
	}
}

void Edit_Question(char RankSymbol, int QuestionNumber, char * Content, int RightAnswer) // Editing a question from the input given from the admin
{
	Question* Q = NULL;
	Decode(Content); // Decoding the admin's content
	switch (RankSymbol)
	{
	case('A'): // Same for every rank
		for (int i = 0; i < A->Q_list->length; i++) // Getting the Question from the rank
		{
			if (A->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = A->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(A, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(A, Q, Content, RightAnswer);
		break;
	case('B'):
		for (int i = 0; i < B->Q_list->length; i++)
		{
			if (B->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = B->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(B, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(B, Q, Content, RightAnswer);
		break;
	case('C'):
		for (int i = 0; i < C->Q_list->length; i++)
		{
			if (C->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = C->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(C, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(C, Q, Content, RightAnswer);
		break;
	case('D'):
		for (int i = 0; i < D->Q_list->length; i++)
		{
			if (D->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = D->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(D, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(D, Q, Content, RightAnswer);
		break;
	case('E'):
		for (int i = 0; i < E->Q_list->length; i++)
		{
			if (E->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = E->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(E, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(E, Q, Content, RightAnswer);
		break;
	case('F'):
		for (int i = 0; i < F->Q_list->length; i++)
		{
			if (F->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = F->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(F, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(F, Q, Content, RightAnswer);
		break;
	case('G'):
		for (int i = 0; i < G->Q_list->length; i++)
		{
			if (G->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = G->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(G, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(G, Q, Content, RightAnswer);
		break;
	case('H'):
		for (int i = 0; i < H->Q_list->length; i++)
		{
			if (H->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = H->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(H, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(H, Q, Content, RightAnswer);
		break;
	case('I'):
		for (int i = 0; i < I->Q_list->length; i++)
		{
			if (I->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = I->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(I, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(I, Q, Content, RightAnswer);
		break;
	case('J'):
		for (int i = 0; i < J->Q_list->length; i++)
		{
			if (J->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = J->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(J, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		Edit_Question_For_Ranks(J, Q, Content, RightAnswer);
		break;
	}
}

void Edit_Question_For_Ranks(Rank* R, Question* Q, char * Content, int RightAnswer) // Editing a question's content in the rank
{
	int BasicTime = Q->Basic_Time;
	if (!Check_Question_Existence_In_Ranks(R, Q))
	{
		printf("The question is not in the rank.\n");
		return;
	}
	Delete_Question_In_Ranks(R, Q);
	Q->Basic_Time = BasicTime;
	strcpy(Q->content, Content);
	Q->Right_Answer = RightAnswer;
	Add_Question_To_Ranks(R, Q);
}

int Encode(char* QContent) // Encoding the content of a question from the ranks list
{
	int count = 0;
	while (QContent[count] != '\0')
	{
		if (QContent[count] == '@')
		{
			QContent[count] = '\n';
		}
		count++;
	}
	if (count >= 0) return 1;
	return 0;
}

void Print_Question_Details(char RankSymbol, int QuestionNumber, int option) // Printing the question details (if the option is not 0, it will print only the question's content without the right answer
{
	Question* Q = NULL;
	char str[256];
	switch (RankSymbol)
	{
	case('A'):
		for (int i = 0; i < A->Q_list->length; i++)
		{
			if (A->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = A->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(A, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('B'):
		for (int i = 0; i < B->Q_list->length; i++)
		{
			if (B->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = B->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(B, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('C'):
		for (int i = 0; i < C->Q_list->length; i++)
		{
			if (C->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = C->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(C, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('D'):
		for (int i = 0; i < D->Q_list->length; i++)
		{
			if (D->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = D->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(D, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('E'):
		for (int i = 0; i < E->Q_list->length; i++)
		{
			if (E->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = E->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(E, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('F'):
		for (int i = 0; i < F->Q_list->length; i++)
		{
			if (F->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = F->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(F, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('G'):
		for (int i = 0; i < G->Q_list->length; i++)
		{
			if (G->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = G->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(G, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('H'):
		for (int i = 0; i < H->Q_list->length; i++)
		{
			if (H->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = H->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(H, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('I'):
		for (int i = 0; i < I->Q_list->length; i++)
		{
			if (I->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = I->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(I, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	case('J'):
		for (int i = 0; i < J->Q_list->length; i++)
		{
			if (J->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				Q = J->Q_list->Values[i];
			}
		}
		if (!Check_Question_Existence_In_Ranks(J, Q))
		{
			printf("The question dosn't exist in the rank\n");
			return;
		}
		break;
	}
	strcpy(str, Q->content);
	Encode(str); // Encoding the question content
	if (option == 0) {
		printf("Question Number: %d\nBasic Time: %d\nContent: %s\nRight Answer: %d\n",
			Q->Q_Number,
			Q->Basic_Time,
			str,
			Q->Right_Answer);
	}
	else
		printf("%s", str);

}

void Print_Rank(Rank *R) // Printing the rank's information (including the questions in the rank)
{
	char str[256];
	printf("Rank Symbol: %c\nRank Title: %sAdded Time: %d\nScore: %d\n", R->Rank_Symbol, R->Rank_Title, R->Added_Time, R->Score);
	printf("------- Questions -------\n");
	for (int i = 0; i < R->Q_list->length; i++)
	{
		strcpy(str, R->Q_list->Values[i]->content);
		Encode(str);
		printf("Question Number: %d\nBasic Time: %d\nContent:\n%s\nRight Answer: %d\n",
			R->Q_list->Values[i]->Q_Number,
			R->Q_list->Values[i]->Basic_Time,
			str,
			R->Q_list->Values[i]->Right_Answer);
		printf("-------------------------\n");
	}
}

void Print_Rank_Details(char RankSymbol) // Printing a rank details (given rank)
{
	switch (RankSymbol)
	{
	case('A'):
		Print_Rank(A);
		break;
	case('B'):
		Print_Rank(B);
		break;
	case('C'):
		Print_Rank(C);
		break;
	case('D'):
		Print_Rank(D);
		break;
	case('E'):
		Print_Rank(E);
		break;
	case('F'):
		Print_Rank(F);
		break;
	case('G'):
		Print_Rank(G);
		break;
	case('H'):
		Print_Rank(H);
		break;
	case('I'):
		Print_Rank(I);
		break;
	case('J'):
		Print_Rank(J);
		break;
	}
}

int Check_Answer(int UserInput, int QuestionNumber, char RankSymbol) // Checking if the answer is correct with a given question number, rank symbol and user's input
{
	switch (RankSymbol)
	{
	case('A'):
		for (int i = 0; i < A->Q_list->length; i++)
		{
			if (A->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == A->Q_list->Values[i]->Right_Answer) // checking if the user's answer is correct
					return 1;
				else
					return 0;
			}
		}
		break;
	case('B'):
		for (int i = 0; i < B->Q_list->length; i++)
		{
			if (B->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == B->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('C'):
		for (int i = 0; i < C->Q_list->length; i++)
		{
			if (C->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == C->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('D'):
		for (int i = 0; i < D->Q_list->length; i++)
		{
			if (D->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == D->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('E'):
		for (int i = 0; i < E->Q_list->length; i++)
		{
			if (E->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == E->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('F'):
		for (int i = 0; i < F->Q_list->length; i++)
		{
			if (F->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == F->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('G'):
		for (int i = 0; i < G->Q_list->length; i++)
		{
			if (G->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == G->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('H'):
		for (int i = 0; i < H->Q_list->length; i++)
		{
			if (H->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == H->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('I'):
		for (int i = 0; i < I->Q_list->length; i++)
		{
			if (I->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == I->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	case('J'):
		for (int i = 0; i < J->Q_list->length; i++)
		{
			if (J->Q_list->Values[i]->Q_Number == QuestionNumber)
			{
				if (UserInput == J->Q_list->Values[i]->Right_Answer)
					return 1;
				else
					return 0;
			}
		}
		break;
	}
	return 0; //it will get here if the question dosent exist in the rank! no good!
}

void Print_All_Ranks() // Printing all the ranks in the game (using Print_Rank_Details)
{
	char Names[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	for (int i = 0; i < 10; i++)
	{
		printf("-------------------------------------------\n");
		Print_Rank_Details(Names[i]);
	}
	printf("-------------------------------------------\n");
}

//Print the registered user to the daily winner file
void Print_to_DWinner(Reg_User user) {
	FILE* DWinner_file = fopen(Daily_Winner, "a");
	if (!DWinner_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	fprintf(DWinner_file, "%s\n%s\n%d\n",
		user.Nickname,
		user.Full_Name,
		user.Last_Score);
	fclose(DWinner_file);
}

//Print the daily winner
void Print_The_Daily_Winner() {
	FILE* DWinner_file = fopen(Daily_Winner, "r");
	char Winner_NickName[50], Nickname[50], score_string[20], Full_Name[20], Full_Name_Winner[50] = "", tmp_string[30] = "";
	int Winner_score = -1, score = -1, tmp = 0;
	if (!DWinner_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	//Find the player with the higest score
	while (!feof(DWinner_file)) {
		fscanf(DWinner_file, "%s\n", Nickname);
		fgets(Full_Name, 20, DWinner_file);
		strtok(Full_Name, "\n");
		fscanf(DWinner_file, "%d\n", &score);
		if (score > Winner_score) {
			Winner_score = score;
			strcpy(Winner_NickName, Nickname);
			strcpy(Full_Name_Winner, Full_Name);
		}
	}
	//Print the daily winner nickname, full name and score
	while (tmp <= 5) {
		system("cls");
		if (tmp == 0 || tmp == 3) {
			printf("\x1b[93m                   (                                                        \n");
			printf("  *   )   )        )\\ )          (        (  (                              \n");
			printf(" ( )(_))\\()) ))\\   /(_)) ( /( )\\((_)\\ )  ((_)()\\ ) )\\  (     (     ))\\ )(   \n");
			printf("(_(_()|(_)\\ /((_) (_))_  )(_)|(_)_(()/(  _(())\\_)(|(_) )\\ )  )\\ ) /((_|()\\  \n\x1b[91m");
			printf("|_   _| |\x1b[93m(_|_))    \x1b[91m|   \\\x1b[93m((_)_\x1b[91m (_| |\x1b[93m)(_)(\x1b[91m \\ \\\x1b[93m((_)\x1b[91m/ /(_)\x1b[93m_)_/( _(_/()_)(  ((_( \n\x1b[91m");
			printf("  | | | ' \\/ -_)   | |) / _` || | | || |  \\ \\/\\/ / | | ' \\)| ' \\)| -_)| '_| \n");
			printf("  |_| |_||_\\___|   |___/\\__,_||_|_|\\_, |   \\_/\\_/  |_|_||_||_||_|\\___||_|   \n");
			printf("                                   |__/                                     \n\x1b[0m");
			printf("\n\t\t     Searching for the daily winner.");
		}
		if (tmp == 1 || tmp == 4) {
			printf("\x1b[93m                   (                                                        \n");
			printf("  *   (   )        (/ )          )        (  )                              \n");
			printf(" ( )(_))\\()) ))\\   \\(_)) ( /( )\\((_)/ )  ((_)()/ ) )\\  (     )     ))/ )(   \n");
			printf("(_(_()|(_(\\ /((_) (_)(_  )(_(|(_)_(()/(  _(())\\_)(|(_) )\\ )  )\\ ) /((_|()\\  \n\x1b[91m");
			printf("|_   _| |\x1b[93m(_|_))    \x1b[91m|   \\\x1b[93m((_)_\x1b[91m (_| |\x1b[93m)(_))\x1b[91m \\ \\\x1b[93m((_)\x1b[91m/ /(_)\x1b[93m_)_/( _(_/((_))  ))_( \n\x1b[91m");
			printf("  | | | ' \\/ -_)   | |) / _` || | | || |  \\ \\/\\/ / | | ' \\)| ' \\)| -_)| '_| \n");
			printf("  |_| |_||_\\___|   |___/\\__,_||_|_|\\_, |   \\_/\\_/  |_|_||_||_||_|\\___||_|   \n");
			printf("                                   |__/                                     \n\x1b[0m");
			printf("\n\t\t     Searching for the daily winner..");
		}
		if (tmp == 2 || tmp == 5) {
			printf("\x1b[93m                   (                                                        \n");
			printf("  *   (   )        (/ )          )        (  )                              \n");
			printf(" ( )(_()\\()) ()\\   /(_)) ( /( (\\((_)\\ (  ((_)((\\ ) )\\  )     (     ()\\ ()   \n");
			printf("(_(_))|(_)/ \\((_) (_)(_  ))_(|)_)_)()/(  _(())\\_)(|(_( )\\ )  )/ ( /((_|()/  \n\x1b[91m");
			printf("|_   _| |\x1b[93m(_|_))    \x1b[91m|   \\\x1b[93m((_)_\x1b[91m (_| |\x1b[93m)(_))\x1b[91m \\ \\\x1b[93m((_)\x1b[91m/ /(_)\x1b[93m_)_/( _)_/()_))  )(_) \n\x1b[91m");
			printf("  | | | ' \\/ -_)   | |) / _` || | | || |  \\ \\/\\/ / | | ' \\)| ' \\)| -_)| '_| \n");
			printf("  |_| |_||_\\___|   |___/\\__,_||_|_|\\_, |   \\_/\\_/  |_|_||_||_||_|\\___||_|   \n");
			printf("                                   |__/                                     \n\x1b[0m");
			printf("\n\t\t     Searching for the daily winner...");
		}
		Wait(1);
		tmp++;
	}
	system("cls");
	printf("\x1b[93m                   (                                                        \n");
	printf("  *   )   )        )\\ )          (        (  (                              \n");
	printf(" ( )(_))\\()) ))\\   /(_)) ( /( )\\((_)\\ )  ((_)()\\ ) )\\  (     (     ))\\ )(   \n");
	printf("(_(_()|(_)\\ /((_) (_))_  )(_)|(_)_(()/(  _(())\\_)(|(_) )\\ )  )\\ ) /((_|()\\  \n\x1b[91m");
	printf("|_   _| |\x1b[93m(_|_))    \x1b[91m|   \\\x1b[93m((_)_\x1b[91m (_| |\x1b[93m)(_)(\x1b[91m \\ \\\x1b[93m((_)\x1b[91m/ /(_)\x1b[93m_)_/( _(_/()_)(  ((_( \n\x1b[91m");
	printf("  | | | ' \\/ -_)   | |) / _` || | | || |  \\ \\/\\/ / | | ' \\)| ' \\)| -_)| '_| \n");
	printf("  |_| |_||_\\___|   |___/\\__,_||_|_|\\_, |   \\_/\\_/  |_|_||_||_||_|\\___||_|   \n");
	printf("                                   |__/                                     \n\x1b[0m\n");
	sprintf(score_string, "%d", Winner_score);
	strcpy(tmp_string, "Score: ");
	strcat(tmp_string, score_string);
	strcpy(score_string, tmp_string);
	strcpy(tmp_string, "Name: ");
	strcat(tmp_string, Full_Name_Winner);
	strcpy(Full_Name_Winner, tmp_string);
	if (Winner_score != -1) {
		printf("\x1b[95m---------------------->\x1b[0m%*s%*s\x1b[95m<----------------------\n", 14 + (int)(strlen(Winner_NickName)) / 2,Winner_NickName, 14 - (int)(strlen(Winner_NickName)) / 2, "");
		Wait(1);
		printf("\x1b[95m---------------------->\x1b[0m%*s%*s\x1b[95m<----------------------\n", 14 + (int)(strlen(Full_Name_Winner)) / 2, Full_Name_Winner, 14 - (int)(strlen(Full_Name_Winner)) / 2, "");
		Wait(1);
		printf("---------------------->\x1b[0m%*s%*s\x1b[95m<----------------------\n\x1b[0m\n", 14 + (int)(strlen(score_string)) / 2, score_string, 14 - (int)(strlen(score_string)) / 2, "");
	}
	else
		printf("\t\t\t\tNo daily winner!\n");
	printf("\nPress any key to exit.");
	getchar();
	fclose(DWinner_file);
	//Delete the content of the daily winner
	DWinner_file = fopen(Daily_Winner, "w");
	fclose(DWinner_file);
}

//Print to the log file with the messege recived
void Print_To_Log_File(char *msg) {
	FILE* log_file = fopen(Log_File, "a");
	time_t rawtime;
	struct tm *info;
	char buffer[100];
	if (!log_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	time(&rawtime);
	info = localtime(&rawtime);
	//Print the date and the action
	strftime(buffer, 100, "%d/%m/%G", info);
	fprintf(log_file, "%s\n%s\n", buffer, msg);
	fclose(log_file);
}

//Print from log file by date
void Print_From_Log_File(char* date)
{
	FILE* log_file = fopen(Log_File, "r");
	char Date[20], Temp_Date[20], Action[120];
	int flag = 0;
	if (!log_file) {
		printf("** ERROR : FILE UNWRITEABLE **");
		return;
	}
	//If the date is null, print all the log file
	if (date == NULL) {
		while (!feof(log_file)) {
			fseek(log_file, -1, SEEK_CUR);
			fscanf(log_file, "%s\n", Temp_Date);
			if (strcmp(Date, Temp_Date) != 0) {
				strcpy(Date, Temp_Date);
				printf("-----------------------------------------------------\n");
				printf("All actions for the date: %s\n", Date);
			}
			fgets(Action, 120, log_file);
			fgetc(log_file);
			printf("%s", Action);
		}
		printf("-----------------------------------------------------\n");
	}
	//Else print all the actions that occourred at this date
	else {
		while (!feof(log_file)) {
			fseek(log_file, -1, SEEK_CUR);
			fscanf(log_file, "%s\n", Temp_Date);
			if (strcmp(Temp_Date, date) == 0 && flag == 0) {
				flag = 1;
				printf("-----------------------------------------------------\n");
				printf("All actions for the date: %s\n", Temp_Date);
			}
			fgets(Action, 120, log_file);
			fgetc(log_file);
			if (strcmp(Temp_Date, date) == 0) {
				printf("%s", Action);
			}
		}
		if (flag)
			printf("-----------------------------------------------------\n");
		else
			printf("There is no action for this date!\n");
	}
	fclose(log_file);
}

int Create_Admin(Admin admin) {
	char msg[100] = "Admin ";
	if (admin_verification(admin.ID, NULL)) {//check if the admin id already in the system
		return 0; // if yes, return 0 and dont add the admin.
	}
	strcat(msg, admin.Name);
	strcat(msg, " (");
	strcat(msg, admin.ID);
	strcat(msg, ") registered to the system!");
	Register_Admin(admin);
	Print_To_Log_File(msg);
	return 1;
}

//add admin to the system
int add_admin() {
	//create null instance
	Admin a;
	//ask the corrent admin for details to the new admin
	printf("Enter new admin ID: ");
	gets_s(a.ID, 50);
	printf("Enter new admin name: ");
	gets_s(a.Name, 50);
	printf("Enter new admin password: ");
	gets_s(a.Password, 50);
	//register the admin to the files.
	return Create_Admin(a);
}

//register the user to the files
int Create_User(Reg_User usr) {
	char msg[100] = "New user with nickname: ";
	if (user_verification(usr.Nickname, NULL)) {//check if the user nickname already in the system
		return 0; // if yes, return 0 and dont add the user.
	}
	//set the message to the log file
	strcat(msg, usr.Nickname);
	strcat(msg, " registered to the system!");
	//print the user to the files
	Register_user(usr);
	//print the message to the log file.
	Print_To_Log_File(msg);
	return 1;
}

//add user to the system
int add_user(int* hs, int*ls, int*lt, int is_anonymous) {
	//create null instance
	Reg_User u;
	int flag = 0;
	//get info for the new user
	do {
		printf("Enter nickname: ");
		gets_s(u.Nickname, 50);
		printf("Enter full name: ");
		gets_s(u.Full_Name, 50);
		printf("Enter password: ");
		gets_s(u.Password, 50);
		//update stats if given
		if (hs == NULL)
			u.High_Score = 0;
		else
			u.High_Score = *hs;
		if (ls == NULL)
			u.Last_Score = 0;
		else
			u.Last_Score = *ls;
		if (lt == NULL)
			u.Last_Time = 0;
		else
			u.Last_Time = *lt;
		//if the user is anonimyus print it to the daily winner
		if (is_anonymous == 1)
			Print_to_DWinner(u);
		//regisetr the user to the files.
		flag = Create_User(u);
		if (!flag)
			printf("This User is already in the system! Try again.\n");
	} while (flag == 0);
	return 1;
}

//delete admin from the system by its id
int delete_admin(char id[]) {
	//set new message to the log file
	char msg[100] = "Admin with id: ";
	//chceck if the admin id exist in the file
	if (!admin_verification(id, NULL)) {
		printf("No such admin with that id.\n");
		return 0;
	}
	//remove the admin
	remove_admin(id);
	//set the message to the log file
	strcat(msg, id);
	strcat(msg, " deleted from the system by admin ");
	strcat(msg, current_admin->Name);
	strcat(msg, ".");
	//print the message to the log
	Print_To_Log_File(msg);
	return 1;
}

//delete admin interface
int delete_admin_from_system() {
	//get the admin's id
	char id[50];
	printf("Enter admin id that you want to delete: ");
	scanf("%s", id);
	getchar();
	//check if the id entered is valid
	if (strcmp(current_admin->ID, id) == 0) {
		printf("You can't delete yourself!\n");
		return 0;
	}
	//delete the admin from the system
	return delete_admin(id);
}

//remove user from the system by its nickname
int delete_user(char nickname[]) {
	//set message to the log
	char msg[100] = "User with nickname: ";
	//check if the user exist by its nick name
	if (!user_verification(nickname, NULL)) {
		return 0;
	}
	//remove the user from the system
	remove_user(nickname);
	//set the message to the log
	strcat(msg, nickname);
	strcat(msg, " deleted from the system by admin ");
	strcat(msg, current_admin->Name);
	strcat(msg, ".");
	//print the messgae to the log file
	Print_To_Log_File(msg);
	return 1;
}

//delete user from the system  - interface
int delete_user_from_system() {
	//get nickname of the user we want to delete
	char nick[50];
	printf("Enter user nickname that you want to delete: ");
	gets_s(nick, 50);
	//delete the user from the file.
	return delete_user(nick);
}

//change user ditails by the admin
int Edit_User_Details() {
	Reg_User u, *u1 = (Reg_User*)malloc(sizeof(Reg_User));
	char  term;
	int valid, choice;
	//get the user nickname 
	printf("Enter the user nickname you want to change info: ");
	gets_s(u.Nickname, 50);
	//check if the user exist in the system
	if (!user_verification(u.Nickname, NULL)) {
		printf("This user does no exist.\n");
		return 0;
	}
	//get user from the system
	get_user(u.Nickname, u1);
	//change the user ditails by the admin choise
	printf("1) Change user full name\n2) Change user password\n3)Go back");
	do {
		//get admin coise
		printf("\nYour choice:");
		valid = scanf("%d%c", &choice, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((choice > 3 || choice < 1) || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (choice > 3 || choice < 1));
	switch (choice) {
	case 1://if admin choose 1, change the user name
		printf("Enter full name for %s: ", u.Nickname);
		gets_s(u1->Full_Name, 50);
		Change_user_info(u1);
		break;
	case 2://if admin choose 2, change the user password
		printf("Enter password for %s: ", u.Nickname);
		scanf("%s", u1->Password);
		while (getchar() != '\n');
		Change_user_info(u1);
		break;
	case 3://if the user choose 3, exit from the change menu
		return 0;
	default:
		break;
	}
	return 1;
}

//change user details
int change_user_info(Reg_User *u) {
	char term;
	int flag = 0, valid, choice;
	//check if user exist
	if (!user_verification(u->Nickname, NULL)) {
		printf("ERROR: USER NOT FOUND!");
		return 0;
	}
	//show user change info menu
	printf("1) Change user full name\n2) Change user password\n3) Go back");
	do {
		//get user choise
		printf("\nYour choice:");
		valid = scanf("%d%c", &choice, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((choice > 3 || choice < 1) || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (choice > 3 || choice < 1));
	switch (choice) {
	case 1://user choose to change its name
		printf("%s, enter new full name: ", u->Nickname);
		gets_s(u->Full_Name, 50);
		Change_user_info(u);

		break;
	case 2://user choose to change its password
		printf("%s, enter new password: ", u->Nickname);
		gets_s(u->Password, 50);
		Change_user_info(u);
		break;
	case 3://user choose to exit
		return 0;
	}
	return 1;
}

//edit admin info
int edit_admin_details(Admin* admin) {
	char term;
	int flag = 0, valid, choice;
	//check if the admin exist
	if (!admin_verification(admin->ID, NULL)) {
		printf("ERROR: Admin NOT FOUND!\n");
		return 0;
	}
	//show admin change info menu
	printf("1) Change Admin full name\n2) Change Admin password\n3) Go back");
	do {
		//get admin choise
		printf("\nYour choice:");
		valid = scanf("%d%c", &choice, &term);
		if (valid != 2 || term != '\n')
			while (getchar() != '\n');
		if ((choice > 3 || choice < 1) || valid != 2 || term != '\n')
			printf("Worng input. Try again");
	} while (valid != 2 || term != '\n' || (choice > 3 || choice < 1));
	switch (choice) {
	case 1://admin choose to change his name
		printf("%s, please enter new full name: ", admin->Name);
		gets_s(admin->Name, 50);
		Change_admin_info(admin);
		break;
	case 2://admin choose to change his password
		printf("%s, please enter new password: ", admin->Name);
		gets_s(admin->Password, 50);
		Change_admin_info(admin);
		break;
	case 3://admin choose to exit operation
		return 0;
	default:
		break;
	}
	return 1;
}

void main() {
	system("cls");
	Open_Animiation();
	Pre_Start_Of_The_System();
	LogIn_Menu();
	system("cls");
	End_Of_The_System();
}