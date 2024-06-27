/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:36:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 17:42:00 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VirtualMachine.hpp"

VirtualMachine::VirtualMachine() {}

VirtualMachine::~VirtualMachine() {}

int	VirtualMachine::runProgram(std::string input) {

	/*	~~~~~~~~~~~~~~~~~~~~~ Lexical LAYER ~~~~~~~~~~~~~~~~~~~~~	*/

	Lexer				lexer(input);
	std::vector<Token>	tokens;

	try {
		tokens = lexer.tokenize();
	} catch(std::exception &e) {
		std::cerr	<< RED
					<< e.what()
					<< RESET
					<< std::endl;
		return 1;
	}

	std::cout << "Tokenized input:" << std::endl;
	for (const auto &token : tokens) {
		std::cout	<< static_cast<int>(token.type)
					<< ": "
					<< token.value << std::endl;
	}

	/*	~~~~~~~~~~~~~~~~ Syntaxic/Semantic LAYER ~~~~~~~~~~~~~~~~	*/

	Parser			parser(tokens);
	ProgramNode *	program;
	try {
		program = parser.parse();
	} catch (const std::exception &e) {
		std::cerr	<< RED
					<< e.what()
					<< RESET
					<< std::endl;
	}


	if (this->_lexical_error.size() != 0
	 || this->_syntactic_error.size() != 0
	 || this->_semantic_error.size() != 0) {
		this->_flush_static_errors();
		return 1;
	 }

	/*	~~~~~~~~~~~~~~~~~~~~~ Runtime LAYER ~~~~~~~~~~~~~~~~~~~~~	*/

	Executer	executer;
	try {
		executer.executeProgram(program);
	} catch (const std::exception &e) {
		std::cerr	<< RED
					<< e.what()
					<< RESET
					<< std::endl;
	}

	// if (this->_runtime_error.size() != 0) {
	// 	this->_flush_dynamic_errors();
	// 	return 1;
	// }

	return 0;
}




void	VirtualMachine::_flush_static_errors(void) {

	std::cout << "Lexical errors found:" << std::endl;
	for (std::vector<std::string>::iterator it; it != this->_lexical_error.end(); ++it) {
		std::cout	<< "  |- "
					<< *it
					<< std::endl;
	}

	std::cout << "Syntactic errors found:" << std::endl;
	for (std::vector<std::string>::iterator it; it != this->_syntactic_error.end(); ++it) {
		std::cout	<< "  |- "
					<< *it
					<< std::endl;
	}

	std::cout << "Semantic errors found:" << std::endl;
	for (std::vector<std::string>::iterator it; it != this->_semantic_error.end(); ++it) {
		std::cout	<< "  |- "
					<< *it
					<< std::endl;
	}
}

// void	VirtualMachine::_flush_dynamic_errors(void) {

// 	std::cout << "Runtime errors found:" << std::endl;
// 	for (std::vector<std::string>::iterator it; it != this->_runtime_error.end(); ++it) {
// 		std::cout	<< "  |- "
// 					<< *it
// 					<< std::endl;
// 	}
// }
