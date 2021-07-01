  

### 数据库

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

