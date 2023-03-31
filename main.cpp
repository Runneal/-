/*
����һ�������࣬�������һ������ĸ������������ظ��
��1�����������в����������������ҡ����ң�ʵ�����鲿����ͬ�������롢ɾ����Ψһ���Ĳ���
��2���Ը�����ģΪ��׼��������ģ��ͬ������£���ʵ��Ϊ��׼�����Ƚ�˳���������������£���������͹鲢�����Ч�ʣ�clock()������ʱ��
��3����˳��ĸ��������У�ʵ����������㷨�����ҳ�ģ����[m1,m2) ������Ԫ�أ��������һ������������Ϊ����ֵ��
*/
#include <iostream>
#include "Vector.h"
#include "Complex.h"
#include <ctime>//���ڻ�ȡ��������Ӻ�clock()���� 
#include <chrono>
using namespace std::chrono; 
inline void PRINT (Vector<Complex<int>>);
int main()
{
	srand(time(NULL));//��ȡ��ǰʱ���Ӧ����������ӣ�ȷ��ÿ���������������һ�� 
	int n;//��������������Ԫ�صĸ���
	cout<<"������Ҫ���ɵĸ����ĸ���:";
	cin>>n;
	Vector< Complex<int> > Vec(n, n, Complex<int>(0, 0));
	for(int i=0; i<Vec.size(); i++)
	{
		Vec[i] = ( Complex<int> ( rand()%15, rand()%15 ) );//Ϊ������ʾֻȡ15���ڵ������ 
	}
	cout<<"������..."<<endl;

	Vec.insert( Complex<int> (10, 10) );
	Vec.insert( Complex<int> (10, 10) );
	cout<<"�����"<<endl;
	PRINT(Vec);
	
	Vec.unsort();
	cout<<"���Һ�"<<endl;
	PRINT(Vec);
	
	Vec.remove(2);
	cout<<"ɾ����Ϊ2��Ԫ�غ�"<<endl;
	PRINT(Vec);
	
	Vec.sort();
	cout<<"�����"<<endl;
	PRINT(Vec);
	
	Vec.uniquify();
	cout<<"��һ��"<<endl;
	PRINT(Vec);
	
	cout<<"����10+10iλ��Ϊ:"<<Vec.search(Complex<int> (10, 10))<<endl;
	
	cout<<"˳�������"<<endl;
	auto start = high_resolution_clock::now();  // ʹ�ø߾���ʱ��
	Vec.bubbleSort(0, Vec.size());
	auto end = high_resolution_clock::now();  // ʹ�ø߾���ʱ��
	auto elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "ð������ʱ��: " << elapsed_time.count() << " ��" << endl;

	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;

	cout<<"���������"<<endl;
	Vec.unsort(); 
	start = high_resolution_clock::now(); 
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "ð������ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;
	
	cout <<"���������"<<endl;
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;
	
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;
	
	cout<<"����ģ��[4, 10)֮��ĸ���"<<endl; 
	Vector< Complex<int> > VVV = Vec.findInRange(4, 10);
	PRINT(VVV); 
	
	return 0; 											
}
inline void PRINT (Vector<Complex<int>> vec)
{
	Rank i=0;
	if(vec.size()==0)
		cout<<"��"<<endl;
	while(i < vec.size())
	{
		vec[i].ComPrint();
		cout<<endl;
		i++;
	}
}

