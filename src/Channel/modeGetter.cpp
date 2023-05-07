/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeGetter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:12:46 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:15:29 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** --------------------------------- MODE GETTER ----------------------------------
*/

bool	Channel::modeInviteOnly() const {

	return(this->inviteOnly);
}

bool	Channel::modePasswordSet() const {

	return(this->passwordSet);
}

bool	Channel::modeMaxUserSet() const {

	return(this->maxUserSet);
}

/* ************************************************************************** */