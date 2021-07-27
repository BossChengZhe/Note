  

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

