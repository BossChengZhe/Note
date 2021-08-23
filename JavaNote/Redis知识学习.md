## Redis知识学习

#### 一、Redis基本介绍

1. Redis 是完全开源的，遵守 BSD 协议，是一个高性能的 key-value 数据库：
   - Redis支持数据的持久化，可以将内存中的数据保存在磁盘中，重启的时候可以再次加载进行使用。
   - Redis不仅仅支持简单的key-value类型的数据，同时还提供list，set，zset，hash等数据结构的存储。
   - Redis支持数据的备份，即master-slave模式的数据备份。

2. 安装问题：fatal error: jemalloc/jemalloc.h: No such file or directory。

    ```shell
    sudo apt install gcc 
    make distclean && make
    sudo make install
    ```

3. 后台启动：

    ```shell
    sudo cp redis.conf /etc/redis.conf
    daemon = yes
    cd /usr/local/bin/
    redis-server /etc/redis.conf
    ```

4. Redis默认有16个数据库，初始默认使用0号库，支持**多数据类型**、**持久化**、**单线程IO多路复用**，默认端口是6379。

#### 二、Redis数据类型

1. Redis的value底层数据结构为简单动态字符串，是可以修改的字符串，采用预分配冗余空间的方式。基本操作：

   * set key value：设置key-value值；
   * setnx key value：key不存在时设置值；
   * get key：获取key的value；
   * strlen key：获取对应value长度；

   * keys *：查看所有key；
   * exists key：判断某个key是否存在；
   * type key：查看key类型；
   * del key：删除指定的key数据；
   * unlink key：异步删除key；
   * expire key：设置key的过期时间；
   * ttl key：查看key的过期时间（-1永不过期，-2已经过期）；
   * incr/decr：+1/-1；
   * incrby/decrby key num：+num/-num；
   * mset/mget/msetnx：可以设置/获取多个key；
   * setrange/getrange:  范围值；
   * getset key：以新值换旧值；

2. List的数据结构为快速链表quickList，在列表元素较少情况下使用一块连续内存存储，即ziplist。redis将链表和ziplist结合起来组成了quickList，使用双向指针串接起来使用。

3. Set是string类型的无序集合，数据结构是字典，底层是一个hash表，所有value指向同一个内部值。

4. Hash是一个键值对集合，是一个string类型的field-value集合。当field-value长度较短且个数较少时，使用ziplist，否则使用hashtable。

5. Zset：有序集合中每个成员都关联了一个评分，集合成员唯一，但评分可以重复。底层使用了两个数据结构，第一个是**hash**来关联元素value和权重score，第二个是**跳跃表**，在于给元素value排序。

6. Redis的发布订阅模式：

   ```shell
   127.0.0.1:6379> SUBSCRIBE channel1
   127.0.0.1:6379> PUBLISH channel1 hello
   ```

7. Bitmaps：可以对字符串的位进行操作，每个单元只能存储0或1，操作命令有setbit、getbit、bitcount和bitop。

8. HyperLogLog：求取集合中不重复元素的个数，操作命令有pfadd和pfcount。

9. Geospatial：对地理坐标信息的支持，操作命令有geoadd、geopos、geodist和georadius。

#### 三、Redis实际应用

