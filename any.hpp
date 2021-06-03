#pragma once

#include <exception>
#include <memory>
#include <cstring>
#include <typeinfo>
#include <type_traits>
#include <stdexcept> 

#ifndef __ANY_HPP_INCLUDED
#define __ANY_HPP_INCLUDED

const char* transfer(const char* word){
    if(strcmp(word,"i")==0) return "integer";
    else if(strcmp(word,"b")==0) return "bool";
    else if(strcmp(word,"PKc")==0) return "char*";
    else if(strcmp(word,"c")==0) return "char";
    else if(strcmp(word,"d")==0) return "double";
    else if(strcmp(word,"f")==0) return "double";
    else if(strcmp(word,"4listI3anyE")==0) return "list<any>";
    else if(strcmp(word,"NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE")==0) return "string";
    else return word;
}
    


class DIFFERENT_TYPE_ERROR: public std::exception
{
    public:
    DIFFERENT_TYPE_ERROR(const char* left,const char* right){
        sprintf(errstr,"Cannot compare between different type(%s and %s).",transfer(left),transfer(right));
    }
        const char* what() const throw() override{
                return errstr;
            }
    private:
        char errstr[100];
};


class any;

template<class Type> Type any_cast(any&);
template<class Type> Type any_cast(const any&);
template<class Type> Type* any_cast(any*);
template<class Type> const Type* any_cast(const any*);

struct bad_any_cast : public std::bad_cast {};

class any {
public:

    template<class Type> friend 
    Type any_cast(any&);
    
    template<class Type> 
    friend Type any_cast(const any&);
    
    template<class Type> 
    friend Type* any_cast(any*);
    
    template<class Type> 
    friend const Type* any_cast(const any*);
    
    any():ptr(nullptr){}

    any(any&& x): ptr(std::move(x.ptr)){}
        
    any(const any& x) {
        if (x.ptr)
            ptr = x.ptr->clone();
    }
    
    template<class Type> any(const Type& x) 
        : ptr(new concrete<typename std::decay<const Type>::type>(x)) 
        {}
    
