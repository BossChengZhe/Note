## MySQL数据库

#### 一、MySQL基础知识

1. 停止和启动mysql服务：

   ```powershell
   net stop mysql
   net start mysql
   ```

2. MySQL服务登录：

   ```powershell
   mysql -h localhost -P 3306 -u root -p
   ```

3. MySQL常用命令：

   * **USE 数据库名 : **

     选择要操作的Mysql数据库，使用该命令后所有Mysql命令都只针对该数据库;

   * **SHOW DATABASES:**
     列出 MySQL 数据库管理系统的数据库列表；

   * **SHOW TABLES:**
     显示指定数据库的所有表，使用该命令前需要使用 use 命令来选择要操作的数据库；

   * **DESC 表名**：

     查看数据库表的各种属性；

   * **SELECT DATABASE()**：

     显示当前使用的数据库。

4. 数据库的创建与删除：

   ```sql
   CREATE DATABASE 数据库名;
   DROP DATABASE 数据库名;
   ```

5. 数据类型：

   * 数值类型：

     | 类型         | 大小                                     | 范围（有符号）                                               | 范围（无符号）                                               | 用途            |
     | :----------- | :--------------------------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- | :-------------- |
     | TINYINT      | 1 byte                                   | (-128，127)                                                  | (0，255)                                                     | 小整数值        |
     | SMALLINT     | 2 bytes                                  | (-32 768，32 767)                                            | (0，65 535)                                                  | 大整数值        |
     | MEDIUMINT    | 3 bytes                                  | (-8 388 608，8 388 607)                                      | (0，16 777 215)                                              | 大整数值        |
     | INT或INTEGER | 4 bytes                                  | (-2 147 483 648，2 147 483 647)                              | (0，4 294 967 295)                                           | 大整数值        |
     | BIGINT       | 8 bytes                                  | (-9,223,372,036,854,775,808，9 223 372 036 854 775 807)      | (0，18 446 744 073 709 551 615)                              | 极大整数值      |
     | FLOAT        | 4 bytes                                  | (-3.402 823 466 E+38，-1.175 494 351 E-38)，0，(1.175 494 351 E-38，3.402 823 466 351 E+38) | 0，(1.175 494 351 E-38，3.402 823 466 E+38)                  | 单精度 浮点数值 |
     | DOUBLE       | 8 bytes                                  | (-1.797 693 134 862 315 7 E+308，-2.225 073 858 507 201 4 E-308)，0，(2.225 073 858 507 201 4 E-308，1.797 693 134 862 315 7 E+308) | 0，(2.225 073 858 507 201 4 E-308，1.797 693 134 862 315 7 E+308) | 双精度 浮点数值 |
     | DECIMAL      | 对DECIMAL(M,D) ，如果M>D，为M+2否则为D+2 | 依赖于M和D的值                                               | 依赖于M和D的值                                               | 小数值          |

   * 时间类型：

     | 类型      | 大小 ( bytes) | 范围                                                         | 格式                | 用途                     |
     | :-------- | :------------ | :----------------------------------------------------------- | :------------------ | :----------------------- |
     | DATE      | 3             | 1000-01-01/9999-12-31                                        | YYYY-MM-DD          | 日期值                   |
     | TIME      | 3             | '-838:59:59'/'838:59:59'                                     | HH:MM:SS            | 时间值或持续时间         |
     | YEAR      | 1             | 1901/2155                                                    | YYYY                | 年份值                   |
     | DATETIME  | 8             | 1000-01-01 00:00:00/9999-12-31 23:59:59                      | YYYY-MM-DD HH:MM:SS | 混合日期和时间值         |
     | TIMESTAMP | 4             | 1970-01-01 00:00:00/2038结束时间是第 **2147483647** 秒，北京时间 **2038-1-19 11:14:07**，格林尼治时间 2038年1月19日 凌晨 03:14:07 | YYYYMMDD HHMMSS     | 混合日期和时间值，时间戳 |

   * 字符串类型：char(n) 和 varchar(n) 中括号中 n 代表字符的个数，并不代表字节个数

     | 类型       | 大小                  | 用途                            |
     | :--------- | :-------------------- | :------------------------------ |
     | CHAR       | 0-255 bytes           | 定长字符串                      |
     | VARCHAR    | 0-65535 bytes         | 变长字符串                      |
     | TINYBLOB   | 0-255 bytes           | 不超过 255 个字符的二进制字符串 |
     | TINYTEXT   | 0-255 bytes           | 短文本字符串                    |
     | BLOB       | 0-65 535 bytes        | 二进制形式的长文本数据          |
     | TEXT       | 0-65 535 bytes        | 长文本数据                      |
     | MEDIUMBLOB | 0-16 777 215 bytes    | 二进制形式的中等长度文本数据    |
     | MEDIUMTEXT | 0-16 777 215 bytes    | 中等长度文本数据                |
     | LONGBLOB   | 0-4 294 967 295 bytes | 二进制形式的极大文本数据        |
     | LONGTEXT   | 0-4 294 967 295 bytes | 极大文本数据                    |

