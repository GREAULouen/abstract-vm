/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:59:29 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 16:17:15 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

# define RESET "\033[0m"
# define RED "\033[0;31m"

enum class eOperandType {
	INT8, INT16, INT32, FLOAT, DOUBLE, UNKNOWN
};

class IOperand {
	public:
		virtual int				getPrecision( void ) const = 0; // Precision of the type of the instance
		virtual eOperandType	getType( void ) const = 0; // Type of the instance

		virtual IOperand const *	operator+( IOperand const & rhs ) const = 0; // Sum
		virtual IOperand const *	operator-( IOperand const & rhs ) const = 0; // Difference
		virtual IOperand const *	operator*( IOperand const & rhs ) const = 0; // Product
		virtual IOperand const *	operator/( IOperand const & rhs ) const = 0; // Quotient
		virtual IOperand const *	operator%( IOperand const & rhs ) const = 0; // Modulo

		virtual std::string const &	toString( void ) const = 0; // String representation of the instance
		virtual ~IOperand( void ) {}
};

#endif // IOPERAND_HPP
