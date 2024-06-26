/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:23:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:45:39 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const std::vector<Token> &tokens) : _tokens(tokens), _pos(0) {}

std::unique_ptr<ProgramNode>	Parser::parse() {
	auto	program = std::make_unique<ProgramNode>();

	while (!isAtEnd()) {
		program->addInstruction(parseInstruction());
		consume(TokenType::NEWLINE);
	}
	return program;
}



bool	Parser::isAtEnd() const {
	return this->_pos >= this->_tokens.size() || this->_tokens[this->_pos].type == TokenType::END_OF_FILE;
}

const Token &Parser::currentToken() const {
	return this->_tokens[this->_pos];
}

const Token &Parser::consume(TokenType type) {
	if (currentToken().type == type) {
		return this->_tokens[this->_pos++];
	}
	throw std::runtime_error("Unexpected token: " + currentToken().value);
}

std::unique_ptr<InstructionNode>	Parser::parseInstruction() {
	auto					instrToken = consume(currentToken().type);
	std::optional<Token>	valueToken;

	if (instrToken.type == TokenType::PUSH || instrToken.type == TokenType::ASSERT) {
		valueToken = consume(nextTokenType());
	}

	return std::make_unique<InstructionNode>(instrToken, valueToken);
}

TokenType	Parser::nextTokenType() const {
	if (currentToken().type == TokenType::INT8 || currentToken().type == TokenType::INT16 ||
		currentToken().type == TokenType::INT32 || currentToken().type == TokenType::FLOAT ||
		currentToken().type == TokenType::DOUBLE) {
		return currentToken().type;
	} else if (currentToken().type == TokenType::INTEGER || currentToken().type == TokenType::FLOATING) {
		return currentToken().type;
	} else {
		throw std::runtime_error("Expected a value type token");
	}
}
