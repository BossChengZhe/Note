### 图的广度优先遍历

```c++
for (int i = 0; i < Node_Num; i++)
{
    if(visit[i])
        continue;
    queue<int> q;
    q.push(i);
    visit[i] = true;
    while(!q.empty())
    {
        int node = q.fornt();
        q.pop();
        for (int j = 0; j < Node_Num; j++)
            if(graph[node][j]&&!visit[j])
            {
                q.push(j);
                visit[j] = true;
            }    
    }
}
```

### 图的深度优先队列

```C++
void DFS(int node, vector<bool> &visit, vector<vector<bool>> &graph)
{
    for(int i = 0; i < node_num; i++)
        if(garph[node][i] && !visit[i])
        {
            visit[i] = true;
            DFS(i, visit, graph);
        }
}
```

#### 连通子图

图的深度优先遍历和广度优先遍历都可以实现连通子图，但是深度优先遍历代码简单的一

```C++
void dfs(vector<vector<bool>> &graph, vector<int> &res, vector<bool> &visit, int node)
// res存储连通子图内的节点，node表示当前遍历到的节点
{
    for(int i = 0; i < graph.size(); i++)
    {
        if(graph[node][i] && !visit[i]){ 
            res.push_back(i);
            visit[i] = true;
            dfs(graph, res, visit, i);
        }
    }
}

vector<bool> visit(n, false);
vector<vector<int>> res;
for(int i = 0; i < n; i++)
{
    // 从每个节点开始依次遍历，如果子图是连通的，所有的节点肯定能够遍历到
    vector<int> tmp;
    if(!visit[i])
    { 
        visit[i] = true;
        tmp.push_back(i);
        dfs(graph, tmp, visit, i);
        sort(tmp.begin(), tmp.end());
        res.push_back(tmp);
    }
}
```



### Dijkstra算法：

#### Dijkstra算法框架

在今年师兄笔试的时候遇见过Dijkstra算法，在此记录下Dijkstra算

法的框架和原理。

1. 初始化集合`S`和`U`，其中结合`S`表示已经存在于最小生成树中的节点，`U`中节点都不在最小生成树中

2. 在初始化集合`S`和`U`之后，将源节点置入集合`S`中，表示源节点到其自身距离是最短的，并且用源节点优化其他节点的距离；

3. 在`U`集合中寻找当前最短的路径最短的节点，并将其加入`S`中；

4. 假设在3中加入`S`的节点是K，那么按照如下公式更新距离,A是源节点，
   $$
   distance_{A,D}=\min_{D\in U}\{distance_{A,K}+distance_{K,D}, distance_{A,D}\}
   $$

5. 重复步骤3,4

图节点数据很多的话，Dijkstra算法很多时间就会浪费在寻找最小距离的节点上，所以我们需要建立一个数据结构使我们在很短的时间内直接找到当前最小距离的节点，很显然我们利用优先队列即可实现寻找最小距离节点。

#### Dijkstra源码讲解

整体代码见同级目录下`Dijkstra.cpp`文件

- 由于我们不仅仅想要知道当前最小路径的值，还要知道当前最小路径对应的节点，以及从源节点到该节点的路径，所以我们需要一个结构体`node`存储这些信息，那么这结构体又怎么列入到最小优先队列中呢，我们需要重载运算符`<`

  ```C++
  struct node
  {
      int node_id;
      int dist;
      int update;
      bool operator<(const node &a) const
      {
          if (dist == a.dist)
              return node_id > a.node_id;
          return dist > a.dist;
      }
  };
  ```

  上面就是结构体内容，`node_id`存储节点ID，`dist`存储距离，`update`记录节点当前`dist`是由哪个节点松弛方便记录节点次序。而`bool operator<(const node &a)`就是对运算符`<`的重载，由于优先队列默认的是大顶堆，而我们需要的是小顶堆，就需要改变优先级将`<`重载(底层原理现在的我解释不清楚，留待以后)，这样就可以得到当前最下距离以及其对应的节点。

- 初始化很重要：`visit`记录已经存在于最小生成树中的节点，相当于上文中节点`S`的作用，`d`用来存储节点信息，`path`打印源节点到当前节点的路径，`q`为寻找当前最小距离节点的有限队列

  ```C++
  int node_num = graph.size();
  vector<node> d(node_num, {0, M, 0});
  vector<bool> visit(node_num, false);
  for (int i = 0; i < node_num; i++)
      d[i].node_id = i;
  
  d[start].dist = 0;
  path[start] = to_string(start);
  
  priority_queue<node> q;
  q.push(d[start]);
  ```

- 松弛(节点更新)过程：将当前优先队列队头元素取出，

  - 如果当前节点已经处于最小生成树中，直接开始下一循环
  - 如果当前节点没有被访问过也就是不在最小生成树中，那么开始更新节点，更新对象为没有标记过的顶点，并且经由节点`K`到达该节点比原始距离要短，跟新其更新节点和距离，并将其推入优先队列中。走完`for`循环，一次更新结束，并且加入了一个新的节点到生成树中。

  ```c++
  while (!q.empty())
  {
      node tmp = q.top();
      q.pop();
      if (visit[tmp.node_id])
          continue;
      visit[tmp.node_id] = true;
      // 打印路径
      path[tmp.node_id] = (path[tmp.update] + "->" + (char)(tmp.node_id + 'A'));
      if (tmp.node_id == start)
          path[tmp.node_id] = tmp.node_id + 'A';
  
      // 更新节点信息
      for (int i = 0; i < node_num; i++)
      {
          if (!visit[i] && d[i].dist > d[tmp.node_id].dist + graph[tmp.node_id][i])
          {
              d[i].update = tmp.node_id;
              d[i].dist = d[tmp.node_id].dist + graph[tmp.node_id][i];
              q.push(d[i]);
          }
      }
  }
  ```

  重复该过程最后，队列为空`Dijkstra`算法终止。



