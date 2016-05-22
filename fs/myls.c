#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    struct stat st;
    mode_t m;

    if (argc == 1) {
        fprintf(stderr, "No args\n");
        return -1;
    }

    if (lstat(argv[1], &st) < 0) {
        perror(argv[1]);
        return -1;
    }

    if (S_ISBLK(st.st_mode)) {
        putchar('b');
    } else if (S_ISCHR(st.st_mode)) {
        putchar('c');
    } else if (S_ISDIR(st.st_mode)) {
        putchar('d');
    } else if (S_ISREG(st.st_mode)) {
        putchar('-');
    } else if (S_ISLNK(st.st_mode)) {
        putchar('l');
    } else if (S_ISFIFO(st.st_mode)) {
        putchar('p');
    } else if (S_ISSOCK(st.st_mode)) {
        putchar('s');
    } else {
        putchar('?');
    }

    putchar(st.st_mode & S_IRUSR ? 'r' : '-');
    putchar(st.st_mode & S_IWUSR ? 'w' : '-');

    m = st.st_mode & (S_ISUID | S_IXUSR );
    switch (m) {
    case (S_ISUID | S_IXUSR):
        putchar('s');
        break;
    case S_ISUID:
        putchar('S');
        break;
    case S_IXUSR:
        putchar('x');
        break;
    case 0:
    default: // to make compiler happy
        putchar('-');
        break;
    }

    putchar(st.st_mode & S_IRGRP ? 'r' : '-');
    putchar(st.st_mode & S_IWGRP ? 'w' : '-');

    m = st.st_mode & (S_ISGID | S_IXGRP);

    switch (m) {
    case (S_ISGID | S_IXGRP):
        putchar('s');
        break;
    case S_ISGID:
        putchar('S');
        break;
    case S_IXGRP:
        putchar('x');
        break;
    case 0:
    default: // to make compiler happy
        putchar('-');
        break;
    }

    putchar(st.st_mode & S_IROTH ? 'r' : '-');
    putchar(st.st_mode & S_IWOTH ? 'w' : '-');
    m = st.st_mode & (S_ISVTX | S_IXOTH);
    switch (m) {
    case (S_ISVTX | S_IXOTH):
        putchar('t');
        break;
    case S_ISVTX:
        putchar('T');
        break;
    case S_IXOTH:
        putchar('x');
        break;
    case 0:
    default: // to make compiler happy
        putchar('-');
        break;
    }

    printf(" %3llu", (unsigned long long)st.st_nlink);

    printf(" %5d", st.st_uid); // Will replace with user/group names in the next iteration
    printf(" %5d", st.st_gid);


    printf(" %7.7lld", (long long)st.st_mtime); // Will replace with string representation in the next iteration
    putchar('\n');

    return 0;
}
