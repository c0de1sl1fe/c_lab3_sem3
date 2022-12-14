#pragma once
#include <iostream>
#include "Graphics.h"
#include <math.h>
#include "Graphics.h"

#include <string>
#include <typeinfo>

#include <limits>
#include <vector>

#define SCALE 10

template <class T>
class BinaryImg
{
private:
    std::vector<std::vector<T>> a;


    //T** array;
    int row;
    int col;
    void DrawDot(float x, float y) const;
    void DrawBlankDot(float x, float y) const;
    Graphics* screen;
    void Print();
    BinaryImg<T> And(T rhs) const;
    BinaryImg<T> Or(T rhs) const;
    BinaryImg<T> And(const BinaryImg<T>& rhs) const;
    BinaryImg<T> Or(const BinaryImg<T>& rhs) const;


public:
    
    BinaryImg(int x, int y);
    //for task...
    BinaryImg(const BinaryImg<T>& src) = default;
    ~BinaryImg() = default;
    BinaryImg<T>& operator= (const BinaryImg<T>& src) = default;

    //BinaryImg(const BinaryImg& src);
    //~BinaryImg();
    int GetRow() const;
    int GetCol() const;

    //friend std::ostream& operator<<(std::ostream& os, BinaryImg<T>& obj)
    //{
    //    obj.Print();
    //    return os;
    //}

    bool operator==(const BinaryImg<T>& src) const;
    bool operator!=(const BinaryImg<T>& src) const;

    void operator()(int x, int y, T value); //especially for bool 

    T& operator()(int x, int y);
    T operator()(int x, int y) const;
    BinaryImg operator+(const BinaryImg<T>& src) const;
    BinaryImg operator*(const BinaryImg<T>& src) const;
    BinaryImg operator+(T src) const;
    BinaryImg operator*(T src) const;
    BinaryImg operator!();
    //BinaryImg& operator= (const BinaryImg& src);
    double AccumulationFactor() const;

    friend BinaryImg operator*(T rhs, /*const*/ BinaryImg<T>& src)
    {
        return src.And(rhs);
    }

    friend BinaryImg operator+(T rhs, /*const*/ BinaryImg<T>& src)
    {
        return src.Or(rhs);
    }

    //new
    auto begin() {
        return a.begin();
    }
    //new
    auto end() {
        return a.end();
    }
};


class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err);
    virtual void Print();
    virtual ~EClassException();
};


#include "Class.h"
#include <math.h>
#include <iostream>
#include "Graphics.h"
#define SCALE 10

template <class T>
void BinaryImg<T>::DrawDot(float x, float y) const
{
    screen->DrawSquare(x, y);
}
template <class T>
void BinaryImg<T>::DrawBlankDot(float x, float y) const
{
    screen->DrawLine(x, y, x + SCALE, y);
    screen->DrawLine(x, y, x, y + SCALE);
    screen->DrawLine(x + SCALE, y, x + SCALE, y + SCALE);
    screen->DrawLine(x, y + SCALE, x + SCALE, y + SCALE);
}


template <class T>
BinaryImg<T>::BinaryImg(int x, int y)
{
    screen = NULL;
    if (x <= 0 || y <= 0) { throw EClassException("invalid dimension"); }
    row = x;
    col = y;
    // add new container
    a.resize(row);
    for (auto& i : a)
    {
        i.resize(col);
        for (auto& j : i)
        {
            j = 0;
        }
    }
}

template <>
BinaryImg<bool>::BinaryImg(int x, int y)
{
    screen = NULL;
    if (x <= 0 || y <= 0) { throw EClassException("invalid dimension"); }
    row = x;
    col = y;
    // add new container
    a.resize(row);
    for (int i = 0; i < a.size(); i++)
    {
        a[i].resize(col);
        for (int j = 0; j < a[i].size(); j++)
        {
            a[i][j] = false;
        }
    }
}



