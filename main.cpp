#include<bits/stdc++.h>
using namespace std;
#include <unistd.h>

void delay(int n){
    sleep(n);
    return;
}

struct Node{
    char ch;
    int f;
    Node *left,*right;
};

Node* getNode(char c,int freq,Node *l,Node *r){
    Node *n=new Node();
    n->ch=c;
    n->f=freq;
    n->left=l;
    n->right=r;
    return n;
}

struct comp{
    bool operator()(Node* a,Node* b){
        return a->f>b->f;
    }
};

long long actual_size;

Node* make_tree(string tocompress){
    fstream file;
    file.open(tocompress);

    unordered_map<char,int> fmp;

    char ch;
    while(file.get(ch)){
        actual_size++;
        fmp[ch]++;
    }

    priority_queue<Node*,vector<Node*>,comp> pq;

    for(auto it : fmp){
        pq.push(getNode(it.first,it.second,NULL,NULL));
    }

    while(pq.size()>1){
        Node *a=pq.top();pq.pop();
        Node *b=pq.top();pq.pop();

        pq.push(getNode('\0',a->f+b->f,a,b));
    }

    file.close();

    return pq.top();
}

void create_codes(string s,Node *root,map<char,string> &mp){

    if(root==NULL) return;

    if(!root->left && !root->right){
        mp[root->ch]=s;
    }

    create_codes(s+"0",root->left,mp);
    create_codes(s+"1",root->right,mp);

    return;
}

void encode(string tocompress,string compressed_file,map<char,string> &mp){

    fstream en,file;
    en.open(compressed_file);

    file.open(tocompress);
    char ch;

    long long size=0;

    while(file.get(ch)){
        string s=mp[ch];
        en<<s;
        size+=s.size();
    }

    cout<<endl<<"Number of Bits used are "<<size<<endl;
    cout<<"So the aprrox size is "<<(size/8)/1024<<" Kilo Bytes"<<endl;
    delay(2);

    file.close();
    en.close();

    return;
}

void compress_file(string tocompress,string compressed_file,Node* huff_tree){
    fstream in;
    fstream out;
    in.open(tocompress);
    out.open(compressed_file);
    if(!in){
        cout<<"No input file found!"<<endl;
        return;
    }

    if(!out){
        cout<<"No out file found!"<<endl;
        return;
    }

    in.close();
    out.close();

    map<char,string> mp;

    create_codes("",huff_tree,mp);

    cout<<endl<<"Codes are created for each character"<<endl<<endl;
    delay(1);

    encode(tocompress,compressed_file,mp);

    cout<<endl<<"file compressed succesfully!"<<endl;

    return;
}

void decompress_file(string compressed_file,string decompressed_file,Node* huff_tree){
    fstream en,de;
    en.open(compressed_file,ios :: in);
    de.open(decompressed_file,ios :: out);

    if(!en){
        cout<<"No compressed file!"<<endl;
        return;
    }
    if(!de){
        cout<<"No decompressed file!"<<endl;
        return;
    }

    char c;

    Node *root=huff_tree;

    while(en>>c){
        if(c=='0'){
            root=root->left;
        }else{
            root=root->right;
        }

        if(root->ch!='\0'){
            de.put(root->ch);
            root=huff_tree;
        }
    }

    en.close();
    de.close();
    
    cout<<endl<<"file decompressed succesfully!"<<endl;

    return;
}

int main(){

    string tocompress="inputfile.txt";
    string compressed_file="compressed_file.txt";
    string decompressed_file="decompressed_file.txt";

    cout<<endl<<"This is a Compression and Decompression code for text file from GUKS"<<endl<<endl;

    delay(1);

    cout<<"Huffman coding is a lossless data compression algorithm. This means that no information is lost when the file is compressed and decompressed. The algorithm works by assigning variable-length codes to each character in the file, where the length of the code is inversely proportional to the frequency of the character. In other words, the most frequent characters are assigned the shortest codes, and the least frequent characters are assigned the longest codes."<<endl<<endl;
    delay(3);

    Node* huff_tree;
    actual_size=0;

    huff_tree=make_tree(tocompress);

    cout<<endl<<"The actual size of given input file is "<<actual_size/1024<<" Kilo Bytes"<<endl<<endl;

    cout<<endl<<"Hufmann Tree Created"<<endl;

    compress_file(tocompress,compressed_file,huff_tree);
    delay(2);

    decompress_file(compressed_file,decompressed_file,huff_tree);
    delay(1);
    cout<<endl<<endl<<"       "<<"Thank You"<<endl;
    delay(5);

    cout<<endl<<endl<<"type any digit and enter to exist"<<endl;
    int exit;
    cin>>exit;


    return 0;
}