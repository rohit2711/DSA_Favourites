#include<bits/stdc++.h>
using namespace std;


class Trie {
    public:
    class TrieNode{
        public:
        TrieNode* children[26];
        int p_count;
        char data;
        int end_count;
         TrieNode(char data){
            this -> p_count = 0;
            this -> data = data;
            for(int i = 0 ; i<26; i++){
                children[i] = NULL;
            }

            this -> end_count = 0;
         }


    };

    TrieNode* root;
    Trie() {
        root = new TrieNode('\0');

        
    }

    void insertUtil(TrieNode* root,string word){
        if(word.length() == 0){
            
            root->end_count += 1;
            return;
        }

        TrieNode* child;
        int idx = word[0]-'a';

        if(root -> children[idx] != NULL){
            child = root->children[idx];
        }else{
            child = new TrieNode(word[0]);
            root->children[idx] = child;
        }
        child -> p_count += 1;

        insertUtil(child,word.substr(1));
    }
    
    void insert(string word) {
        insertUtil(root,word);
        return;
        
    }

    int searchUtil(TrieNode* root, string word){
        if(word.length() == 0){
            
                return root->end_count;
            
        }

        int idx = word[0]-'a';
        TrieNode* child;
        if(root->children[idx] != NULL){
            child = root->children[idx];
        }else{
            return 0;
        }

        return searchUtil(child, word.substr(1));
    }
    
    int countWordsEqualTo(string word) {
        return searchUtil(root,word);
        
    }

     int searchUtil2(TrieNode* root, string word){
        if(word.length() == 0){
            return root->p_count;
        }

        int idx = word[0]-'a';
        TrieNode* child;
        if(root->children[idx] != NULL){
            child = root->children[idx];
        }else{
            return 0;
        }

        return searchUtil2(child, word.substr(1));
    }
    
    int countWordsStartingWith(string prefix) {
        return searchUtil2(root,prefix);
        
    }

     void eraseUtil(TrieNode* root,string word){
       int len = word.size();
       int i= 0;
       TrieNode* node = root;
       while( i< len){
           int idx = word[i] - 'a';
           node = node -> children[idx];
           node ->p_count--;
           i++;
       }
       node -> end_count--;
    }
    
    void erase(string word) {
        eraseUtil(root,word);
        return;
        
    }
};

int main(){
    //example testcase


    return 0;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */