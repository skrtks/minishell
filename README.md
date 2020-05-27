# File handling:
- open, read, close

# Directory handling:
### getcwd():
Get current working directory.
Usage: _char *getcwd(char *buf, size_t size);_

getcwd mallocs for _buf_ for length _size_. If _size_ is 0, _buf_ is allocated as big as necessary. Returned buffer has to be freed!

### chdir():
Change working directory.
Usage: _int chdir(const char *path);_

Returns 0 on success and -1 on error.

### opendir():
Opens the directory stream of the provided _path_.
Usage: _DIR *opendir(const char *name);_

Return pointer to the directory stream or NULL on error.

### readdir():
Reads a directory stream.
Usage: _struct dirent *readdir(DIR *dirp);_

Returns a pointer to _dirent struct_ containing the next item in DIR or NULL on error.	 
The struct has the following format:
```
struct dirent {
    ino_t          d_ino;       /* inode number */
    off_t          d_off;       /* offset to the next dirent */
    unsigned short d_reclen;    /* length of this record */
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types */
    char           d_name[256]; /* filename */
};
```

#### Example of combining _opendir()_ & _readdir()_:
```
#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdio.h>

// Prints the filenames in the root dir ("/")
int main(void) {
	// DIR type represents a 'directory stream'
	DIR *dir;
	struct dirent *entry;


	if ((dir = opendir("/")) == NULL)
		perror("opendir() error");
	else {
		puts("contents of root:");
		while ((entry = readdir(dir)) != NULL)
			printf("  %s\n", entry->d_name);
		closedir(dir);
	}
}
```

## closedir():
Closes the directory stream associated with \*dirp.
Usage: _int closedir(DIR *dirp);_

Return 0 on success and -1 on error.

## execve():
Executes the program referred to by _pathname_.  This causes
the program that is currently being run by the calling process to be
*replaced with a new program*, with newly initialized stack, heap, and
(initialized and uninitialized) data segments.
Usage: _int execve(const char *pathname, char *const argv[], char *const envp[]);_

## dup() & dup2():
Both system calls duplicate an open filediscriptor. 
Usage:
- _int dup(int oldfd)_
- _int dup2(int oldfd, int newfd)_
Dup chooses the lowest available fd for the duplicate whereas dup2 let's. you specify the new fd. 
Afterwards, both fd's can be used interchangebaly. 

On success, these system calls return the new descriptor. On error, -1 is returned, and errno is set appropriately. 

### Example for dup() & dup2():
```
fd 0 is stdin.
If we want stdin to read from a file instead of from stdin, we can replace the file fd 0 refers to like so:

int main() {
	int old_fd;
	int new_fd;

	new_fd = open("path"); // Open a file and save the fd in new_fd.
	old_fd = dup(0); // This moves stdin the the lowest available fd and saves this fd in 'old_fd'
	close(0); // Closes fd 0 so it becomes available again.
	dup(new_fd); // The new_fd is now linked to the lowest available fd, which is 0 because it was just closed. 
	
	close(0); // Close fd 0 again when done.
	dup2(old_fd, 0); // Move stdin back to fd 0.

	return (0);
}
```

## pipe():
Creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.
Usage: _int pipe(int pipefd[2])_

Return 0 on success and -1 on error.

## strerror():
Returns a string describing error number _errnum_.
Usage: _char *strerror(int errnum)_

## errno:
Errno is a variable that contains the error number of the last error.
