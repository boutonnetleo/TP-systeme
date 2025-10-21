#include <fcntl.h>
#include "tosfs.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    int fd;
    struct stat st;
    fd = open("test_tosfs_files",O_RDWR);
    fstat(fd,&st);
    printf("size of file is : %ld \n" ,st.st_size);
    off_t file_size = st.st_size;
    struct tosfs_superblock *data = mmap(NULL, file_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    printf("bitmap block is : "PRINTF_BINARY_PATTERN_INT32 "\n",PRINTF_BYTE_TO_BINARY_INT32(data->block_bitmap));
    printf("bitmap inodes is : "PRINTF_BINARY_PATTERN_INT32 "\n",PRINTF_BYTE_TO_BINARY_INT32(data->inode_bitmap));
    printf("inodes : %d \n" ,data->inodes);
    printf("blocks : %d \n" ,data->blocks);
    printf("magic : %d \n" ,data->magic);
    printf("tosfmagic : %d \n", TOSFS_MAGIC);
    printf("root_inode : %d \n" ,data->root_inode);
    munmap(data,file_size);
}