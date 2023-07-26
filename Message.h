#pragma once

#include <fstream>
#include <string>

class Message
{
public:
	Message() = default;

	~Message() = default;

	Message(const std::string& from, const std::string& to,
	     const std::string& text) : from_(from), to_(to), text_(text) {}

	friend std::fstream& operator >>(std::fstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);

private:
	std::string from_;
	std::string to_;
	std::string text_;
};