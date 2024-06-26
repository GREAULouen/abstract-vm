/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:03:21 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:13:16 by lgreau           ###   ########.fr       */
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

int	main(void)
{
	std::string	input_file_path = "test_files/simple.avm";

	std::string input;

	try {
		input = readFile(input_file_path);
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	{
		Lexer				lexer(input);
		std::vector<Token>	tokens = lexer.tokenize();

		std::cout << "Found tokens:" << std::endl;
		for (std::vector<Token>::iterator it = tokens.begin(); it != tokens.end(); ++it)
		{
			std::cout << (*it).value << std::endl;
		}
	}
}
