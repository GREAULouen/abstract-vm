/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:29:11 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 19:05:10 by lgreau           ###   ########.fr       */
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

class VirtualMachine
{
	private:
		VirtualMachine(VirtualMachine const &);
		VirtualMachine &	operator=(VirtualMachine const &);

	public:
		VirtualMachine();
		~VirtualMachine();

		int	runProgram(std::string);

};

#endif // VIRTUALMACHINE_HPP
