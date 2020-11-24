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