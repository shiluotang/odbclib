#ifndef ODBCLIB_NULLABLE_HPP_INCLUDED
#define ODBCLIB_NULLABLE_HPP_INCLUDED

#include "config.hpp"
#include <istream>
#include <ostream>
#include <string>
#include <stdexcept>

namespace odbclib
{
	template<typename T>
	class Nullable
	{
			typedef T const& const_reference;
			typedef T const* const_pointer;
		public:
			Nullable()
				:m_value(T()),
				m_isNull(true)
			{ }

			Nullable(T const& value)
				:m_value(value)
			{ }

			bool isNull() const{return m_isNull;}

			operator T()
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}

			operator T()const
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}

			Nullable& operator=(Nullable const& value)
			{
				if(value.isNull())
					m_isNull = true;
				return *this;
			}

			Nullable& operator=(T const& value)
			{
				m_value = value;
				m_isNull = false;
				return *this;
			}


			T const& value()const
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}

			T& value()
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}
		public:
			static Nullable const& Null;
		private:
			T m_value;
			bool m_isNull;

			template<typename V>
			friend std::ostream& operator<<(std::ostream&,Nullable<V> const&);

			template<typename V>
			friend std::istream& operator>>(std::istream&,Nullable<V> &);
	};

	template<typename T>
	Nullable<T> const& Nullable<T>::Null = Nullable<T>();

	template<typename T> 
	std::ostream& operator<<(std::ostream& os,Nullable<T> const& value) 
	{
		if(value.m_isNull)
			throw std::runtime_error("null has no value");
		os << value.m_value;
		return os;
	}

	template<typename T>
	std::istream& operator>>(std::istream& is,Nullable<T> &value)
	{
		is >> value.m_value;
		return is;
	}

	template<>
	class Nullable<std::string>
	{
		public:
			Nullable()
				:m_value(std::string()),
				m_isNull(true)
			{ }

			Nullable(std::string const& value)
				:m_value(value),
				m_isNull(false)
			{ }

			Nullable(char const* value)
				:m_value(value),
				m_isNull(false)
			{ }

			Nullable(Nullable const& other)
			{
				m_value = other.m_value;
				m_isNull = other.m_isNull;
			}

			template<size_t N>
				Nullable(char const (&a)[N])
				:m_value(a),
				m_isNull(false)
			{ }

			bool isNull() const{return m_isNull;}

			operator std::string()
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}

			operator std::string()const
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}

			Nullable& operator=(char const* value)
			{
				m_value.assign(value);
				m_isNull = false;
				return *this;
			}

			std::string const& value()const
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}

			std::string& value()
			{
				if(isNull())
					throw std::runtime_error("null has no value");
				return m_value;
			}
		public:
			static Nullable const& Null;

		private:
			std::string m_value;
			bool m_isNull;

			template<typename V>
			friend std::ostream& operator<<(std::ostream&,Nullable<V> const&);

			template<typename V>
			friend std::istream& operator>>(std::istream&,Nullable<V> &);
	};
}

#endif
