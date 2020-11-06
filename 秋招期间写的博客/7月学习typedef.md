ps:关于这个关键字之前老是弄不明白。

<!-- more -->
C语言允许用户使用 typedef 关键字来定义自己习惯的数据类型名称，来替代系统默认的基本类型名称、数组类型名称、指针类型名称与用户自定义的结构型名称、共用型名称、枚举型名称等。一旦用户在程序中定义了自己的数据类型名称，就可以在该程序中用自己的数据类型名称来定义变量的类型、数组的类型、指针变量的类型与函数的类型等。
例如，C 语言在C99之前并未提供布尔类型，但我们可以使用typedef关键字来定义一个简单的布尔类型，如下面的代码所示：

```
	typedef int BOOL;
	#define TRUE 1
	#define FALSE 0
```

定义好之后，就可以像使用基本类型数据一样使用它了，如下面的代码所示：

```
	BOOL flag=TRUE;
```

typedef的四种用法:
**（1）为基本的数据类型定义新的类型名**
系统所默认的所有基本类型都可以利用这个关键字来重新定义类型名，例如：

```
	typedef unsigned int COUNT;
	typedef long double REAL;
	typedef double REAL;//在不支持long double的平台可以更改为double。
	typedef float REAL;//同理可以改为float
```

这样，当跨平台移植程序时，只需要修改一下 typedef 的定义即可，而不用对其他源代码做任何修改。标准库中广泛地使用了这个技巧，size_t 在 VC++2010 的 crtdefs.h 文件中的定义如下所示：

```
#ifndef _SIZE_T_DEFINED
	#ifdef  _WIN64
	typedef unsigned __int64    size_t;
	#else
	typedef _W64 unsigned int   size_t;
	#endif
	#define _SIZE_T_DEFINED
	#endif
```

**（2）为自定义的数据类型（结构体、共用体和枚举类型）定义简洁的类型名称**
以结构体为例，我们定义一个point的结构体：

```
	struct Point
	{
	    double x;
	    double y;
	    double z;
	};
```

在调用这个结构体时，我们必须像下面的代码这样来调用这个结构体：

在这里，

```
	struct Point oPoint1={100，100，0};
	struct Point oPoint2;
```

结构体struct Point为新的数据类型，在定义变量的时候均要向上面的调用方法一样有保留字struct，而不能像 int 和 double 那样直接使用Point来定义变量。现在，我们利用 typedef 定义这个结构体，如下面的代码所示：

```
	typedef struct tagPoint
	{
	    double x;
	    double y;
	    double z;
	} Point;
```

在上面的代码中，实际上完成了两个操作：
1、定义了一个新的结构类型，代码如下所示：

```
	struct tagPoint
	{
	    double x;
	    double y;
	    double z;
	} ;
```

其中，struct 关键字和 tagPoint 一起构成了这个结构类型，无论是否存在 typedef 关键字，这个结构都存在。
2、使用 typedef 为这个新的结构起了一个别名，叫 Point，即：

```
	typedef struct tagPoint Point
```

因此，现在你就可以像 int 和 double 那样直接使用 Point 定义变量，如下面的代码所示：

```
	Point oPoint1={100，100，0};
	Point oPoint2;
```

为了加深对 typedef 的理解，再来看一个结构体例子，如下面的代码所示：

```
	typedef struct tagNode
	{
	    char *pItem;
	    pNode pNext;
	} *pNode;
```

从表面上看，上面的示例代码与前面的定义方法相同，所以应该没有什么问题。但是编译器却报了一个错误，为什么呢？莫非 C 语言不允许在结构中包含指向它自己的指针？
其实问题并非在于 struct 定义的本身，C 语言是允许在结构中包含指向它自己的指针的，我们可以在建立链表等数据结构的实现上看到很多这类例子。那问题在哪里呢？其实，根本问题还是在于 typedef 的应用。
在上面的代码中，新结构建立的过程中遇到了 pNext 声明，其类型是 pNode。这里要特别注意的是，pNode 表示的是该结构体的新别名。于是问题出现了，在结构体类型本身还没有建立完成的时候，编译器根本就不认识 pNode，因为这个结构体类型的新别名还不存在，所以自然就会报错。因此，我们要做一些适当的调整，比如将结构体中的 pNext 声明修改成如下方式：

```
	typedef struct tagNode
	{
	    char *pItem;
	    struct tagNode *pNext;
	} *pNode;
```

或者将 struct 与 typedef 分开定义，如下面的代码所示：

```
	typedef struct tagNode *pNode;
	struct tagNode
	{
	    char *pItem;
	    pNode pNext;
	};
```

在上面的代码中，我们同样使用 typedef 给一个还未完全声明的类型 tagNode 起了一个新别名。不过，虽然 C 语言编译器完全支持这种做法，但不推荐这样做。建议还是使用如下规范定义方法：

```
	struct tagNode
	{
	    char *pItem;
	    struct tagNode *pNext;
	};
	typedef struct tagNode *pNode;
```

（3）为数组定义简洁的类型名称
它的定义方法很简单，与为基本数据类型定义新的别名方法一样，示例代码如下所示：

```
	typedef int INT_ARRAY_100[100];
	INT_ARRAY_100 arr;
```

（4）为指针定义简洁的名称
对于指针，我们同样可以使用下面的方式来定义一个新的别名：

```
	typedef char* PCHAR;
	PCHAR pa;
```

对于上面这种简单的变量声明，使用 typedef 来定义一个新的别名或许会感觉意义不大，但在比较复杂的变量声明中，typedef 的优势马上就体现出来了，如下面的示例代码所示：

```
	int *(*a[5])(int,char*);
```

对于上面变量的声明，如果我们使用 typdef 来给它定义一个别名，这会非常有意义，如下面的代码所示：

```
// PFun是我们创建的一个类型别名
	typedef int *(*PFun)(int,char*);
	// 使用定义的新类型来声明对象，等价于int*(*a[5])(int,char*);
	PFun a[5];
```

**attention**：小心使用 typedef 带来的陷阱
接下来看一个简单的 typedef 使用示例，如下面的代码所示：

```
	typedef char* PCHAR;
	int strcmp(const PCHAR,const PCHAR);
```

在上面的代码中，“const PCHAR” 是否相当于 “const char * ” 呢？
答案是否定的，，typedef 是用来定义一种类型的新别名的，它不同于宏，不是简单的字符串替换。因此，“const PCHAR”中的 const 给予了整个指针本身常量性，也就是形成了常量指针“char * const（一个指向char的常量指针）”。即它实际上相当于“char * const”，而不是“const char  * （ 指向常量 char 的指针）”。当然，要想让 const PCHAR 相当于 const char* 也很容易，如下面的代码所示：

```
	typedef const char* PCHAR;
	int strcmp(PCHAR， PCHAR);
```

其实，无论什么时候，只要为指针声明 typedef，那么就应该在最终的 typedef 名称中加一个 const，以使得该指针本身是常量。
还需要特别注意的是，虽然 typedef 并不真正影响对象的存储特性，但在语法上它还是一个存储类的关键字，就像 auto、extern、static 和 register 等关键字一样。因此，像下面这种声明方式是不可行的：

```
	typedef static int INT_STATIC;
```

不可行的原因是不能声明多个存储类关键字，由于 typedef 已经占据了存储类关键字的位置，因此，在 typedef 声明中就不能够再使用 static 或任何其他存储类关键字了。当然，编译器也会报错，如在 VC++2010 中的报错信息为“无法指定多个存储类”。