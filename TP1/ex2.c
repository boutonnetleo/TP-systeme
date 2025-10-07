#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int fd;
int main(){
    struct stat st;
    fd = open("test.txt",O_RDWR);
    fstat(fd,&st);
    printf("size of file is : %ld \n" ,st.st_size);
    off_t file_size = st.st_size;
    char *data = mmap(NULL, file_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    
    for(off_t i =0 ;i<file_size/2;i++){
        char temp=data[i];
        data[i]=data[file_size-1-i];
        data[file_size-1-i]=temp;
    }

    munmap(data, st.st_size);
    close(fd);
}