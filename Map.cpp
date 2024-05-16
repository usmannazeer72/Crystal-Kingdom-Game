#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include "AVL.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

class Node
{
public:
public:
    int x, y;
    Node* next;
    int weight;
    char ch;
    int distance;
    int id;
    bool visited;
    Node* prev;
    int row;
    int col;
    int index;
    int val;
    Node() {}
    Node(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->next = NULL;
        this->val = val;
        weight = 0;
    }
    Node(int x, int y, int val)
    {
        this->x = x;
        this->y = y;
        this->next = NULL;
        this->val = val;
        weight = 0;
    }
    Node(int id)
    {
        this->id = id;
        distance = INT_MAX;
        visited = false;
        prev = NULL;
        row = INT_MAX;
        col = INT_MAX;
    }

};

char** Map(int rows, int cols)
{
    srand(time(NULL));

    char** GameMap = new char* [rows];
    for (int i = 0; i < rows; i++)
    {
        GameMap[i] = new char[cols];
    }

    char rewards[9] = { 'C', 'J', 'P', 'W', '%', '#', '$', '@', '&' };
    static bool star_printed = false;

    int star_row = rand() % rows;
    int star_col = rand() % cols;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == star_row && j == star_col)
            {
                GameMap[i][j] = '*';
                cout << "Star exists" << endl;
            }
            else
            {
                GameMap[i][j] = rewards[rand() % 9];
            }
        }
    }

    return GameMap;
}


class Graph {
public:
    int rows, cols;
    char** GameMap;
    Node*** adjList;
    int** arr;

    Graph(int rows, int cols, char** GameMap)
    {
        this->rows = rows;
        this->cols = cols;
        this->GameMap = GameMap;

        adjList = new Node * *[rows];
        for (int i = 0; i < rows; i++)
        {
            adjList[i] = new Node * [cols];
            for (int j = 0; j < cols; j++)
            {
                adjList[i][j] = NULL;
            }
        }
        arr = new int* [rows * rows];
        for (int i = 0; i < cols * cols; i++)
        {
            arr[i] = new int[cols * cols];
        }
        for (int i = 0; i < rows * rows; i++)
        {
            for (int j = 0; j < rows * rows; j++)
            {
                arr[i][j] = INT_MAX;
            }
        }

        createAdjList();
    }

    void createAdjList()
    {
        int n = rows * cols;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                int m = i * rows + j;
                if (i > 0 && GameMap[i - 1][j])
                {

                    Node* AdjNode = new Node(i - 1, j);
                    AdjNode->next = adjList[i][j];
                    AdjNode->ch = GameMap[i - 1][j];
                    int k = (i - 1) * rows + j;
                    if (AdjNode->ch == '#')
                    {
                        AdjNode->weight = 100;
                        arr[m][k] = 100;
                    }

                    else {
                        AdjNode->weight = 1;
                        arr[m][k] = 1;
                    }
                    adjList[i][j] = AdjNode;
                }

                if (j > 0 && GameMap[i][j - 1])
                {
                    int k = i * rows + (j - 1);
                    Node* AdjNode = new Node(i, j - 1);
                    AdjNode->next = adjList[i][j];
                    AdjNode->ch = GameMap[i][j - 1];
                    if (AdjNode->ch == '#')
                    {
                        AdjNode->weight = 100;
                        arr[m][k] = 100;
                    }
                    else
                    {
                        AdjNode->weight = 1;
                        arr[m][k] = 1;
                    }
                    adjList[i][j] = AdjNode;
                }

                if (i < rows - 1 && GameMap[i + 1][j])
                {
                    int k = (i + 1) * rows + j;
                    Node* AdjNode = new Node(i + 1, j);
                    AdjNode->next = adjList[i][j];
                    AdjNode->ch = GameMap[i + 1][j];
                    if (AdjNode->ch == '#')
                    {
                        AdjNode->weight = 100;
                        arr[m][k] = 100;
                    }
                    else
                    {
                        AdjNode->weight = 1;
                        arr[m][k] = 1;
                    }

                    adjList[i][j] = AdjNode;
                }

                if (j < cols - 1 && GameMap[i][j + 1])
                {
                    int k = i * rows + (j + 1);
                    Node* AdjNode = new Node(i, j + 1);
                    AdjNode->next = adjList[i][j];
                    AdjNode->ch = GameMap[i][j + 1];
                    if (AdjNode->ch == '#')
                    {
                        AdjNode->weight = 100;
                        arr[m][k] = 100;
                    }
                    else
                    {
                        AdjNode->weight = 1;
                        arr[m][k] = 1;
                    }

                    adjList[i][j] = AdjNode;
                }
            }
        }
    }


};

