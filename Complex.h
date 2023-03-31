#include <iostream>
#include <cmath> 
#include <utility>
#include <stdexcept>
template<typename T> class Complex 
{
private:
    T real_;
    T imag_;
    double modulus_;
    
    void update_modulus() { // һ����������ģ��С�ĸ�������
        modulus_ = std::sqrt( std::pow(real_, 2) + std::pow(imag_, 2) );
        modulus_ = modulus_ * 1.00;
    }
public:
	Complex() : real_(0), imag_(0) { update_modulus(); }
	Complex(T real) : real_(real), imag_(0) { update_modulus(); }
    Complex(T real, T imag) : real_(real), imag_(imag) { update_modulus(); }
    
    T real() const { return real_; }
    T imag() const { return imag_; }
    double modulus() const { return modulus_; }
    
    Complex<T> operator-() const { return Complex<T>(-real_, -imag_); } //ȡ�����㣬ʵ���鲿�ֱ�ȡ�� 
    
    Complex<T>& operator=(const Complex<T>& other) { //��ֵ���� 
        if (this == &other) return *this; // ����Ը�ֵ
		real_ = other.real_;
        imag_ = other.imag_;
        update_modulus();
        return *this;
	}
	
    Complex<T> operator+(const Complex<T>& other) const {
        //�ӷ�����
        Complex<T> result(real_ + other.real_, imag_ + other.imag_);
        result.update_modulus();
        return result;
    }

    Complex<T> operator-(const Complex<T>& other) const {
        //��������
        Complex<T> result(real_ - other.real_, imag_ - other.imag_);
        result.update_modulus();
        return result;
    }

    Complex<T> operator*(const Complex<T>& other) const {
        //�˷�����
        Complex<T> result(real_ * other.real_ - imag_ * other.imag_, real_ * other.imag_ + imag_ * other.real_);
        result.update_modulus();
        return result;
    }

    Complex<T> operator/(const Complex<T>& other) const {
        //��������
        T denominator = std::pow(other.real_, 2) + std::pow(other.imag_, 2);
        if (denominator == 0) {
            throw std::runtime_error("Division by zero!"); //������� 
        }
        Complex<T> result((real_ * other.real_ + imag_ * other.imag_) / denominator,
                          (imag_ * other.real_ - real_ * other.imag_) / denominator);
        result.update_modulus();
        return result;
    }
		
	bool operator==(const Complex<T>& other) const { //�������� 
	    return real_ == other.real_ && imag_ == other.imag_;
	}

    bool operator!=(const Complex<T>& other) const {
        //����������
        return !(*this == other);
    }

    bool operator<(const Complex<T>& other) const {
        //С������
        if (modulus_ < other.modulus_) {
            return true;
        } else if (modulus_ == other.modulus_) {
            return real_ < other.real_;
        } else {
            return false;
        }
    }

    bool operator<=(const Complex<T>& other) const {
        //С�ڵ�������
        if (modulus_ < other.modulus_) {
            return true;
        } else if (modulus_ == other.modulus_) {
            return real_ <= other.real_;
        } else {
            return false;
        }
    }
    
    bool operator>(const Complex<T>& other) const {
        //��������
        if (modulus_ > other.modulus_) {
            return true;
        } else if (modulus_ == other.modulus_) {
            return real_ > other.real_;
        } else {
            return false;
        }
    }

    bool operator>=(const Complex<T>& other) const {
        //���ڵ�������
        if (modulus_ > other.modulus_) {
            return true;
        } else if (modulus_ == other.modulus_) {
            return real_ >= other.real_;
        } else {
            return false;
        }
    }
    
    //ֱ�������ֱȽ� 
	bool operator==(const T& other) const {
    	return modulus_ == other;
	}	

	bool operator!=(const T& other) const {
    	return !(*this == other);
	}

	bool operator<(const T& other) const {
    	return modulus_ < other;
	}

	bool operator<=(const T& other) const {
    	return modulus_ <= other;
	}

	bool operator>(const T& other) const {
    	return modulus_ > other;
	}

	bool operator>=(const T& other) const {
    	return modulus_ >= other;
	}
	
	void ComPrint() const {//��ӡ����
		if(real_ != 0)
			std::cout << real_;
    	if (imag_ < 0) {
        	std::cout << imag_ << "i" ;
    	}
		else if (real_ !=0 && imag_ > 0){
			std::cout << "+" << imag_ << "i";
		}
		else if (real_ ==0 && imag_ > 0){
			std::cout << imag_ << "i";
		}
		else if (imag_ == 0){}
		if(real_ == 0 && imag_ == 0 )
			std::cout << real_;
		//�������� -1-1i��-1+1i��1i��-1�� 
	}
};

