#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

// Renvoie le temps actuel en millisecondes
unsigned long get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

int main() {
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    const char *ifname = "can0";

    // 1. Création du SocketCAN
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket creation failed");
        return 1;
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    srand(time(NULL));

    // Timers pour chaque tâche (ms)
    unsigned long t_101 = get_time_ms();
    unsigned long t_203 = get_time_ms();
    unsigned long t_205 = get_time_ms();
    unsigned long t_418 = get_time_ms();
    unsigned long t_503 = get_time_ms();

    // Variable pour ZZ (0x00 à 0xA0 = 160 décimal)
    unsigned char zz_val = 0;

    struct can_frame frame;

    printf("Démarrage de l'envoi CAN sur %s... Press Ctrl+C to stop.\n", ifname);

    while (1) {
        unsigned long now = get_time_ms();

        // 1. ID 0x101 | 10ms | Payload: 0x0100
        if (now - t_101 >= 10) {
            frame.can_id = 0x101;
            frame.can_dlc = 2;
            frame.data[0] = 0x01;
            frame.data[1] = 0x00;
            write(s, &frame, sizeof(struct can_frame));
            t_101 = now;
        }

        // 2. ID 0x203 | 20ms | Payload: YY 02 YY
        if (now - t_203 >= 20) {
            frame.can_id = 0x203;
            frame.can_dlc = 3;
            frame.data[0] = rand() % 256;
            frame.data[1] = 0x02;
            frame.data[2] = rand() % 256;
            write(s, &frame, sizeof(struct can_frame));
            t_203 = now;
        }

        // 3. ID 0x205 | 30ms | Payload: 45 YY
        if (now - t_205 >= 30) {
            frame.can_id = 0x205;
            frame.can_dlc = 2;
            frame.data[0] = 0x45;
            frame.data[1] = rand() % 256;
            write(s, &frame, sizeof(struct can_frame));
            t_205 = now;
        }

        // 4. ID 0x418 | 100ms | Payload: 00 78 ZZ (ZZ s'arrête à 0xA0 / 160)
        if (now - t_418 >= 100) {
            frame.can_id = 0x418;
            frame.can_dlc = 3;
            frame.data[0] = 0x00;
            frame.data[1] = 0x78;
            frame.data[2] = zz_val;
            write(s, &frame, sizeof(struct can_frame));

            if (zz_val < 0xA0) {
                zz_val++;
            }
            t_418 = now;
        }

        // 5. ID 0x503 | 200ms | Payload: YY 55 YY 00 YY
        if (now - t_503 >= 200) {
            frame.can_id = 0x503;
            frame.can_dlc = 5;
            frame.data[0] = rand() % 256;
            frame.data[1] = 0x55;
            frame.data[2] = rand() % 256;
            frame.data[3] = 0x00;
            frame.data[4] = rand() % 256;
            write(s, &frame, sizeof(struct can_frame));
            t_503 = now;
        }

        // Pause de 1ms pour ne pas faire consommer 100% de CPU à la boucle
        usleep(1000);
    }

    close(s);
    return 0;
}
