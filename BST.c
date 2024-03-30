/*
BST Implementation in C

Team Members:
Batuhan Yıldız
Can Mızraklı
Gökay Toğa
*/

#include <stdio.h>
/*
The  CONSTRUCT  command  expects  a  set  of  integers  in  brackets  separated  by  commas.  The 
command takes the input and constructs a binary tree rooted at the first element of the input.   
For example, for the input given below, your program should construct a tree as shown in Figure 1. 
 CONSTRUCT [31, 65, 3, 10, 5, 100, 3, 12]
*/
int construct(int[]);

/*
The INSERT command expects a single integer. It creates a new node and places the node in the 
correct position in the tree. For example, INSERT 55, places the value 55 in the correct position as 
shown in Figure 2 and outputs:  
The parent of 55 is 65
*/
int insert(int);

/*
The  LIST  command  performs  inorder traversal  on  the  tree (see  Figure  3) and  prints  the  keys  of 
every  visiting  node.  Observe  that  inorder  traversal  of  the  BST  prints  sorted  list  in  ascending 
order.  For  example,  LIST  command  that  is  given  after  previous  two  example  commands,  the 
output will be: 
3 3 5 10 12 31 55 65 100
*/
int* list();

/*
The  PARENT  command  takes  the  input  value,  searches  it  in  the  tree  and  prints  its  parent.  For 
example: 
 
PARENT 12 
The parent of 12 is 10 
PARENT 31 
It is a root node 
Note:  You can assume that there are no errors in the input. Hence, you do not need to explicitly 
check for correctness of the provided input. 
             Here are some sample runs
*/
int parent(int);

/*
The  DELETE  command  expects  one  integer  value.  Its  purpose  is  to  find  the  given  value  in  the 
tree  and  delete  it. The state  of the tree  after deletion should still obey  the  rules specified  above. 
Also  observe  that  the  root of  the  tree  might  change after  delete  operation.  You should  maintain 
the  order  of  the  tree  and  reconnect  the  parent/child  connections.  Figure  4  shows  three  different 
scenarios of delete operation: a node has no children, has single child and has two children.
*/
int delete(int);

int main() {
    
    
    return 0;
}