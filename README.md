fork, wait,
waitpid, wait3, wait4, signal, kill, exit, stat, lstat, fstat,


# File handling:
- open, read, close

# Directory handling:
### getcwd:
Get current working directory.
Usage: _char *getcwd(char *buf, size_t size);_

getcwd mallocs for _buf_ for length _size_. If _size_ is 0, _buf_ is allocated as big as necessary. Returned bufer has to be freed!

### chdir:
Change working directory.
Usage: _int chdir(const char *path);_

Returns 0 on success and -1 on error.

### opendir
Opens the directory stream of the provided _path_.
Usage: _DIR *opendir(const char *name);_

Return pointer to the directory stream or NULL on error.

### readdir
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

#### Example of combining _opendir_ & _readdir_:
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

## closedir
Closes the directory stream associated with \*dirp.
Usage: _int closedir(DIR *dirp);_

Return 0 on success and -1 on error.





- chdir, opendir, readdir, closedir, execve, dup, dup2, pipe,
strerror, errno
