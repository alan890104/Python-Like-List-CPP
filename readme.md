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

## Table of Contents

[TOC]

## Description
You can easily create a list 
It supplies int,double,string,char,char*,bool,etc.
and user-defined class also work.

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
