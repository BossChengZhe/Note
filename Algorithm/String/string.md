### 字典树(`Trie`树)

字典树，单词查找树或者说前缀树，是一种利用时间换空间的快速检索的多叉树结构。字典树的根节点不包含字符，除了根节点外每个节点都包含一个字符

#### 构建字典树

```C++
struct Trie 
{
    char val;           // 当前节点字符
    Trie* child[26];    // 由于是英文，所以有26个可能子树
    bool is_end;        // 标志以当前节点为结束的字符串是否是一个单词
    int cnt;
        
    Trie()
    {
        val = '0';
        memset(child, 0, sizeof(child));
        is_end = false;
        cnt = 0;
    }
};
```

#### 插入操作

按照字符串下标依次将字符插入到字典树中，如果当前字母对应的节点存在则继续，不存在则新建节点

```C++
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
```

#### 查询操作

对一个单词如果单词当前字符在字典树中存在，继续寻找下一字符；如果不在字典树中，则返回`false`

```C++
bool _search(Trie *root, string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if (root->child[s[i]-'a']==nullptr)
            return false;
        root = root->child[s[i]-'a'];
    }
    root->cnt++;
    return true;
}
```

