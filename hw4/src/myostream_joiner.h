#pragma once

#include <iterator>
#include <iosfwd>
#include <experimental/type_traits>

using namespace std;

/// Output iterator that inserts a delimiter between elements.
template<typename _DelimT, typename _CharT = char,
        typename _Traits = char_traits<_CharT>>
class myostream_joiner
{
public:
    typedef _CharT                              char_type;
    typedef _Traits                             traits_type;
    typedef basic_ostream<_CharT, _Traits>      ostream_type;
    typedef output_iterator_tag                 iterator_category;
    typedef void                                value_type;
    typedef void                                difference_type;
    typedef void                                pointer;
    typedef void                                reference;

    myostream_joiner(ostream_type& __os, const _DelimT& __delimiter)
    noexcept(is_nothrow_copy_constructible_v<_DelimT>)
    : _M_out(std::addressof(__os)), _M_delim(__delimiter)
    { }

    myostream_joiner(ostream_type& __os, _DelimT&& __delimiter)
    noexcept(is_nothrow_move_constructible_v<_DelimT>)
    : _M_out(std::addressof(__os)), _M_delim(std::move(__delimiter))
    { }

    template<typename _Tp>
    myostream_joiner&
    operator=(const _Tp& __value)
    {
        if (!_M_first)
        *_M_out << _M_delim;
        _M_first = false;
        *_M_out << (int)__value;
        return *this;
    }

    myostream_joiner& operator*() noexcept { return *this; }
    myostream_joiner& operator++() noexcept { return *this; }
    myostream_joiner& operator++(int) noexcept { return *this; }

private:
    ostream_type* _M_out;
    _DelimT _M_delim;
    bool _M_first = true;
};

/// Object generator for ostream_joiner.
template<typename _CharT, typename _Traits, typename _DelimT>
    inline myostream_joiner<decay_t<_DelimT>, _CharT, _Traits>
    make_myostream_joiner(basic_ostream<_CharT, _Traits>& __os,
                        _DelimT&& __delimiter)
    { return { __os, std::forward<_DelimT>(__delimiter) }; }
