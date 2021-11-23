#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
    struct tree *left;
    int info;
    struct tree *right;
} tree;
////////////////////////////////////////////////////////////////////////
tree *insert(tree *root, int data);
tree *delete (tree *root, int data);
int search(tree *root, int data);
void preorder(tree *root);
void inorder(tree *root);
void postorder(tree *root);
int height(tree *root);
int max(tree *root);
int min(tree *root);
////////////////////////////////////////////////////////////////////////
int main()
{
    tree *root = NULL;
    int n, data, choice, h, maximum, minimum, s;
    printf("Create a Binary Search Tree.\n\n\n");
    printf("Enter the number of nodes you want to create.\n");
    scanf("%d", &n);
    printf("Enter the elements you want to insert.\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        root = insert(root, data);
    }
    printf("Tree has been successfully created.\n");
    printf("Preorder:\t");
    preorder(root);
    printf("\n");
    printf("Inorder:\t");
    inorder(root);
    printf("\n");
    printf("Postorder:\t");
    postorder(root);
    printf("\n");
    do
    {
        printf("1.Insert element in the tree.\n");
        printf("2.Delete an element in the tree.\n");
        printf("3.Search an element in the tree.\n");
        printf("4.Find the height of the tree.\n");
        printf("5.Find the maximum element in the tree.\n");
        printf("6.Find the minimum element in the tree.\n");
        printf("0.Exit.\n");
        printf("****************************************************\n\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the number of nodes you want to insert.\n");
            scanf("%d", &n);
            printf("Enter the elements you want to insert.\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &data);
                root = insert(root, data);
            }
            printf("Tree has been successfully updated.\n");
            printf("Preorder:\t");
            preorder(root);
            printf("\n");
            printf("Inorder:\t");
            inorder(root);
            printf("\n");
            printf("Postorder:\t");
            postorder(root);
            printf("\n");
            break;
        case 2:
            printf("Enter the element you want to delete.\n");
            scanf("%d", &data);
            root = delete(root, data);
            printf("Tree has been successfully updated.\n");
            printf("Preorder:\t");
            preorder(root);
            printf("\n");
            printf("Inorder:\t");
            inorder(root);
            printf("\n");
            printf("Postorder:\t");
            postorder(root);
            printf("\n");
            break;
        case 3:
            printf("Enter the element you would like to search in the tree.\n");
            scanf("%d", &data);
            s = search(root, data);
            if(s==1)
                printf("Element found.\n");
            else
                printf("%d is not present in the tree.\n");
            break;
        case 4:
            h = height(root);
            if(h == -1)
            printf("Empty tree.\n");
            else
            printf("Height of the tree is %d\n", h);
            break;
        case 5:
            maximum = max(root);
            if(maximum == -1)
            printf("Empty tree.\n");
            else
            printf("The maximum element in the tree is %d\n", maximum);
            break;
        case 6:
            minimum = min(root);
            if(minimum == -1)
            printf("Empty tree.\n");
            else
            printf("The minimum element in the tree is %d\n", minimum);
            break;
        }
    } while (choice != 0);
    return 0;
}
tree *insert(tree *root, int data)
{
    if (root == NULL)
    {
        root = (tree *)malloc(sizeof(tree));
        root->info = data;
        root->left = NULL;
        root->right = NULL;
    }
    else if (root->info > data)
        root->left = insert(root->left, data);
    else if (root->info < data)
        root->right = insert(root->right, data);
    else
        printf("Duplicate Key.\n");
    return root;
}
int search(tree *root, int data)
{
    if (root == NULL)
        return 0;
    else if (root->info > data)
        return search(root->left, data);
    else if (root->info < data)
        return search(root->right, data);
    else
        return 1;
}
int height(tree *root)
{
    int h_left, h_right;
    if (root == NULL)
        return -1;
    h_left = height(root->left);
    h_right = height(root->right);
    if (h_left > h_right)
        return h_left + 1;
    else
        return h_right + 1;
}
int max(tree *root)
{
    if (root == NULL)
        return -1;
    else if (root->right == NULL)
        return root->info;
    else
        return max(root->right);
}
int min(tree *root)

{
    if (root == NULL)
        return -1;
    else if (root->left == NULL)
        return root->info;
    else
        return min(root->left);
}
void preorder(tree *root)
{
    if (root == NULL)
        return;
    else
    {
        printf("%d--", root->info);
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(tree *root)
{
    if (root == NULL)
        return;
    else
    {
        inorder(root->left);
        printf("%d--", root->info);
        inorder(root->right);
    }
}
void postorder(tree *root)
{
    if (root == NULL)
        return;
    else
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d--", root->info);
    }
}
tree *delete (tree *root, int data)
{
    tree *succ, *temp;
    if (root == NULL)
    {
        printf("Element Not present in the tree.\n");
        return root;
    }
    else if (root->info > data)
        root->left = delete (root->left, data);
    else if (root->info < data)
        root->right = delete (root->right, data);
    else
    {
        if (root->left != NULL && root->right != NULL)
        {
            succ = root->right;
            while (succ->left != NULL)
                succ = succ->left;
            root->info = succ->info;
            root->right = delete (root->right, succ->info);
        }
        else
        {
            temp = root;
            if (root->left != NULL)
                root = root->left;
            else
                root = root->right;
            free(temp);
        }
    }
    return root;
}