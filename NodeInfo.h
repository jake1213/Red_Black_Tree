#ifndef _NODEINFO_H
#define _NODEINFO_H

#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
//#include <bits/stdc++.h>

#define PRINTLIST 0

using namespace std;

class NodeInfo
{
    private:
        bool is_dir;
        string name;
        string p_name;

    public:
        NodeInfo();
        NodeInfo *parent; // This can be public or private
        NodeInfo *next;
        vector<NodeInfo *> children; // This can be public or private
        void setIfDir(string);
        void setName(string);
        void setParentName(string);
        //void setParent(string); // Will need to use this if parent is private
        void setNodeType(bool);
        bool checkIfDir();
        string getNodeName();
        string getParentName();
        //NodeInfo* getParent(); // Will need to use this if parent is private
		//void addChild(NodeInfo *); // Will need to use this if children is private
        //vector<NodeInfo *> getChildren(); // Will need to use this if children is private
};
/* I needed these two lists for my implementation */
extern NodeInfo *dir_list;
extern NodeInfo *file_list;
extern NodeInfo* tree_root;

NodeInfo::NodeInfo(){
      is_dir = false;
      name = "";
      p_name = "";
      parent = nullptr;
      next = nullptr;
      vector<NodeInfo> children;
  }

inline string
NodeInfo::getParentName()
{
    return p_name;
}

inline void
NodeInfo::setNodeType(bool nType)
{
	// might have been set in assignment 1; depends on implementation.
}

inline void
NodeInfo::setParentName(string par_name)
{
    p_name = par_name;
}

//inline void
//NodeInfo::setParent(string par_name)
//{
    // Will need to use this if parent is private
//}

inline void
NodeInfo::setIfDir(string dir_str)
{
	std::string test_str = dir_str.substr(0, 3);
    if(test_str.compare(dir_str) == 0){
        this->is_dir = true;
    }
    else{
        this->is_dir = false;
    }
}

inline void
NodeInfo::setName(string name_str)
{
	name = name_str;
}

inline bool
NodeInfo::checkIfDir()
{
    return is_dir;
}

inline string
NodeInfo::getNodeName()
{
    return name;
}

//inline NodeInfo*
//NodeInfo::getParent()
//{
    // Will need to use this if parent is private
//}

//inline vector<NodeInfo *>
//NodeInfo::getChildren()
//{
    // Will need to use this if parent is private
//}

void printList(NodeInfo *);
void append(NodeInfo**, vector<string>);
vector<string> tokenize_input_string(string);

#endif