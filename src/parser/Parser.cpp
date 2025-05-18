/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:23:38 by lgreau            #+#    #+#             */
/*   Updated: 2025/05/18 12:24:57 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const std::vector<Token> &tokens) : _tokens(tokens), _pos(0), _errorsFound(false) {}

ProgramNode*	Parser::parse() {
	ProgramNode*	program = new ProgramNode();

	while (this->_pos < this->_tokens.size()) {
		Token	token = this->_tokens[this->_pos];
		if (token.type == TokenType::END) {
			break;
		}
		program->addInstruction(parseInstruction());
	}

	if (this->_errorsFound)
		throw std::runtime_error("Error(s) found during parsing: not executing");

	return program;
}


InstructionNode*	Parser::parseInstruction() {
	Token	token = this->_tokens[this->_pos++];
	while (token.type == TokenType::NEWLINE && this->_pos < this->_tokens.size())
		token = this->_tokens[this->_pos++];

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
		case TokenType::UNKNOWN:
			return new InstructionNode(token);
		case TokenType::VALUE:
			flushError("" + token.value + " can only be pushed or asserted");
			return new InstructionNode(Token(TokenType::UNKNOWN, ""));
		case TokenType::END:
			return new InstructionNode(Token(TokenType::END, "#"));
		default:
			throw std::runtime_error("Unexpected token type");
	}
}



InstructionNode*	Parser::parsePush() {
	Token valueToken = this->_tokens[this->_pos++];
	if (valueToken.type != TokenType::VALUE) {
		flushError("Expected a value type token after push");
	}

	return new InstructionNode(this->_tokens[this->_pos - 2], valueToken);
}

InstructionNode*	Parser::parseAssert() {
	Token valueToken = this->_tokens[this->_pos++];
	if (valueToken.type != TokenType::VALUE) {
		flushError("Expected a value type token after assert");
	}
	return new InstructionNode(this->_tokens[this->_pos - 2], valueToken);
}




void	Parser::flushError(std::string error_msg) {
	this->_errorsFound = true;
	std::cerr	<< RED
				<< "Syntactic error: "
				<< error_msg
				<< RESET
				<< std::endl;
}
