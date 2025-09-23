#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int Data_variable = 20;
int Bss_variable;

void function() {};

int main()
{
    int Stack_variable = 3;
    char *Char_variable = "hello";
    int *malloc_var = malloc(3000);
    int *mmap_var = mmap(NULL, 3000, PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    pid_t pid = getpid();
    printf("Data memory pointer :  %p \n", (void *)&Data_variable);
    printf("Bss memory pointer :  %p \n", (void *)&Bss_variable);
    printf("Stack memory pointer :  %p \n", (void *)&Stack_variable);
    printf("Str memory pointer : %p \n", (void *)Char_variable);
    printf("Main function memory pointer : %p \n", (void *)function);
    printf("Libc function memory pointer : %p \n", (void *)printf);
    printf("Heap memory pointer : %p \n", (void *)malloc_var);
    printf("mmap memory pointer : %p \n", (void *)mmap_var);
    munmap(mmap_var, 3000);
    free(malloc_var);
    // create a buffer and use it to enter the pid as an arg for execlp
    char pid_buffer[16];
    snprintf(pid_buffer,sizeof(pid_buffer), "%d", pid);
    execlp("pmap", "pmap", "-X", pid_buffer, NULL);
}