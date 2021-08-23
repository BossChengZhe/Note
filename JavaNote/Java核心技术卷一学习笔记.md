## Java核心技术卷一

#### Java基本程序设计结构

1. 类名是以大写字母开头的名词，其源代码文件必须与公共类的名字相同。每个Java应用程序都必须有一个main方法，同时main方法必须声明为**public**。

2. Java的8种数据类型：整型（int, short, long, byte）、浮点类型（float, double）、char类型、boolean类型。

3. 强制类型转换：在圆括号中给出想要转换的目标类型，后面紧跟待转换的变量名。

   ```java
   double x = 0.9897;
   int nx = (int) x;
   ```

4. 检测字符串是否相等：使用equals方法去检测两个字符串是否相等，而不要使用 == 运算符去检测。

   ```java
   s.equals(t);
   ```

5. 使用StringBuilder类来构建字符串：

   ```java
   StringBuilder builder = new StringBuilder();
   builder.append("Hello");
   String str = builder.toString();
   ```

6. Java的Scanner类：

   ![image.png](https://i.loli.net/2021/03/02/o6sqmTrul1bAzGH.png)

7. 大数值类型：java.math包中有两个类BigInteger和BigDecimal，可以处理任何长度数字序列的数值。

8. for each循环：用来依次处理数组中每个元素。

   ```
   for (int element : a)
   	System.out.println(element);
   ```

9. java.util.Arrays：sort(type[] a)采用优化的快速排序算法对数组进行排序，binarySearch(type[] a, type v)采用二分搜索算法查找值v，copyOfRange(type[] a, int min, int max)获取数组的指定部分。

10. 字符串反转：

    ```java
    String reverse = new StringBuffer(string).reverse().toString();
    ```

#### 对象与类

1. 在java中，任何对象变量的值都是对存储在另一个对象的引用，new操作符的返回值也是一个引用。

2. 构造器总是伴随着new操作符的执行来被调用，构造器与类同名，可以有0个、1个或多个参数，且没有返回值。另外，不要在构造器中定义与实例域重名的局部变量。

3. 类中定义的方法可以访问所调用对象的私有数据，一个方法可以访问所属类的所有队形的私有数据。

   ```java
   class Employee
   {
       public boolean equals(Employee other)
       {
           return this.name.equals(other.name);
       }
   }
   ```

4. 静态域static属于类，而不属于任何独立的对象，这个类的所有实例将共享该静态域。静态方法是一种不能向对象实施操作的方法，是一种没有this参数的方法，不能操作对象，但可以访问自身类中的静态域。静态方法主要在两种情况下进行使用：（1）一个方法不需要访问对象状态，其所需参数都是通过显示参数提供（Math.pow）。（2）一个方法只需要访问类的静态域。

5. 类设计技巧方法：

   （1）一定要保证数据私有，不要破坏封装性；

   （2）一定要对数据初始化，可以提供默认值，也可以在所有构造器中设置默认值；

   （3）不要在类中使用过多的基本类型，可以用其他类进行代替使用；

   （4）不是所有域都需要独立的域访问器和域更改器；

   （5）将复杂的类进行分解；

   （6）优先使用不可变的类。

#### 继承

1. 子类构造器：我们可以通过super实现对超类构造器的调用，使用super调用构造器的语句必须是子类构造器的第一条语句。super关键字一是可以调用超类的方法，二是调用超类的构造器。

2. 一个对象变量可以指示多种实际类型的现象称为多态，它在运行时能够自动地选择调用哪个方法的现象称为动态绑定。如果是private方法、static方法、final方法或者构造器，那么编译器将可以准确知道调用哪个方法，称这种调用方式为静态绑定。

3. 在覆盖一个方法时，子类方法不能低于超类方法的可见性，如果超类方法是public，子类方法一定要声明为public。

4. final修饰的类不可以被继承，final修饰的方法不可以被覆盖。

5. 将一个子类的引用赋给一个超类变量，编译器是允许的。但是将一个超类的引用赋给一个子类变量，必须进行类型转换。

   ```java
   Employee e = new Manager();
   Manager m = (Manager)new Employee();
   ```

6. 抽象类：不可以被实例化，但可以定义一个抽象类的对象变量，其只能引用非抽象子类的对象。

7. Java用于控制可见性的4个访问修饰符：

   （1）private：仅对本类可见；

   （2）public：对所有类可见；

   （3）protected：对本包和所有子类可见；

   （4）默认类：对本包可见。

8. 灵活扩展数组和访问数组元素：首先创建一个ArrayList数组，并添加所有元素，然后再使用toArray()方法将数组元素拷贝到一个数组中。

   ```java
   X[] a = new X[list.size()];
   list.toArray(a);
   ```

9. 对象包装器与自动装箱：将基本数据类型转换为对象，需要使用对象包装器，包括Integer、Long、Float、Double、Short、Byte、Character、Void和Boolean。对象包装器是不可变的，一旦构造后则不允许更改包装值，另外对象包装类是final，不能定义其子类。添加int类型的元素到ArrayList\<Integer>中，其int类型的变量会自动变换成Integer对象，这种变换称为自动装箱。相对应将一个Integer对象赋给一个int值时，将会自动拆箱。

10. 反射：能够分析类能力的程序。它可以用来在运行时分析类的能力，在运行时查看对象，实现通用的数组操作代码，还可以利用Method对象。

    ![img](https://pic4.zhimg.com/80/v2-312b1b34ca2ebd1317bedf70ddfad38b_1440w.jpg)

#### 接口、Lambda表达式与内部类

1. 接口（interface）：用来描述类具有什么功能，而并不给出每个功能的具体实现。一个类可以实现一个或多个接口，并在需要接口的地方，随时使用实现了相应接口的对象。接口中所有方法自动属于public，因此不必提供关键字public。

2. Comparable接口是在类内部制定比较策略，而Comparator接口是在类外部来制定比较策略。

3. lambda表达式：它就是一个代码块，以及必须传入代码的变量规范。

   ```java
   Comparator<String> comp = (first,second) -> first.length()-second.length();
   ```

4. 内部类：可以访问该类定义所在作用域中的数据，包括私有数据；可以对同一个包中的其他类隐藏起来。

5. 匿名内部类：如果只创建这个类的一个对象，则无须命名。一般用于实现事件监听器和其他回调。

#### 集合

1. 迭代器：iterator方法用于返回一个实现了Iterator接口的对象，可以使用它来依次访问集合中的元素。java迭代器被认为是位于两个元素之间。

   ```java
   Collection<String> c = ...;
   Iterator<String> iter = c.iterator();
   while(iter.hasNext())
   {
       String element = iter.next();
       .....
   }
   ```

2. Java集合框架：

   ![img](https://www.runoob.com/wp-content/uploads/2014/01/2243690-9cd9c896e0d512ed.gif)

   ![image.png](https://i.loli.net/2021/03/04/2UBR347EVNSfdHn.png)

   ![image.png](https://i.loli.net/2021/03/04/TuhboVW2Iep6HLF.png)

3. 集合有两个基本接口：Collection和Map。List是一个有序集合，可以采用迭代器访问和随机访问两种方式。Set的add方法不允许增加重复元素。如果需要大量的插入或删除元素，我们优先使用链表；如果列表中只有少数元素，则完全可以使用ArrayList。ArrayList封装了一个动态再分配的对象数组。

4. Vector和ArrayList的使用区别：Vector类的所有方法都是同步的，如果由一个线程访问Vector，则在同步操作上消耗大量事件，而ArrayList方法不是同步的。因此在不需要同步时使用ArrayList，而不要使用Vector。

5. HashSet类实现了基于散列表的集合，可以用add方法添加元素。TreeSet类是 一个有序集合，可以以任意顺序将元素插到集合中，在对集合进行遍历时，每个值将自动按照排序后的顺序呈现，它的实现使用的**红黑树**。

6. 优先级队列PriorityQueue：元素可以按照任意顺序插入，但总是按照排序的顺序进行检索，无论何时调用remove方法，总会获得当前优先级队列中最小的元素，它使用了堆的数据结构。

7. java类库提供了两种map类型：HashMap和TreeMap，都实现了Map接口。HashMap对key进行散列，TreeMap用key的整体顺序对元素进行排序，并将其组织成搜索树。

8. LinkedHashMap将用于访问顺序，而不是插入顺序，对映射条目进行迭代，对于实现高速缓存的“最近最少使用”原则十分重要。

9. 集合与数组的转换：Arrays.asList可以将一个数组转换为集合，使用toArray()方法可以从集合转换为数组。

   ```javascript
   String[] values = ...;
   ArrayList<String> staff = new ArrayList<>(Arrays.asList(values));
   
   String[] values = staff.toArray(new String[staff.size()]);
   ```

10. `LinkedList`即实现了`List`接口，又实现了`Queue`接口，但是，在使用的时候，如果我们把它当作List，就获取List的引用，如果我们把它当作Queue，就获取Queue的引用。而Queue是一个接口，不可以被实例化。

    ```java
    // 这是一个List:
    List<String> list = new LinkedList<>();
    // 这是一个Queue:
    Queue<String> queue = new LinkedList<>();
    ```

11. Java的栈初始化：

    ```java
    Deque<T> stack = new ArrayDeque<>();
    ```

    由于Stack继承自Vector，其底层结构是数组类型，并没有用链表结构单独实现，效率上有所下降。而Deque继承自Queue，更加适合于Stack的LIFO功能。

12. Queue和Deque的区别：

    Queue以及Deque都是继承于Collection，Deque是Queue的子接口。Queue是FIFO的单端队列，Deque是双端队列。Queue有一个直接子类PriorityQueue，而Deque中直接子类有两个：LinkedList以及ArrayDeque。

    PriorityQueue可以作为堆使用，而且可以根据传入的Comparator实现大小的调整，会是一个很好的选择。 ArrayDeque通常作为栈或队列使用，但是栈的效率不如LinkedList高。 LinkedList通常作为栈或队列使用，但是队列的效率不如ArrayQueue高。
    
13. HashTable和HashMap的区别：

    * HashMap允许将 null 作为一个 entry 的 key 或者 value，而 Hashtable 不允许。

    * HashMap 把 Hashtable 的 contains 方法去掉了，改成 containsValue 和 containsKey。因为 contains 方法容易让人引起误解。

    * HashTable 继承自 Dictionary 类，而 HashMap 是 Java1.2 引进的 Map interface 的一个实现。

    * HashTable 的方法是 Synchronize 的，而 HashMap 不是，在多个线程访问 Hashtable 时，不需要自己为它的方法实现同步，而 HashMap 就必须为之提供外同步。

    * Hashtable 和 HashMap 采用的 hash/rehash 算法都大概一样，所以性能不会有很大的差异。

    | HashMap   | 线程不安全 | 允许null键和值 | 效率高   | 非同步 | 继承自Map        |
    | --------- | ---------- | -------------- | -------- | ------ | ---------------- |
    | HashTable | 线程安全   | 不允许         | 效率稍低 | 同步   | 继承自Dictionary |

14. java复制Map对象：

    * 浅拷贝：只复制对象的引用，两个引用仍然指向同一对象，在内存中占用同一内存，使用方式为=；
    * 深拷贝：被复制对象的所有变量都含有与原来对象相同的值，但不占用同一内存，使用方式为通过putAll()方法。

#### 并发

1. 多进程与多线程的区别：进程是程序的一次执行，是系统进行资源分配和调度的独立单位，线程是进程的一个实体，是CPU调度和分派的基本单位。多进程与多线程的本质区别在于每个进程拥有自己的一整套变量，而线程则共享数据。

2. 线程有6种状态：New(新创建)、Runnable(可运行)、Blocked(被阻塞)、Waiting(等待)、Timed waiting(计时等待)、Terminated(被终止)。

   <img src="https://i.loli.net/2021/03/05/lhrfbIsvKGa9xNc.png" alt="image.png" style="zoom:50%;" />

3. 守护线程通过调用t.setDaemon(true)来将线程进行转换，其目的是为其他线程提供服务。

4. 用ReentrantLock锁方法来防止代码块受并发访问的干扰，保证任何时刻只有一个线程进入临界区，一旦一个线程封锁了锁对象，其他任何线程都无法通过lock语句。当其他线程调用lock时，这些线程被阻塞，直到第一个线程释放锁对象。

   ```java
   Lock myLock = new ReentrantLock();
   myLock.lock();
   try{
       ...
   }finally{
       myLock.unlock();
   }
   ```

5. 条件对象Condition类：一旦一个线程调用await方法，它进入该条件的等待集。当锁可用时，该线程不能马上解除阻塞，直到另一个线程调用同一条件上的signalAll方法为止。

6. 锁和条件的作用：锁用来保护代码片段，任何时刻只能有一个线程执行被保护的代码；锁可以管理试图进入被保护代码段的线程；锁可以拥有一个或多个相关的条件对象；每个条件对象管理那些已经进入被保护代码段但还不能运行的线程。

7. 如果一个方法用synchronized关键字声明，那么对象的锁将保护整个方法。wait方法添加一个线程到等待集中，notifyAll/notify方法解除等待线程的阻塞状态。

