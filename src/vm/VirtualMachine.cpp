/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:36:52 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/28 10:57:25 by lgreau           ###   ########.fr       */
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

	return 0;
}
