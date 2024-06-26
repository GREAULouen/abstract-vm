/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:19:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 14:57:11 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASTNode.hpp"

InstructionNode::InstructionNode(Token instruction, std::optional<Token> value)
		: instruction(instruction), value(value) {}


ProgramNode::ProgramNode() {}

void	ProgramNode::addInstruction(std::unique_ptr<InstructionNode> instr) {
		instructions.push_back(std::move(instr));
}

void	ProgramNode::print() const {
	for (const auto& instr : instructions) {
		std::cout << instr->instruction.value;
		if (instr->value.has_value()) {
			std::cout << " " << instr->value->value;
		}
		std::cout << std::endl;
	}
}