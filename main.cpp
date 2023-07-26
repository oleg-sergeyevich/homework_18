#include <iostream>
#include <filesystem>

#include "User.h"
#include "Message.h"

namespace fs = std::filesystem;

void printPermissions(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
    		  << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
			  << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
        	  << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
       	      << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
        	  << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
        	  << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
        	  << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
        	  << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
        	  << '\n';
}

int main()
{
	std::fstream user_file = std::fstream("user.txt", std::ios::in | std::ios::out);
	std::fstream message_file = std::fstream("message.txt", std::ios::in | std::ios::out);

	if (false == user_file.is_open())
	{
		user_file = std::fstream("user.txt", std::ios::in |
				std::ios::out | std::ios::trunc);
		fs::permissions("user.txt", fs::perms::group_read |
        				fs::perms::group_write | fs::perms::others_all,
       					fs::perm_options::remove);
		std::cout << "Created file (user.txt) with permissions: ";
		printPermissions(fs::status("user.txt").permissions());
	}

	std::string name;

	if (true == user_file.is_open())
	{
		user_file.seekp(0, std::ios_base::end);

		std::cout << "\n---Registration---\n";
		std::cout << "Login: ";
		std::string login;
		std::cin >> login;

		std::cout << "Password: ";
		std::string pass;
		std::cin >> pass;

		std::cout << "Name: ";
		std::cin >> name;

		User users(login, pass, name);
		user_file << users << std::endl;
	}
	else
	{

		std::cout << "Could not open file user.txt" << std::endl;
		return 0;
	}

	if (false == message_file.is_open())
	{

		message_file = std::fstream("message.txt", std::ios::in |
				std::ios::out | std::ios::trunc);
		fs::permissions("message.txt", fs::perms::group_read |
        				fs::perms::group_write | fs::perms::others_all,
       					fs::perm_options::remove);
		std::cout << "\nCreated file (message.txt) with permissions: ";
		printPermissions(fs::status("message.txt").permissions());
	}

	if (true == message_file.is_open())
	{

		message_file.seekp(0, std::ios_base::end);

		std::cout << "\nenter the recipient of the message: ";
		std::string to;
		std::cin >> to;

		std::cout << "enter your message: ";
		std::string text;
		std::cin.ignore();
		getline(std::cin, text);

		Message messages(name, to, text);
		message_file << messages << std::endl;
	}
	else
	{

		user_file.close();
		std::cout << "Could not open file message.txt" << std::endl;
		return 0;
	}

	std::cout << "\n--------------------\n";
	user_file.seekg(0, std::ios_base::beg);

	while (false == user_file.eof())
	{
		User users;
		user_file >> users;
		std::cout << users << std::endl;
	}

	std::cout << "--------------------\n";
	message_file.seekg(0, std::ios_base::beg);

	while (false == message_file.eof())
	{

		Message messages;
		message_file >> messages;
		std::cout << messages << std::endl;
	}

	user_file.close();
	message_file.close();

	return 0;
}