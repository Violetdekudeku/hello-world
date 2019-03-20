#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<stdexcept>
using namespace std;
 
class integer
{
    friend istream& operator>>(istream& is,integer&);
    friend ostream& operator<<(ostream& os,const integer&);//
    friend bool operator>(const integer &,const integer&);//
    friend bool operator<(const integer &,const integer&);//
    friend bool operator>=(const integer &,const integer&);//
    friend bool operator<=(const integer &,const integer&);//
    friend bool operator==(const integer &,const integer&);//
    friend bool operator!=(const integer &,const integer&);//
    friend integer operator+(const integer&,const integer&);//
    friend integer operator-(const integer&,const integer&);//
    friend integer operator*(const integer&,const integer&);//
    friend integer operator/(const integer&,const integer&);//
    friend integer operator%(const integer&,const integer&);//
    friend integer abs(const integer&);//
    friend integer operator-(const integer& num);//
public:
    integer& operator=(const integer &);//
    integer& operator++();
    integer operator++(int);
    integer& operator--();
    integer operator--(int);
    integer& operator+=(const integer&);
    integer& operator-=(const integer&);
    integer& operator*=(const integer&);
    integer& operator/=(const integer&);
    integer& operator%=(const integer&);
    integer(const char* s="0");//
    integer(const long long int& num);//
    integer(const integer& num);//
    virtual ~integer();//

private:
    struct _int
    {
public:
        _int(const char*str="0");
        _int(const long long&);
        _int(const _int&);
        void show()const;
        ~_int();
        _int(size_t,short);
        static _int add(const _int&,const _int&);
        static _int sub(const _int&,const _int&);
        static _int mul(const _int&,const _int&);
        static _int div(const _int&,const _int&);
        static _int mod(const _int&,const _int&);
        static void intcpy(_int&,const _int&);
        static bool big(const _int&,const _int&);
        static bool low(const _int&,const _int&);
        static bool equ(const _int&,const _int&);
        short *p;
        size_t len;
    }*p;
    bool sign;
};

integer::_int::_int(const char* str):p(0),len(1)
{
    char* t_str=(char*)str;
    if(strlen(str)==0)
    {
        len=1;
        p=new short[len];
        p[0]=0;
        return;
    }
    while(*t_str=='0')t_str++;
    if(t_str==&str[strlen(str)]&&*(t_str-1)=='0')
    {
        len=1;
        p=new short[len];
        p[0]=0;
    }
    else
    {
        int t_len=strlen(t_str),t_sum=0;
        len=t_len%4==0?t_len/4:t_len/4+1;
        int index=0;
        p=new short[len];
        string s(t_str);
        reverse(s.begin(),s.end());
        string::iterator it=s.begin();
        for(it=s.begin(); it<s.end()-4; it+=4)
        {
            reverse(it,it+4);
        }
        reverse(it,s.end());
        for(int i=0; i<t_len; ++i)
        {
            t_sum=t_sum*10+s.c_str()[i]-'0';
            if((i!=0&&(i+1)%4==0)||i==t_len-1)
            {
                p[index++]=t_sum;
                t_sum=0;
            }
        }
    }
}
integer::_int::_int(const long long& num):p(0),len(1)
{
    int t_len=0;
    long long temp(num);
    while(temp>0)temp/=10,t_len++;
    len=t_len%4==0?t_len/4:t_len/4+1;
    p=new short [len];
    temp=num;
    for(int i=0; i<(int)len; ++i)
    {
        p[i]=temp%10000;
        temp/=10000;
    }
}

integer::_int::_int(const _int&other):p(0),len(1)
{
    this->len=other.len;
    p=new short [len];
    for(size_t i=0; i<len; i++)
    {
        p[i]=other.p[i];
    }
}
integer::_int::_int(size_t l,short v):p(0),len(1)
{
    len=l;
    p=new short[l];
    for(int i=0; i<(int)l; i++)p[i]=v;
}
integer::_int integer::_int:: add(const _int& a,const _int& other)
{
    int max_len,min_len;
    short *p1=0,*p2=0;
    if(other.len>=a.len)
    {
        p1=a.p,p2=other.p,max_len=other.len,min_len=a.len;
    }
    else
    {
        p1=other.p,p2=a.p,max_len=a.len,min_len=other.len;
    }
    _int sum(max_len+1,0);
    int t_num=0;
    for(int i=0; i<max_len; i++)
    {
        if(i<min_len)t_num=p1[i];
        else t_num=0;
        sum.p[i]+=t_num+p2[i];
        if(sum.p[i]>=10000)
        {
            sum.p[i]-=10000;
            sum.p[i+1]++;
        }
    }
    if(sum.p[max_len]==0)sum.len--;
    return sum;
}
integer::_int integer::_int:: sub(const _int& a,const _int& b)
{
    int max_len,min_len;
    short *p1=0,*p2=0;
    max_len=a.len,min_len=b.len;
    p1=a.p,p2=b.p;
    _int sub(max_len+1,0);
    int t_num=0;
    for(int i=0; i<max_len; ++i)
    {
        if(i<min_len)t_num=p2[i];
        else t_num=0;
        sub.p[i]+=p1[i]-t_num;
        if(sub.p[i]<0)
        {
            sub.p[i+1]--;
            sub.p[i]+=10000;
        }
    }
    sub.len--;
    while(sub.len>1&&sub.p[sub.len-1]==0)sub.len--;
    return sub;
}
integer::_int integer::_int:: mul(const _int& a,const _int& other)
{
    _int result(a.len+other.len,0);;
    for(int i=0; i<(int)result.len; i++)
        result.p[i]=0;
    int index=0;
    for(int i=0; i<(int)a.len; i++)
    {
        index=i;
        for(int j=0; j<(int)other.len; j++)
        {
            int mul=a.p[i]*other.p[j];
            result.p[index]+=mul%10000;
            if(result.p[index]>=10000)result.p[index+1]++,result.p[index]-=10000;
            result.p[++index]+=mul/10000;
            if(result.p[index]>=10000)result.p[index+1]++,result.p[index]-=10000;
        }
    }
    for(int i=result.len-1; i>0; i--)
    {
        if(result.p[i]==0)
            result.len--;
        else break;
    }
    return result;
}
 
