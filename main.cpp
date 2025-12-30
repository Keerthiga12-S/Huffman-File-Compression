#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};
unordered_map<char, int> buildFrequency(string text) {
    unordered_map<char, int> freq;
    for (char c : text)
        freq[c]++;
    return freq;
}
Node* buildHuffmanTree(unordered_map<char, int> freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }
    return pq.top();
}
void generateCodes(Node* root, string code,
                   unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (root->ch != '\0')
        huffmanCode[root->ch] = code;

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}
string compress(string text,
                unordered_map<char, string>& huffmanCode) {
    string encoded = "";
    for (char c : text)
        encoded += huffmanCode[c];
    return encoded;
}
string decompress(Node* root, string encoded) {
    string decoded = "";
    Node* curr = root;

    for (char bit : encoded) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }
    return decoded;
}
int main() {
    ifstream inFile("input.txt");
    string text((istreambuf_iterator<char>(inFile)),
                 istreambuf_iterator<char>());
    inFile.close();

    auto freq = buildFrequency(text);
    Node* root = buildHuffmanTree(freq);

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    string compressed = compress(text, huffmanCode);

    ofstream outFile("compressed.txt");
    outFile << compressed;
    outFile.close();

    string decompressed = decompress(root, compressed);

    ofstream decFile("decompressed.txt");
    decFile << decompressed;
    decFile.close();

    cout << "Compression and Decompression Successful!" << endl;
    return 0;
}
