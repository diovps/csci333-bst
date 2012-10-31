#include "BST.h"
#include <iostream>
#include <list>
#include <vector>

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
	
	std::vector<std::vector<T> > levels;

	s.push_front(root);
	int currentLevel = 1;
	int nextLevel = 0;
	int depth = 0;
	
	while(!s.empty()){
		Node<T>* val = s.front();
		s.pop_front();
		
		//std::cout << val->getValue() << " ";
		currentLevel--;
		
		std::vector<T> row;
		levels.push_back(row);

		if(val->getLeftChild()!=0){
			s.push_back(val->getLeftChild());
			levels[depth].push_back(val->getLeftChild()->getValue());
			nextLevel++;
		}else{
			levels[depth].push_back(0);
		}
		
		if(val->getRightChild()!=0){
		        s.push_back(val->getRightChild());
			levels[depth].push_back(val->getRightChild()->getValue());
			nextLevel++;
		}else{
			levels[depth].push_back(0);	
		}
		
		if(currentLevel==0){
			depth++;
			/*std::cout << "Depth: " << depth << std::endl;
			std::cout << std::endl; 
			std::cout << std::endl;
			*/
			currentLevel = nextLevel;
			nextLevel = 0;
		}
	}
		
	for(int i = 0; i < depth; i++){
		for(int j = 0; j < (int)levels[i].size(); j++){
			if(levels[i][j] == 0){
				std::cout << "       ";
			}else{
				std::cout << levels[i][j];
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
//template class BST<std::string>;
