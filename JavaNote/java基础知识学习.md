## Java基础知识笔记

#### 一、java基础：一切从基础开始

1. java的编译执行过程：

   首先解释一下编译和解释语言的区别：

   * 编译型语言（compiled language）指通过编译器（compiler）将源代码编译为机器码（machine code）后运行的语言，例如C、C++；

   * 解释型语言（interpreted language）指由解释器（interpreter）直接执行，不需要编译成机器语言，例如 PHP、JavaScript。

   编译型语言和解释型语言的优点和缺点：

   - 由于解释型语言会在运行时翻译源代码，一般情况下运行速度不如编译型语言；
   - 解释型语言由解释器运行，而不是直接运行在操作系统上，所以一般有较强的跨平台能力。

   为了兼顾跨平台和运行速度，Java 源代码首先会被编译为字节码文件（.class），但并非是机器语言，而是需要在 JVM 上运行，而 .class 文件在 JVM 上是解释执行的。所以 Java 兼具编译型语言和解释型语言的特点。

   <img src="https://pic1.zhimg.com/80/45e5e8e74ed0fec7c782e30ac8c4edd7_1440w.jpg?source=1940ef5c" alt="img" style="zoom: 80%;" />

2. jdk = jre + 开发工具集， jre = jvm + 基础类。

3. 在一个java源文件中可以声明多个class，但是只能有一个类声明为public，而且声明为public的类必须与源文件名相同。

4. 在java中，char可以存储2个字节，这里的字符为2字节，而C/C++中的char存储1个字节。

5. 数据类型转换：

   * 自动类型提升：容量小的数据类型数据变量与容量大的数据类型数据变量运算时，结果自动提升为容量大的数据类型。byte、char、short之间不能相互转换，做运算时其结果为int类型。

   * 强制类型转换：自动类型提升的逆运算，需要使用强转符号()，可能导致精度损失。

     ```java
     double a = 22.8;
     int b = (int)a;
     ```

   * +=、 -=、 *=、 /=并不会改变变量本身的数据类型

6. 计算机底层都以补码的方式来存储数据，其中正数的补码和原码一样，负数的补码是其反码加一。

7. String不是基本数据类型，它属于引用数据类型；String允许使用""，而char不允许使用''。

