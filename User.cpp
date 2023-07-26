#include "User.h"

std::fstream& operator >>(std::fstream& is, User& obj)
{
	is >> obj.login_;
	is >> obj.pass_;
	is >> obj.name_;
	return is;
}

std::ostream& operator <<(std::ostream& os, const User& obj)
{
	os << obj.login_;
	os << " ";
	os << obj.pass_;
	os << " ";
	os << obj.name_;
	return os;
}