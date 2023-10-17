

#include <iostream>
using namespace std;


//int div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0)
//		throw invalid_argument("除0错误");
//
//	return a / b;
//}
//void func()
//{
//	div();
//}
//int main()
//{
//
//	try
//	{
//		func();
//	}
//	catch(const exception& e)//抛基类异常，用父类来接受
//	{
//		cout << e.what() << endl;
//	}
//}
// 
// 

//#include <vector>
//int div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0)
//		throw invalid_argument("除0错误");
//
//	return a / b;
//}
//void func()
//{
//	vector<int>* p1 = new vector<int>;
//
//	div();
//
//	delete p1;
//	cout << "delete:" << p1 << endl;
//}
////正常情况下，如果不抛异常，就不会内存泄露，但抛异常后，就会泄露，解决方法
////是再套一层异常判断，捕获的异常不处理，继续抛出(在抛出之前将资源释放)
//int main()
//{
//
//	try
//	{
//		func();
//	}
//	catch (const exception& e)//抛基类异常，用父类来接受
//	{
//		cout << e.what() << endl;
//	}
//}

//异常的缺点：内存泄露,在new和delete之间抛异常
//#include <vector>
//int div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0)
//		throw invalid_argument("除0错误");
//
//	return a / b;
//}
//void func()
//{
//	vector<int>* p1 = new vector<int>;
//	//如果p1抛异常就 没有问题，没有资源的申请，所以也不需要释放
//	vector<int>* p2 = new vector<int>;
//	//如果p2抛异常，p1就内存泄露
//	vector<int>* p3 = new vector<int>;
//	//如果p3抛异常，p1和p2就内存泄露
//	//…………
//	//所以异常出现后，很容易造成内存泄露，有什么办法可以解决呢？
//	try
//	{
//		div();
//	}
//	catch (...)
//	{
//		delete p1;
//		cout << "delete" << p1 << endl;
//		throw;//再抛出
//	}
//
//
//	delete p1;
//	cout << "delete:" << p1 << endl;
//}
//正常情况下，如果不抛异常，就不会内存泄露，但抛异常后，就会泄露，解决方法
//是再套一层异常判断，捕获的异常不处理，继续抛出(在抛出之前将资源释放)
//int main()
//{
//
//	try
//	{
//		func();
//	}
//	catch (const exception& e)//抛基类异常，用父类来接受
//	{
//		cout << e.what() << endl;
//	}
//}

//智能指针：解决异常造成内存泄露
//智能指针有三大特性：1.RAII  2.像指针一样  3.拷贝问题
// RAII就是利用对象的生命周期来管理资源。将资源交给对象管理，对象生命周期内，资源是有效的
// 当对象生命周期结束，则资源释放.
// 
template<class T>

class smater_ptr
{
public:
	smater_ptr( T* ptr)
		:_ptr(ptr)
	{}

	~smater_ptr()
	{
		cout << "delete:" << _ptr << endl;
		delete _ptr;
	}

	//像指针一样
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}

private:
	T* _ptr;
};

#include <vector>
int div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw invalid_argument("除0错误");

	return a / b;
}
void func()
{
	//vector<int>* p1 = new vector<int>;
	////如果p1抛异常就 没有问题，没有资源的申请，所以也不需要释放
	//vector<int>* p2 = new vector<int>;
	////如果p2抛异常，p1就内存泄露
	//vector<int>* p3 = new vector<int>;
	////如果p3抛异常，p1和p2就内存泄露
	//…………
	//所以异常出现后，很容易造成内存泄露，有什么办法可以解决呢？
	smater_ptr<vector<int>> p1(new vector<int>);
	//将资源给对象p1管理
	smater_ptr<vector<int>> p2(new vector<int>);
	smater_ptr<vector<int>> p3(new vector<int>);

	smater_ptr<string> ps(new string("小陶来咯"));
	div();
	cout << *ps << endl;
	cout << ps->size() << endl;
}
//正常情况下，如果不抛异常，就不会内存泄露，但抛异常后，就会泄露，解决方法
//是再套一层异常判断，捕获的异常不处理，继续抛出(在抛出之前将资源释放)
//int main()
//{
//
//	try
//	{
//		func();
//	}
//	catch (const exception& e)//抛基类异常，用父类来接受
//	{
//		cout << e.what() << endl;
//	}
//}


//智能指针 1.auto_ptr 2.unique_ptr 3.shared_ptr 4.weak_ptr
//int main()
//{
//	smater_ptr<string> sp1(new string("xioatao"));
//	smater_ptr<string> sp2(new string("xioyao"));
//
//	//存在这样的场景：
//	smater_ptr<string> sp3(sp1);
//	//指针之间的赋值就应该是浅拷贝，我们不用写
//	//但浅拷贝会出现什么问题呢？
//	//1.同一块资源被释放两次 2.内存泄露
//	return 0;
//}



//我们写一个类，方便观察资源创建和释放
#include "smater_ptr.h"
class B
{
public:

	B(int b = 0)
		:_b(b)
	{
		cout << "b=0" << endl;
	}

	~B()
	{
		cout << this;
		cout << "~B()" << endl;
	}



private:

