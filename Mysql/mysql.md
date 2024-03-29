###  Mysql基础

数据库

1. 数据库的好处

   - 持久化数据到本地
   - 结构化查询

2. 数据库常见概念

   - DB：数据库，存储数据的容器
   - DBMS：数据库管理系统，创建和管理DB
   - SQL：结构化查询语言，用于数据库通讯的语言，不是某个数据库软件特有的，是几乎所有主流的数据库软件通用的语言

3. 数据库存储的特点

   - 数据存储子表中，表放入库中
   - 数据库可以有多张表
   - 表中有同一个或者多个列，又称为是“字段”
   - 表中每一行，表示一个数据

4. mysql启动与停止

   ```bash
   net start mysql
   net stop mysql
   ```

#### Mysql常见命令

```mysql
# 查看当前使用的数据库
show database;
# 打开指定数据库
use database_name;
# 查看当前库中所有表
show tables;
# 查看其他库中所有表
show tables from database_name;
# 创建表
create table 表明 (
    列名 类型
    列名 类型
)
# 查看表结构
desc 表明;
```

#### Mysql查询

##### 基础查询

```Mysql
# 查询单个字段
SELECT last_name FROM employees;

# 查询多个字段
SELECT salary, last_name, email FROM employees;

# 查询所有
SELECT * FROM employees;

# 起别名(宏定义)
SELECT last_name AS 姓氏, first_name AS 名字 FROM employees;

# 去重
SELECT DISTINCT department_id FROM employees;
```

##### 条件查询

```mysql
# 条件查询
/*
SELECT
	查询列表
FROM 
	表名
WHERE 
	筛选条件;
	
筛选分类：
	1. 条件表达式 < > = != <> >= <=
	2. 逻辑表达式 && and || or ! not
	3. 模糊查询 like、 in、 between and、 is null 
*/
# 查询工资大于12000的员工
SELECT
	*
FROM
	employees
WHERE
	salary > 12000;
# 部门id不等于90
SELECT
	last_name,
	department_id
FROM
	employees
WHERE
	department_id <> 90;

# 查询工资在10000~20000之间的员工
SELECT
	last_name,
	salary,
	commission_pct
FROM
	employees
WHERE
	salary >= 10000 AND salary <= 20000;

# 查找名字中带有字母a的员工条目
/*
1. LIKE 一般个通配符使用
	% 任意多个字符
	_ 任意一个字符
*/
SELECT
	*
FROM
	employees
WHERE
	last_name LIKE '%a%';

SELECT
	*
FROM
	employees
WHERE
	last_name LIKE '_$_%' ESCAPE '$';       # ESCAPE是说在'$'符号之后的'_'不作为通配符

# 模糊查询
SELECT
	*
FROM
	employees
WHERE
	employee_id BETWEEN 100 AND 120;

/*
in：判断某字段是否属于in列表中的一项
	1. 使得语句简洁
	2. in列表中的类型必须一致或者兼容
	3. 
*/
SELECT
	last_name,
	job_id
FROM
	employees
WHERE
	job_id IN ('IT_PROT', 'AD_VP', 'AD_PRES');

/*
is null 查询有奖金员工名和奖金率
<> = 不能用于判断null值
*/
SELECT
	last_name,
	commission_pct
FROM
	employees
WHERE
	commission_pct IS NOT NULL;

# 安全等于<=>
# 即可以判断null值，又可以判断普通数值 
SELECT
	last_name,
	commission_pct
FROM
	employees
WHERE
	commission_pct <=> NULL;
```

##### 排序查询

```mysql
# order by 排序列表 [asc | desc]（升序或者是降序）

# 员工工资信息，从高到低排序
SELECT * FROM employees ORDER BY salary DESC; # 降序，ASC升序，不写默认升序
# 查询部门编号>=90的员工信息，按照入职的前后进行
SELECT 
	*
FROM 
	employees
WHERE
	department_id >= 90 
ORDER BY
	hiredate DESC;

# 按照年薪排序显示员工信息
SELECT *, salary*12*(1+IFNULL(commission_pct,0)) AS 年薪
FROM employees
ORDER BY salary*12*(1+IFNULL(commission_pct,0)) DESC; # 可用别名可用表达式

# 复合字段排序
SELECT *
FROM employees
ORDER BY salary ASC, employee_id DESC;
```

#### Mysql常见函数

##### 单行函数

###### 字符函数

```mysql
# length 获取参数值的字节个数
SELECT LENGTH('jhon')

# concat 拼接字符串
SELECT CONCAT(first_name,' ', last_name) FROM employees;

# upper lower
SELECT UPPER("lower");
SELECT LOWER("UPPER");

# substr截取字符串中子串，substring
SELECT SUBSTR('李莫愁爱上了XXX', 7);
SELECT SUBSTR('李莫愁爱上了XXX', 7, 2);

# instr：返回子串第一次出现的索引
SELECT INSTR('杨不悔爱上了殷六侠','殷六侠') ;

# trim：去除左右空格，Ltrim、Rtrim分别去除左右空格
SELECT TRIM(' barbar ');
SELECT TRIM('a' from 'aaaaaaaaaaaaaaabarbar aaaaaaaaaaaaaaaaaaaaaaaaaaaa');

# LPAD 置顶字符实现左填充长度 RPAD
SELECT RPAD('test',14,'a');

# replace
SELECT REPLACE('test test test test aaaaaaaaa','test','fuck');
```

###### 数学函数

```mysql
# round 四舍五入
SELECT ROUND(-1.55)
SELECT ROUND(-1.557, 2)

#ceil
SELECT CEIL(-1.02);

#floor 向下取整
SELECT FLOOR(-1.02);

# truncate 截断
SELECT TRUNCATE(1.65,1);

# mod 取余
SELECT MOD(10,-3);
```

###### 日期函数

```mysql
# now 返回当前系统日期和时间
SELECT NOW();

#curdata 返回当前系统日期，不包含时间
SELECT CURDATE();

#curtime 返回时间
SELECT CURTIME();

# YEAR MOUTH 返回指定的部分年、月、日、小时、分钟
SELECT HOUR(NOW());
SELECT Year(NOW());

# 日期处理函数
SELECT STR_TO_DATE('9-12-1899','%m-%d-%Y');
SELECT DATE_FORMAT('2018/6/6','%Y年%m月%d日')
```

###### 其他函数

```mysql
SELECT VERSION();
SELECT DATABASE();
SELECT USER();
```

###### 流程控制函数

```mysql
# if 
SELECT IF(10<5,'大','小')

# case : switch case
# 查询员工工资，
SELECT salary, department_id,
CASE department_id
WHEN 30 THEN salary*1.1
WHEN 40 THEN salary*1.2
WHEN 50 THEN salary*1.3
ELSE salary
END AS 新工资
FROM employees;
# 类似多重if
SELECT salary, 
CASE 
	WHEN salary>20000 THEN
		'A'
	WHEN salary>15000 THEN
		'B'
	WHEN salary>15000 THEN
		'C'
	ELSE 'D'
END AS level 
FROM employees;

```

##### 分组函数

###### 简单使用

```mysql
SELECT SUM(salary) FROM employees;
SELECT AVG(salary) FROM employees;
SELECT MIN(salary) FROM employees;
SELECT MAX(salary) FROM employees;
SELECT COUNT(salary) FROM employees;

# 为每一个数据加入常量，统计数据规模
SELECT COUNT('test') FROM employees;
```

分组查询

