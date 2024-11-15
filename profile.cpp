#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAXNEWS = 10; 

struct NewsPost {
    int id;
    string title;
    string content;
    int likes;
    int ratings;
};

class ProfilePage {
private:
    NewsPost updatedPosts[MAXNEWS];
    int newsCount;
    string uploaderProfile;
    
public:
    ProfilePage(const string& uploader) : uploaderProfile(uploader), newsCount(0) {}

    void addNews(int id, const string& title, const string& content) 
	{
        if (newsCount < MAXNEWS) 
		{
            updatedPosts[newsCount].id = id;
            updatedPosts[newsCount].title = title;
            updatedPosts[newsCount].content = content;
            updatedPosts[newsCount].likes = 0;      // Initial values for likes and ratings
            updatedPosts[newsCount].ratings = 0;
            newsCount++;
        } 
		else 
		{
            cout << "Maximum news posts reached.\n";
        }
    }

    void viewProfile() const 
	{
        cout << "\n------ " << uploaderProfile << "'s Profile ------\n";
        cout << "Uploaded News:\n";
        for (int i = 0; i < newsCount; i++) 
		{
            cout << "News ID: " << updatedPosts[i].id << "\n";
            cout << "Title: " << updatedPosts[i].title << "\n";
            cout << "Content: " << updatedPosts[i].content << "\n\n";
        }
    }

    void viewAnalytics(const string& viewerName) const 
	{
        if (viewerName == uploaderProfile) 
		{
            cout << "\n------ Analytics for " << uploaderProfile << " ------\n";
            for (int i = 0; i < newsCount; i++) 
			{
                cout << "News ID: " << updatedPosts[i].id << "\n";
                cout << "Likes: " << updatedPosts[i].likes << "\n";
                cout << "Ratings: " << updatedPosts[i].ratings << "\n\n";
            }
        } 
		else 
		{
            cout << "You do not have permission to view analytics.\n";
        }
    }

    void saveToFile() const 
	{
        ofstream file("ProfileData.txt");
        if (file.is_open()) 
		{
            file << uploaderProfile << "\n";
            file << newsCount << "\n";
            for (int i = 0; i < newsCount; i++) 
			{
                file << updatedPosts[i].id << "\n";
                file << updatedPosts[i].title << "\n";
                file << updatedPosts[i].content << "\n";
                file << updatedPosts[i].likes << "\n";
                file << updatedPosts[i].ratings << "\n";
            }
            file.close();
        } 
		else 
		{
            cout << "Error saving data.\n";
        }
    }
};

int main() 
{
    string uploader = "Myvolunteer";  // uploader's name
    ProfilePage profile(uploader);

    // try test news
    profile.addNews(1, "Stray Cats Campaign", "Join us for the annual campaign!");
    profile.addNews(2, "New Gymnasium Timings", "Gym hours extended till 11 PM.");

    // show profile page (titles and contents only)
    profile.viewProfile();

    // view analytics as the uploader
    cout << "\nAttempt to view analytics as uploader:\n";
    profile.viewAnalytics("Myvolunteer");

    // Attempt to view analytics as a different user
    cout << "\nAttempt to view analytics as another user:\n";
    profile.viewAnalytics("AnotherUser");

    // nak save profile data dalam file
    profile.saveToFile();

    return 0;
}

