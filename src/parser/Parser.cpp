/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:23:38 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 14:10:54 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const std::vector<Token> &tokens) : _tokens(tokens), _pos(0) {}

ProgramNode*	Parser::parse() {
	ProgramNode*	program = new ProgramNode();

	while (this->_pos < this->_tokens.size()) {
		Token	token = this->_tokens[this->_pos];
		if (token.type == TokenType::END) {
			break;
		}
		program->addInstruction(parseInstruction());
	}

	return program;
}


InstructionNode*	Parser::parseInstruction() {
	Token	token = this->_tokens[this->_pos++];

	switch (token.type) {
		case TokenType::PUSH:
			return parsePush();
		case TokenType::POP:
			return new InstructionNode(token);
		case TokenType::DUMP:
			return new InstructionNode(token);
		case TokenType::ASSERT:
			return parseAssert();
		case TokenType::ADD:
			return new InstructionNode(token);
		case TokenType::SUB:
			return new InstructionNode(token);
		case TokenType::MUL:
			return new InstructionNode(token);
		case TokenType::DIV:
			return new InstructionNode(token);
		case TokenType::MOD:
			return new InstructionNode(token);
		case TokenType::PRINT:
			return new InstructionNode(token);
		case TokenType::EXIT:
			return new InstructionNode(token);
		default:
			throw std::runtime_error("Unexpected token type");
	}
}



InstructionNode*	Parser::parsePush() {
	Token valueToken = this->_tokens[this->_pos++];
	if (valueToken.type != TokenType::VALUE) {
		throw std::runtime_error("Expected a value type token after push");
	}
	return new InstructionNode(this->_tokens[this->_pos - 2], valueToken);
}

InstructionNode*	Parser::parseAssert() {
	Token valueToken = this->_tokens[this->_pos++];
	if (valueToken.type != TokenType::VALUE) {
		throw std::runtime_error("Expected a value type token after assert");
	}
	return new InstructionNode(this->_tokens[this->_pos - 2], valueToken);
}
