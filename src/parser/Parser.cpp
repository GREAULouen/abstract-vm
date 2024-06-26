/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:23:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 15:03:12 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const std::vector<Token> &tokens) : _tokens(tokens), _pos(0) {}

std::unique_ptr<ProgramNode>	Parser::parse() {
	auto	program = std::make_unique<ProgramNode>();

	while (currentToken().type != TokenType::END) {
		program->addInstruction(parseInstruction());
	}
	return program;
}




const Token &Parser::currentToken() const {
	if (this->_pos < this->_tokens.size()) {
		return this->_tokens[this->_pos];
	}
	throw std::runtime_error("No more tokens available");
}

void	Parser::consumeToken() {
	if (this->_pos < this->_tokens.size()) {
		this->_pos++;
	} else {
		throw std::runtime_error("Attempted to consume token past the end");
	}
}

std::unique_ptr<InstructionNode>	Parser::parseInstruction() {
	Token instrToken = currentToken();
	consumeToken();

	std::optional<Token>	valueToken = std::nullopt;
	if (instrToken.type == TokenType::PUSH || instrToken.type == TokenType::ASSERT) {
		valueToken = parseValue();
	}

	return std::make_unique<InstructionNode>(instrToken, valueToken);
}

Token	Parser::parseValue() {
	Token typeToken = currentToken();
	consumeToken();

	Token valueToken = currentToken();
	consumeToken();

	// Combine type and value into a single token
	std::string combinedValue = typeToken.value + "(" + valueToken.value + ")";
	TokenType combinedType;

	if (typeToken.type == TokenType::INT8 || typeToken.type == TokenType::INT16 || typeToken.type == TokenType::INT32) {
		combinedType = TokenType::VALUE;
	} else if (typeToken.type == TokenType::FLOAT || typeToken.type == TokenType::DOUBLE) {
		combinedType = TokenType::VALUE;
	} else {
		throw std::runtime_error("Expected a value type token");
	}

	return Token(combinedType, combinedValue);
}