// Specialization for char
template <>
BinaryImg<char>::BinaryImg(int x, int y)
{
    screen = NULL;
    if (x <= 0 || y <= 0) { throw EClassException("invalid dimension"); }
    row = x;
    col = y;
    // add new container
    a.resize(row);
    for (auto& i : a)
    {
        i.resize(col);
        for (auto& j : i)
        {
            j = '0';
        }
    }
}


template <class T>
int BinaryImg<T>::GetRow() const { return row; }
template <class T>
int BinaryImg<T>::GetCol() const { return col; }

//need to find out how to iter in two vector in one time
template <class T>
bool BinaryImg<T>::operator==(const BinaryImg<T>& src) const
{
    if (row != src.row || col != src.col) { throw EClassException("Can't cmp imgs with different sizes"); } // probably more fair to trow exception 
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            if (a[i][j] != src.a[i][j]) { return false; }
        }
    }
    return true;
}


template <class T>
bool BinaryImg<T>::operator!=(const BinaryImg<T>& src) const
{
    return !(*this == src);
}


template <class T>
T& BinaryImg<T>::operator()(int x, int y)
{
    if ((x >= row || y >= col) || (x < 0 || y < 0))
    {
        throw EClassException("invalid index");
    }
    //changed need to test
    return a[x][y];
}

template<>
bool& BinaryImg<bool>::operator()(int x, int y)
{
    if ((x >= row || y >= col) || (x < 0 || y < 0))
    {
        throw EClassException("invalid index");
    }
    //changed need to test
    bool tmp = a[x][y];
    return tmp;
}

template<class T>
void BinaryImg<T>::operator()(int x, int y, T value)
{
    if ((x >= row || y >= col) || (x < 0 || y < 0))
    {
        throw EClassException("invalid index");
    }
    a[x][y] = value;
}

template <class T>
T BinaryImg<T>::operator()(int x, int y) const
{
    if ((x >= row || y >= col) || (x < 0 || y < 0))
    {
        throw EClassException("invalid index");
    }
    //changed
    return a[x][y];
}

template<>
bool BinaryImg<bool>::operator()(int x, int y) const
{
    if ((x >= row || y >= col) || (x < 0 || y < 0))
    {
        throw EClassException("invalid index");
    }
    //changed need to test
    bool tmp = a[x][y];
    return tmp;
}


template <class T>
BinaryImg<T> BinaryImg<T>::operator+(const BinaryImg<T>& src) const
{
    return this->Or(src);
}


template <class T>
BinaryImg<T> BinaryImg<T>::operator*(const BinaryImg<T>& src) const
{
    return this->And(src);
}


template <class T>
BinaryImg<T> BinaryImg<T>::operator+(T src) const
{
    return this->And(src);
}


template <class T>
BinaryImg<T> BinaryImg<T>::operator*(T src) const
{
    return this->Or(src);
}


template <class T>
BinaryImg<T> BinaryImg<T>::operator!()
{
    for (auto& i : a)
    {
        for (auto& j : i)
        {
            if (j == 0)
            {
                j = std::numeric_limits<T>::max();
            }
            else
            {
                j = 0;
            }
        }
    }
    return *this;
}

template <>
BinaryImg<bool> BinaryImg<bool>::operator!()
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            if (a[i][j] == 0)
            {
                a[i][j] = true;
            }
            else
            {
                a[i][j] = false;
            }
        }
    }
    return *this;
}

template <>
BinaryImg<char> BinaryImg<char>::operator!()
{
    for (auto& i : a)
    {
        for (auto& j : i)
        {
            if (j == 0)
            {
                j = std::numeric_limits<char>::max();
            }
            else
            {
                j = '0';
            }
        }
    }
    return *this;
}