1. Jedis基本操作：

   ```java
   public class JedisDemo1 {
       public static void main(String[] args) {
           // 创建jedis对象
           Jedis jedis = new Jedis("192.168.0.110", 6379);
   
           // 测试连接
           String value = jedis.ping();
           System.out.println("value = " + value);
       }
   
       @Test
       public void demo1(){
           // 创建jedis对象
           Jedis jedis = new Jedis("192.168.0.110", 6379);
           // 添加数据
           jedis.set("name", "lucy");
           System.out.println(jedis.get("name"));
   
           jedis.mset("k1","v1","k2","v2");
           System.out.println(jedis.mget("k1", "k2"));
   
           Set<String> keys = jedis.keys("*");
           for (String key : keys){
               System.out.println("key = " + key);
           }
       }
   
       /**
        * 操作list
        */
       @Test
       public void demo2(){
           // 创建jedis对象
           Jedis jedis = new Jedis("192.168.0.110", 6379);
           jedis.lpush("key1", "lucy", "mary", "jack");
           List<String> list = jedis.lrange("key1", 0, -1);
           System.out.println("list = " + list);
       }
   
       /**
        * 操作set
        */
       @Test
       public void demo3(){
           // 创建jedis对象
           Jedis jedis = new Jedis("192.168.0.110", 6379);
           jedis.sadd("key2", "lucy", "mary", "jack", "lucy");
           Set<String> set = jedis.smembers("key2");
           System.out.println("set = " + set);
       }
   
       /**
        * 操作hash
        */
       @Test
       public void demo4(){
           // 创建jedis对象
           Jedis jedis = new Jedis("192.168.0.110", 6379);
           jedis.hset("user", "age", "20");
           jedis.hset("user", "name", "Lucy");
           System.out.println(jedis.hget("user", "age"));
       }
   
       /**
        * 操作zset
        */
       @Test
       public void demo5(){
           // 创建jedis对象
           Jedis jedis = new Jedis("192.168.0.110", 6379);
           jedis.zadd("china", 100d, "shanghai");
           Set<String> china = jedis.zrange("china", 0, -1);
           System.out.println("china = " + china);
       }
   }
   ```

#### 四、Redis事务操作

1. Redis事务操作是一个单独的隔离操作，事务中的所有命令都会序列化、按顺序执行。

2. 基本命令：

   * watch：监视多个key；

   * Multi：输入命令依次进入命令队列中，但不会执行；
   * Exec：将命令队列的命令进行执行；
   * discard：放弃组队。

3. 事务错误处理：组队失败，则全部命令失败；执行失败，则其他正常执行。

4. Redis使用乐观锁check-and-set机制。

5. Redis事务三特性：

   * 单独隔离操作：事务在执行过程中，不会被其他客户端请求打断；
   * 没有隔离级别的概念：在没有提交之前都不会实际执行；
   * 不保证原子性：执行过程中一条命令失败，其他命令仍会被执行。

6. 并发问题：

   * 连接超时使用redis连接池解决；
   * 超卖问题使用乐观锁解决，但会导致库存遗留问题；
   * 库存遗留问题使用lua脚本。

#### 五、Redis持久化操作

1. RDB（Redis Database）：在指定**时间间隔**内将内存中数据集**快照**写入磁盘。Redis会单独创建一个子线程进行持久化，先将数据写入到一个==临时文件==中，待持久化过程结束后，再替换持久化文件。优点是适合大数据规模复制，但缺点是==最后一次持久化的数据==可能会丢失。
2. AOF（Append Only File）：以日志形式来记录**每个写操作**（增量保存），将redis执行过的所有==写指令==记录下来，==读操作不记录==，只许追加文件但不可以修改文件，redis启动时会读取该文件重新构建数据。

#### 六、 Redis主从复制

1. 主从复制：实现读写分离，容灾的快速恢复。

2. 配置过程：

   ```shell
   # 添加三个配置文件redis_6379.conf、redis_6380.conf、redis_6381.conf
   include /myredis/redis.conf
   pidfile /var/run/redis_6379.pid
   port 6379
   dbfilename dump6379.rdb 
   # 启动三个redis服务
   redis-server redis_6379.conf
   # 查看当前库类型（master/slave）
   info replication
   # 设置主库和从库
   slaveof 127.0.0.1 6379
   ```

3. 一主二仆：

   * 当从服务器关闭后，重新连接并配置成为从服务器后，数据和主服务器**数据同步**。
   * 当主服务器关闭后，重新连接后仍然是**主服务器**。
   * 当从服务器连接后，从服务器向主服务器发送进行数据同步消息，主服务器发送同步消息，把主服务器数据持久化，将rdb文件发送给从服务器，从服务器读取rdb文件。
   * 每次主服务器进行**写操作**后，和从服务器进行数据同步。

