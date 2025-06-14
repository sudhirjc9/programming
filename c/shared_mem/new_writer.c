#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SHM_SIZE 1024

int main() {
    // Create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    char *shm_ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Create or open semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0); // Initial value = 0

    // Write data
    const char *message = "Hello from writer with event!";
    strcpy(shm_ptr, message);
    printf("Writer: wrote message: %s\n", message);

    // Signal the reader
    sem_post(sem);

    // Cleanup
    munmap(shm_ptr, SHM_SIZE);
    close(shm_fd);
    sem_close(sem);
    return 0;
}
