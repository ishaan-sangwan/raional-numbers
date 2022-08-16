#include <iostream>
#include <algorithm>
using namespace std;
typedef long Intype;

class rational{
    private:
        Intype numer;
        Intype denom;

        void fixsigns();
        void reduce();
    public:
        // constructor for when only one parameter is given

        rational(const Intype & numerator =0)
            :numer(numerator), denom(1){}

        //constructor for when 2 paramenters are giver

        rational(const Intype & numerator , const Intype & denominator)
            :numer(numerator), denom(denominator){
                fixsigns();
                reduce();
            }

        //constructor for when rational class obj is passed
        //which is the copy constructor 
        rational(const rational & rhs)
            :numer(rhs.numer), denom(rhs.denom){}

        //destructor
        ~rational(){}

        //assignment operators
        const rational & operator= (const rational & rhs);
        const rational & operator+= (const rational & rhs);
        const rational & operator-= (const rational & rhs);
        const rational & operator/= (const rational & rhs);
        const rational & operator*= (const rational & rhs);

        //maths operators
        rational operator+ (const rational & rhs) const;
        rational operator- (const rational & rhs) const;
        rational operator* (const rational & rhs) const;
        rational operator/ (const rational & rhs) const;

        //boolean operators
        bool operator< (const rational& rhs) const;
        bool operator<= (const rational& rhs) const;
        bool operator> (const rational & rhs) const;
        bool operator>= (const rational & rhs) const;
        bool operator==(const rational & rhs) const;
        bool operator!= (const rational & rhs) const;

        //unirary operators
        const rational & operator++();
        const rational & operator--();
        rational operator++(int);
        rational operator--(int);
        const rational & operator+( ) const;
        rational operator-()const;
        bool operator!() const;

        //member functions

        double ToDouble() const{
            return static_cast<double> (numer)/(denom);
        }
        // io friends: privacy is vaived
        friend istream & operator>>(istream & in, rational & value)
{
	in >> value.numer;
	value.denom = 1;
	char ch;
	in.get(ch);
	
	if  (!in.eof())
	{
		if (ch == '/'){
			in>>value.denom;
			value.fixsigns();
			value.reduce();
		}
		else in.putback(ch);
	}
}

friend ostream & operator<<(ostream & out, const rational & value){
	if (value.denom !=0 )
	{
		out << value.numer;
		if (value.denom !=1) out<<'/'<<value;
		return out;
	}
	if (value.numer == 0) out<<"intermediate";
	else
	{
		if (value.numer < 0) out<<'-';
		out<< "infinity";
	}
	return out;
}

    
};

//assignment operators implementation
const rational & rational::operator= (const rational & rhs){
     if (this != &rhs){
        numer = rhs.numer;
        denom = rhs.denom;
    }
    return *this;
}

const rational & rational::operator+= (const rational & rhs){
    numer = numer*rhs.denom +rhs.numer*denom;
    denom = denom*rhs.denom;
    fixsigns();
    reduce();
    return *this;
}

const rational & rational::operator-=(const rational & rhs){
    numer = numer*rhs.denom - rhs.numer*denom;
    denom = denom*rhs.denom;
    reduce();
    return *this;
}

const rational & rational::operator*=(const rational & rhs){
    numer *= rhs.numer;
    denom *= rhs.numer;
    reduce();
    return *this;
}

const rational & rational::operator/=(const rational & rhs){
    numer *= rhs.denom;
    denom *= rhs.numer;
    return *this;
}

//math operator implementation

rational rational::operator+(const rational & rhs)const
{
    rational temp(*this);
    temp += rhs;
    return temp;
}

rational rational::operator-(const rational & rhs)const
{
    rational temp(*this);
    temp -= rhs;
    return temp;
}

rational rational::operator*(const rational & rhs)const
{
    rational temp(*this);
    temp *= rhs;
    return temp;
}

rational rational::operator/(const rational & rhs)const
{
    rational temp(*this);
    temp *= rhs;
    return temp;
}

//boolean operators

bool rational::operator < (const rational & rhs) const
{
    if (numer*rhs.denom< rhs.numer*denom) return true;
    else return false;
}

bool rational::operator == (const rational & rhs) const
{
    if (numer==rhs.numer && denom == rhs.denom) return true;
    else return false;
}

bool rational::operator <= (const rational & rhs) const
{
    if (numer*rhs.denom < rhs.numer*denom || *this == rhs) return true;
    else return false; 
}

bool rational::operator >(const rational & rhs) const
{
    if (numer*rhs.denom > rhs.denom*numer) return true;
    else return false;
}

bool rational::operator>= (const rational & rhs) const
{
    if (numer*rhs.denom >= rhs.denom*numer|| *this ==rhs) return true;
    else return false;
}

bool rational::operator!= (const rational & rhs) const
{
    if(*this == rhs) return false;
    else return true;
}

//unirary operator implentation
rational rational::operator++(int){
    rational temp(*this);
    numer += denom;
    return temp;
}

const rational & rational::operator++ (){
    numer += denom;
    return *this;
}

rational rational::operator--(int){
    rational temp(*this);
    numer -= denom;
    return temp;
}

const rational & rational::operator--()
{
    numer -= denom;
    return *this;
}

bool rational::operator!() const{
    return !numer;
}

const rational & rational::operator+()const{
    return *this;
}

rational rational::operator-()const
{
    return rational(-numer, denom);
}

void rational::fixsigns(){
    if (denom <0){
        denom = -denom;
        numer = -numer;
    }
}
void rational::reduce(){
    Intype d =1;
    if (denom != 0 && numer != 0){
        d =__gcd(numer,denom);
    }
    if (d>1){
        numer /=d;
        denom /=d;
    }
}