integer::_int integer::_int:: div(const _int& a,const _int& b)
{
    vector<_int>v;
    v.reserve(10000);
    if(low(a,b))return "0";
    _int res("0");
    _int zero("0");
    v.push_back(_int("1"));
    _int base(a);
    _int sub_num;
    while(!low(base,b))
    {
        intcpy(sub_num,mul(v[v.size()-1],b));
        if(!low(base,sub_num))
        {
            ;
            intcpy(base,sub(base,sub_num));
            intcpy((res),add(res,v[v.size()-1]));
            v.push_back(mul(v[v.size()-1],2));
        }
        else if(equ(v[v.size()-1],"1"))
        {
            break;
        }
        else
            v.erase(v.end()-1);
    }
    return res;
}
 
integer::_int integer::_int:: mod(const _int& a,const _int& b)
{
    vector<_int>v;
    v.reserve(10000);
    if(low(a,b))return "0";
    _int res("0");
    _int zero("0");
    v.push_back(_int("1"));
    _int base(a);
    _int sub_num;
    while(!low(base,b))
    {
        intcpy(sub_num,mul(v[v.size()-1],b));
        if(!low(base,sub_num))
        {
            ;
            intcpy(base,sub(base,sub_num));
            intcpy((res),add(res,v[v.size()-1]));
            v.push_back(mul(v[v.size()-1],2));
        }
        else if(equ(v[v.size()-1],"1"))
        {
            break;
        }
        else
            v.erase(v.end()-1);
    }
    return base;
}

void integer::_int:: intcpy(_int& dest,const _int&src)
{
    if(&dest!=&src)
    {
        delete []dest.p;
        dest.p=0;
        dest.p=new short[src.len];
        for(int i=0; i<(int)src.len; i++)
            dest.p[i]=src.p[i];
        dest.len=src.len;
    }
}
bool integer::_int:: big(const _int& a,const _int& b)
{
    if(a.len>b.len)return true;
    if(a.len<b.len)return false;
    for(int i=a.len-1; i>=0; i--)
    {
        if(a.p[i]<b.p[i])return false;
    }
    if(a.p[0]==b.p[0])return false;
    return true;
}
bool integer::_int:: low(const _int& a,const _int& b)
{
    if(a.len<b.len)return true;
    if(a.len>b.len)return false;
    for(int i=a.len-1; i>=0; i--)
    {
        if(a.p[i]<b.p[i])return true;
    }
    if(a.p[0]==b.p[0])return false;
    return false;
}
bool integer::_int:: equ(const _int& a,const _int& b)
{
    return (!big(a,b))&&(!low(a,b));
}
void integer::_int::show()const
{
    int l=this->len;
    while(l-1>-0&&0==p[l-1])l--;
    printf("%d",p[l-1]);
    for(int i=l-2; i>=0; --i)
    {
        printf("%.4d",p[i]);
    }
}
 
integer::_int::~_int()
{
    delete []p;
}
 
 
integer::integer(const char* s):p(0),sign(0)
{
    if(s[0]=='-')p=new _int(s+1),sign=1;
    else p=new _int(s);
}
integer::integer(const long long int& n):p(0),sign(0)
{
    if(n<0)p=new _int(-n),sign=1;
    else p=new _int(n);
}
integer::integer(const integer& n):p(0),sign(0)
{
    sign=n.sign;
    p=new _int;
    integer::_int::intcpy(*p,*n.p);
}
istream& operator>>(istream& is,integer& num)
{
    string s;
    is>>s;
    num=integer(s.c_str());
    return is;
}
ostream& operator<<(ostream& os,const integer&num)
{
    if(abs(num)=="0")
    {
        printf("0");
        return os;
    }
    if(num.sign==1)printf("-");
    num.p->show();
    return os;
}
 
