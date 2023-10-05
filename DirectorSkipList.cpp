#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
/**
 * creates Director SkipList
 */
DirectorSkipList::DirectorSkipList() {
    // TODO
    capacity = 2000;
    levels = 10;
    head = new DirectorSLNode("", levels);
    size = 0;
}

// Constructor for DirectorSkipList with given capacity and levels
/**
 * creates Director SkipList, except with specifies cap and levels
 */
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    // TODO
    capacity = _cap;
    levels = _levels;
    head = new DirectorSLNode("", levels);
    size = 0;
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
/**
 * traverses through each node in the 0th level, deleting the node
 */
DirectorSkipList::~DirectorSkipList() {
    // TODO
    DirectorSLNode* kill = head;
    while (kill != nullptr)
    {
        DirectorSLNode* next = kill;
        kill = kill->next.at(0);
        delete next;
    }

}

// Inserts a movie node into the skip list with the specified director
/**
 * uses search function to traverse to find the directors within the list, saving the last node in the level onto prev
 * if current director is equal to director, add the movie into the node vector
 * if curr is null or the curr director is not the parameter director, create a new Director node with the speficied director and levels
 * store all previous nodes' next as the new node's next, and current node as previous' next, add movie into node using addMovie
 * 
 * @param string, MovieNode*
 */
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    // TODO
    int n_levels = 1;
    while (n_levels < levels && rand() % 2 == 0)
    {
        n_levels++;
    }
    
    DirectorSLNode* curr = head;
    DirectorSLNode* prev[levels];
    for (int i = levels - 1; i >= 0; i--)
    {
        while (curr != nullptr && curr->next[i] != nullptr && curr->next[i]->director < director)
        {
            curr = curr->next[i];
        }
        prev[i] = curr;
    }
    curr = curr->next[0];
    if (curr != nullptr && curr->director == director)
    {
        curr->addMovie(_movie);
    }
    else if (curr == nullptr || curr->director != director)
    {
        DirectorSLNode* node = new DirectorSLNode(director, n_levels);
        for (int i = n_levels - 1; i >= 0; i--)
        {
            node->next[i] = prev[i]->next[i];
            prev[i]->next[i] = node;
        }
        node->addMovie(_movie);
    }

}

// Searches for a node in the skip list with the specified director
/**
 * traverses through each node in each level until a node with the matching director is found
 * returns node if the director matches
 * 
 * @param string
 * @return DirectorSLNode*
 */
DirectorSLNode* DirectorSkipList::search(string director) {
    // TODO
    DirectorSLNode* curr = head;
    for (int i = levels - 1; i >= 0; i--)
    {
        while (curr->next[i] != nullptr && curr->next[i]->director < director)
        {
            curr = curr->next[i];
        }
    }
    curr = curr->next[0];
    if (curr != nullptr && curr->director == director)
    {
        return curr;
    }

    return nullptr;
}

// Pretty-prints the skip list
/**
 * traverses every node in each level from top to bottom
 * prints director and moves to next node while the node isn't null
 */
void DirectorSkipList::prettyPrint() {
    // TODO
    for (int i = levels - 1; i >= 0; i--)
    {
        DirectorSLNode* out = head->next[i];
        
         while (out != nullptr)
         {
             cout << out->director << endl;
            out = out->next[i];
         }
    }
}
