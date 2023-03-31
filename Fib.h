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

class MyFib : public Fib { // 继承自Fib类
public:
    MyFib(Rank n) : Fib(n) {} // 在public中构造函数，调用Fib的protected构造函数
    Rank getFib() { return get(); } // 在public中提供访问protected函数的接口
    Rank getNextFib() { return next(); }
    Rank getPrevFib() { return prev(); }
};
