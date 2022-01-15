/*
  this class works in 3 phases:
  1. Pass in the Movie title via constructor (user can change the movie title or keywords later via Set_Title() method).
  2. Call the Scrapper via RunScraper() method to perform scraping on given keywords.
  3. Show the data scraped from using the scraper on console or save the data onto a .txt file .

*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

class MovieScraper
{
private:
	string Query_Formating(string usr_Input)
	{
		string finalString = "";
		//This function adjusts query parameters acording to the websites search protocols.
		if (usr_Input.find(' '))
		{
			string arr[20];
			int count = 0;
			int index = 0;

			while (true)
			{
				string temp = "";
				while (index < usr_Input.length())
				{
					if (usr_Input[index] == ' ')
					{
						index++;
						break;
					}
					else
					{
						temp = temp + usr_Input[index];
						index++;
					}
				}

				arr[count] = arr[count] + temp;

				if (index >= usr_Input.length())
					break;

				count++;
				arr[count] += "%20";
				count++;
			}

			for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
			{
				finalString += arr[i];
			}
			return finalString;

		}
		else
			return finalString;

	}
	string PathSetter(string Location)
	{

		for (int i = Location.length() - 1; i > 0; i--)
		{
			char a = '\\';
			if (Location[i] != a)
			{
				Location = Location.substr(0, Location.length() - 1);
				continue;
			}
			else
			{
				string temp = "mkdir " + Location + "Assets";
				system(temp.c_str());
				return Location + "Assets";
			}

		}
	}
	struct Movie
	{
		string Title;
		string Release_Date = "NULL";
		string Synopsis = "NULL";
	};
	//________________________________________________
	string _KeyWords;
	string _Path;
	int Movies_Count = 0;

public:
	Movie MovieDB[30];   
	MovieScraper(string KeyWords , string PATH)
	{
		this->_Path = PathSetter(PATH);
		this->_KeyWords = Query_Formating(KeyWords);

	}
	MovieScraper() {}    // default constructor

	/**
	  Set the title of the movie you want to Search for.

	 @param std::string Title of the movie
	 */
	void RunScraper()
	{
		string URL = "curl https://www.themoviedb.org/search/movie?query=" + this->_KeyWords + " > " + this->_Path + "\\Search_result.txt";
		system(URL.c_str());

		string line;
		int count = 0;
		bool flag = false; //FOr Result Flex "Class" Entry
		string PATH = this->_Path + "\\Search_result.txt";

		ifstream file(PATH);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line.find("class=\"pagination_wrapper\"") != -1)
					break; //Program will stop after this break point which is this div
				if (line.find("class=\"card v4 tight\"") != -1)
					count++;

				if (line.find("<div class=\"results flex\">") != -1 || flag == true)
				{
					flag = true;
					//For Title Scraping
					if (line.find("data-media-type=\"movie\"") != -1 && line.find("<h2>") != -1)
					{
						int h2_index = (line.find("<h2>"));
						line = line.substr(h2_index + 4, ((line.length() - h2_index) - 4) - 9);
						this->MovieDB[count].Title = line;

						Movies_Count++;
					}


					//For Release Date scrape
					if (line.find("<span class=\"release_date\">") != -1 && line.find("</span>") != -1)
					{
						line = line.substr(39, (line.length() - 39) - 7);
						this->MovieDB[count].Release_Date = line;
					}

					//For Discription
					if (line.find("</p>") != -1)
					{
						line = line.substr(11, (line.length() - 11) - 4);
						this->MovieDB[count].Synopsis = line;
					}
				}

			}

		}

	}
	void ShowResult()
	{

		for (int i = 0; i < 30; i++)
		{
			if (MovieDB[i].Title.find_first_not_of(' ') != -1)
			{
				cout << '[' << i << ']' <<endl;
				cout << ANSI_COLOR_CYAN "Title: " ANSI_COLOR_RESET;
				cout << this->MovieDB[i].Title << endl;

				cout << ANSI_COLOR_CYAN "Release Date: " ANSI_COLOR_RESET;
				cout << this->MovieDB[i].Release_Date << endl;

				cout << ANSI_COLOR_CYAN "Synopsis: " ANSI_COLOR_RESET;
				cout << this->MovieDB[i].Synopsis << endl;
				cout << "_____________________________________\n";
			}
		}

	}
	int Get_NumberOfMovies()
	{
		return this->Movies_Count;
	}

	void Set_Title(string keywords)
	{
		this->_KeyWords = Query_Formating(keywords);
	}
	void set_path(string path)
	{
		this->_Path = PathSetter(path);
	}

};


