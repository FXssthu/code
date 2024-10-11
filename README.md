# C++面向对象
## 内存模型
### 代码区
二进制代码 操作系统管理

存放CPU执行的机器指令 **机器指令=操作码+地址码**

**共享**-只有一份-省内存

**只读**-防止反编译大师恶意修改

### 全局区
全局变量（函数外部） 静态变量（static） 常量（指的是字符串常量）

**函数外部**的变量+static修饰的变量+字符串常量 ->全局区

**操作系统管理**
### 栈区
[区别栈和栈区、堆区和堆](https://blog.csdn.net/panjiapengfly/article/details/102665381)
**编译器分配**

不能返回局部变量的指针的原因是：

局部变量在函数结束时被销毁，虽然可以取到他的地址，但是地址对应的数值却不是原来的

地址虽在，但是地址对应住的人换了

一个函数结束时才会销毁局部变量，main函数一般不会出现返回局部变量地址发生错误的问题，因为main函数是某个项目的唯一主函数

**解决方法是：1.static修饰  or  堆区开辟  or  ->跨越阶级才能保证生存！**


### 堆区
程序员分配
new int(1314);

上面这个是个指针

int *a = new int(1314);

return *a;
## 引用
**量子纠缠**

int a = 1314;

int &b = a;

绑定宿主后，不可更改

Applicaton：引用传递

形参如何修饰实参：值传递；指针传递；引用传递；

**不要返回函数的引用**

**可以返回全局变量的引用**

**返回类型是:引用 的函数 可以作为左值**

### 引用的本质->指针常量
int &ref = a ；<=>
int *const ref = &a;

这也就是宿主绑定后不可换宿主的原因；

锁死引用，不可修改值的操作：
const int& a；

防止a值被误操作
Application：void func(const int &val);

## 默认参数与重载
函数形参可以有默认值

函数声明有了默认参数，函数实现就不能有默认参数

只能有一次默认参数的机会，

### 函数占位参数
### 函数重载
函数默认参数和函数重载可能会发生冲突，一般不建议同时使用

## C++类和对象
### 封装：属性和服务打包在一起；
###    ：接口权限设置；
#### 类和对象：

struct 相当于基本类型（int double string 或者int *）的组合

类相当于高级的struct 


对象相当于类的实例
#### 实战

实战创建学生的类时，string类型的变量赋值要用"  "引起来；

否则会警告！

### 权限
public：任何人都可以访问

protected：子类可以访问

private：仅本小类内访问

权限：读 写 权限

通过函数接口控制单独的读写权限

写权限：设置（void）类内变量值 or （double）return所需值；

为什么：设置公开的读写函数，而不能让属性公开

**总是忘了李括号**

### 初始化 与 清理
**构造函数** 

有参无返

**析构函数**

无参无返

构造函数如果私有，那么class将不可创建对象

正确的例子如下
```cpp
class student
{
public:
    student()//构造函数
    {
        cout << "Start..." << endl;
    }
    ~student()//析构函数
    {
        cout << "End!" << endl;
    }
};
```
**构造函数进阶**

无参构造 有参构造

普通构造 拷贝构造

```cpp
#include <iostream>
#include <string.h>
using namespace std;
class student
{

    string id;
    string name;

public:
    student()
    {
        cout << "Start..." << endl;
    }
    student(int a)
    {
        this->id = "1120233198";
        this->name = "FanYuchen!";
        cout << "A@-Start!" << endl;
    }
    student(const student &stu01)
    {
        id = stu01.id;
        name = stu01.name;
        cout << "copy-Start!" << endl;
    }
    ~student()
    {
        cout << "End!" << endl;
    }
};

int main()
{
//括号法调用！
    student stu1;
    student stu2(1);
    student stu3(stu1);
    cout << "Hello!" << endl;
//显式调用,关键在于匿名对象的使用
    
//隐式调用,省略了显式调用的匿名对象
    return 0;
}
```
如果存在自我创建构造函数，会销毁系统自带的构造函数


**拷贝构造函数进阶**

调用时机：

1.利用已创建对象进行拷贝；


2.创建函数是值传递时；
 
        explaining:
        
        参数是值传递的函数在调用时，会复制一份完全相同的变量，编译器在此时使用了构造函数
        
        如果已创建拷贝构造函数，就使用存在的函数，如果没有，编译器会使用默认的拷贝构造函数

        编译器会创建默认构造函数、拷贝构造函数、析构函数

3.返回值被调用，编译器优化，可能看不到
``` cpp
student dowork()
{
    student stu1;
    cout << "stu1的地址:" << &stu1 << endl;
    return stu1;
}
void test()
{
    student stu2(dowork());
    cout << "stu2的地址:" << &stu2 << endl;
}
int main()
{
    test();
    return 0;
}
```
输出为：
```
Start...
stu1的地址:0x7ffd55467fe0
stu2的地址:0x7ffd55467fe0
End!
```

**深拷贝和浅拷贝**

析构函数在此用于释放堆区内存

**静态成员变量**

所有对象共享同一变量；

类内声明，类外初始化；

记住要public；

**静态函数**

所有对象共享同一函数；

【权限不足】静态成员函数：只能访问静态成员变量；

静态必须公开！


**内存**：类内变量和类内函数分开存储；

空对象也会占用内存，大小为 1

只有非静态成员变量是计算内存的，其他的会在别的地方

**this指针**

返回对象本身用*this

Function：避免名称重复

```cpp
student& add(const student &stu1)
    {
        this->age += stu1.age;
        return *this;
    }
```
拷贝构造函数，普通返回会创建一个新的副本，引用才是本体

空指针调用成员函数

```cpp
//常函数
  void func() const
    {
        this->age =100;
    }
int main()
{
    const student stu1;
}
```
想修改
```cpp
mutable int age;
```
const作用：锁死const对应的值；

常对象只能调用常函数；

### 友元
**全局函数**

**类**

**类内对象**

### 运算符重载

### 继承

### 多态
#### 静态多态
#### 动态多态











