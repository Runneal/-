typedef int Rank; //定义数据类型Rank，意思差不多是元素的秩相当于数组的元素的位置 
#define DEFAULT_CAPACITY 3 //默认初始容量为3 默认3维向量 
#include <cstdlib> //包含取随机数rand()函数 
#include "Fib.h" // 引入 斐波那契数列 类 
using namespace std; 
template <typename T> class Vector //向量模板类 
{
	protected:
		Rank _size; int _capacity; T* _elem; //规模、容量、数据区属性 
		void copyFrom (T const* A, Rank lo, Rank hi); //复制数组区间A[lo,hi) （前闭后开） √ 
		void expand(); //用于空间不足时扩容 √ 
		void shrink(); //装填因子过小时压缩 √ 

		Rank max(Rank lo, Rank hi); //在区间内选取最大元素
		void selectionSort (Rank lo,Rank hi); //选择排序算法 
		Rank partition (Rank lo, Rank hi); //轴点构造算法 
		void quickSort (Rank lo, Rank hi); //快速排序算法 
		void heapSort (Rank lo, Rank hi); //堆排序 
	public:
		//把排序算法放到了public里方便指定使用哪个排序方法 
		bool bubble (Rank lo, Rank hi); //扫描交换 √
		void bubbleSort (Rank lo, Rank hi); //起泡排序算法  √
		void merge (Rank lo,Rank mi,Rank hi); //归并算法  √
		void mergeSort (Rank lo, Rank hi); //归并排序算法 √
		
		Vector (int c = DEFAULT_CAPACITY, int s = DEFAULT_CAPACITY, T v = 0) //容量为c，规模为s，所有元素初始为v 
		{_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);} //动态申请存储空间s<=c 
		Vector (T const* A, Rank n){copyFrom (A, 0, n);} //数组整体复制 
		Vector (T const* A, Rank lo, Rank hi) {copyFrom (A, lo, hi); }//复制区间 √ 
		Vector (Vector<T> const& V) {copyFrom (V._elem, 0, V._size);} //整体复制该向量 
		Vector (Vector<T> const& V, Rank lo, Rank hi) {copyFrom (V._elem, lo, hi);} //复制该向量区间 
		~Vector(){delete [] _elem;} //释放内部空间 
		Rank size() const {return _size;} //查询规模大小 
		void resize(Rank newSize) {_size = newSize;} //更新规模大小 
		bool empty() const {return !_size;} //判断是否为空，无_size即为空 
		int disordered() const; //判断向量是否已排序 √ 
		Rank find (T const& e) const {return find (e, 0, _size);} //无序向量整体查找 
		Rank find (T const& e, Rank lo, Rank hi) const; //无序向量区间查找 √ 
        template <typename U>
        Vector<T> findInRange(U m1, U m2);
		Rank search (T const& e) const {return (0 >= _size) ? -1 : search (e, 0, _size); } //有序向量整体查找
		Rank search (T const& e, Rank lo, Rank hi) const; //有序向量区间查找
		T& operator[] (Rank r) const; //重载下标操作符"[]"，可以引用向量内元素 
		Vector<T> & operator= (Vector<T> const&); //重载赋值操作符"="，可以直接克隆向量
		T remove (Rank r); //删除秩为r的元素 √ 
		int remove (Rank lo, Rank hi); //插入删除秩在区间[lo, hi)之间的元素 √ 
		Rank insert (Rank r, T const& e); //在r处插入元素 √ 
		Rank insert (T const& e) {return insert (_size, e);} //不指定位置则默认在末位插入元素
		void sort (Rank lo, Rank hi); //对区间[lo, hi)排序 
		void sort() {sort(0, _size);} //对整体排序 
		void unsort (Rank lo, Rank hi); //对区间[lo, hi)置乱 √ 
		void unsort() {unsort (0, _size);} //对整体置乱 √ 
		void reverse (Rank lo, Rank hi); //对区间[lo, hi)倒序
		void reverse() {reverse(0, _size);} 
		int deduplicate(); //无序去重 √ 
		int uniquify(); //有序去重 √ 
		void traverse (void (*) (T&)); //使用函数指针遍历，实现只读或局部修改  √ 
		template <typename VST> void traverse (VST&); //使用函数对象遍历，可全局性修改 √ 
		
    	void copyfrom(T const* A, Rank lo, Rank hi) {this->copyFrom(A, lo, hi);} // 调用基类的copyFrom函数
    	void expanding(){this->expand();}
};

