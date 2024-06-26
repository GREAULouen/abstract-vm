/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 13:55:50 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>
# include <vector>

# include "../token/Token.hpp"

enum class TokenType;
class Token;

class Lexer {
	private:
		Lexer();
		Lexer(Lexer const &);
		Lexer &	operator=(Lexer const &);

		std::string	_input;
		size_t		_pos;
		size_t		_length;

		char	currentChar() const;
		void	consume();
		void	skipComment();
		Token	matchKeywordOrValueType();
		Token	matchNumber();

	public:
		Lexer(const std::string &input);
		std::vector<Token>	tokenize();
};

#endif // LEXER_HPP
