/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:37:37 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/26 13:45:03 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(TokenType type, std::string value): type(type), value(value) {}
Token::Token(Token const &toCopy) {*this = toCopy;}

Token &	Token::operator=(Token const &toAssign)
{
	if (this == &toAssign)
		return *this;
	this->type = toAssign.type;
	this->value = toAssign.value;
	return *this;
}
