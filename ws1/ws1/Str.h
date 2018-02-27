// string standard header
#pragma once
#ifndef _STRING_
#define _STRING_
#ifndef RC_INVOKED
#include <istream>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new

#pragma warning(disable: 4189)
#pragma warning(disable: 4172)
#pragma warning(disable: 4455)

_STD_BEGIN
// basic_string INSERTERS AND EXTRACTORS
template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_istream<_Elem, _Traits>& operator >> (
		basic_istream<_Elem, _Traits>&& _Istr,
		basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// extract a string
	typedef ctype<_Elem> _Ctype;
	typedef basic_istream<_Elem, _Traits> _Myis;
	typedef basic_string<_Elem, _Traits, _Alloc> _Mystr;
	typedef typename _Mystr::size_type _Mysizt;

	ios_base::iostate _State = ios_base::goodbit;
	bool _Changed = false;
	const typename _Myis::sentry _Ok(_Istr);

	if (_Ok)
	{	// state okay, extract characters
		const _Ctype& _Ctype_fac = _USE(_Istr.getloc(), _Ctype);
		_Str.erase();

		_TRY_IO_BEGIN
			_Mysizt _Size = 0 < _Istr.width()
			&& (_Mysizt)_Istr.width() < _Str.max_size()
			? (_Mysizt)_Istr.width() : _Str.max_size();
		typename _Traits::int_type _Meta = _Istr.rdbuf()->sgetc();

		for (; 0 < _Size; --_Size, _Meta = _Istr.rdbuf()->snextc())
			if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			{	// end of file, quit
				_State |= ios_base::eofbit;
				break;
			}
			else if (_Ctype_fac.is(_Ctype::space,
				_Traits::to_char_type(_Meta)))
				break;	// whitespace, quit
			else
			{	// add character to string
				_Str.append(1, _Traits::to_char_type(_Meta));
				_Changed = true;
			}
		_CATCH_IO_(_Istr)
	}

	_Istr.width(0);
	if (!_Changed)
		_State |= ios_base::failbit;
	_Istr.setstate(_State);
	return (_Istr);
}

template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_istream<_Elem, _Traits>& getline(
		basic_istream<_Elem, _Traits>&& _Istr,
		basic_string<_Elem, _Traits, _Alloc>& _Str,
		const _Elem _Delim)
{	// get characters into string, discard delimiter
	typedef basic_istream<_Elem, _Traits> _Myis;

	ios_base::iostate _State = ios_base::goodbit;
	bool _Changed = false;
	const typename _Myis::sentry _Ok(_Istr, true);

	if (_Ok)
	{	// state okay, extract characters
		_TRY_IO_BEGIN
			_Str.erase();
		const typename _Traits::int_type _Metadelim =
			_Traits::to_int_type(_Delim);
		typename _Traits::int_type _Meta = _Istr.rdbuf()->sgetc();

		for (; ; _Meta = _Istr.rdbuf()->snextc())
			if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			{	// end of file, quit
				_State |= ios_base::eofbit;
				break;
			}
			else if (_Traits::eq_int_type(_Meta, _Metadelim))
			{	// got a delimiter, discard it and quit
				_Changed = true;
				_Istr.rdbuf()->sbumpc();
				break;
			}
			else if (_Str.max_size() <= _Str.size())
			{	// string too large, quit
				_State |= ios_base::failbit;
				break;
			}
			else
			{	// got a character, add it to string
				_Str += _Traits::to_char_type(_Meta);
				_Changed = true;
			}
		_CATCH_IO_(_Istr)
	}

	if (!_Changed)
		_State |= ios_base::failbit;
	_Istr.setstate(_State);
	return (_Istr);
}

template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_istream<_Elem, _Traits>& getline(
		basic_istream<_Elem, _Traits>&& _Istr,
		basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// get characters into string, discard newline
	return (getline(_Istr, _Str, _Istr.widen('\n')));
}

template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_istream<_Elem, _Traits>& operator >> (
		basic_istream<_Elem, _Traits>& _Istr,
		basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// extract a string
	return (_STD move(_Istr) >> _Str);
}

template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_istream<_Elem, _Traits>& getline(
		basic_istream<_Elem, _Traits>& _Istr,
		basic_string<_Elem, _Traits, _Alloc>& _Str,
		const _Elem _Delim)
{	// get characters into string, discard delimiter
	return (getline(_STD move(_Istr), _Str, _Delim));
}

