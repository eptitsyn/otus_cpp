#pragma once

#include <cstddef>
#include <iostream>
#include <list>
#include <algorithm>
//my Allocator

template <class T, std::size_t chunkSize = 1> 
class myallocator {
public:
	using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    struct Chunk
    {
    	T* _data = static_cast<T*>(::operator new(chunkSize * sizeof(T)));
    	T* _lastFree = _data;
        size_t used = 0;
        Chunk(){
            if (!_data)
            throw std::bad_alloc();
            // std::cout << ">C:" << std::flush;
        }
        ~Chunk(){ 
            // std::cout << "<C:" << std::flush;
            ::operator delete(_data); }
    };

    template<typename U>
    struct rebind {
        using other = myallocator<U, chunkSize>;
    };

	myallocator() = default;
    ~myallocator() = default;

    template <class Tp, std::size_t Cs>
    myallocator(const myallocator<Tp, Cs>&){
    };

    T* allocate(std::size_t n){
        if (n > chunkSize) 
            throw std::bad_alloc();

        //look for place in existing chunks
        for(Chunk& i : _pool){
            if((unsigned)(i._data+chunkSize-i._lastFree) >= n){
                std::cout << "'atc'" << std::flush;
                return addtoChunk(i, n);
            }
        }

        //add chunk
        Chunk& c = _pool.emplace_back();
        return addtoChunk(c, n);
    }

    T* addtoChunk(Chunk& chunk, std::size_t n){
        T* result = chunk._lastFree;
        chunk._lastFree += n;
        chunk.used +=n;
        return result;
    }
    
    void deallocate(T* p, std::size_t n){
        auto chunk = find_if(_pool.begin(), _pool.end(), 
            [p](const Chunk& i) { 
                return (p >= i._data && p <= (i._data + chunkSize) ); 
            });
        if (chunk == _pool.end()) 
            throw std::exception();
        
        chunk->used -= n;
        if(chunk->used == 0){
            _pool.erase(chunk);
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) {
        p->~T();
    }

    void reserve(std::size_t n){
    	std::cout << "reserve " << n << std::endl;
    }
private:
	std::list<Chunk> _pool;
};	