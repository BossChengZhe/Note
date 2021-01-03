#### Makefile的规则

```makefile
target: prerequisites ...
	command
	...
	...
```

`target` 可以是一个`object file`（目标文件），也可以是一个执行文件，还可以是一个标签（`label`）。对于标签这种特性，在后续的“伪目标”章节中会有叙述。
`prerequisites` 生成该`target` 所依赖的文件和`/`或`target`
`command` 该`target` 要执行的命令（任意的shell 命令）

#### Makefile的常用变量

```makefile
#$@表示目标，$^表示所有依赖，$<表示依赖中的第一个
CPPFLAGS=
CFLAGS=
LDFLAGS=
CC=
```

`CPPFLAGS`  预处理器需要的选项 如：-I (大写i指定头文件路径)

`CFLAGS` 编译的时候使用的参数 –Wall –g -c

`LDFLAGS` 链接库使用的选项 –L -l (大写L指定动态库的路径，小写L指定动态库的名称)

#### 其他

```makefile
make -C subdir # 进入指定的目录下
```

进入`subdir`并执行`make`命令，我们把这个Makefile 叫做“总控Makefile”。	

#### 示例

```makefile
# 阶段1
all: add.c sub.c div.c mul.c main.c
	gcc add.c sub.c div.c mul.c main.c -o app

# 阶段2
add: add.o sub.o div.o mul.o main.o
	gcc add.o sub.o div.o mul.o main.o -o app
add.o: add.c
	gcc -c add.c
sub.o: sub.c
	gcc -c sub.c
div.o: div.c
	gcc -c div.c
mul.o: mul.c
	gcc -c mul.o

# 阶段3
#obj=add.o sub.o mul.o div.o main.o
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = app
$(target):$(obj)
	gcc $(obj) -o $(target)
#$@表示目标，$^表示所有依赖，$<表示依赖中的第一个
%o:%c
	gcc -c $< -o $@

# 阶段4
CPPFLAGS=-Iinclude
CFLAGS=-g -Wall
LDFLAGS= -L../lib -lmycalc
CC=gcc

src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = app
$(target):$(obj)
	$(cc) $^ $(LDFLAGS) -o $(target)
%o:%c
	$(cc) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

.PHONE: clean
clean: 
	-rm -f *.o
	-rm -f app
# "-"表示词条命令出错，make也会继续执行后续的命令“-rm -f main.o”
# "@"不显示命令本身，只显示结果“@echo "clean done"”

# 彻底清除生成过程文件和生成配置文件
distclean:
	rm  /usr/bi/app
install:
	cp app /usr/bin
```