template <class T>
double BinaryImg<T>::AccumulationFactor() const
{
    int k = 0;
    for (auto i : a)
    {
        for (auto j : i)
        {
            if (j) { k++; }
        }
    }
    return (double)k / ((double)row * (double)col);
}
template <>
double BinaryImg<bool>::AccumulationFactor() const
{
    int k = 0;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            if (!a[i][j]) { k++; }
        }
    }
    return (double)k / ((double)row * (double)col);
}
template <>
double BinaryImg<char>::AccumulationFactor() const
{
    int k = 0;
    for (auto& i : a)
    {
        for (auto& j : i)
        {
            if (j != '0') { k++; }
        }
    }
    return (double)k / ((double)row * (double)col);
}



template <class T>
void BinaryImg<T>::Print()
{

    //screen = new Graphics((row * SCALE) + SCALE * 12, (col * SCALE) + SCALE * 12);
    //for (int i = 0; i < a.size(); i++)
    //{
    //    for (int j = 0; j < a[i].size(); j++)
    //    {
    //        a[i][j] ? DrawDot((float)(i * SCALE), (float)(j * SCALE)) : DrawBlankDot((float)(i * SCALE), (float)(j * SCALE));
    //    }
    //}
    //delete screen;
    for (auto i : a)
    {
        for (auto j : a)
        {
            std::cout << j;
        }
        std::cout<<std::endl;
    }
}


// Specialization for char
template <>
void BinaryImg<char>::Print()
{
    screen = new Graphics((row * SCALE) + SCALE * 12, (col * SCALE) + SCALE * 12);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            a[i][j] != '0' ? DrawDot((float)(i * SCALE), (float)(j * SCALE)) : DrawBlankDot((float)(i * SCALE), (float)(j * SCALE));
        }
    }
    delete screen;
}


template <class T>
BinaryImg<T> BinaryImg<T>::And(T src) const
{
    BinaryImg<T> result(row, col);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            if ((double)a[i][j] * src > std::numeric_limits<T>::max() || (double)a[i][j] * src < std::numeric_limits<T>::min())
            {
                result.a[i][j] = 0;
            }
            else
            {
                result.a[i][j] = a[i][j] * src;
            }
        }
    }

    return result;
}


template <class T>
BinaryImg<T> BinaryImg<T>::Or(T src) const
{
    BinaryImg<T> result(row, col);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            if ((double)a[i][j] + src > std::numeric_limits<T>::max() || (double)a[i][j] + src < std::numeric_limits<T>::min())
            {
                result.a[i][j] = 0;
            }
            else
            {
                result.a[i][j] = a[i][j] + src;
            }
        }
    }
    return result;
}


template <class T>
BinaryImg<T> BinaryImg<T>::And(const BinaryImg<T>& rhs) const
{
    if (row != rhs.row || col != rhs.col) { throw EClassException("Invalid dimensions of imgs"); }
    BinaryImg<T> result(row, col);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {

            if ((double)a[i][j] * rhs.a[i][j] > std::numeric_limits<T>::max() || (double)a[i][j] * rhs.a[i][j] < std::numeric_limits<T>::min())
            {
                result.a[i][j] = 0;
            }
            else
            {
                result.a[i][j] = a[i][j] * rhs.a[i][j];
            }
        }
    }
    return result;
}


template <class T>
BinaryImg<T> BinaryImg<T>::Or(const BinaryImg<T>& rhs) const
{
    if (row != rhs.row || col != rhs.col) { throw EClassException("Invalid dimensions of imgs"); }
    BinaryImg<T> result(row, col);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            double test1 = this->a[i][j];
            double test2 = rhs.a[i][j];

            if ((double)a[i][j] + rhs.a[i][j] > std::numeric_limits<T>::max() || (double)a[i][j] + rhs.a[i][j] < std::numeric_limits<T>::min())
            {
                result.a[i][j] = 0;
            }
            else
            {
                result.a[i][j] = a[i][j] + rhs.a[i][j];
            }
        }
    }
    return result;
}



EClassException::EClassException(const char* err)
{
    strncpy_s(_err, err, 255);
    _err[255] = 0;
}
void EClassException::Print()
{
    std::cout << _err << std::endl;
}
EClassException::~EClassException() {}