
template<class T,class Allocator = std::allocator<T>> 
class myvector{
public:
	myvector() = default;

	template <class Tp, class Al = std::allocator<T>>
    myvector(const myvector<Tp, Al>&){
    };

    void push_back(T item){
		if(_size == _capacity){
			grow();
		}
		++_size;
		_data[_size-1] = item;
    }

    void grow(){
    	T* old_data = _data;
		std::size_t oldcap = _capacity;

    	if (_capacity == 0) {_capacity = 1;}
    	else if(_capacity == 1) {_capacity = 2;}
    	else 
    		_capacity *= 2;

    	_data = allocator.allocate(_capacity);
    	//move
		{
			T* p = old_data;
			T* np = _data;
			for(size_t i = 0; i < _size; ++i){
				allocator.construct(np, *p);
				++np;
				++p;
			}
		}
    	//destruct
		{
			T* p = old_data;
			for(size_t i = 0; i < _size; ++i){
				allocator.destroy(p);
				++p;
			}
		}
    	//deallocate
		if(old_data != nullptr)
    		allocator.deallocate(old_data, oldcap);
    }

	T& operator[](size_t index) {
  		return _data[index];
	}

    T* begin(){ return _data; };
  	T* end(){ return _data + _size; };

	size_t size(){return _size;};
	size_t capacity(){return _capacity;};
  private:
  	T* _data = nullptr;
  	size_t _size = 0;
  	size_t _capacity = 0;
	Allocator allocator;
};

