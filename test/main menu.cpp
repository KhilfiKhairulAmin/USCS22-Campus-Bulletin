#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Function to write to file
void writeNews (string &news)
{
	ofstream myFile;
	myFile.open("News.txt", ios::app);
	
	if (!myFile.is_open())
	{
		cerr<<"File not found!\a"<<endl;
		return;
	}
	
	else
	{
		myFile<<news<<endl;
		cout<<"\nNews saved."<<endl;
	}
	myFile.close();
	
	return;
}

//Function to read from file
void readNews ()
{
	ifstream myFile ("News.txt");
	
	if (!myFile.is_open())
	{
		cerr<<"File not found!\a"<<endl;
		return;
	}
	
	else
	{
		string line;
		while (getline (myFile, line))
		{
			cout<<"\n\n"<<line<<endl;
		}
	}
	
	myFile.close();
	
	return;
}

//Function to edit news
void editNews(){
}

//Function to delete news
void deleteNews(){
}

/*----------------------------- MENU----------------------------*/
int main ()
{
	cout<<"+++++++++++++++++++++INTEC CAMPUS BULLETIN+++++++++++++++++++++"<<endl;
	cout<<"+++++++++++++++++++Stay INTEC, Eliminate FOMO++++++++++++++++++"<<endl;
	
	cout<<"\n\n[1]Write"<<endl<<"[2]Read"<<endl<<"[3]Edit"<<endl<<"[4]Delete"<<endl;
	cout<<"Choose your action: ";
	int option;
	cin>>option;
	cin.ignore();
	
	string news;
	if (option == 1)
	{
		cout<<"\n\nWrite your news here: "<<endl;
		getline (cin, news);
		writeNews(news);
	}
	
	if (option == 2)
	{
		cout<<"\n\n++++++++Catch up on latest news!++++++++"<<endl;
		readNews();
	}
	
	if (option == 3)
	{
		edi
	}
	
	if (option == 4)
	{
		deleteNews();
	}
	
	return 0;
}
