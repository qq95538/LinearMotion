/*
 * linearmotioncontrol.hpp
 *
 *  Created on: 2016Äê5ÔÂ11ÈÕ
 *      Author: Administrator
 */

#ifndef LINEARMOTIONCONTROL_HPP_
#define LINEARMOTIONCONTROL_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define CLIENT_IP_ADDRESS_STRING "192.168.12.102"
#define SERVER_IP_ADDRESS_STRING "192.168.12.101"
#define BUF0_COMMAND_CLIENT_TO_SERVER_VERIFY_USER_PASSWORD (0x01)
#define BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_AN_EXIT_NOTIFICATION (0x02)
//#define BUF0_COMMAND_CLIENT_TO_SERVER_ASK_MOUSE_POINT (0x04)
#define BUF0_COMMAND_SERVER_TO_CLIENT_VERIFY_SERVER (0x81)
#define BUF0_COMMAND_SERVER_TO_CLIENT_EXIT_NOTIFICATION (0x82)
#define BUF0_COMMAND_SERVER_TO_CLIENT_SEND_MOUSE_POINT (0x84)

#define DEFAULT_IOPIN (13)
#define DIRECTION_IOPIN (2)
#define PULSE_IOPIN (3)


int loginserver(int socket_descriptor);
//int send_a_position_request(int socket_descriptor);
int reply_an_exit_notification(int socket_descriptor);

#endif /* LINEARMOTIONCONTROL_HPP_ */