```mysql
# 简单的分组查询
SELECT MAX(salary), job_id
FROM employees
GROUP BY job_id 
ORDER BY MAX(salary);

# 邮箱中带有a字母的部门平均工资
SELECT AVG(salary), department_id
FROM employees
WHERE email like '%a%'
GROUP BY department_id;

# 有奖金的每个领导手下员工的最高工资
SELECT MAX(salary), manager_id
FROM employees
WHERE commission_pct IS NOT NULL
GROUP BY manager_id;

# 复杂筛选条件
# 查询部门员工数大于2的
SELECT COUNT(*), department_id
FROM employees
GROUP BY department_id
HAVING COUNT(*) > 2;          # HAVING  配合 GROUP BY 使用，对分组后的数据进行限制,可以使用聚合函数。

# 查询每个工种有奖金的员工的最高工资>12000的工种编号和最高工资
SELECT job_id, MAX(salary)
FROM employees
WHERE commission_pct IS NOT NULL        # 在原始表中有的，就可以放在group by 前
GROUP BY job_id
HAVING MAX(salary) > 12000;

# 查询领导编号>102的每个领导手下的最低工资>5000的领导编号是哪个，以及其最低工资
SELECT MIN(salary), manager_id
FROM employees
WHERE manager_id > 102
GROUP BY manager_id
HAVING MIN(salary) > 5000;

# 按员工姓名的长度分组，查询每一组的员工个数，筛选员工个数>5的有哪些
SELECT COUNT(*), LENGTH(last_name) name_len
FROM employees
GROUP BY name_len
HAVING COUNT(*) > 5;

# 按多个字段分组
# 查询每个部门每个工种的员工的平均工资
SELECT AVG(salary), department_id, job_id
FROM employees
GROUP BY department_id, job_id
ORDER BY AVG(salary) DESC;
```

###### 连接查询

```mysql
SELECT NAME,boyName FROM boys,beauty
WHERE beauty.boyfriend_id = boys.id;
```

#### 连接查询

##### sql92语法

- 等值连接

```mysql
# 女人的对应的男朋友
SELECT NAME,boyName FROM boys,beauty
WHERE beauty.boyfriend_id = boys.id;

# 员工名与其所属的部门名
SELECT last_name, department_name
FROM employees, departments
WHERE employees.department_id = departments.department_id;

#查询有奖金的员工名、部门名
SELECT last_name,department_name
FROM departments, employees
WHERE commission_pct IS NOT NULL
		  and departments.department_id = employees.department_id;

# 查询每个城市有多少个部门
SELECT COUNT(*) nums, city
FROM departments d, locations l
WHERE d.location_id = l.location_id
GROUP BY city;

# 每个职业有多少人
SELECT job_title, COUNT(*) num
FROM employees, jobs
WHERE employees.job_id = jobs.job_id
GROUP BY employees.job_id
ORDER BY num DESC;

# 每名员工所在部门和城市
SELECT last_name, department_name, locations.city
FROM employees, departments, locations
WHERE employees.department_id = departments.department_id and
	locations.location_id = departments.location_id;
```

- ###### 非等值连接

```mysql
# 查询员工的工资和工资级别
SELECT last_name, salary, grade_level
FROM employees, job_grades
WHERE salary BETWEEN lowest_sal and highest_sal
ORDER BY salary;
```

- 自连接

```mysql
# 查询员工以及其领导(在employees表中)
SELECT e.employee_id, e.last_name, m.employee_id, m.last_name
FROM employees e, employees m
WHERE e.manager_id = m.employee_id
ORDER BY m.employee_id, e.employee_id;
```

##### sql99语法

###### 内连接

```mysql
select查询列表
from 表1 别名 [连接类型]
join 表2 别名
on 连接条件
[where 筛选条件]
[group by 分组]
[having 筛选条件]
[order by 排序列表]

分类：内连接外连接
内连接 : inner
外连接
	左外（*） ：left [outer]
	右外（*）： right [outer]
	全外： full [outer]
交叉连接： cross
```

- 非等值连接

```mysql
# 查询员工的工资级别
SELECT salary, grade_level
FROM employees e
JOIN job_grades j
ON salary BETWEEN lowest_sal AND highest_sal
ORDER BY salary DESC;

# 查询工资级别的个数＞20的个数，并且按工资级别降序
SELECT COUNT(*), grade_level
FROM employees e
JOIN job_grades j
ON salary BETWEEN lowest_sal AND highest_sal
GROUP BY grade_level
HAVING COUNT(*) > 20
ORDER BY grade_level;
```

- 自连接

```mysql
# 查询员工姓名、上级的名字
SELECT e.last_name, m.last_name
FROM employees e
JOIN employees m
ON e.manager_id = m.employee_id;
```

###### 外连接

1. 外连接的查询结果为主表中的所有记录

   如果从表中有和它匹配的，则显示匹配的值如果从表中没有和它匹配的，则显示null

   外连接查询结果＝内连接结果＋主表中有而从表没有的记录

2. 左外连接，left join左边的是主表右外连接，right join右边的是主表

3. 左外和右外交换两个表的顺序，可以实现同样的效果

```mysql
# 查询男朋友不在boys表中的女生
SELECT b.`name`, bo.`boyName`
FROM beauty b                        # 左外连接，主表是LEFT JOIN 左边，即beauty
LEFT JOIN boys bo 
ON b.boyfriend_id = bo.`id`
WHERE bo.boyName IS NULL;

# 查询部门没有人
SELECT d.*, employees.employee_id
FROM departments d 
LEFT JOIN employees
ON d.department_id = employees.department_id
WHERE employee_id IS NULL;
```

###### 交叉连接

```mysql
# 使用sql99的标准实现笛卡尔乘积
SELECT b.*, bo.*
FROM beauty b
CROSS JOIN boys bo
```

#### 子查询

按子查询出现的位置：

- select后面：仅仅支持标量子查询 
- from后面：支持表子查询 
- where或having后面： 标量子查询、列子查询、行子查询
- exists后面（相关子查询）表子查询 

按结果集的行列数不同：

- 标量子查询（结果集只有一行一列）
- 列子查询（结果集只有一列多行）
- 行子查询（结果集有一行多列）
- 表子查询（结果集一般为多行多列）

###### where后

```mysql
# where或having后面
/*
特点：
1子查询放在小括号内
2子查询一般放在条件的右侧
3标量子查询，一般搭配着单行操作符使用 > < >= <= <>
列子查询，一般搭配着多行操作符使用in, any/some, all
*/
# 标量子查询：查询工资比Abel高的员工信息
SELECT *
FROM employees
WHERE salary > (
	SELECT salary
	FROM employees
	WHERE last_name = 'Abel'
);
# 返回job_id与141号员工相同， salary比143号员工多的员工姓名， job_id和工资
SELECT * 
FROM employees
WHERE salary > (
	SELECT salary 
	FROM employees
	WHERE employee_id = 143
) AND job_id = (
	SELECT job_id 
	FROM employees
	WHERE employee_id = 141
);
# 返回公司工资最少的员工的last_name，job_id和salary
SELECT last_name, job_id, salary
FROM employees
WHERE salary = (
	SELECT MIN(salary)
	FROM employees
);
# 查询最低工资大于50号部门最低工资的部门id和其最低工资
SELECT department_id, MIN(salary)
FROM employees
GROUP BY department_id
HAVING MIN(salary) > (
	SELECT MIN(salary)
	FROM employees
	WHERE department_id = 50
);

# 列子查询
SELECT last_name
FROM employees
WHERE employees.department_id in (
	SELECT DISTINCT department_id
	FROM departments
	WHERE location_id IN (1400, 1700)
);
```

###### select后

​	仅支持标量子查询

```mysql
# 查询每个部门的人数
SELECT d.*, (
	SELECT COUNT(*)
	FROM employees
	WHERE employees.department_id = d.department_id
) nums
FROM departments d;
```

###### from后

```mysql
# 查询部门平均工资水平(查询结果当成一张表)
SELECT avg_salary.* , job_grades.grade_level
FROM (
	SELECT AVG(salary) ag, department_id
	FROM employees
	GROUP BY department_id
) AS avg_salary
INNER JOIN job_grades
ON avg_salary.ag BETWEEN lowest_sal AND highest_sal;
```

###### exists后

```mysql
# exists([完整的查询语句]) 相关子查询
SELECT department_name
FROM departments d
WHERE EXISTS(
	SELECT *
	FROM employees e
	WHERE d.department_id = e.department_id
);
```

#### 分页查询

```mysql
#  查询前五条员工信息
SELECT * FROM employees LIMIT 1, 15;
SELECT * FROM employees LIMIT 11, 15;
```

#### 联合查询

- 要查询的表来自于多个表，且表之间没有连接关系
- 查询顺序和字段个数相等
- union会默认去重，需要时UNION ALL

```mysql
# 将多条语句的结果合并成一个
SELECT
	* 
FROM
	employees 
WHERE
	email LIKE '%a%' UNION
SELECT
	* 
FROM
	employees 
WHERE
	department_id > 90;
```

