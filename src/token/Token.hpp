/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:52:52 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>

enum class TokenType {
	PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT,
	INT8, INT16, INT32, FLOAT, DOUBLE, VALUE, COMMENT, SEP, END, UNKNOWN
};

class Token {
	private:
		Token();

	public:
		TokenType	type;
		std::string	value;

		Token(TokenType type, std::string value);
		Token(Token const &);

		Token &	operator=(Token const &);
};

#endif // TOKEN_HPP
