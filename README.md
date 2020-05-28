# Directory handling:
### getcwd():
Usage: _char *getcwd(char *buf, size_t size);_

Get current working directory.

getcwd mallocs for _buf_ for length _size_. If _size_ is 0, _buf_ is allocated as big as necessary. Returned buffer has to be freed!

### chdir():
Usage: _int chdir(const char *path);_

Change working directory.

Returns 0 on success and -1 on error.

### opendir():
Usage: _DIR *opendir(const char *name);_

Opens the directory stream of the provided _path_.

Return pointer to the directory stream or NULL on error.

### readdir():
Usage: _struct dirent *readdir(DIR *dirp);_

Reads a directory stream.

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

### closedir():
Usage: _int closedir(DIR *dirp);_

Closes the directory stream associated with \*dirp.

Return 0 on success and -1 on error.

# File handling:
- open, read, close

### dup() & dup2():
Usage:
- _int dup(int oldfd);_
- _int dup2(int oldfd, int newfd);_

Both system calls duplicate an open filediscriptor. 
Dup chooses the lowest available fd for the duplicate whereas dup2 let's. you specify the new fd. 
Afterwards, both fd's can be used interchangebaly. 

On success, these system calls return the new descriptor. On error, -1 is returned, and errno is set appropriately. 

#### Example for dup() & dup2():
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

# Wait, process termination.
Good to know:
- pid_t is a data type with a signed integer type which is capable of representing a process ID.

### wait():
Usage: _pid_t wait(int *stat_loc);_

Suspends execution of its calling process until stat_loc information is available for a terminated child process, or a signal is received. 

If wait() returns due to a stopped or terminated child process, the process ID of the child is returned to the calling process (saved in stat_loc).  Otherwise, a value of -1 is returned and errno is set to indicate the error. If any process has no child process, then wait() immediately returns -1.

### wait4() & wait3() & waitpid():
Usage: 
- _pid_t wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage);
- pid_t wait3(int *stat_loc, int options, struct rusage *rusage);
- pid_t waitpid(pid_t pid, int *stat_loc, int options);_

The _pid_ paramater specifies the set of child processes for which to wait. 

_stat_loc_ is a pointer to an area where status information about how the child process ended is to be placed.

If _rusage_ is non-zero, a summary of the resources used by the terminated process and all its children is returned (this information is currently not available for stopped processes).
     
Wait (4)provides a more general interface for programs that need to wait for certain child processes, that need resource utilization statistics accumulated by child processes. The older wait3() call is the same as wait4() with a pid value of -1. The waitpid() call is identical to wait4() with an rusage value of zero.

# Other:

### execve():
Usage: _int execve(const char *pathname, char *const argv[], char *const envp[]);_

Executes the program referred to by _pathname_.  This causes
the program that is currently being run by the calling process to be
*replaced with a new program*, with newly initialized stack, heap, and
(initialized and uninitialized) data segments.

### fork():
Usage: _pid_t fork(void);_

Causes creation of a new process, The new process (child process) is an exact copy of the calling process (parent process).

Upon succesful completion, fork() returns a value of 0 to the child process and returns the process ID of the child process to the parent process. If it isn't successful, a value of -1 is returned to the parent process, no child process is created, and the global variable eerno is set to indicate the error.

### pipe():
Usage: _int pipe(int pipefd[2]);_

Creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.

Return 0 on success and -1 on error.

### strerror():
Usage: _char *strerror(int errnum);_

Returns a string describing error number _errnum_.

### errno:
Errno is a variable that contains the error number of the last error.