class Floyd
{
public:
    Floyd() {}
    void printFloyd(int start, int crystal, int** arr1)
    {
        if (arr1[start][crystal] == -1) {
            return;
        }
        printFloyd(start, arr1[start][crystal], arr1);
        cout << arr1[start][crystal] << " -> ";
        printFloyd(arr1[start][crystal], crystal, arr1);
    }


    int** FloydAlgo(Graph g1, int** arr1, int rows) {

        int n = rows * rows;

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (g1.arr[i][k] != INT_MAX)
                    {
                        if (g1.arr[k][j] != INT_MAX)
                        {
                            if ((g1.arr[i][k] + g1.arr[k][j]) < g1.arr[i][j])
                            {
                                g1.arr[i][j] = g1.arr[i][k] + g1.arr[k][j];
                                arr1[i][j] = k;

                            }
                        }
                    }
                }
            }
        }




        return arr1;

    }
};
class Dijkstra
{
public:
    Dijkstra() {}
    void printDijkstra(int** parent, int start, int crystal, int size) {


        if (start == crystal) {
            cout << start << endl;
            return;
        }

        int* parent1 = new int[size];

        int curr = crystal;

        int index = 0;

        while (curr != start)
        {
            parent1[index++] = curr;

            curr = parent[start][curr];

        }
        parent1[index++] = start;

        cout << "Shortest path from " << start << " to " << crystal << " by using Dijkstra Algo : ";

        while (index > 0)
        {
            cout << parent1[--index];
            if (index > 0) {
                cout << " -> ";
            }
        }

        cout << endl;

        delete[] parent1;
    }

    void printDijkstraDistance(int* distance, int** parent, int start, int crystal, int size)
    {
        cout << endl;
        cout << "The Shortest Distance using Dijkestra Alog from " << start << " to Crystal Point " << crystal << " : " << distance[crystal] << endl << endl;;
        if (parent[start][crystal] == -1) {
            cout << "No path exists from " << start << " to " << crystal << endl;
            return;
        }
        else
            printDijkstra(parent, start, crystal, size);

    }


    int Distance(int* arr, bool* boolarr, int total_index, int source) {
        int index = -1;
        int mini = INT_MAX;

        for (int i = 0; i < total_index; i++) {
            if (!boolarr[i])
            {
                if (arr[i] <= mini)
                {
                    mini = arr[i];
                    index = i;
                }
            }
        }
        return index;
    }

    void dijkstraAlgo(int** newarr, int x, int rows, int crystal, int size) {
        int start = x;
        int total_index = rows * rows;
        int* arr = new int[total_index];
        int** parent = new int* [total_index];
        int updated_val = 0;
        for (int i = 0; i < total_index; i++)
        {
            parent[i] = new int[total_index];
        }
        bool* boolarray = new bool[total_index] { false };
        int i = 0;
        while (i < total_index) {
            arr[i] = INT_MAX;
            int j = 0;
            while (j < total_index) {
                parent[i][j] = -1;
                j++;
            }
            i++;
        }
        arr[x] = 0;
        i = 0;
        while (i < total_index)
        {
            int updated_val = Distance(arr, boolarray, total_index, x);
            boolarray[updated_val] = true;
            int j = 0;
            while (j < total_index)
            {
                if (boolarray[j] == false)
                {
                    if (newarr[updated_val][j] != INT_MAX)
                    {
                        if (arr[updated_val] + newarr[updated_val][j] < arr[j])
                        {
                            arr[j] = arr[updated_val] + newarr[updated_val][j];
                            parent[x][j] = updated_val;
                        }
                    }
                }

                j++;
            }
            i++;
        }

        printDijkstraDistance(arr, parent, start, crystal, size);

    }
};

