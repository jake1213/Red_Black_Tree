//#ifndef _PRINTLIST_CPP
//#define _PRINTLIST_CPP

#include "../include/NodeInfo.h"

/*
 * This function prints contents of the linked list
 */
void printList(NodeInfo *node)
{
	NodeInfo* curr = node;
	while(curr){
		std::cout << curr->getNodeName();
		if(curr->checkIfDir()){
			std::cout << " 1";
		}
		else{
			std::cout << " 0";
		}
		std::cout << std::endl;
		curr = curr->next;
	}
}

//#endif