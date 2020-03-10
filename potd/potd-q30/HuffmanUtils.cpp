#include "HuffmanNode.h"
#include "HuffmanUtils.h"
#include <string>
#include <stack>
#include <iostream>

using std::string;

/**
 * binaryToString
 *
 * Write a function that takes in the root to a huffman tree
 * and a binary string.
 *
 * Remember 0s in the string mean left and 1s mean right.
 */

string binaryToString(string binaryString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
    HuffmanNode* curr = huffmanTree;
    string out = "";
    for (char& c : binaryString) {
      if (curr->left_ == NULL && curr->right_ == NULL) {
        out += curr->char_;
        curr = huffmanTree;
      }
      if (c == '0') {
        curr = curr->left_;
      } else {
        curr = curr->right_;
      }
    }
    return out;
}

/**
 * stringToBinary
 *
 * Write a function that takes in the root to a huffman tree
 * and a character string. Return the binary representation of the string
 * using the huffman tree.
 *
 * Remember 0s in the binary string mean left and 1s mean right
 */

string stringToBinary(string charString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
    string binary = "";
    for (char& c : charString) {
      stack<HuffmanNode*> s;
      s.push(huffmanTree);
      HuffmanNode* curr = huffmanTree->left_;
      while (true) {
        while (curr != NULL) {
          s.push(curr);
          curr = curr->left_;
            binary += "0";
        }
        if (s.top()->char_ == c) {
          break;
        }
        binary.pop_back();
        binary += "1";
        curr = s.top()->right_;
        s.pop();
      }
    }
    return binary;
}
