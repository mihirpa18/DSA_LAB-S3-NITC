#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct car
{
    int mdnum;
    char *mdname;
    int price;
    struct car *parent;
    struct car *left;
    struct car *right;
} car;

car *Create_Node(int mdnum, char *mdname, int price)
{
    car *new = malloc(sizeof(car));
    new->mdname = malloc(strlen(mdname) + 1);
    new->mdnum = mdnum;
    strcpy(new->mdname, mdname);
    new->price = price;
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;

    return new;
}

car *Add(car *root, int mdnum, char *mdname, int price)
{
    if (root == NULL)
    {
        return Create_Node(mdnum, mdname, price);
    }
    if (root->mdnum > mdnum)
    {
        root->left = Add(root->left, mdnum, mdname, price);
        root->left->parent = root;
    }
    else
    {
        root->right = Add(root->right, mdnum, mdname, price);
        root->right->parent = root;
    }
    return root;
}

car *search(car *root, int mdnum)
{
    if (root == NULL || root->mdnum == mdnum)
    {
        return root;
    }
    if (root->mdnum < mdnum)
    {
        return search(root->right, mdnum);
    }
    else
    {
        return search(root->left, mdnum);
    }
}

car *ipre(car *root)
{
    if (root == NULL || root->left == NULL)
    {
        return NULL;
    }
    root = root->left;
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

car *Delete(car *root, car *x)
{

    if (root == NULL)
    {
        printf("-1\n");
        return NULL;
    }
    if (root->mdnum > x->mdnum)
    {
        root->left = Delete(root->left, x);
    }
    else if (root->mdnum < x->mdnum)
    {
        root->right = Delete(root->right, x);
    }

    else if (root->left==NULL && root->right == NULL)
    {
        free(root);
        return NULL;
    }

    else if (root->left == NULL)
    {
        car *temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL)
    {
        car *temp = root->left;
        free(root);
        return temp;
    }
    else
    {
        car *ipred = ipre(root);
        root->mdnum = ipred->mdnum;
        root->left = Delete(root->left, ipred);
    }
    return root;
}

void inorder(car *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->mdnum);
        printf("%s ", root->mdname);
        printf("%d\n", root->price);
        inorder(root->right);
    }
}

void preorder(car *root)
{
    if (root != NULL)
    {
        printf("%d ", root->mdnum);
        printf("%s ", root->mdname);
        printf("%d\n", root->price);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(car *root)
{
    if (root != NULL)
    {
        preorder(root->left);
        preorder(root->right);
        printf("%d ", root->mdnum);
        printf("%s ", root->mdname);
        printf("%d\n", root->price);
    }
}

void modify(car *root, int mdnum, int new_price)
{
    car *temp = search(root, mdnum);
    if(temp!=NULL){
        temp->price = new_price;
    }

}

int main()
{
    car *root = NULL;
    char c;
    int mdnum, price, mdnum2;
    char mdname[100];
    int mdnum3, mdnum4,moprice;
    do
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'a':
            scanf("%d", &mdnum);
            scanf("%s", mdname);

            scanf("%d", &price);
            root = Add(root, mdnum, mdname, price);
            break;

        case 's':
            scanf("%d", &mdnum4);
            car *tp = search(root, mdnum4);
            if (tp == NULL)
            {
                printf("-1\n");
            }
            else
                printf("%d %s %d\n", tp->mdnum, tp->mdname, tp->price);
            break;

        case 'i':
            inorder(root);
            break;


        case 'p':
            preorder(root);
            break;

        case 't':
            postorder(root);
            break;


        case 'd':
            scanf("%d", &mdnum2);
            car *x = search(root, mdnum2);
            if (x == NULL)
            {
                printf("-1\n");
            }
            root = Delete(root, x);
            break;

        case 'm':

            scanf("%d",&mdnum3);
            scanf("%d",&moprice);
            car *temp = search(root, mdnum3);
            modify(root,temp->mdnum,moprice);
            if (temp == NULL)
            {
                printf("-1\n");
            }
            else
                printf("%d %s %d\n", temp->mdnum, temp->mdname, temp->price);
            break;

        case 'e':
            break;

        }
    } while (c != 'e');
    return 0;
}