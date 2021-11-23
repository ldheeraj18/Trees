#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
    int info;
    struct tree *left;
    struct tree *right;
    int balance;
} tree;
///////////////////////////////////////////////////////////////////////////
tree *insert(tree *root, int data);
tree *insert_left_check(tree *root, int *factor);
tree *insert_left_balance(tree *root);
tree *insert_right_check(tree *root, int *factor);
tree *insert_right_balance(tree *root);
tree *delete (tree *root, int data);
tree *del_left_check(tree *root, int *smaller);
tree *del_right_check(tree *root, int *smaller);
tree *del_left_balance(tree *root, int *smaller);
tree *del_right_balance(tree *root, int *smaller);
tree *rot_left(tree *root);
tree *rot_right(tree *root);
void preorder(tree *root);
void inorder(tree *root);
void postorder(tree *root);
//////////////////////////////////////////////////////////////////////////
int main()
{
    tree *root = NULL;
    int n, data, choice;
    printf("Enter the number of elements you want to enter in the tree.\n");
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
    printf("\n\n");
    do
    {
        printf("1.Insert elements in the tree.\n");
        printf("2.Delete an element from the list.\n");
        printf("3.Search an element in the list.\n");
        printf("4.Display.\n");
        printf("0.Exit.\n");
        printf("************************************************\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n\n");
        switch (choice)
        {
        case 1:
            printf("Enter the number of elements you want to enter in the tree.\n");
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
            printf("\n\n");
            break;
        case 2:
            printf("Enter the element you want to delete: ");
            scanf("%d", &data);
            printf("\n");
            root = delete(root, data);
        case 4:
            printf("Preorder:\t");
            preorder(root);
            printf("\n");
            printf("Inorder:\t");
            inorder(root);
            printf("\n");
            printf("Postorder:\t");
            postorder(root);
            printf("\n\n");
        }
    }while(choice != 0);
    return 0;
}
tree *insert(tree *root, int data)
{
    static int factor;
    if (root == NULL)
    {
        root = (tree *)malloc(sizeof(tree));
        root->info = data;
        root->left = NULL;
        root->right = NULL;
        root->balance = 0;
        factor = 1;
    }
    else if (root->info > data)
    {
        root->left = insert(root->left, data);
        if (factor == 1)
            root = insert_left_check(root, &factor);
    }
    else if (root->info < data)
    {
        root->right = insert(root->right, data);
        if (factor == 1)
            root = insert_right_check(root, &factor);
    }
    else
        printf("Duplicate Node.\n");
    return root;
}
tree *insert_left_check(tree *root, int *factor)
{
    if (root->balance == -1)
    {
        root->balance = 0;
        *factor = 0;
    }
    else if (root->balance == 0)
        root->balance = 1;
    else
    {
        *factor = 0;
        root = insert_left_balance(root);
    }
    return root;
}
tree *insert_left_balance(tree *root)
{
    tree *next, *next2;
    next = root->left;
    if (next->balance == 1)
    {
        next->balance = 0;
        root->balance = 0;
        root = rot_right(root);
    }
    else
    {
        next2 = next->right;
        if (next2->balance == -1)
        {
            root->balance = 0;
            next->balance = 1;
        }
        else if (next2->balance == 1)
        {
            root->balance = -1;
            next->balance = 0;
        }
        else
        {
            root->balance = 0;
            next->balance = 0;
        }
        next2->balance = 0;
        root->left = rot_left(next);
        root = rot_right(root);
    }
    return root;
}
tree *insert_right_check(tree *root, int *factor)
{
    switch (root->balance)
    {
    case 1:
        root->balance = 0;
        *factor = 0;
        break;
    case 0:
        root->balance = -1;
        break;
    case -1:
        root = insert_right_balance(root);
        *factor = 0;
        break;
    }
    return root;
}
tree *insert_right_balance(tree *root)
{
    tree *next, *next2;
    next = root->right;
    if (next->balance == -1)
    {
        root->balance = 0;
        next->balance = 0;
        root = rot_left(root);
    }
    else
    {
        next2 = next->left;
        switch (next2->balance)
        {
        case -1:
            root->balance = 1;
            next->balance = 0;
            break;
        case 0:
            root->balance = 0;
            next->balance = 0;
            break;
        case 1:
            root->balance = 0;
            next->balance = -1;
        }
        next2->balance = 0;
        root->right = rot_right(next);
        root = rot_left(root);
    }
    return root;
}
tree *delete (tree *root, int data)
{
    static int shorter;
    if (root == NULL)
    {
        printf("Element not found.\n");
        shorter = 0;
    }
    else if (root->info > data)
    {
        root->left = delete (root->left, data);
        if (shorter)
            root = del_left_check(root, &shorter);
    }
    else if (root->info < data)
    {
        root->right = delete (root->right, data);
        if (shorter)
            root = del_right_check(root, &shorter);
    }
    else
    {
        tree *ptr, *temp;
        if (root->left != NULL && root->right != NULL)
        {
            ptr = root->right;
            while (ptr->left != NULL)
                ptr = ptr->left;
            root->info = ptr->info;
            root->right = delete (root->right, ptr->info);
            if (shorter)
                root = del_right_check(root, &shorter);
        }
        else
        {
            temp = root;
            if (root->left != NULL)
                root = root->left;
            else if (root->right != NULL)
                root = root->right;
            else
                root = NULL;
            free(temp);
            shorter = 1;
            printf("Element successfully removed from the tree.\n");
        }
    }
    return root;
}
tree *del_left_check(tree *root, int *smaller)
{
    switch (root->balance)
    {
    case 1:
        root->balance = 0;
        break;
    case 0:
        root->balance = -1;
        *smaller = 0;
        break;
    case -1:
        root = del_right_balance(root, smaller);
    }
    return root;
}
tree *del_right_balance(tree *root, int *smaller)
{
    tree *ptr, *n_ptr;
    ptr = root->right;
    if (ptr->balance == -1)
    {
        root->balance = 0;
        ptr->balance = 0;
        root = rot_left(root);
        // *smaller = 0;
    }
    else if (ptr->balance == 0)
    {
        root->balance = -1;
        ptr->balance = 1;
        root = rot_left(root);
        *smaller = 0;
    }
    else
    {
        n_ptr = ptr->left;
        switch (n_ptr->balance)
        {
        case -1:
            root->balance = 1;
            ptr->balance = 0;
            break;
        case 0:
            root->balance = 0;
            ptr->balance = 0;
            break;
        case 1:
            root->balance = 0;
            ptr->balance = -1;
            break;
        }
        n_ptr->balance = 0;
        root->right = rot_right(ptr);
        root = rot_left(root);
    }
    return root;
}
tree *del_right_check(tree *root, int *smaller)
{
    switch (root->balance)
    {
    case 0:
        root->balance = 1;
        *smaller = 0;
        break;
    case -1:
        root->balance = 0;
        break;
    case 1:
        root = del_left_balance(root, smaller);
    }
    return root;
}
tree *del_left_balance(tree *root, int *smaller)
{
    tree *ptr, *n_ptr;
    ptr = root->left;
    if (ptr->balance == 1)
    {
        root->balance = 0;
        ptr->balance = 0;
        root = rot_right(root);
    }
    else if (ptr->balance == 0)
    {
        root->balance = 1;
        ptr->balance = -1;
        root = rot_right(root);
        *smaller = 0;
    }
    else
    {
        n_ptr = ptr->right;
        switch (n_ptr->balance)
        {
        case 0:
            root->balance = 0;
            ptr->balance = 0;
            break;
        case 1:
            root->balance = -1;
            ptr->balance = 0;
            break;
        case -1:
            root->balance = 0;
            ptr->balance = 1;
            break;
        }
        n_ptr->balance = 0;
        root->left = rot_left(ptr);
        root = rot_right(root);
    }
    return root;
}
tree *rot_left(tree *root)
{
    tree *ptr = root->right;
    root->right = ptr->left;
    ptr->left = root;
    // root = ptr;
    return ptr;
}
tree *rot_right(tree *root)
{
    tree *ptr = root->left;
    root->left = ptr->right;
    ptr->right = root;
    // root = ptr;
    return ptr;
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