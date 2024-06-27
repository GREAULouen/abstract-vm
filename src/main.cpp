/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:03:21 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 13:15:05 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Abstract-vm.hpp"

std::string readFile(const std::string &filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + filename);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

std::string readInput() {
	std::string	input;
	std::string	line;

	while (std::getline(std::cin, line)) {
		if (line == ";;")
			break;

		input += line + "\n";
	}
	return input;
}

int	main(int argc, char *argv[])
{
	std::string input;

	if (argc == 2) {
		std::string input_file_path = argv[1];

		try {
			input = readFile(input_file_path);
		} catch (const std::runtime_error &e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	} else {
		std::cout << "Enter your AVM program (end with ';;'):" << std::endl;
		input = readInput();
	}

	try {
		Lexer lexer(input);
		std::vector<Token> tokens = lexer.tokenize();

		std::cout << "Tokenized input:" << std::endl;
		for (const auto& token : tokens) {
			std::cout << token.value << std::endl;
		}

		Parser parser(tokens);
		auto program = parser.parse();
		VirtualMachine vm;
		vm.executeProgram(program.get());
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
