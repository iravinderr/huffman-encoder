#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;


// creating Node class for the Binary Tree in which each Node will contain the sum of the values of its childrens
class Node{
    public:
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};


// creating the comparator class for the min-heap
class cmp{
    public:
    bool operator()(Node* a, Node* b){
        return a->data > b->data;
    }
};


// function to count the frequency of each character in the input string and storing them using hashmaps
unordered_map<char, int> frequencyCounter(string str){
    unordered_map<char, int> f;
    string :: iterator it = str.begin();
    while(it != str.end()){
        char c = *it;
        f[c]++;
        it++;
    }

    return f;
}


// dfs function to traverse the binary tree and store the huffman codes formed for each character using hashmaps
void traverse(Node* &root, unordered_map<int, string> &codes, string temp){
    if(root->left == NULL && root->right == NULL){
        codes[root->data] = temp;
        return;
    }

    traverse(root->left, codes, temp + "0");
    traverse(root->right, codes, temp + "1");
}



int main(){

    // taking the input string
    string input;
    cout << "Enter the string : ";
    cin >> input;


    // counting the frequency of each character in the input string using frequencyCounter function and storing them using an unordered map
    unordered_map<char, int> freq = frequencyCounter(input);


    // creating a min-heap
    priority_queue<Node*, vector<Node*>, cmp> pq;


    // pushing the nodes in the min-heap containing the frequency of the character
    unordered_map<char, int> :: iterator it = freq.begin();
    while(it != freq.end()){
        Node* temp = new Node(it->second);
        pq.push(temp);
        it++;
    }



    // building the binary tree where each node's data is the sum of the values of its children nodes

    /* since it is a min-heap so the top most element is the smallest, so two minimum nodes are popped out
    and a new node is created which contain the sum of those two nodes and it is made their parent node and
    pushed into the heap */

    while(pq.size() > 1){
        Node* leftNode = pq.top();
        pq.pop();

        Node* rightNode = pq.top();
        pq.pop();

        Node* newNode = new Node(leftNode->data + rightNode->data);
        newNode->left = leftNode;
        newNode->right = rightNode;

        pq.push(newNode);
    }



    /* now the root node is popped out of the priority queue and each path is traversed to get the huffman
    code for each character*/

    Node* root = pq.top();
    unordered_map<int, string> codes;
    string temp = "";
    traverse(root, codes, temp);


    // iterating through the map to print the huffman codes
    it = freq.begin();
    while(it != freq.end()){
        cout << it->first << " -> " << codes[it->second] << endl;
        it++;
    }

    cout << endl;
}