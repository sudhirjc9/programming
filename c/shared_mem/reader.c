// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234

int main() {
    int shmid;
    char *shm_ptr;

    // Locate the shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to the segment
    shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read and print the data
    printf("Reader: read message: %s\n", shm_ptr);

    // Detach and delete the segment
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL); // Optional: delete memory after use

    return 0;
}
