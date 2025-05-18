/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:04 by lgreau            #+#    #+#             */
/*   Updated: 2025/05/18 12:20:47 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <vector>
# include <optional>
# include <iostream>

# define RESET "\033[0m"
# define RED "\033[0;31m"

# include "../token/Token.hpp"
# include "../ast/ASTNode.hpp"

class Parser {
	private:
		Parser();
		Parser(Parser const &);
		Parser &	operator=(Parser const &);

		const std::vector<Token>&	_tokens;
		size_t						_pos;
		bool							_errorsFound;

		InstructionNode*	parseInstruction();
		InstructionNode*	parsePush();
		InstructionNode*	parseAssert();

	public:
		Parser(const std::vector<Token> &tokens);
		ProgramNode *	parse();

		void	flushError(std::string);
};

#endif // PARSER_HPP
