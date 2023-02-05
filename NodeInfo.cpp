/*
1. List of students: Cory Overgaard, Haden Johnson, Jonnathon Hicks
2. External Sources: tutorialspoint.com, geeksforgeeks.org, Peer Teachers in PETR 127
3. Concerns: None
*/
#ifndef _NODEINFO_CPP
#define _NODEINFO_CPP
//Worked with Jake Rounds
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <queue>
//#include <bits/stdc++.h>
#include "../include/NodeInfo.h"
#include "../src/PrintList.cpp"
#include <cstring>

using namespace std;

/* I needed these two lists for my implementation */

NodeInfo* dir_list = NULL;
NodeInfo* file_list = NULL;
NodeInfo* tree_root = NULL;

vector<string>
tokenize_input_string(string line)
{
    char space_char = ' ';
    vector<string> words{};

    stringstream sstream(line);
    string word;
    while (std::getline(sstream, word, space_char))
    {
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        words.push_back(word);
    }
    return words;
}

/* 
 * appends a new node at the end 
 */
void
append(NodeInfo** head_ref, vector<string> new_data)
{
	//make new node
    NodeInfo* node = new NodeInfo();
    node->setIfDir(new_data.at(0));
    node->setName(new_data.at(1));
    node->setParentName(new_data.at(2));
    if(*head_ref == nullptr || *head_ref == NULL){
        *head_ref = node; //This will create a new list if there is a nonexistant list
    }
    else{
        NodeInfo* curr = *head_ref;
        while(curr->next){ //This works to find the end of the list so that the node can be appended
            curr = curr->next;
        }
        curr->next = node;
        curr = nullptr;
    }
}

#define MAXLNSZ 256
/*
 * In my approach, I split the linked list into a directory list and a file list.
 * If you use a different approach, you can remove this function.
*/
void
split_into_lists(NodeInfo *tree_node)
{
    vector<string> words{};
    NodeInfo* curr = tree_node;
    words.push_back("0");
    words.push_back("1");
    words.push_back("2");//These are holding values
    while(curr){
        words.at(0) = to_string(curr->checkIfDir());
        words.at(1) = curr->getNodeName();
        words.at(2) = curr->getParentName();
        if(curr->checkIfDir() == true){
            words.at(0) = "dir"; //This needs to be done so that it can be qualified as a dir node
            append(&dir_list, words);
        }
        else{
            words.at(0) = "file"; //This needs to be done so that it can be qualified as a file node 
            append(&file_list, words);
        }
        curr = curr->next;
    }
}


/* Here I create sub-trees with directory as the parent, and files as the children. 
 * If you use a different approach, you can remove this function.
*/
void
create_subtrees()
{
	// Here, I traverse the directory and file lists, and add the files to the directories
    NodeInfo* curr = file_list;
    NodeInfo* curr2 = dir_list;
    while(curr){
        while(curr2){
            if(curr->getParentName() == curr2->getNodeName()){ //Goes through the list looking for a parent to match
                curr->parent = curr2; //Parent pointer assigned and added to the children vector of the parent
                curr2->children.push_back(curr);
            }
            curr2 = curr2->next;
        }
        curr = curr->next;
        curr2 = dir_list;//Starts at the beginning of the list
    }
}

void
printTree(NodeInfo *dir_node)
{
	// I do BF Traversal here using STL queue.
	// get the first element from the queue, and push all the children into the queue.
	// print the popped element for printing in BF traversal
	// https://en.cppreference.com/w/cpp/container/queue
	queue<NodeInfo *> q;
    NodeInfo* curr = nullptr;
    q.push(dir_node);//Add the root node to the tree
    while(!q.empty()){
        curr = q.front();//Look at the front of the queue
        q.pop();
        for(size_t i = 0; i < curr->children.size(); ++i){
            q.push(curr->children.at(i));//Add all of the children to the queue
        }
        std::cout << curr->getNodeName() << " ";//Print out what was the front of the queue
    }
    std::cout << std::endl;
        //cout << u->getNodeName() << " "; // Prints the popped element (the one in the front)
	//cout << endl;
}

void
nullify_seq()
{
	// Set the next pointer that we used in order to create the linked list in assignment 1 to NULL.
	// No matter what strategy to use, at the end of 3a, the only pointers that need to have an
	// address associated with them are parent and children nodes.
    NodeInfo* curr = dir_list;
    NodeInfo* curr2 = dir_list;
    queue<NodeInfo *> q;
    while(curr->getParentName() != "none"){ //Looks for the root, which should have no parents
        curr = curr->next;
    }
    tree_root = curr; //Assigns the root of the tree
    //std::cout << "The root node here should be: " <<curr->getNodeName() << std::endl;
    while(!q.empty()){//Works the same as the print function above
        curr = q.front();
        q.pop();
        curr2 = dir_list;
        while(curr2){
            if(curr2->getParentName() == curr->getNodeName()){
                curr2->next = NULL;
                q.push(curr2);
            }
            curr2 = curr2->next;
        }
    }
}

void
create_tree()
{
	/*
	 * I create my tree using the directory list. I create parent-children relationships
	 * between directories here. Here, I need the next pointer to traverse the list.
	 */
    NodeInfo* curr = dir_list;
    NodeInfo* curr2 = dir_list;
    queue<NodeInfo *> q;
    while(curr->getParentName() != "none"){
        curr = curr->next;
    }
    tree_root = curr;
    //std::cout << "The root node here should be: " <<curr->getNodeName() << std::endl;
    while(curr2){
        if(curr2->getParentName() == curr->getNodeName()){ //The logic here is identical to the nullify_seq function
            curr2->parent = curr;
            curr->children.push_back(curr2);
            q.push(curr2);
        }
        curr2 = curr2->next;
    }
    while(!q.empty()){
        curr = q.front();
        q.pop();
        curr2 = dir_list;
        while(curr2){
            if(curr2->getParentName() == curr->getNodeName()){//The logic here is identical to the nullify_seq function
                curr2->parent = curr;
                curr->children.push_back(curr2);
                q.push(curr2);
            }
            curr2 = curr2->next;
        }
    }
    

	nullify_seq(); // After the use of the next pointer is served, I set all next pointers to NULL.
}

int 
main(int argc, char **argv)
{
    string line;
    char *filename = (char *) malloc(MAXLNSZ * sizeof(char));
    NodeInfo *tree_node = NULL;
	if (argc != 2)
	{
		cerr << "Please input a file to read from" << endl;
		return EXIT_FAILURE; 
	}
    vector<string> lines{};
    vector<string> words;
    strcpy(filename, argv[1]);
    string files(filename);

    ifstream input_file(files);
    if (!input_file.is_open()) 
    {
        cerr << "Could not open the file - '"
             << files << "'" << endl;
        return EXIT_FAILURE;
    }

    while (getline(input_file, line))
    {
        lines.push_back(line);
        words = tokenize_input_string(line);
        append(&tree_node, words);
    }
	
	split_into_lists(tree_node); // Used in my way of creating the tree
	create_subtrees(); // Used in my way of creating the tree
#if PRINTLIST
	printf("Printing Directories\n");
    printList(dir_list);
	printf("Printing Files\n");
    printList(file_list);
#endif
	create_tree();
	printTree(tree_root); // Breadth First Traversal code should go here. 
							 // dir_list has the start node of the tree for me.
    input_file.close();
    delete tree_node;
    free(filename);
    filename = NULL;
    return EXIT_SUCCESS;
}

#endif