/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:23:08 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 14:57:04 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"

OperandFactory::OperandFactory(){
	this->_createFunctions[static_cast<int>(eOperandType::INT8)]	= &OperandFactory::_createInt8;
	this->_createFunctions[static_cast<int>(eOperandType::INT16)]	= &OperandFactory::_createInt16;
	this->_createFunctions[static_cast<int>(eOperandType::INT32)]	= &OperandFactory::_createInt32;
	this->_createFunctions[static_cast<int>(eOperandType::FLOAT)]	= &OperandFactory::_createFloat;
	this->_createFunctions[static_cast<int>(eOperandType::DOUBLE)]	= &OperandFactory::_createDouble;
}

OperandFactory::OperandFactory(OperandFactory const &rhs) {*this = rhs;}

OperandFactory::~OperandFactory() {}

OperandFactory &	OperandFactory::operator=(OperandFactory const &rhs) {
	if (this == &rhs) {return *this;}
	return *this;
}




IOperand const *OperandFactory::_createInt8(std::string const &value) const {
	int8_t	val = static_cast<int8_t>(std::stoi(value));
	return new Operand<int8_t>(val, eOperandType::INT8);
}

IOperand const *OperandFactory::_createInt16(std::string const &value) const {
	int16_t	val = static_cast<int16_t>(std::stoi(value));
	return new Operand<int16_t>(val, eOperandType::INT16);
}

IOperand const *OperandFactory::_createInt32(std::string const &value) const {
	int32_t	val = static_cast<int32_t>(std::stoi(value));
	return new Operand<int32_t>(val, eOperandType::INT32);
}

IOperand const *OperandFactory::_createFloat(std::string const &value) const {
	float	val = std::stof(value);
	return new Operand<float>(val, eOperandType::FLOAT);
}

IOperand const *OperandFactory::_createDouble(std::string const &value) const {
	double	val = std::stod(value);
	return new Operand<double>(val, eOperandType::DOUBLE);
}




IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const {
	int	typeIndex = static_cast<int>(type);
	return (this->*_createFunctions[typeIndex])(value);
}