/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:07:56 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 16:08:31 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef EXECUTER_HPP
# define EXECUTER_HPP

# include "../operand/OperandFactory.hpp"
# include "../operand/Operand.hpp"
# include "../ast/ASTNode.hpp"

# include <stack>
# include <vector>
# include <string>
# include <regex>
# include <iostream>

class Executer
{
	private:
		Executer(Executer const &);
		Executer &	operator=(Executer const &);

		OperandFactory					_operand_factory;
		std::stack<const IOperand*>		_stack;
		std::vector<std::string>		_runtime_error;

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


		/*	~~~~~~~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~~~	*/

		std::pair<eOperandType, std::string>			parseValue(const std::string& value);
		std::pair<const IOperand *, const IOperand *>	getOperands(void);

		template <typename Op>
		void	performBinaryOperation(Op op, const std::string& opName) {
			try {
				auto [lhs, rhs]	= getOperands();

				eOperandType	resultType = static_cast<eOperandType>(std::max(lhs->getPrecision(), rhs->getPrecision()));

				const IOperand	*result = nullptr;
				if (resultType <= eOperandType::INT32) {
					int	lhsValue = std::stoi(lhs->toString());
					int	rhsValue = std::stoi(rhs->toString());
					int	resultValue = op(lhsValue, rhsValue);
					result = this->_operand_factory.createOperand(resultType, std::to_string(resultValue));
				} else {
					double	lhsValue = std::stod(lhs->toString());
					double	rhsValue = std::stod(rhs->toString());
					double	resultValue = op(lhsValue, rhsValue);
					result = this->_operand_factory.createOperand(resultType, std::to_string(resultValue));
				}

				this->_stack.push(result);
				delete lhs;
				delete rhs;
			} catch (std::runtime_error &e) {
				std::stringstream	error_msg;
				error_msg	<< e.what()
							<< " '" << opName << "'";
				flushError(error_msg.str());
				return ;
				// throw std::runtime_error(error_msg.str());
			} catch (std::exception &e) {
				std::cerr	<< RED
							<< "Unforseen exception caught: "
							<< e.what()
							<< RESET
							<< std::endl;
			}
		}

	public:
		Executer();
		~Executer();

		void	executeProgram(ProgramNode * program);
		void	flushError(std::string error_msg);

};

#endif // EXECUTER_HPP
