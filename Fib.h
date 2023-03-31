typedef int Rank;
#include <iostream>
class Fib {
private:
    Rank f, g;
protected:
    Fib(Rank n) { f = 1; g = 0; while (g < n) next(); }
    Rank get() { return g; }
    Rank next() { g += f; f = g - f; return g; }
    Rank prev() { f = g - f; g -= f; return g; }
};

class MyFib : public Fib { // �̳���Fib��
public:
    MyFib(Rank n) : Fib(n) {} // ��public�й��캯��������Fib��protected���캯��
    Rank getFib() { return get(); } // ��public���ṩ����protected�����Ľӿ�
    Rank getNextFib() { return next(); }
    Rank getPrevFib() { return prev(); }
};
