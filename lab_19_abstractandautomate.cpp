#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Brandon Julao
COMSC-210-5470
10.07.25
lab-19-abstractandautomate
*/

// structs for movie reviews.
struct ReviewNode{
    double rating;
    string comment;
    ReviewNode* next;
};

//Movie Class definition
class Movie{
    private:
    string title;
    ReviewNode* head;

public:
    //constructor
    Movie(const string& t) : title(t), head(nullptr){}

    //add review
    void addReview(double rating, const string& comment) {
        ReviewNode* n = new ReviewNode{rating, comment, head};
        head = n;
    }

    //display logic to show each review and compute the average
    void display() {
        cout << "Movie: " << title << endl;
        cout <<"--------------------------" << endl;

        int count = 0;
        double sum = 0.0;

        for (ReviewNode* p = head; p; p = p->next) {
            cout << " Review #" << ++count << ": "
                 << " - " << p->comment << endl;

            sum+= p->rating;
        }

        if (count==0) {
            cout <<" No reviews yet.\n";
        } else {
            cout << " Average Rating: " << fixed << setprecision(2)
                 << (sum / count) << "\n";
        }
    }

    //cleans up all review nodes to prevent leaks
    ~Movie() {
        while (head) {
            ReviewNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

};

int main () {
    // randomizer
    srand(static_cast<unsigned>(time(nullptr)));

    ifstream fin("review.txt");
        if(!fin) {
            cerr <<"Error file found found";
            return 1;
        }

    vector<Movie> movies;
    string title, comment;

    //read titles, and reviews
}