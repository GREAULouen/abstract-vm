/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:37:37 by lgreau            #+#    #+#             */
/*   Updated: 2025/05/18 12:15:17 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(): type(TokenType::UNKNOWN), value("") {}
Token::Token(TokenType type, std::string value): type(type), value(value) {}
Token::Token(Token const &toCopy) {*this = toCopy;}

Token &	Token::operator=(Token const &toAssign)
{
	if (this == &toAssign)
		return *this;
	this->type = toAssign.type;
	this->value = toAssign.value;
	return *this;
}


std::string	Token::typeAsString(void) {
	static const std::unordered_map<TokenType, std::string>	types = {
		{TokenType::PUSH, "push"},
		{TokenType::POP, "pop"},
		{TokenType::DUMP, "dump"},
		{TokenType::ASSERT, "assert"},
		{TokenType::ADD, "add"},
		{TokenType::SUB, "sub"},
		{TokenType::MUL, "mul"},
		{TokenType::DIV, "div"},
		{TokenType::MOD, "mod"},
		{TokenType::PRINT, "print"},
		{TokenType::EXIT, "exit"},
		{TokenType::VALUE, "value"},
		{TokenType::COMMENT, ";"},
		{TokenType::END, "#"},
		{TokenType::NEWLINE, "\n"},
		{TokenType::UNKNOWN, "unknown"},
	};

	return types.at(this->type);
}