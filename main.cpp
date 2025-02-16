#include<iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include<ctime>

using namespace std;

//system("Color 57");

//////////////////////////////////////////////////////// CLASSES PROTOTYPES /////////////////////////////////////////////
class message;
class router;
class routingTable;

//////////////////////////////////////////////////////// QUEUES ////////////////////////////////////////////////////////
template <class T>
class QueueNode
{
public:

    int priority;
    T data;
    QueueNode* next;

    QueueNode() {

        priority = 0;
        //data = NULL;
        next = NULL;
    }

    T getData()
    {
        return data;
    }
};

//////////////////////////////////////////////////////// PRIORITY QUEUE ////////////////////////////////////////////////////////
template <class T>
class Priority_Queue
{
public:

    QueueNode<T>* head;

    Priority_Queue()
    {
        head = NULL;
    }


    void insert(message item, int p)
    {
        QueueNode<T>* newNode, * temp;

        //making a new node
        newNode = new QueueNode<T>;
        newNode->data = item;
        newNode->priority = p;

        /*if head is null or given priority is less than priority
         of head then put head in newNode's next and make newNode head*/

        if (head == NULL || p > head->priority)
        {
            newNode->next = head;
            head = newNode;
        }

        /*else we will store head in newNode (temp) and traverse list till
        head gets and also checks if priority of next is less than
        the given priority and then insert the node*/
        else
        {
            temp = head;
            while (temp->next != NULL && temp->next->priority >= p)
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;

        }
    }

    //ignore for now as it deletes only in a sequence
     /* void del()
      {
          node<T> *newNode;
          if(head == NULL)
              cout<<"Queue Underflow\n";
          else
          {
              newNode = head;
              cout<<"Deleted item is: "<<newNode->data<<endl;
              head = head->next;
              delete newNode;
              //free(newNode);
          }
      }*/


    T dequeue()
    {
        QueueNode<T>* ptr;
        ptr = head;
        message msg;
        if (head == NULL)
            cout << "Queue is empty\n";
        else
        {

            msg = head->data;
            head = ptr->next;
            delete ptr;
        }

        return msg;
    }

    void display()
    {
        QueueNode<T>* ptr;
        ptr = head;
        if (head == NULL)
            cout << "Queue is empty\n";
        else
        {
            cout << "Queue is :\n";

            while (ptr != NULL)
            {
                ptr->data.display();
                ptr = ptr->next;
            }
        }
    }
};

//////////////////////////////////////////////////////// OUTGOING QUEUE ////////////////////////////////////////////////////////
template<class T>
class outgoingQueue {
public:
    QueueNode<T>* front;
    QueueNode<T>* rear;
    QueueNode<T>* getRear() {
        return rear;
    }
    outgoingQueue() {
        front = NULL;
        rear = NULL;
    }
    bool isEmpty() {
        return front == NULL;
    }
    void enqueue(T data) {
        QueueNode<T>* newnode = new QueueNode<T>;

        newnode->next = NULL;
        newnode->data = data;

        if (isEmpty()) {
            front = newnode;
            rear = newnode;

        }
        else {
            rear->next = newnode;
            rear = newnode;
        }

    }
    T dequeue() {
        QueueNode<T>* temp;
        T data;
        if (isEmpty())
            cout << "The queue is empty.\n";
        else {

            temp = front->next;
            data = front->getData();
            delete front;
            front = temp;

            if (front == rear) {
                rear = NULL;
                front = NULL;
            }
        }
        return data;
    }

    T Front() {
        return front->value;
    }
};

//////////////////////////////////////////////////////// Structure to store Real Names of Routers and Machines ////////////////////////////////////////////////////////
struct routerNames {

    int id;
    string name;
};
routerNames Names[21] = { {0,"0"}, {1,"M1"}, {2,"M2"}, {3,"M3"}, {4,"M4"}, {5,"M5"}, {6,"M6"}, {7,"M7"}, {8,"M8"}, {9,"M9"}, {10,"M10"}, {11,"M11"}, {12,"M12"}, {13,"M13"}, {14,"14"}, {15,"M15"}, {16,"R1"}, {17,"R2"}, {18,"R3"}, {19,"R4"}, {20,"R5"}, };

