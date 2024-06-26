/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:04 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:01:16 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Lexer.hpp"

Lexer::Lexer(const std::string &input) : _input(input), _pos(0), _length(input.length()) {}


std::vector<Token> Lexer::tokenize() {
	std::vector<Token>	tokens;

	while (this->_pos < this->_length) {
		if (isspace(currentChar())) {
			consume();
		} else if (currentChar() == ';') {
			skipComment();
		} else if (isalpha(currentChar())) {
			tokens.push_back(matchKeywordOrValueType());
		} else if (isdigit(currentChar()) || currentChar() == '-' || currentChar() == '.') {
			tokens.push_back(matchNumber());
		} else if (currentChar() == '\n') {
			tokens.emplace_back(TokenType::NEWLINE, "\n");
			consume();
		} else {
			consume();  // Skip unknown characters
		}
	}
	tokens.emplace_back(TokenType::END_OF_FILE, "");
	return tokens;
}


char Lexer::currentChar() const {
	return this->_pos < this->_length ? this->_input[this->_pos] : '\0';
}
void Lexer::consume() {
	this->_pos++;
}


void Lexer::skipComment() {
	while (this->_pos < this->_length && currentChar() != '\n') {
		consume();
	}
}


Token Lexer::matchKeywordOrValueType() {
	std::string	value;

	while (isalpha(currentChar())) {
		value += currentChar();
		consume();
	}
	if (value == "push") return Token(TokenType::PUSH, value);
	if (value == "pop") return Token(TokenType::POP, value);
	if (value == "dump") return Token(TokenType::DUMP, value);
	if (value == "assert") return Token(TokenType::ASSERT, value);
	if (value == "add") return Token(TokenType::ADD, value);
	if (value == "sub") return Token(TokenType::SUB, value);
	if (value == "mul") return Token(TokenType::MUL, value);
	if (value == "div") return Token(TokenType::DIV, value);
	if (value == "mod") return Token(TokenType::MOD, value);
	if (value == "print") return Token(TokenType::PRINT, value);
	if (value == "exit") return Token(TokenType::EXIT, value);
	if (value == "int8") return Token(TokenType::INT8, value);
	if (value == "int16") return Token(TokenType::INT16, value);
	if (value == "int32") return Token(TokenType::INT32, value);
	if (value == "float") return Token(TokenType::FLOAT, value);
	if (value == "double") return Token(TokenType::DOUBLE, value);
	return Token(TokenType::UNKNOWN, value);
}


Token Lexer::matchNumber() {
	std::string	value;
	bool		hasDot = false;

	if (currentChar() == '-') {
		value += currentChar();
		consume();
	}
	while (isdigit(currentChar()) || (!hasDot && currentChar() == '.')) {
		if (currentChar() == '.') hasDot = true;
		value += currentChar();
		consume();
	}
	if (hasDot) {
		return Token(TokenType::FLOATING, value);
	} else {
		return Token(TokenType::INTEGER, value);
	}
}