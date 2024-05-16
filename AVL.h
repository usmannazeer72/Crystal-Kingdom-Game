//#pragma once
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//using namespace std;
//
//class TreeNode {
//public:
//    int id;
//    int reward_score;
//    int count;
//    TreeNode* left;
//    TreeNode* right;
//    int height;
//    char val;
//    TreeNode* next;
//    TreeNode* down;
//};
//
//int height(TreeNode* Avlnode)
//{
//    if (Avlnode == NULL)
//    {
//        return 0;
//    }
//    return Avlnode->height;
//}
//int calculateScore(char** arr, int rows, int cols) {
//    int score = 0;
//    bool reachedStar = false;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            if (reachedStar) {
//                // player has reached '*', stop counting score
//                return score;
//            }
//            switch (arr[i][j]) {
//            case 'C':
//                score += 1;
//                break;
//            case 'P':
//                score += 70;
//                break;
//            case 'J':
//                score += 50;
//                break;
//            case 'W':
//                score += 30;
//                break;
//            case '%':
//                score = 0;
//                break;
//            case '#':
//                score -= 2;
//            case '&':
//                score -= 1;
//            case '$':
//                score -= 1;
//            case '@':
//                score -= 1;
//            case '*':
//                reachedStar = true;
//                break;
//            default:
//                // do nothing for other characters
//                break;
//            }
//        }
//    }
//    return score;
//}
//
//
//TreeNode* newNode(int reward_score, int id = -1)
//{
//    TreeNode* Avlnode = new TreeNode();
//    Avlnode->reward_score = reward_score;
//    if (id == -1)
//    {
//        Avlnode->id = rand() % 200 + 1;
//    }
//    else
//    {
//        Avlnode->id = id;
//    }
//    Avlnode->count = 1;
//    Avlnode->left = NULL;
//    Avlnode->right = NULL;
//    Avlnode->height = 1;
//    return Avlnode;
//}
//
//TreeNode* leftRotate(TreeNode* AVL_x)
//{
//    TreeNode* y = AVL_x->right;
//    TreeNode* T2 = y->left;
//    y->left = AVL_x;
//    AVL_x->right = T2;
//
//    int height_left = height(AVL_x->left);
//    int height_right = height(AVL_x->right);
//
//    if (height_left > height_right)
//    {
//        AVL_x->height = height_left + 1;
//    }
//    else if (height_left < height_right)
//    {
//        AVL_x->height = height_right + 1;
//    }
//
//    int yheight_left = height(y->left);
//    int yheight_right = height(y->right);
//
//    if (yheight_left > yheight_right)
//    {
//        y->height = yheight_left + 1;
//    }
//    else if (yheight_left < yheight_right)
//    {
//        y->height = yheight_right + 1;
//    }
//
//    return y;
//}
//
//TreeNode* rightRotate(TreeNode* y) {
//    TreeNode* x = y->left;
//    TreeNode* T2 = x->right;
//    x->right = y;
//    y->left = T2;
//
//    int yheight_left = height(y->left);
//    int yheight_right = height(y->right);
//
//    if (yheight_left > yheight_right)
//    {
//        y->height = yheight_left + 1;
//    }
//    else if (yheight_left < yheight_right)
//    {
//        y->height = yheight_right + 1;
//    }
//
//    int xheight_left = height(x->left);
//    int xheight_right = height(x->right);
//
//    if (xheight_left > xheight_right)
//    {
//        x->height = xheight_left + 1;
//    }
//    else if (xheight_left < xheight_right)
//    {
//        x->height = xheight_right + 1;
//    }
//
//
//    return x;
//}
//
//int getBalance(TreeNode* node)
//{
//    if (node == NULL)
//    {
//        return 0;
//    }
//    int Height = height(node->left) - height(node->right);
//    return Height;
//}
//
//TreeNode* insert(TreeNode* node, char** arr, int row, int col, int id = -1)
//{
//    if (node == NULL)
//    {
//        int reward_score = calculateScore(arr, row, col);
//        TreeNode* NewNode = newNode(reward_score, id);
//        return NewNode;
//    }
//    if (id == node->id)
//    {
//        node->reward_score += calculateScore(arr, row, col);
//        node->count++;
//        return node;
//    }
//    else if (id < node->id)
//    {
//        if (node->left == NULL)
//        {
//            int reward_score = calculateScore(arr, row, col);
//            TreeNode* NewNode = newNode(reward_score, id);
//            node->left = NewNode;
//        }
//        else
//        {
//            node->left = insert(node->left, arr, row, col, id);
//        }
//    }
//
//    else
//    {
//        if (node->right == NULL)
//        {
//            int reward_score = calculateScore(arr, row, col);
//            TreeNode* NewNode = newNode(reward_score, id);
//            node->right = NewNode;
//        }
//        else
//        {
//            node->right = insert(node->right, arr, row, col, id);
//        }
//    }
//
//    int xheight_left = height(node->left);
//    int xheight_right = height(node->right);
//    if (xheight_left > xheight_right)
//    {
//        node->height = xheight_left + 1;
//    }
//    else if (xheight_left < xheight_right)
//    {
//        node->height = xheight_right + 1;
//    }
//    int balance = getBalance(node);
//    if (balance > 1 && id < node->left->id)
//    {
//        return rightRotate(node);
//    }
//    else if (balance < -1 && id > node->right->id)
//    {
//        return leftRotate(node);
//    }
//    else if (balance > 1 && id > node->left->id)
//    {
//        node->left = leftRotate(node->left);
//        return rightRotate(node);
//    }
//    else if (balance < -1 && id < node->right->id)
//    {
//        node->right = rightRotate(node->right);
//        return leftRotate(node);
//    }
//
//    return node;
//}
//
//
//TreeNode* minValueNode(TreeNode* node) {
//    TreeNode* current = node;
//
//    while (current->left != NULL)
//    {
//        current = current->left;
//    }
//
//    return current;
//}
//TreeNode* deleteNode(TreeNode* root, int id) {
//    if (root == NULL)
//    {
//        return root;
//    }
//    if (id < root->id)
//    {
//        root->left = deleteNode(root->left, id);
//    }
//    else if (id > root->id)
//    {
//        root->right = deleteNode(root->right, id);
//    }
//    else
//    {
//        if (root->count > 1)
//        {
//            root->count--;
//            root->reward_score -= root->reward_score;
//            return root;
//        }
//        if ((root->left == NULL) || (root->right == NULL))
//        {
//            TreeNode* temp = NULL;
//            if (root->left)
//            {
//                temp = root->left;
//            }
//            else if (!root->left)
//            {
//                temp = root->right;
//            }
//            if (temp == NULL)
//            {
//                temp = root;
//                root = NULL;
//            }
//            else *root = *temp;
//
//            delete temp;
//        }
//        else {
//            TreeNode* temp = minValueNode(root->right);
//            root->id = temp->id;
//            root->reward_score = temp->reward_score;
//            root->count = temp->count;
//            root->right = deleteNode(root->right, temp->id);
//        }
//    }
//    if (root == NULL)
//    {
//        return root;
//    }
//    int xheight_left = height(root->left);
//    int xheight_right = height(root->right);
//    if (xheight_left > xheight_right)
//    {
//        root->height = xheight_left + 1;
//    }
//    else if (xheight_left < xheight_right)
//    {
//        root->height = xheight_right + 1;
//    }
//    int balance = getBalance(root);
//    if (balance > 1 && getBalance(root->left) >= 0)
//    {
//        return rightRotate(root);
//    }
//    else if (balance > 1 && getBalance(root->left) < 0)
//    {
//        root->left = leftRotate(root->left);
//        return rightRotate(root);
//    }
//    else if (balance < -1 && getBalance(root->right) <= 0)
//    {
//        return leftRotate(root);
//    }
//    else if (balance < -1 && getBalance(root->right) > 0)
//    {
//        root->right = rightRotate(root->right);
//        return leftRotate(root);
//    }
//    return root;
//}
//void inorder(TreeNode* root)
//{
//    if (root == NULL)
//    {
//        return;
//    }
//    inorder(root->left);
//    cout << "ID: " << root->id << " Score: " << root->reward_score << " Count: " << root->count << endl;
//    inorder(root->right);
//}
//
//


