堆中声明和栈中声明：

```cpp
#include <iostream>
class new_test{
    public:
    int a;
    int b;
};
using namespace std;
void* stack_bottom=NULL;
void ptr_in_stack(new_test* ptr)
{   
    //函数调用时处于栈顶位置。
    void* stack_top=&stack_top;//获取栈顶位置
    if( stack_bottom>ptr && stack_top<ptr)//比较地址范围
    {
        cout<<"指针"<<ptr<<"在栈中"<<endl;
    }
    else
    {
        cout<<"指针"<<ptr<<"不在栈中"<<endl;
    }
	return ;
}
int main() {
	int i;
	stack_bottom=&i;//记录下栈底的大概位置。
    new_test a;//栈中声明的abc
    new_test b;
    new_test c;
    new_test *p1=new new_test;//堆中
    new_test *p2=new new_test;
    new_test *p3=new new_test;
    cout<<"a address is: "<<&a<<endl;
    cout<<"b address is: "<<&b<<endl;
    cout<<"c address is: "<<&c<<endl;
    cout<<"p1 address is: "<<p1<<endl;
	ptr_in_stack(p1);
    cout<<"p2 address is: "<<p2<<endl;
	ptr_in_stack(p2);
    cout<<"p3 address is: "<<p3<<endl;
	ptr_in_stack(p3);
	system("pause");
    return 0;
}
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

运行结果如下所示：

![img](https://img-blog.csdnimg.cn/20191111202954514.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

从上图可以看出，abc的内存地址是依次减小的，这也符合栈中地址从高位到地位的特性，使用new方法申请的三个结构体也证明不存在与栈中。

关于删除：

栈中的结构体会自动删除，但是堆中的需要手动用delete删除，并且数组形式的也要加上[]，但是如果结构体只包含基本的数据类型，好像使用delete p和使用delete []p效果是一样的：

```cpp
#include <iostream>
class new_test{
    public:
    int a;
    int b;
};
using namespace std;
int main() {
	new_test *p=new new_test[2];
	new_test *p1=&p[0];
	new_test *p2=&p[1];
	p1->a=1;
	p2->a=2;
	cout<<"p1 is: "<<p1<<" p2 is: "<<p2<<endl;
	cout<<"p1的a："<<p1->a;
	cout<<endl;
	cout<<"p2的a："<<p2->a<<endl;
	delete p;
	cout<<"p1 is: "<<p1<<" p2 is: "<<p2<<endl;
	cout<<"p1的a："<<p1->a;
	cout<<endl;
	cout<<"p2的a："<<p2->a<<endl;
	 _CrtDumpMemoryLeaks();  
	system("pause");
    return 0;
}
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

输出结果：

![img](https://img-blog.csdnimg.cn/20191111204603880.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

可以看出p1和p2指向的好像都是被成功删除了，并且检测函数并没有输出检测到内存泄漏，试试复杂的结构体，看这样是否还是可以：

```cpp
#include <iostream>
using namespace std;
class new_test  
{
public:
    int a;
    new_test()  { a=0; }
    ~new_test()  {  cout<<"~new_test()"<<endl;    }  
    void test(int n)    {   a=n;   }  
};  

int main() {
	new_test *p=new new_test[2];
	new_test *p1=&p[0];
	new_test *p2=&p[1];
	p1->a=1;
	p2->a=2;
	cout<<"p1 is: "<<p1<<" p2 is: "<<p2<<endl;
	cout<<"p1的a："<<p1->a;
	cout<<endl;
	cout<<"p2的a："<<p2->a<<endl;
	delete p;
	cout<<"p1 is: "<<p1<<" p2 is: "<<p2<<endl;
	cout<<"p1的a："<<p1->a;
	cout<<endl;
	cout<<"p2的a："<<p2->a<<endl;
	 _CrtDumpMemoryLeaks();  
	system("pause");
    return 0;
}
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

输出结果报错，而且可以看到只析构了一个结构体：

![img](https://img-blog.csdnimg.cn/20191111205217433.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

改成了delete[] p,再看输出结果应该是正确得了：

![img](https://img-blog.csdnimg.cn/20191111205520767.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

两者为啥不一样还需要在做实验判断下。