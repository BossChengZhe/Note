#include <bits/stdc++.h>
using namespace std;

class Stack
{
public:
    // 构造
    Stack(int size = 1000) 
	:msize(size), mtop(0)
    {
        cout << "Stack(int)" << endl;
        mpstack = new int[size];
    }
	
    // 析构
    ~Stack()
    {
        cout << "~Stack()" << endl;
        delete[]mpstack;
        mpstack = nullptr;
    }
	
    // 拷贝构造
    Stack(const Stack &src)
	:msize(src.msize), mtop(src.mtop)
    {
        cout << "Stack(const Stack&)" << endl;
        mpstack = new int[src.msize];
        for (int i = 0; i < mtop; ++i) {
            mpstack[i] = src.mpstack[i];
        }
    }
	
    // 赋值重载
    Stack& operator=(const Stack &src)
    {
        cout << "operator=" << endl;
        if (this == &src)
                return *this;

        delete[]mpstack;

        msize = src.msize;
        mtop = src.mtop;
        mpstack = new int[src.msize];
        for (int i = 0; i < mtop; ++i) {
            mpstack[i] = src.mpstack[i];
        }
        return *this;
    }

    // 带右值引用参数的拷贝构造函数
    Stack(Stack &&src)
        :msize(src.msize), mtop(src.mtop)
    {
        cout << "Stack(Stack&&)" << endl;

        /*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
        mpstack = src.mpstack;  
        src.mpstack = nullptr;
    }

    // 带右值引用参数的赋值运算符重载函数
    Stack& operator=(Stack &&src)
    {
        cout << "operator=(Stack&&)" << endl;

        if(this == &src)
            return *this;
            
        delete[]mpstack;

        msize = src.msize;
        mtop = src.mtop;

        /*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
        mpstack = src.mpstack;
        src.mpstack = nullptr;

        return *this;
    }

    int getSize() 
    {
	    return msize;
    }
private:
    int *mpstack;
    int mtop;
    int msize;
};

Stack GetStack(Stack &stack)
{
    Stack tmp(stack.getSize());
    return tmp;
}

int main()
{
    Stack s;
    s = GetStack(s);
    return 0;
}