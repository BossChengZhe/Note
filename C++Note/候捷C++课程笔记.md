##### 数量不定的模板参数

```c++
void print()
{
}
template <typename T, typename... Types>               // ...模板参数包
void pirnt(const T& fistArg, cosnt Types&... args)     // ...函数参数类型包
{
    cout << firtArg << endl;
    print(args...);   // ...函数参数包
}
```

做到不定的参数一一输出出来

##### C++11新特性

1. initializer_list

   ```c++
   vector<int> s{2,12,3,4};
   vector<string> z{"cheng","beijing","shanghai"};
   int x{10};
   int *p{};
   // 初始化一致性，背后涉及到模板函数和参数包(装逼利器)
   ```

   

##### explicit

```c++
// 常用于类的构造函数
struct Complex
{
    int real, imag;
    
    explicit
    Complex(int re, int im = 0) : real(re), imag(im) {}
    Complex operatort(const Complex &x) 
    { 
        return Complex((real + x.real),(imag + x.imag)); 
    }
};
Complex c1(12,5);
Complex c2 = c1 + 5;       
// 不加explicit是不会报错,将5转换成5+0i虚数;但是加了的话并不会隐式转换并且报错
```