6. 创建和删除表：

   ```mysql
   CREATE TABLE IF NOT EXISTS `runoob_tbl`(
      `runoob_id` INT UNSIGNED AUTO_INCREMENT, # AUTO_INCREMENT定义列为自增的属性，一般用于主键，数值会自动加1。
      `runoob_title` VARCHAR(100) NOT NULL,
      `runoob_author` VARCHAR(40) NOT NULL,
      `submission_date` DATE,
      PRIMARY KEY ( `runoob_id` ) # PRIMARY KEY关键字用于定义列为主键。 您可以使用多列来定义主键，列间以逗号分隔。
   )ENGINE=InnoDB DEFAULT CHARSET=utf8; # ENGINE 设置存储引擎，CHARSET 设置编码。
   
   DROP TABLE `runoob_tbl`;
   ```

7. 数据插入：

   ```mysql
   INSERT INTO table_name ( field1, field2,...fieldN )
                          VALUES
                          ( value1, value2,...valueN );
   ```

8. 数据删除：

   ```mysql
   DELETE FROM table_name [WHERE Clause]
   ```

9. 数据更新：

   ```mysql
   UPDATE table_name SET field1=new-value1, field2=new-value2
   [WHERE Clause];
   ```

10. mysql "+"的作用：作为运算符使用，如果一方为数值字符型，则将字符型数值转换成数值型做加法运算，否则将该字符型值转为0。

#### 二、数据库查询

1. 模糊查询：

   * LIKE：一般和通配符搭配使用，%指任意多个字符，包含0个字符，_指任意单个字符，转义字符后面可以用ESCAPE指定。

     ```mysql
     SELECT field1, field2,...fieldN 
     FROM table_name
     WHERE field1 LIKE condition1 [AND [OR]] filed2 = 'somevalue'
     ```

   * BETWEEN AND：在两个顺序值中间的查找范围；

   * IN：判断某字段的值是否属于in列表中的某一项；

   * IS NULL：判断某字段是否为空。

     ```mysql
     SELECT
       last_name,
       commission_pct
     FROM
       employees
     WHERE commission_pct IS NULL;
     ```

2. UNION操作符：用于连接两个以上的 SELECT 语句的结果组合到一个结果集合中。多个 SELECT 语句会删除重复的数据。

   * **UNION 语句**：用于将不同表中相同列中查询的数据展示出来；（不包括重复数据）

   * **UNION ALL 语句**：用于将不同表中相同列中查询的数据展示出来；（包括重复数据）

   ```mysql
   SELECT expression1, expression2, ... expression_n
   FROM tables
   [WHERE conditions]
   UNION [ALL | DISTINCT]
   SELECT expression1, expression2, ... expression_n
   FROM tables
   [WHERE conditions];
   ```

3. ORDER BY：将查询数据排序后再返回数据。

   ```mysql
   SELECT field1, field2,...fieldN FROM table_name1, table_name2...
   ORDER BY field1 [ASC [DESC][默认 ASC]], [field2...] [ASC [DESC][默认 ASC]]
   ```

   - 你可以使用任何字段来作为排序的条件，从而返回排序后的查询结果；
   - 你可以设定多个字段来排序；
   - 你可以使用 ASC 或 DESC 关键字来设置查询结果是按升序或降序排列。 默认情况下，它是按升序排列；
   - ORDER BY语句一般放到最后，limit除外。