#### 插入语句

```mysql
/*
INSERT INTO [table_name] VALUES(value1，value2,...)
列的顺序可以调换
列数和值的个数必须一致
可以省略列名，默认所有列，且列的顺序和表中列的顺讯相同
*/
# 第一种方式
# 可支持多行插入，支持子查询
INSERT INTO beauty( id, `name`, sex, borndate, phone, photo, boyfriend_id ) VALUES(13, '唐艺昕', '女', '1990-4-23', '18988889999', NULL, 20)
# 第二种方式
# 
INSERT INTO beauty
SET id = 14, `name`='刘涛',phone = '999';
```

#### 修改语句

```mysql
# 修改beauty表中姓唐的女神的电话为13899888899
UPDATE beauty
SET phone = '13899888899'
WHERE `name` LIKE '唐%';
# 修改boys表中id号为2的名字为飞哥，usercp为1800
UPDATE boys
SET boyName = '飞哥', userCP = 1800
WHERE id = 2;

-- 修改多个表的类别
# 修改张无忌女朋友的手机号
UPDATE boys bo
INNER JOIN beauty b on bo.`id` = b.boyfriend_id
SET phone = '13156879012'
WHERE bo.boyName = '张无忌';
```

删除语句

```mysql
-- 单表删除
# 删除beauty表中电话号码长度小于5的条目
DELETE FROM beauty
WHERE LENGTH(beauty.phone) < 5;

-- 多表删除
# 删除beauty中张无忌女朋友的信息
DELETE b
FROM beauty b
INNER JOIN boys bo
ON b.boyfriend_id = bo.id
WHERE bo.boyName = '张无忌';
# 删除多表信息
DELETE b, bo
FROM boys bo INNER JOIN beauty b
ON b.boyfriend_id = bo.id
WHERE bo.boyName = '黄晓明';

# truncate语句：清空表
# 2．truncate删除，效率高一丢丢
# 3．假如要删除的表中有自增长列，如果用delete删除后，再插入数据，自增长列的值从断点开始，而truncate删除后，再插入数据，自增长列的值从1开始。
# 4.truncate删除没有返回值， delete删除有返回值1
# 5.truncate删除不能回滚， delete删除可以回滚
TRUNCATE TABLE boys;
```

#### 数据定义语言DDL

##### 库的管理

```mysql
# 库的创建
CREATE DATABASE books;
CREATE DATABASE IF NOT EXISTS books; # 如果存在则不创建

# 库的修改
# 无方法
# 更改库的字符集
ALTER DATABASE books CHARACTER SET gbk;

# 删除库
DROP DATABASE IF EXISTS books;
```

##### 表的管理

```mysql
CREATE TABLE table_name (
	列名 列的类型[约束]
)

# 创建表
CREATE TABLE book (
	id INT,
	bName VARCHAR(20),
	price DOUBLE,
	authorID INT,
	publishDate DATETIME
);
CREATE TABLE author (
	id INT,
	author_name VARCHAR(20),
	nation VARCHAR(10)
);

# 表格修改
-- 修改列名
ALTER TABLE book CHANGE COLUMN publishDate pubDate DATETIME;

-- 修改列的类型或者是约束
ALTER TABLE book MODIFY COLUMN pubDate TIMESTAMP;

-- 添加列
ALTER TABLE author ADD COLUMN annual DOUBLE;

-- 删除列
ALTER TABLE author DROP COLUMN annual;

-- 修改表名
ALTER TABLE author RENAME TO book_author;

-- 删除表
DROP TABLE book_author;

-- 复制表
CREATE TABLE copy_author LIKE author;   # 仅仅复制表的结构
CREATE TABLE copy_author SELECT * FROM author [WHERE nation = '中国'];   # 复制表的结构+数据，也可加条件筛选

```

#### 数据类型

- 数值型
- 字符型：
  - 较短的文本：char, varchar
  - 较长的文本：text, blob
  - 其他
    - binary、varbinary保存较短的二进制
    - enum用于保存枚举
    - set用于保存集合
- 日期型：
  - date：日期
  - time：只有时间
  - timestamp：范围较小，并且更能反应实际的日期和实际市区有关（属性和mysql版本和SQLMode的影响）
  - datetime：范围较大（8个字节）

#### 常见约束

1. NOT NULL：保证当前字段的值不能为空
2. DEFAULT：保证字段有默认值
3. PRIMARY：保证该字段的值拥有唯一性，不可为空
4. UNIQUE：保证字段值唯一，但是可以为空
5. CHECK：检查约束（mysql不支持）满足某种条件
6. FOREIGN KEY：外键，用于限制两个表的关系，保证该字段的值必须来自于主表的关联列的值。在外表添加外键约束，用于引用主表中某列的值

创建约束的时机：

- 列级约束：外键约束没有效果

- 表级约束：除了非空，默认其他都支持

```mysql
# 表级约束
CREATE TABLE stuinfo (
	id INT,
	stuname VARCHAR(20),
	gender char(1),
	seat INT,
	age INT,
	majorid INT
	
	CONSTRAINT pk PRIMARY KEY(id),
	CONSTRAINT uq UNIQUE(seat),
	CONSTRAINT ck CHECK(gender = '男' OR gender = '女'),
	CONSTRAINT fk_info_major FOREIGN KEY(majorid) REFERENCES major(id)
)

# 列级约束
CREATE TABLE stuinfo (
	id INT PRIMARY KEY,
	stuname VARCHAR(20) NOT NULL,
	gender char(1) CHECK(gender = '男' OR gender = '女'),
	seat INT UNIQUE,
	age INT DEFAULT 18,
	majorid INT
};
```

外键特点

1. 要求在从表设置外键关系
2. 从表前外键列的类型和主表的关联列的类型要求一致或兼容，名称无要求
3. 主表的关联列必须是一个key （一般是主键或唯—）
4. 插入数据时，先插入主表，再插入从表删除数据时，先删除从表，再删除主表

#### 标识列

1. 标识列一定和key(primary key、 unique)搭配
2. 每个表最多一个标识列
3. 标识列的类型只能是数值型
4. SET auto_increment_increment =3;更改自增步长

```mysql
# 按照默认规则自增(可设置步长，起始编号为1)
CREATE TABLE tab_id (
	id INT PRIMARY KEY AUTO_INCREMENT,
	`name` VARCHAR ( 20 ) NOT NULL 
);
INSERT INTO tab_id VALUES(NULL, 'John'), (NULL, 'Tom');
```

#### 事务

​	事务由单独单元的一个或多个SQL语句组成，在这个单元中，每个MySQL语句是相互依赖的。而整个单独单元作为一个不可分割的整体，如果单元中某条SQL语句一旦执行失败或产生错误，整个单元将会回滚。所有受到影响的数据将返回到事物开始以前的状态；如果单元中的所有SQL语句均执行成功，则事物被顺利执行。

1. 原子性：不可分割的工作单位
2. 一致性：从一个一致性状态变换到另外一个一致性状态
3. 隔离性：事务的隔离性是指一个事务的执行不能被其他事务干扰，即一个事务内部的操作及使用的数据对并发豹其他事务是隔离的，并发执行的各个事务之间不能互相干扰。
4. 持久性：持久性是指一个事务一旦被提交，它对数据库中数据的改变就是永久性的，接下来的其他操作和数据库故障不应该对其有任何影响

##### 创建

```mysql
-- 隐式的事务 insert、update、delete
-- 显式事务：明显的开启和结束的标记，必须先设置自动提交功能为禁用 set_autocommit = 0;
/*
步骤1：开启事务
set autocommit=0;
start transaction; 可选的
步骤2：编写事务中的sql语句（select insert update delete） 
语句1;
语句2;
步骤3：结束事务 commit；提交事务 rollback；回滚事务 
*/
SET autocommit = 0;               # 禁用自动提交
START TRANSACTION;                # 开始事务
UPDATE tab_id SET balance = 999 WHERE id =  1;
UPDATE tab_id SET balance = 9991 WHERE id = 2;
COMMIT;                           # 结束事务(提交)
[ROLLBACK;                        # 回滚]
 
# 事务中delete和truncate的区别
SET autocommit = 0;
START TRANSACTION;  
DELETE FROM account;
ROLLBACK;      # 无影响

SET autocommit = 0;
START TRANSACTION;  
TRUNCATE FROM account;
ROLLBACK;      # 清空表
```

