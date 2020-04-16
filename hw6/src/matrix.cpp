#pragma once
#include <tuple>
#include <map>

template<typename T, T default_value>
class Matrix{
    using coords = std::tuple<size_t, size_t>;
    using datastore = std::map<coords, T>;

    class MatrixElement{
        datastore& data;
        size_t row,col;
    public:
        MatrixElement(datastore& data, size_t row, size_t col) : data(data), row(row), col(col){};
        operator T(){ 
            return data.count({row, col}) > 0 ? data[{row, col}] : default_value;}
        operator const T() const {
            return data.count({row, col}) > 0 ? data[{row, col}] : default_value;}
        MatrixElement& operator=(T element){
            if(element != default_value)
                data[{row, col}] = element;
            else 
                data.erase({row,col});
            return *this;
        };
    };

    class MatrixRow{
        datastore& data;
        size_t row;
    public:
        MatrixRow(datastore& data, size_t row): data(data), row(row){}; 
        MatrixElement operator[](size_t columnindex){
            return MatrixElement(data, row, columnindex);
        };
    };

public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T>{
    public:
        iterator(typename datastore::iterator iter) : iter(iter){};
        bool operator==(iterator& rhs){return iter == rhs.iter;}
        bool operator!=(iterator& rhs){return iter != rhs.iter;}
        iterator& operator--(){ --iter; return *this; }
        iterator& operator++(){ ++iter; return *this; }
        std::tuple<size_t, size_t, T> operator*(){ return {std::get<0>(iter->first), std::get<1>(iter->first), iter->second}; }
    protected:
        typename datastore::iterator iter;
    };

    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T>{
    public:
        const_iterator(typename datastore::iterator iter) : iter(iter){};
        bool operator==(iterator& rhs){return iter == rhs.iter;}
        bool operator!=(iterator& rhs){return iter != rhs.iter;}
        const iterator& operator--() const { --iter; return *this; }
        const iterator& operator++() const { ++iter; return *this; }
        std::tuple<size_t, size_t, T> operator*(){ return {std::get<0>(iter->first), std::get<1>(iter->first), iter->second}; }
    protected:
        typename datastore::iterator iter;
    };

    size_t size(){ return data.size(); };
    MatrixRow operator[](size_t index){
        return MatrixRow(data, index);
    };
    Matrix::iterator begin(){ return data.begin(); };
    Matrix::iterator end(){ return data.end(); }; 
private:
    datastore data;
};
