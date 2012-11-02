#include "BST.h"
#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
#include <math.h>

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  
  Node<T>* goal = findOutsourced(root,v);
  
  if(goal!=0)
  	return goal->getValue()==v;
  return false;
}

template <typename T>
Node<T>* BST<T>::findOutsourced(Node<T>* head, T v){
	
	if(head == 0) return head;

	if(head->getValue()<v){
		return findOutsourced(head->getRightChild(),v);
	}else if(head->getValue()>v){
		return findOutsourced(head->getLeftChild(),v);
	}else{
		return head;
	}
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>** temp = &root;
  while(*temp!=0 && (*temp)->getValue()!=v){
	if((*temp)->getValue()<v)
	    temp = &((*temp)->getRightChild());
	else{
	    temp = &((*temp)->getLeftChild());
	}
  }
  if(*temp==0) return;
  Node<T>** ios = temp;
  
  if((*temp)->getRightChild()==0){
	Node<T>* something = (*temp);
	(*temp) = (*temp)->getLeftChild();
	delete something;
  }else{
	ios = &((*ios)->getRightChild());
	
	bool hIos = (*ios)->getLeftChild()==0;
	
	while((*ios)->getLeftChild()!=0){
		ios = &((*ios)->getLeftChild());
	}
  	
	Node<T>* leftTree = (*temp)->getLeftChild();
	Node<T>* rightTree = (*temp)->getRightChild();
	Node<T>* iosRight = (*ios)->getRightChild();

	(*ios)->setLeftChild(*leftTree);
	(*temp) = (*ios);
	
	if(!hIos){
		rightTree->setLeftChild(*iosRight);
		(*temp)->setRightChild(*rightTree);	
   	}
   }
   
}

template <typename T>
void BST<T>::treePrint(){
	std::list<Node<T>* > s;
	
	std::vector<std::vector<bool> > isPresent;
	std::vector<std::vector<T> > levels;
	std::vector<T> someRows;
	std::vector<bool> someOtherRow;
	levels.push_back(someRows);
	isPresent.push_back(someOtherRow);
	
	levels[0].push_back(root->getValue());
	isPresent[0].push_back(true);	
	
	s.push_front(root);
	
	int currentLevel = 1;
	int nextLevel = 0;
	int depth = 1;
	
	while(!s.empty()){
		Node<T>* val = s.front();
		s.pop_front();
		
		currentLevel--;
		
		std::vector<T> row;
		std::vector<bool> otherRow;
		levels.push_back(row);
		isPresent.push_back(otherRow);
	
		if(val->getLeftChild()!=0){
			s.push_back(val->getLeftChild());
			levels[depth].push_back(val->getLeftChild()->getValue());
			isPresent[depth].push_back(true);
			nextLevel++;
		}else{
			isPresent[depth].push_back(false);
		}
		
		if(val->getRightChild()!=0){
		        s.push_back(val->getRightChild());
			levels[depth].push_back(val->getRightChild()->getValue());
			isPresent[depth].push_back(true);
			nextLevel++;
		}else{
			isPresent[depth].push_back(false);	
		}
		
		if(currentLevel==0){
			depth++;
			currentLevel = nextLevel;
			nextLevel = 0;
		}
	}
	
	int width;

	for(int i = 0; i < depth;i++){	
		width = pow(1.625,depth-i-1);
		if(isPresent[i][0]){
			std::cout << std::setw(width) << levels[i][0];
		}else{
			std::cout << std::setw(width) << " ";
		}

		for(int j = 1; j < (int)levels[i].size();j++){
			if(isPresent[i][j]){
				std::cout << std::setw(pow(1.75,depth-i-1)) << 
					std::setfill(' ') << levels[i][j];
			}else{
				std::cout << std::setw(pow(1.75,depth-i-1)) << 
					std::setfill(' ') << " ";
			}
		}
		std::cout << std::endl;
			
	}	
}


template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
