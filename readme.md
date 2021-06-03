---
title:  'python-like LIST in C++'
disqus: hackmd
---

python like list in C++
===
[ ![github](https://img.shields.io/badge/github-alan890104-brightgreen.svg)](https://github.com/alan890104/Python-Like-List-CPP)
![downloads](https://img.shields.io/static/v1?label=size&message=30KB&color=<SUCCESS>)
![build](https://img.shields.io/appveyor/ci/:user/:repo.svg)
![chat](https://img.shields.io/discord/:serverId.svg)

# Github Link
https://github.com/alan890104/Python-Like-List-CPP

## Table of Contents
[TOC]

## Description
You can easily create a list 
It supports int,double,string,char,char*,bool,and any other user-defined class.

## Functionality
```cpp=
<template class T>
class list{
    public:
        //constructor
        list()
        list(const std::initializer_list<T>& x)
        list(const  int size):a(size)
        list(const  int  size,const  T value)
        list(const list<T> &b)
        //functions
        void append(T item)
        void extend(list<T>& b)
        void insert(int pos, T item)
        void reverse()
        void where(const list<U> &mask,V value)
        T pop(int element=-1)
        int index(T item)
        const int len() const
        friend std::ostream& operator<<(std::ostream&,const list<U>&)
        //operator
        //include + - * / == != >= <= > < ostream<<
    private:
        std::vector<T> a;
```

## Construct Example
```cpp=
	list<any> a; // an empty list
	list<any> b(10); // a list with length 10, fill with 0
	list<any> c(10,"char*") // a list with length 10, fill with "char*"
	
	std::string s="alan"
	list<any> d{1,2.5,'c',"str",s,false,list<any>(1,2,3)} // initialize with {} 
	
	list<any> e(d) // e is a deep copy from d
```

## Outstream Overloading Example
```cpp=
	cout<<d; //d = [1,2.5,'c',"str","alan",false,[1,2,3]]
```

## Index Example
```cpp=
	list<any> a{1,2,3,list<any>{'a','b','c'}};
	cout<<a[3][0]; // = 'a'
	
	cout<<a[-1]; // = ['a','b','c']
	
	cout<<a[list<any>{false,true,false,true}]; // = [2,['a','b','c']]
```

## Append Example
```cpp=
	list<any> a{1,2,3},b{4,5,6};
	a.append(b[0]); // a = [1,2,3,4]
	a.append(b);    // a = [1,2,3,[4,5,6]]
```

## Insert Example
```cpp=
	list<any> a{0,1,2,3};
	a.insert(0,'x'); // a = ['x',0,1,2,3]
```

## Extend Example
```cpp=
	list<any> a{1,2,3},b{4,5,6};
	a.extend(b); // a = [1,2,3,4,5,6]
```

## Comparison Example
```cpp=
	list<any> a{1,2.6,'f'},b{4,2.6,'d'};
	cout<<(a==b); //[false,true,false]
```

## Reverse Example
```cpp=
	list<any> a{7,8,9,'end'};
	a.reverse(); // a = ['end',9,8,7]
```

## arithmetic Example
```cpp=
	list<any> a{1,2,3,4},b{1,2,3,4};
	cout<<(a+b); //  = [2,4,6,8]
```

## Where 
```cpp=
	list<any> a{1,2,3,4},idx{false,false,true,true};
	a.where(idx,"nice"); // a = [1,2,"nice","nice"]
```

## Example
```cpp=
#include <iostream>
#include <vector>
#include "list.hpp"
using namespace std;

int main(){
    try{
        list<any> a{1,2,3,4,5,6,7,8},b{1,2,3,4,9,10,11,12},e{false,false,false,true,true,true,true,true},tmp;
        cout<<"a= "<<a;
        cout<<"b= "<<b;
        cout<<"e= "<<e;
        cout<<"(a<b) or (a>=b): ";
        tmp = ((a<b)|(a>=b));
        cout<<tmp;
        cout<<"b[b>4] = ";
        tmp = b[(b>4)];
        cout<<tmp;
        cout<<"(a==b) and e: ";
        cout<<((a==b)&e);
        cout<<"a append b: ";
        a.append(b);
        cout<<a;
        cout<<"a extend b: ";
        a.extend(b);
        cout<<a;
        list<any> f{a,'b',"good",13.5,7,false};
        cout<<"f= "<<f;
    }
    catch(bad_any_cast &e){
        cerr<<e.what()<<endl;
    }
    catch(LIST_NOT_FOUND_ELEMENT &e){
        cerr<<e.what()<<endl;
    }
    catch(INDEX_ERROR &e){
        cerr<<e.what()<<endl;
    }
    catch(SIZE_INCOMPATIBLE_ERROR &e){
        cerr<<e.what()<<endl;
    }
    catch(const std::exception& e){
        cerr<<e.what()<<endl;
    }
    catch(...)
    {
        std::exception_ptr p = std::current_exception();
        std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        cerr<<"exception caught, but continuing...\n";
        return 1;
    }
    return 0;
}

```
## Result
![](https://i.imgur.com/pnZZ06W.png)


## Appendix and FAQ

:::info
**Find this document incomplete?** Leave a comment!
:::

###### tags: `List` `C++` `python` `Container`
