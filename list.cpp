#include <iostream>
#include <vector>
// # include "any.hpp"
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
