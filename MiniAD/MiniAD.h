#pragma once
#include <cmath>
#include <array>

namespace MiniAD 
{	

	template <std::size_t SIZE>
	struct FD
	{		
		FD(float a, int index)
		{
			this->a = a;
			this->b = {};
		
			this->b[index] = 1.0f;
		}

		FD(float a = 0.0f)
		{
			this->a = a;			
		}

		float a;
		std::array<float, SIZE>  b; // differential coefficients
	};


	template <std::size_t SIZE>
	FD<SIZE> cos(const FD &x)
	{
		return FD(::cos(x.a), -x.b*::sin(x.a));
	}	

	template <std::size_t SIZE>
	FD<SIZE> operator+(const FD<SIZE> &x, const FD<SIZE> &y)
	{
		FD<SIZE> result;
		result.a = x.a + y.a;
		for (int i = 0; i < SIZE; ++i)
			result.b[i] = x.b[i] + y.b[i];

		return result;
	}

	template <std::size_t SIZE>
	FD<SIZE> operator-(const FD<SIZE> &x, const FD<SIZE> &y)
	{
		FD<SIZE> result;
		result.a = x.a - y.a;
		for (int i = 0; i < SIZE; ++i)
			result.b[i] = x.b[i] - y.b[i];

		return result;
	}	

	template <std::size_t SIZE>
	FD<SIZE> operator*(const FD<SIZE> &x, const FD<SIZE> &y)
	{
		FD<SIZE> result;		
		result.a = x.a * y.a;
		for (int i = 0; i < SIZE; ++i)
			result.b[i] = x.a * y.b[i] + x.b[i] * y.a;
		return result;
	}

	template <std::size_t SIZE>
	FD<SIZE> operator*(const float x, const FD<SIZE> &y)
	{
		FD<SIZE> result;
		result.a = x * y.a;
		for (int i = 0; i < SIZE; ++i)
			result.b[i] = x * y.b[i];
		return result;
	}

	template <std::size_t SIZE>
	FD<SIZE> operator*(const FD<SIZE> &y, const float x)
	{
		FD<SIZE> result;
		result.a = x * y.a;
		for (int i = 0; i < SIZE; ++i)
			result.b[i] = x * y.b[i];
		return result;
	}

	template <typename R, typename ... Types> 
	constexpr size_t get_argument_count(R(*f)(Types ...))
	{
		return sizeof...(Types);
	}

	template< 
		template<typename...> class List,
		template<typename> class Mod,
		typename ...Args>
		struct magic
	{
		typedef List<typename Mod<Args>::type...> type;
	};

	template <class... Pack>
	void store_pack(Pack... p) {
		std::tuple<Pack...> store(p...);
		// do something with store
	}

	template <typename F, typename ... Types, typename... Args>
	//std::array<float, sizeof...(Types)> grad( R(*f)(Types...p), Args ... args)
	std::array<float, sizeof...(Types)> grad(F f, Args ... args)
	{		
		//std::tuple<Types...> pack(p...)
		return F(args);
		//FD<sizeof...(Types)> result();

		//return array<float, sizeof...(Types)>();
	}	
}