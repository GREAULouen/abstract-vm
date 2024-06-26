/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:04 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:30:39 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <vector>
# include <memory>
# include <optional>

# include "../token/Token.hpp"
# include "../ast/ASTNode.hpp"

class Parser {
	private:
		Parser();
		Parser(Parser const &);
		Parser &	operator=(Parser const &);

		std::vector<Token>	_tokens;
		size_t				_pos;

		bool								isAtEnd() const;
		const Token &						currentToken() const;
		const Token &						consume(TokenType type);
		std::unique_ptr<InstructionNode>	parseInstruction();
		TokenType							nextTokenType() const;

	public:
		Parser(const std::vector<Token> &tokens);
		std::unique_ptr<ProgramNode>	parse();
};

#endif // PARSER_HPP
