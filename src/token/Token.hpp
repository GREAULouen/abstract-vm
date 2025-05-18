/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:01 by lgreau            #+#    #+#             */
/*   Updated: 2025/05/18 12:04:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <unordered_map>

enum class TokenType {
	PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, VALUE, COMMENT, END, NEWLINE, UNKNOWN
};

class Token {
	public:
		TokenType	type;
		std::string	value;

		Token();
		Token(Token const &);
		Token &	operator=(Token const &);
		Token(TokenType type, std::string value);

		std::string	typeAsString(void);
};

#endif // TOKEN_HPP
