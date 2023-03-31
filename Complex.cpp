#include "Complex.h"
#include "Vector.h"
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	Complex<int>* ArrCom = new Complex<int>[n];
	for(int i=0; i<n; i++)
	{
		ArrCom[i] = Complex<int> (rand()%15, rand()%15);
		ArrCom[i].ComPrint(); 
		cout<<endl;
	}
	cout<<endl;
	Complex<int> com1 (3, 8);
	Complex<int> com2 (8, 0);
	cout<<com1.modulus()<<endl;
	cout<<com2.modulus()<<endl;
	cout<<(com1 > com2)<<endl;
	/*
	Complex<int> temp;
	int lo=0, hi=10;
	bool sorted;
	while ((++lo < hi)&&!sorted){ //自左向右，逐一检查各对相邻元素是否需要交换 
		sorted = true; //排完序标志 
		if (ArrCom[lo - 1] > ArrCom[lo]){ //若逆序则标志变为“未排序” 
			sorted = false;
			temp = ArrCom[lo-1];
			ArrCom[lo-1] = ArrCom[lo];
			ArrCom[lo] = temp; //并交换一对相邻元素使得局部有序 
		}
	}
	cout<<endl;
	for(int i=0; i<10; i++)
	{
		ArrCom[i].ComPrint(); 
	}
	*/
}
