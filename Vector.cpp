#include <iostream>
#include <unordered_set>
#include "Vector.h"
#include "Complex.h"

using namespace std;

int main()
{
    int n; // 生成无序复数向量元素的个数
    cout << "输入想要生成的复数的个数:";
    cin >> n;

    Vector<Complex<int>> vec(n, n, Complex<int>(0, 0));

    for (int i = 0; i < n; i++) {
        vec[i] = Complex<int>(rand() % 100, rand() % 100); // 为方便演示只取100以内的随机数
    }

    cout << "原始向量：" << endl;
    for (int i = 0; i < vec.size(); i++) {
        vec[i].ComPrint();
    }
	vec.insert(Complex<int> (10, 10));
	vec.insert(Complex<int> (10, 10));
	vec.insert(Complex<int> (10, 10));//插入几个重复向量
	vec.unsort(); 
    unordered_set<Complex<int>> s;
    for (auto iter = vec.begin(); iter != vec.end();) {
        if (s.count(*iter) == 1) { // 如果元素已经出现过，则删除它
            iter = vec.remove(iter);
        } else { // 否则将元素添加到无序集合中
            s.insert(*iter);
            iter++;
        }
    }

    cout << "唯一化后的向量：" << endl;
    for (int i = 0; i < vec.size(); i++) {
        vec[i].ComPrint();
    }

    return 0;
}