template <typename T> void Vector<T>::copyFrom (T const* A, Rank lo, Rank hi){ //复制向量A的[lo, hi)区间 
	_elem = new T[_capacity = 2*(hi - lo)]; //分配一个新空间 
	_size = 0; //将待从A粘贴的向量规模清零
	while (lo < hi)
		_elem[_size++] = A[lo++]; //将A[lo, hi)中的元素 逐 一 地 复制到_elem[0, hi-lo) 
} 

template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V){ //重载赋值运算符"=" 
	if (_elem)
		delete [] _elem; //若有原本内容则释放原本内容
	copyFrom (V._elem, 0, V.size()); //整体复制向量V
	return *this; //返回当前对象的引用以便链式赋值 
} 

template <typename T> T& Vector<T>::operator[] (Rank r)const{ //重载下标运算符"[]"
	return _elem[r];
}

template <typename T> void Vector<T>::expand (){ //向量空间不足时扩容 ，足够时直接返回 
	if(_size<_capacity)  //判断是否需要扩容 
		return;
	if(_capacity<DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i]; //复制原向量内容 
	}
	delete [] oldElem; //释放原空间 
} 

template <typename T> void Vector<T>::shrink(){ //装填因子过小时压缩向量所占空间
	if(_capacity<DEFAULT_CAPACITY << 1)
		return;
	if(_size << 2 > _capacity)
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for(int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i]; //复制原向量内容 
	}
	delete [] oldElem; //释放原空间 
}

template <typename T> void permute (Vector<T>& V){ //随机置乱向量，使各元素等概率出现于各位置 
	for(int i = V.size(); i>0; i--)
		swap (V[i-1], V[rand() % i]); 
}

template <typename T> void Vector<T>::unsort (Rank lo, Rank hi){ //等概率随机置乱区间[lo, hi)
	T* V = _elem + lo; //将子向量_elem[lo,hi)视作另一向量V[0, hi-lo) 
	for(Rank i = hi-lo; i > 0; i--) //自后向前
		swap (V[i-1], V[rand() % i]); //将V[i-1]与V[0,i)中某一元素随机交换 
}

//判等 
template <typename T> static bool lt (T* a, T* b) {return lt (*a, *b);} //
template <typename T> static bool lt (T& a, T& b) {return a < b;} //
template <typename T> static bool eq (T* a, T* b) {return eq(*a, *b);} //
template <typename T> static bool eq (T& a, T& b) {return a == b;} //a是否与b相等 

template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{ //无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回lo-1 
	while ((lo < hi--)&&(e != _elem[hi]));//从后向前顺序查找 
	return hi; //若hi < lo，则意味着查找失败，否则返回值hi即为所求元素的秩 
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::findInRange(U m1, U m2) {
    Vector<T> result(0, 0, T());
    Rank lo = 0, hi = _size - 1;
    while (lo < hi) {
        Rank mid = (lo + hi) / 2;
        if (_elem[mid] < m1) lo = mid + 1;
        else hi = mid;
    }
    Rank start = lo;
    hi = _size - 1;
    while (lo < hi) {
        Rank mid = (lo + hi) / 2;
        if (_elem[mid] < m2) lo = mid + 1;
        else hi = mid;
    }
    Rank end = lo;
    for (Rank i = start; i < end; i++) {
        result.insert(_elem[i]);
    }
    return result;
}

template <typename T> Rank Vector<T>::insert(Rank r, T const& e){ //将e作为秩为r的元素插入 
	expand(); //若有必要的话对向量进行扩容 
	for (int i = _size; i>r; i--) _elem[i] = _elem[i-1]; //自最后到插入位置，后继元素依次后移一个单元 
	_elem[r] = e; _size++; //插入新元素并更新容量 
	return r; //返回秩 
}

template <typename T> int Vector<T>::remove(Rank lo, Rank hi){ //删除区间[lo, hi) 
	if(lo == hi) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0) 
	while (hi < _size) _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移hi - lo个单元 
	_size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间 
	shrink(); //删除后若有必要则缩容 
	return hi-lo; //返回被删除元素的数目 
}

template <typename T> T Vector<T>::remove(Rank r){ //删除向量中秩为r的元素，0 <= r < size 
	T e = _elem[r]; //备份被删除元素 
	remove (r, r+1); //调用区间删除算法，等效于对区间[r, r+1)的删除 
	return e; //返回被删除元素 
}