    any operator+(const any& rhss) const {
        if(this->type()!=rhss.type()){
            throw std::invalid_argument("Cannot add between different type.");
        }
        any rhs = rhss;
        any wtf = *this;
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) + any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) + any_cast<double>(rhs);
        }
        else if (temp==typeid(std::string).name()){
            return any_cast<std::string>(wtf) + any_cast<std::string>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    any operator-(const any& rhss) const {
        if(this->type()!=rhss.type()){
            throw std::invalid_argument("Cannot minus between different type.");
        }
        any rhs = rhss;
        any wtf = *this;
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) - any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) - any_cast<double>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    any operator*(const any& rhss) const {
        if(this->type()!=rhss.type()){
            throw std::invalid_argument("Cannot multiply between different type.");
        }
        any rhs = rhss;
        any wtf = *this;
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) * any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) * any_cast<double>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    any operator/(const any& rhss) const {
        if(this->type()!=rhss.type()){
            throw std::invalid_argument("Cannot divide between different type.");
        }
        any rhs = rhss;
        any wtf = *this;
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) / any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) / any_cast<double>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator&(const any& rhss) const {
        if(this->type()!=rhss.type()){
            throw DIFFERENT_TYPE_ERROR(this->type().name(),rhss.type().name());
        }
        any rhs = rhss;
        any wtf = *this;
        auto temp = this->type().name();
        if (temp==typeid(bool).name()){
            return any_cast<bool>(wtf) & any_cast<bool>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator|(const any& rhss) const {
        if(this->type()!=rhss.type()){
            throw DIFFERENT_TYPE_ERROR(this->type().name(),rhss.type().name());
        }
        any rhs = rhss;
        any wtf = *this;
        auto temp = this->type().name();
        if (temp==typeid(bool).name()){
            return any_cast<bool>(wtf) | any_cast<bool>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator>(const any& rhss) const {
        any rhs = rhss;
        any wtf = *this;
        if(this->type()!=rhs.type()){
            throw DIFFERENT_TYPE_ERROR(this->type().name(),rhss.type().name());
        }
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) > any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) > any_cast<double>(rhs);
        }
        else if (temp==typeid(char).name()){
            return any_cast<char>(wtf) > any_cast<char>(rhs);
        }
        else if (temp==typeid(bool).name()){
            return any_cast<bool>(wtf) > any_cast<bool>(rhs);
        }
        else if (temp==typeid(std::string).name()){
            return any_cast<std::string>(wtf) > any_cast<std::string>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator<(const any& rhss) const {
        any wtf = *this;
        any rhs = rhss;
        if(this->type()!=rhs.type()){
            throw DIFFERENT_TYPE_ERROR(this->type().name(),rhss.type().name());
        }
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) < any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) < any_cast<double>(rhs);
        }
        else if (temp==typeid(char).name()){
            return any_cast<char>(wtf) < any_cast<char>(rhs);
        }
        else if (temp==typeid(bool).name()){
            return any_cast<bool>(wtf) < any_cast<bool>(rhs);
        }
        else if (temp==typeid(std::string).name()){
            return any_cast<std::string>(wtf) < any_cast<std::string>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator==(const any& rhss)const {
        any rhs = rhss;
        any wtf = *this;
        if(this->type()!=rhs.type()){
            if(this->type().name()==typeid(bool).name() && rhss.type().name()==typeid(int).name()){
                return any_cast<bool>(wtf) == any_cast<int>(rhs);
            }
            else if(this->type().name()==typeid(int).name() && rhss.type().name()==typeid(bool).name()){
                return any_cast<int>(wtf) == any_cast<bool>(rhs);
            }
            else{
                throw DIFFERENT_TYPE_ERROR(this->type().name(),rhss.type().name());
            }
        }
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) == any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) == any_cast<double>(rhs);
        }
        else if (temp==typeid(char).name()){
            return any_cast<char>(wtf) == any_cast<char>(rhs);
        }
        else if (temp==typeid(bool).name()){
            return any_cast<bool>(wtf) == any_cast<bool>(rhs);
        }
        else if (temp==typeid(std::string).name()){
            return any_cast<std::string>(wtf) == any_cast<std::string>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator>=(const any& rhss)const {
        any rhs = rhss;
        any wtf = *this;
        if(this->type()!=rhs.type()){
            throw DIFFERENT_TYPE_ERROR(this->type().name(),rhss.type().name());
        }
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) >= any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) >= any_cast<double>(rhs);
        }
        else if (temp==typeid(char).name()){
            return any_cast<char>(wtf) >= any_cast<char>(rhs);
        }
        else if (temp==typeid(bool).name()){
            return any_cast<bool>(wtf) >= any_cast<bool>(rhs);
        }
        else if (temp==typeid(std::string).name()){
            return any_cast<std::string>(wtf) >= any_cast<std::string>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator<=(const any& rhss)const {
        any rhs = rhss;
        any wtf = *this;
        if(this->type()!=rhs.type()){
            throw DIFFERENT_TYPE_ERROR(this->type().name(),rhss.type().name());
        }
        auto temp = this->type().name();
        if(temp==typeid(int).name()){
            return any_cast<int>(wtf) <= any_cast<int>(rhs);
        }
        else if (temp==typeid(double).name()){
            return any_cast<double>(wtf) <= any_cast<double>(rhs);
        }
        else if (temp==typeid(char).name()){
            return any_cast<char>(wtf) <= any_cast<char>(rhs);
        }
        else if (temp==typeid(bool).name()){
            return any_cast<bool>(wtf) <= any_cast<bool>(rhs);
        }
        else if (temp==typeid(std::string).name()){
            return any_cast<std::string>(wtf) <= any_cast<std::string>(rhs);
        }
        else{
            throw std::invalid_argument("Comparison Method Not Implement.");
        }
    }

    bool operator!=(const any& rhs)const {
        return !((*this)==rhs);
    }

    any& operator=(any&& rhs) {
        ptr = std::move(rhs.ptr);
        return (*this);
    }

    any& operator=(const any& rhs) {
        ptr = std::move(any(rhs).ptr);
        return (*this);
    }

    template<class T> any& operator=(T&& x) {
        ptr.reset(new concrete<typename std::decay<T>::type>(typename std::decay<T>::type(x)));
        return (*this);
    }  

    template<class T> any& operator=(const T& x) {
        ptr.reset(new concrete<typename std::decay<T>::type>(typename std::decay<T>::type(x)));
        return (*this);
    }

    void clear() { 
        ptr.reset(nullptr); 
    }

    bool empty() const { 
        return ptr == nullptr; 
    }

    const std::type_info& type() const { 
        return (!empty()) 
            ? ptr->type() 
            : typeid(void); 
    }

    friend std::ostream& operator<<(std::ostream&,const any&);
    
private:
    
    struct placeholder {

        virtual std::unique_ptr<placeholder> clone() const = 0;
        virtual const std::type_info& type() const = 0;
        virtual ~placeholder() {}

    };
    
    template<class T>
    struct concrete : public placeholder {

        concrete(T&& x) 
            : value(std::move(x)) 
            {}

        concrete(const T& x) 
            : value(x) 
            {}

        virtual std::unique_ptr<placeholder> clone() const override {
            return std::unique_ptr<placeholder>(new concrete<T>(value));
        }

        virtual const std::type_info& type() const override { 
            return typeid(T); 
        }

        T value;

    };
    
    std::unique_ptr<placeholder> ptr;
    
};

template<class Type> 
Type any_cast(any& val) {
    if (val.ptr->type() != typeid(Type))
        throw bad_any_cast();
    return static_cast<any::concrete<Type>*>(val.ptr.get())->value;
}

template<class Type> 
Type any_cast(const any& val) {
    return any_cast<Type>(any(val));
}

template<class Type> 
Type* any_cast(any* ptr) {
    return dynamic_cast<Type*>(ptr->ptr.get());
}

template<class Type> 
const Type* any_cast(const any* ptr) {
    return dynamic_cast<const Type*>(ptr->ptr.get());
}


std::ostream& operator<<(std::ostream& out,const any& x){
    any y = x;
    if(x.type().name()==typeid(int).name())
        out<<any_cast<int>(y);
    else if(x.type().name()==typeid(double).name())
        out<<any_cast<double>(y);
    else if(x.type().name()==typeid(bool).name()){
        if(any_cast<bool>(y)) out<<"true";
        else out<<"false";
    }    
    else if(x.type().name()==typeid(char).name())
        out<<'\''<<any_cast<char>(y)<<'\'';
    else if(x.type().name()==typeid(const char *).name())
        out<<'"'<<any_cast<const char *>(y)<<'"';
    else if(x.type().name()==typeid(std::string).name())
        out<<'"'<<any_cast<std::string>(y)<<'"';
    return out;
}


#endif