4. 函数使用：

   * 字符函数：

     * LENGTH()：获取参数值的字节个数（中文字符在UTF8中占据3个字节，GBK2个字节）；
     * CONCAT(s1,s2...sn)：字符串 s1,s2 等多个字符串合并为一个字符串；
     * SUBSTR(s, start, length)：从字符串 s 的 start 位置截取长度为 length 的子字符串（索引从1开始）；
     * TRIM(s)：去掉字符串 s 开始和结尾处的空格；
     * REPLACE(s,s1,s2)：将字符串 s2 替代字符串 s 中的字符串 s1。

   * 数学函数：

     * ROUND(x)：四舍五入，返回离 x 最近的整数；
     * CEIL(x)：返回大于或等于 x 的最小整数；
     * FLOOR(x)： 返回小于或等于 x 的最大整数。

   * 日期函数：

      * NOW()：返回当前日期和时间；

      * CURRENT_DATE()： 返回当前日期；

      * CURRENT_TIME()： 返回当前时间；

      * STR_TO_DATE(string, format_mask)：将字符串转变为日期；

        ```mysql
        	
        SELECT STR_TO_DATE("August 10 2017", "%M %d %Y");
        -> 2017-08-10
        ```

      * DATE_FORMAT(d,f)：按表达式 f的要求显示日期 d；

        ```mysql
        SELECT DATE_FORMAT('2011-11-11 11:11:11','%Y-%m-%d %r')
        -> 2011-11-11 11:11:11 AM
        ```

   * 流程控制函数：

     * IF(expr,v1,v2)：如果表达式 expr 成立，返回结果 v1；否则，返回结果 v2；

     * IFNULL(v1,v2)：如果 v1 的值不为 NULL，则返回 v1，否则返回 v2；

     * CASE函数：CASE 表示函数开始，END 表示函数结束，等同于switch case结构。

       ```mysql
       SELECT CASE 
       　　WHEN 1 > 0
       　　THEN '1 > 0'
       　　WHEN 2 > 0
       　　THEN '2 > 0'
       　　ELSE '3 > 0'
       　　END
       ```

   * 分组函数：SUM求和，AVG求均值，MIN最小值，MAX最大值，COUNT个数，分组函数都忽略NULL值。

5. 分组查询GROUP BY：根据一个或多个列对结果集进行分组。

   ```mysql
   SELECT column_name, function(column_name)
   FROM table_name
   WHERE column_name operator value
   GROUP BY column_name;
   ```

6. MySQL查询顺序：

   ```mysql
   Select
   from
   join on
   where
   group by
   having
   order by
   limit
   ```

7. 一个表只能有一个自增长列，且必须为一个key，只能支持数值型。

8. mysql不支持全连接full join。

#### 三、事务处理机制

1. 事务：一条或多条sql语句组成一个执行单位，一组sql语句要么都执行要么都不执行。

2. 数据库事务具备四大特性(ACID)：

   * 原子性：是指事务是一个不可分割的最小单位，执行的事务，要么全部成功，要么回滚到执行事务之前的状态。
   * 一致性：事务执行前后的数据，必须保持一致，即使数据从一个一致性状态变换到另一个一致性状态。
   * 隔离性：一个事务不受其他事务的干扰，多个事务相互隔离，避免同时对同一数据做操作。
   * 持久性：事务一旦被提交（commit / rollback ），数据的改变是永久性的。

3. 事务操作：

   * 开启事务

   ```mysql
   set autocommit = 0;
   begin;
   start transaction; # 可以省略
   ```

   * 编写一组逻辑sql语句（支持增删查改）：

     ```mysql
     savepoint 回滚点名; # 设置回滚点
     ```

   * 结束事务

     ```mysql
     commit; # 提交
     rollback; # 回滚
     rollback to 回滚点名; # 回滚指定地方
     ```

4. 并发问题：

   * 脏读：一个事务读取了其他事务还未提交的数据（更新的数据）；
   * 不可重复读：一个事务多次读取结果不一样；
   * 幻读：一个事务读取了其他事务还未提交的数据（插入或删除数据）。

5. 事务隔离级别：

   * 读未提交（read uncommitted）
   * 读已提交（read committed）
   * 可重复读（repeatable read）：MySQL默认
   * 串行化（serializable）

6. 事务隔离级别查看与设置：@@是系统变量，@是用户或局部变量

   ```mysql
   select @@transaction_isolation; # 默认为当前会话的下个事务
   select @@session.transaction_isolation; # 当前会话
   select @@global.transaction_isolation; # 全局
   
   set session transaction isolation level read uncommitted;
   set global transaction isolation level read uncommitted;
   ```

7. 参考链接：

   * [浅谈mysql事务](https://zhuanlan.zhihu.com/p/52677680)
   * [mysql的事务四个特性以及事务的四个隔离级别](https://www.cnblogs.com/limuzi1994/p/9684083.html)