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

    //helper function to clear linked list
    void clear(){
        while (head){
            ReviewNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    //constructor
    Movie(const string& t) : title(t), head(nullptr){}

    //delete copy constructor and assignment operator
    Movie(const Movie&) = delete;
    Movie& operator=(const Movie&) = delete;

    //move constructor
    Movie(Movie&& other) noexcept : title(move(other.title)), head(other.head) {
        other.head = nullptr;
    }
    //move assignment operator
    Movie& operator=(Movie&& other) noexcept {
        if (this != &other) {
            clear();
            title = move(other.title);
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

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
                 << fixed << setprecision(1) << p->rating
                 << " - " << p->comment << endl;

            sum+= p->rating;
        }

        if (count==0) {
            cout <<" No reviews yet.\n";
        } else {
            cout << " Average Rating: " << fixed << setprecision(2)
                 << (sum / count) << "\n\n";
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

    ifstream fin("reviews.txt");
        if(!fin) {
            cerr <<"Error file not found";
            return 1;
        }

    vector<Movie> movies;
    movies.reserve(6); //reserve space for 6 movies

    string title, comment;

    //read titles, and reviews
    while(getline(fin, title)) {
        if (title.empty()) continue;

        movies.emplace_back(title);
        Movie &m = movies.back();

        for (int i= 0; i < 3; ++i) {
        if (!getline(fin, comment)) break;
            double rating = (rand() % 41 + 10) / 10.0;
            m.addReview(rating, comment);
        }
        
    }
    fin.close();

        //display reviews
    for (auto& m : movies)
        m.display();

        return 0;
}