/* {{{
 * =============================================================================
 *      Filename    :   ex_file.c
 *      Description :
 *      Created     :   2015-08-23 16:08:22
 *      Author      :   Wu Hong
 * =============================================================================
 }}} */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/select.h>
#include "../include/ex_file.h"
#include "../include/ex_string.h"

#ifdef WIN32
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#define PATH_SEPARATOR   "\\"
#else
#define ACCESS access
#define MKDIR(a) mkdir((a),0755)
#define PATH_SEPARATOR   "/"
#endif

#ifdef __linux__
/* ssize_t read_timed(int fd, void *buf, size_t count, unsigned int msec) */
static ssize_t read_timed_once(int fd, void *buf, size_t count, unsigned int msec)
{
    fd_set rfds;
    struct timeval tv;
    int retval = 1;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    tv.tv_sec  = msec / 1000;
    tv.tv_usec = msec % 1000 * 1000;

    retval = select(fd + 1, &rfds, NULL, NULL, &tv);
    if(retval){
        return read(fd, buf, count);
    } else {
        return retval;
    }
}

#if 1
ssize_t read_timed(int fd, void *buf, size_t count, unsigned int msec)
{
    size_t cnt_left = count;
    int retval = 1;

    while(cnt_left > 0) {
        retval = read_timed_once(fd, (uint8_t*)buf + (count - cnt_left),
                                 cnt_left,  msec);
        if(retval < 0) {
            return retval;
        } else {
            cnt_left -= retval;
        }
    }

    return count;
}
#endif
#endif

FILE  *ex_fopen_readonly(const char *path)
{
    return ex_fopen(path, "r+");
}

FILE  *ex_fopen_write_append(const char *path)
{
    return ex_fopen(path, "a+");
}

FILE  *ex_fopen_write_truncate(const char *path)
{
    return ex_fopen(path, "w+");
}

long ex_file_size(const char *path)
{
    long size = 0;
    FILE *pfile = fopen(path, "rb");
    if(NULL == pfile) {
        return 0;
    }

    size = ex_fsize(pfile);
    ex_fclose(pfile);

    return size;
}

long ex_fsize(FILE *stream)
{
    long offset_old = 0;
    long size = 0;

    offset_old = ex_ftell(stream);
    fseek(stream, 0, SEEK_END);

    size = ex_ftell(stream);

    ex_fseek(stream, offset_old, SEEK_SET);

    return size;
}

int ex_fseek_set(FILE *stream, long offset)
{
    return ex_fseek(stream, offset, SEEK_SET);
}

int ex_fseek_cur(FILE *stream, long offset)
{
    return ex_fseek(stream, offset, SEEK_CUR);
}

int ex_fseek_to_begin(FILE *stream)
{
    return ex_fseek(stream, 0L, SEEK_SET);
}

int ex_fseek_to_end(FILE *stream)
{
    return ex_fseek(stream, 0L, SEEK_END);
}

int ex_fseek_from_begin(FILE *stream, long offset)
{
    return ex_fseek(stream, offset, SEEK_SET);
}

int ex_fseek_from_end(FILE *stream, long offset)
{
    return ex_fseek(stream, offset, SEEK_END);
}

size_t ex_fread(FILE *stream, void *ptr, size_t length)
{
    return fread(ptr, 1, length, stream);
}

