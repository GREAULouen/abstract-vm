/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:35:35 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 13:42:59 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VirtualMachine.hpp"

VirtualMachine::VirtualMachine() {}

VirtualMachine::VirtualMachine(VirtualMachine const &rhs) {*this = rhs;}
VirtualMachine::~VirtualMachine() {}
VirtualMachine &	VirtualMachine::operator=(VirtualMachine const &rhs) {
	if (this == &rhs) {return *this;}
	return *this;
}




void	VirtualMachine::executeProgram(ProgramNode * program) {
	for (const auto& instruction : program->instructions) {
		this->_executeInstruction(*instruction);
	}
}

void	VirtualMachine::_executeInstruction(const InstructionNode& instruction) {
	switch (instruction.instruction.type) {
		case TokenType::PUSH:
			this->_executePush(instruction.value.value());
			break;
		case TokenType::POP:
			this->_executePop();
			break;
		case TokenType::DUMP:
			this->_executeDump();
			break;
		case TokenType::ASSERT:
			this->_executeAssert(instruction.value.value());
			break;
		case TokenType::ADD:
			this->_executeAdd();
			break;
		case TokenType::SUB:
			this->_executeSub();
			break;
		case TokenType::MUL:
			this->_executeMul();
			break;
		case TokenType::DIV:
			this->_executeDiv();
			break;
		case TokenType::MOD:
			this->_executeMod();
			break;
		case TokenType::PRINT:
			this->_executePrint();
			break;
		case TokenType::EXIT:
			this->_executeExit();
			break;
		default:
			throw std::runtime_error("Unknown instruction: " + instruction.instruction.value);
	}
}




void	VirtualMachine::_executePush(const Token& valueToken){
	if (!valueToken.is_operand())
		throw std::runtime_error("Invalid value type for push: " + valueToken.value);

	auto			[type, val]	= parseValue(valueToken.value);
	const IOperand	*operand = this->_operand_factory->createOperand(type, val);
	this->_stack.push(operand);
}


void	VirtualMachine::_executePop(){
	if (this->_stack.empty())
		throw std::runtime_error("Pop on empty stack");

	const IOperand	*op = this->_stack.top();
	this->_stack.pop();
	delete op;
}


void	VirtualMachine::_executeDump(){
	std::stack<const IOperand *>	tempStack = this->_stack;

	while (!tempStack.empty()) {
		const IOperand *op = tempStack.top();
		std::cout << op->toString() << std::endl;
		tempStack.pop();
	}
}


void	VirtualMachine::_executeAssert(const Token& valueToken){
	if (this->_stack.empty())
		throw std::runtime_error("Assert on empty stack");

	auto			[type, val] = parseValue(valueToken.value);
	const IOperand	*top = this->_stack.top();
	const IOperand	*expected = this->_operand_factory->createOperand(type, val);

	if (top->toString() != expected->toString() || top->getType() != expected->getType()) {
		delete expected;
		throw std::runtime_error("Assert failed");
	}
	delete expected;
}


void VirtualMachine::_executeAdd() {
	performBinaryOperation(std::plus<double>(), "+");
}

void VirtualMachine::_executeSub() {
	performBinaryOperation(std::minus<double>(), "-");
}

void VirtualMachine::_executeMul() {
	performBinaryOperation(std::multiplies<double>(), "*");
}

void VirtualMachine::_executeDiv() {
	performBinaryOperation(std::divides<double>(), "/");
}

void VirtualMachine::_executeMod() {
	performBinaryOperation(std::modulus<int>(), "%");
}


void	VirtualMachine::_executePrint(){
	if (this->_stack.empty())
		throw std::runtime_error("Print on empty stack");

	const IOperand	*top = this->_stack.top();
	std::cout << top->toString() << std::endl;
}


void	VirtualMachine::_executeExit(){
	std::exit(0);
}




/*	~~~~~~~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~~~	*/


std::pair<eOperandType, std::string>	VirtualMachine::parseValue(const std::string& value) {
	std::regex	int8_regex(R"(int8\((-?\d+)\))");
	std::regex	int16_regex(R"(int16\((-?\d+)\))");
	std::regex	int32_regex(R"(int32\((-?\d+)\))");
	std::regex	float_regex(R"(float\((-?\d+\.\d+)\))");
	std::regex	double_regex(R"(double\((-?\d+\.\d+)\))");

	std::smatch	match;
	if (std::regex_match(value, match, int8_regex)) {
		return {eOperandType::INT8, match[1]};
	} else if (std::regex_match(value, match, int16_regex)) {
		return {eOperandType::INT16, match[1]};
	} else if (std::regex_match(value, match, int32_regex)) {
		return {eOperandType::INT32, match[1]};
	} else if (std::regex_match(value, match, float_regex)) {
		return {eOperandType::FLOAT, match[1]};
	} else if (std::regex_match(value, match, double_regex)) {
		return {eOperandType::DOUBLE, match[1]};
	} else {
		throw std::runtime_error("Invalid value format");
	}
}


std::pair<const IOperand *, const IOperand *>	VirtualMachine::getOperands(void) {
	if (this->_stack.size() < 2)
		throw std::runtime_error("Not enough operands to perform: ");

	const IOperand	*rhs = this->_stack.top();
	this->_stack.pop();
	const IOperand	*lhs = this->_stack.top();
	this->_stack.pop();

	return {lhs, rhs};
}
