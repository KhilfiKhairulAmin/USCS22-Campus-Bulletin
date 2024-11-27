#include <iostream>
#include <vector>
#include "include/News.h"
#include "include/Publisher.h"
using namespace std;

const vector <News> *news;

void getPublisher (int id)
{
	PublisherManager creator;
	int index = PublisherManager.searchPublisherId(id);
	Publisher writer;
	cout<<"\n\n"<<writer[index].name;
	
	return;
}

int main()
{
	cout<<"+++++++++++++++++++++INTEC CAMPUS BULLETIN+++++++++++++++++++++"<<endl;
	cout<<"+++++++++++++++++++Stay INTEC, Eliminate FOMO++++++++++++++++++"<<endl;
	
	News info;
	for (auto it = news->rbegin(); it != news->rend(); it++)
	{
		getPublisher (info.publisherId);
		cout<<info.publishedAt<<endl;
		cout<<"\t"<<info.title<<endl;
		cout<<info.content<<endl;
	}

	return 0;
}
