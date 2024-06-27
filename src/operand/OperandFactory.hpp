/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:20:19 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 11:27:53 by lgreau           ###   ########.fr       */
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

		IOperand const *	_createInt8(std::string const &value) const {
			int8_t val = static_cast<int8_t>(std::stoi(value));
			return new Operand<int8_t>(val, eOperandType::INT8);
		}

		IOperand const *	_createInt16(std::string const &value) const {
			int16_t val = static_cast<int16_t>(std::stoi(value));
			return new Operand<int16_t>(val, eOperandType::INT16);
		}

		IOperand const *	_createInt32(std::string const &value) const {
			int32_t val = static_cast<int32_t>(std::stoi(value));
			return new Operand<int32_t>(val, eOperandType::INT32);
		}

		IOperand const *	_createFloat(std::string const &value) const {
			float val = std::stof(value);
			return new Operand<float>(val, eOperandType::FLOAT);
		}

		IOperand const *	_createDouble(std::string const &value) const {
			double val = std::stod(value);
			return new Operand<double>(val, eOperandType::DOUBLE);
		}

	public:
		OperandFactory();
		~OperandFactory();

		IOperand const *	createOperand(eOperandType type, std::string const &value) const;
};

#endif // OPERANDFACTORY_HPP
