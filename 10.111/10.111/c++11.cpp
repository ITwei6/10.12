

#include <iostream>
using namespace std;


//int div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0)
//		throw invalid_argument("��0����");
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
//	catch(const exception& e)//�׻����쳣���ø���������
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
//		throw invalid_argument("��0����");
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
////��������£���������쳣���Ͳ����ڴ�й¶�������쳣�󣬾ͻ�й¶���������
////������һ���쳣�жϣ�������쳣�����������׳�(���׳�֮ǰ����Դ�ͷ�)
//int main()
//{
//
//	try
//	{
//		func();
//	}
//	catch (const exception& e)//�׻����쳣���ø���������
//	{
//		cout << e.what() << endl;
//	}
//}

//�쳣��ȱ�㣺�ڴ�й¶,��new��delete֮�����쳣
//#include <vector>
//int div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0)
//		throw invalid_argument("��0����");
//
//	return a / b;
//}
//void func()
//{
//	vector<int>* p1 = new vector<int>;
//	//���p1���쳣�� û�����⣬û����Դ�����룬����Ҳ����Ҫ�ͷ�
//	vector<int>* p2 = new vector<int>;
//	//���p2���쳣��p1���ڴ�й¶
//	vector<int>* p3 = new vector<int>;
//	//���p3���쳣��p1��p2���ڴ�й¶
//	//��������
//	//�����쳣���ֺ󣬺���������ڴ�й¶����ʲô�취���Խ���أ�
//	try
//	{
//		div();
//	}
//	catch (...)
//	{
//		delete p1;
//		cout << "delete" << p1 << endl;
//		throw;//���׳�
//	}
//
//
//	delete p1;
//	cout << "delete:" << p1 << endl;
//}
//��������£���������쳣���Ͳ����ڴ�й¶�������쳣�󣬾ͻ�й¶���������
//������һ���쳣�жϣ�������쳣�����������׳�(���׳�֮ǰ����Դ�ͷ�)
//int main()
//{
//
//	try
//	{
//		func();
//	}
//	catch (const exception& e)//�׻����쳣���ø���������
//	{
//		cout << e.what() << endl;
//	}
//}

//����ָ�룺����쳣����ڴ�й¶
//����ָ�����������ԣ�1.RAII  2.��ָ��һ��  3.��������
// RAII�������ö��������������������Դ������Դ������������������������ڣ���Դ����Ч��
// �������������ڽ���������Դ�ͷ�.
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

	//��ָ��һ��
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
		throw invalid_argument("��0����");

	return a / b;
}
void func()
{
	//vector<int>* p1 = new vector<int>;
	////���p1���쳣�� û�����⣬û����Դ�����룬����Ҳ����Ҫ�ͷ�
	//vector<int>* p2 = new vector<int>;
	////���p2���쳣��p1���ڴ�й¶
	//vector<int>* p3 = new vector<int>;
	////���p3���쳣��p1��p2���ڴ�й¶
	//��������
	//�����쳣���ֺ󣬺���������ڴ�й¶����ʲô�취���Խ���أ�
	smater_ptr<vector<int>> p1(new vector<int>);
	//����Դ������p1����
	smater_ptr<vector<int>> p2(new vector<int>);
	smater_ptr<vector<int>> p3(new vector<int>);

	smater_ptr<string> ps(new string("С������"));
	div();
	cout << *ps << endl;
	cout << ps->size() << endl;
}
//��������£���������쳣���Ͳ����ڴ�й¶�������쳣�󣬾ͻ�й¶���������
//������һ���쳣�жϣ�������쳣�����������׳�(���׳�֮ǰ����Դ�ͷ�)
//int main()
//{
//
//	try
//	{
//		func();
//	}
//	catch (const exception& e)//�׻����쳣���ø���������
//	{
//		cout << e.what() << endl;
//	}
//}


//����ָ�� 1.auto_ptr 2.unique_ptr 3.shared_ptr 4.weak_ptr
//int main()
//{
//	smater_ptr<string> sp1(new string("xioatao"));
//	smater_ptr<string> sp2(new string("xioyao"));
//
//	//���������ĳ�����
//	smater_ptr<string> sp3(sp1);
//	//ָ��֮��ĸ�ֵ��Ӧ����ǳ���������ǲ���д
//	//��ǳ���������ʲô�����أ�
//	//1.ͬһ����Դ���ͷ����� 2.�ڴ�й¶
//	return 0;
//}



//����дһ���࣬����۲���Դ�������ͷ�
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
//�Զ������͹����������Ĺ��캯����������������
//int main()
//{
//	tao::auto_ptr<B> b1(new B(1));
//	tao::auto_ptr<B> b2(new B(2));
//	//�����auto_ptr C++98ʱ�ھͳ��֣�������,�ܶ๫˾�Ͻ�����ʹ�������
//
//	//��Ϊ�������صĲ�����ط�������������ָ�뿽����ֵ�ĵط�
//	//auto_ptr����ķ�ʽ�ǣ�ֱ��ת����Դ�Ĺ���Ȩ��
//	//����ʱ����ѱ������������Դ����ת�Ƹ��������󡣶��������������û����Դ����ֱ���ÿ�
//	//�������⣺����Ȩת�ƺ��ٴη��ʱ���������
//
//	tao::auto_ptr<B> b3(b1);
//
//	//b1�������ָ���Ѿ�û����Դ���Թ����ˣ������ָ��ֱ���ÿ��ˣ������ٷ�����
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
//	//unique_ptr�м򵥴ֱ���ֱ�Ӳ���������ֱ�ӽ�����ɾ����������Ҫд�������delete���ɡ���Ȼ������Ĭ�Ͽ�����
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

//shared_ptr����û��ȷ������������ȱ��ģ�ѭ������

//��Ҫ��������һ���أ������ɵĽڵ�������һ���أ�

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
	//���Ͳ�ƥ�䣬sp1->next��������Node��sp2��������shared_ptr�������������޷�����������

//
//	//����Node�ڵ�����Ӧ����shared_ptr���͵�ָ�룬�����ſ�����������
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
//	//��ĸ����
//	if (bigchar == 0 && smallchar == 0)num += 0;
//	else if (bigchar == 1 && smallchar == 1)num += 20;
//	else num += 10;
//	//���ִ���
//	if (digit == 0)num += 0;
//	else if (digit == 1)num += 10;
//	else num += 25;
//	//���Ŵ���
//	if (smybol == 0)num += 0;
//	else if (smybol == 1)num += 10;
//	else num += 25;
//
//	//�����
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
// 64 λ������� printf("%lld")
bool checkWon(vector<vector<int> > board)
{

	//���ж�ÿһ��

	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] ==1&& board[i][1]==1 && board[i][2] == 1)
		{
			return true;
		}
	}
	//���ж�ÿһ��
	for (int j = 0; j < 3; j++)
	{
		if (board[0][j] ==1&& board[1][j]==1 &&  board[2][j] == 1)
		{
			return true;
		}
	}
	//���ж϶Խ���

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