bool operator>(const integer &a,const integer&b)
{
    if(a.sign^b.sign)
    {
        if(a.sign)return false;
        else return true;
    }
    else
    {
        return integer::_int:: big(*a.p,*b.p);
    }
}
bool operator<(const integer &a,const integer&b)
{
    if(a.sign^b.sign)
    {
        if(a.sign)return true;
        else return false;
    }
    else
    {
        return integer::_int:: low(*a.p,*b.p);
    }
}
bool operator>=(const integer &a,const integer&b)
{
    return a>b||a==b;
}
bool operator<=(const integer &a,const integer&b)
{
    return a<b||a==b;
}
bool operator==(const integer &a,const integer&b)
{
    return !(a<b||b<a);
}
bool operator!=(const integer &a,const integer&b)
{
    return !(a==b);
}
integer operator+(const integer&a,const integer&b)
{
    if(a.sign^b.sign)
    {
        if(a.sign)
        {
            return abs(b)-abs(a);
        }
        else
        {
            return abs(a)-abs(b);
        }
    }
    else
    {
        integer t;
        t.sign=a.sign;
        integer::_int::intcpy(*t.p,integer::_int::add(*a.p,*b.p));
        // cout<<t<<endl;
        return t;
    }
}
integer operator-(const integer&a,const integer&b)
{
    if(a.sign^b.sign)
    {
        if(a.sign)
        {
            integer t=abs(a)+abs(b);
            t.sign=a.sign;
            return t;
        }
        else
        {
            return abs(a)+abs(b);
        }
    }
    else
    {
        if(a.sign==1)
        {
            return -(abs(a)-abs(b));
        }
        else
        {
            integer t;
            if(abs(a)>=abs(b))
            {
 
                t.sign=0;
                integer::_int::intcpy(*t.p,integer::_int::sub(*a.p,*b.p));
            }
            else
            {
                t.sign=1;
                integer::_int::intcpy(*t.p,integer::_int::sub(*b.p,*a.p));
            }
            return t;
        }
    }
}
integer operator*(const integer&a,const integer&b)
{
    integer t;
    t.sign=a.sign^b.sign;
    integer::_int::intcpy(*t.p,integer::_int::mul(*a.p,*b.p));
    return t;
}
integer operator/(const integer&a,const integer&b)
{
    integer t;
    if(abs(b)=="0")throw;
    t.sign=a.sign^b.sign;
    integer::_int::intcpy(*t.p,integer::_int::div(*a.p,*b.p));
    return t;
}
integer operator%(const integer&a,const integer&b)
{
    if(abs(b)=="0")throw ;
    if(abs(a)<abs(b))return a;
    integer t;
    t.sign=a.sign^b.sign;
    integer::_int::intcpy(*t.p,integer::_int::mod(*a.p,*b.p));
    return t;
}
integer abs(const integer & a)
{
    integer t(a);
    t.sign=0;
    return t;
}
integer operator -(const integer&a)
{
    integer t(a);
    t.sign^=1;
    if(abs(a)=="0")t.sign=0;
    return t;
}
integer& integer::operator =(const integer&a)
{
    if(this!=&a)
    {
        sign=a.sign;
        integer::_int::intcpy(*p,*a.p);
    }
    return *this;
}
integer& integer::operator++()
{
    return *this+=1;
}
integer integer:: operator++(int)
{
    integer t=*this;
    *this+=1;
    return t;
}
integer& integer::operator--()
{
    return *this-=1;
}
integer integer::operator--(int)
{
    integer t=*this;
    *this-=1;
    return t;
}
integer& integer::operator+=(const integer&a)
{
    return *this=*this+a;
}
integer& integer::operator-=(const integer&a)
{
    return *this=*this-a;
}
integer& integer::operator*=(const integer&a)
{
    return *this=*this*a;
}
integer& integer::operator/=(const integer&a)
{
    return *this=*this/a;
}
integer& integer::operator%=(const integer&a)
{
    return *this=*this%a;
}
integer::~integer()
{
    delete p;
}

int main()
{
    integer a,b;
    while(cin>>a>>b,!cin.eof())
    {
        cout<<"a+b= "<<a+b<<endl;
        cout<<"a-b= "<<a-b<<endl;
        cout<<"a*b= "<<a*b<<endl;
        cout<<"a/b= "<<a/b<<endl;
        cout<<"a%b= "<<a%b<<endl;
        cout<<"a++= "<<a++<<endl;
        cout<<"a--= "<<a--<<endl;
        cout<<"++b= "<<++b<<endl;
        cout<<"--b= "<<--b<<endl;
        cout<<"a>b= "<<(a>b)<<endl;
        cout<<"a<b= " <<(a<b)<<endl;
        cout<<"a==b = "<<(a==b)<<endl;
    }
    return 0;
}