template <typename T> int Vector<T>::deduplicate(){ //删除无序向量中重复的元素（高效版） 
	int oldSize = _size; //记录原规模
	Rank i = 1; //从_elem[1]开始 
	while (i < _size) //从头至i位置逐一考查各元素 
		(find (_elem[i], 0, i) < 0)? i++ : remove(i);  //在其前缀中寻找与之雷同者（至多一个） 
	return oldSize - _size; //返回规模变化量，被删除的元素总数 
}

template <typename T> void Vector<T>::traverse(void (*visit) (T&)){  //借助函数指针机制 
	for (int i=0; i < _size; i++)
		visit(_elem[i]); //遍历向量 
}
template <typename T> template <typename VST> //T和VST分别是元素类型和操作器(operator) 
void Vector<T>::traverse (VST& visit) //借助函数对象机制 
{
	for (int i=0; i < _size; i++)
		visit (_elem[i]); //遍历向量 
}

template <typename T> struct Increase{ //函数对象为一个任意类的递增对象 
	virtual void operator() (T& e) {e++;}; //假设T可直接递增或运算符"++"已被重载 
};
template <typename T> void increase (Vector<T> & V) //统一递增向量中各元素 
{ V.traverse( increase<T>() ); } //以Increase<T>()为基本操作进行遍历 

template <typename T> int Vector<T>::disordered() const{ //返回向量中逆序相邻元素对的个数 
	int n=0; //定义并初始化计数器 
	for ( int i=1; i<_size; i++ ) //逐一查找共_size-1对相邻元素 
		if ( _elem[i-1]>_elem[i] ) n++; //若为逆序则计数 
	return n; //当且仅当n=0时向量为有序 
} 
 

template <typename T> int Vector<T>::uniquify() { // 对已排序的向量重复元素剔除算法
	Rank i = 0, j = 0; //初始化各对互异相邻元素的秩
	while (++j < _size) //)逐一扫描 
		if ( _elem[i] != _elem[j]) //当检查到独特的元素时将其前移，重复的元素自然而然的就到后面去了 
			_elem[++i] = _elem[j];
	_size = ++i; shrink(); //扫描完以后一口气将最后面的元素通通去掉 
	return j-i; //返回值反映了向量规模的变化量，即被删除元素的总数 
} 

/*
#include <unordered_set>
template <typename T> 
int Vector<T>::uniquify() {  哈希表法唯一化，难以应用在含复数为元素的向量 
    unordered_set<T> s;
    Rank i = 0, j = 0;
    while (j < _size) {
        if (s.find(_elem[j]) == s.end()) { // 如果元素未出现过，则插入哈希表
            s.insert(_elem[j]);
            _elem[i++] = _elem[j++];
        } else { // 如果元素已经出现过，则直接跳过
            ++j;
        }
    }
    _size = i;
    shrink();
    return j - i;
}
#include <functional> // 包含 hash 函数所在的头文件

template<typename T>
struct ComplexHash {
    std::size_t operator()(const Complex<T>& c) const {
        std::hash<T> hash_fn;
        return hash_fn(c.real()) ^ hash_fn(c.imag());
    }
};
#include <unordered_set> // 包含 unordered_set 类所在的头文件
int main() {
    Vector< Complex<int> > vec;
    // 向 vec 中添加元素
    std::unordered_set< Complex<int>, ComplexHash<int> > seen;
    int i = 0;
    while (i < vec.size()) {
        if (seen.count(vec[i]) == 0) {
            seen.insert(vec[i]);
            i++;
        } else {
            vec.remove(i);
        }
    }
    // 其他代码
}
*/


/*
template <typename T>
int Vector<T>::uniquify() {
    if (_size < 2) return 0;
    int i = 0, j = 0;
    sort(0, _size); // 排序
    while (_elem, _elem + _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}
*/

template <typename T> Rank Vector<T>::search (T const& e, Rank lo, Rank hi) const {
	return (rand() % 2) ? binSearch (_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); //随机使用二分查找法或斐波那契查找法 
} 
/*template <typename T> //返回多个秩的查找 
std::vector<Rank> Vector<T>::search(T const& e, Rank lo, Rank hi) const {
    std::vector<Rank> result;
    Rank r = (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
    if (r >= 0) {
        result.insert(r);
        Rank i = r;
        while (--i >= lo && _elem[i] == e) {
            result.insert(i);
        }
        i = r;
        while (++i < hi && _elem[i] == e) {
            result.insert(i);
        }
    }
    return result;
}*/
template <typename T> static Rank binSearch (T* A, T const& e, Rank lo, Rank hi){ //二分查找法 版本C
	while ( lo < hi ){ //改进后每步迭代只需做一次比较判断，只有两个分支， 而 且 成功查找后会继续查找是否有多个一并输出 
		Rank mi = ( lo + hi ) >> 1; //仍从中点开始 
		(e<A[mi]) ? hi = mi : lo = mi + 1; //进行比较后决定查找前半还是后半段 
	} 
	return --lo; //循环结束时，lo为大于e元素的最小秩，故lo - 1为不大于e的元素的最大秩 
} //改进了无法返回最大秩的缺点，并且失败时也能返回失败的位置 