##### 数据的隔离级别

​	对于同时运行的多个事务，当这些事务访问数据库中相同的数据时，如果没有采取必要的隔离机制，就会导致各种并发问题：

1. 脏读：对于两个事务$T_1$、 $T_2$， $T_1$读取了已经被$T_2$更新但还没有被提交的字段.之后，若$T_2$回滚，$T_1$读取的内容就是临时且无效的
2. 不可重复读：对于两个事务$T_1$、$T_2$， $T_1$读取了一个字段，然后$T_2$**更新**了该字段.之后，$T_1$再次读取同一个字段，值就不同了.
3. 幻读：对于两个事务$T_1$、$T_2$，$T_1$从一个表中读取了一个字段，然后$T_2$在该表中**插入**了一些新的行．之后，如果$T_1$再次读取同一个表，就会多出几行．

|              隔离级别              |                             描述                             |
| :--------------------------------: | :----------------------------------------------------------: |
| Read Uncommitted（读取未提交内容） | 在该隔离级别，所有事务都可以看到其他未提交事务的执行结果。本隔离级别很少用于实际应用，因为它的性能也不比其他级别好多少。读取未提交的数据，也被称之为脏读（Dirty Read）。 |
|   Read Committed（读取提交内容）   | 这是大多数数据库系统的默认隔离级别（但不是MySQL默认的）。它满足了隔离的简单定义：一个事务只能看见已经提交事务所做的改变。这种隔离级别 也支持所谓的不可重复读（Nonrepeatable Read），因为同一事务的其他实例在该实例处理其间可能会有新的commit，所以同一select可能返回不同结果。 |
|     Repeatable Read（可重读）      | 这是MySQL的默认事务隔离级别，它确保同一事务的多个实例在并发读取数据时，会看到同样的数据行。不过理论上，这会导致另一个棘手的问题：幻读 （Phantom Read）。简单的说，幻读指当用户读取某一范围的数据行时，另一个事务又在该范围内插入了新行，当用户再读取该范围的数据行时，会发现有新的“幻影” 行。InnoDB和Falcon存储引擎通过多版本并发控制（MVCC，Multiversion Concurrency Control）机制解决了该问题。 |
|      Serializable（可串行化）      | 这是最高的隔离级别，它通过强制事务排序，使之不可能相互冲突，从而解决幻读问题。简言之，它是在每个读的数据行上加上共享锁。在这个级别，可能导致大量的超时现象和锁竞争。 |

##### savepoint

```mysql
SET autocommit = 0;
START TRANSACTION;
DELETE FROM tab_id WHERE id = 1;
SAVEPOINT a;
DELETE FROM tab_id WHERE id = 2;
ROLLBACK TO a;
```

#### 视图

​	MySQL从5.0.1版本开始提供视图功能。一种虚拟存在的表，行和列的数据来自定义视图的查询中使用的表，并且是在使用视图时动态生成的，只保存了sql逻辑，不保存查询结果

- 重用sql语句
- 简化复杂的sql操作，不必知道它的查询细节
- 保护数据，提高安全性

```mysql
# 创建
# 查询姓名中包含a字符的员工名、部门名和工种信息
CREATE VIEW test   # 创建视图
AS
SELECT last_name, department_name, job_title, e.email
FROM employees e
JOIN departments d ON e.department_id = d.department_id
JOIN jobs j ON e.job_id = j.job_id;
# 查询姓名模式
SELECT
	* 
FROM
	test 
WHERE
	last_name LIKE '%a%';

# 修改
# 方式1
CREATE OR REPLACE VIEW test
AS
SELECT last_name, department_name, job_title
FROM employees e
JOIN departments d ON e.department_id = d.department_id
JOIN jobs j ON e.job_id = j.job_id;
# 方式2
ALTER VIEW test
AS
SELECT last_name, department_name, job_title
FROM employees e
JOIN departments d ON e.department_id = d.department_id
JOIN jobs j ON e.job_id = j.job_id;

# 删除视图
DROP VIEW test;

# 查看视图
SHOW CREATE VIEW test;

# 更新视图
# 插入
CREATE OR REPLACE VIEW  myv1
AS
SELECT last_name, email
FROM employees;
INSERT INTO myv1 VALUES("张无忌",'121226162@qq.com'); # 对于视图的更改会影响到原表格
# 修改
UPDATE myv1 SET last_name = '杰哥' WHERE last_name = '张无忌';
# 删除
DELETE FROM myv1 WHERE last_name = '杰哥';
```

视图的可更新性和视图中查询的定义有关系，以下类型的视图是不能更新的。

- 包含以下关键字的sgl语句:分组函数、distinct, group by 、having、 dnion或者union all
- 常量视图
- Select中包含子查询join
- from一个不能更新的视图
- .where子句的子查询引用了from子句中的表

#### 变量

- 系统变量

  1. 全局变量
     作用域；服务器每次启动将为所有的全局变量赋初始值，针对于所有的会话（连接）有效，但不能跨重启

  2. 会话变量
     当前会话有效

     ```mysql
     # 查看所有的系统变量
     SHOW GLOBAL|[SESSION] VARIABLES;
     # 查着满足条件的部分系统变量
     show GLOBAL|[SESSION] VARIABLES like '%char%';
     # 查看指定的某个系统变量的值
     show @@GLOBAL|[SESSION] VARIABLES;
     /*
     为某个系统变量赋值
     方式一：
     set globall [session]系统变量名=值；
     方式二：
     set @eglobal1 [session].系统变量名=值；注意：
     如果是全局级别，则需要加global，如果是会话级别，则需要加session，如果不写，则默认session
     */
     ```

- 自定义变量

  1. 用户变量
     针对于当前会话或者连接
     ```mysql
     # 声明初始化
     SET @用户变量名=值;
     SET @用户变量名:=值;
     SELECT @用户变量名:=值;
     # 赋值
     SET @用户变量名=值;
     SET @用户变量名:=值;
     SELECT @用户变量名:=值;
     SELECT 字段 INTO 变量名 FROM 表;
     # 查看
     SELECT @用户变量名;
     SET @count := 0;
     SELECT COUNT(*) INTO @count FROM employees;
     SELECT @count;
     ```
     
  2. 局部变量
     在定义他的begin end 中，且为第一句话
  
     ```mysql
     # 声明
     DECLARE 变量名 类型;
     DECLARE 变量名 类型 DEFAULT 值;
     # 赋值
     SET @用户变量名=值;
     SET @用户变量名:=值;
     SELECT @用户变量名:=值;
     SELECT 字段 INTO 变量名 FROM 表;
     # 查看
     SELECT @局部变量名;
     ```
  
  #### 存储过程
  
  一组预先编译好的sql语句的集合，理解成批处理语句
  1. 提高代码的重用性  
  2. 简化操作  
  3. 减少了编译次数并且减少了和数据库服务器的连接次数，提高了效率

```mysql
# 创建列表
CREATE PROCEDURE 存储过程名(参数列表)
BEGIN
	存储过程体(合法的SQL语句)
END
/*
1. 参数列表包含三部分
参数模式 参数名 参数类型 
举例：
IN stuname VARCHAR(20) 
参数模式：
IN: 该参数可以作为输入，也就是需要调用方传入值
OUT:该参数可以作为输出，改参数可以作为返回值
INOUT:该参数既可以作为输入又可以作为输出，也就是该参数既需要传入值，又可以返回值 
2. 如果存储过程体仅仅只有一句话，BEGIN END可以省略
存储过程体中的每条sQL语句的结尾要求必须加分号
存储过程的结尾可以使用DELIMITER重新设置
语法：
DELIMITER 结束标记 
DELIMITER $
*/

# 调用语法
CALL 存储过程名(参数列表);

# 无参数
DELIMITER $
CREATE PROCEDURE myp1()
BEGIN 
	INSERT INTO admin(username, `password`)
	VALUES
		('lili','2012'),
		('lii','20212'),
		('lli','20122'),
		('ili','20122'),
		('li','20312');
END $

# in模式参数存储过程
# 创建存储过程实现根据女神名，查询对应的男神信息
DELIMITER $
CREATE PROCEDURE myp2(IN beautyName VARCHAR(20))
BEGIN
	SELECT bo.*
	FROM boys bo
	RIGHT JOIN beauty b ON bo.id = b.boyfriend_id
	WHERE b.`name` = beautyName;
END $
CALL myp2('小昭');

# 根据女神名返回对应男神名称
DELIMITER $
CREATE PROCEDURE myp3(IN beautyName VARCHAR(20), OUT Boy_Name VARCHAR(20))
BEGIN
	SELECT bo.`boyName` INTO Boy_Name
	FROM boys bo
	inner JOIN beauty b ON bo.id = b.boyfriend_id
	WHERE b.`name` = beautyName;
END $
SET @Boyname$
CALL myp3('小昭', @Boyname)$
SELECT @Boyname;

# 删除存储过程
DROP PROCEDURE myp2;
```