class Kruskal
{
public:
    Kruskal()
    {}
    Node*** Kruskalalgo(Graph g, char** array, int rows, int cols, Node* start_node)
    {
        Node*** path = new Node * *[rows];
        for (int i = 0; i < rows; i++)
        {
            path[i] = new Node * [cols];
            for (int j = 0; j < cols; j++)
            {
                path[i][j] = NULL;
            }
        }

        int* weights = new int[rows * cols];
        int k = 0;
        for (int i = 0; i < g.rows; i++)
        {
            for (int j = 0; j < g.cols; j++)
            {
                weights[k] = g.adjList[i][j]->weight;
                k++;
            }
        }

        int minimumdistance = 0;
        k = 0;
        Node* prev_node = NULL;
        for (int i = start_node->row; i < rows; i++)
        {
            for (int j = start_node->col; j < cols; j++)
            {
                if (array[i][j] != '#' && array[i][j] != '*')
                {
                    if (weights[k] > weights[k + 1])
                    {
                        if ((prev_node == NULL) || (prev_node != NULL && path[prev_node->row][prev_node->col] != NULL))
                        {
                            path[i][j] = g.adjList[i][j];
                            minimumdistance += weights[k];
                            prev_node = g.adjList[i][j];
                        }
                    }
                    k++;
                }
                else
                {
                    k++;
                }
            }
        }

        cout << "Minimum distance traveled: " << minimumdistance << endl;
        delete[] weights;
        return path;
    }

    void printPath(Node*** path, char** array, int rows, int cols)
    {
        int k = 0;
        int max_path_length = rows * cols;

        int* x_nodes = new int[max_path_length];
        int* y_nodes = new int[max_path_length];

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (path[i][j] != NULL)
                {
                    x_nodes[k] = path[i][j]->x;
                    y_nodes[k] = path[i][j]->y;
                    k++;
                }
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (array[i][j] == '*')
                {
                    x_nodes[k] = i;
                    y_nodes[k] = j;
                    k++;
                }
            }
        }


        for (int i = 0; i < k - 1; i++)
        {
            cout << "(" << x_nodes[i] << "," << y_nodes[i] << ")" << "->";
        }
        cout << "(" << x_nodes[k - 1] << "," << y_nodes[k - 1] << ")";
        delete[] x_nodes;
        delete[] y_nodes;
    }
};

class Prims
{
public:
    Prims() {}
    int minDistance(int* dist, bool* visited, int rows) {
        int min = INT_MAX, min_index = -1;

        for (int v = 0; v < rows; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                min_index = v;
            }
        }

        return min_index;
    }

    int** PrimsAlgo(Graph g1, int** arrweight, int start_x, int start_y, int end_x, int end_y)
    {
        int rows = g1.rows;
        bool* visited = new bool[rows];
        int* dist = new int[rows];
        int* parent = new int[rows];

        for (int i = 0; i < rows; i++)
        {
            visited[i] = false;
            dist[i] = INT_MAX;
        }

        dist[start_x * rows + start_y] = 0;
        parent[start_x * rows + start_y] = -1;

        for (int i = 0; i < rows - 1; i++)
        {
            int u = minDistance(dist, visited, rows);
            visited[u] = true;

            for (int v = 0; v < rows; v++)
            {
                if (g1.adjList[u][v] && !visited[v] && g1.adjList[u][v]->weight < dist[v])
                {
                    parent[v] = u;
                    dist[v] = g1.adjList[u][v]->weight;
                }
            }
        }

        for (int i = 1; i < rows; i++)
        {
            arrweight[i][parent[i]] = dist[i];
            arrweight[parent[i]][i] = dist[i];
        }

        delete[] visited;
        delete[] dist;
        delete[] parent;

        return arrweight;
    }
    int** Weigthedarr(Graph g1, int** arrweight, int rows, int cols)
    {
        int i = 0, j = 0;
        while (i < rows)
        {
            j = 0;
            while (j < cols)
            {

                if (i == j)
                {
                    arrweight[i][j] = 0;
                }
                else if (g1.adjList[i][j] != NULL)
                {
                    arrweight[i][j] = g1.adjList[i][j]->weight;
                }
                else
                    arrweight[i][j] = -1;

                j++;
            }
            i++;
        }
        i = 0;
        j = 0;
        int m = 0;
        while (m < rows)
        {
            i = 0;
            while (i < rows)
            {
                j = 0;
                while (j < cols)
                {

                    if (arrweight[i][j] > arrweight[i][m] + arrweight[m][j])
                    {
                        arrweight[i][j] = arrweight[i][m] + arrweight[m][j];
                    }
                    j++;
                }
                i++;
            }
            m++;
        }


        return arrweight;

    }

    void printPrimsAlgo(int** mst, int rows, int cols, int start_x, int start_y, int end_x, int end_y)
    {
        cout << "Minimum Spanning Tree from (" << start_x << ", " << start_y << ") to (" << end_x << ", " << end_y << "):\n";
        for (int i = start_x; i <= end_x; i++)
        {
            for (int j = start_y; j <= end_y; j++)
            {
                if (mst[i][j] == -1)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << mst[i][j] << "   ";
                }
            }
            cout << "\n";
        }
    }
};



