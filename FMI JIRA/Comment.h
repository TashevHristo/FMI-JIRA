#pragma once
#include "User.h"
#include "Date.h"

class Comment {
	User* author;
	std::string content;
	Date date;

public:
	Comment(User* author, std::string content, Date date);

	User* getAuthor() const;
	const std::string& getContent() const;
	const Date& getDate() const;

	std::string getComment() const;
};