template <typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
    MyFib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.getFib()) 
			fib.getPrevFib();
        Rank mi = lo + fib.getFib() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else {
			return mi;
        }
    }
    return -1;
}

/*
template <typename T> static Rank binSearch (T* A, T const& e, Rank lo, Rank hi){ //二分查找法 版本A 
	while (lo < hi){ //每步迭代 可能 要做两次比较判断，共有三个分支 
		Rank mi = (lo + hi) >> 1; //以中点为起始点 
		if (e<A[mi]) //查找前半段 
			hi = mi;
		else if (A[mi] < e) //查找后半段 
			lo = mi + 1;
		else //找到后返回位置，提前终止 
			return mi;
	}
	return -1; //查找失败 
} //缺点：①待查找元素重复出现时不能保证返回秩最大的那个； ②查找失败时没法指示在哪里失败
*/


/*
template <typename T> static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
    MyFib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.getFib())
            fib.getPrevFib();
        Rank mi = lo + fib.getFib() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
} //缺点同二分法 A 
*/


/*template <typename T> 输出多个秩的查找方法废案 
static Rank* fibSearch(T* A, T const& e, Rank lo, Rank hi) { //fib查找法 
    Rank* result = new Rank[hi - lo]; //将查找结果存放在一个动态分配数组内 
    int count = 0;
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get()) fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else {
            result[count++] = mi; //将相等元素的秩存入数组 
            lo = mi + 1; // 顺序查找下一个重复元素
        }
    }
    if(count == 0){ //查找失败 
    	delete[] result; //释放数组内存 
    	return nullptr; //返回一个空数组 
	} 
	else{ //查找成功 
		Rank* finalresult = new Rank[count + 1]; //新建一个动态分配数组用来存放最终输出结果 
        for (int i = 0; i < count; i++)
            finalresult[i] = result[i]; // 复制数组元素
        finalresult[count] = -1; // 末尾添加哨兵元素，方便输出
        delete[] result; // 释放数组内存
        return finalresult;
	} 
}*/


/*
template <typename T> static Rank binSearch (T* A, T const& e, Rank lo, Rank hi) { //二分查找法 版本B
	while (i < hi - lo){ //改进后每步迭代只需做一次比较判断，只有两个分支， 而 且 成功查找后会继续查找是否有多个一并输出 
		Rank mi = ( lo + hi ) >> 1; //仍从中点开始 
		(e<A[mi])?hi = mi:lo = mi; //进行比较后决定查找前半还是后半段 
	} //查找区间内仅含一个元素A[lo] 
	return (e == A[lo])?lo:-1; //成功找到后返回对应的秩，一个没找到就返回-1 
} //缺点没变 
*/

/*template <typename T> static Rank* binSearch(T* A, T const& e, Rank lo, Rank hi) { // 二分查找法 版本C 究极无敌plus重置版 废案 
    Rank* result = new Rank[hi - lo];
    int count = 0;
    while (lo < hi) { // 改进后每步迭代只需做一次比较判断，只有两个分支，而且成功查找后会继续查找是否有多个一并输出
        Rank mi = (lo + hi) >> 1; // 仍从中点开始
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else { // 查找成功时将相等元素的秩压入向量result
            result[count++] = mi;
            for (Rank i = mi - 1; i >= lo && A[i] == e; i--) result[count++] = i;
            for (Rank i = mi + 1; i < hi && A[i] == e; i++) result[count++] = i;
            break;
        }
    }
    if (count == 0) { //查找失败 
    	delete[] result; //释放数组内存 
    	return nullptr; //返回一个空数组 
    }
    else { //查找成功 
        Rank* finalResult = new Rank[count + 1]; //新建一个动态分配数组用来存放最终输出结果 
        for (int i = 0; i < count; i++)
            finalResult[i] = result[i]; //复制数组元素 
        finalResult[count] = -1; //末尾添加哨兵元素，方便输出 
        delete[] result; //释放数组内存 
        return finalResult; // 循环结束时，lo为大于e元素的最小秩，故lo - 1为不大于e的元素的最大秩
    }
} //改进了无法输出重复元素的秩的缺点 */


	//switch (rand() % 2){ //等可能随机选取排序算法 //快排和堆排还没做 
		//case 1: bubbleSort (lo, hi); break; //起泡排序 
		//case 2: selectionSort (lo, hi); break; //选择排序（待做） 
		//case 3: mergeSort (lo, hi); break; //归并排序 
		//case 4: heapSort (lo, hi); break; //堆排序 
		//default: quickSort (lo, hi); break; //快速排序 
	//}
