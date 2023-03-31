/*
定义一个复数类，随机生成一个无序的复数向量（有重复项）
（1）在主函数中测试无序向量的置乱、查找（实部和虚部均相同）、插入、删除和唯一化的操作
（2）以复数的模为基准进行排序（模相同的情况下，以实部为基准），比较顺序、乱序、逆序的情况下，起泡排序和归并排序的效率（clock()函数记时）
（3）在顺序的复数向量中，实现区间查找算法，查找出模介于[m1,m2) 的所有元素，按序存于一个子向量中作为返回值。
*/
#include <iostream>
#include "Vector.h"
#include "Complex.h"
#include <ctime>//用于获取随机数种子和clock()函数 
#include <chrono>
using namespace std::chrono; 
inline void PRINT (Vector<Complex<int>>);
int main()
{
	srand(time(NULL));//获取当前时间对应的随机数种子，确保每次生成随机数都不一样 
	int n;//生成无序复数向量元素的个数
	cout<<"输入想要生成的复数的个数:";
	cin>>n;
	Vector< Complex<int> > Vec(n, n, Complex<int>(0, 0));
	for(int i=0; i<Vec.size(); i++)
	{
		Vec[i] = ( Complex<int> ( rand()%15, rand()%15 ) );//为方便演示只取15以内的随机数 
	}
	cout<<"已生成..."<<endl;

	Vec.insert( Complex<int> (10, 10) );
	Vec.insert( Complex<int> (10, 10) );
	cout<<"插入后"<<endl;
	PRINT(Vec);
	
	Vec.unsort();
	cout<<"置乱后"<<endl;
	PRINT(Vec);
	
	Vec.remove(2);
	cout<<"删除秩为2的元素后"<<endl;
	PRINT(Vec);
	
	Vec.sort();
	cout<<"排序后"<<endl;
	PRINT(Vec);
	
	Vec.uniquify();
	cout<<"归一后"<<endl;
	PRINT(Vec);
	
	cout<<"查找10+10i位置为:"<<Vec.search(Complex<int> (10, 10))<<endl;
	
	cout<<"顺序情况下"<<endl;
	auto start = high_resolution_clock::now();  // 使用高精度时钟
	Vec.bubbleSort(0, Vec.size());
	auto end = high_resolution_clock::now();  // 使用高精度时钟
	auto elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "冒泡运行时间: " << elapsed_time.count() << " 秒" << endl;

	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;

	cout<<"乱序情况下"<<endl;
	Vec.unsort(); 
	start = high_resolution_clock::now(); 
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "冒泡运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;
	
	cout <<"逆序情况下"<<endl;
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;
	
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;
	
	cout<<"查找模在[4, 10)之间的复数"<<endl; 
	Vector< Complex<int> > VVV = Vec.findInRange(4, 10);
	PRINT(VVV); 
	
	return 0; 											
}
inline void PRINT (Vector<Complex<int>> vec)
{
	Rank i=0;
	if(vec.size()==0)
		cout<<"无"<<endl;
	while(i < vec.size())
	{
		vec[i].ComPrint();
		cout<<endl;
		i++;
	}
}

