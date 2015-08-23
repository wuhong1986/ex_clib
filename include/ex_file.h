#ifndef EX_FILE_H_201508231608
#define EX_FILE_H_201508231608
#ifdef __cplusplus
extern "C" {
#endif

/* {{{
 * =============================================================================
 *      Filename    :   ex_file.h
 *      Description :
 *      Created     :   2015-08-23 16:08:17
 *      Author      :   Wu Hong
 * =============================================================================
 }}} */

#include <stdio.h>
#include <dirent.h>
#include <stdint.h>
#include <stdbool.h>
#ifdef WIN32
#include <direct.h>
#include <io.h>
#elif __linux__
#include <stdarg.h>
#include <sys/stat.h>
#endif

#ifdef __linux__
ssize_t read_timed(int fd, void *buf, size_t count, unsigned int msec);
#endif

/**
 * @Brief  等同fopen，添加打印失败信息
 *
 * @Param path  需要打开的文件路径
 * @Param mode  打开文件的模式
 *
 * @Returns   打开的文件的指针，打开失败则返回NULL
 */
// FILE  *ex_fopen(const char *path, const char *mode);
#define ex_fopen fopen

/**
 * @Brief  以只读方式打开文件
 *
 * @Param path  需要打开的文件路径
 *
 * @Returns
 */
FILE  *ex_fopen_readonly(const char *path);

/**
 * @Brief  以追加方式打开文件
 *
 * @Param path  需要打开的文件路径
 *
 * @Returns
 */
FILE  *ex_fopen_write_append(const char *path);

/**
 * @Brief  以覆盖方式打开文件
 *
 * @Param path  需要打开的文件路径
 *
 * @Returns
 */
FILE  *ex_fopen_write_truncate(const char *path);

size_t ex_fread(FILE *stream, void *ptr, size_t length);
uint8_t  ex_fread_u8(FILE *stream,   uint8_t dvalue);
int8_t   ex_fread_s8(FILE *stream,    int8_t dvalue);
uint16_t ex_fread_u16(FILE *stream, uint16_t dvalue);
int16_t  ex_fread_s16(FILE *stream,  int16_t dvalue);
uint32_t ex_fread_u32(FILE *stream, uint32_t dvalue);
int32_t  ex_fread_s32(FILE *stream,  int32_t dvalue);
uint64_t ex_fread_u64(FILE *stream, uint64_t dvalue);
int64_t  ex_fread_s64(FILE *stream,  int64_t dvalue);
size_t ex_fwrite(FILE *stream, const void *ptr, size_t length);
size_t ex_fwrite_u64(FILE *stream, uint64_t value);
size_t ex_fwrite_s64(FILE *stream,  int64_t value);
size_t ex_fwrite_u32(FILE *stream, uint32_t value);
size_t ex_fwrite_s32(FILE *stream,  int32_t value);
size_t ex_fwrite_u16(FILE *stream, uint16_t value);
size_t ex_fwrite_s16(FILE *stream,  int16_t value);
size_t ex_fwrite_u8 (FILE *stream,  uint8_t value);
size_t ex_fwrite_s8 (FILE *stream,   int8_t value);

#define ex_ftell ftell
#define ex_fseek fseek
int ex_fseek_set(FILE *stream, long offset);
int ex_fseek_cur(FILE *stream, long offset);
int ex_fseek_to_begin(FILE *stream);
int ex_fseek_to_end(FILE *stream);
int ex_fseek_from_begin(FILE *stream, long offset);
int ex_fseek_from_end(FILE *stream, long offset);

long ex_fsize(FILE *stream);
#define 	ex_fclose(pfile) 	\
	do{\
		if(NULL != pfile){\
			fclose(pfile);\
			pfile = NULL;\
		}\
	}while(0)

/*********************************************************************
 *                        ex_file 开头的参数为文件路径               *
 *********************************************************************/
long ex_file_size(const char *path);
int  ex_file_remove(const char *path);
bool ex_file_exist(const char *path);

/*********************************************************************
 *                      目录操作相关API                              *
 *********************************************************************/
int ex_mkdir(const char *path);
int ex_scandir(const char *dirp, struct dirent ***namelist);


char* ex_path_normalize(const char *path);
char* ex_path_join(const char *dir, const char *file);
char* ex_path_basename (const char *path, const char *extension);

#ifdef __cplusplus
}
#endif
#endif  /* EX_FILE_H_201508231608 */

