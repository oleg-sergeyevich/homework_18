#pragma once

#include <fstream>
#include <string>

class User
{
public:
	User() = default;

	~User() = default;

	User(const std::string& login, const std::string& pass,
	     const std::string& name) : login_(login), pass_(pass), name_(name) {}

	friend std::fstream& operator >>(std::fstream& is, User& obj);
	friend std::ostream& operator <<(std::ostream& os, const User& obj);

private:
	std::string login_;
	std::string pass_;
	std::string name_;
};