#### 函数

一组预先编译好的sql语句的集合，理解成批处理语句
1. 提高代码的重用性  
2. 简化操作  
3. 减少了编译次数并且减少了和数据库服务器的连接次数，提高了效率

存储过程：可以有0个返回，也可以有多个返回，适合做批量插入、批量更新
函数：有且仅有1个返回，适合做处理数据后返回一个结果

```mysql
DELIMITER $
CREATE FUNCTION 函数名(参数列表) RETURNS 返回类型;
BEGIN
	函数体
END $

-- 调用语法
SELECT 函数名(参数列表)
# 返回当前部门人数
DELIMITER $
CREATE FUNCTION myf1() RETURNS INT
BEGIN
	DECLARE c INT DEFAULT 0;    # 局部变量
	SELECT COUNT(*) INTO c
	FROM employees;
	RETURN c;
END $
SELECT myf1()$       # 调用

# 根据员工名返回工资
DROP FUNCTION myf1;
DELIMITER $
CREATE FUNCTION myf2(emname VARCHAR(20)) RETURNS DOUBLE
BEGIN
	SET @sal=0; # 定义用户变量
	SELECT salary*12*(IFNULL(commission_pct,0) + 1) INTO @sal
	FROM employees e
	WHERE last_name = emname;
	RETURN @sal;
END $
SELECT myf2('Kochhar')$

# 查看函数
SHOW CREATE FUNCTION myf2;
```

#### 流程控制结构

##### 分支结构

```mysql
# 如果表达式1成立，则IF函数返回表达式2的值，否则返回表达式3的值
SELECT IF(expr1,expr2,expr3);

# case结构
# 类似于java中的switch语句，一般用于实现等值
CASE 变量｜表达式｜字段
WHEN  要判断的值1 THEN 返回的值1 或者是语句1;
WHEN 要判断的值2 THEN 返回的值2 或者是语句2;
...
ELSE 要返回的值n 或者是语句n;
END
# 判断类似于java中的多重1语句，一般用于实现区间判断
CASE
WHEN 要判断的条件1 THEN返回的值1 或者是语句1;
WHEN 要判断的条件2 THEN返回的值2 或者是语句2;
...
ELSE 要返回的值n 或者是语句n;
END
# 可以作为表达式，嵌套在其他语句中使用，可以放在任何地方，BEGIN END 中或BEGIN END 的外面
# 可以作为独立的语句去使用，只能放在BEGIN END中
# ELSE可以省略，如果ELSE省略了，并且所有WHEN条件都不满足，则返回NULL

# 创建存储过程，根据传入的成绩，来显示等级，比如传入的成绩：90—100，显示A，80—90，显示B，60—80，显示C，否则，显示D
DELIMITER $
CREATE PROCEDURE test_Case(IN score INT)
BEGIN
	CASE 
	WHEN score >= 90 THEN
		SELECT 'A';
	WHEN score >= 80 THEN
		SELECT 'B';
	WHEN score >= 70 THEN
		SELECT 'C';
	WHEN score >= 60 THEN
		SELECT 'D';
	ELSE
		SELECT 'E';
END CASE;
END $
CALL test_Case(95)


-- if结构，语法形式
IF search_condition THEN
	statement_list
ELSEIF search_condition THEN
	statement_list
ELSE
	statement_list
END IF;
 
# 根据传入的成绩，来显示等级，比如传入的成绩：90—100，返回A，80—90，返回B，60—80，返回c，否则，返回D
CREATE FUNCTION test233(score INT) RETURNS CHAR
BEGIN
	IF score >= 90 THEN
		return 'A';
	ELSEIF score >= 80 THEN
		return 'B';
	ELSEIF score >= 70 THEN
		return 'C';
	ELSEIF score >= 60 THEN
		return 'D';
ELSE
	return 'E';
END IF;
END $
SELECT test233(89)$
```

##### 循环结构

- while

  ```mysql
  [标签:] while 循环条件 do
  	循环体
  end while [标签];
  # 循环插入数据
  delimiter $
  CREATE PROCEDURE pro_while(IN insertCount INT)
  BEGIN
  	DECLARE i INT DEFAULT 1;
  	WHILE i <= insertCount DO
  		INSERT INTO admin(username, `password`) VALUES(CONCAT('Rose',i),'666');
  		SET i = i + 1;
  END WHILE;
  END $
  
  CALL pro_while(10)$
  ```

- loop

  ```mysql
  [标签:] loop
  	循环体
  end loop [标签];
  ```

- repeat

  ```mysql
  [标签:] repeat
  	循环体
  until 循环结束条件
  end repeat [标签];
  ```

iterate类似于continue，继续，结束本次循环，继续下一次
leave 类似于 break，跳出，结束当前所在的循环

#### 索引

##### 索引创建

```mysql
# 直接创建
CREATE INDEX index_name ON table(column(length))
# 修改表的形式
ALTER TABLE table_name ADD INDEX index_name ON (column(length))
# 创建表的时候创建索引
CREATE TABLE `table` (
	`id` int(11) NOT NULL AUTO_INCREMENT ,
	`title` char(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
	`content` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL ,
	`time` int(10) NULL DEFAULT NULL ,
	PRIMARY KEY (`id`),
	INDEX index_name (title(length))
)

# 创建唯一索引：索引列的值必须唯一，但允许有空值。如果是组合索引，则列值的组合必须是唯一的，创建方法和普通索引类似
CREATE UNIQUE INDEX index_name ON table(column(length)) 

# 组合索引：
ALTER TABLE article ADD INDEX index_titme_time (title(50),time(10))
# 建立这样的组合索引，其实是相当于分别建立了下面两组组合索引：为什么没有time这样的组合索引呢？这是因为MySQL组合索引“最左前缀”的结果。
# 简单的理解就是只从最左面的开始组合。并不是只要包含这两列的查询都会用到该组合索引，如下面的几个SQL所示：
–title,time
–title
```

### mysql进阶

#### mysql的分层结构

1. 连接层
   最上层是一些客户端和连接服务，包含本地sock通信和大多数基于客户端/服务端工具实现的类似于tcplip的通信。主要完成一些类似于连接处理、授权认证、及相关的安全方案。在该层上引入了线程池的概念，为通过认证安全接入的客户端提供线程。同样在该层上可以实现基于SSL的安全链接。服务器也会为安全接入的每个客户端验证它所具有的操作权限。
2. 服务层
第二层架构主要完成大多少的核心服务功能，如SQL接口，并完成缓存的查询， SQL的分析和优化及部分内置函数的执行。所有跨存储引擎的功能也在这一层实现，如过程、函数等。在该层，服务器会解析查询并创建相应的内部解析树，并对其完成相应的优化如确定查询表的顺序，是否利用素引等，最后生成相应的执行操作。如果是select语句，服务器还会查询内部的缓存。如果缓存空间足够大，这样在解决大量读操作的环境中能够很好的提升系统的性能。
3. 引擎层
存储引擎层，存储引擎真正的负责了MySQL中数据的存储和提取，服务器通过API与存储引擎进行通信。不同的存储引擎具有的功能不同，这样我们可以根据自己的实际需要进行选取。后面介绍MylSAM和InnoDB
4. 存储层
数据存储层，主要是将数据存储在运行于裸设备的文件系统之上，并完成与存储引擎的交互。

