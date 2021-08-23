## Spring5框架

#### 一、基本概述

1. Spring是一个轻量级的开源的JavaEE容器，主要针对**bean的生命周期**进行管理，有两个核心部分：IOC（控制反转，将创建对象过程交给Spring进行管理）和AOP（面向切面编程，不修改源代码进行功能增强）。简而言之，Spring是一个轻量级的IOC和AOP的容器框架。

   ![img](https://upload-images.jianshu.io/upload_images/24808978-ed59988f54c0041f.png?imageMogr2/auto-orient/strip|imageView2/2/w/884/format/webp)

2. Spring特点：

   * 方便解耦，简化开发；
   * AOP编程的支持；
   * 声明式事务的支持；
   * 方便程序测试；
   * 方便继承各种框架；
   * 降低Java EE API的使用难度。

#### 二、IOC容器

1. 基本概念：把对象创建和对象之间的调用过程，交给spring进行管理，其目的是为了降低耦合度。

2. 使用过程：

   * 创建xml配置文件，配置创建的对象；

     ```xml
     <bean id="user" class="com.librah.spring5.User"></bean>
     ```

   * 有service和dao类，创建工厂类；

     ```java
     class UserFactory{
         public static UserDao getDao() {
             // xml解析获取类属性值
             String classValue = class属性值;
             // 通过反射创建对象
             Class clazz = Class.forName(classValue);
             return (UserDao)clazz.newInstance();
         }
     }
     ```

3. 底层原理：主要用到了xml解析、**工厂模式**和**反射机制**，IOC容器底层就是对象工厂。

   * Spring提供IOC容器实现两种方式：
     * BeanFactory（Spring内部的使用接口，不提供开发人员使用）：加载配置文件时不会创建对象，在获取对象时才去创建；
     * ApplicationContext（BeanFactory接口的子接口，提供更多功能，由开发人员使用）：加载配置文件时就会把配置文件对象进行创建。
       * `FileSystemXmlApplicationContext`: xml文件全路径；
       * `ClassPathXmlApplicationContext`：当前项目下的资源文件名。

4. Bean管理：Spring创建对象和Spring注入属性。

   * 基于xml配置文件方式实现：

     * 创建对象：id属性表示唯一标记，class属性表示类的全路径，创建对象时默认执行无参数构造方法完成对象创建；

       ```xml
       <bean id="user" class="com.librah.spring5.User"></bean>
       ```

     * 注入属性（DI，依赖注入）：

       * set方法注入：

         ```xml
         <!-- set方法注入属性 -->
         <bean id="book" class="com.librah.spring5.Book">
             <!-- 使用property完成属性注入 -->
             <property name="name" value="天龙八部"/>
             <property name="author" value="金庸"/>
         </bean>
         ```

       * 有参构造器注入属性：

         ```xml
         <!-- 有参构造器注入属性 -->
         <bean id="book" class="com.librah.spring5.Book">
             <constructor-arg name="name" value="天龙八部"/>
             <constructor-arg name="author" value="金庸"/>
         </bean>
         ```

       * 外部bean注入：

         ```xml
         <bean id="userService" class="com.librah.spring5.service.UserService">
             <!-- 注入UserDao对象-->
             <property name="userDao" ref="userDaoImpl"/>
         </bean>
         
         <bean id="userDaoImpl" class="com.librah.spring5.dao.UserDaoImpl">
         </bean>
         ```

       * 内部bean注入：

         ```xml
         <bean id="userService" class="com.librah.spring5.service.UserService">
             <property name="userDao">
                 <bean id="userDaoImpl" class="com.librah.spring5.dao.UserDaoImpl">
                 </bean>
             </property>
         </bean>
         ```

   * 基于注解方式实现：

     * 引入依赖Spring-aop包；

     * 开启组件扫描：

       ```xml
       <context:component-scan base-package="com.librah.spring5.dao"/>
       
       <!--include-filter: 设置要扫描的内容 exclude-filter: 设置不扫描的内容-->
           <context:component-scan base-package="com.librah.spring5" use-default-filters="false">
               <context:include-filter type="annotation" expression="org.springframework.stereotype.Controller"/>
               <context:exclude-filter type="annotation" expression="org.springframework.stereotype.Repository"/>
           </context:component-scan>
       ```

     * @Component，@Service，@Controller，@Repository都可以用来创建bean实例，但一般声明在不同功能的类上。

5. 普通bean和工厂bean区别：

   * 普通bean在配置文件中定义bean类型就是返回类型；

   * 工厂bean（FactoryBean）在配置文件定义bean类型可以和返回类型不一样。

     ```java
     public class MyBean implements FactoryBean<Book> {
     
     
         @Override
         public Book getObject() throws Exception {
     
             Book book = new Book("天龙八部", "金庸");
             return book;
         }
     
         @Override
         public Class<?> getObjectType() {
             return null;
         }
     
         @Override
         public boolean isSingleton() {
             return FactoryBean.super.isSingleton();
         }
     }
     
     @Test
     public void test3(){
         ApplicationContext context = new ClassPathXmlApplicationContext("bean3.xml");
     
         Book book = context.getBean("myBean", Book.class);
         System.out.println(book);
     }
     ```

6. bean的作用域：可以设置创建bean实例是单实例还是多实例，默认情况下为单实例对象。bean标签中scope属性值，可以指定prototype表示多实例，singleton表示单实例。

   * singleton：加载配置文件时就会创建单实例对象；
   * prototype：调用getBean()方法时才会创建对象。

7. bean的生命周期：

   <img src="https://pic2.zhimg.com/80/v2-baaf7d50702f6d0935820b9415ff364c_1440w.jpg?source=1940ef5c" alt="img" style="zoom: 50%;" />

   * 通过构造器创建bean实例（无参构造）；

   * 为bean的属性设置值和对其他bean引用（调用set方法）；

   * 把bean实例传递给BeanPostProcesser前置处理；

   * 调用bean的初始化方法（配置初始化方法）；

   * 把bean实例传递给BeanPostProcesser后置处理；

   * 开始使用bean（对象已获取）；

   * 当容器关闭时，调用bean的销毁方法（需要进行配置销毁方法）。

     ```xml
     <bean id="orders" class="com.librah.spring5.bean.Orders" init-method="initMethod" destroy-method="destroyMethod">
         <property name="orderName" value="手机”"/>
     </bean>
     <!--配置后置处理器-->
     <bean id="myBeanPost" class="com.librah.spring5.bean.MyBeanPost"/>
     ```

     ```java
     public class MyBeanPost implements BeanPostProcessor {
         @Override
         public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException 	  {
             System.out.println("MyBeanPost.postProcessBeforeInitialization");
             return BeanPostProcessor.super.postProcessBeforeInitialization(bean, beanName);
         }
     
         @Override
         public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException 	 {
             System.out.println("MyBeanPost.postProcessAfterInitialization");
             return BeanPostProcessor.super.postProcessAfterInitialization(bean, beanName);
         }
     }
     @Test
     public void test4(){
         ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("bean4.xml");
         
         Orders orders = context.getBean("orders", Orders.class);
     
         System.out.println(orders);
     
         // 手动消耗bean实例对象
         context.close();
     }
     ```

8. 自动装配：bean标签属性autowire，来进行配置。其属性值有byName和byType两种，前者根据名称自动装配，后者根据类型自动装配。

9. 操作Bean管理引入外部属性文件：

   ```xml
   <?xml version="1.0" encoding="UTF-8"?>
   <beans xmlns="http://www.springframework.org/schema/beans"
          xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
          xmlns:context="http://www.springframework.org/schema/context"
          xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
                              http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd">
   
   <!--    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">-->
   <!--        <property name="driverClassName" value="com.mysql.jdbc.Driver"/>-->
   <!--        <property name="url" value="jdbc:mysql://localhost:3306/test"/>-->
   <!--        <property name="username" value="root"/>-->
   <!--        <property name="password" value="librah"/>-->
   <!--    </bean>-->
   
           <!--引入外部属性文件-->
           <context:property-placeholder location="jdbc.properties"/>
           <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">
               <property name="driverClassName" value="${prop.driverClass}"/>
               <property name="url" value="${prop.url}"/>
               <property name="username" value="${prop.userName}"/>
               <property name="password" value="${prop.password}"/>
           </bean>
   </beans>
   ```

10. 基于注解方式实现属性注入：

    * @Autowired：根据属性类型进行自动装配；

    * @Qualifier：根据属性名称进行注入，和上面的@Autowired一起使用；

    * @Resource：根据类型注入，也可以根据名称注入，不在spring包中，不建议使用；

    * @Value：注入普通类型属性。

      ```java
      @Autowired
      @Qualifier(value = "consumerImpl")
      private ConsumerDao consumerDao;
      
      @Value(value = "abc")
      private String name;
      ```

11. 完全注解开发：

    ```java
    @Configuration // 作为配置类，替代xml配置文件
    @ComponentScan(basePackages = {"com.librah.spring5"})
    public class SpringConfig {
    
    }
    ApplicationContext context = new AnnotationConfigApplicationContext(SpringConfig.class);
    ```

#### 三、AOP

1. 基本概念：面向切面编程，利用AOP可以对业务逻辑的各个部分进行隔离，从而使得业务逻辑各部分之间的耦合度降低，提高程序可重用性。简而言之，即不通过修改源代码方式来添加新的功能。

2. 底层原理：使用动态代理机制，有两种情况：

   * 第一种是有接口情况，使用JDK动态代理，创建接口实现类的代理对象来增强类的方法；

     * 调用Proxy.newProxyInstance(ClassLoader loader, Class<?>[] interfaces,InvocationHandler h)方法，参数分别表示类加载器，增强方法所在类实现的接口，实现这个接口InvocationHandler的类（写增强的方法）。 
       
* 第二种没有接口情况，使用cglib动态代理，创建当前类子类的代理对象。
   
3. AOP术语：

   * 连接点：类里面可以增强的方法；
   * 切入点：类里面实际被真正增强的方法；
   * 通知（增强）：实际增强的逻辑部分，有五种类型：
     * 前置通知：方法前增强；
     * 后置通知：方法后增强；
     * 环绕通知：方法前后都增强；
     * 异常通知：出现异常后的增强；
     * 最终通知：finally。
   * 切面：将通知应用到切入点的过程。

4. AOP操作：一般都是基于**AspectJ**实现AOP操作，有两种方式来实现。

   * 基于xml配置文件实现：

   * 基于注解方式实现：

     * 在spring配置文件中，开启注解扫描；

       ```xml
       <!--开启组件扫描-->
       <context:component-scan base-package="com.librah.spring5.aopanno"/>
       ```

     * 使用注解创建被增强类和增强类对象；

       ```java
       // 被增强类
       @Component
       public class User {
           public void add(){
               System.out.println("User.add");
           }
       }
       ```

     * 在增强类上添加注解@Aspect；

       ```java
       //增强类
       @Component
       @Aspect //生成代理对象
       public class UserProxy {
       
           // 前置通知，添加@Before注解
           @Before(value = "execution(* com.librah.spring5.aopanno.User.add(..))")
           public void before(){
               System.out.println("UserProxy.before");
           }
       
           @After(value = "execution(* com.librah.spring5.aopanno.User.add(..))")
           public void after(){
               System.out.println("UserProxy.after");
           }
       
           @AfterReturning(value = "execution(* com.librah.spring5.aopanno.User.add(..))")
           public void afterReturning(){
               System.out.println("UserProxy.afterReturning");
           }
       
           @AfterThrowing(value = "execution(* com.librah.spring5.aopanno.User.add(..))")
           public void afterThrowing(){
               System.out.println("UserProxy.afterThrowing");
           }
           @Around(value = "execution(* com.librah.spring5.aopanno.User.add(..))")
           public void around(ProceedingJoinPoint proceedingJoinPoint) throws Throwable {
               System.out.println("UserProxy.around before");
               proceedingJoinPoint.proceed();
               System.out.println("UserProxy.around after");
           }
       
       }
       ```

     * 在spring配置文件中开启生成代理对象。

       ```xml
       <!--开启aspectj生成代理对象-->
       <aop:aspectj-autoproxy/>
       ```

5. 切入点表达式：execution(\[权限修饰符]\[返回类型]\[类全路径]\[方法名称]([参数列表])

6. 多个增强类对同一个方法进行增强时，可以在增强类上面添加@Order(数字)来设置优先级。

7. AOP完全注解开发：

   ```java
   @Configuration
   @ComponentScan(basePackages = {"com.librah.spring5"})
   @EnableAspectJAutoProxy(proxyTargetClass = true)
   public class AopConfig {
   }
   ```

#### 四、jdbcTemplate

1. 基本概念：对JDBC进行封装，方便对数据库进行操作。

2. 文件配置：

   ```xml
   <!--开启组件扫描-->
   <context:component-scan base-package="com.librah.spring5"/>
   
   <!--引入外部属性文件-->
   <context:property-placeholder location="jdbc.properties"/>
   <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">
       <property name="driverClassName" value="${prop.driverClass}"/>
       <property name="url" value="${prop.url}"/>
       <property name="username" value="${prop.userName}"/>
       <property name="password" value="${prop.password}"/>
   </bean>
   
   <!--配置JdbcTemplate对象-->
   <bean id="jdbcTemplate" class="org.springframework.jdbc.core.JdbcTemplate">
       <property name="dataSource" ref="dataSource"/>
   </bean>
   ```

3. JdbcTemplate操作数据库：

   - execute方法：可以用于执行任何SQL语句，一般用于执行DDL语句；
   - update方法及batchUpdate方法：update方法用于执行新增、修改、删除等语句；batchUpdate方法用于执行批处理相关语句；
   - query方法及queryForXXX方法：用于执行查询相关语句；
   - call方法：用于执行存储过程、函数相关语句。

#### 五、Spring事务操作

1. 事务要添加到JavaEE三层结构里面的Service层（业务逻辑层），有两种事务管理方式：

   * 编程式事务管理：通过代码完成；
   * 声明式事务管理（使用）：通过配置注解完成。

2. 声明式事务管理：底层使用AOP原理。Spring提供一个接口PlatformTransactionManager，代表事务管理器，针对不同框架提供不同的实现类。

3. 声明式事务管理操作：

   * 在spring配置文件中配置事务管理器，开启事务注解：

     ```xml
     <?xml version="1.0" encoding="UTF-8"?>
     <beans xmlns="http://www.springframework.org/schema/beans"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:context="http://www.springframework.org/schema/context"
            xmlns:aop="http://www.springframework.org/schema/aop"
            xmlns:tx="http://www.springframework.org/schema/tx"
            xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
                                http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context.xsd
                                http://www.springframework.org/schema/aop  http://www.springframework.org/schema/aop/spring-aop.xsd
                                http://www.springframework.org/schema/tx http://www.springframework.org/schema/tx/spring-tx.xsd http://www.alibaba.com/schema/stat http://www.alibaba.com/schema/stat.xsd">
     
         <!--开启组件扫描-->
         <context:component-scan base-package="com.librah.spring5test2"/>
     
         <!--引入外部属性文件-->
         <context:property-placeholder location="jdbc.properties"/>
         <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">
             <property name="driverClassName" value="${prop.driverClass}"/>
             <property name="url" value="${prop.url}"/>
             <property name="username" value="${prop.userName}"/>
             <property name="password" value="${prop.password}"/>
         </bean>
     
         <!--配置JdbcTemplate对象-->
         <bean id="jdbcTemplate" class="org.springframework.jdbc.core.JdbcTemplate">
             <property name="dataSource" ref="dataSource"/>
         </bean>
     
         <!--创建事务管理器-->
         <bean id="transactionManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
             <property name="dataSource" ref="dataSource"/>
         </bean>
     
         <!--开启事务注解-->
         <tx:annotation-driven transaction-manager="transactionManager"/>
     
     </beans>
     ```

   * 在service类上面添加事务注解@Transactional，可以添加到类或方法上面；

4. @Transactional参数配置：

   * propagation：事务传播行为

     * 多事务方法直接进行调用;

     * 事务传播行为有7种：

       * REQUIRED：如果有事务在运行，当前方法就在这个事务内运行，否则就启动一个新的事务，并在自己的事务内运行；

       * REQUIRED_NEW：当前方法必须启动新事务，并在自己的事务内运行，如果有事务正在运行，则将它挂起；

       * ```java
         REQUIRED(0),
         SUPPORTS(1),
         MANDATORY(2),
         REQUIRES_NEW(3),
         NOT_SUPPORTED(4),
         NEVER(5),
         NESTED(6);
         ```

   * ioslation：事务隔离级别设置；

   * timeout：超时时间， 需要在一定时间内提交，否则回滚；

   * readOnly：是否只读；

   * rollbackFor：回滚，设置出现哪些异常进行回滚；

   * noRollbackFor：不回滚，设置出现哪些异常不进行回滚；

5. 完全注解开发：

   ```java
   @Configuration
   @ComponentScan(basePackages = "com.librah.spring5test2")
   @EnableTransactionManagement // 开启事务
   
   public class TxConfig {
   
       // 创建数据库连接池
       @Bean
       public DruidDataSource getDruidDataSource(){
           DruidDataSource dataSource = new DruidDataSource();
           dataSource.setDriverClassName("com.mysql.cj.jdbc.Driver");
           dataSource.setUrl("jdbc:mysql://localhost:3306/test?useUnicode=true&characterEncoding=UTF-8&serverTimezone=UTC");
           dataSource.setUsername("root");
           dataSource.setPassword("librah");
   
           return dataSource;
       }
   
       // 创建JdbcTemplate对象
       public JdbcTemplate getJdbcTemplate(DataSource dataSource){
           JdbcTemplate jdbcTemplate = new JdbcTemplate();
           jdbcTemplate.setDataSource(dataSource);
           return jdbcTemplate;
       }
   
       // 创建事务管理器
       public DataSourceTransactionManager getTransactionManager(DataSource dataSource){
           DataSourceTransactionManager dataSourceTransactionManager = new DataSourceTransactionManager();
           dataSourceTransactionManager.setDataSource(dataSource);
   
           return dataSourceTransactionManager;
       }
   }
   ```

#### 六、Spring5框架新功能

1. @Nullable注解可以使用在方法、属性和参数上面，表示可以为空。

2. Spring5整合JUnit4：

   ```java
   @RunWith(SpringJUnit4ClassRunner.class)
   @ContextConfiguration("classpath:bean8.xml")
   public class JTest4 {
   
       @Autowired
       private BankService bankService;
   
       @Test
       public void test1(){
           bankService.transferMoney();
       }
   
   }
   ```

3. Spring5整合JUnit5：

   ```java
   //@ExtendWith(SpringExtension.class)
   //@ContextConfiguration("classpath:bean8.xml")
   @SpringJUnitConfig(locations = "classpath:bean8.xml") // 复合注解
   public class JTest5 {
       @Autowired
       private BankService bankService;
   
       @Test
       public void test1(){
           bankService.transferMoney();
       }
   }
   ```

4. 异步和同步：针对**调用者**，调用者发送请求，如果等着对方回应之后再去做其他事情就是同步，如果发送请求之后不等着对方回应就去做其他事情就是异步。

5. 阻塞和非阻塞：针对**被调用者**，被调用者收到请求后，做完请求任务之后再给出反馈就是阻塞，收到请求之后马上给出反馈然后再去做事情就是非阻塞。

6. WebFlux：之后再看......

