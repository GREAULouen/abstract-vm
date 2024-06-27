/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:03:21 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 17:41:57 by lgreau           ###   ########.fr       */
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

std::string readStandardInput() {
	std::string	input;
	std::string	line;

	std::cout << "Input your AVM program, ending it with ';;'" << std::endl;

	while (std::getline(std::cin, line)) {
		if (line == ";;")
			break;

		input += line + "\n";
	}
	return input;
}

int	main(int argc, char *argv[])
{
	std::string	input;

	if (argc == 2) {
		try {
			input = readFile(argv[1]);
		} catch (const std::runtime_error &e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	} else {
		input = readStandardInput();
	}

	VirtualMachine	vm;
	int	status = vm.runProgram(input);

	return status;
}