|   事项   |                          MyISAM                          |                            InnoDB                            |
| :------: | :------------------------------------------------------: | :----------------------------------------------------------: |
|  主外键  |                          不支持                          |                             支持                             |
|   事务   |                          不支持                          |                             支持                             |
|  行表锁  | 表锁，即使操作一条记录也会锁住整个表，并不适合高并发操作 |              行锁，不对其他行有影响，适合高并发              |
|   缓存   |                只缓存索引，不缓存真实数据                | 不仅缓存索引，还要缓存真实数据，对内存要求较高，内存大小对性能有决定性的影响 |
|  表空间  |                            小                            |                              大                              |
|  关注点  |                           性能                           |                             事务                             |
| 默认安装 |                            Y                             |                              Y                               |

#### 推荐建立索引的列

1. 主键自动建立唯一索引
2. 频繁作为查询条件的字段应该创建索引
3. 查询中与其它表关联的字段，外键关系建立索引
4. 频繁更新的字段不适合创建索引—因为每次更新不单单是更新了记录还会更新索引
5. Where条件里用不到的字段不创建索引
6. 单键/组合索引的选择问题， who？ （在高并发下倾向创建组合索引）
7. 查询中排序的字段，排序字段若通过索引去访问将大大提高排序速度 
8. 查询中统计或者分组字段

#### Explain

| id   | select_type | table | partiitions | type | possible_key | key  | key_len | ref  | rows | filtered | Extra |
| ---- | ----------- | ----- | ----------- | ---- | ------------ | ---- | ------- | ---- | ---- | -------- | ----- |

- `id`：表示查询过程中的读取表的优先级

  1. id的序号相同，**执行顺序由上到下**
  2. 如果是子查询id的序号会递增，**id的值越大，优先级越高越是优先被执行**
  3. 同时出现的话先执行id大的值，id相同的被视作是同一组，执行顺序从上往下

- `select_type`：查询类型

  1. `SIMPLE`：简单的select查询，不包含任何子查询或者是UNION
  2. `PRIMARY`：查询中若包含任何复杂的子部分，最外层查询标记为PRIMARY
  3. `SUBQUERY`：在SELECT或WHERE列表中包含了子查询
  4. `DERIVED`：在FROM列表中包含的子查询会被标记为DERIVED，mysql会递归执行子查询，将结果放在临时表中
  5. `UNION`：若第二个SELECT出现在UNION之后，则被标记为UNION，若UNION包含在FROM子句的子查询中，外层SELECT将被标记为： DERIVED
  6. `UNION RESULT`： 从UNION中得到的结果
  
- `table`：显示这行数据来源于哪一张表

- `type`：访问类型
  `system > const > eq_ref > ref > range > index > ALL`
  至少保证查询达到`range`级别，最好达到`ref`

  1. `ALL`：全表扫描

  2. `index`：Full Index Scan， index与ALL区别为index类型只遍历索引树。这通常比ALL快，因为引文件通常比数据文件小。（也就是说虽然all和Index都是读全表，但index是从索引中读取的，而all是从硬盘中读的）

  3. `range`：只检索给定范围的行，使用一个索引来选择行。key列显示使用了哪个索引一般就是在你的where语句中出现了between， <、>、in等的查询

     这种范围扫描索引扫描比全表扫描要好，因为它只需要开始于索引的某一点，而结束语另一点，不用扫描全部索引。

  4. `ref`：非唯一性索引扫描，返回匹配某个单独值的所有行.

     本质上也是一种索引访问，它返回所有匹配某个单独值的行，然而，它可能会找到多个符合条件的行，所以他应该属于查找和扫描的混合体

  5. `eq_ref`：唯一性索引扫描，对于每个索引键，表中只有一条记录与之匹配。常见于主键或唯一索引扫描

  6. `system`：只有一行记录，是const类型的特例，平时可以忽略不计

  7. `const`：表示通过索引一次就找到了，const用于比较primary key或者unique索引。因为只匹配一行数据，所以很快如将主键置于where列表中，MySQL就能将该查询转换为一个常量

  8. `NULL`

-  `possible_key`：显示可能应用在这张表中的索引，一个或多个。

  查询涉及到的字段上若存在索引，则该索引将被列出，但不一定被查询实际使用

- keys:实际使用的索引。如果为NULL，则没有使用索引

  查询中若使用了覆盖索引，则该索引仅出现在key列表中

- `key_len`：表示索引中使用的字节数，可通过该列计算查询中使用的索引的长度。在不损失精确性的情况下，长度越短越好

  key＿len显示的值为索引字段的最大可能长度，并非实际使用长度，即key＿len是根据表定义计算而得，不是通过表内检索出的

- `ref`：显示索引的哪一列被使用了，如果可能的话，是一个常数。哪些列或常量被用于查找索引列上的值

- `rows`：根据表统计信息及索引选用情况，大致估算出找到所需的记录所需要读取的行数

- `Extra`：包含不适合在其他列中显示但十分重要的额外信息

  1. **Using filesort**：说明mysql会对数据使用一个外部的索引排序，而不是按照表内的索引顺序进行读取，MySQL中无法利用索引完成的排序操炸称为“文件排序”（a1,a2,a3, 使用顺序为a1,a3就会产生文件内排序）

  2. **Using temporary**：使了用临时表保存中间结果，MySQL在对查询结果排序时使用临时表。常见于排序order by和分组查询group by

  3. **Using index**：表示相应的select操作中使用了覆盖索引（Covering Index），避免访问了表的数据行，效率不错！
     如果同时出现using where，表明索引被用来执行索引键值的查找；
     如果没有同时出现using where，表明索引用来读取数据而非执行查找动作。
     
  4. Using where
  
  5. Using join buffer
  
  6. impossible where：where子句的值总是false，不能用来获取任何元组
  
  7. select tables optimized away：在没有GROUP BY子句的情况下，基于索引优化MIN/MAX操作或者
  
     对于MyISAM存储引擎优化COUNT（*）操作，不必等到执行阶段再进行计算，查询执行计划生成的阶段即完成优化。
  8. distinct：优化distinct操作，在找到第一匹配的元组后即停止找同样值的动作

####  Join优化

1. 尽量减少Join语句中的NestedLoop的循环总次数，**永远用小表驱动大表**
2. 保证Join语句中北区东表上的Join条件字段已被索引
3. 当无法保证被驱动表的Join条件字段被索引且内存资源充足的前提下，不要太吝惜JoinBuffer的设置；

```mysql
# 由于jobs表中存在默认的主键索引，在左外连接时，会用到右表索引；同理右外连接时候，会用到做表部分索引
EXPLAIN
SELECT e.last_name ,e.employee_id 
FROM employees e
LEFT JOIN jobs j
ON e.job_id = j.job_id
WHERE e.salary > 1000;
```

![Join优化](../Image/Join优化.png)

##### 避免索引失效的方式

1. 全值匹配我最爱

2. 最佳左前缀法则(带头大哥不能死，中间兄弟不能断 )
   如果索引了多列，要遵守**最左前缀法则**。指的是查询从索引的最左前列开始并且不跳过索引中的列。

   > 最左前缀法则：mysql会一直向右匹配直到遇到范围查询(>、<、between、like)就停止匹配（包括`like '陈%'`这种）

3. 不在索引列上做任何操作（计算、函数、（自动or手动）类型转换），会导致索引失效而转向全表扫描

4. 存储引擎不能使用索引中范围条件右边的列

5. 尽量使用覆盖索引（只访问索引的查询（索引列和查询列一致）），减少select

   > **覆盖索引**：索引列和查询列相同，SQL只需要通过索引就可以返回查询所需要的数据，而不必通过二级索引查到主键之后再去查询数据。

6. mysql 在使用不等于（！＝或者＜＞）的时候无法使用索引会导致全表扫描

7. is null ，is not null 也无法使用索引

8. like以通配符开头（＇％abc...＇）mysql索引失效会变成全表扫描的操作

   > 可以使用**覆盖索引**解决必须使用'%aa%'双百分号问题

9. 字符串不加单引号索引失效，即不能出现隐式的类型转换

10. 少用or，用它来连接时会索引失效

##### 索引建立建议

