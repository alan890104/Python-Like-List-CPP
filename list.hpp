#include <iterator>
#include <algorithm>
#include <exception>
#include <vector>
#include "any.hpp"
#ifndef __LIST_HPP_INCLUDED
#define __LIST_HPP_INCLUDED
class LIST_ERROR: public std::exception{
    public:
        virtual const char* what() const throw(){
            return errstr;
        }
    protected:
        const char* errstr = "";

};

class LIST_NOT_FOUND_ELEMENT: public LIST_ERROR
{
    public:
        const char* what() const throw() override{
                return errstr;
            }
    private:
        const char* errstr = "The specified element cannot be found";
};

class INDEX_ERROR: public LIST_ERROR
{
    public:
        INDEX_ERROR(int pos){
            sprintf(errstr,"Error occurs on index %d\n",pos);
        }
        const char* what() const throw() override{
                return errstr;
            }
    private:
        char errstr[100];
};

class SIZE_INCOMPATIBLE_ERROR: public LIST_ERROR
{
    public:
        SIZE_INCOMPATIBLE_ERROR(int size1,int size2){
            sprintf(errstr,"The size of left side is %d but the right side is %d\n",size1,size2);
        }
        const char* what() const throw() override{
                return errstr;
            }
    private:
        char errstr[100];
};

class NOT_DEFINE_ERROR: public LIST_ERROR
{
    public:
        NOT_DEFINE_ERROR(char operate,const char* var_type){
            sprintf(errstr,"The operator %c is not defined over type %s\n",operate,var_type);
        }
        const char* what() const throw() override{
                return errstr;
            }
    private:
        char errstr[100];
};

class INPUT_ERROR: public LIST_ERROR
{
    public:
        INPUT_ERROR(){
            sprintf(errstr,"The input shold be [0,1].\n");
        }
        const char* what() const throw() override{
                return errstr;
            }
    private:
        char errstr[100];
};

class LIST_WARNING: public LIST_ERROR
{
    public:
        LIST_WARNING(){}
        LIST_WARNING(const char * s){
            sprintf(errstr,"%s",s);
        }
        const char* what() const throw() override{
                return errstr;
            }
    private:
        char errstr[100]="To assign value, you should use where() instead.\n";
};


template<typename T>
class list{
    public:
        list(){}
        list(const std::initializer_list<T>& x):a(x){}
        list(const  int size):a(size){}
        list(const  int  size,const  T value):a(size, value){}
        list(const list<T> &b){
            a = b.a;
        }
        ~list(){
            a.clear();
        }

        list& operator=(T right_hand_side[]){
            a.insert(a.begin(),right_hand_side,sizeof(right_hand_side)/sizeof(*right_hand_side));
             return *this;
        }
        T operator[](int pos) const{// const after function : function cannot revise member of class,ex: vector a cannot be revised in this function
            if(pos>=this->len() || -pos>this->len()){
                throw INDEX_ERROR(pos); 
            }
            return pos>=0? a[pos]:a[a.size()+pos];
        }
        T& operator[](int pos){
            if(pos>=this->len() || -pos>this->len()){
                throw INDEX_ERROR(pos); 
            }
            return pos>=0? a[pos]:a[a.size()+pos];
        }
        template<typename U>
        list operator[](const list<U>& rhs){
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp;
            for(int i=0;i<a.size();i++){
                if(rhs[i]==1){
                    tmp.append(a[i]);
                }
                else if(rhs[i]!=0){
                    throw INPUT_ERROR();
                    break;
                }
            }
            return tmp;
        }

        // template<typename U>
        //  list& operator[](list<U> rhs){
        //     throw LIST_WARNING();
        //     return *this;
        // }

