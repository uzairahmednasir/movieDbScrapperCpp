#include <iostream>
#include <string>
#include "MovieScraper.h"

using namespace std;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CyanBackground   "\033[2;47;35m"
#define ANSI_COLOR_WhiteBackground   "\033[3;42;30m"
#define ANSI_COLOR_Background_RESET   "\033[0m "


//Menu-1
void ShowSearchMenu(MovieScraper &movie , string *title , string *realeaseDate , string *Synopsis , int &ArrCount)
{


	//Asking for Movie Name
	system("cls");
	cout << ANSI_COLOR_CyanBackground "Enter Movie Name: " ANSI_COLOR_Background_RESET;

	string usr_input;
	getline(cin, usr_input);
	movie.Set_Title(usr_input);

	//Clearing up the Screen and Showing the Result Menu
	movie.RunScraper();

	int movieCount = movie.Get_NumberOfMovies();
	string stringToShow = movieCount > 20 ? "20+" : to_string(movieCount);


	system("cls");
	cout << "\n\n\n					========================================" << endl;
	printf(ANSI_COLOR_WhiteBackground "						Number of Results Found: %s\n"			ANSI_COLOR_Background_RESET , stringToShow.c_str());
	cout << "					========================================" << endl;

	movie.ShowResult();
	cout << ANSI_COLOR_CyanBackground "===================================================" ANSI_COLOR_Background_RESET;
	cout << "\n\n";

	//Adding to DB or go back ?
	cout << "1 " << ANSI_COLOR_CyanBackground "Add movie to data Base ?" ANSI_COLOR_Background_RESET << endl;
	cout << endl;
	cout << "2 " << ANSI_COLOR_CyanBackground "Go Back to main-menu?" ANSI_COLOR_Background_RESET << endl;

	cout << "\n";
	cout << ANSI_COLOR_CyanBackground "===================================================" ANSI_COLOR_Background_RESET;
	cout << "\n\n";

	cout << "Choice (1/2): ";
	int input;
	cin >> input;
	cin.ignore();

	if (input == 1)
	{
		cout << ANSI_COLOR_CyanBackground "Enter the Movie Number from the Above List: " ANSI_COLOR_Background_RESET;
		int input_2;
		cin >> input_2;
		
		*(title + ArrCount) = movie.MovieDB[input_2].Title;
		*(realeaseDate + ArrCount) = movie.MovieDB[input_2].Release_Date;
		*(Synopsis + ArrCount) = movie.MovieDB[input_2].Synopsis;
		ArrCount++;
		
	}



}

//Menu-2
void EnterLibrary(string* title, string* realeaseDate, string* Synopsis, int& ArrCount)
{
	system("cls");
	for (int i = 0; i < 30; i++)
	{
		if (title[i].find_first_not_of(' ') != -1 || title[i].length() != 0)
		{
			cout << "\n_____________________________________\n";
			cout << '[' << i << ']' << endl;
			cout << ANSI_COLOR_CYAN "Title: " ANSI_COLOR_RESET;
			cout << title[i] << endl;

			cout << ANSI_COLOR_CYAN "Release Date: " ANSI_COLOR_RESET;
			cout << realeaseDate[i] << endl;

			cout << ANSI_COLOR_CYAN "Synopsis: " ANSI_COLOR_RESET;
			cout << Synopsis[i] << endl;
			cout << "_____________________________________\n";
		}
	}

	cout << "\n\n";
	cout << "#####################################################" << endl;
	cout << "1 " << ANSI_COLOR_CyanBackground "ADD" ANSI_COLOR_Background_RESET;
	cout << "\n\n";
	cout << "2 " << ANSI_COLOR_CyanBackground "DELETE" ANSI_COLOR_Background_RESET <<endl;
	cout << "\n";
	cout << "3 " << ANSI_COLOR_CyanBackground "BACK TO MAIN MENU" ANSI_COLOR_Background_RESET << endl;
	cout << "#####################################################" << endl;
	cout << "\n\n";

	cout << "Press 1 - 3: ";
	int usr_input_2;
	cin >> usr_input_2;
	cin.ignore();

	if (usr_input_2 == 1)
	{
		system("cls");

		cout << ANSI_COLOR_CYAN "Title: " ANSI_COLOR_RESET << endl;
		string t;
		getline(cin, t);
		*(title + ArrCount) = t;

		cout << ANSI_COLOR_CYAN "Release Date: " ANSI_COLOR_RESET << endl;
		string r;
		getline(cin, r);
		*(realeaseDate + ArrCount) = r;

		cout << ANSI_COLOR_CYAN "Synopsis: " ANSI_COLOR_RESET << endl;
		string s;
		getline(cin, s);
		*(Synopsis + ArrCount) = s;

		ArrCount++;
		system("cls");

		cout << "DataBase Updated Press any Key to continue" << endl;
		system("PAUSE");

	}

	if (usr_input_2 == 3)
	{
		cout << "Returning to Main menu";
	}

	if (usr_input_2 == 2)
	{
		cout << "Enter the Element No to Delete from DataBase: ";
		int usr_input_3;
		cin >> usr_input_3;

		if (title[usr_input_3].find_first_not_of(' ') != -1 || title[usr_input_3].length() != 0)
		{
			title[usr_input_3] = "";
			realeaseDate[usr_input_3] = "";
			Synopsis[usr_input_3] = "";

		}
	}
}


int main(int argc , char* argv[])
{

	string Title_[60];
	string ReleaseDate_[60];
	string Synopsis_[60];
	int ArrCount = 0;


	MovieScraper movie;
	movie.set_path(argv[0]);


	bool MainLoop = true;
	while (MainLoop)
	{
		system("cls");

		cout <<					"\n\n\n					========================================" << endl;
		printf(ANSI_COLOR_WhiteBackground "						WELCOME TO THE PROGRAM\n"			ANSI_COLOR_Background_RESET);
		cout <<						"					========================================" << endl;

		cout << "\n\n";
		cout  << "1 " << ANSI_COLOR_CyanBackground "SEARCH MOVIE\n" ANSI_COLOR_Background_RESET << endl;
		cout << "2 "<< ANSI_COLOR_CyanBackground "LIBRARY\n" ANSI_COLOR_Background_RESET << endl;
		cout << "3 " << ANSI_COLOR_CyanBackground "EXIT\n" ANSI_COLOR_Background_RESET << endl;

		cout << "Enter 1-3: ";

		int usr_input;
		cin >> usr_input;
		cin.ignore();

		switch (usr_input)
		{
		case 1:
			ShowSearchMenu(movie , Title_ , ReleaseDate_ , Synopsis_ , ArrCount);
			break;

		case 2:
			EnterLibrary( Title_, ReleaseDate_, Synopsis_, ArrCount);
			break;

		case 3:
			MainLoop = false;
			break;

		default:
			break;
		}


	}

}