1. 对于单键索引，尽量选择针对当前query过滤性更好的索引
2. 在选择组合索引的时候，当前Query中过滤性最好的字段在索引字段顺序中，位置越靠前越好。
3. 在选择组合索引的时候，尽量选择可以能够包含当前query中的where字句中更多字段的索引
4. 尽可能通过分析统计信息和调整query的写法来达到选择合适索引的目的

##### 小表驱动大表

```mysql
select * from A where id in (select id from B) 
# 等价于
for select id from B
for select * from A where A.id =B.id
# 当B表的数据集必须小于A表的数据集时，用in优于exists

select * from A where exists (select 1 from B where B.id=A.id) 2
# 等价于
for select * from A
or select * from B where B.id = A.id
# 当A表的数据集系小于B表的数据集时，用exists
# 注意： A表与B表的ID字段应建立索引。
```

> **`in` 和 `exists`的区别**: 如果子查询得出的结果集记录较少，主查询中的表较大且又有索引时应该用in, 反之如果外层的主查询记录较少，子查询中的表大，又有索引时使用exists。其实我们区分in和exists主要是造成了驱动顺序的改变(这是性能变化的关键)，如果是exists，那么以外层表为驱动表，先被访问，如果是IN，那么先执行子查询，所以我们会以驱动表的快速返回为目标，那么就会考虑到索引及结果集的关系了 ，另外IN时不对NULL进行处理。

##### 提升`order by`速度

1. Order by时select＊是一个大忌只Query需要的字段，这点非常重要。在这里的影响是
   - 当Query的字段大小总和小于max_length_for_sort_data 而且排序字段不是TEXT｜BLOB类型时，会用改进后的算法--单路排序，否则用老算法——多路排序。
   - 种算法的数据都有可能超出sort_buffer的容量，超出之后，会创建tmp文件进行合并排序，导致多次I／O，但是用单路排序算法的风险会更大一些，所以要提高sort_buffer_size。
2. 尝试提高 sort_buffer_size
   不管用哪种算法，提高这个参数都会提高效率，当然，要根据系统的能力去提高，因为这个参数是针对每个进程的
3. 尝试提高max_length_for_sort_data
   提高这个参数，会增加用改进算法的概率。但是如果设的太高，数据总容量超出sort_buffer_size的概率就增大，明显症状是高的磁盘I／O活动和低的处理器使用率.

##### 慢查询日志

- MySQL的慢查询日志是MySQL提供的一种日志记录，它用来记录在MySQL中响应时间超过阀值的语句，具体指运行时间超过long_query_time值的SQL，则会被记录到慢查询日志中

- 具体指运行时间超过long_query_time值的SQL，则会被记录到慢查询日志中。long_query_time的默认值为 10，意思是运行10秒以上的语句。

- 由他来查看哪些SQL超出了我们的最大忍耐时间值，比如一条sql执行超过5秒钟，我们就算慢SQL，希望能收集超过5秒的sql，结合之前explain进行全面分析。

  > 开启记录方法为`set global slow_query_time=1`

##### 脚本生成千万级数据

```mysql
create database bigData;
use bigData;

# 建表dept
CREATE TABLE dept(
	id INT UNSIGNED PRIMARY KEY AUTO INCREMENT, 
    deptno MEDIUMINT UNSIGNED NOT NULL DEFAULT O,
    dname VARCHAR(20) NOT NULL DEFAULT '',
	loc VARCHAR(13) NOT NULL DEFAULT ''
) ENGINE-INNODB DEFAULT CHARSET-GBK;

# 建表emp
CREATE TABLE emp(
	id INT UNSIGNED PRIMARY KEY AUTO INCREMENT,
	empno MEDIUMINT UNSIGNED NOT NULL DEFAULT 0, # 编号 
    ename VARCHAR(20) NOT NULL DEFAULT '', # 名字
	ob VARCHAR(9) NOT NULL DEFAULT '', # 工作
	mgr MEDIUMINT UNSIGNED NOT NULL DEFAULT O, # 上级编号 
    hiredate DATE NOT NULL, # 入职时间
	sal DECIMAL(7,2) NOT NULL, # 薪水 
    comm DECIMAL(7,2) NOT NULL, # 红利
	deptno MEDIUMINT UNSIGNED NOT NULL DEFAULT 0 #部门编号
)ENGINE=INNODB DEFAULT CHARSET-GBK;

# 设置二进制日志开启(大规模数据不会报错)
show variables like 'log_bin_trust_function_creators';
set global log_bin_trust_function_creators=1;

# 生成随机字符串
DELIMITER $$
CREATE FUNCTION rand_string(n INT) RETURNS VARCHAR(255)
BEGIN
	DECLARE chars _str VARCHAR(100) DEFAULT 'abcdefghijklmnopgrstuvwxyzABCDEFJHIJKLMNOPQRSTUVWXYZ'; 
	DECLARE return _str VARCHAR(255) DEFAULT '';
	DECLARE i INT DEFAULT 0; 
	WHILE i < n DO
		SET return_str=CONCAT(return_str,SUBSTRING(chars_str,FLOOR(1+RAND()*52), 1)); 
		SETi=i+1;
	END WHILE
RETURN return_str;
END $$

# 用于随机产生部门编号
DELIMITER $$
CREATE FUNCTION rand_num() RETURNS INT(5)
BEGIN
	DECLARE i INT DEFAULT 0;
	SET i = FLOOR(100+RAND()*10); 
	RETURN i;
END $$

# 创建存储过程
DELIMITER $$
CREATE PROCEDURE insert_emp(IN START INT(10),IN max_num INT(10))
BEGIN
	DECLARE  INT DEFAULT 0;
	set autocommit=0;  # 把autocommit设置成0
	REPEAT SET i =i+1;
		INSERT INTO emp (empno, ename ,job ,mgr ,hiredate ,sal ,comm 	,deptno) VALUES ((START+i)) 		,rand_string(6),'SALESMAN',0001,CURDATE(),2000,400,rand_num();
		UNTIL i =max_num
	END REPEAT;
	COMMIT;
END $$
 
# 执行存储过程，往dept表添加随机数据
DELIMITER $$
CREATE PROCEDURE insert_dept(IN START INT(10),IN max_num INT(10))
DECLARE i INT DEFAULT 0;
SET autocommit = 0;
REPEAT
	SETi=i+1;
	INSERT INTO dept (deptno ,dname,loc) VALUES ((START+i) ,rand_string(10),rand_string(8));
	UNTIL i =max_num
END REPEAT;
COMMIT;
END $$
```

##### Show Profile

​	是mysql提供可以用来分析当前会话中语句执行的资源消耗情况。可以用于SQL的调优的测量

1. 查看当前版本是否支持 

2. 开启 `set profiling=on;`

3. 运行sql语句

4. 诊断CPU，`show profiles;` `show profile cpu, block io for query 10 #id为10的查询各步骤时间占用 `

   > - ALL：显示所有的开销信息
   > - BLOCK IO：显示块I/O相关开销
   > - CONTEXT SWITCHES：上下文切换相关开销
   > - CPU：显示CPU相关开销信息
   > - IPC：显示发送和接收相关开销信息
   > - MEMORY：示内存相关开销信息
   > - PAGE FAULTS：示页面错误相关开销信息
   > - SOURCE：显示和Source-function, Source file, Sourceline相关的开销信息 
   > - SWAPS：显示交换次数相关开销的信息

   > **常见问题展示**
   >
   > `converting HEAP to MyISAM`：查询结果太大，内存都不够用了往磁盘上搬了。
   >
   > `Creating tmp table`：创建临时表，拷贝数据到临时表用完再删除
   >
   > `Copying to tmp table on disk`：把内存中临时表复制到磁盘,危险
   >
   > `locked`

##### 读写锁

```mysql
# 读锁和写锁
lock table mylock read, book write;

# 释放表
unlock tables;

# 查看上锁的表
show open tables;
```

> 当前session对table加上**读锁**，session只能够读取当前上锁的的table，不能够读取其他表，也不能修改加了读锁的table
>
> 其余session能够读取上读锁的table，也能够读其他表，对读锁table的写入操作会被阻塞，直至读锁被释放
>
>
> 当前session对table加了**写锁**，拥有对table的完全控制权，但不能够读其他表格
>
> 其他session对table的查询被阻塞，需要等待锁被释放

