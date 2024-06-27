/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:19:24 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 16:59:42 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASTNode.hpp"

InstructionNode::InstructionNode(Token instruction, std::optional<Token> value)
		: instruction(instruction), value(value) {}


ProgramNode::ProgramNode() {}

void	ProgramNode::addInstruction(InstructionNode *instr) {
		instructions.push_back(instr);
}
