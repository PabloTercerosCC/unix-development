#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096

int main() {
    // Open the shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map the shared memory object into the process's virtual address space
    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Get the user's name
    char name[100];
    printf("Please enter your name: ");
    fgets(name, 100, stdin);

    // Copy the user's name into the shared memory
    strcpy((char *)shm_ptr, name);

    // Unmap the shared memory object
    if (munmap(shm_ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }

    // Close the shared memory object
    if (close(shm_fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
