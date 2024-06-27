/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Abstract-vm.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:06:01 by lgreau            #+#    #+#             */
/*   Updated: 2024/06/27 15:43:46 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

# include "token/Token.hpp"
# include "lexer/Lexer.hpp"
# include "ast/ASTNode.hpp"
# include "parser/Parser.hpp"
# include "vm/VirtualMachine.hpp"

#include <fstream>
#include <sstream>

# define RESET "\033[0m"
# define RED "\033[0;31m"

#endif // ABSTRACT_VM_HPP
