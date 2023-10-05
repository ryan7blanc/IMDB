#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) {
    // TODO
    if (argc != 4)
    {
        cout << "Invalid number of arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size> <skipList size>" << endl;
        return 0;
    }

    string file = argv[1];
    int hashsize = stoi(argv[2]);
    int listsize = stoi(argv[3]);

    MovieHashTable hash(hashsize);
    DirectorSkipList direc(listsize, 10);

    readMovieCSV(file, hash, direc);
    cout << "Number of collisions:" << hash.getCollisions() << endl;
    int inputval = 0;
    string input;

    
    do {
        display_menu();
        cin >> inputval;

        if (inputval == 1)
        {
            cout << "Enter movie name: ";
            cin.ignore(1000, '\n');
            getline(cin,input);

            MovieNode* save = hash.search(input);
            if (save == nullptr)
            {
                cout << "Movie could not be found" << endl;
            }
            else
            cout << "The director of " << input << " is " << save->director << endl;
        }
        else if (inputval == 2)
        {
            cout << "Enter director name: ";
            cin.ignore(1000, '\n');
            getline(cin,input);

            DirectorSLNode* mov = direc.search(input);
            if (mov != nullptr)
            cout << input << " directed " << mov->movies.size() << " movies" << endl;
            else
            cout << input << " has not directed any movies yet" << endl;
        }
        else if (inputval == 3)
        {
            cout << "Enter movie name: ";
            cin.ignore(1000, '\n');
            getline(cin, input);

            MovieNode* sum = hash.search(input);
            cout << "Summary: " << sum->title << " is a " << sum->year << " (" << sum->genre << ") film featuring " << sum->actors << endl;
            cout << "Plot: " << sum->description << endl;
        }
        else if (inputval == 4)
        {
            cout << "Enter director name: ";
            cin.ignore(1000, '\n');
            getline(cin, input);

            DirectorSLNode* node = direc.search(input);
            cout << input << " direted the following movies: " << endl;
            for (int i = 0; i < node->movies.size(); i++)
            {
                cout << i + 1 << ": " << node->movies[i]->title << endl;
            }
        }

    } while (inputval != 5);

    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
/**
 * readMovieCSV - takes in file and uses parseMovieLine function to create a movie node
 * node is stored into Hash and SkipList
 * 
 * @param filename, movieTable, directorList
 */
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // TODO
    ifstream fin;
    string line;
    fin.open(filename);
    getline(fin, line);
    while (getline(fin, line))
    {
        MovieNode* hold = parseMovieLine(line);
        movieTable.insert(hold->title, hold);
        directorList.insert(hold->director, hold);
    }
}

// Function to display the menu options
void display_menu() {
    // TODO
    cout << "Please select an option:" << endl;
    cout << "1. Find director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl << endl;
    cout << "Enter an option: ";
}
