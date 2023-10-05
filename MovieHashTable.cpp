#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
/**
 * creates MovieHashTable
 */
MovieHashTable::MovieHashTable() {
    // TODO
    table_size = 2000;
    table = new MovieNode*[table_size];
    for (int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

// Constructor for MovieHashTable with given size
/**
 * creates MovieHashTable with specified table_size
 */
MovieHashTable::MovieHashTable(int s) {
    // TODO
    table_size = s;
    table = new MovieNode*[table_size];
    for (int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
/**
 * traverses through each index in the array, clearing the linked list within the index if existing
 * deletes array of table[]
 */
MovieHashTable::~MovieHashTable() {
    // TODO
    for (int i = 0; i < table_size; i++)
    {
        MovieNode* deleter = table[i];
        while (deleter != nullptr)
        {
            MovieNode* kill = deleter;
            deleter = deleter->next;
            delete kill;
        }
    }
    delete[] table;


}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
/**
 * hash - value c which holds the ascii value of the key, each value of the key multipiled by the title length
 * value v which holds the ascii value of the title
 * value hashv which holds the remainder of the product of c and v divided by the table size
 * 
 * @param string
 * @return int
 */
int MovieHashTable::hash(string title) {
    // TODO
    string key = "lobl1307";
    int v = 0;
    int c = 0;
    for (int i = 0; i < key.length(); i++)
    {
        c += int(key.at(i)) * title.length();
    }
    for (int j = 0; j < title.length(); j++)
    {
        char x = title.at(j);
        v += int(x);
    }
    int hashv = (c * v) % table_size;
    if (hashv < 2000)
    {
        return hashv;
    }

    return 0;
}

// Inserts a movie node into the hash table with the specified title
/**
 * insert - finds hash value using title, if table at hash is null, adds the movie into the array
 * if not, adds movie into the start of the linked list
 * 
 * @param title, movie
 */
void MovieHashTable::insert(string title, MovieNode* movie) {
    // TODO
    int hash = this->hash(title);
    if (this->table[hash] == nullptr)
    {
        this->table[hash] = movie;
    }
    else
    {
        movie->next = this->table[hash];
        this->table[hash] = movie;
        n_collisions++;
    }
}

// Searches for a node in the hash table with the specified title
/**
 * search - passes in title to find hash value, creating a new node by plugging in the value to the table
 * traverse through the node, if title is equal to parameter then return, else nullptr
 * 
 * @param title
 * @return MovieNode*
 */
MovieNode* MovieHashTable::search(string title) {
    // TODO
    int hash = this->hash(title);
    MovieNode* mover = table[hash];

    while (mover != nullptr)
    {
        if (mover->title == title)
        {
            return mover;
        }
        
        mover = mover->next;
    }

    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
/**
 * getCollisions - returns the number of collisions
 * 
 * @return int
 */
int MovieHashTable::getCollisions() {
    // TODO
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
/**
 * setCollisions - increments n_collisions
 */
void MovieHashTable::setCollisions() {
    // TODO
    n_collisions++;
}
