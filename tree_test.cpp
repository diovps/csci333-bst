#include "BST.h"
#include <iostream>
#include <string>

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(10);
  bst->insert(5);
  bst->insert(7);
  bst->insert(3);
  bst->insert(8);
  bst->insert(15);
  bst->insert(18);
  bst->insert(16);
  bst->insert(12);
  bst->insert(11);
  bst->insert(17);
  bst->treePrint();
}
