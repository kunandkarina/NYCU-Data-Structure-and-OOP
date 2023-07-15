#include <iostream>
#include <string>
#include <vector>
#include<queue>
#include<iomanip>
#include<fstream>
#include<sstream>
using namespace std;
int a[128];
int WEPL = 0;
vector<char> data1 = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
vector<int> weight1 = {11,5,2,3,12,3,5,6,8,1,2,4,8,7,2,2,1,9,6,2,4,1,10,10,1,1};
char ans1[58];
string ans2[58];
vector<char> data2;
vector<int> weight2;
class huffnode{
public:
    huffnode(char ch, int weights){
        data = ch;
        weight = weights;
        left = right = NULL;
    }
    char data;
    int weight;
    huffnode* left;
    huffnode* right;
    string code;
};

class compare{
public:
    bool operator()(huffnode* a, huffnode* b){
        return a->weight > b->weight;
    }
};

huffnode* generateTree(priority_queue<huffnode* ,vector<huffnode*> ,compare> pq){
    while(pq.size()!= 1 ){
        huffnode* left = pq.top();
        pq.pop();
        huffnode* right = pq.top();
        pq.pop();
        huffnode* node = new huffnode('P',left->weight + right->weight);
        node->left = left;
        node->right = right;
        pq.push(node);
    }
    return pq.top();
}
void DFS(huffnode* root,int Size,vector<char>data,vector<int>weight){
    if(root->left){
        root->left->code = root->code + "0";
        DFS(root->left,Size,data,weight);
    }
    if(root->right){
        root->right->code = root->code + "1";
        DFS(root->right,Size,data,weight);
    }
    if(!root->left && !root->right){
        ans1[root->data - 'A'] = root->data;
        ans2[root->data - 'A'] = root->code;
//        cout << root->data << " ";
//        cout << root->code;
//        cout << endl;
        int j;
        for(int i=0;i<Size;i++){
            if(data[i] == root->data) j = i;
           // cout << ans1[i] << " " << ":" << " " << ans2[i];
        }
        WEPL += root->code.size()*weight[j];
    }
}
void decodeFile(huffnode* root,string s){
    bool temp = true;
    string ans = "";
    class huffnode* curr = root;
    for(int i=0;i<s.size();i++){
        if(s[i] == '0')
            curr = curr->left;
        else if(s[i] == '1')
            curr = curr->right;
        if(curr->left == NULL && curr->right == NULL){
            ans += curr->data;
            curr = root;
        }
    }
    if(curr != root) temp = false;
    string decodeString = ans + '\0';
    //cout << temp << endl;
    if(temp == false) cout << "decode : " << decodeString << " " << "-wrong decode-" <<endl;
    else cout << "decode : " << decodeString << endl;

}

void decode(vector<char> data, vector<int> weight, int Size, string s){
    priority_queue<huffnode* , vector<huffnode*> ,compare> pq2;
    for(int i=0;i<Size;i++){
        huffnode* newNode = new huffnode(data[i],weight[i]);
        pq2.push(newNode);
    }
    huffnode* root = generateTree(pq2);
    decodeFile(root,s);
}

void huffcode(vector<char> data, vector<int> weight, int Size){
    priority_queue<huffnode* , vector<huffnode*> ,compare> pq;
    for(int i=0;i<Size;i++){
        huffnode* newNode = new huffnode(data[i],weight[i]);
        pq.push(newNode);
    }
    huffnode* root = generateTree(pq);
    DFS(root,Size,data,weight);
}
void part1(){
    int Size = data1.size();
    huffcode(data1, weight1, Size);
    for(int i=0;i<Size;i++){
        cout << data1[i] << " " << "=" << " " << setw(2) << weight1[i] << " " << "|" << " ";
        if(i%10 == 9) cout << endl;
    }
    cout << endl;
    cout << endl;
    for(int i=0;i<Size;i++){
        if(ans1[i] != '\0')
        cout << ans1[i] << " " << ":" << " " << ans2[i] << endl;
    }
    cout << endl;
    cout << "WEPL" << " " << ":" << " " << WEPL << " ";
}

void part2(string filename){
    cout << "DSOO-Program2-Demo: ./tree " << filename << endl;
    ifstream input_file;
    input_file.open(filename);
    if (!input_file.is_open()) { cout << "error!" << endl; }
    stringstream ss1, ss2;
    ss1 << input_file.rdbuf();
    string s1(ss1.str()); 
    string s2 = s1;
    int index;
    for(index = 0; index < s1.size() && s1[index] != ' '; index++);
    s1.erase(index, s1.size() / 2 + 1); 
    s2.erase(s2.begin(),s2.begin()+index);
    //cout<<s1<<endl<<s2<<endl;
    for(int i=0;i<s1.size();i++){
        a[s1[i]]++;
    }
    for(int i=65;i<128;i++){
        if(a[i]!=0){
            data2.push_back(i);
        }
    }
    for(int i=65;i<128;i++){
        if(a[i]!=0){
            weight2.push_back(a[i]);
        }
    }
    int Size2 = data2.size();
    huffcode(data2, weight2, Size2);
    cout << "characters : " << s1 << endl << endl;
    for(int i=0;i<Size2;i++){
        cout << data2[i] << " " << "=" << " " << setw(2) <<  weight2[i] << " " << "|" << " ";
        if(i%10==9) cout << endl;
    }
    cout << endl;
    for(int i=0;i<58;i++){
        if(ans1[i] != '\0')
        cout << ans1[i] << " " << ":" << " " << ans2[i] << endl;
    }
    cout << endl;
    
    cout << "Huffman code : " << s2 << endl;
    decode(data2,weight2,Size2,s2); 
    cout << "WEPL" << " " << ":" << " " << WEPL << " "; 
}
int main(int argc, const char* argv[]){
    vector<string> all_args;
    all_args.assign(argv, argv + argc); // convert command line argument to string

   cout << "DSOO-Program2-Demo: ";
    for(auto a : all_args){
        cout << a << " ";
    }
    cout << "\n"; 
     if(argc != 2){
        cout << "part1\n";
        part1();
    }else{
        string filename = argv[1];
        cout << "read file from : " << "test/" << filename << endl;
        part2(filename);

    } 
    return 0;
}