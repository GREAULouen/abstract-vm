/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:29:11 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 17:39:36 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

# include <vector>
# include <string>
# include <sstream>
# include <iostream>
# include <exception>

# include "../lexer/Lexer.hpp"
# include "../parser/Parser.hpp"
# include "../exec/Executer.hpp"

# define RESET "\033[0m"
# define RED "\033[0;31m"

class VirtualMachine
{
	private:
		VirtualMachine(VirtualMachine const &);
		VirtualMachine &	operator=(VirtualMachine const &);

		// Stores all errors to be flushed
		std::vector<std::string>	_lexical_error;
		std::vector<std::string>	_syntactic_error;
		std::vector<std::string>	_semantic_error;

		void	_flush_static_errors(void);
		// void	_flush_dynamic_errors(void);

	public:
		VirtualMachine();
		~VirtualMachine();

		int	runProgram(std::string);

};

#endif // VIRTUALMACHINE_HPP
