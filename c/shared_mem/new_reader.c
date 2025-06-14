#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <errno.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SHM_SIZE 1024

int main() {
    int shm_fd;
    sem_t *sem;
    char *shm_ptr;

    // Wait until shared memory is available
    while ((shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666)) == -1) {
        if (errno != ENOENT) {
            perror("shm_open");
            exit(1);
        }
        printf("Waiting for shared memory...\n");
        sleep(1);
    }

    // Wait until semaphore is available
    while ((sem = sem_open(SEM_NAME, 0)) == SEM_FAILED) {
        if (errno != ENOENT) {
            perror("sem_open");
            exit(1);
        }
        printf("Waiting for semaphore...\n");
        sleep(1);
    }

    shm_ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Reader: waiting for writer to write...\n");

    // Wait for the writer's event
    sem_wait(sem);

    // Read message
    printf("Reader: got message: %s\n", shm_ptr);

    // Cleanup
    munmap(shm_ptr, SHM_SIZE);
    close(shm_fd);
    sem_close(sem);
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);

    return 0;
}
