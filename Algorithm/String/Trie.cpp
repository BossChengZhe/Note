#include "iostream"
#include "vector"
#include "memory.h"
#include "string"
using namespace std;

struct Trie 
{
    char val;
    Trie* child[26];
    bool is_end;

    Trie()
    {
        val = '0';
        memset(child, 0, sizeof(child));
        is_end = false;
    }
};

void _inset(Trie *&root, string s)
{
    int len = s.length();
    Trie *temp = root;
    for(int i = 0; i < len; i++)
    {
        if (temp->child[s[i]-'a']==nullptr)
            temp->child[s[i]-'a'] = new Trie();
        temp = temp->child[s[i]-'a'];
        temp->val = s[i];
    }
    temp->is_end = true;
}

bool _search(Trie *root, string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if (root->child[s[i]-'a']==nullptr)
            return false;
        root = root->child[s[i]-'a'];
    }
    return true;
}