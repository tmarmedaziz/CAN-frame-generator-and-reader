//
// Created by moham on 04/02/2023.
//
//scp .\testcan.cpp ubuntu@192.168.222.137:/home/ubuntu/Vcan/src

/* A simple SocketCAN example */

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

void read_port()
{
    struct can_frame frame_rd;
    int recvbytes = 0;

    read_can_port = 1;
    while(read_can_port)
    {
        struct timeval timeout = {1, 0};
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(soc, &readSet);

        if (select((soc + 1), &readSet, NULL, NULL, &timeout) >= 0)
        {
            if (!read_can_port)
            {
                break;
            }
            if (FD_ISSET(soc, &readSet))
            {
                recvbytes = read(soc, &frame_rd, sizeof(struct can_frame));
                if(recvbytes)
                {
//                    cout<<format("dlc = {}, data = {}\n", frame_rd.can_dlc,frame_rd.data)<<endl;
                    printf("id = %d, data = %s\n", frame_rd.can_id,frame_rd.data);


                }
            }
        }

    }

}

int main(int argc, char* argv[])
{
    if (argc>1){
        open_port(argv[1]);
    } else {
        open_port("vcan0");
    }
    struct can_frame frame_rd;

    send_port(&frame_rd);
    read_port();
    return 0;
}