int main()
{
    const char* narrowString = "C:\\Users\\E-TIME\\Documents\\Semester_4\\music.wav";
    int size = MultiByteToWideChar(CP_UTF8, 0, narrowString, -1, NULL, 0);
    wchar_t* wideString = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, narrowString, -1, wideString, size);

    PlaySoundW(wideString, NULL, SND_FILENAME | SND_ASYNC);

    //system("clear");

    // Display the title
    cout << "                     _      _         ._                            _           ._.\n";
    cout << "                     /  \\    /  \\   __ |  |   __  _ _  __     |_| __   _| |\n";
    cout << "                     \\   \\/\\/   /  /    \\|  |  /  _ \\|  |  \\/    \\    |  |/    \\ /__  |\n";
    cout << "                      \\        /|  \\__|  |(  <> )  |  /   |  \\   |  |   |  \\ /_| |\n";
    cout << "                       \\/\\  /  /  >_/\\_/|_/|_|  /\\|  |_|  /\\_|\n";
    cout << "                            \\/        \\/                       \\/\\____|   \\/       \n\n";
    cout << "                     ------------------THE QUEST FOR THE CRYSTAL KINGDOM-----------------" << endl;
    cout << "                      _      _         ._                            _           ._.\n";
    cout << "                     /  \\    /  \\   __ |  |   __  _ _  __     |_| __   _| |\n";
    cout << "                     \\   \\/\\/   /  /    \\|  |  /  _ \\|  |  \\/    \\    |  |/    \\ /__  |\n";
    cout << "                      \\        /|  \\__|  |(  <> )  |  /   |  \\   |  |   |  \\ /_| |\n";
    cout << "                       \\/\\  /  /  >_/\\_/|_/|_|  /\\|  |_|  /\\_|\n";
    cout << "                            \\/        \\/                       \\/\\____|   \\/       \n\n";




    cout << endl << endl << endl;
    cout << "     ######     #    #######    #        #####  ####### ######  #     #  #####  ####### #     # ######  #######  #####\n";
    cout << "     #     #   # #      #      # #      #     #    #    #     # #     # #     #    #    #     # #     # #       #     # \n";
    cout << "     #     #  #   #     #     #   #     #          #    #     # #     # #          #    #     # #     # #       #       \n";
    cout << "     #     # #     #    #    #     #     #####     #    ######  #     # #          #    #     # ######  #####    #####  \n";
    cout << "     #     # #######    #    #######          #    #    #   #   #     # #          #    #     # #   #   #             # \n";
    cout << "     #     # #     #    #    #     #    #     #    #    #    #  #     # #     #    #    #     # #    #  #       #     # \n";
    cout << "     ######  #     #    #    #     #     #####     #    #     #  #####   #####     #     #####  #     # #######  #####\n";

    cout << endl << endl << endl;
    system("pause");
    system("cls");

    cout << "     ### ##     ####   ####       ##     ####               ## ##     ##     ####     ### ###  ### ###  ##   ##\n";
    cout << "     ##  ##     ##     ##         ##     ##               ##   ##     ##     ##       ##  ##   ##  ##   ## ##\n";
    cout << "     ##  ##     ##     ##       ## ##    ##               ####      ## ##    ##       ##       ##      # ### #\n";
    cout << "     ## ##      ##     ##       ##  ##   ##                #####    ##  ##   ##       ## ##    ## ##   ## # ##\n";
    cout << "     ##  ##     ##     ##       ## ###   ##                   ###   ## ###   ##       ##       ##      ##   ##\n";
    cout << "     ##  ##     ##     ##  ##   ##  ##   ##  ##           ##   ##   ##  ##   ##  ##   ##  ##   ##  ##  ##   ##\n";
    cout << "     ### ##     ####   ### ###  ###  ##  ### ###            ## ##   ###  ##  ### ###  ### ###  ### ###  ##   ##\n";

    cout << endl << endl;

    cout << "     ##  ###   ## ##   ##   ##    ##     ###  ##           ###  ##    ##     ### ##   ### ###  ### ###  ### ##\n";
    cout << "     ##   ##  ##   ##   ## ##      ##      ## ##             ## ##     ##    ##  ##    ##  ##   ##  ##   ##  ##\n";
    cout << "     ##   ##  ####     # ### #   ## ##    # ## #            # ## #   ## ##      ##     ##       ##       ##  ##\n";
    cout << "     ##   ##   #####   ## # ##   ##  ##   ## ##             ## ##    ##  ##    ##      ## ##    ## ##    ## ##\n";
    cout << "     ##   ##      ###  ##   ##   ## ###   ##  ##            ##  ##   ## ###   ##       ##       ##       ## ##\n";
    cout << "     ##   ##  ##   ##  ##   ##   ##  ##   ##  ##            ##  ##   ##  ##  ##  ##    ##  ##   ##  ##   ##  ##\n";
    cout << "     ## ##    ## ##   ##   ##  ###  ##  ###  ##           ###  ##  ###  ##  # ####   ### ###  ### ###  #### ##\n";

    cout << endl << endl;

    cout << "     #     #                                                     #    #                               \n";
    cout << "     ##   ## #    # #    #   ##   #    # #    #   ##   #####     #   #    ##    ####  #    # # ######\n";
    cout << "     # # # # #    # #    #  #  #  ##  ## ##  ##  #  #  #    #    #  #    #  #  #      #    # # #      \n";
    cout << "     #  #  # #    # ###### #    # # ## # # ## # #    # #    #    ###    #    #  ####  ###### # #####  \n";
    cout << "     #     # #    # #    # ###### #    # #    # ###### #    #    #  #   ######      # #    # # #     \n";
    cout << "     #     # #    # #    # #    # #    # #    # #    # #    #    #   #  #    # #    # #    # # #    \n";
    cout << "     #     #  ####  #    # #    # #    # #    # #    # #####     #    # #    #  ####  #    # # # \n";




    system("pause");
    system("cls");


    char cont = 'Y';

    // Loop until the user exits the program



    int rows = 10;
    int cols = 10;
    int crystal_index = 0;
    char** gameMap = Map(rows, cols);
    int n = rows * cols;

    int** arrweight = new int* [n];
    for (int i = 0; i < n; i++)
    {
        arrweight[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            arrweight[i][j] = -1;
        }
    }


    cout << "Game map:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << gameMap[i][j] << " ";

        }
        cout << endl;
    }
    cout << endl;

    Graph graph(rows, cols, gameMap);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << "AdjNode (" << i << "," << j << "): ";
            Node* curr = graph.adjList[i][j];
            if (graph.adjList[i][j]->ch == '*')
            {
                crystal_index = (i * cols) + j;
                crystal_index++;

            }
            while (curr != NULL)
            {
                cout << "(" << curr->x << "," << curr->y << ") " << " " << curr->ch << " " << " " << curr->weight << " ";


                curr = curr->next;
            }
            cout << endl;
        }
    }

    srand(time(NULL));
    TreeNode* root = NULL;
    root = insert(root, gameMap, rows, cols, 100);
    for (int i = 0; i < 5; i++)
    {
        int id = rand() % 200 + 1;
        root = insert(root, gameMap, rows, cols, id);
    }
    cout << "Initial inventory: " << endl;
    inorder(root);
    cout << endl;
    root = deleteNode(root, 100);
    cout << "Inventory after removing ID 100: " << endl;
    inorder(root);
    cout << endl;
    int id = rand() % 200 + 1;
    int score = rand() % 100 + 1;
    root = insert(root, gameMap, rows, cols, id);
    cout << "Inventory after adding ID " << id << ": " << endl;
    inorder(root);
    cout << endl;
    int opt;

    do
    {
        cout << " Enter Algorithm you want to implement " << endl;
        cout << "1.Floyd Algorithm " << endl;
        cout << "2.Prims Algorithm " << endl;
        cout << "3.Kruskal Algorithm " << endl;
        cout << "4.Dijkstra Algorithm " << endl;
        cin >> opt;


        int** newweight = new int* [n];
        for (int i = 0; i < n; i++)
        {
            newweight[i] = new int[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                newweight[i][j] = graph.arr[i][j];
            }
        }
        int x = 0;
        if (opt == 1)
        {
            Floyd F;
            int** parent;
            parent = F.FloydAlgo(graph, arrweight, rows);
            cout << endl << endl;;
            cout << "Floyd's Algorithm From Default Location 0" << " to " << crystal_index << " : ";
            cout << 0 << " -> ";
            F.printFloyd(0, crystal_index, parent);
            cout << crystal_index << endl;
            //parent = NULL;
            cout << endl;
            cout << "Enter starting node for Floyd's Algoithm : ";
            cin >> x;
            //parent = F.FloydAlgo(graph, arrweight, rows);
            cout << endl;
            cout << "Floyd's Algorithm From Custom Location " << x << " to " << crystal_index << " : ";
            cout << x << " -> ";
            F.printFloyd(x, crystal_index, parent);
            cout << crystal_index << endl;
        }
        else if (opt == 2)
        {

            Prims P;
            int** weightarr = new int* [rows];

            for (int i = 0; i < rows; i++)
            {
                weightarr[i] = new int[cols];

            }
            weightarr = P.Weigthedarr(graph,weightarr,rows,cols);
            int** arrweight2 = new int* [rows];

            for (int i = 0; i < rows; i++)
            {
                arrweight2[i] = new int[cols];

            }

            int start_x, start_y, end_x, end_y;

            cout << "Enter starting point X" << endl;
            cin >> start_x;
            cout << "Enter starting point Y" << endl;
            cin >> start_y;

            cout << "Enter end point X" << endl;
            cin >> end_x;
            cout << "Enter ending point Y" << endl;
            cin >> end_y;

            int** next = new int* [rows];
            for (int i = 0; i < rows; i++)
            {
                next[i] = new int[cols];
            }


            arrweight2 = P.PrimsAlgo(graph, weightarr, start_x, start_y, end_x, end_y);
            P.printPrimsAlgo(arrweight2, rows, cols, start_x, start_y, end_x, end_y);
        }
        else if (opt == 3)
        {
            Kruskal k;
            Node*** path = new Node * *[rows];
            for (int i = 0; i < rows; i++)
            {
                path[i] = new Node * [cols];
                {
                    for (int j = 0; j < cols; j++)
                    {
                        path[i][j] = NULL;
                    }
                }
            }

            int* w = new int[rows * cols];


            int x_coord = 0;
            int y_coord = 0;
            Node* start_node = graph.adjList[x_coord][y_coord];
            path = k.Kruskalalgo(graph, gameMap, rows, cols, start_node);
            cout << " Enter x-coordinate for starting node " << endl;
            cin >> x_coord;
            cout << " Enter y-coordinate for starting node " << endl;
            cin >> y_coord;
            start_node = graph.adjList[x_coord][y_coord];
            path = k.Kruskalalgo(graph, gameMap, rows, cols, start_node);

            k.printPath(path, gameMap, rows, cols);
        }
        else if (opt == 4)
        {
            Dijkstra D;
            cout << crystal_index << endl;
            D.dijkstraAlgo(newweight, 0, rows, crystal_index, n);
            cout << endl;
            cout << "Enter starting node for Dijkstra Algoithm : ";
            cin >> x;
            D.dijkstraAlgo(newweight, x, rows, crystal_index, n);
        }
        cout << endl;
        cout << " Do you want to countinue Y/N." << endl;
        cin >> cont;
    }

    while (cont == 'Y' || cont == 'y');
    delete[] wideString;

    return 0;

}