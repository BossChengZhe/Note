## MySQL高级优化

#### 一、MySQL架构介绍

1. MySQL逻辑系统架构分成四层：应用层、MySQL服务层、存储引擎层和数据存储层。它采用插件式的存储引擎架构将查询处理和其他系统任务以及数据存储提取相分离。

![img](https://pic2.zhimg.com/80/v2-4ce9c07e160c6c3e48387bc98d5295e1_1440w.jpg)

2. **应用层**：MySQL体系架构的最上层。
   * **连接处理**（Connection Handling）：当一个客户端向服务端发送连接请求后，MySQL server会从**线程池**中分配一个线程来和客户端进行连接，以后该客户端的请求都会被分配到该线程上。MySQL Server为了提高性能，提供了线程池，减少了创建线程和释放线程所花费的时间。
   * **用户鉴权**（Authentication）：当客户端向MySQL服务端发起连接请求后，MySQL server会对发起连接的用户进行鉴权处理，MySQL鉴权依据是: 用户名，客户端主机地址和用户密码。
   * **安全管理**（Security）：当客户连接到MySQL server后，MySQL server会根据用户的权限来判断用户具体可执行哪些操作。
3. **服务层**：MySQL的核心层，提供了MySQL Server数据库系统的所有逻辑功能。
   * **MySQL Management Server & utilities(系统管理)** ：提供了丰富的数据库管理功能。
     * 数据库备份和恢复
     * 数据库安全管理，如用户及权限管理
     * 数据库复制管理
     * 数据库集群管理
     * 数据库分区，分库，分表管理
     * 数据库元数据管理
   * **SQL Interface(SQL 接口)** ：SQL接口，接收用户的SQL命令并进行处理，得到用户所需要的结果。
     * Data Manipulation Language (DML).
     * Data Definition Language (DDL).
     * 存储过程
     * 视图
     * 触发器
   * **SQL Parser(SQL 解析器)** ：解析器的作用主要是解析查询语句，最终生成语法树。首先解析器会对查询语句进行语法分析，如果语句语法有错误，则返回相应的错误信息。语法检查通过后，解析器会查询缓存，如果缓存中有对应的语句，就直接返回结果不进行接下来的优化执行操作。
   * **Optimizer(查询优化器)** ：优化器的作用主要是对查询语句进行优化，包括选择合适的索引，数据的读取方式。
   * **Caches & buffers(缓存)** ：包括全局和引擎特定的缓存，提高查询的效率。如果查询缓存中有命中的查询结果，则查询语句就可以从缓存中取数据，无须再通过解析和执行。这个缓存机制是由一系列小缓存组成，如表缓存、记录缓存、key缓存、权限缓存等。
4. **存储引擎层**：存储引擎是MySQL中具体与文件打交道的子系统，也是MySQL最有特色的地方。MySQL区别于其他数据库的最重要特点是其插件式的表存储引擎。
5. 参考链接：
   * https://zhuanlan.zhihu.com/p/43736857
   * https://www.cnblogs.com/huangjuncong/p/11318810.html
   * https://juejin.cn/post/6844903505283514381

#### 二、索引优化分析

1. **索引（Index）**：是帮助MySQL高效获取数据的==数据结构==，其目的在于提高查询效率，可以类比字典。索引就是一种==排好序==的==快速查找==数据结构。数据本身之外，数据库还维护着一个满足特定查找算法的数据结构，这些数据结构以某种方式指向数据，在这些数据结构基础上实现高级查找算法。

2. 索引分类：

   * 单值索引：即一个索引只包含单个列，一个表可以有多个单值索引；
   * 唯一索引：索引列值必须唯一，但允许有空值；
   * 复合索引：一个索引包含多个列；

3. 索引基本语法：

   * 创建索引：

     ```mysql
     create [unique] index index_name on table_name(column_name(length));
     alter table_name add [unique] index index_name on (column_name(length));
     ```

   * 删除索引：

     ```mysql
     drop index index_name on table_name;
     ```

   * 查看索引：

     ```mysql
     show index from table_name;
     ```

4. MySQL索引结构：

   * BTree索引：
   * Hash索引：
   * full-text全文索引：
   * R-Tree索引：

5. 创建索引的情况：

   * 主键自动建立唯一索引；
   * 频繁作为查询条件的字段应该创建；
   * 查询中与其他表关联的字段，外键关系建立索引；
   * 查询中排序的字段；
   * 查询中统计或者分组字段。

6. 不适合创建索引的情况：

   * 表记录太少；
   * 经常增删改的表；
   * 数据重复且平均分配的表字段。

7. EXPLAIN：模拟优化器执行sql查询语句，分析查询语句或者表结构的性能瓶颈。

   其主要作用有以下几种：

   * 表的读取顺序（id）；
   * 数据读取操作的操作类型（select_type）；
   * 哪些索引可以使用（possble_keys）；
   * 哪些索引被实际使用（key）；
   * 表之间的引用；
   * 每张表有多少行被优化器查询（rows）。

8. 覆盖索引：select的数据列只用从索引中就能够获取得到，不必读取数据行。

9. join优化：永远用小结果集驱动大的结果集，保证join语句中==被驱动表==上join条件字段已经被索引。

10. 索引优化要求：

    * 全值匹配：使用复合索引的所有列；

    * 最佳左前缀法则：如果索引有多列，要遵守最左前缀法则，即查询从索引的最左前列开始并且==不跳过索引中的列==；

    * 不要在索引列上做任何操作（计算，函数或类型转换），会导致索引失效而全表搜索；

      ```mysql
      EXPLAIN SELECT * FROM staffs WHERE LEFT(NAME,4)="july";
      ```

    * 存储引擎不能使用索引中范围条件右边的列：

      ```sql
      EXPLAIN SELECT * FROM staffs WHERE NAME="july" AND age>25 AND pos = 'dev';
      ```

    * 尽量使用覆盖索引，减少select *；

    * 在使用!=或者<>时无法使用索引会导致全表扫描；

    * is null, is not null也无法使用索引；

    * like以通配符开头%abc时，msyql索引失效会变成全表扫描，可以使用覆盖索引来解决；

    * 字符串不加单引号索引会失效；

    * 少用or，也会导致索引失效。

11. 索引选择：

    * 对于单键索引，尽量选择针对当前查询过滤性更好的索引；
    * 选择组合索引时，过滤性最好字段在索引顺序中位置尽量靠前，选择where字句中包含更多字段的索引。

#### 三、查询截取分析

1. 整体过程：
   * 慢查询的开启并捕获；
   * explain+慢SQL分析；
   * show profile查询SQL在MySQL服务器里面的执行细节和生命周期情况；
   * SQL数据库服务器的参数调优。
2. 在多表查询时，如果B表的数据集小于A表数据集时，查询A表时用in更优，否则用exists。
3. order by关键字优化：尽量使用Index方式排序，避免使用FileSort方式排序；

#### 四、MySQL锁机制

1. 数据操作类型分类：

   * 读锁（共享锁）：针对同一份数据，多个读操作可以同时进行而不会相互影响，加读锁后其他session可以读但不可以进行写操作；

   * 写锁（排它锁）：当前写操作没有完成前，会阻断其他写锁和读锁。

     ```sql
     lock table mylock read,book write;
     ```

2. MyISAM在执行查询语句时前，会自动给涉及的所有表加读锁，在执行增删改操作前，会自动给涉及表加写锁。读锁会阻塞写操作，但不会阻塞读操作，而写锁会把读写操作都阻塞。

3. 加锁粒度分类：

   * 表锁：偏向于读操作，
   * 行锁：偏向于写操作，支持事务；

4. 间隙锁：当我们用范围条件而不是相等条件检索数据，并请求共享或排他锁时，InnoDB会给符合条件的已有数据记录的索引项加锁，对于键值在条件范围但不存在的记录，叫做间隙GAP。

5. 行锁定：for update锁定某一行后，其他操作会被阻塞，直到锁定行的会话提交。

   ```sql
   begin;
   select * from test_table where a=8 for update;
   commit;
   ```

#### 五、主从复制

1. 复制的基本原理：

   ![img](https://pic1.zhimg.com/80/v2-4cc45135539256c966a7113db9247194_1440w.jpg)

2. MySQL复制过程：

   * master将改变记录到二进制日志(Binary Log)，这些记录过程叫做二进制日志事件，`Binary Log Events`；
   * Slave将Master的`Binary Log Events`拷贝到它的中继日志(Replay Log);
   * Slave重做中继日志中的事件，将改变应用到自己的数据库中。MySQL复制是异步且串行化的。

3. 复制的基本原则：

   - 每个Slave只有一个Master。
   - 每个Slave只能有一个唯一的服务器ID。
   - 每个Master可以有多个Salve。

4. 链接：https://zhuanlan.zhihu.com/p/351206384