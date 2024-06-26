/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:16:55 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:29:34 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef ASTNODE_HPP
# define ASTNODE_HPP

# include <optional>
# include <memory>
# include "../token/Token.hpp"

class ASTNode {
	public:
		virtual ~ASTNode() = default;
};

class InstructionNode : public ASTNode {
	private:
		InstructionNode();
		InstructionNode(InstructionNode const &);
		InstructionNode &	operator=(InstructionNode const &);

	public:
		Token					instruction;
		std::optional<Token>	value;

		InstructionNode(Token instruction, std::optional<Token> value = std::nullopt);
};

class ProgramNode : public ASTNode {
	private:
		ProgramNode();
		ProgramNode(ProgramNode const &);
		ProgramNode &	operator=(ProgramNode const &);

	public:
		std::vector<std::unique_ptr<InstructionNode>>	instructions;
		void	addInstruction(std::unique_ptr<InstructionNode> instr);
};

#endif // ASTNODE_HPP