/*
BST Implementation in C

Team Members:
Batuhan Yıldız
Can Mızraklı
Gökay Toğa

Current Problems by Batuhan Yıldız:
Incorrect program output
--- Input ---
CONSTRUCT [31,65,3,10,5,100,3,12]
LIST
DELETE 5
LIST
DELETE 65
LIST
PARENT 100
DELETE 31
DELETE 100
LIST

--- Program output ---
3 3 5 10 12 31 65 100
Root changed. The new root is 31
3 3 10 12 31 65 100
Root changed. The new root is 31
3 3 10 12 31 100
The parent of 100 is 31
Root changed. The new root is 100
Root changed. The new root is 3
3 3 10 12

--- Expected output (text)---
3 3 5 10 12 31 65 100
3 3 10 12 31 65 100
3 3 10 12 31 100
The parent of 100 is 31
Root changed. The new root is 100
Root changed. The new root is 3
3 3 10 12

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node *root = NULL;

struct Node* insert(int key);
void freeTree(struct Node* root) ;

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

/*
The  CONSTRUCT  command  expects  a  set  of  integers  in  brackets  separated  by  commas.  The 
command takes the input and constructs a binary tree rooted at the first element of the input.   
For example, for the input given below, your program should construct a tree as shown in Figure 1. 
 CONSTRUCT [31, 65, 3, 10, 5, 100, 3, 12]
*/
struct Node* construct(int keys[]){
    int size = sizeof(keys) / sizeof(keys[0]);
    struct Node* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(keys[i]);
    }
    return root;
}


/*
The INSERT command expects a single integer. It creates a new node and places the node in the 
correct position in the tree. For example, INSERT 55, places the value 55 in the correct position as 
shown in Figure 2 and outputs:  
The parent of 55 is 65
*/
struct Node* insert(int key) {
    // If the tree is empty, create a new node
    if (root == NULL) {
        root = createNode(key);
        return root;
    }

    struct Node *current = root;
    struct Node *parent = NULL;

    // Find the appropriate position to insert the new node
    while (current != NULL) {
        parent = current;
        if (key <= current->key) { 
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Create the new node
    struct Node *newNode = createNode(key);

    // Insert the new node at the appropriate position
    if (key <= parent->key) {
        parent->left = newNode;
        newNode->parent = parent;
    } else {
        parent->right = newNode;
        newNode->parent = parent;
    }

}


/*
The  LIST  command  performs  inorder traversal  on  the  tree (see  Figure  3) and  prints  the  keys  of 
every  visiting  node.  Observe  that  inorder  traversal  of  the  BST  prints  sorted  list  in  ascending 
order.  For  example,  LIST  command  that  is  given  after  previous  two  example  commands,  the 
output will be: 
3 3 5 10 12 31 55 65 100
*/
void list(){
    if (root != NULL) {
        list(root->left);
        printf("%d ", root->key);
        list(root->right);
    }
}

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
void parent(int key){

    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (parent == NULL) {
        printf("It is a root node\n");
    } else {
        printf("The parent of %d is %d\n", key, parent->key);
    }

}
//Method to find the parent of the given key
struct Node* findParent(int key) {
    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return parent;
}

/*
The  DELETE  command  expects  one  integer  value.  Its  purpose  is  to  find  the  given  value  in  the 
tree  and  delete  it. The state  of the tree  after deletion should still obey  the  rules specified  above. 
Also  observe  that  the  root of  the  tree  might  change after  delete  operation.  You should  maintain 
the  order  of  the  tree  and  reconnect  the  parent/child  connections.  Figure  4  shows  three  different 
scenarios of delete operation: a node has no children, has single child and has two children.
*/

struct Node* delete(int key) {
    // Base case: If the tree is empty
    if (root == NULL) {
        return root;
    }

    struct Node *current = root;
    struct Node *parent = NULL;

    // Find the node to delete and its parent
    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // If the key is not found, return NULL
    if (current == NULL) {
        return NULL;
    }

    // Node with only one child or no child
    if (current->left == NULL) {
        if (parent == NULL) {
            root = current->right;
        } else if (current == parent->left) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        free(current);
    } else if (current->right == NULL) {
        if (parent == NULL) {
            root = current->left;
        } else if (current == parent->left) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        free(current);
    }

    // Node with two children: Get the inorder successor 
    struct Node* successor = minValueNode(current->right);

    // Copy the inorder successor's content to this node
    current->key = successor->key;

    // Delete the inorder successor
    current->right = delete(successor->key);

}


int main() {
    
    //struct Node* root = NULL;
    char line[100];
    char command[20];
    int key;

    while (fgets(line, sizeof(line), stdin) != NULL) {//while loop for reading inputs
        sscanf(line, "%s", command);
        if (strcmp(command, "CONSTRUCT") == 0) {// checks the commands for CONSTRUCT
            int keys[20];
            int size = 0;
            char *token = strtok(line, "[,]");
            while (token != NULL) {// While loop for takin the inputs
                if (sscanf(token, "%d", &key) == 1) {
                    keys[size++] = key;
                }
                token = strtok(NULL, "[,]");
            }
            construct(keys);
        } else if (strcmp(command, "INSERT") == 0) {// checks the commands for INSERT
            sscanf(line, "INSERT %d", &key);
            insert(key);// inserts root
            struct Node* parent = findParent(key);
            if (parent != NULL) {// if no parent it sets parent
                printf("The parent of %d is %d\n", key, parent->key);
            }
        } else if (strcmp(command, "LIST") == 0) {// checks the commands for LIST
            list();//prints inorder traversal
            printf("\n");
        } else if (strcmp(command, "DELETE") == 0) {// checks the commands for DELETE
            int temp = root->key;
            sscanf(line, "DELETE %d", &key);
            delete(key);//deletes the wanted node
            if (root != NULL && root->key != temp) {
                printf("Root changed. The new root is %d\n", root->key);
            }
        } else if (strcmp(command, "PARENT") == 0) {// checks the commands for PARENT
            sscanf(line, "PARENT %d", &key);
            parent(key);
        }
    }

    freeTree(root);//frees the space used by the tree
    return 0;    
}
void freeTree(struct Node* root) {//free method
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}