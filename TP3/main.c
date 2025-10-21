#include <fcntl.h>
#include "tosfs.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


struct tosfs_superblock * checkfile(char* file){
    int fd;
    struct stat st;
    fd = open(file,O_RDWR);
    fstat(fd,&st);
    printf("size of file is : %ld \n" ,st.st_size);
    off_t file_size = st.st_size;
    struct tosfs_superblock *data = mmap(NULL, file_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(data->magic==TOSFS_MAGIC){
        return data;
    }
}


void infoSuperblock(struct tosfs_superblock* data){
    printf("magic : %d \n" ,data->magic);
    printf("bitmap block is : "PRINTF_BINARY_PATTERN_INT32 "\n",PRINTF_BYTE_TO_BINARY_INT32(data->block_bitmap));
    printf("bitmap inodes is : "PRINTF_BINARY_PATTERN_INT32 "\n",PRINTF_BYTE_TO_BINARY_INT32(data->inode_bitmap));
    printf("inodes : %d \n" ,data->inodes);
    printf("blocks : %d \n" ,data->blocks);
    printf("block-size : %d \n" ,data->block_size);
    printf("root_inode : %d \n" ,data->root_inode);
}

void infoInode(struct tosfs_inode* inodeStart,int inodeNumber){
    struct tosfs_inode* inode = inodeStart+ inodeNumber;
    printf("Inode : %d \n" ,inode->inode);
    printf("block no : %d \n" ,inode->block_no);
    printf("Uid : %d \n" ,inode->uid);
    printf("Gid : %d \n" ,inode->gid);
    printf("Mode : %d \n" ,inode->mode);
    printf("Perm : %d \n" ,inode->perm);
    printf("size : %d \n" ,inode->size);
    printf("nlink : %d \n" ,inode->nlink);
}

int main(){
    struct tosfs_superblock *data = checkfile("test_tosfs_files");
    infoSuperblock(data);

    struct tosfs_inode* inodeStart = ((void*) data + data->block_size);
    infoInode(inodeStart,2);

    munmap(data,data->block_size * data->blocks);
}