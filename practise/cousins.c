#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} tree;

// Utility function to create a new node
tree* createNode(int val) {
    tree *newNode = (tree*)malloc(sizeof(tree));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}



// Recursive function to build the tree using preorder and inorder traversals
tree* buildTree(int inorder[], int preorder[], int ins, int ine, int pres,int pree) {
    if (ins > ine || pres>pree) {
        return NULL;
    }

    // Select the current node from preorder traversal
    int head=preorder[pres];
    int index=0;
        tree *root = createNode(head);
    for (index = ins; index <= ine; index++) {
        if (inorder[index] == head) {
            break;
        }
    }
    int lgap=index-ins;

    // Build the left and right subtrees
    root->left = buildTree(inorder, preorder, ins, index - 1, pres+1,pres+lgap);
    root->right = buildTree(inorder, preorder, index + 1, ine, pres+lgap+1,pree);

    return root;
}

// Function to print postorder traversal
void postOrder(tree *root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->val);
}

// Function to check if two nodes are cousins
int getLevel(tree *root, int node, int level) {
    if (root == NULL) {
        return 0;
    }
    if (root->val == node) {
        return level;
    }
    int leftLevel = getLevel(root->left, node, level + 1);
    if (leftLevel != 0) {
        return leftLevel;
    }
    return getLevel(root->right, node, level + 1);
}

// Function to check if two nodes have the same parent
int isSibling(tree *root, int a, int b) {
    if (root == NULL) {
        return 0;
    }
    return ((root->left && root->right && root->left->val == a && root->right->val == b) ||
            (root->left && root->right && root->left->val == b && root->right->val == a) ||
            isSibling(root->left, a, b) || isSibling(root->right, a, b));
}

// Function to check if two nodes are cousins
void cousin(tree *root, int a, int b) {
    if ((getLevel(root, a, 1) == getLevel(root, b, 1)) && !isSibling(root, a, b)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int main() {
    int inorder[100], preorder[100], n, a, b;
    tree *root = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

    root = buildTree(inorder, preorder, 0, n - 1, 0,n-1);

    char c;
    do {
        scanf("%c",&c);
        switch (c) {
        case 'i':
            
            break;

        case 'p':
            printf("PostOrder Traversal: ");
            postOrder(root);
            printf("\n");
            break;

        case 'c':
            printf("Enter two nodes to check if they are cousins: ");
            scanf("%d %d", &a, &b);
            cousin(root, a, b);
            break;

        case 'e':
            break;

        }

    } while (c != 'e');

    return 0;
}
