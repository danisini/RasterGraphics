#ifndef _VECTOR_H_
#define _VECTOR_H_

template <class T>
class Vector
{
    private:
        T* arr;
        size_t sz;
    public:
        Vector();
        Vector(const Vector<T>&) = delete;
        Vector<T>& operator=(const Vector<T>&) = delete;
        ~Vector();
        void push_back(const T&);
        void pop_back();
        T& operator[](const size_t&)const;
        size_t size()const;
        void clear();
};
template <class T>
void Vector<T>::clear()
{
    while(sz != 0)
        pop_back();
}
template <class T>
Vector<T>::Vector()
{
    arr = nullptr;
    sz = 0;
}
template <class T>
Vector<T>::~Vector()
{
    if(arr != nullptr)
        delete[] arr;
}
template <class T>
void Vector<T>::push_back(const T& newEl)
{
    T* temp = new T[sz + 1];
    for(size_t i = 0; i < sz; i ++)
        temp[i] = arr[i];
    temp[sz] = newEl;
    delete[] arr;
    arr = temp;
    sz ++;
}
template <class T>
void Vector<T>::pop_back()
{
    T* temp = new T[sz - 1];
    for(size_t i = 0; i < sz; i ++)
        temp[i] = arr[i];
    delete[] arr;
    arr = temp;
    sz --;
}
template <class T>
T& Vector<T>::operator[](const size_t& ind) const
{
    return arr[ind];
}
template <class T>
size_t Vector<T>::size()const
{
    return sz;
}

#endif // _VECTOR_H_
