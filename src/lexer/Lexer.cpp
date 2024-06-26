/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:04 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:54:22 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Lexer.hpp"

Lexer::Lexer(const std::string &input) : _input(input), _pos(0), _length(input.length()) {}


std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens;
		std::string::const_iterator it = this->_input.begin();

		while (it != this->_input.end()) {
			if (std::isspace(*it)) {
				++it;
				continue;
			}

			if (*it == ';') {
				while (it != this->_input.end() && *it != '\n') ++it;  // Skip comments
				continue;
			}

			if (std::isdigit(*it) || (*it == '-' && std::isdigit(*(it + 1)))) {
				tokens.push_back(parseNumber(it));
				continue;
			}

			if (std::isalpha(*it)) {
				tokens.push_back(parseIdentifier(it));
				continue;
			}

			if (*it == '(' || *it == ')') {
				tokens.push_back(Token(TokenType::VALUE, std::string(1, *it)));
				++it;
				continue;
			}

			throw std::runtime_error("Unexpected character: " + std::string(1, *it));
		}

		tokens.push_back(Token(TokenType::END, "#"));
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

Token	Lexer::parseNumber(std::string::const_iterator& it) {
	std::string	number;

	while (it != this->_input.end() && (std::isdigit(*it) || *it == '.' || *it == '-')) {
		number += *it;
		++it;
	}
	return Token(TokenType::VALUE, number);
}

Token	Lexer::parseIdentifier(std::string::const_iterator& it) {
	std::string	identifier;

	while (it != this->_input.end() && std::isalnum(*it)) {
		identifier += *it;
		++it;
	}

	if (identifier == "push") return Token(TokenType::PUSH, identifier);
	if (identifier == "pop") return Token(TokenType::POP, identifier);
	if (identifier == "dump") return Token(TokenType::DUMP, identifier);
	if (identifier == "assert") return Token(TokenType::ASSERT, identifier);
	if (identifier == "add") return Token(TokenType::ADD, identifier);
	if (identifier == "sub") return Token(TokenType::SUB, identifier);
	if (identifier == "mul") return Token(TokenType::MUL, identifier);
	if (identifier == "div") return Token(TokenType::DIV, identifier);
	if (identifier == "mod") return Token(TokenType::MOD, identifier);
	if (identifier == "print") return Token(TokenType::PRINT, identifier);
	if (identifier == "exit") return Token(TokenType::EXIT, identifier);
	if (identifier == "int8") return Token(TokenType::INT8, identifier);
	if (identifier == "int16") return Token(TokenType::INT16, identifier);
	if (identifier == "int32") return Token(TokenType::INT32, identifier);
	if (identifier == "float") return Token(TokenType::FLOAT, identifier);
	if (identifier == "double") return Token(TokenType::DOUBLE, identifier);

	return Token(TokenType::UNKNOWN, identifier);
}