static int staticid = 0;

//////////////////////////////////////////////////////// LINKED LIST ////////////////////////////////////////////////////////
class listNode {

public:

    int data; //Stores the Data
    listNode* next; //Stores the address to the Next listNode
    int id;
    listNode() {

        data = 0;
        next = NULL;
    }
};

class List {

public:

    listNode* head; //Address of the starting listNode
    int size;

    //Constructor
    List() {

        head = NULL;
        size = 0;
    }

    void emptyList() {

        listNode* temp;

        while (head) {

            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertNode(int x) // index = 2 data = 150
    {



        //Locating the index
        listNode* currNode = head;

        //Creating a new listNode
        listNode* newNode = new listNode;
        newNode->data = x;
        newNode->id = staticid++;

        if (currNode == NULL) //Inserting as First Element
        {
            newNode->next = NULL;
            head = newNode;
        }
        else //Inserting after currIndex
        {
            while (currNode->next != NULL) {

                currNode = currNode->next;
            }

            newNode->next = currNode->next;
            currNode->next = newNode;
        }

        size++;
        //cout << "Inserted " << x << endl;
    }

    void displayList() {

        int num = 0;
        listNode* currNode = head;

        cout << endl << "List" << endl;
        while (currNode != NULL) {
            cout << num << ": " << currNode->data << endl;
            currNode = currNode->next;
            num++;
        }

        cout << "Total Nodes in List: " << size;
    }

    int findNode(int x) {

        listNode* currNode = head;
        int currIndex = 0;

        while (currNode && currNode->data != x) {

            currNode = currNode->next;

            currIndex++;
        }

        if (currNode) return currIndex;
        else return -1;
    }

    int Access(int x) {

        listNode* currNode = head;
        int currIndex = 0;

        while (currNode && currNode->id != x) {

            currNode = currNode->next;
        }
        if (currNode)
            return currNode->data;
        else
        {
            return -1;
        }
    }

    bool DeleteNode(int x) {

        listNode* prevNode = NULL;
        listNode* currNode = head;
        int currIndex = 1;

        //Finding listNode with value x
        while (currNode->data != x) {

            prevNode = currNode;
            currNode = currNode->next;
            currIndex++;
        }

        if (currNode) {

            if (prevNode) //If Deleteing a middle listNode
            {

                prevNode->next = currNode->next; //Store Address of Next listNode
                delete currNode; //Deleting
            }

            else //if Deleting the first listNode
            {
                head = currNode->next;
                delete currNode;
            }

            return true;
        }

        return false;
    }

};

//////////////////////////////////////////////////////// SPLAY TREE ////////////////////////////////////////////////////////
template<class T>
class treeNode
{
public:
    T key;
    treeNode<T>* left, * right;
    treeNode()
    {
        key = NULL;
        left = right = NULL;
    }
};

template<class T>
class splayTree
{
public:
    treeNode<T>* root;

    splayTree()
    {
        root = NULL;
    }
    /* Helper function that allocates
    a new treeNode with the given key and
    NULL left and right pointers. */
    treeNode<T>* newNode(T key)
    {
        treeNode<T>* temp = new treeNode<T>;
        temp->key = key;
        temp->left = temp->right = NULL;
        return (temp);
    }

    // A utility function to right
    // A utility function to left
    // rotate subtree rooted with x
    // See the diagram given above.
    treeNode<T>* leftRotate(treeNode<T>* x)
    {
        treeNode<T>* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // A utility function to right
    // rotate subtree rooted with y
    // See the diagram given above.
    treeNode<T>* rightRotate(treeNode<T>* x)
    {
        treeNode<T>* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    // This function brings the key at
    // root if key is present in tree.
    // If key is not present, then it
    // brings the last accessed item at
    // root. This function modifies the
    // tree and returns the new root
    treeNode<T>* splay(treeNode<T>* root, T key)
    {
        // Base cases: root is NULL or
        // key is present at root
        if (root == NULL || root->key == key)
            return root;

        // Key lies in left subtree
        if (root->key > key)
        {
            // Key is not in tree, we are done
            if (root->left == NULL) return root;

            // Zig-Zig (Left Left)
            if (root->left->key > key)
            {
                // First recursively bring the
                // key as root of left-left
                root->left->left = splay(root->left->left, key);

                // Do first rotation for root,
                // second rotation is done after else
                root = rightRotate(root);
            }
            else if (root->left->key < key) // Zig-Zag (Left Right)
            {
                // First recursively bring
                // the key as root of left-right
                root->left->right = splay(root->left->right, key);

                // Do first rotation for root->left
                if (root->left->right != NULL)
                    root->left = leftRotate(root->left);
            }

            // Do second rotation for root
            return (root->left == NULL) ? root : rightRotate(root);
        }
        else // Key lies in right subtree
        {
            // Key is not in tree, we are done
            if (root->right == NULL) return root;

            // Zig-Zag (Right Left)
            if (root->right->key > key)
            {
                // Bring the key as root of right-left
                root->right->left = splay(root->right->left, key);

                // Do first rotation for root->right
                if (root->right->left != NULL)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->key < key)// Zag-Zag (Right Right)
            {
                // Bring the key as root of
                // right-right and do first rotation
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }

            // Do second rotation for root
            return (root->right == NULL) ? root : leftRotate(root);
        }
    }
    void preOrder(treeNode<T>* treeNode)
    {
        if (treeNode != NULL)
        {
            cout << treeNode->key << " ";
            preOrder(treeNode->left);
            preOrder(treeNode->right);
        }
    }
    treeNode<T>* insert(T k)
    {
        // Simple Case: If tree is empty
        if (root == NULL)
            return root = newNode(k);

        // Bring the closest leaf treeNode to root
        root = splay(root, k);

        // If key is already present, then return
        if (root->key == k) return root;

        // Otherwise allocate memory for new treeNode
        treeNode<T>* newnode = newNode(k);

        // If root's key is greater, make
        // root as right child of newnode
        // and copy the left child of root to newnode
        if (root->key > k)
        {
            treeNode<T>* temp = root;
            newnode->right = temp;
            newnode->left = temp->left;
            temp->left = NULL;
            root = newnode;
        }

        // If root's key is smaller, make
        // root as left child of newnode
        // and copy the right child of root to newnode
        else
        {
            treeNode<T>* temp = root;
            newnode->left = temp;
            newnode->right = temp->right;
            temp->right = NULL;
            root = newnode;
        }
        return newnode; // newnode becomes new root
    }

    void createTree(List l) {

        listNode* currNode = l.head;

        while (currNode) {

            insert(currNode->data);
            currNode = currNode->next;
        }
    }
};

//////////////////////////////////////////////////////// FILE READING ////////////////////////////////////////////////////////
//total vertices
int vertix = 20;

//contains graph
int graph[22][22];

//contains the distance of edge
int dist[21];

//the vertices that are added to tree successfully are marked visited 
bool visited[21];

//path is the array that contains the vertices whose distance has been found successfully
int path[21];

//Weights Array
int weights[21][21];

//Reading From File
void read(string arr[][21]) {

    string line = "";
    string data = "X";
    int l = 0, x = 0, y = 0, c = 0;

    ifstream file;
    file.open("network.csv");

    for (int i = 0; i < 21; i++) {

        getline(file, line, '\n');

        //0,0 cell is empty so adding X in its place (Runs only for row 1)
        if (l == 0) {

            data += line;
            line = data;
            l++;
        }

        c = 0; //reset char counter of line
        y = 0; //reset column number 

        while (line[c] != '\n' && line[c] != '\0') {

            if (line[c] == ',' || line[c] == '\n' || line[c] == '\0') {

                //cout << "," << endl;
                y++; //Change Column

            }
            else {

                //cout << "" << line[c] << "";
                //cout << "X " << x << " Y " << y << endl;
                arr[x][y] += line[c]; //Add to Array
            }

            c++; //Next Char

        }

        x++; //Next Row
    }

    file.close();
}

//graph is created which we will read from excel sheet
void makeGraph()
{

    //u and v = edges
    //w is weight
    int u, v, p = 0, q = 0;

    string arr[21][21];

    read(arr);

    /*cout << "ADJACENCY MATRIX IN STRING" << endl;

    for (int i = 0; i < 21; i++) {

        for (int j = 0; j < 21; j++)
            cout << left << setw(5) << arr[i][j];

        cout << endl;
    }
    */

    int mat[21][21];
    int row = 1, col = 1;


    for (int i = 0; i < 21; i++) {

        //cout << endl;

        for (int j = 0; j < 21; j++) {

            //cout << i << " " << j << " " << arr[i][j] << " ";

            if (i == 0 && j == 0) {
                mat[i][j] = 0;
            }
            else if (i == 0 && j > 0) {

                mat[i][j] = row;
                row++;
            }
            else if (i > 0 && j == 0) {
                mat[i][j] = col;
                col++;
            }
            else if ((arr[i][j]) == "?") {
                mat[i][j] = 10000;
            }
            else {

                mat[i][j] = stoi(arr[i][j]);
            }
        }
    }

    /*cout << "ADJACENCY MATRIX IN INT" << endl;

    for (int i = 0; i < 21; i++) {

        for (int j = 0; j < 21; j++)
            cout << left << setw(5) << mat[i][j];

        cout << endl;
    }
    */

    //cout << "ADJACENCY MATRIX for algo showing weights" << endl;
    for (int i = 0; i < 21; i++) {

        for (int j = 0; j < 21; j++) {

            if (i == 0) {

                u = mat[i][j];
            }

            else if (j == 0) {

                v = mat[i][j];
            }

            else {

                weights[p][q] = mat[i][j];
                q++;

                if (q > 19) {

                    q = 0;
                    p++;


                }
            }

        }

    }


    /*for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++)
            cout << left << setw(5) << weights[i][j];

        cout << endl;
    }
    */

    //storing value of weight corresponding to the vertices
    int n = 0;
    int m = 0;

    //cout << "final matrix for algo" << endl;
    for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++)

            graph[i][j] = weights[i][j];
    }

    /*
    for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++)
            cout << left << setw(5) << graph[i][j];

        cout << endl;
    }
    */

    graph[21][21] = -1;
}

//////////////////////////////////////////////////////// MESSAGE CLASS ////////////////////////////////////////////////////////

//Message Class
class message
{
public:

    int msg_id;
    int priority;
    int src_add;
    int des_add;
    string payload;
    string trace;
    string src_Name;
    string des_Name;

    message()
    {
        msg_id = 0;
        priority = 0;
        src_add = 0;
        des_add = 0;
        payload = "";
        trace = "";
    }

    void write_msg()
    {
        bool f = false; //Flag to Check Input Validity

        cout << "Message" << endl;
        cout << "Enter Message: ";
        cin >> payload;
        cin.ignore();
        cout << "Enter ID: ";
        cin >> msg_id;
        cin.ignore();
        cout << "Enter Priority: ";
        cin >> priority;
        cin.ignore();

        while (f == false) {

            cout << "Source: ";
            cin >> src_Name;
            for (int i = 0; i < 21; i++) {

                if (Names[i].name == src_Name) {
                    src_add = Names[i].id;
                    f = true;
                    break;
                }
            }

            if (f == false) cout << "Incorrect Source! Please enter again." << endl;
        }
        src_add--;

        cin.ignore();
        f = false; //Reset Flag for Next Input

        while (f == false) {

            cout << "Destination: ";
            cin >> des_Name;

            for (int i = 0; i < 21; i++) {
                if (Names[i].name == des_Name) {
                    des_add = Names[i].id;
                    f = true;
                    break;
                }
            }

            if (f == false) cout << "Incorrect Source! Please enter again." << endl;
        }
        des_add--;

        cin.ignore();

        ofstream fout; //Creating an Output Stream

        fout.open("backupMessages.txt", ios::app); // Opening a File with the name "myFile", of type "text", in "append" mode

        //Writing to the File
        fout << endl << "MESSAGE" << endl;
        fout << "Payload: " << payload << endl;
        fout << "ID: " << to_string(msg_id) << endl;
        fout << "Priority: " << to_string(priority) << endl;
        fout << "Source: " << src_Name << endl;
        fout << "Destination: " << des_Name << endl;

        fout.close(); //closing the file

    }

    void display()
    {
        cout << "______________" << endl;
        cout << "Message: " << payload << endl;
        cout << "Message ID: " << msg_id << endl;
        cout << "Message Priority: " << priority << endl;
        cout << "Message Source: " << src_add << endl;
        cout << "Source Name: ";
        for (int i = 0; i < 21; i++) {
            if (Names[i].id == (src_add + 1)) {
                cout << Names[i].name << endl;
                break;
            }
        }
        cout << "Destination: " << des_add << endl;
        cout << "Destination Name: ";

        for (int i = 0; i < 21; i++) {
            if (Names[i].id == (des_add + 1)) {
                cout << Names[i].name << endl;
                break;
            }
        }
        cout << "______________" << endl;
    }
};

//////////////////////////////////////////////////////// ROUTING TABLE ////////////////////////////////////////////////////////
class routingTable {

public:

    int sourceNode;
    int destinationNode;
    message msg;
    List routerPath;
    splayTree<int> treePath;

    routingTable() {

        sourceNode = 0;
        destinationNode = 0;
    }

    routingTable(message m) {

        msg = m;
        sourceNode = m.src_add;
        destinationNode = m.des_add;
    }

    //function to find the vertex which is at the minimum distance
    int MinDisVer()
    {
        int min = 10000, minDist = 0;

        //vertix is number of nodes
        for (int v = 0; v < vertix; v++)
            if (visited[v] == false && dist[v] <= min)
            {
                min = dist[v];
                minDist = v;
            }

        return minDist;
    }

    //function to print path
    /* This function will print all the previous vertices
    that were visited from the source vertex before reaching
    a certain desired vertex*/
    void displayPath(int j)
    {
        if (path[j] == -1)
            return;
        displayPath(path[j]);
        cout << j << " ";
        routerPath.insertNode(j);
    }

    void dijkstra_algorithm()
    {
        /*for all vertices the loop sets distance to infinity and marks then as unvisited
        path is the vertix that comes before the concerned vertex and is used to find the path later on*/
        for (int i = 0; i < vertix; i++)
        {
            path[0] = -1;
            dist[i] = 10000;
            visited[i] = false;
        }

        //distance of source is zero
        dist[sourceNode] = 0;

        //loop to traverse all vertices
        for (int count = 0; count < vertix - 1; count++)
        {
            //u has the vertex which is at the minimum distance
            int u = MinDisVer();

            //after getting vertex it is marked as visited
            visited[u] = true;

            /* Loop runs for all nodes, if the direct distance of source node dist[v]
            is larger than the sum of distance from source node to u and u to v (dist[u] + graph[u][v])
            than the distance is updated and u is added to the list of path */
            for (int v = 0; v < vertix; v++)
                if (!visited[v] && graph[u][v] &&
                    dist[u] + graph[u][v] < dist[v])
                {
                    path[v] = u;
                    dist[v] = dist[u] + graph[u][v];
                }
        }

        //Deleting List
        //routerPath.emptyList();
        routerPath.head = NULL;
        staticid = 0;
        //printing path
        cout << "Src->Dest " << "\t" << "Distance" << "\t" << "Path" << endl;
        for (int i = 1; i < vertix; i++)
        {
            if (i == destinationNode) {

                cout << left << sourceNode << "->" << i << "\t\t" << dist[i] << "\t\t" << sourceNode << " ";
                routerPath.insertNode(sourceNode);
                displayPath(i);
                cout << endl;
            }
        }

        cout << endl << "LINEAR LIST IMPLEMENTATION" << endl;
        routerPath.displayList();

        treePath.createTree(routerPath);

        cout << endl << endl << "SPLAY TREE IMPLEMENTATION" << endl;
        treePath.preOrder(treePath.root);
        cout << endl;
    }
};


//////////////////////////////////////////////////////// ROUTER ////////////////////////////////////////////////////////
class router
{
public:

    int num;
    int id;
    string router_name;
    message msg;
    Priority_Queue<message> incoming;
    outgoingQueue<message> outgoing;
    routingTable rt;

    router() {
        num = 0;
        id = 0;
        router_name = "";
    }

    void insert_message()
    {
        incoming.insert(msg, msg.priority);
    }

    void display_incoming()
    {

        incoming.display();
    }

    void displayRouter()
    {
        for (int i = 0; i < 20; i++)
        {
            if (num+1 == Names[i].id)
            {
                router_name = Names[i].name;
            }
        }
        cout << "Router No.: " << num << endl;
        cout << "Router Name: " << router_name << endl;

    }
};

/////FILE HANDLING
message readMessageFromFile(string filename) {

    string outputLine;
    string linesArr[5];
    message msg;
    int i = 0;
    bool f = false;

    //-------------------------------Reading from a File

    ifstream fin; //Creating an object for reading from a file

    fin.open(filename); // Opening a File with the name "myFile", of type "text", in "input" mode

    if (fin.is_open()) //Checking whether the file exists
    {

        while (!fin.eof()) //Reads until the end of file is reached
        {
            getline(fin, outputLine); //Reading a Char from file	

            //eof executes one more file after the file ends
            if (fin.eof())
                break;

            cout << outputLine << endl; //Displaying that char on console	
            linesArr[i] = outputLine;
            i++;
        }

        fin.close(); //Closing the File	
    }

    else
        cout << "Unable to Open File";

    //Adding to Message Class
    msg.payload = linesArr[0];
    msg.msg_id = stoi(linesArr[1]);
    msg.priority = stoi(linesArr[2]);
    msg.src_Name = linesArr[3];
    msg.des_Name = linesArr[4];

    for (int i = 0; i < 21; i++) 
    {

        if (Names[i].name == msg.src_Name) {
            msg.src_add = Names[i].id;
            f = true;
            break;
        }
    }

    msg.src_add--;

    for (int i = 0; i < 21; i++) {
        if (Names[i].name == msg.des_Name) {
            msg.des_add = Names[i].id;
            break;
        }
    }

    msg.des_add--;

    //Writing to File
    ofstream fout; //Creating an Output Stream

    fout.open("backupMessages.txt", ios::app); // Opening a File with the name "myFile", of type "text", in "append" mode

    //Writing to the File
    fout << endl << "MESSAGE" << endl;
    fout << "Payload: " << msg.payload << endl;
    fout << "ID: " << to_string(msg.msg_id) << endl;
    fout << "Priority: " << to_string(msg.priority) << endl;
    fout << "Source: " << msg.src_Name << endl;
    fout << "Destination: " << msg.des_Name << endl;

    fout.close(); //closing the file

    return msg;
}

void updateWeight() {

    int src = 0, des = 0, w;

    /*for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++)
            cout << left << setw(5) << weights[i][j];

        cout << endl;
    }*/

    cout << "Enter source id: ";
    cin >> src;

    cout << "Enter Destination id: ";
    cin >> des;

    cout << "Enter Weight: ";
    cin >> w;

    src = src - 1;
    des = des - 1;

    weights[src][des] = w;

    /*for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++)
            cout << left << setw(5) << weights[i][j];

        cout << endl;
    }*/

}

void changeEdge() {

    int src = 0, des = 0, w;

    /*for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++)
            cout << left << setw(5) << weights[i][j];

        cout << endl;
    }*/

    cout << "Change Edge between" << endl;

    cout << "Source ID: ";
    cin >> src;
    cout << "Destination ID: ";
    cin.ignore();
    cin >> des;
    cout << "Enter Weight: ";
    cin.ignore();
    cin >> w;
    cin.ignore();
    src = src - 1;
    des = des - 1;

    if (w == 0) {
        weights[src][des] = 10000;
    }
    else
        weights[src][des] = w;

    /*for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 20; j++)
            cout << left << setw(5) << weights[i][j];

        cout << endl;
    }*/

}

//////////////////////////////////////////////////////// MAIN ////////////////////////////////////////////////////////
int main()
{

    makeGraph();

    bool replay = true;

    while (replay)
    {
        int choice = 0;


        cout << "*****************************************" << endl;
        cout << "*" << "   (1) write a message" << setw(18) << "*" << endl;
        cout << "*" << "   (2) read the message from a file" << setw(5) << "*" << endl;
        cout << "*" << "   (3) change the weight of an edge" << setw(5) << "*" << endl;
        cout << "*" << "   (4) change an edge" << setw(19) << "*" << endl;
        cout << "*****************************************" << endl;

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            bool again = true;
            message msg[5];
            int x = 0;
            Priority_Queue<message> msg_queue;
            while (again)
            {
                msg[x].write_msg();
                msg_queue.insert(msg[x], msg[x].priority);
                cout << "Do you want to enter another message" << endl;
                cout << "Press 1 for YES" << endl;
                cout << "Press 0 for NO !" << endl;
                cin >> again;
                x++;
            }

            for (int k = 0; k <= x; k++)
            {

                routingTable rt;
                message msgtemp = msg_queue.dequeue();
                rt.sourceNode = msgtemp.src_add;
                rt.destinationNode = msgtemp.des_add;

                rt.dijkstra_algorithm();
                int noOfRouters = rt.routerPath.size;
                router* routers = new router[noOfRouters];


                for (int i = 0; i < noOfRouters; i++)
                {
                    if (i == 0)
                    {
                        routers[i].num = rt.routerPath.Access(i);
                        routers[i].id = rt.routerPath.findNode(i);
                        routers[i].router_name = Names[routers[i].id].name;
                        routers[i].msg = msgtemp;
                        routers[i].insert_message();
                        routers[i].displayRouter();
                        routers[i].display_incoming();
                        cout << endl;
                        Sleep(1000);
                        routers[i].outgoing.enqueue(routers[i].incoming.dequeue());

                    }
                    else
                    {
                        routers[i].num = rt.routerPath.Access(i);
                        routers[i].id = rt.routerPath.findNode(i);

                        routers[i].router_name = Names[routers[i].id].name;
                        routers[i].msg = routers[i - 1].outgoing.dequeue();
                        routers[i].insert_message();
                        routers[i].displayRouter();
                        routers[i].display_incoming();
                        cout << endl;
                        Sleep(1000);
                        routers[i].outgoing.enqueue(routers[i].incoming.dequeue());

                    }
                }
                cout << "Message Successfully Delivered to Destination Address" << endl;

            }
            break;
        }
        case 2:
        {
            message m(readMessageFromFile("message.txt"));
            routingTable rt(m);
            rt.dijkstra_algorithm();

            int noOfRouters = rt.routerPath.size;
            router* routers = new router[noOfRouters];

            for (int i = 0; i < noOfRouters; i++)
            {
                if (i == 0)
                {
                    routers[i].num = rt.routerPath.Access(i);
                    routers[i].id = rt.routerPath.findNode(i);
                    routers[i].router_name = Names[routers[i].id].name;
                    routers[i].msg = m;
                    routers[i].insert_message();
                    routers[i].displayRouter();
                    routers[i].display_incoming();
                    cout << endl;
                    Sleep(1000);
                    routers[i].outgoing.enqueue(routers[i].incoming.dequeue());

                }
                else
                {
                    routers[i].num = rt.routerPath.Access(i);
                    routers[i].id = rt.routerPath.findNode(i);

                    routers[i].router_name = Names[routers[i].id].name;
                    routers[i].msg = routers[i - 1].outgoing.dequeue();
                    routers[i].insert_message();
                    routers[i].displayRouter();
                    routers[i].display_incoming();
                    cout << endl;
                    Sleep(1000);
                    routers[i].outgoing.enqueue(routers[i].incoming.dequeue());

                }
            }
            cout << "Message Successfully Delivered to Destination Address" << endl;

            break;
        }
        case 3:
        {
            updateWeight();

            break;
        }
        case 4:
        {
            changeEdge();

            break;
        }
        }

        cout << "Do you want play again?" << endl;
        cout << "(1) YES" << endl;
        cout << "(0) NO!!!!" << endl;
        cin >> replay;

    }


    return 0;
}