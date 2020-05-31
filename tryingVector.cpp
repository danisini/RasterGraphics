#include <iostream>
#include "vector.hpp"
using namespace std;
int main()
{
    Vector<int> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    v.push_back(3);
    for(int i = 0; i < v.size(); i ++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    v.pop_back();
    for(int i = 0; i < v.size(); i ++)
    {
        cout << v[i] << " ";
    }
    return 0;
}

