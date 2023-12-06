#include "Status.h"

using std::exception;

class Invalid_choice:public exception
{
private:
	string m_str;

public:
	explicit Invalid_choice(const string& s):m_str(s) {};
	char const* what() const noexcept override
	{
		return m_str.c_str();
	}
};

class invalid_argument :public exception
{
private:
	string m_str;

public:
	explicit invalid_argument(const string& s) :m_str(s) {};
	char const* what() const noexcept override
	{
		return m_str.c_str();
	}
};

class logic_error :public exception
{
private:
	string m_str;

public:
	explicit logic_error(const string& s) :m_str(s) {};
	char const* what() const noexcept override
	{
		return m_str.c_str();
	}
};