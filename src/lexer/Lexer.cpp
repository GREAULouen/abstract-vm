/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:04 by lgreau            #+#    #+#             */
/*   Updated: 2025/05/18 12:33:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Lexer.hpp"

Lexer::Lexer(const std::string &input) : _input(input), _pos(0), _length(input.length()) {} //, _errorsFound(false) {}


std::vector<Token>	Lexer::tokenize() {
	std::vector<Token>	tokens;

	while (this->_pos < this->_length) {
		if (std::isspace(this->_input[this->_pos])) {
			if (this->_input[this->_pos] == '\n')
				tokens.push_back(Token(TokenType::NEWLINE, "\n"));

			this->_pos++;
			continue;
		}

		if (this->_input[this->_pos] == ';') {
			skipComment();
			continue;
		}

		if (std::isdigit(this->_input[this->_pos]) || this->_input[this->_pos] == '-' || this->_input[this->_pos] == '.') {
			tokens.push_back(Token(TokenType::VALUE, parseValue()));
			continue;
		}

		if (std::isalpha(this->_input[this->_pos])) {
			tokens.push_back(parseKeywordOrValue());
			continue;
		}

		flushError("Unexpected character: " + std::string(1, this->_input[this->_pos]));
	}

	tokens.push_back(Token(TokenType::END, "#"));

	// if (this->_errorsFound)
	// 	throw std::runtime_error("Error(s) found during tokenization: not parsing");
	return tokens;
}

void	Lexer::skipComment() {
	while (this->_pos < this->_length && this->_input[this->_pos] != '\n') {
		this->_pos++;
	}
}

std::string	Lexer::parseValue() {
	static const std::regex valueRegex(R"((int8|int16|int32|float|double)\((-?\d+(\.\d+)?)\))");
	std::smatch match;
	std::string::const_iterator start = this->_input.begin() + this->_pos;
	std::string::const_iterator end = this->_input.end();

	if (std::regex_search(start, end, match, valueRegex)) {
		this->_pos += match.position() + match.length();
		return match.str();
	}

	flushError("Invalid value format at position: " + std::to_string(this->_pos));
	this->_pos++;
	return ("");
}

Token	Lexer::parseKeywordOrValue() {
	static const std::unordered_map<std::string, TokenType>	keywords = {
		{"push", TokenType::PUSH},
		{"pop", TokenType::POP},
		{"dump", TokenType::DUMP},
		{"assert", TokenType::ASSERT},
		{"add", TokenType::ADD},
		{"sub", TokenType::SUB},
		{"mul", TokenType::MUL},
		{"div", TokenType::DIV},
		{"mod", TokenType::MOD},
		{"print", TokenType::PRINT},
		{"exit", TokenType::EXIT},
	};

	std::string	tokenValue;
	while (this->_pos < this->_length && std::isalpha(this->_input[this->_pos])) {
		tokenValue += this->_input[this->_pos++];
	}

	if (keywords.find(tokenValue) != keywords.end()) {
		return Token(keywords.at(tokenValue), tokenValue);
	}

	if (tokenValue == "int")
		while (this->_pos < this->_length && std::isdigit(this->_input[this->_pos]))
			tokenValue += this->_input[this->_pos++];

	if (tokenValue == "int8" || tokenValue == "int16" || tokenValue == "int32" ||
		tokenValue == "float" || tokenValue == "double") {
		if (this->_input[this->_pos] == '(') {
			std::string	parenthesized_value = parseParenthesizedValue();
			if (!parenthesized_value.empty()) {
				std::string fullValue = tokenValue + parenthesized_value;
				return Token(TokenType::VALUE, fullValue);
			}

			flushError("Invalid value format: " + tokenValue);
			return Token(TokenType::UNKNOWN, "");
		}
	}

	flushError("Invalid keyword: " + tokenValue);
	return Token(TokenType::UNKNOWN, "");
}


std::string	Lexer::parseParenthesizedValue() {
	std::string	value;
	value += this->_input[this->_pos++]; // Add the opening '('

	while (this->_pos < this->_length && this->_input[this->_pos] != ')') {
		value += this->_input[this->_pos++];
	}

	if (this->_pos < this->_length && this->_input[this->_pos] == ')') {
		value += this->_input[this->_pos++]; // Add the closing ')'
		return value;
	}

	flushError("Mismatched parentheses in value");
	return "";
}




void	Lexer::flushError(std::string error_msg) {
	// this->_errorsFound = true;
	std::cerr	<< RED
				<< "Lexical error: "
				<< error_msg
				<< RESET
				<< std::endl;
}
