#include "Comment.h"
#include <iostream>

Comment::Comment(User* author, std::string content, Date date): author(author), content(content), date(date){}

User* Comment::getAuthor() const
{
	return author;
}

const std::string& Comment::getContent() const
{
	return content;
}

const Date& Comment::getDate() const
{
	return date;
}

std::string Comment::getComment() const
{
	return std::format("[{}] {}: {}", date.getDate(), author->getUsername(), content);
}