#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class TreeNode {
public:
    int id;
    int reward_score;
    int count;
    TreeNode* left;
    TreeNode* right;
    int height;
    char val;
    TreeNode* next;
    TreeNode* down;
};

int height(TreeNode* Avlnode)
{
    if (Avlnode == NULL)
    {
        return 0;
    }
    return Avlnode->height;
}
int calculateScore(char** arr, int rows, int cols) {
    int score = 0;
    bool reachedStar = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (reachedStar) {
                // player has reached '*', stop counting score
                return score;
            }
            switch (arr[i][j]) {
            case 'C':
                score += 1;
                break;
            case 'P':
                score += 70;
                break;
            case 'J':
                score += 50;
                break;
            case 'W':
                score += 30;
                break;
            case '%':
                score = 0;
                break;
            case '#':
                score -= 2;
            case '&':
                score -= 1;
            case '$':
                score -= 1;
            case '@':
                score -= 1;
            case '*':
                reachedStar = true;
                break;
            default:
                // do nothing for other characters
                break;
            }
        }
    }
    return score;
}


TreeNode* newNode(int reward_score, int id = -1)
{
    TreeNode* Avlnode = new TreeNode();
    Avlnode->reward_score = reward_score;
    if (id == -1)
    {
        Avlnode->id = rand() % 200 + 1;
    }
    else
    {
        Avlnode->id = id;
    }
    Avlnode->count = 1;
    Avlnode->left = NULL;
    Avlnode->right = NULL;
    Avlnode->height = 1;
    return Avlnode;
}

