/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:00:26 by cdutel            #+#    #+#             */
/*   Updated: 2025/01/16 23:01:33 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# define ERR_MSG_ARG "Error\nBad input, please retry with : \
./cub3D mapname.cub\n"
# define ERR_MSG_MALLOC "Error\nCan't allocate memory\n"
# define ERR_MSG_FILENAME "Error\nInvalid filename. Filename should be a .cub\n"
# define ERR_MSG_INVALID "Error\nLine is not valid : "
# define ERR_MSG_INV "Error\nThere should be at least 4 texture_path, 2 colours and\
 map description should be at the end of the file\n"
/*Textures*/
# define ERR_MSG_TEXT_ID "Error\nInvalid texture identifier : "
# define ERR_MSG_INVALID_TEXT "Error\nInvalid texture name : "
# define ERR_MSG_TEXT_NAME "Error\nTwo texture have the same path\n"
# define ERR_MSG_OPEN_TEXT "Error\nCan't open : "
# define ERR_MSG_2_NORTH_TEXT "Error\nThere cannot be 2 north textures\n"
# define ERR_MSG_2_SOUTH_TEXT "Error\nThere cannot be 2 south textures\n"
# define ERR_MSG_2_EAST_TEXT "Error\nThere cannot be 2 east textures\n"
# define ERR_MSG_2_WEST_TEXT "Error\nThere cannot be 2 west textures\n"
# define ERR_MSG_2_DC_TEXT "Error\nNo closed door textures\n"
# define ERR_MSG_2_DO_TEXT "Error\nNo opened door textures\n"
# define ERR_MSG_LOAD_TEXT "Error\nCouldn't load textures\n"
/*Colours*/
# define ERR_MSG_COL_ID "Error\nInvalid colour identifier : "
# define ERR_MSG_INVALID_COL "Error\nInvalid colours number : "
# define ERR_MSG_RANGE_COL "Error\nColour number should be betweem 0 and 255 : "
/*Map*/
# define ERR_MSG_PLAYER "Error\nThere can only be one player\n"
# define ERR_MSG_NO_PLAYER "Error\nThere is no player in the map\n"
# define ERR_MSG_MAP_OP "Error\nMap shouldn't be open : "
# define ERR_MSG_MAP_OPEN "Error\nMap shouldn't be open\n"
/*Window*/
# define ERR_MSG_WINDOW "Error\nCan't open window\n"
#endif