4. 薪火相传：主服务器只管理一台从服务器，由该从服务器管理其他从服务器。

5. 反客为主：当master宕机后，后面的slave可以立刻升为master。slaveof no one可以使从机变为主机。

6. 哨兵模式（sentinel）：能够后台监控主机是否故障，发生故障则根据投票数自动将从库变为主库。如果旧的主服务器重新启动，则变成从服务器。

   投票选择条件：选择优先级最小的、选择偏移量最大的、选择runid最小的从服务器。

   ```shell
   # mymaster 为监控对象起的服务器名称，1为至少多少个哨兵同意迁移的数量
   sentinel monitor mymaster 127.0.0.1 6379 1
   # 启动哨兵服务
   sudo redis-sentinel sentinel.conf
   ```

#### 七、Redis集群

1. Redis采用无中心化集群配置，实现了对Redis的水平扩容。
2. 一个集群中至少有三个主节点，分配原则尽量保证每个主数据库运行在不同的IP地址上，每个从库和主库不在一个IP地址上。
3. 在集群中可以通过{}来定义组的概念，从而使key中{}相同内容的键值对放到同一个slot中。

#### 八、Redis应用问题

1. **缓存穿透**：假如发送的请求传进来的key是不存在Redis中的，那么就查不到缓存，查不到缓存就会去数据库查询。假如有大量这样的请求，这些请求像“穿透”了缓存一样直接打在数据库上，这种现象就叫做缓存穿透。

   ![img](https://pic2.zhimg.com/80/v2-ba08c0076931750ec07a0a3411ec3cb9_1440w.jpg)

   解决方案：

   * **把无效的Key存进Redis中**：如果Redis查不到数据，数据库也查不到，我们把这个Key值保存进Redis，设置value="null"，当下次再通过这个Key查询时就不需要再查询数据库。这种处理方式肯定是有问题的，假如传进来的这个不存在的Key值每次都是随机的，那存进Redis也没有意义。
   * **设置可访问名单**：使用bitmaps类型定义一个可访问名单。
   * **使用布隆过滤器**：布隆过滤器的作用是某个 key 不存在，那么就一定不存在，它说某个 key 存在，那么很大可能是存在(存在一定的误判率)。于是我们可以在缓存之前再加一层布隆过滤器，在查询的时候先去布隆过滤器查询 key 是否存在，如果不存在就直接返回。
   * **进行实时监控**：设置黑名单。

2. **缓存击穿**：缓存击穿是一个热点的Key，有大并发集中对其进行访问，突然间这个Key失效了，导致大并发全部打在数据库上，导致数据库压力剧增。这种现象就叫做缓存击穿。

   解决方案：

   * **预先设置热门数据**：将一些热门数据提前存入redis里面。

   * 对于热点的key可以设置永不过期的key。
   * **使用互斥锁**：如果缓存失效的情况，只有拿到锁才可以查询数据库，降低了在同一时刻打在数据库上的请求，防止数据库打死，当然这样会导致系统的性能变差。

3. **缓存雪崩**：当某一个时刻出现大规模的缓存失效的情况，那么就会导致大量的请求直接打在数据库上面，导致数据库压力巨大，如果在高并发的情况下，可能瞬间就会导致数据库宕机。这时候如果运维马上又重启数据库，马上又会有新的流量把数据库打死。

   解决方案：

   * **构建多级缓存架构**：nginx缓存+redis缓存+其他缓存；
   * **使用锁或队列**：不适用高并发情况；
   * **设置过期标志更新缓存**：记录缓存数据是否过期，若过期则通知另外线程区更新缓存；
   * **将缓存失效时间分散**：在原有的失效时间上加上一个随机值，比如1-5分钟随机。
   * **使用熔断机制**：当流量到达一定的阈值时，就直接返回“系统拥挤”之类的提示，防止过多的请求打在数据库上。

4. 三种问题的区别：缓存穿透是查询key不在缓存中，缓存击穿是热点key失效，缓存雪崩是大量key失效。