8. String中==比较引用地址是否相同，equals()比较字符串的内容是否相同。

   ```java
   String s1 = "Hello";              // String 直接创建
   String s2 = "Hello";              // String 直接创建
   String s3 = s1;                   // 相同引用
   String s4 = new String("Hello");  // String 对象创建
   String s5 = new String("Hello");  // String 对象创建
    
   s1 == s1;         // true, 相同引用
   s1 == s2;         // true, s1 和 s2 都在公共池中，引用相同
   s1 == s3;         // true, s3 与 s1 引用相同
   s1 == s4;         // false, 不同引用地址
   s4 == s5;         // false, 堆中不同引用地址
    
   s1.equals(s3);    // true, 相同内容
   s1.equals(s4);    // true, 相同内容
   s4.equals(s5);    // true, 相同内容
   ```

   ![img](https://www.runoob.com/wp-content/uploads/2013/12/java-string-1-2020-12-01.png)

9. &与&&的区别：如果第一个条件为false的情况下，前者都需要判断条件，后者则跳过后面的条件。同理|与||也有这样的关系（第一个判断条件为true）。

10. 三元运算符的两个表达式要求类型必须一致，因此if-else并不能完全转换成三元运算符表达式。

11. Scanner的next()和nextLine()区别：

    * next()方法在读取内容时，会过滤掉有效字符前面的无效字符，对输入有效字符之前遇到的空格键、Tab键或Enter键等结束符，next()方法会自动将其过滤掉；只有在读取到有效字符之后，next()方法才将其后的空格键、Tab键或Enter键等视为结束符；所以next()方法不能得到带空格的字符串。
    * nextLine()方法字面上有扫描一整行的意思，它的结束符只能是Enter键，即nextLine()方法返回的是Enter键之前没有被读取的所有字符，它是可以得到带空格的字符串的。

12. if-else结构具有**就近原则**的定义，即如果当前else没有括号说明范围，则和它最近的if结构相匹配。

13. switch结构中的表达式，只能是如下6种数据类型：byte、short、int、char、枚举、String。

14. java中数组初始化过程中，整型默认0，浮点数类型默认为0.0，char类型默认为0，boolean类型默认为false，引用数据类型默认为null。但是基本数据类型和引用数据类型必须要初始化才能使用，没有默认初始化值。

15. 对于二维数组中，int\[][] arr = new int\[4][]的外层元素初始化值为null。

16. 数组的赋值使用=，将原数组的地址值赋给该数组；数组的复制使用new，将原数组的内容值copy给该数组。

17. 排序算法：

    * 选择排序：直接选择排序、堆排序
    * 交换排序：冒泡排序、快速排序
    * 插入排序：直接插入排序、折半插入排序、shell排序
    * 归并排序
    * 桶式排序
    * 基数排序

18. Arrays工具类使用：

    * binarySearch(int[] a, int key)：二分查找
    * fill(int[] a, int val)：将指定值填充到数组中
    * equals(int[] a, int[] b)：判断两个数组是否相等
    * toString(int[] a)：输出数组信息
    * sort(int[] a)：数组排序
    * copyOf(int[] a, iny newLength)：复制数组

#### 二、java面向对象：万事万物皆对象

1. 对象的创建和使用（内存分析）：

   堆（Heap）：存放**对象实例**，所有的对象实例以及数组都要在堆上分配。

   栈（Stack）：指虚拟机栈，用于存储**局部变量**，各种基本数据类型和对象引用类型，方法执行完之后自动释放内存。

   方法区（Method Area）：用于存储虚拟机加载的**类信息**、**常量**、**静态变量**、即时编译器编译后的代码等数据。

   <img src="https://img-blog.csdnimg.cn/20210311190353482.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5Nzk0MDYy,size_16,color_FFFFFF,t_70" alt="img" style="zoom:67%;" />

2. 类中的局部变量没有默认初始化值，因此必须**显式初始化**。另外，类中的非静态属性存放在堆中，局部变量存放在栈中。

3. 属性（成员变量）和局部变量的相同点和不同点：

   **相同点：**

   * 变量格式定义相同
   * 先声明后使用
   * 变量都有其对应的作用域

   **不同点：**

   * 在类中声明的位置不同：属性直接定义在类的{}内，局部变量声明在方法内、方法形参、代码块内、构造器形参、构造器内部的变量。
   * 权限修饰符不同：在声明属性时使用权限修饰符来指明其权限，局部变量不可以使用权限修饰符。
   * 默认初始化值：属性根据其类型都有默认初始化值，局部变量没有默认初始化值，调用前必须赋值。
   * 在内存位置不同：属性加载到堆空间中，局部变量加载到栈空间。

4. return关键字的使用：

   * 在void方法中可以起结束作用；
   * 针对有返回值类型的方法，则可以返回数据方法所要求的数据。

5. 所有变量可以分为成员变量和局部变量，其中成员变量包括实例变量和类变量（static修饰），局部变量包括形参（方法、构造器中定义的变量）、方法局部变量（在方法内定义）和代码块局部变量。

6. 方法重载：同一个类、相同方法名，参数列表不同，参数类型不同，参数个数不同。跟方法的权限修饰符、返回值类型、形参变量名和方法体都没有关系。

7. 可变个数形参的方法与类中方法名相同，形参类型也相同的数组之间不构成重载，并且必须声明在末尾，且最多只能声明一个可变形参。（主要用在数据库查询语句中，充当占位符）

8. 方法参数的值传递机制：

   * 形参是基本数据类型，将实参的数据值传递给形参；
   * 形参是引用数据类型，将实参的地址值传递给形参。

   **java在方法传递参数时，是将变量复制一份，然后传入方法体去执行。**

9. String的值传递机制：

   >1. 虚拟机在堆中开辟一块内存，并存值"ab"。
   >
   >2. 虚拟机在栈中分配给str一个内存，内存中存的是1中的地址。
   >
   >3. 虚拟机复制一份str，我们叫str'，str和str'内存不同，但存的值都是1的地址。
   >
   >4. 将str'传入方法体
   >
   >5. 方法体在堆中开辟一块内存，并存值"cd"
   >
   >6. 方法体将str'的值改变，存入5的内存地址
   >
   >7. 方法结束，方法外打印str，由于str存的是1的地址，所有打印结果是"ab"

10. int[]数组输出的是地址值，char[]数组输出的是字符串：

    ```java
    int[] a = new int[]{1,2,3,4};
    System.out.println(a);
    char[] b = new char[]{'a','b','c'};
    System.out.println(b);
    ```

11. 一旦显式定义了类的构造器，则不再提供默认的空参构造器。另外，默认构造器的权限和类的权限相同，如果类是public，则构造器也为public。

12. 类中属性赋值的先后顺序：

    默认初始化 -- 显式初始化 /代码块赋值（看位置的先后顺序）--构造器赋值 -- 通过方法或者属性设值。

13. javaBean：可重用组件。

    * 类是公共的；
    * 有一个无参的公共构造器；
    * 有属性，且有对应的set、get方法。

14. this(形参列表)必须声明在构造器的首行，如果既有super构造器也有this构造器，只能二选一，不能同时出现。

    ```java
        public Student(String name, int age, String major) {
    //        this(major);
            super(name, age);
            this.major = major;
        }
    ```

15. 方法重写（override）：子类继承父类之后，对父类中同名参数的方法进行覆盖操作，子类重写方法的方法名、形参列表和父类的相同。子类重写方法的权限修饰符不小于父类被重写方法的权限修饰符，子类不能重写父类private方法。

16. 多态性：父类的引用指向子类的对象，当调用**子父类同名同参数**的方法时，实际执行的是子类重写父类的方法（虚拟方法调用）。编译看左，运行看右。对象的多态性只适用于方法，而不适用于属性。多态是**运行时行为**。

    ```java
    Person p1 = new Man();
    Person p2 = new Woman();
    ```

17. 方法的重载与重写：

    * 重载允许多个同名方法，而方法的参数不同，在方法调用前，编译器就已经确定了所要调用的方法，称为**静态绑定**。
    * 对于多态，只有等到方法调用时，解释运行器才会确定要调用的具体方法，称为**动态绑定**。

18. 多态也被称为**向上转型**，而**向下转型**使用强制类型转换符可以调用子类中特有的属性和方法。

19. instanceof关键字：判断对象是否是某个类的实例。

20. 若子类重写父类方法，则子类里定义的方法彻底覆盖父类里的同名方法，即**编译看左边，运行看右边**；而对于实例变量，即使子类定义了与父类完全相同的实例变量，也不能进行覆盖，即**编译运行均看左边**。

21. 可变形参和同名数组之间的方法可以进行重写。

    ```java
    public class InterviewTest {
        public static void main(String[] args) {
            Base base = new Sub();
            base.add(1,2,3); // sub
    
            Sub sub = (Sub) base;
            sub.add(1,2,3); // sub2
        }
    }
    
    class Base {
        public void add(int a, int... arr){
            System.out.println("base");
        }
    }
    
    class Sub extends Base {
        @Override
        public void add(int a, int... arr) {
            System.out.println("sub");
        }
    
        public void add(int a, int b, int c){
            System.out.println("sub2");
        }
    }
    ```

22. ==运算符：

    * 如果比较的是基本数据类型变量，则比较两个变量保存的数值是否相同，类型不一定必须相同；
    * 如果比较的是引用数据类型变量，则比较两个对象的地址值是否相同。

23. 包装类（Wrapper）：八种基本数据类型定义相应的引用类型。

    * 装箱：基本数据类型到包装类，调用包装类的构造器或者**自动装箱**；
    * 拆箱：包装类到基本数据类型，调用包装类的xxxValue()方法或者**自动拆箱**。

    ![image.png](https://i.loli.net/2021/05/28/L6XNjWHxnIAO8aq.png)

24. 包装类常见问题：

    ```java
    public void test4(){
        Integer a1 = new Integer(1);
        Integer a2 = new Integer(1);
        System.out.println(a1==a2); //false
    
        // Integer内部定义了IntegerCache结构，保存了-128~127范围的整数，可以直接使用而不用new。
        Integer b1 = 1;
        Integer b2 = 1;
        System.out.println(b1==b2); //true
    
        Integer c1 = 128;
        Integer c2 = 128;
        System.out.println(c1==c2); //false
    }
    ```

25. static关键字：可以用来修饰属性、方法、代码块和内部类。

    * 静态变量随着类的加载而加载，因此也程为类变量。静态变量的加载早于对象的创建，且只会存在一份，存在方法区的静态域中。
    * 静态方法也随着类的加载而加载，只能调用静态方法或静态属性；非静态方法既可以调用静态的也可以调用非静态的方法或属性。
    * 静态方法内不能使用this或super关键字。
    * 静态属性或方法的生命周期早于非静态属性或方法。
    * static方法不可以被重写。

26. 代码块：用来初始化类和对象，只能用static修饰，分成静态代码块和非静态代码块。代码块按照声明的**先后顺序**进行。

    * 静态代码块：随着类的加载而执行，只执行一次；
    * 非静态代码块：随着对象的创建而执行，每创建一个对象便执行一次；**作用**在创建对象时，可以对对象的属性等进行初始化。

    ```java
    class Person{
        String name;
        int age;
        static String desc = "I am a person";
    
        public Person(){
    
        }
    
        public Person(String name, int age) {
            this.name = name;
            this.age = age;
        }
    
        //static代码块
        static{
            System.out.println("static block");
            desc = "I am studying";
            info();
        }
    
        // 代码块
        {
            System.out.println("block");
            age = 1;
            info();
        }
    
        public void eat(){
            System.out.println("Eating");
        }
    
        @Override
        public String toString() {
            return "Person{" +
                    "name='" + name + '\'' +
                    ", age=" + age +
                    '}';
        }
    
        public static void info(){
            System.out.println("I am a happy person");
        }
    }
    ```

27. **final**关键字：用来修饰类、方法和变量。

    - 修饰类：此类不能被==继承==；
    - 修饰方法：此方法不能被==重写==；
    - 修饰变量：此变量称为常量，不能被修改，可以显式初始化、代码块中初始化和构造器初始化。
    - static final用来修饰属性，被称为全局常量。

28. **abstract**关键字：用来修饰类和方法。

    * 修饰类：此类不能被实例化，类中一定有构造器，便于子类实例化时调用。
    * 修饰方法：抽象方法只有方法的声明，没有方法体，且抽象方法所在的类一定是抽象类。
    * 子类重写父类的所有抽象方法，才可实例化，否则该子类也是一个抽象类。

29. 匿名子类的使用：

    ```java
    public class AbstractTest {
    
        public static void main(String[] args) {
            Student student = new Student();
            student.eat();
    
            // 创建匿名子类的对象
            Person1 p = new Person1() {
                @Override
                public void eat() {
                    System.out.println("Eating");
                }
            };
            method(p);
            // 匿名子类的匿名对象
            method(new Person1() {
                @Override
                public void eat() {
                    System.out.println("Eating2");
                }
            });
    
        }
        public static void method(Person1 p){
            p.eat();
        }
    }
    
    abstract class Person1{
        String name;
        int age;
    
        public Person1(){
    
        }
    
        public Person1(String name, int age) {
            this.name = name;
            this.age = age;
        }
        public abstract void eat();
        public void walk(){
            System.out.println("Walking");
        }
    }
    
    class Student extends Person1{
    
        @Override
        public void eat() {
            System.out.println("Student eating");
        }
    }
    ```

30. **接口：** 定义全局常量、抽象方法，还可以定义静态方法和默认方法。

    * 全局常量：public static final(可以省略不写)；

    * 抽象方法：public abstract；

    * 接口中不能定义构造器，即表示不可以被实例化，但可以让类去实现接口（可以实现多个接口）；

    * 如果实现类覆盖了接口中所有的抽象方法，则此实现类可以被实例化，否则仍未一个抽象类；

    * 接口与接口之间可以继承，且可以==多继承==；

      ```java
      class DD implements CC{
      
          @Override
          public void method1() {
              
          }
      
          @Override
          public void method2() {
      
          }
      }
      
      interface AA{
          void method1();
      }
      
      interface BB{
          void method2();
      }
      
      interface CC extends AA,BB{
          
      }
      ```

    * 接口中定义的静态方法使用static修饰，只能通过接口来调用；

    * 接口中定义的默认方法使用default修饰，可以通过实现类对象调用，如果子类或实现类继承的父类和实现接口中声明了同名同参数方法，则子类默认调用父类同名同参数的方法，即类优先原则；

    * 接口冲突：多个实现接口中定义了同名同参数的默认方法，直接报错；

    * 在实现类方法中调用接口中的默认方法，使用接口名.super.method()。

      ```java
      public class SubClassTest {
      
          public static void main(String[] args) {
              SubClass s = new SubClass();
              s.method3();
              s.myMethod();
          }
      }
      
      class SuperClass {
          public void method3(){
              System.out.println("SuperClass: method3");
          }
      }
      
      class SubClass extends SuperClass implements CompareA,CompareB{
      
          @Override
          public void method2() {
              System.out.println("SubClass: method2");
          }
      
          @Override
          public void method3() {
              System.out.println("SubClass: method3");
          }
      
          public void myMethod(){
              method3(); // 调用自定义重写方法
              super.method3(); // 调用父类中声明的方法
              CompareA.super.method3(); // 调用接口中默认方法
          }
      }
      
      interface CompareA {
      
          // 接口中定义的静态方法，只能通过接口来调用
          public static void method1(){
              System.out.println("CompareA: method1");
          }
      
          // 默认方法
          public default void method2(){
              System.out.println("CompareA: method2");
          }
      
          default void method3(){
              System.out.println("CompareA: method3");
          }
      }
      
      interface CompareB {
      
          default void method3(){
              System.out.println("CompareB: method3");
          }
      }
      ```

31. 接口的多态性：

    ```java
    public class USBTest {
    
        public static void main(String[] args) {
            new Computer().transferData(new Flash());
            new Computer().transferData(new Printer());
        }
    }
    
    class Computer{
        public void transferData(USB usb){
            usb.start();
            usb.stop();
        }
    }
    
    interface USB{
        void start();
        void stop();
    }
    class Flash implements USB{
    
        @Override
        public void start() {
            System.out.println("U盘开启工作");
        }
    
        @Override
        public void stop() {
            System.out.println("U盘停止工作");
        }
    }
    class Printer implements USB{
    
        @Override
        public void start() {
            System.out.println("打印机开启工作");
        }
    
        @Override
        public void stop() {
            System.out.println("打印机停止工作");
        }
    }
    ```

32. 内部类：分成成员内部类（静态、非静态）和局部内部类（方法、代码块、构造器）。

    * 成员内部类：可以定义属性、方法、构造器，也可以被static、final、abstract修饰，也可以调用外部类的结构，也可以被4种不同权限符修饰；
    * 局部内部类：常用于返回实现接口对象方法中定义一个实现接口的内部类；
    * 在局部内部类的方法中，如果调用局部内部类所声明方法中的局部变量，要求此局部变量声明为final。

    ```java
    public class InnerClassTest {
    
        public static void main(String[] args) {
            // 实例化静态成员内部类
            Human.Dog dog = new Human.Dog();
            dog.show();
    
            // 实例化非静态成员内部类
            Human h = new Human();
            Human.Bird bird = h.new Bird();
            bird.show();
    
            bird.display("黄鹂");
        }
    }
    
    class Human {
    
        String name;
        int age;
        public void eat(){
            System.out.println("Human: eat()");
        }
    
        // 静态成员内部类
        static class Dog{
            String name;
            int age;
    
            public void show(){
                System.out.println("Dog: show()");
            }
        }
    
        class Bird{
            String name;
            int age;
    
            public void show(){
                System.out.println("Bird: show()");
                eat();
            }
    
            public void display(String name){
                System.out.println(name);
                System.out.println(this.name); // 内部类属性
                System.out.println(Human.this.name); // 外部类属性
            }
        }
    }
    ```

#### 三、java基础进阶：更上一层楼

1. 异常类型：分为错误Error和异常Exception。

   * Error：一般不编写针对性的代码进行处理；
   * Exception：可以进行异常的处理，分为编译时异常（IOException、ClassNotFoundException）和运行时异常。

   ```java
   public class ExceptionTest {
   
       /**
        * 运行时异常
        */
   
       // NullPointerException
       @Test
       public void test1(){
           String str = "abc";
           str = null;
           System.out.println(str.charAt(0));
       }
   
       // ArrayIndexOutOfBoundsException
       @Test
       public void test2(){
           int[] a = new int[3];
           System.out.println(a[3]);
       }
   
       // ClassCastException
       @Test
       public void test3(){
           Object obj = new Date();
           String str = (String)obj;
       }
   
       // NumberFormatException
       @Test
       public void test4(){
           String str = "abc";
           int num = Integer.parseInt(str);
       }
   
       @Test
       public void test5(){
           Scanner sc = new Scanner(System.in);
           int num = sc.nextInt();
           System.out.println(num);
       }
   
       // ArithmeticException
       @Test
       public void test6(){
           int a = 10;
           int b = 0;
           System.out.println(a/b);
       }
   }
   ```

2. throws和try-catch-finally的选择使用：

   * 如果父类被重写的方法没有throws方式处理异常，则子类重写的方法不能使用throws，必须使用try-catch-finally来处理异常；
   * 执行方法中先后调用了另外几个方法（递进执行的），建议这几个方法使用throws，执行方法使用try-catch-finally来处理；

   ![image.png](https://i.loli.net/2021/05/31/t9pkLinU1KYsycQ.png)

3. throw和throws区别：thorw表示抛出一个异常类的对象，生成异常对象的过程，声明在方法体内；throws属于异常处理的一种方式，声明在方法的声明处。

4. 浅拷贝与深拷贝：

   * 浅拷贝指的是被复制对象的所有属性都含有，且与原来对象相同，但所有的对象引用属性仍然指向原来对象；
   * 深拷贝在浅拷贝的基础上，所有引用其他对象的变量也进行了clone，并指向被复制过的新对象。
   * 如果一个被复制的属性都是基本类型，那么只需要实现当前类的cloneable机制就可以了，此为浅拷贝。
   * 如果被复制对象的属性包含其他实体类对象引用，那么这些实体类对象都需要实现cloneable接口并覆盖clone()方法。
   * 实现深拷贝的方法：利用序列化实现深拷贝、使用原型工厂类。
   * **区别：** 浅拷贝是指拷贝对象时仅仅拷贝对象本身（包括对象中的基本变量），而不拷贝对象包含的引用指向的对象。深拷贝不仅拷贝对象本身，而且拷贝对象包含的引用指向的所有对象。

#### 四、java多线程

1. 程序、进程与线程的区别：

   * 程序（program）是为完成特定任务、用某种语言编写的一组指令集合，是一段**静态代码**；
   * 进程（process）是程序的一次执行，是一个动态过程，是系统进行资源分配的基本单位，系统在运行时会为每个进程分配不同的内存区域；
   * 线程（thread）是CPU调度和分配的基本单位，拥有独立的**运行栈和程序计数器**，可以与同进程的其他线程**共享数据**，但没有单独的地址空间。
   * 一个进程中的多个线程共享相同的内存单元/内存地址空间，它们从同一堆中分配对象，可以访问相同的变量和对象，但共享系统资源会带来一定安全隐患。

2. 多线程的创建方式一：继承于Thread类

   * 创建一个继承于Thread类的子类；
   * 重写Thread类的run()方法；
   * 创建Thread类的子类对象；
   * 通过此对象调用start()，作用一是启动当前线程，作用二是调用当前线程的run()方法。

3. Thread类的有关方法：

   * start()：启动当前线程，调用当前线程的run()；
   * run()：将创建的线程要执行的操作声明在此方法中；
   * currentThread()：静态方法，返回执行当前代码的线程；
   * getName()：获取当前线程的名字；
   * setName()：设置当前线程的名字；
   * yield()：释放当前cpu的执行权，暂停当前线程，让给优先级相同或更高的线程；
   * join()：在线程a中调用线程b的join()，此时线程a进入阻塞状态，直到线程b完全执行完以后，线程a才结束阻塞状态；
   * sleep(long millitime)：睡眠指定的毫秒时间，在指定时间内，当前线程是阻塞状态；
   * isAlive()：当前线程是否存活。

4. java的线程调度方法：

   * 同优先级线程组成先进先出队列，使用时间片策略；
   * 对高优先级，使用优先调度的抢占式策略。

5. 线程优先级：

   * setPriority()：设置优先级；
   * getPriority()：获取当前线程的优先级。

6. 多线程的创建方式二：实现Runnable接口

   * 创建一个实现了Runnable接口的类；
   * 实现类去实现Runnable中的抽象方法；
   * 创建实现类的对象；
   * 将此对象作为参数传递给Thread类的构造器中，创建Thread类的对象；
   * 通过Thread类对象调用start()；
   * 现实中更多使用此方式，没有类的单继承性的局限性，更适合处理多个线程共享数据的情况。

7. java线程分为守护线程和用户线程，守护线程是用来服务用户线程的，通过在start()方法前调用thread.setDaemon(true)来将用户线程切换成守护线程。

8. 线程的生命周期：新建态NEW、就绪态RUNNABLE、运行态Running、阻塞态BLOCKED、死亡态TERMINATED。

   - 新建状态，当程序使用new关键字创建了一个线程之后，该线程就处于新建状态，此时仅由JVM为其分配内存，并初始化其成员变量的值；

   - 就绪状态，当线程对象调用了start()方法之后，该线程处于就绪状态。Java虚拟机会为其创建方法调用栈和程序计数器，等待调度运行；

   - 运行状态，如果处于就绪状态的线程获得了CPU，开始执行run()方法的线程执行体，则该线程处于运行状态；

   - 阻塞状态，当处于运行状态的线程失去所占用资源之后，便进入阻塞状态；

   链接：https://www.cnblogs.com/sunddenly/p/4106562.html

   ![image.png](https://i.loli.net/2021/06/01/swyQg8Ox1kivC4q.png)

9. 线程同步：同步代码块和同步方法。

   * 同步代码块：synchronized(同步监视器){被同步代码}，同步监视器也称同步锁，可以是任何一个类的对象，其中多个线程必须要共用同一把锁，共享数据是指多个线程共同操作的变量；

     ```java
     public void run() {
         while(true){
             synchronized(this) {
                 if (ticket > 0) {
                     try {
                         Thread.sleep(100);
                     } catch (InterruptedException e) {
                         e.printStackTrace();
                     }
     
                     System.out.println(Thread.currentThread().getName() + ": 卖票，票号为： " + ticket);
                     ticket--;
                 } else {
                     break;
                 }
             }
         }
     }
     ```

   * 同步方法：非静态的同步方法同步监视器是this，静态同步方法的是当前类本身。

     ```java
     public void run() {
         while(true){
             show();
         }
     }
     
     public synchronized void show(){
         if (ticket > 0) {
             try {
                 Thread.sleep(100);
             } catch (InterruptedException e) {
                 e.printStackTrace();
             }
     
             System.out.println(Thread.currentThread().getName() + ": 卖票，票号为： " + ticket);
             ticket--;
         }
     }
     ```

10. 死锁：不同线程分别占用对方需要的同步资源不放弃，都在等待对方放弃所需要的同步资源。

    应当尽量减少同步资源的使用和嵌套同步。

11. Lock锁：

    * 实例化ReentrantLock；
    * 调用锁定方法lock()；
    * 调用解锁方法unlock()。

    ```java
    class Window4 implements Runnable {
    
        private int ticket = 100;
    
        // 1.实例化ReentrantLock
        private ReentrantLock lock = new ReentrantLock(true);
    
        @Override
        public void run() {
            while(true){
                try{
                    // 2.调用锁定方法lock()
                    lock.lock();
                    if (ticket > 0) {
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
    
                        System.out.println(Thread.currentThread().getName() + ": 卖票，票号为： " + ticket);
                        ticket--;
                    } else {
                        break;
                    }
                }finally{
                    // 3. 调用解锁方法unlock()
                    lock.unlock();
                }
    
            }
        }
    }
    ```

12. synchronized与lock的区别：

    * 二者都可以解决线程安全问题；
    * synchronized机制在执行完相应的同步代码以后，自动释放同步监听器；Lock需要手动启动同步和结束同步；
    * 实际使用中，lock > 同步代码块 > 同步方法。

13. 线程通信：

    * wait()：一旦执行此方法，当前线程就进入阻塞状态，并释放同步监听器；
    * notify()：唤醒被wait的一个线程，如果有多个线程则唤醒优先级最高的；
    * notifyAll()：唤醒所有被wait的一个线程；
    * 这三个方法必须使用在同步代码块和同步方法中，它们的调用者必须是其中的同步监听器。

    ```java
    class Number implements Runnable{
        private int number = 1;
        private Object obj = new Object();
    
        @Override
        public void run() {
            while(true){
                synchronized(obj){
                    // 唤醒阻塞进程
                    obj.notify();
                    if(number < 100){
                        try {
                            Thread.sleep(10);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        System.out.println(Thread.currentThread().getName() + ": "+number);
                        number++;
    
                        try {
                            // 调用wait()方法使当前线程进入阻塞状态，同时会释放当前锁
                            obj.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }else{
                        break;
                    }
                }
            }
        }
    }
    ```

14. sleep()和wait()的区别：

    * 都可以使当前线程进入阻塞状态；
    * 两个方法声明的位置不同，Thread类中声明sleep()，Object类中声明wait()；
    * 调用的要求不同，前者在任何场景，后者必须在同步代码块或同步方法中；
    * sleep不会释放同步监听器，wait会释放同步监听器。

15. 线程创建的其他方式：

    * 实现Callable接口来创建线程：

      ```java
      public class ThreadNew {
          public static void main(String[] args) {
              // 3.创建Callable接口实现类的对象
              NumberThread numberThread = new NumberThread();
              // 4.将对象传递给FutureTask构造器中，创建对象
              FutureTask<Integer> futureTask = new FutureTask(numberThread);
      
              // 5.将FutureTask对象传递给线程对象
              new Thread(futureTask).start();
      
              try {
                  // 获取call方法中的返回值
                  int sum = futureTask.get();
                  System.out.println("总和为：" + sum);
              } catch (InterruptedException e) {
                  e.printStackTrace();
              } catch (ExecutionException e) {
                  e.printStackTrace();
              }
      
          }
      }
      
      // 1.创建一个实现Callable的类
      class NumberThread implements Callable<Integer> {
          // 2.实现call()方法
          @Override
          public Integer call() throws Exception {
              int sum = 0;
              for (int i = 0; i <= 100; i++) {
                  if(i%2 == 0){
                      System.out.println(i);
                      sum += i;
                  }
              }
              return sum;
          }
      }
      ```

    * 使用线程池创建多个线程，使用时直接获取，使用完放回池中，可以提高响应速度，降低资源消耗，同时便于多个线程的管理。

      ```java
      // 1.提供指定线程数量的线程池
      ExecutorService service  = Executors.newFixedThreadPool(10);
      
      // 2.执行指定线程的操作，需要提供实现Runnable和Callable接口实现类的对象
      service.execute(new NumberThread1());
      service.execute(new NumberThread2());
      // service.submit(); // 适用于Callable
      
      // 3.关闭线程池
      service.shutdown();
      ```

16. 乐观锁与悲观锁的区别：https://www.jianshu.com/p/d2ac26ca6525

#### 五、java常用类

1. String类特性：

   * 声明为final，不可被继承；
   * 实现了Serializable接口，可以支持序列化；
   * 实现了Comparable接口，可以比较大小；
   * 内部定义了final byte[] value，用于存储字符串数据；
   * 代表了不可变的字符序列；

2. 字符串常量存储在字符串常量池中，目的是共享，比如String str = "abc"；字符串非常量对象存储在堆中，比如String str = new String("abc")。

3. String常量与常量的拼接结果在常量池，且常量池不会存在相同内容的常量；只要其中一个是变量，结果就在堆中；如果拼接的结果调用intern()方法，返回值就在常量池中。

4. String常用方法：

   * length()：返回字符串的长度；
   * equalsIgnoreCase()：比较字符串的内容是否相同，忽略大小写；
   * compareTo()：比较两个字符串的大小；
   * substring(int beginIndex, int endIndex)：返回指定的子字符串，不包含endIndex；
   * contains(String str)：是否包含指定的字符串序列；
   * indexOf(String str)：返回子字符串第一次出现的索引号；
   * replace()：字符串替换；
   * match(String regex)：判断字符串是否符合给定的正则表达式；
   * split(String regex)：给定正则表达式来划分字符串；
   * toCharArray()：将字符串转换为char数组；
   * getBytes()：将字符串转换为byte数组。

5. String、StringBuffer与StringBuilder的异同：

   * String表示不可变的字符序列；
   * StringBuffer表示可变的字符序列，是线程安全的，效率较低；
   * StringBuilder表示可变的字符序列，是线程不安全的，效率高；
   * 底层源码分析：StringBuffer底层创建了一个长度是16的数组，如果要添加的数据底层数组范围超出，则需要扩容底层数组，扩容为原来容量的2倍+2，同时将原有数组中的元素复制到新的数组中。

   参考链接：https://www.cnblogs.com/DMingO/p/13407303.html

6. StringBuffer类的常用方法：

   * append()：进行字符串拼接；
   * reverse()：将当前字符串翻转；

7. java对象排序：

   * Comparable接口的使用：自然排序，重写compareTo()方法，来比较两个对象的大小；
   * Comparator接口的使用：定制排序，强行对多个对象进行整体排序的比较；
   * 前者方式一旦指定，保证Comparable接口实习类的对象在任何位置都可以比较大小，Comparator接口属于临时性比较。

   ```java
   public class CompareTest {
   
       @Test
       public void test1(){
           String[] arr = new String[]{"AA", "CC", "KK", "BB", "HH", "LL"};
   
           Arrays.sort(arr);
           System.out.println(Arrays.toString(arr));
       }
   
       @Test
       public void test2(){
           Goods[] arr = new Goods[5];
           arr[0] = new Goods("lenovo", 34);
           arr[1] = new Goods("apple", 54);
           arr[2] = new Goods("google", 78);
           arr[3] = new Goods("facebook", 65);
           arr[4] = new Goods("tencent", 65);
   
           Arrays.sort(arr);
   
           System.out.println(Arrays.toString(arr));
       }
   
       @Test
       public void test3(){
           String[] arr = new String[]{"AA", "CC", "KK", "BB", "HH", "LL"};
           Arrays.sort(arr, new Comparator(){
               @Override
               public int compare(Object o1, Object o2) {
                   if(o1 instanceof String && o2 instanceof String){
                       String s1 = (String) o1;
                       String s2 = (String) o2;
                       return -s1.compareTo(s2);
                   }
                   throw new RuntimeException("数据类型不一致");
               }
           });
           System.out.println(Arrays.toString(arr));
       }
   
       @Test
       public void test4(){
           Goods[] arr = new Goods[5];
           arr[0] = new Goods("lenovo", 34);
           arr[1] = new Goods("apple", 54);
           arr[2] = new Goods("google", 78);
           arr[3] = new Goods("facebook", 65);
           arr[4] = new Goods("tencent", 65);
   
           Arrays.sort(arr, new Comparator(){
               @Override
               public int compare(Object o1, Object o2) {
                   if(o1 instanceof Goods && o2 instanceof Goods){
                       Goods g1 = (Goods) o1;
                       Goods g2 = (Goods) o2;
                       if(g1.getName().equals(g2.getName())){
                           return -Double.compare(g1.getPrice(), g2.getPrice());
                       }else{
                           return g1.getName().compareTo(g2.getName());
                       }
                   }
                   throw new RuntimeException("数据类型不一致");
               }
           });
   
           System.out.println(Arrays.toString(arr));
       }
   }
   
   class Goods implements Comparable{
       private String name;
       private double price;
   
       public Goods() {
       }
   
       public Goods(String name, double price) {
           this.name = name;
           this.price = price;
       }
   
       public String getName() {
           return name;
       }
   
       public void setName(String name) {
           this.name = name;
       }
   
       public double getPrice() {
           return price;
       }
   
       public void setPrice(double price) {
           this.price = price;
       }
   
       @Override
       public String toString() {
           return "Goods{" +
                   "name='" + name + '\'' +
                   ", price=" + price +
                   '}';
       }
   
       @Override
       public int compareTo(Object o) {
           if(o instanceof Goods){
               Goods goods = (Goods)o;
               if(this.price > goods.price){
                   return 1;
               }else if(this.price < goods.price){
                   return -1;
               }else{
   //                return 0;
                   return -this.name.compareTo(goods.name);
               }
   
   //            return Double.compare(this.price, goods.price);
           }
           throw new RuntimeException("传入数据类型不一致");
       }
   }
   ```

8. BigInteger/BigDecimal：表示不可变的任意精度的整数或浮点数。

   * add()：两数相加；
   * subtract()：两数相减；
   * multiply()：两数相乘；
   * divide()：两数相除；
   * remainder()：求余。

#### 六、枚举类与注解

1. 枚举类：类的对象只有有限个并且确定的，当需要定义一组常量时，建议使用枚举类。如果枚举类只有一个对象，则可以作为单例模式的实现方式。

2. 枚举类的定义：

   * jdk5.0之前，自定义枚举类；

     ```java
     //自定义枚举类
     class Season {
         // 1.声明Season对象的属性
         private final String seasonName;
         private final String seasonDesc;
     
         // 2.私有化类的构造器
         private Season(String seasonName, String seasonDesc) {
             this.seasonName = seasonName;
             this.seasonDesc = seasonDesc;
         }
     
         // 3.提供当前枚举类的多个对象
         public static final Season SPRING = new Season("春天", "春暖花开");
         public static final Season SUMMER = new Season("夏天", "春暖花开");
         public static final Season AUTUMN = new Season("秋天", "春暖花开");
         public static final Season WINTER = new Season("冬天", "春暖花开");
     
         public String getSeasonName() {
             return seasonName;
         }
     
         public String getSeasonDesc() {
             return seasonDesc;
         }
     
         @Override
         public String toString() {
             return "Season{" +
                     "seasonName='" + seasonName + '\'' +
                     ", seasonDesc='" + seasonDesc + '\'' +
                     '}';
         }
     }
     ```

   * jdk5.0时，可以使用enum关键字自定义枚举类。

     ```java
     // enum枚举类
     enum Season1{
     
         // 1.提供当前枚举类的多个对象
         SPRING("春天", "春暖花开"),
         SUMMER("夏天", "夏日炎炎"),
         AUTUMN("秋天", "秋高气爽"),
         WINTER("冬天", "冰天雪地");
     
         // 2.声明Season对象的属性
         private final String seasonName;
         private final String seasonDesc;
     
         // 3.私有化类的构造器
         private Season1(String seasonName, String seasonDesc) {
             this.seasonName = seasonName;
             this.seasonDesc = seasonDesc;
         }
     
     
         public String getSeasonName() {
             return seasonName;
         }
     
         public String getSeasonDesc() {
             return seasonDesc;
         }
     }
     ```

3. 注解（Annotation）：用于修饰包、类、构造器、方法、成员变量、参数、局部变量的声明。框架=注解+反射+设计模式。

4. 注解用法：

   * 生成文档相关注解；
   * 在编译时进行格式检查；
   * 跟踪代码依赖性，实现替代配置文件功能。

5. 自定义注解使用@interface关键字，其成员变量以无参数方法的形式来声明，方法名和返回值定义了该成员的名字和类型。可以指定成员的默认值，使用default定义。

6. 元注解：用于修饰其他注解定义，包括Retention, Target, Documented, Inherited。

   * Retention：指定所修饰的注解生命周期，SOURCE/CLASS(默认行为)/RUNTIME，只有声明为RUNTIME的注解，才能通过反射获取；
   * Target：用于指定被修饰的注解能用于修饰哪些程序元素；
   * Documented：用于指定被修饰的注解类将被javadoc解析时，保留下来；
   * Inherited：被它修饰的注解具有继承性。

7. 可重复注解：在基本注解MyAnnotation上声明@Repeatable(MyAnnotations.class)，两者的元注解要相同。

8. 类型注解：ElementType.TYPE_PARAMETER表示该注解能写在类型变量的声明语句中（如泛型），TYPE_USE表示该注解能写在使用类型的任何语句中。

   ```java
   @Inherited
   @Repeatable(MyAnnotations.class)
   @Target({TYPE, FIELD, METHOD, PARAMETER, CONSTRUCTOR, LOCAL_VARIABLE, MODULE, TYPE_PARAMETER, TYPE_USE})
   @Retention(RetentionPolicy.RUNTIME)
   public @interface MyAnnotation {
   
       String value() default "hello";
   }
   @Inherited
   @Target({TYPE, FIELD, METHOD, PARAMETER, CONSTRUCTOR, LOCAL_VARIABLE, MODULE})
   @Retention(RetentionPolicy.RUNTIME)
   public @interface MyAnnotations {
       MyAnnotation[] value();
   }
   ```

#### 七、集合

1. 集合框架分为Collection接口和Map接口；

   * Collection接口：单列集合，用来存储一个个对象。
     * List接口：存储有序的、可重复的数据，包括ArrayList、LinkedList、Vector；
     * Set接口：存储无序的、不可重复的数据，包括HashSet、LinkedHashSet、TreeSet。这里的无序不等于随机性，是存储无序性，存储时根据对象hash值进行存储。不可重复性保证添加的元素按照equals()方法判断时，不能返回true。
   * Map接口：双列集合，用来存储一对（key-value）数据，包括HashMap、LinkedHashMap、TreeMap、Hashtable、Properties。

   ![img](https://user-gold-cdn.xitu.io/2019/10/14/16dc8ee74157e0ab?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

   ![img](https://user-gold-cdn.xitu.io/2019/10/14/16dc8ee741612be7?imageView2/0/w/1280/h/960/format/webp/ignore-error/1)

2. Collection接口的相关方法：

   * add()/addAll()方法：添加元素到集合中；
   * remove()/removeAll()方法：删除集合中的指定元素；
   * contains()/containsAll()方法：集合中是否包含指定元素；
   * size()：获取集合中的元素数量；
   * retainAll()：获取当前集合和指定集合的交集，并返回给当前集合；
   * toArray()：集合转成对象数组；
   * clear()：清空当前集合所有元素；
   * isEmpty()：判断当前集合是否为空。

3. 集合迭代器接口：

   ```java
   Iterator iterator = collection.iterator();
   // hasNext(): 判断当前集合是否还有下一个元素
   while(iterator.hasNext()){
       // next(): 指针下移，将下移以后集合位置上的元素返回
       System.out.println(iterator.next());
   }
   ```

4. ArrayList、LinkedList和Vecotr的异同：

   * 相同点是三个类都实现了List接口，存储数据有序且可重复；
   * ArrayList是线程不安全的，但执行效率高，底层使用object[]存储;
   * LinkedList底层使用双向链表存储，适合频繁的插入、删除操作；
   * Vector是线程安全的，执行效率低，底层使用object[]存储；

5. ArrayList源码分析：

   ```java
   /**
    * 底层创建了Object[]数组elementData，初始化为{}, 并没有创建长度为10的数组
    *
    * transient Object[] elementData;
    * public ArrayList() {
    *    this.elementData = DEFAULTCAPACITY_EMPTY_ELEMENTDATA;
    * }
    */
   ArrayList list = new ArrayList();
   
   /**
    * 第一次调用add()时，底层才创建了长度为10的数组
    * 当添加元素之后底层elementData数组容量不够，则进行扩容。默认情况下
    * 扩容为原来容量的1.5倍，同时将原有数组数据复制到新的数组中
    *
    * private Object[] grow(int minCapacity) {
    *     int oldCapacity = elementData.length;
    *     if (oldCapacity > 0 || elementData != DEFAULTCAPACITY_EMPTY_ELEMENTDATA) {
    *         int newCapacity = ArraysSupport.newLength(oldCapacity,
    *                 minCapacity - oldCapacity, // minimum growth
    *                 oldCapacity >> 1           // preferred growth);
    *         return elementData = Arrays.copyOf(elementData, newCapacity);
    *     } else {
    *         return elementData = new Object[Math.max(DEFAULT_CAPACITY, minCapacity)];
    *     }
    * }
    */
   list.add(123);
   ```

6. LinkedList源码分析：

   * 初始化：内部声明了Node类型的first和last属性；

   * 底层链表节点组成：

     ```java
     private static class Node<E> {
         E item;
         Node<E> next;
         Node<E> prev;
     
         Node(Node<E> prev, E element, Node<E> next) {
             this.item = element;
             this.next = next;
             this.prev = prev;
         }
     }
     ```

   * 添加元素：

     ```java
     void linkLast(E e) {
         final Node<E> l = last;
         final Node<E> newNode = new Node<>(l, e, null);
         last = newNode;
         if (l == null)
             first = newNode;
         else
             l.next = newNode;
         size++;
         modCount++;
     }
     ```

7. Vector源码分析：初始化为容量10的数组，在扩容方面默认扩容为原来数组长度的2倍。

8. List中remove(int index)和remove(Object obj)的区别：

   ```java
   list.remove(Integer.valueOf(1)); // 将基本类型数据转换成包装类调用
   list.remove(1);
   ```

9. HashSet、LinkedHashSet和TreeSet的区别：

   * HashSet作为Set接口的主要实现类，其线程不安全，可以存储null值；
   * LinkedHashSet作为HashSet的子类，遍历其内部数据时，可以按照添加的顺序遍历；
   * TreeSet可以按照添加对象的指定属性进行排序。

10. HashSet添加元素a过程：

    * 调用元素a所在类的hashCode()方法，计算元素a的哈希值；
    * 此哈希值通过某种算法计算出在HashSet底层数组中的存放位置；
    * 如果此位置上没有其他元素，则元素a添加成功；
    * 如果此位置上有其他元素b（或以链表形式存储的多个元素），则比较元素a与元素b的hash值；
      *  如果hash值不相同，则元素a添加成功；
      * 如果hash值相同，则需要调用元素a所在类的equals()方法；
        * 如果返回true，则元素a添加失败；
        * 如果返回false，则元素a添加成功。
    * 对于jdk7，元素a放到数组中，指向原来的元素，对于jdk8，原来元素在数组中，指向元素a。

11. HashSet底层结构为==数组+链表==的形式（**jdk7**），并且添加元素所在的类一定要重写hashCode()和equals()，两者尽可能保持一致性。

12. LinkedHashSet在添加数据的同时，每个数据还维护了两个引用，记录了此数据的前后数据，适合频繁的遍历操作。

13. TreeSet添加的数据要求是相同类对象，不能添加不同类对象。TreeSet在存储元素（自然排序）时调用的不是equals()而是compareTo()。

14. HashMap、LinkedHashMap、TreeMap、Hashtable、Properties区别：

    * HashMap作为Map的主要实现类，其线程不安全，执行效率高，可以存储null的key和value；
      * LinkedHashMap是HashMap的子类，保证在遍历map元素时，可以按照添加的顺序实现遍历，主要在原有HashMap底层结构基础上添加了一对指针，指向前一个和后一个数据元素。主要用于频繁的遍历操作。
    * TreeMap保证按照key-value对进行排序，实现排序遍历，考虑key的排序，其底层结构使用**红黑树**；
    * Hashtable是过去的实现类，其线程安全，效率低，不能存储null的key和value；
      * Properties常用来处理配置文件，其key和value是String类型。

15. Map结构：

    * key是无序、不可重复的，使用set存储所有key，key所在类需要重写equals()和hashCode()；
    * value是无序、可重复的，使用Collection存储所有value，其所在类需要重写equals()。

16. HashMap的底层实现原理：

    * jdk7：

      ```java
      /**
       * 实例化以后，底层创建了长度为16的一维数组Entry[] table
       */
      HashMap map = new HashMap();
      
      /**
       * 调用key1所在类的hashCode()方法，计算key1的哈希值；
       * * 此哈希值通过某种算法计算出在Entry数组中的存放位置；
       * * 如果此位置上的数据为空，则key1-value1添加成功；（情况1）
       * * 如果此位置上的数据不为空（或以链表形式存储的多个元素），则比较key1与其他数据的hash值；
       *   *  如果hash值不相同，则key1-value1添加成功；（情况2）
       *   * 如果hash值与某个数据key2-value2的hash值相同，则需要调用key1所在类的equals()方法；
       *     * 如果返回false，则key1-value1添加成功；（情况3——
       *     * 如果返回true，则使用value1替换value2。
       *
       * 情况二和三下key1-value1和原来数据都以链表的形式存储
       */
      map.put(key1, value1);
      
      /**
       * 扩容：默认扩容方式为扩容为原来容量的2倍，并将原有的数据复制过来（超出临界值并且要存放的位置非空）
       */
      ```

    * jdk8：

      ```java
      // 初始化时创建一个加载因子0.75，并没有创建数组
      public HashMap() {
          this.loadFactor = DEFAULT_LOAD_FACTOR; // all other fields defaulted
      }
      
      // 添加数据到HashMap中
      final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
                     boolean evict) {
          Node<K,V>[] tab; Node<K,V> p; int n, i;
          // 判断是否为首次添加数据，如果首次添加数据，则新建一个长度为16的Node数组
          if ((tab = table) == null || (n = tab.length) == 0)
              n = (tab = resize()).length;
          // 根据key的hash值计算获取该key的存储位置((n-1) & hash)，如果当前位置为空，则直接添加数据
          if ((p = tab[i = (n - 1) & hash]) == null)
              tab[i] = newNode(hash, key, value, null);
          else {
              Node<K,V> e; K k;
              // 如果该存放位置的当前节点hash值与key的hash值相同，并且其key值也相同，则替换对应value值
              if (p.hash == hash &&
                  ((k = p.key) == key || (key != null && key.equals(k))))
                  e = p;
              // 判断p是否为TreeNode，
              else if (p instanceof TreeNode)
                  e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value);
              else {
                  for (int binCount = 0; ; ++binCount) {
                      // 判断p的下一个节点是否为空，如果为空则直接添加数据节点值
                      if ((e = p.next) == null) {
                          p.next = newNode(hash, key, value, null);
                          // 当当前链表节点数量大于8时，判断是否将链表转成红黑树
                          if (binCount >= TREEIFY_THRESHOLD - 1) // -1 for 1st
                              treeifyBin(tab, hash);
                          break;
                      }
                      // 继续判断当前节点的hash值是否与key的hash相同，并且内容也相同，都相同的话替换对应value值
                      if (e.hash == hash &&
                          ((k = e.key) == key || (key != null && key.equals(k))))
                          break;
                      p = e;
                  }
              }
              if (e != null) { // existing mapping for key
                  V oldValue = e.value;
                  if (!onlyIfAbsent || oldValue == null)
                      e.value = value;
                  afterNodeAccess(e);
                  return oldValue;
              }
          }
          ++modCount;
          if (++size > threshold)
              resize();
          afterNodeInsertion(evict);
          return null;
      }
      
      // 链表转红黑树
      final void treeifyBin(Node<K,V>[] tab, int hash) {
              int n, index; Node<K,V> e;
          	// 如果当前数组长度<64,则进行扩容
              if (tab == null || (n = tab.length) < MIN_TREEIFY_CAPACITY)
                  resize();
              // 如果数组当前位置不为空，则将链表转成红黑树
              else if ((e = tab[index = (n - 1) & hash]) != null) {
                  TreeNode<K,V> hd = null, tl = null;
                  do {
                      TreeNode<K,V> p = replacementTreeNode(e, null);
                      if (tl == null)
                          hd = p;
                      else {
                          p.prev = tl;
                          tl.next = p;
                      }
                      tl = p;
                  } while ((e = e.next) != null);
                  if ((tab[index] = hd) != null)
                      hd.treeify(tab);
              }
          }
      ```

    * jdk8和jdk7区别：

      * new HashMap()底层没有创建一个长度为16的数组；
      * 其底层数组是Node[]，而不是Entry[]；
      * 首此调用put()方法时，底层创建长度为16的数组；
      * jdk7底层结构只有数组+链表，jdk8底层结构为数组+链表+红黑树，当数组的某一个索引位置上元素以链表形式存在的数据个数>8并且当前数组长度>64时，此索引位置上的所有数据改为使用红黑树存储，目的是减少比较不同数据hash值的时间。

    * 底层构造默认值：

      * DEFAULT_INITIAL_CAPACITY：HashMap的默认容量16；
      * DEFAULT_LOAD_FACTOR：默认加载因子0.75；
      * threshold：扩容临界值=容量*加载因子=16\*0.75=12；
      * TREEIFY_THRESHOLD：Bucket中链表长度大于该默认值，则转化为红黑树，默认值8；
      * MIN_TREEIFY_CAPACITY：桶中的Node转红黑树时最新的hash表容量，默认64。

17. 加载因子大小对HashMap的影响：

    * 其大小决定了HashMap的数据密度；
    * 加载因子较大则发生碰撞的积累较高，较小则会浪费一定的内存空间。

18. LinkedHashMap的底层实现结构：

    ```java
    // 继承了HashMap的Node，同时添加了before和after对象引用，记录了添加前后数据的顺序
    static class Entry<K,V> extends HashMap.Node<K,V> {
        Entry<K,V> before, after;
        Entry(int hash, K key, V value, Node<K,V> next) {
            super(hash, key, value, next);
        }
    }
    ```

19. Map集合遍历：

    ```java
    // 遍历所有的key集合：keySet()
    Set keySet = map.keySet();
    Iterator iter = keySet.iterator();
    
    while(iter.hasNext()){
        System.out.println(iter.next());
    }
    
    //遍历所有的value集合：values()
    Collection values = map.values();
    System.out.println(values);
    
    //遍历所有的key-value：entrySet()
    Set set = map.entrySet();
    Iterator iter1 = set.iterator();
    while(iter1.hasNext()){
        Map.Entry entry = (Map.Entry) iter1.next();
        System.out.println(entry.getKey() + "---->" +entry.getValue());
    }
    ```

20. Collections工具类：是一个操作Set、List和Map的工具类。

    * reverse(List)：反转list中元素顺序；
    * shuffle(List)：对list集合元素进行随机排序；
    * sort(List)：根据元素的自然顺序对指定list集合元素升序排序；
    * swap(List, int, int)：将指定list集合中的i处元素和j处元素交换；
    * void copy(List dest, List src)：将src中的内容复制到dest中，这里dest集合大小必须大于src，List dest = Arrays.asList(new Object[list.size()]);
    * synchronizedList(List)：转成线程安全集合。

#### 八、泛型与IO流

1. 集合中使用泛型：

   * 在实例化集合类时，可以指明具体的泛型类型；
   * 泛型的类型必须是类，不能是基本数据类型，可以使用包装类替换；
   * 如果实例化没有指明类的泛型，则默认为Object类型。

2. 自定义泛型结构：泛型类、泛型结构、泛型方法。

   * 子类在继承带泛型的父类时，指明了泛型类型，则实例化子类对象时，不需要指明泛型；

   * 泛型不同的引用不能相互赋值；

     ```java
     ArrayList<String> list1 = null;
     ArrayList<Integer> list2 = new ArrayList<Integer>();
     list1 = list2; // 报错
     ```

   * **静态方法**和**异常类**不能使用类的泛型；

   * 泛型方法：在方法中出现泛型结构，与类的泛型参数没有任何关系，泛型方法所属的类是不是泛型类都没有关系，同时泛型方法可以声明为静态，其中泛型参数在调用时被确定的。

3. 有限制条件通配符？的使用：

   ```java
   // ? extends 可以作为Person和其子类的父类来使用，即<=Person
   List<? extends Person> list1 = null;
   // list1.add(new Student());
   // ? super Person 可以作为Person和其父类的父类来使用，即>=Person
   List<? super Person> list2 = null;
   list2.add(new Person());
   
   List<Student> list3 = null;
   List<Person> list4 = null;
   List<Object> list5 = null;
   
   list1 = list3;
   list1 = list4;
   // list1 = list5;
   
   // list2 = list3;
   list2 = list4;
   list2 = list5;
   
   list1 = list3;
   Person p = list1.get(0);
   // Student s = list1.get(0);
   
   list2 = list4;
   Object obj = list2.get(0);
   // Person p1 = list2.get(0);
   ```

4. IO流：

   * 抽象基类：字节流（InputStream\OutputStream），字符流（Reader\Writer）；
   * 节点流（文件流）: FileInPutStream\FileOutputStream\FileReader\FileWriter；
   * 缓冲流：BufferedInPutStream\BufferedOutputStream\BufferedReader\BufferedWriter。

5. IO流实例：

   ```java
   BufferedInputStream bis = null;
   BufferedOutputStream bos = null;
   try {
       File srcFile = new File("test.jpg");
       File destFile = new File("test1.jpg");
   
       FileInputStream fis = new FileInputStream(srcFile);
       FileOutputStream fos = new FileOutputStream(destFile);
   
       bis = new BufferedInputStream(fis);
       bos = new BufferedOutputStream(fos);
   
       byte[] buffer = new byte[1024];
       int len;
       while((len = bis.read(buffer)) != -1){
           bos.write(buffer);
           bos.flush(); // 刷新缓冲区
       }
   } catch (IOException e) {
       e.printStackTrace();
   } finally {
       // 先关闭外层流，再关闭内层流，但关闭外层流会自动关闭内层流
       try {
           if(bos!=null){
               bos.close();
           }
       } catch (IOException e) {
           e.printStackTrace();
       }
   
       try {
           if (bis!=null) {
               bis.close();
           }
       } catch (IOException e) {
           e.printStackTrace();
       }
   }
   ```

6. 转换流：属于字符流，提供字节流与字符流之间的转换。其中InputStreamReader将一个字节的输入流转换为字符的输入流，OutputStreamWriter将一个字符的输出流转换为字节的输出流。

   ```java
   FileInputStream fis = new FileInputStream("hello.txt");
   InputStreamReader isr = new InputStreamReader(fis, "UTF-8");
   
   FileOutputStream fos = new FileOutputStream("hello3.txt");
   OutputStreamWriter osw = new OutputStreamWriter(fos, "GBK");
   
   char[] cbuf = new char[5];
   int len;
   while((len = isr.read(cbuf)) != -1){
       osw.write(cbuf, 0, len);
   }
   osw.close();
   isr.close();
   ```

7. 对象流：用于存储和读取基本数据类型数据或对象的处理流，可以将java中的对象写入到数据源中，也能把对象从数据源中还原出来。

   * 序列化：用ObjectOutputStream类保存基本类型数据或对象的机制；
   * 反序列化：用ObjectInputStream类读取基本类型数据或对象的机制；
   * 对象序列化机制：允许把内存中的java对象转换成平台无关的二进制流；
   * java对象可序列化需要满足的要求：
     * 实现接口Serializable；
     * 当前类提供一个全局常量serialVersionUID，用来表明类的不同版本兼容性；
     * 除了当前类需要实现接口之外，还必须保证类内所有属性也是可序列化的（默认情况下基本类型数据以及String天然可序列化）。

   ```java
   public class ObjectTest {
       
       @Test
       public void test1(){
           ObjectOutputStream oos = null;
           try {
               oos = new ObjectOutputStream(new FileOutputStream("object.txt"));
               oos.writeObject(new String("爱我中华"));
               oos.flush();
   
               oos.writeObject(new Person("Tom", 15));
               oos.flush();
           } catch (IOException e) {
               e.printStackTrace();
           } finally {
               if(oos!=null){
                   try {
                       oos.close();
                   } catch (IOException e) {
                       e.printStackTrace();
                   }
               }
           }
       }
   
       @Test
       public void test2(){
           ObjectInputStream ois = null;
           try {
               ois = new ObjectInputStream(new FileInputStream("object.txt"));
               Object obj = ois.readObject();
               String str = (String) obj;
               Person p = (Person) (ois.readObject());
               System.out.println(str);
               System.out.println(p);
           } catch (IOException | ClassNotFoundException e) {
               e.printStackTrace();
           } finally {
               if(ois!=null){
                   try {
                       ois.close();
                   } catch (IOException e) {
                       e.printStackTrace();
                   }
               }
           }
       }
   }
   ```

8. NIO：支持面向缓冲区、基于通道的非阻塞IO操作。

#### 九、网络编程

1. TCP通信：

   ```java
   public void client(){
       Socket socket = null;
       OutputStream os = null;
       FileInputStream fis = null;
   
       InputStream is = null;
       ByteArrayOutputStream baos = null;
       try {
   
           InetAddress inet = InetAddress.getByName("localhost");
           socket = new Socket(inet, 8989);
   
           os = socket.getOutputStream();
           fis = new FileInputStream("test1.jpg");
           int len;
           byte[] buffer = new byte[1024];
           while((len=fis.read(buffer))!=-1){
               os.write(buffer, 0, len);
           }
   
           // 关闭客户端输出流
           socket.shutdownOutput();
   
           is = socket.getInputStream();
           baos = new ByteArrayOutputStream();
           byte[] buffer1 = new byte[20];
           int len1;
           while((len1=is.read(buffer1))!=-1){
               baos.write(buffer1, 0, len1);
           }
           System.out.println(baos.toString());
   
       } catch (IOException e) {
           e.printStackTrace();
       } finally {
           if(baos != null){
               try {
                   baos.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
           if (is != null){
               try {
                   is.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
           if(os!=null){
               try {
                   os.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
           if(socket!=null){
               try {
                   socket.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
       }
   }
   
   @Test
   public void server(){
       ServerSocket ss = null;
       Socket socket = null;
       InputStream is = null;
       FileOutputStream fos = null;
       OutputStream os = null;
       try {
           // 1.创建服务器端的ServerSocket，指明端口号
           ss = new ServerSocket(8989);
           // 2.调用accept()表示接收来自于客户端的socket
           socket = ss.accept();
           // 3.获取输入流
           is = socket.getInputStream();
   
           fos = new FileOutputStream("test2.jpg");
   
           byte[] buffer = new byte[1024];
           int len;
           while((len=is.read(buffer))!=-1){
               fos.write(buffer, 0, len);
           }
   
           os = socket.getOutputStream();
           os.write("你好，我已经接收到该消息".getBytes());
   
           System.out.println("收到了来自于："+socket.getInetAddress().getHostAddress());
       } catch (IOException e) {
           e.printStackTrace();
       } finally {
           if(fos!=null){
               try {
                   fos.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
           if (is != null){
               try {
                   is.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
           if (socket!=null){
               try {
                   socket.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
           if(ss!=null){
               try {
                   ss.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
           if(os!=null){
               try {
                   os.close();
               } catch (IOException e) {
                   e.printStackTrace();
               }
           }
       }
   
   }
   ```

2. UDP通信：

   ```java
   @Test
   public void sender() throws IOException {
       DatagramSocket socket = new DatagramSocket();
   
       String str = "UDP 测试";
       byte[] data = str.getBytes();
       InetAddress inet = InetAddress.getLocalHost();
       DatagramPacket pcaket = new DatagramPacket(data, 0, data.length, inet, 9090);
   
       socket.send(pcaket);
       socket.close();
   }
   
   @Test
   public void receiver() throws IOException {
       DatagramSocket socket = new DatagramSocket(9090);
   
       byte[] data = new byte[100];
       DatagramPacket packet = new DatagramPacket(data, 0, data.length);
       socket.receive(packet);
   
       System.out.println(new String(packet.getData(), 0, packet.getLength()));
   
       socket.close();
   }
   ```

3. URL(Uniform Resource Locator)：统一资源定位符，是一种具体的URI，对应着互联网的某一资源地址，其格式为：协议+主机名+端口号+资源地址+参数列表。

#### 十、反射机制

1. 反射(Reflection)：允许程序在**执行**期间借助于Reflection API获取任何类的内部信息，并能直接操作任意对象的内部属性及方法，是**动态语言**的关键。反射方式是实例化对象->getClass()方法->得到完整的包类结构。

2. 反射示例：

   ```java
   public class ReflectionTest {
   
       // 反射之前的类操作
       @Test
       public void test1(){
           // 1.创建类对象
           Person p = new Person("Tom", 12);
   
           // 2.通过对象，调用其内部属性、方法
           p.age = 15;
           System.out.println(p.toString());
   
           p.show();
       }
   
       // 反射之后的类操作
       @Test
       public void test2() throws Exception {
   
           // 1.通过反射创建类对象
           Class clazz = Person.class;
           Constructor cons = clazz.getConstructor(String.class, int.class);
   
           Object obj = cons.newInstance("Tom", 12);
           Person p = (Person) obj;
           System.out.println(p.toString());
   
           // 2.通过反射，调用对象指定属性和方法
           Field age = clazz.getDeclaredField("age");
           age.set(p, 10);
           System.out.println(p.toString());
   
           Method show = clazz.getDeclaredMethod("show");
           show.invoke(p);
   
           // 通过反射，可以调用类的私有结构
           Constructor cons1 = clazz.getDeclaredConstructor(String.class);
           cons1.setAccessible(true);
           Person p1 = (Person) cons1.newInstance("Jerry");
           System.out.println(p1);
   
           // 调用私有属性
           Field name = clazz.getDeclaredField("name");
           name.setAccessible(true);
           name.set(p1, "Lily");
           System.out.println(p1);
   
           // 调用私有方法
           Method showNation = clazz.getDeclaredMethod("showNation", String.class);
           showNation.setAccessible(true);
           String nation = (String)showNation.invoke(p1, "中国");
           System.out.println(nation);
   
       }
   }
   ```

3. 反射机制与封装性的理解：

   * 封装性表示建议使用者如何调用方法；
   * 反射机制表示能不能调用方法。

4. 反射的使用场景：

5. Class类的理解：

   * 类的加载过程：源代码经过javac.exe命令编译生成字节码(.class)文件，接着使用java.exe命令对某个字节码文件进行解释运行，相当于将某个字节码文件加载到内存中（类的加载），加载到**内存中的类**称为运行时类，它作为Class的一个实例；
     * 类的加载（Load）：将class文件字节码内容加载到内存中，并将这些静态数据转换成方法区的运行时数据结构，然后生成一个代表这个类的Class对象，作为方法区中类数据的访问入口；
     *  类的链接（Link）：将Java类的二进制代码合并到JVM的运行状态之中的过程；
     *  类的初始化（Initialize)：执行类构造器方法的过程。
   * ==Class的实例就对应着一个运行时类==；
   * 加载到内存中的运行时类，会缓存一定时间，可以通过不同方式获取此运行时类；
   * 只要数组的类型和维度相同，就可以认为是同一个Class。

   ```java
   // 方式一：调用运行时类的属性.class
   Class<Person> clazz1 = Person.class;
   
   // 方式二：通过运行时类的对象，调用getClass()
   Person p = new Person();
   Class clazz2 = p.getClass();
   
   // 方式三：调用Class的静态方法，forName(String classPath)，使用较多
   Class clazz3 = Class.forName("exercise6.Person");
   
   // 方式四：使用类的加载器ClassLoader，了解
   ClassLoader classLoader = ReflectionTest.class.getClassLoader();
   Class clazz4 = classLoader.loadClass("exercise6.Person");
   ```

6. 类加载器ClassLoader：用来把类class装载进内存。

   * BootstrapClassLoader（启动类加载器）：`c++`编写，加载`java`核心库 `java.*`,构造`ExtClassLoader`和`AppClassLoader`。由于引导类加载器涉及到虚拟机本地实现细节，开发者无法直接获取到启动类加载器的引用，所以不允许直接通过引用进行操作

   * ExtClassLoader （标准扩展类加载器）：`java`编写，加载扩展库，如`classpath`中的`jre` ，`javax.*`或者
      `java.ext.dir` 指定位置中的类，开发者可以直接使用标准扩展类加载器。

   * AppClassLoader（系统类加载器）：`java`编写，加载程序所在的目录，如`user.dir`所在的位置的`class

   * CustomClassLoader（用户自定义类加载器）：`java`编写,用户自定义的类加载器,可加载指定路径的`class`文件

   ```java
   // 系统类加载器
   ClassLoader classLoader = ReflectionTest.class.getClassLoader();
   System.out.println(classLoader);
   // 扩展类加载器
   ClassLoader classLoader1 = classLoader.getParent();
   System.out.println(classLoader1);
   // 引导类加载器，负责java的核心类库，无法加载自定义类
   ClassLoader classLoader2 = classLoader1.getParent();
   System.out.println(classLoader2);
   
   ClassLoader classLoader3 = String.class.getClassLoader();
   System.out.println(classLoader3);
   ```


   链接：https://www.jianshu.com/p/1e4011617650

7. 创建运行时类对象：

   * newInstance()创建对应的运行时类的对象，内部调用了运行时类的空参构造器。在javabean中要求提供一个public的空参构造器，便于通过反射创建运行时类对象，也便于子类继承此运行时类时，默认调用super()时，保证父类有此构造器。

     ```java
     Class<Person> clazz = Person.class;
     Person obj = clazz.newInstance();
     System.out.println(obj);
     ```

8. 调用运行时类的指定结构：

   * 调用运行类属性：

     ```java
     Class clazz = Person1.class;
     // 创建运行时类对象
     Person1 p = (Person1) clazz.newInstance();
     // 获取指定属性
     Field name = clazz.getDeclaredField("name");
     // 保证当前属性可访问
     name.setAccessible(true);
     name.set(p, "Tom");
     String pName = (String) name.get(p);
     System.out.println(pName);
     ```

   * 调用运行类方法：

     ```java
     Class clazz = Person1.class;
     // 创建运行时类对象
     Person1 p = (Person1) clazz.newInstance();
     
     // 获取指定方法
     Method show = clazz.getDeclaredMethod("show", String.class);
     show.setAccessible(true);
     // 调用运行时类的方法
     Object returnValue = show.invoke(p,"中国");
     
     System.out.println(returnValue);
     
     Method showInfo = clazz.getDeclaredMethod("showInfo");
     showInfo.setAccessible(true);
     // 静态方法对象可以设置为null
     showInfo.invoke(null);
     ```

9. 动态代理：客户通过代理类来调用其他对象的方法，并且是在程序运行时根据需要动态创建目标类的代理对象。

   ```java
   interface Human{
       String getBelief();
   
       void eat(String food);
   }
   
   // 被代理类
   class SuperMan implements Human{
       @Override
       public String getBelief() {
           return "I believe I can fly";
       }
   
       @Override
       public void eat(String food) {
           System.out.println("food = " + food);
       }
   }
   
   class MyInvocationHandler implements InvocationHandler{
   
       // 被代理类
       private Object obj;
   
       public void bind(Object obj){
           this.obj = obj;
       }
   
       // 当我们通过代理类的对象，调用方法时，就会自动调用下面方法invoke()
       // 将被代理类要执行的方法功能声明在invoke()中
       @Override
       public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
           Object returnValue = method.invoke(obj, args);
   
           return returnValue;
       }
   }
   
   class ProxyFactory{
   
       /**
        * @param obj 被代理类对象
        * @return 返回一个代理类的对象
        */
       public static Object getProxyInstance(Object obj){
           MyInvocationHandler handler = new MyInvocationHandler();
           handler.bind(obj);
           Object instance = Proxy.newProxyInstance(obj.getClass().getClassLoader(), obj.getClass().getInterfaces(), handler);
           return instance;
       }
   }
   
   public class ProxyTest {
       public static void main(String[] args) {
           SuperMan superMan = new SuperMan();
   
           // 生成一个代理类对象
           Human proxyInstance = (Human) ProxyFactory.getProxyInstance(superMan);
           System.out.println(proxyInstance.getBelief());
           proxyInstance.eat("川菜");
   
           NikeClothFactory nikeClothFactory = new NikeClothFactory();
           ClothFactory clothFactory = (ClothFactory) ProxyFactory.getProxyInstance(nikeClothFactory);
           clothFactory.produceCloth();
       }
   }
   ```


#### java内存与垃圾回收机制

1. 内存泄漏与内存溢出的区别：

   内存泄露本意是申请的内存空间没有被正确释放，导致后续程序里这块内存被永远占用（不可达），而且指向这块内存空间的指针不再存在时，这块内存也就永远不可达了。简而言之，就是无法释放已申请的内存。

   内存溢出是指存储的数据超出了指定空间的大小，这时数据就会越界，举例来说，常见的溢出，是指在栈空间里，分配了超过数组长度的数据，导致多出来的数据覆盖了栈空间其他位置的数据，这种情况发生时，可能会导致程序出现各种难排查的异常行为，或是被有心人利用，修改特定位置的变量数据达到溢出攻击的目的。简而言之，就是申请不到足够内存。

2. java的堆、栈、方法区和常量池：

   * 栈（stack）：在函数中定义的一些基本类型的变量数据和对象的引用变量都在函数的栈内存中分配。当在一段代码块定义一个变量时，java就在栈中为这个变量分配内存空间，当该变量退出该作用域后，Java会自动释放掉为该变量所分配的内存空间，该内存空间可以立即被另作他用。

   * 堆（heap）：堆内存用来存放由new创建的对象和数组。在堆中分配的内存，由Java虚拟机的自动垃圾回收器来管理。在堆中产生了一个数组或对象后，在栈中定义一个特殊的变量，让栈中这个变量的取值等于数组或对象在堆内存中的首地址，栈中的这个变量就成了数组或对象的引用变量。实际上，栈中的变量指向堆内存中的变量，这就是java中的指针！jvm只有一个堆区(heap)被所有线程共享。

   * 方法区（method area）：方法区跟堆一样，被所有的线程共享。用于存储虚拟机加载的类信息、常量、静态变量、即时编译器编译后的代码等数据。

   * 常量池（constant pool）：常量池指的是在编译期被确定，并被保存在已编译的.class文件中的一些数据。除了包含代码中所定义的各种基本类型（如int、long等等）和对象型（如String及数组）的常量值(final)还包含一些以文本形式出现的符号引用，比如：类和接口的全限定名； 字段的名称和描述符； 方法和名称和描述符。虚拟机必须为每个被装载的类型维护一个常量池。

     原文链接：https://www.jianshu.com/p/af0b70ffcaf6


#### 设计模式

1. 单例（SIngleton）设计模式：对某个类**只能存在一个对象实例**，并且该类只提供一个取得其对象实例的方法。

   * 私有化类构造器：将类构造器的访问权限设置为private；
   * 内部创建类的静态对象；
   * 提供公共静态方法，返回类的对象。
   * 饿汉式设计：缺点是对象加载时间过长，优点是线程安全的；
   * 懒汉式设计：优点是延迟对象的创建，缺点是线程不安全。

   ```java
   /**
    * 单例模式的饿汉式实现（提前创建对象）
    */
   class Bank{
   
       //1.私有化类的构造器
       private Bank(){
   
       }
   
       //2.内部创建类的静态对象
       private static Bank instance = new Bank();
   
       //3.提供公共静态方法，返回类的对象
       public static Bank getInstance() {
           return instance;
       }
   }
   
   /**
    * 单例模式的懒汉式实现（啥时用啥时造）
    */
   class Order{
   
       //1.私有化类的构造器
       private Order(){
   
       }
   
       //2.声明当前类的静态对象，无初始化
       private static Order instance = null;
   
       //3.提供公共静态方法，返回当前类的对象
       public static Order getInstance() {
           // 修改成线程安全方式
           if(instance == null){
               synchronized(Order.class){
                   if(instance == null){
                       instance = new Order();
                   }
               }
           }
           return instance;
       }
   }
   ```

   **应用场景：** 网站计数器、应用程序的日志应用、数据库连接池、读取配置文件的类。

2. 代理（Proxy）模式：为其他对象提供一种代理以控制这个对象的访问，分为静态代理和动态代理。代理对象决定是否以及何时将方法调用转到原始对象上。

   ```
   public class NetWorkTest {
       public static void main(String[] args) {
           Server server = new Server();
           ProxyServer ps = new ProxyServer(server);
           ps.browse();
       }
   }
   
   interface NetWork{
       public void browse();
   }
   
   //被代理类
   class Server implements NetWork{
   
       @Override
       public void browse() {
           System.out.println("真实的服务器访问网络");
       }
   }
   
   //代理类
   class ProxyServer implements NetWork{
   
       private  NetWork netWork;
   
       public ProxyServer(NetWork netWork) {
           this.netWork = netWork;
       }
   
       public void check(){
           System.out.println("联网之前的检查工作");
       }
   
       @Override
       public void browse() {
           check();
           netWork.browse();
       }
   }
   ```

   **应用场景：**安全代理、远程代理、延迟加载。

3. 工厂模式：实现了创建者与调用者的分离。