template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_istream<_Elem, _Traits>& getline(
		basic_istream<_Elem, _Traits>& _Istr,
		basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// get characters into string, discard newline
	return (getline(_STD move(_Istr), _Str, _Istr.widen('\n')));
}

template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_ostream<_Elem, _Traits>& operator<<(
		basic_ostream<_Elem, _Traits>& _Ostr,
		const basic_string<_Elem, _Traits, _Alloc>& _Str)
{	// insert a string
	typedef basic_ostream<_Elem, _Traits> _Myos;
	typedef basic_string<_Elem, _Traits, _Alloc> _Mystr;
	typedef typename _Mystr::size_type _Mysizt;

	ios_base::iostate _State = ios_base::goodbit;
	_Mysizt _Size = _Str.size();
	_Mysizt _Pad = _Ostr.width() <= 0 || (_Mysizt)_Ostr.width() <= _Size
		? 0 : (_Mysizt)_Ostr.width() - _Size;
	const typename _Myos::sentry _Ok(_Ostr);

	if (!_Ok)
		_State |= ios_base::badbit;
	else
	{	// state okay, insert characters
		_TRY_IO_BEGIN
			if ((_Ostr.flags() & ios_base::adjustfield) != ios_base::left)
				for (; 0 < _Pad; --_Pad)	// pad on left
					if (_Traits::eq_int_type(_Traits::eof(),
						_Ostr.rdbuf()->sputc(_Ostr.fill())))
					{	// insertion failed, quit
						_State |= ios_base::badbit;
						break;
					}

		if (_State == ios_base::goodbit
			&& _Ostr.rdbuf()->sputn(_Str.c_str(), (streamsize)_Size)
			!= (streamsize)_Size)
			_State |= ios_base::badbit;
		else
			for (; 0 < _Pad; --_Pad)	// pad on right
				if (_Traits::eq_int_type(_Traits::eof(),
					_Ostr.rdbuf()->sputc(_Ostr.fill())))
				{	// insertion failed, quit
					_State |= ios_base::badbit;
					break;
				}
		_Ostr.width(0);
		_CATCH_IO_(_Ostr)
	}

	_Ostr.setstate(_State);
	return (_Ostr);
}

// sto* NARROW CONVERSIONS

