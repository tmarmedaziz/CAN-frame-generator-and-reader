/* Script made by Mohamed Aziz Tmar */

/*
 * This script enables to open a port and then send custom can frames into this port*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <syscall.h>
#include <iostream>

using namespace std;

int soc;
int read_can_port;

int open_port(const char *port)
{
    /*
     * indicate the port
     */
    struct ifreq ifr;
    struct sockaddr_can addr;

    /* open socket */
    soc = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if(soc < 0)
    {
        return (-1);
    }

    addr.can_family = AF_CAN;

    strcpy(ifr.ifr_name, port);

    if (ioctl(soc, SIOCGIFINDEX, &ifr) < 0)
    {

        return (-1);
    }

    addr.can_ifindex = ifr.ifr_ifindex;

    fcntl(soc, F_SETFL, O_NONBLOCK);

    if (bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {

        return (-1);
    }

    return 0;
}

int send_port(struct can_frame *frame)
{
    /*
     * Send the CAN frame to the port
     */
    int retval;
    retval = write(soc, frame, sizeof(struct can_frame));
    if (retval != sizeof(struct can_frame))
    {
        return (-1);
    }
    else
    {
        return (0);
    }
}

int read_frame(struct can_frame *frame){
    /*
     * Fed by the CAN frame (empty or full)
     */
    unsigned char data_to_send[8];
    int id;

    cout<<"Please enter the id of the CAN frame :";
    cin>>id;
    frame->can_id = id;

    cout<<"Please enter the data of the CAN frame :";
    cin>>data_to_send;

    memcpy(&frame->data, &data_to_send, sizeof(data_to_send) );
    return 0;
}

int main(void)
{
    open_port("vcan0");
    struct can_frame frame_rd;

    read_frame(&frame_rd);
    send_port(&frame_rd);

    return 0;
}