	int _b;
};
//自定义类型构造会调用它的构造函数，和析构函数。
//int main()
//{
//	tao::auto_ptr<B> b1(new B(1));
//	tao::auto_ptr<B> b2(new B(2));
//	//这个是auto_ptr C++98时期就出现，但不好,很多公司严禁不给使这个玩意
//
//	//因为存在严重的不合理地方，当出现智能指针拷贝赋值的地方
//	//auto_ptr处理的方式是：直接转移资源的管理权。
//	//拷贝时，会把被拷贝对象的资源管理转移给拷贝对象。而被被拷贝对象就没有资源管理，直接置空
//	//存在问题：管理权转移后，再次访问被拷贝对象
//
//	tao::auto_ptr<B> b3(b1);
//
//	//b1这个智能指针已经没有资源可以管理了，里面的指针直接置空了，不能再访问了
//	//b1->_b++;
//	b3->_b++;
//	
//
//}
//
//int main()
//{
//	tao::unique_ptr<B> b1(new B(1));
//	tao::unique_ptr<B> b2(new B(2));
//
//
//	tao::unique_ptr<B> b3(b1);
//	//unique_ptr中简单粗暴，直接不给拷贝。直接将拷贝删除掉，但是要写，后面加delete即可。不然会生成默认拷贝。
//	
//	return 0;
//}

//int main()
//{
//	tao::shared_ptr<B> b1(new B(1));
//	tao::shared_ptr<B> b2(b1);
//	tao::shared_ptr<B> b3(b1);
//
//	  
//    tao::shared_ptr<B> b4(new B(2));
//
//	tao::shared_ptr<B> b5(b4);
//	b1 = b5;
//
//}

//shared_ptr几乎没有确定，但还是有缺点的：循环计数

//想要对象连在一起呢？让生成的节点链接在一起呢？

struct Node
{
	B _val;
	/*Node* _next;
	Node* _prev;*/

	weak_ptr<Node> _next;
    weak_ptr<Node> _prev;

	//shared_ptr<Node> _next;
	//shared_ptr<Node> _prev;
};

int main()
{

	shared_ptr<Node> sp1(new Node);
	shared_ptr<Node> sp2(new Node);

	//sp1->_next = sp2;
	//类型不匹配，sp1->next的类型是Node而sp2的类型是shared_ptr类型所以这样无法链接起来。

//
//	//所以Node节点里存的应该是shared_ptr类型的指针，这样才可以链接起来
	sp1->_next = sp2;
	sp2->_prev = sp1;

//
//
}
#include <iostream>
using namespace std;

//int main()
//{
//	string s;
//	cin >> s;
//	int num = 0;
//	if (s.size() <= 4)num += 5;
//
//	else if (s.size() >= 5 && s.size() <= 7) num += 10;
//
//	else  num += 25;
//
//	int digit = 0, bigchar = 0, smallchar = 0, smybol = 0;
//	for (int i = 0; i < s.size(); i++)
//	{
//		if (s[i] >= 'a' && s[i] <= 'z')
//			smallchar = 1;
//		else if (s[i] >= 'A' && s[i] <= 'Z')
//			bigchar = 1;
//		else if (s[i] >= '0' && s[i] <= '9')
//			digit++;
//		else smybol++;
//	}
//	//字母处理
//	if (bigchar == 0 && smallchar == 0)num += 0;
//	else if (bigchar == 1 && smallchar == 1)num += 20;
//	else num += 10;
//	//数字处理
//	if (digit == 0)num += 0;
//	else if (digit == 1)num += 10;
//	else num += 25;
//	//符号处理
//	if (smybol == 0)num += 0;
//	else if (smybol == 1)num += 10;
//	else num += 25;
//
//	//最后奖励
//	if (digit > 0 && smybol && bigchar && smallchar)num += 5;
//	else if (digit > 0 && smybol && bigchar || smallchar) num += 3;
//	else if (digit > 0 && bigchar || smallchar)num += 2;
//
//	if (num >= 90)cout << "VERY_SECURE";
//	else if (num >= 80)cout << "SECURE";
//	else if (num >= 70)cout << "VERY_STRONG";
//	else if (num >= 60)cout << "STRONG";
//	else if (num >= 50)cout << "AVERAGE";
//	else if (num >= 25)cout << "WEAK";
//	else if (num >= 0)cout << "VERY_WEAK";
//
//
//
//}
// 64 位输出请用 printf("%lld")
bool checkWon(vector<vector<int> > board)
{

	//先判断每一行

	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] ==1&& board[i][1]==1 && board[i][2] == 1)
		{
			return true;
		}
	}
	//再判断每一列
	for (int j = 0; j < 3; j++)
	{
		if (board[0][j] ==1&& board[1][j]==1 &&  board[2][j] == 1)
		{
			return true;
		}
	}
	//再判断对角线

	if (board[0][0] ==1&& board[1][1] ==1&& board[2][2] == 1)
		return true;

	if (board[0][2] ==1&& board[1][1] ==1&& board[2][0] == 1)
		return true;


	return false;

}
//
//int main()
//{
//	vector<vector<int>> vv = { {-1,1,-1},{0,0,1},{0,0,0} };
//	cout<<checkWon(vv);
//}