TreeNode* leftRotate(TreeNode* AVL_x)
{
    TreeNode* y = AVL_x->right;
    TreeNode* T2 = y->left;
    y->left = AVL_x;
    AVL_x->right = T2;

    int height_left = height(AVL_x->left);
    int height_right = height(AVL_x->right);

    if (height_left > height_right)
    {
        AVL_x->height = height_left + 1;
    }
    else if (height_left < height_right)
    {
        AVL_x->height = height_right + 1;
    }

    int yheight_left = height(y->left);
    int yheight_right = height(y->right);

    if (yheight_left > yheight_right)
    {
        y->height = yheight_left + 1;
    }
    else if (yheight_left < yheight_right)
    {
        y->height = yheight_right + 1;
    }

    return y;
}

TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;

    int yheight_left = height(y->left);
    int yheight_right = height(y->right);

    if (yheight_left > yheight_right)
    {
        y->height = yheight_left + 1;
    }
    else if (yheight_left < yheight_right)
    {
        y->height = yheight_right + 1;
    }

    int xheight_left = height(x->left);
    int xheight_right = height(x->right);

    if (xheight_left > xheight_right)
    {
        x->height = xheight_left + 1;
    }
    else if (xheight_left < xheight_right)
    {
        x->height = xheight_right + 1;
    }


    return x;
}

int getBalance(TreeNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    int Height = height(node->left) - height(node->right);
    return Height;
}

TreeNode* insert(TreeNode* node, char** arr, int row, int col, int id = -1)
{
    if (node == NULL)
    {
        int reward_score = calculateScore(arr, row, col);
        TreeNode* NewNode = newNode(reward_score, id);
        return NewNode;
    }
    if (id == node->id)
    {
        node->reward_score += calculateScore(arr, row, col);
        node->count++;
        return node;
    }
    else if (id < node->id)
    {
        if (node->left == NULL)
        {
            int reward_score = calculateScore(arr, row, col);
            TreeNode* NewNode = newNode(reward_score, id);
            node->left = NewNode;
        }
        else
        {
            node->left = insert(node->left, arr, row, col, id);
        }
    }

    else
    {
        if (node->right == NULL)
        {
            int reward_score = calculateScore(arr, row, col);
            TreeNode* NewNode = newNode(reward_score, id);
            node->right = NewNode;
        }
        else
        {
            node->right = insert(node->right, arr, row, col, id);
        }
    }

    int xheight_left = height(node->left);
    int xheight_right = height(node->right);
    if (xheight_left > xheight_right)
    {
        node->height = xheight_left + 1;
    }
    else if (xheight_left < xheight_right)
    {
        node->height = xheight_right + 1;
    }
    int balance = getBalance(node);
    if (balance > 1 && id < node->left->id)
    {
        return rightRotate(node);
    }
    else if (balance < -1 && id > node->right->id)
    {
        return leftRotate(node);
    }
    else if (balance > 1 && id > node->left->id)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    else if (balance < -1 && id < node->right->id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}
TreeNode* deleteNode(TreeNode* root, int id) {
    if (root == NULL)
    {
        return root;
    }
    if (id < root->id)
    {
        root->left = deleteNode(root->left, id);
    }
    else if (id > root->id)
    {
        root->right = deleteNode(root->right, id);
    }
    else
    {
        if (root->count > 1)
        {
            root->count--;
            root->reward_score -= root->reward_score;
            return root;
        }
        if ((root->left == NULL) || (root->right == NULL))
        {
            TreeNode* temp = NULL;
            if (root->left)
            {
                temp = root->left;
            }
            else if (!root->left)
            {
                temp = root->right;
            }
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else *root = *temp;

            delete temp;
        }
        else {
            TreeNode* temp = minValueNode(root->right);
            root->id = temp->id;
            root->reward_score = temp->reward_score;
            root->count = temp->count;
            root->right = deleteNode(root->right, temp->id);
        }
    }
    if (root == NULL)
    {
        return root;
    }
    int xheight_left = height(root->left);
    int xheight_right = height(root->right);
    if (xheight_left > xheight_right)
    {
        root->height = xheight_left + 1;
    }
    else if (xheight_left < xheight_right)
    {
        root->height = xheight_right + 1;
    }
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }
    else if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if (balance < -1 && getBalance(root->right) <= 0)
    {
        return leftRotate(root);
    }
    else if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void inorder(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    cout << "ID: " << root->id << " Score: " << root->reward_score << " Count: " << root->count << endl;
    inorder(root->right);
}