template <typename T> void Vector<T>::sort (Rank lo, Rank hi){ //向量区间[lo, hi)排序 
	(rand() % 2) ? bubbleSort (lo, hi) : mergeSort(lo, hi);
} 

template <typename T> void Vector<T>::bubbleSort (Rank lo, Rank hi){
	while (!bubble (lo, hi--)); //每趟做一遍扫描，直到完全排好序 
} 
template <typename T> bool Vector<T>::bubble (Rank lo, Rank hi){ //对于每一趟的扫描 
	bool sorted = true; //排完序标志 
	while (++lo < hi) //自左向右，逐一检查各对相邻元素是否需要交换 
		if ((_elem[lo - 1] > _elem[lo])){ //若逆序则标志变为“未排序” 
			sorted = false;
			swap ( _elem[lo-1], _elem[lo]); //并交换一对相邻元素使得局部有序 
		}
	return sorted; //返回排序标志，若为true即排完，若为false则再来一趟 
}

template <typename T> //向量归并排序
void Vector<T>::mergeSort (Rank lo, Rank hi){
	if (hi - lo < 2) return; //若单元素区间自然无序则开始归并排序 
	int mi = (lo + hi)/2; //从中点开始 
	mergeSort (lo, mi); mergeSort (mi, hi); //对中点两边分别排序 
	merge (lo, mi, hi); //归并 
}

/*
template <typename T> void Vector<T>::merge (Rank lo, Rank mi, Rank hi){ //对有序向量[lo, mi)和[mi, hi)的归并
	T* A = _elem + lo; //设合并后的向量为向量A[0, hi-lo) = _elem[lo, mi)，规模为hi-lo 
	int lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) = _elem[lo, mi) 
	for (Rank i = 0; i < lb; B[i] = A[i++]); //复制前子向量 
	int lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi) 
    for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc); i++) { //B[j]和C[k]中的较小者接到A的尾部 
        if ((j < lb) && ((k >= lc) || (B[j] <= C[k]))) {
            A[i] = B[j++];
        } else {
            A[i] = C[k++];
        }
    }

	delete [] B; //释放临时空间B 
}  //归并后得到完整的有序向量[lo, hi) 
*/ 
template<typename T> //对复数向量特化归并排序（以子向量元素的模进行排序，调用了比如 B[j].modulus()函数） 
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo; // 左半区间的起始地址
    int lb = mi - lo; T* B = new T[lb]; // B为左半区间副本
    for (Rank i = 0; i < lb; i++) B[i] = A[i]; // 复制左半区间
    T* C = _elem + mi; // 右半区间的起始地址
    int lc = hi - mi; T* D = new T[lc]; // D为右半区间副本
    for (Rank i = 0; i < lc; i++) D[i] = C[i]; // 复制右半区间
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
        if ((j < lb) && (!(k < lc) || (B[j].modulus() < D[k].modulus()))) A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (D[k].modulus() <= B[j].modulus()))) A[i++] = D[k++];
    }
    delete [] B; delete [] D; // 释放临时空间
}
//在上述代码中，mergeSort()函数使用了分治算法的思想，将待排序区间分为左右两个子区间，递归地对两个子区间进行排序，然后再将已经有序的左右两个子序列合并成一个有序序列。
//merge()函数则是用于合并两个有序子序列的函数，它将左右两个子区间分别复制到临时数组B和D中，再用归并排序的思想合并B和D中的元素，最后将合并后的元素复制回原数组中。

template <typename T> void Vector<T>::reverse(Rank lo, Rank hi) { //对有序向量逆序 
    while (lo < hi) {
        swap(_elem[lo++], _elem[--hi]);
    }
}