inline int stoi(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to int
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	long _Ans = _CSTD strtol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoi argument");
	if (errno == ERANGE || _Ans < INT_MIN || INT_MAX < _Ans)
		_Xout_of_range("stoi argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return ((int)_Ans);
}

inline long stol(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to long
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	long _Ans = _CSTD strtol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stol argument");
	if (errno == ERANGE)
		_Xout_of_range("stol argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline unsigned long stoul(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to unsigned long
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	unsigned long _Ans = _CSTD strtoul(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoul argument");
	if (errno == ERANGE)
		_Xout_of_range("stoul argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline long long stoll(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to long long
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	long long _Ans = _CSTD strtoll(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoll argument");
	if (errno == ERANGE)
		_Xout_of_range("stoll argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline unsigned long long stoull(const string& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert string to unsigned long long
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	unsigned long long _Ans = _CSTD strtoull(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoull argument");
	if (errno == ERANGE)
		_Xout_of_range("stoull argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline float stof(const string& _Str, size_t *_Idx = 0)
{	// convert string to float
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	float _Ans = _CSTD strtof(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stof argument");
	if (errno == ERANGE)
		_Xout_of_range("stof argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline double stod(const string& _Str, size_t *_Idx = 0)
{	// convert string to double
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	double _Ans = _CSTD strtod(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stod argument");
	if (errno == ERANGE)
		_Xout_of_range("stod argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline long double stold(const string& _Str, size_t *_Idx = 0)
{	// convert string to long double
	const char *_Ptr = _Str.c_str();
	char *_Eptr;
	errno = 0;
	long double _Ans = _CSTD strtold(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stold argument");
	if (errno == ERANGE)
		_Xout_of_range("stold argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

// sto* WIDE CONVERSIONS
inline int stoi(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to int
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	long _Ans = _CSTD wcstol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoi argument");
	if (errno == ERANGE || _Ans < INT_MIN || INT_MAX < _Ans)
		_Xout_of_range("stoi argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return ((int)_Ans);
}

inline long stol(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to long
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	long _Ans = _CSTD wcstol(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stol argument");
	if (errno == ERANGE)
		_Xout_of_range("stol argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline unsigned long stoul(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to unsigned long
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	unsigned long _Ans = _CSTD wcstoul(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoul argument");
	if (errno == ERANGE)
		_Xout_of_range("stoul argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline long long stoll(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to long long
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	long long _Ans = _CSTD wcstoll(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoll argument");
	if (errno == ERANGE)
		_Xout_of_range("stoll argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline unsigned long long stoull(const wstring& _Str, size_t *_Idx = 0,
	int _Base = 10)
{	// convert wstring to unsigned long long
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	unsigned long long _Ans = _CSTD wcstoull(_Ptr, &_Eptr, _Base);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stoull argument");
	if (errno == ERANGE)
		_Xout_of_range("stoull argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline float stof(const wstring& _Str, size_t *_Idx = 0)
{	// convert wstring to float
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	float _Ans = _CSTD wcstof(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stof argument");
	if (errno == ERANGE)
		_Xout_of_range("stof argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline double stod(const wstring& _Str, size_t *_Idx = 0)
{	// convert wstring to double
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	double _Ans = _CSTD wcstod(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stod argument");
	if (errno == ERANGE)
		_Xout_of_range("stod argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

inline long double stold(const wstring& _Str, size_t *_Idx = 0)
{	// convert wstring to long double
	const wchar_t *_Ptr = _Str.c_str();
	wchar_t *_Eptr;
	errno = 0;
	long double _Ans = _CSTD wcstold(_Ptr, &_Eptr);

	if (_Ptr == _Eptr)
		_Xinvalid_argument("invalid stold argument");
	if (errno == ERANGE)
		_Xout_of_range("stold argument out of range");
	if (_Idx != 0)
		*_Idx = (size_t)(_Eptr - _Ptr);
	return (_Ans);
}

// HELPERS FOR to_string AND to_wstring
#pragma warning(push)
#pragma warning(disable: 4127) // conditional expression is constant
template<class _Elem,
	class _UTy> inline
	_Elem* _UIntegral_to_buff(_Elem* _RNext, _UTy _UVal)
{	// format _UVal into buffer *ending at* _RNext
	static_assert(is_unsigned<_UTy>::value, "_UTy must be unsigned");

#ifdef _WIN64
	auto _UVal_trunc = _UVal;
#else /* ^^^ _WIN64 ^^^ // vvv !_WIN64 vvv */
	if (sizeof(_UTy) > 4)
	{	// For 64-bit numbers, work in chunks to avoid 64-bit divisions.
		while (_UVal > 0xFFFFFFFFU)
		{
			auto _UVal_chunk = static_cast<_Uint32t>(_UVal % 1000000000);
			_UVal /= 1000000000;

			for (int _Idx = 0; _Idx != 9; ++_Idx)
			{
				*--_RNext = '0' + _UVal_chunk % 10;
				_UVal_chunk /= 10;
			}
		}
	}

	auto _UVal_trunc = static_cast<_Uint32t>(_UVal);
#endif /* _WIN64 */

	do
	{
		*--_RNext = '0' + _UVal_trunc % 10;
		_UVal_trunc /= 10;
	} while (_UVal_trunc != 0);
	return (_RNext);
}
#pragma warning(pop)

template<class _Elem,
	class _Ty> inline
	basic_string<_Elem> _Integral_to_string(const _Ty _Val)
{	// convert _Val to string
	static_assert(is_integral<_Ty>::value, "_Ty must be integral");
	using _UTy = make_unsigned_t<_Ty>;
	_Elem _Buff[21]; // can hold -2^63 and 2^64 - 1, plus NUL
	_Elem* const _Buff_end = _STD end(_Buff);
	_Elem* _RNext = _Buff_end;
	auto _UVal = static_cast<_UTy>(_Val);
	if (_Val < 0)
	{
		_RNext = _UIntegral_to_buff(_RNext, 0 - _UVal);
		*--_RNext = '-';
	}
	else
		_RNext = _UIntegral_to_buff(_RNext, _UVal);

	return (basic_string<_Elem>(_RNext, _Buff_end));
}

template<class _Ty> inline
string _Floating_to_string(const char *_Fmt, _Ty _Val)
{	// convert _Val to string
	static_assert(is_floating_point<_Ty>::value,
		"_Ty must be floating point");

	int _Len = _CSTD _scprintf(_Fmt, _Val);
	string _Str(_Len + 1, '\0');
	_CSTD sprintf_s(&_Str[0], _Len + 1, _Fmt, _Val);
	_Str.resize(_Len);
	return (_Str);
}

template<class _Ty> inline
wstring _Floating_to_wstring(const wchar_t *_Fmt, _Ty _Val)
{	// convert _Val to wstring
	static_assert(is_floating_point<_Ty>::value,
		"_Ty must be floating point");

	int _Len = _CSTD _scwprintf(_Fmt, _Val);
	wstring _Str(_Len + 1, L'\0');
	_CSTD swprintf_s(&_Str[0], _Len + 1, _Fmt, _Val);
	_Str.resize(_Len);
	return (_Str);
}

#undef _TO_STRING_BUF_SIZE

// to_string NARROW CONVERSIONS
inline string to_string(int _Val)
{	// convert int to string
	return (_Integral_to_string<char>(_Val));
}

inline string to_string(unsigned int _Val)
{	// convert unsigned int to string
	return (_Integral_to_string<char>(_Val));
}

inline string to_string(long _Val)
{	// convert long to string
	return (_Integral_to_string<char>(_Val));
}

inline string to_string(unsigned long _Val)
{	// convert unsigned long to string
	return (_Integral_to_string<char>(_Val));
}

inline string to_string(long long _Val)
{	// convert long long to string
	return (_Integral_to_string<char>(_Val));
}

inline string to_string(unsigned long long _Val)
{	// convert unsigned long long to string
	return (_Integral_to_string<char>(_Val));
}

inline string to_string(float _Val)
{	// convert float to string
	return (_Floating_to_string("%f", _Val));
}

inline string to_string(double _Val)
{	// convert double to string
	return (_Floating_to_string("%f", _Val));
}

inline string to_string(long double _Val)
{	// convert long double to string
	return (_Floating_to_string("%Lf", _Val));
}

// to_wstring WIDE CONVERSIONS
inline wstring to_wstring(int _Val)
{	// convert int to wstring
	return (_Integral_to_string<wchar_t>(_Val));
}

inline wstring to_wstring(unsigned int _Val)
{	// convert unsigned int to wstring
	return (_Integral_to_string<wchar_t>(_Val));
}

inline wstring to_wstring(long _Val)
{	// convert long to wstring
	return (_Integral_to_string<wchar_t>(_Val));
}

inline wstring to_wstring(unsigned long _Val)
{	// convert unsigned long to wstring
	return (_Integral_to_string<wchar_t>(_Val));
}

inline wstring to_wstring(long long _Val)
{	// convert long long to wstring
	return (_Integral_to_string<wchar_t>(_Val));
}

inline wstring to_wstring(unsigned long long _Val)
{	// convert unsigned long long to wstring
	return (_Integral_to_string<wchar_t>(_Val));
}

inline wstring to_wstring(float _Val)
{	// convert float to wstring
	return (_Floating_to_wstring(L"%f", _Val));
}

inline wstring to_wstring(double _Val)
{	// convert double to wstring
	return (_Floating_to_wstring(L"%f", _Val));
}

inline wstring to_wstring(long double _Val)
{	// convert long double to wstring
	return (_Floating_to_wstring(L"%Lf", _Val));
}

// basic_string LITERALS
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuser-defined-literals"
#endif /* __clang__ */

inline namespace literals {
	inline namespace string_literals {
		inline string operator "" s(const char *_Str, size_t _Len)
		{	// construct literal from [_Str, _Str + _Len)
			return (string(_Str, _Len));
		}

		inline wstring operator "" s(const wchar_t *_Str, size_t _Len)
		{	// construct literal from [_Str, _Str + _Len)
			return (wstring(_Str, _Len));
		}

		inline u16string operator "" s(const char16_t *_Str, size_t _Len)
		{	// construct literal from [_Str, _Str + _Len)
			return (u16string(_Str, _Len));
		}

		inline u32string operator "" s(const char32_t *_Str, size_t _Len)
		{	// construct literal from [_Str, _Str + _Len)
			return (u32string(_Str, _Len));
		}
	}	// inline namespace string_literals
}	// inline namespace literals

#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */

_STD_END

#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _STRING_ */

/*
* Copyright (c) by P.J. Plauger. All rights reserved.
* Consult your license regarding permissions and restrictions.
V6.50:0009 */
