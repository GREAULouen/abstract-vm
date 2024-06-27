/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:35:35 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 18:25:21 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executer.hpp"

Executer::Executer(): _operand_factory() {}

Executer::Executer(Executer const &rhs) {*this = rhs;}
Executer::~Executer() {}
Executer &	Executer::operator=(Executer const &rhs) {
	if (this == &rhs) {return *this;}
	return *this;
}




void	Executer::executeProgram(ProgramNode * program) {
	for (const auto& instruction : program->instructions) {
		this->_executeInstruction(*instruction);
	}
}

void	Executer::_executeInstruction(const InstructionNode& instruction) {
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
			flushError("Unknown instruction: " + instruction.instruction.value);
	}
}




void	Executer::_executePush(const Token& valueToken){
	if (valueToken.type != TokenType::VALUE) {
		flushError("Invalid value type for push: " + valueToken.value);
		return ;
	}

	auto			[type, val]	= parseValue(valueToken.value);
	const IOperand	*operand = this->_operand_factory.createOperand(type, val);
	this->_stack.push(operand);
}


void	Executer::_executePop(){
	if (this->_stack.empty()) {
		flushError("Pop on empty stack");
		return ;
	}

	const IOperand	*op = this->_stack.top();
	this->_stack.pop();
	delete op;
}


void	Executer::_executeDump(){
	std::stack<const IOperand *>	tempStack = this->_stack;

	while (!tempStack.empty()) {
		const IOperand *op = tempStack.top();
		std::cout << op->toString() << std::endl;
		tempStack.pop();
	}
}


void	Executer::_executeAssert(const Token& valueToken){
	if (this->_stack.empty()) {
		flushError("Assert on empty stack");
		return ;
	}

	auto			[type, val] = parseValue(valueToken.value);
	const IOperand	*top = this->_stack.top();
	const IOperand	*expected = this->_operand_factory.createOperand(type, val);

	if (top->getType() != expected->getType()) {
		std::stringstream	error_msg;
		error_msg	<< "Assert failed: types differ: "
					<< static_cast<int>(top->getType())
					<< ", expected: "
					<< static_cast<int>(expected->getType());
		flushError(error_msg.str());
		delete expected;
		return ;
	}
	if (top->toString() != expected->toString()) {
		std::stringstream	error_msg;
		error_msg	<< "Assert failed: values differ: "
					<< top->toString()
					<< ", expected: "
					<< expected->toString();
		flushError(error_msg.str());
		delete expected;
		return ;
	}
	delete expected;
}


void Executer::_executeAdd() {
	performBinaryOperation(std::plus<double>(), "+");
}

void Executer::_executeSub() {
	performBinaryOperation(std::minus<double>(), "-");
}

void Executer::_executeMul() {
	performBinaryOperation(std::multiplies<double>(), "*");
}

void Executer::_executeDiv() {
	performBinaryOperation(std::divides<double>(), "/");
}

void Executer::_executeMod() {
	performBinaryOperation(std::modulus<int>(), "%");
}


void	Executer::_executePrint(){
	if (this->_stack.empty()){
		flushError("Print on empty stack");
		return ;
	}

	const IOperand	*top = this->_stack.top();
	std::cout << top->toString() << std::endl;
}


void	Executer::_executeExit(){
	std::exit(0);
}




/*	~~~~~~~~~~~~~~~~ UTILS ~~~~~~~~~~~~~~~~	*/


std::pair<eOperandType, std::string>	Executer::parseValue(const std::string& value) {
	std::regex	int8_regex(R"(int8\((-?\d+)\))");
	std::regex	int16_regex(R"(int16\((-?\d+)\))");
	std::regex	int32_regex(R"(int32\((-?\d+)\))");
	std::regex	float_regex(R"(float\((-?\d+\.?\d*)\))");
	std::regex	double_regex(R"(double\((-?\d+\.?\d*)\))");

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
		flushError("Invalid value format: " + value);
		return {eOperandType::INT8, "0"};
	}
}


std::pair<const IOperand *, const IOperand *>	Executer::getOperands(void) {
	if (this->_stack.size() < 2)
		throw std::runtime_error("Not enough operands to perform: ");

	const IOperand	*rhs = this->_stack.top();
	this->_stack.pop();
	const IOperand	*lhs = this->_stack.top();
	this->_stack.pop();

	return {lhs, rhs};
}




void	Executer::flushError(std::string error_msg) {
	std::cerr	<< RED
				<< "Runtime error: "
				<< error_msg
				<< RESET
				<< std::endl;
}
