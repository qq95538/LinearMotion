
#include "linearmotioncontrol.hpp"
#include "mraa.hpp"
#include "pthread.h"
#include "time.h"



int main(int argc, char** argv) {

    //Initiate gpio.
    mraa::Gpio* gpio_of_LED = new mraa::Gpio(DEFAULT_IOPIN);
    mraa::Gpio* gpio_of_direction = new mraa::Gpio(DIRECTION_IOPIN);
    mraa::Gpio* gpio_of_pulse = new mraa::Gpio(PULSE_IOPIN);
    if (gpio_of_LED == NULL || gpio_of_direction == NULL || gpio_of_direction == NULL) {
    	printf("Initiate gpio failed");
        return mraa::ERROR_UNSPECIFIED;
    }
    mraa::Result response = gpio_of_LED->dir(mraa::DIR_OUT);
    mraa::Result response_of_direction = gpio_of_direction->dir(mraa::DIR_OUT);
    mraa::Result response_of_pulse = gpio_of_pulse->dir(mraa::DIR_OUT);
    if (response != mraa::SUCCESS || response_of_direction != mraa::SUCCESS || response_of_pulse != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }

	//Initiate Socket.
	int socket_descriptor;
    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);

    //Login Server.
    if(loginserver(socket_descriptor)!=0){
    	printf("Login Server Failed. main() Exit.\n");
    	return -1;
    }

    //Main loop processing server commands.
    int blink = 0;
    uint16_t iDeltaX = 0;
    uint16_t iDirection = 0;
    uint16_t recv_buf[3];
    bool loop_condition = true;
    while(loop_condition){
    	//Receive the reply.
    	static struct sockaddr_in recv_from_address;
    	//static char ipaddr[16];
    	socklen_t recv_from_addr_length;
    	recv_from_addr_length = sizeof(recv_from_address);
    	struct timeval timeout={10,0};//即timeout={10,0}; 或者timeout.tv_sec=4; timeout.tv_usec=0;
    	setsockopt(socket_descriptor,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
    	int ret = recvfrom(socket_descriptor,recv_buf,sizeof(recv_buf),0,(struct sockaddr *)&recv_from_address, &recv_from_addr_length);
    	if(ret<0){
    	    printf("recvfrom function error: %d\n", ret);
    	    if(ret == -1)
    	    	printf("recv timeout!  No Server replied in recent %ld seconds\nThe error occurs in command receving process, Please check whether the server is still working.\n", timeout.tv_sec);
    	    loop_condition = false;
    	}
    	//memset(ipaddr, 0, sizeof(ipaddr));
    	//memcpy(ipaddr, inet_ntoa(recv_from_address.sin_addr), recv_from_addr_length);
    	//printf("Received From IP:%s, %d, %d, %d\n", ipaddr, (uint16_t)recv_buf[0], (uint16_t)recv_buf[1], (uint16_t)recv_buf[2]);
    	switch(recv_buf[0]){
       	case BUF0_COMMAND_SERVER_TO_CLIENT_SEND_MOUSE_POINT:
       		iDeltaX = (int)recv_buf[1];
       		iDirection = recv_buf[2];
       		if(iDirection == 0){
       			gpio_of_direction->write(0);
       		}
       		else{
       			gpio_of_direction->write(1);
       		}
       		for(int i = 0; i < iDeltaX; i++){
       			blink = !blink;
       			usleep(400);
       			gpio_of_LED->write(blink);
       			gpio_of_pulse->write(blink);
       		}
        	break;
       	case BUF0_COMMAND_SERVER_TO_CLIENT_ASK_FOR_A_STILL_ONLINE_MESSAGE:
       		reply_that_I_am_still_online(socket_descriptor);
       		blink = !blink;
       		gpio_of_LED->write(blink);
        	printf("Replied the server that I am still online.\n");
        	break;
    	case BUF0_COMMAND_SERVER_TO_CLIENT_EXIT_NOTIFICATION:
    		reply_an_exit_notification(socket_descriptor);
    		printf("Received an exit command from server. Program Main Loop Ended.\n");
    		loop_condition = false;
    		break;
    	default:
    		printf("Program Main Loop Failed. main() Exit.\n");
    		loop_condition = false;
    		break;
    	}
    	//Send a request.
//    	send_a_position_request(socket_descriptor);
    }
    delete gpio_of_LED;
    shutdown(socket_descriptor, SHUT_RDWR);
    return 0;
}
/*
int send_a_position_request(int socket_descriptor){
    static struct sockaddr_in send_to_address;
    bzero(&send_to_address,sizeof(send_to_address));
    send_to_address.sin_family=AF_INET;
    send_to_address.sin_addr.s_addr=inet_addr(SERVER_IP_ADDRESS_STRING);//这里不一样
    send_to_address.sin_port=htons(8001);
    static const uint16_t send_buf[3] = {BUF0_COMMAND_CLIENT_TO_SERVER_ASK_MOUSE_POINT, 0, 0};
	if( sendto(socket_descriptor,send_buf,sizeof(send_buf), 0,(struct sockaddr *)&send_to_address,sizeof(send_to_address)) != sizeof(send_buf)){
		printf("Sent Messages not equal to which are planned.\n");
		return -1;
	}
	return 1;
}
*/
int reply_an_exit_notification(int socket_descriptor){
	static struct sockaddr_in send_to_address;
    bzero(&send_to_address,sizeof(send_to_address));
    send_to_address.sin_family=AF_INET;
    send_to_address.sin_addr.s_addr=inet_addr(SERVER_IP_ADDRESS_STRING);//这里不一样
    send_to_address.sin_port=htons(8001);
    static const uint16_t send_buf[3] = {BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_AN_EXIT_NOTIFICATION, 0, 0};
	if( sendto(socket_descriptor,send_buf,sizeof(send_buf), 0,(struct sockaddr *)&send_to_address,sizeof(send_to_address)) != sizeof(send_buf)){
		printf("Sent Messages not equal to which are planned.\n");
		return -1;
	}
	return 1;
}