        list operator+(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = a[i]+rhs.a[i];
            }
            return tmp;
        }
        list operator-(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = a[i]-rhs.a[i];
            }
            return tmp;
        }
        list operator*(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = a[i]*rhs.a[i];
            }
            return tmp;
        }
        list operator/(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = a[i]/rhs.a[i];
            }
            return tmp;
        }
        list operator>(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(a.size(),rhs.a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]>rhs.a[i]);
            }
            return tmp;
        }
        template<typename U>
        list operator>(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]>num);
            }
            return tmp;
        }
        list operator>=(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]>=rhs.a[i]);
            }
            return tmp;
        }
        template<typename U>
        list operator>=(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]>=num);
            }
            return tmp;
        }
        
        list operator==(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(a.size(),rhs.a.size());
            }
            list<T> tmp;
            for(int i=0;i<a.size();i++){
                tmp.append( a[i]==rhs.a[i] );
            }
            return tmp;
        }
        template<typename U>
        list operator==(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]==num);
            }
            return tmp;
        }
        list operator<=(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]<=rhs.a[i]);
            }
            return tmp;
        }
        template<typename U>
        list operator<=(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]<=num);
            }
            return tmp;
        }
        list operator<(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]<rhs.a[i]);
            }
            return tmp;
        }
        template<typename U>
        list operator<(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]<num);
            }
            return tmp;
        }
        list operator!=(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]!=rhs.a[i]);
            }
            return tmp;
        }
        template<typename U>
        list operator!=(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]!=num);
            }
            return tmp;
        }
        list operator&(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]&rhs.a[i]);
            }
            return tmp;
        }
        template<typename U>
        list operator&(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]&num);
            }
            return tmp;
        }
        list operator|(const list<T> &rhs) const{ 
            if (rhs.a.size()!=a.size()){
                throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
            }
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]|rhs.a[i]);
            }
            return tmp;
        }
        template<typename U>
        list operator|(const U &num) const{ 
            list<T> tmp(a.size());
            for(int i=0;i<a.size();i++){
                tmp.a[i] = (a[i]|num);
            }
            return tmp;
        }
        // list operator^(const list<T> &rhs) const{ 
        //     if (rhs.a.size()!=a.size()){
        //         throw SIZE_INCOMPATIBLE_ERROR(rhs.a.size(),a.size());
        //     }
        //     list<T> tmp(a.size());
        //     for(int i=0;i<a.size();i++){
        //         tmp.a[i] = (a[i]^rhs.a[i]);
        //     }
        //     return tmp;
        // }
        // template<typename U>
        // list operator^(const U &num) const{ 
        //     list<T> tmp(a.size());
        //     for(int i=0;i<a.size();i++){
        //         tmp.a[i] = (a[i]^num);
        //     }
        //     return tmp;
        // }

        template<typename U,typename V>
        void where(const list<U> &mask,V value) const{// output elements which meets the condition
            list<T> tmp;
            for(int i=0;i<a.size();i++){
                if(mask[i]==1){
                    tmp.append(value);
                }
                else if(mask[i]==0){
                    tmp.append(a[i]);
                }
                else{
                    throw INPUT_ERROR();
                    break;
                }
            }
            a = tmp;
        }

        void append(T item){
            a.emplace_back(item);
        }
        void extend(list<T>& b){
            a.insert(a.end(), b.a.begin(), b.a.end());
        }
        void insert(int pos, T item){
            pos = (pos>=0? pos:a.size()+pos+1);
            a.insert(a.begin()+pos,item);
        }
        void reverse(){
            std::reverse(a.begin(),a.end());
        }
        void sort(int start=0,int end=-1,bool increase=true){
            if(end==-1) end = a.size();
            if(increase)   std::sort(a.begin()+start,a.begin()+end);
            else           std::sort(a.begin()+start,a.begin()+end,std::greater<int>());
        }
        T pop(int element=-1){
            int pos = element;
            if(element==-1){
                pos = a.size()-1;
            }
            T &ret = a.at(pos);
            a.erase(a.begin()+pos);
            return ret;
        }
        int index(T item){
            typename std::vector<T>::iterator iter;
            for(iter=a.begin();iter!=a.end();iter++){
                if(*iter==item){
                    return *iter;
                }
            }
            throw LIST_NOT_FOUND_ELEMENT();
        }
        const int len() const{
            return (int)a.size();
        }

        template <typename U>
        friend std::ostream& operator<<(std::ostream&,const list<U>&);
        friend void recursive(std::ostream& out,const list<any>& ls);
    private:
        std::vector<T> a;
};

template <typename T>
std::ostream& operator<<(std::ostream& out,const list<T>& tmp)
{
    list<T> ls = tmp;
    out<<'[';
    for(int i=0;i<ls.len();i++){ 
        if(i!=0)out<<", ";
        if(ls.a[i].type().name()==typeid(list<any>).name())
            recursive(out,any_cast< list<any> >(ls.a[i]));
        else
            out<<ls.a[i];
    }
    out<<"]\n";
    return out;
}


void recursive(std::ostream& out,const list<any>& tmp){
    list<any> ls = tmp;
    out<<'[';
    for(int i=0;i<ls.len();i++){ 
        if(i!=0)out<<", ";
        if(ls.a[i].type().name()==typeid(list<any>).name())
            recursive(out,any_cast< list<any> >(ls.a[i]));
        else
            out<<ls.a[i];
    }
    out<<"]";
}

#endif