uint8_t  ex_fread_u8(FILE *stream,   uint8_t dvalue)
{
    uint8_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

int8_t   ex_fread_s8(FILE *stream,    int8_t dvalue)
{
    int8_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

uint16_t ex_fread_u16(FILE *stream, uint16_t dvalue)
{
    uint16_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

int16_t  ex_fread_s16(FILE *stream,  int16_t dvalue)
{
    int16_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

uint32_t ex_fread_u32(FILE *stream, uint32_t dvalue)
{
    uint32_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

int32_t  ex_fread_s32(FILE *stream,  int32_t dvalue)
{
    int32_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

uint64_t ex_fread_u64(FILE *stream, uint64_t dvalue)
{
    uint64_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

int64_t  ex_fread_s64(FILE *stream,  int64_t dvalue)
{
    int64_t value = dvalue;

    if(ex_fread(stream, &value, sizeof(value)) == sizeof(value)) {
        return value;
    } else {
        return dvalue;
    }
}

size_t ex_fwrite(FILE *stream, const void *ptr, size_t length)
{
    return fwrite(ptr, 1, length, stream);
}

size_t ex_fwrite_u64(FILE *stream, uint64_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

size_t ex_fwrite_s64 (FILE *stream,  int64_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

size_t ex_fwrite_u32(FILE *stream, uint32_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

size_t ex_fwrite_s32 (FILE *stream,  int32_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

size_t ex_fwrite_u16(FILE *stream, uint16_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

size_t ex_fwrite_s16(FILE *stream,  int16_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

size_t ex_fwrite_u8(FILE *stream, uint8_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

size_t ex_fwrite_s8(FILE *stream,  int8_t value)
{
    return ex_fwrite(stream, &value, sizeof(value));
}

bool ex_file_exist(const char *path)
{
    return access(path, 0) == 0 ? true : false;
}

int  ex_mkdir(const char *path)
{
    char *pathname = NULL;
    char *parent = NULL;
    char *p = NULL;
    int result = 0;

    if (NULL == path) return -1;

    pathname = ex_path_normalize(path);
    if (NULL == pathname) goto fail;

    parent = strdup(pathname);
    if (NULL == parent) goto fail;

    p = parent + strlen(parent);
    while (PATH_SEPARATOR[0] != *p && p != parent) {
        p--;
    }
    *p = '\0';

    // make parent dir
    if (p != parent && 0 != ex_mkdir(parent)) goto fail;
    free(parent);

    result = MKDIR(pathname);

    free(pathname);

    return 0 == result || EEXIST == errno
           ? 0 : -1;

fail:
    free(pathname);
    free(parent);

    return -1;
}

int ex_file_remove(const char *path)
{
    if(remove(path) != 0){
        return -1;
    }

    return 0;
}

#ifdef __linux__
static int dirselect( const struct dirent * de )
{
    if(NULL == de) return 0;
    if(de->d_name[0] == '.')/*  去掉隐藏文件以及 '.' '..' */
        return 0;
    return 1;
}
#endif

int ex_scandir(const char *dirp, struct dirent ***namelist)
{
#ifdef __linux__
    return scandir(dirp, namelist, dirselect, alphasort);
#else
    UNUSED(dirp);
    UNUSED(namelist);
    log_warn("ex_scandir now only support linux platform.");
    return 0;
#endif
}

char* ex_path_normalize(const char *path)
{
    int i = 0;
    char *copy = NULL;
    char *ptr  = NULL;

    if (!path) return NULL;

    copy = strdup(path);
    if (NULL == copy) return NULL;

    ptr = copy;

    for(i = 0; copy[i]; i++) {
        *ptr++ = path[i];
        if ('/' == path[i]) {
            i++;
            while ('/' == path[i]) i++;
            i--;
        }
    }

    *ptr = '\0';

    return copy;
}

char* ex_path_join(const char *dir, const char *file)
{
    int size = strlen(dir) + strlen(file) + 2;
    char *buf = (char*)malloc(size * sizeof(char));
    if (NULL == buf) return NULL;

    strcpy(buf, dir);

    // add the sep if necessary
    if (!ex_str_ends_with(dir, PATH_SEPARATOR)) {
        strcat(buf, PATH_SEPARATOR);
    }

    // remove the sep if necessary
    if (ex_str_starts_with(file, PATH_SEPARATOR)) {
        char *filecopy = ex_strdup(file);
        if (NULL == filecopy) {
            free(buf);
            return NULL;
        }
        strcat(buf, ++filecopy);
        free(--filecopy);
    } else {
        strcat(buf, file);
    }

    return buf;
}

char* ex_path_basename (const char *path, const char *extension)
{
    char *base = NULL;
    char *path_copy = NULL;
    char *base_copy = NULL;

    if(!path) return NULL;

    path_copy = ex_strdup(path);
    base = basename(path_copy);

    if(extension && strcmp(extension, "") != 0) {
        base_copy = ex_str_replace(base, extension, "");
    } else {
        base_copy = strdup(base);
    }

    free(path_copy);

    return base_copy;
}