int reply_that_I_am_still_online(int socket_descriptor){
	static struct sockaddr_in send_to_address;
    bzero(&send_to_address,sizeof(send_to_address));
    send_to_address.sin_family=AF_INET;
    send_to_address.sin_addr.s_addr=inet_addr(SERVER_IP_ADDRESS_STRING);//这里不一样
    send_to_address.sin_port=htons(8001);
    static const uint16_t send_buf[3] = {BUF0_COMMAND_CLIENT_TO_SERVER_REPLY_FOR_FOR_A_STILL_ONLINE_MESSAGE, 0, 0};
	if( sendto(socket_descriptor,send_buf,sizeof(send_buf), 0,(struct sockaddr *)&send_to_address,sizeof(send_to_address)) != sizeof(send_buf)){
		printf("Sent Messages not equal to which are planned.\n");
		return -1;
	}
	return 1;
}




int loginserver(int socket_descriptor){
    //Login to the server;
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr(SERVER_IP_ADDRESS_STRING);
    address.sin_port=htons(8001);
    uint16_t send_buf[3];
    send_buf[0] = BUF0_COMMAND_CLIENT_TO_SERVER_VERIFY_USER_PASSWORD;
    send_buf[1] = 1212;
    send_buf[2] = 7329;
    if( sendto(socket_descriptor,send_buf,sizeof(send_buf),0,(struct sockaddr *)&address,sizeof(address)) != sizeof(send_buf)){
        	printf("Sent Messages not equal to which are planned.\n");
        	return -1;
    }
    //receive verify result from the server.
    struct sockaddr_in recv_from_address;
    socklen_t recv_from_addr_length;
    uint16_t recv_buf[3];
    recv_from_addr_length = sizeof(recv_from_address);
	struct timeval timeout={4,0};//即timeout={10,0}; 或者timeout.tv_sec=4; timeout.tv_usec=0;
	setsockopt(socket_descriptor,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
    //qq95538 NOTE:  recvfrom(..., socklen_t *__restrict addr_len) is input and output parameter.
	int ret = recvfrom(socket_descriptor,recv_buf,sizeof(recv_buf), 0,(struct sockaddr *)&recv_from_address,&recv_from_addr_length);
	if(ret < 0){
	    printf("recvfrom function: %d\n", ret);
	    if(ret == -1)
	    	printf("recv timeout!  No Server replied in recent %ld seconds\nThe error occurs in login process, Please check whether the server is started.\n", timeout.tv_sec);
	    return -1;
	}
	char ipaddr[16];
    memset(ipaddr, 0, sizeof(ipaddr));
    memcpy(ipaddr, inet_ntoa(recv_from_address.sin_addr), recv_from_addr_length);
    printf("Received From IP:%s,Contents: %d, %d, %d\n",ipaddr, recv_buf[0], recv_buf[1], recv_buf[2]);
    //receive a server reply.
    switch(recv_buf[0]){
    case BUF0_COMMAND_SERVER_TO_CLIENT_VERIFY_SERVER:
    	if(recv_buf[1] != 1234 || recv_buf[2] != 4321){
    		printf("User/Password Verify failed.\n");
    		return -1;
    	}
    	else{
    		printf("User/Password Verify Succeed, Connected.\n");
    	}
    	break;
    default:
    	printf("Server must be Verified first.\n");
    	return -1;
    }
	return 0;
}
