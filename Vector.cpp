#include <iostream>
#include <unordered_set>
#include "Vector.h"
#include "Complex.h"

using namespace std;

int main()
{
    int n; // ��������������Ԫ�صĸ���
    cout << "������Ҫ���ɵĸ����ĸ���:";
    cin >> n;

    Vector<Complex<int>> vec(n, n, Complex<int>(0, 0));

    for (int i = 0; i < n; i++) {
        vec[i] = Complex<int>(rand() % 100, rand() % 100); // Ϊ������ʾֻȡ100���ڵ������
    }

    cout << "ԭʼ������" << endl;
    for (int i = 0; i < vec.size(); i++) {
        vec[i].ComPrint();
    }
	vec.insert(Complex<int> (10, 10));
	vec.insert(Complex<int> (10, 10));
	vec.insert(Complex<int> (10, 10));//���뼸���ظ�����
	vec.unsort(); 
    unordered_set<Complex<int>> s;
    for (auto iter = vec.begin(); iter != vec.end();) {
        if (s.count(*iter) == 1) { // ���Ԫ���Ѿ����ֹ�����ɾ����
            iter = vec.remove(iter);
        } else { // ����Ԫ����ӵ����򼯺���
            s.insert(*iter);
            iter++;
        }
    }

    cout << "Ψһ�����������" << endl;
    for (int i = 0; i < vec.size(); i++) {
        vec[i].ComPrint();
    }

    return 0;
}
