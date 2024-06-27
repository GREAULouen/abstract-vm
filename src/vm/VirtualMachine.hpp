/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:07:56 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 11:34:27 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

# include "../operand/OperandFactory.hpp"
# include "../operand/Operand.hpp"
# include "../ast/ASTNode.hpp"

# include <stack>

class VirtualMachine
{
	private:
		VirtualMachine(VirtualMachine const &);
		VirtualMachine &	operator=(VirtualMachine const &);

		OperandFactory			_operand_factory;
		std::stack<IOperand*>	_stack;

		void	_executeInstruction(const InstructionNode& instruction);

		void	_executePush(const Token& valueToken);
		void	_executePop();
		void	_executeDump();
		void	_executeAssert(const Token& valueToken);
		void	_executeAdd();
		void	_executeSub();
		void	_executeMul();
		void	_executeDiv();
		void	_executeMod();
		void	_executePrint();
		void	_executeExit();

	public:
		void	executeProgram(const ProgramNode& program);

};

#endif // VIRTUALMACHINE_HPP
