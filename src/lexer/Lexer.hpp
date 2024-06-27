/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:00 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 14:20:54 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>
# include <vector>
# include <unordered_map>
# include <regex>

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

		void		skipComment();
		std::string	parseValue();
		Token		parseKeywordOrValue();
		std::string	parseParenthesizedValue();

	public:
		Lexer(const std::string &input);
		std::vector<Token>	tokenize();
};

#endif // LEXER_HPP
