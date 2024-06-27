/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:05:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 11:12:10 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"

template<typename T>
class Operand: public IOperand
{
	private:
		Operand() {}
		Operand(Operand const &toCopy) {*this = toCopy;}
		Operand &	opeartor=(Operand const &toAssign) {
			if (this == &toAssign) {return *this;}
			this->_value = toAssign._value;
			this->_type = toAssign._type;
			this->_str_repr = toAssign._str_repr;
			return *this;
		}

		T				_value;
		eOperandType	_type;
		std::string		_str_repr;

	public:
		~Operand() {}

		Operand(T value, eOperandType type) : _value(value), _type(type) {
			std::ostringstream oss;
			oss << this->_value;
			this->_str_repr = oss.str();
		}

		int getPrecision() const override {
			return static_cast<int>(this->_type);
		}

		eOperandType getType() const override {
			return this->_type;
		}

		IOperand const *operator+(IOperand const &rhs) const override {
			T result = this->_value + static_cast<T>(std::stod(rhs.toString()));
			return new Operand(result, this->_type);
		}

		IOperand const *operator-(IOperand const &rhs) const override {
			T result = this->_value - static_cast<T>(std::stod(rhs.toString()));
			return new Operand(result, this->_type);
		}

		IOperand const *operator*(IOperand const &rhs) const override {
			T result = value * static_cast<T>(std::stod(rhs.toString()));
			return new Operand(result, this->_type);
		}

		IOperand const *operator/(IOperand const &rhs) const override {
			T rhsValue = static_cast<T>(std::stod(rhs.toString()));
			if (rhsValue == 0) {
				throw std::runtime_error("Division by zero");
			}
			T result = this->_value / rhsValue;
			return new Operand(result, this->_type);
		}

		IOperand const *operator%(IOperand const &rhs) const override {
			T rhsValue = static_cast<T>(std::stod(rhs.toString()));
			if (rhsValue == 0) {
				throw std::runtime_error("Modulo by zero");
			}
			T result = std::fmod(this->_value, rhsValue);
			return new Operand(result, this->_type);
		}

		std::string const &toString() const override {
			return this->_str_repr;
		}

};

#endif // OPERAND_HPP
