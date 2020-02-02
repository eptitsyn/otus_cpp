//https://wandbox.org/permlink/P3SskBccnhop89bV
#include <bits/stdc++.h>
#include <boost/static_assert.hpp>

// Реализовать constexpr функцию bin_id - определения ближайшей большей степени двойки 
namespace
{
    constexpr size_t bin_id(size_t x )
	{
        size_t st = 0;
        size_t notpowerof2 = 0;
        
        //std::cout << x;
        while(x > 1-notpowerof2) {
            if (notpowerof2 || (x & 0x1)) notpowerof2 = 1;
            x = x >> 1;
            //std::cout << " < " << x;
            ++st;
        }
        //std::cout << std::endl;
		return st;
	}

    
	BOOST_STATIC_ASSERT(bin_id(0) == 0);
	BOOST_STATIC_ASSERT(bin_id(1) == 0);
	BOOST_STATIC_ASSERT(bin_id(2) == 1);
	BOOST_STATIC_ASSERT(bin_id(4) == 2);
	BOOST_STATIC_ASSERT(bin_id(7) == 3);
	BOOST_STATIC_ASSERT(bin_id(8) == 3);
	BOOST_STATIC_ASSERT(bin_id(9) == 4);
	BOOST_STATIC_ASSERT(bin_id(1023) == 10);
	BOOST_STATIC_ASSERT(bin_id(1024) == 10);
	BOOST_STATIC_ASSERT(bin_id(1025) == 11);
	BOOST_STATIC_ASSERT(bin_id(1024*1024-33) == 20);
	BOOST_STATIC_ASSERT(bin_id(1024*1024) == 20);
	BOOST_STATIC_ASSERT(bin_id(1024*1024+33) == 21);
	BOOST_STATIC_ASSERT(bin_id(1024*1024*1024-127) == 30);
	BOOST_STATIC_ASSERT(bin_id(1024*1024*1024) == 30);
	BOOST_STATIC_ASSERT(bin_id(1024*1024*1024+127) == 31);
	BOOST_STATIC_ASSERT(bin_id(4294967295) == 32);
    
}

int main()
{
    size_t n;
    while(std::cin >> n)
        std::cout << n << " = " << bin_id(n) << std::endl << std::endl;
    return 0;
}