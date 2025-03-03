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


struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node* insert(struct Node* root, int key);
void freeTree(struct Node* root) ;
void inorder(struct Node* root);

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

struct Node* deleteNode(struct Node* root, int key) {
    // Base case: If the tree is empty
    if (root == NULL) {
        return root;
    }

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    // If key is same as root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
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
        root = insert(root, keys[i]);
    }
    return root;
}


/*
The INSERT command expects a single integer. It creates a new node and places the node in the 
correct position in the tree. For example, INSERT 55, places the value 55 in the correct position as 
shown in Figure 2 and outputs:  
The parent of 55 is 65
*/
struct Node* insert(struct Node* root, int key){

    if (root == NULL) {
        return createNode(key);
    }

    // Otherwise, recur down the tree
    if (key <= root->key) { // Allow duplicates by using <= instead of <
        struct Node* leftChild = insert(root->left, key);
        root->left = leftChild;
        leftChild->parent = root; // Update parent pointer
    } else {
        struct Node* rightChild = insert(root->right, key);
        root->right = rightChild;
        rightChild->parent = root; // Update parent pointer
    }

    // Return the unchanged node pointer
    return root;
}

/*
The  LIST  command  performs  inorder traversal  on  the  tree (see  Figure  3) and  prints  the  keys  of 
every  visiting  node.  Observe  that  inorder  traversal  of  the  BST  prints  sorted  list  in  ascending 
order.  For  example,  LIST  command  that  is  given  after  previous  two  example  commands,  the 
output will be: 
3 3 5 10 12 31 55 65 100
*/
void list(struct Node* root){

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
void parent(struct Node* root, int key){

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

struct Node* findParent(struct Node* root, int key) {
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
struct Node* delete(struct Node* root, int key){
    // Base case: If the tree is empty
    if (root == NULL) {
        return root;
    }

    // Recur down the tree
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}


int main() {
    
    struct Node* root = NULL;
    char line[100];
    char command[20];
    int key;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        sscanf(line, "%s", command);
        #include <string.h>
        if (strcmp(command, "CONSTRUCT") == 0) {
            int keys[20];
            int size = 0;
            char *token = strtok(line, "[,]");
            while (token != NULL) {
                if (sscanf(token, "%d", &key) == 1) {
                    keys[size++] = key;
                }
                token = strtok(NULL, "[,]");
            }
            for (int i = 0; i < size; i++) {
                root = insert(root, keys[i]);
            }
        } else if (strcmp(command, "INSERT") == 0) {
            sscanf(line, "INSERT %d", &key);
            root = insert(root, key);
            struct Node* parent = findParent(root, key);
            if (parent != NULL) {
                printf("The parent of %d is %d\n", key, parent->key);
            }
        } else if (strcmp(command, "LIST") == 0) {
            //printf("Inorder traversal of the BST: ");
            inorder(root);
            printf("\n");
        } else if (strcmp(command, "DELETE") == 0) {
            int temp = root->key;
            sscanf(line, "DELETE %d", &key);
            root = deleteNode(root, key);
            if (root != NULL && root->key != temp) {
                printf("Root changed. The new root is %d\n", root->key);
            }
        } else if (strcmp(command, "PARENT") == 0) {
            sscanf(line, "PARENT %d", &key);
            struct Node* parent = findParent(root, key);
            if (parent == NULL) {
                printf("It is a root node\n");
            } else {
                printf("The parent of %d is %d\n", key, parent->key);
            }
        }
    }

    freeTree(root);
    return 0;    
}
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}