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

#### STL源码解析

##### vector

```C++

```



##### HashMap

```C++
// 部分源码  gunc 7.5.0
class unordered_map
{
    typedef __umap_hashtable<_Key, _Tp, _Hash, _Pred, _Alloc>  _Hashtable;
    _Hashtable _M_h;                          // Hash表
}

  template<typename _Key,
	   typename _Tp,
	   typename _Hash = hash<_Key>,
	   typename _Pred = std::equal_to<_Key>,
	   typename _Alloc = std::allocator<std::pair<const _Key, _Tp> >,
	   typename _Tr = __umap_traits<__cache_default<_Key, _Hash>::value>>
    using __umap_hashtable = _Hashtable<_Key, std::pair<const _Key, _Tp>,
                                        _Alloc, __detail::_Select1st,
				        _Pred, _Hash,
				        __detail::_Mod_range_hashing,
				        __detail::_Default_ranged_hash,
				        __detail::_Prime_rehash_policy, _Tr>;

template<typename _Key, typename _Value, typename _Alloc,
	   typename _ExtractKey, typename _Equal,
	   typename _H1, typename _H2, typename _Hash,
	   typename _RehashPolicy, typename _Traits>
class _Hashtable
{
private:
	__bucket_type*		_M_buckets		= &_M_single_bucket;      // 篮子的指针
 	size_type			_M_bucket_count		= 1;                  // 篮子的个数
	__node_base		_M_before_begin;
	size_type			_M_element_count	= 0;                  // 元素个数
	_RehashPolicy		_M_rehash_policy;                          // 重哈希的策略
}
```



- 当HashMap中的元素个数超过篮子的个数时，需要增加篮子(gun c变为两倍附近的质数)，并且将所有元素rehashing  [53->97->193...]
- hashtable的迭代器设计，必须要能够回到hashtable(类似于中控台的意思)

##### iterator_category

```c++
struct output_iterator_tag {}
struct intput_iterator_tag {}
struct farward_iterator_tag : public intput_iterator_tag {}
struct bidirectional_iterator_tag : public farward_iterator_tag {}
struct random_access_iterator_tag : public bidirectional_iterator_tag {}
```

