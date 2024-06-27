/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:20:19 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 13:44:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "IOperand.hpp"
# include "Operand.hpp"

class OperandFactory
{
	private:
		OperandFactory(OperandFactory const &);
		OperandFactory &	operator=(OperandFactory const &);

		typedef IOperand const *(OperandFactory::*CreateFunction)(std::string const &) const;
		CreateFunction	_createFunctions[static_cast<int>(eOperandType::UNKNOWN)];

		IOperand const *	_createInt8(std::string const &value) const;
		IOperand const *	_createInt16(std::string const &value) const;
		IOperand const *	_createInt32(std::string const &value) const;
		IOperand const *	_createFloat(std::string const &value) const;
		IOperand const *	_createDouble(std::string const &value) const;
	public:
		OperandFactory();
		~OperandFactory();

		IOperand const *	createOperand(eOperandType type, std::string const &value) const;
};

#endif // OPERANDFACTORY_HPP
