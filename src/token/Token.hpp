/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 13:37:30 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>

enum class TokenType {
	PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT,
	INT8, INT16, INT32, FLOAT, DOUBLE,
	INTEGER, FLOATING, NEWLINE, COMMENT, END_OF_FILE, UNKNOWN
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

#endif // LEXER_HPP
