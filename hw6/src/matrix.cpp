#include <iostream>
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
        MatrixElement& operator=(T element){
            data[{row, col}] = element;
            return *this;
        };
    };

    class MatrixRow{
        datastore& data;
        size_t rowindex;
    public:
        MatrixRow(datastore& data, size_t rowindex): data(data), rowindex(rowindex){}; 
        MatrixElement operator[](size_t columnindex){
            return MatrixElement(data, rowindex, columnindex);
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

    size_t size(){ return data.size(); };
    MatrixRow operator[](size_t index){
        return MatrixRow(data, index);
    };
    Matrix::iterator begin(){ return data.begin(); };
    Matrix::iterator end(){ return data.end(); }; 
private:
    datastore data;
};

int main(){
    Matrix<int, -1> matrix; // бесконечная матрица int заполнена значениями -1
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    // выведется одна строка
    // 100100314
    for(auto c: matrix)
    {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = c;
    std::cout << x << y << v << std::endl;
    }
    return 0;
}