`Table_locks_immediate`：产生表级锁定的次数，表示可以立即获取锁的查询次数，每立即获取锁值加1；

`Table_locks_waited`：出现表级锁定争用而发生等待的次数（不能立即获取锁的次数，每等待一次锁值加1），此值高则说明存在着较严重的表级锁争用情况；

> Myisam的读写锁调度是写优先，这也是myisam不适合做写为主表的制擎。因为写锁后，其他线程不能做任何操作，大量的更新会使查询很难得到锁，从而造成永远阻塞
>
> InnoDB与MyISAM的最大不同有两点：一是支持事务（TRANSACTION）；二是采用了行级锁

##### 隔离级别

常看当前数据库的事务隔离级别：`show variables like 'tx_isolation'`； 

##### 无索引行锁升级为表锁

  `update tables set a=100 where b=90001` 这里b是varchar型，但是发生隐式转换，索引失效

##### 锁定某一行

```mysql
begin; 
select * from table_name where a=8 for update;            # 锁定某一行后，其他操作会被阻塞，直到锁定行的会话提交commit

commit;
```

##### 行锁分析

```mysql
# 检查InnoDb_row_lock系统变量分析系统上的行锁争夺情况
show status like 'InnoDb_row_lock%';
/*
InnoDb_row_lock_current_waits：当前正在等待锁定的数量
InnoDb_row_lock_time：从系统启动到现在锁定总时间长度
InnoDb_row_lock_avg：每次等待所花平均时间;
InnoDb_row_lock_max：从系统启动到现在等待最常的一次所花的时间；
InnoDb_row_lock_waits：系统启动后到现在总共等待的次数;
*/
```

##### 主从复制

MysQL复制过程分成三步：

1. master将改变记录到二进制日志(binary log) 。这些记录过程叫做二进制日志事件, binary log events;
2. slave将master的binary log events拷贝到它的中继日志(relay log) ;
3. slave重做中继日志中的事件，将改变应用到自己的数据库中。MysQL复制是异步的且串行化的

##### InnoDB底层相关

- InnoDB以页为最小的存储单位，其中页的大小可以采用如下语句参看，默认为16KB

  ```mysql
  SHOW GLOBAL STATUS LIKE 'Innodb_page_size';
  ```

  ![image-20210801171726825](../Image/mysql/image-20210801172434688.png)

  ![innoDB底层原理B+树，主键索引](../Image/mysql/image-20210801173425724.png)

![非聚集索引](../Image/mysql/image-20210801174014980.png)

##### InnoDB框架

![体系结构](../Image/question/innodb-architecture.png)

##### Redo log原理

1. 修改buffer pool中的页，产生脏页

2. update语句生成一个redo log

   > 配置值：`innodb_flush_log_at_trx_commit`
   >
   > 0：不立即持久化，这个任务交给后台线程去做
   >
   > 1：事务提交时，立即把redo log持久化
   >
   > 2：表示事务提交时，立即将redo log写到操作系统的缓冲区，并不会直接将redo log进行持久化，这种情况下，如果数据库挂了，但是操作系统没挂，那么事务的持久性还是可以保证的。

3. redo log持久化(事务提交时)

4. binlog持久化

5. 修改成功

##### binlog，以及和redo log的区别

- redo log记录的是具体页，某一位置的数据修改，而binlog只是记载sql语句，在更新时，redo log性能高于binlog

  > **redo log、undo log、binlog各自的功能**

##### MVCC

​	多版本并发控制：读取数据时通过一种类似快照的方式将数据保存下来，这样读锁就和写锁不冲突了，不同的事务session会看到自己特定版本的数据，版本链
​	MVCC只在**READ COMMITTED**和**REPEATABLE READ**两个隔离级别下工作。其他两个隔离级别够和MVCC不兼 容，因为READ UNCOMMITTED 总是读取最新的数据行，不是符合当前事务版本的数据行。而SERIALIZABLE则会对所有读取的行都加锁。

聚簇索引记录中有两个必要的隐藏列：
- `trx＿id`：用来存储每次对某条聚簇索引记录进行修改的时候的事务id。
- `roll_pointer`：每次对哪条聚簇索引记录有修改的时候，都会把老版本写入undo日志中。这个roll＿pointer就是存了一个指针，它指向这条聚簇索引记录的上一个版本的位置，通过它来获得上一个版本的记录信息。（注意插入操作的undo日志没有这个属性，因为它没有老版本）

已提交读和可重复读的区别就在于它们生成ReadView的策略不同。

开始事务时创建readview， readView维护当前活动的事务id，即未提交的事务id，排序生成一个数组

访问数据，获取数据中的事务id （获取的是事务id最大的记录） ，对比readview：

- 如果在readview的左边（比readview都小） ，可以访问（在左边意味着该事务已经提交）

- 如果在readview的右边（比readview都大）或者就在readview中，不可以访问，获取rollpointer，取上一版本重新对比（在右边意味着，该事务在readview生成之后出现，在readview中意味着该事务还未提交）

已提交读隔离级别下的事务在每次查询的开始都会生成一个独立的ReadView，而可重复读隔离级别则在第一次读的时候生成一个ReadView，之后的读都复用之前的ReadView

这就是Mysql的MVCC，通过版本链，实现多版本，可并发读写，写—读。通过ReadView生成策略的不同实现不同的隔离级别。

Mysql主从同步原理

mysql主从同步的过程：
	Mysql的主从复制中主要有三个线程：**master**（binlog dump thread）、**slave**（I／O thread、SQL thread），Master一条线程和Slave中的两条线程。
- 主节点binlog，主从复制的基础是主库记录数据库的所有变更记录到 binlog。binlog是数据库服务器启动的那一刻起，保存所有修改数据库结构或内容的一个文件。

- 主节点**log dump**线程，当binlog有变动时，log dump线程读取其内容并发送给从节点。

- 从节点**I/O**线程接收binlog内容，并将其写入到relay log文件中。

- 从节点的SQL线程读取relay log文件内容对数据更新进行重放，最终保证主从数据库的一致性

  > 主从节点使用binglog文件＋position 偏移量来定位主从同步的位置，从节点会保存其已接收到的偏移量，如果从节点发生宕机重启，则会自动从position的位置发起同步。

​       由于mysql默认的复制方式是异步的，主库把日志发送给从库后不关心从库是否已经处理，这样会产生一个问题就是假设主库挂了，从库处理失败了，这时候从库升为主库后，日志就丢失了。由此产生两个概念。

- 全同步复制：主库写入binlog后强制同步日志到从库，所有的从库都执行完成后才返回给客户端，但是很显然这个方式的话性能会受到严重影响。
- 半全同步复制：从库写入日志成功后返回ACK确认给主库，主库至少收到一个从库的确认

##### MyISam和InnoDB

###### MyISam

1. 不支持事务，但是每次查询都是原子的；
2. 支持表级锁，即每次操作是对整个表加锁
3. 存储表的总行数；
4. 一个MYISAM表有三个文件：索引文件、表结构文件、数据文件；
5. 采用非聚集索引，索引文件的数据域存储指向数据文件的指针。辅索引与主索引基本一致，但是辅索引不用保证唯一性。

###### InnoDB

1. 支持ACID的事务，支持事务的四种隔离级别；
2. 支持行级锁及外键约束：因此可以支持写并发；
3. 不存储总行数；
4. 一个InnoDb引擎存储在一个文件空间（共享表空间，表大小不受操作系统控制，一个表可能分布在多个文件里），也有可能为多个（设置为独立表空，表大小受操作系统文件大小限制，一般为2G），受操作系统文件大小的限制；
5. 主键索引采用聚集索引（索引的数据域存储数据文件本身），辅索引的数据域存储主键的值；因此从辅索引查找数据，需要先通过辅索引找到主键值，再访问辅索引；最好使用自增主键，防止插入数据时，为维持B＋树结构，文件的大调整。

##### Mysql层次架构分析

![image-20210802143933424](../Image/mysql/image-20210802143933424.png)

##### binlog

- 查看是否开启binlog日志

  ```mysql
  SHOW VARIABLES LIKE '%log_bin%';
  ```

  ![image-20210802151521603](../Image/mysql/image-20210802151521603.png)

