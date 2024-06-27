/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 17:44:33 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <unordered_map>

enum class TokenType {
	PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, VALUE, COMMENT, END, UNKNOWN
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
