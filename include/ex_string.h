#ifndef EX_STRING_H_201508222008
#define EX_STRING_H_201508222008
#ifdef __cplusplus
extern "C" {
#endif

/* {{{
 * =============================================================================
 *      Filename    :   ex_string.h
 *      Description :
 *      Created     :   2015-08-22 20:08:04
 *      Author      :   Wu Hong
 * =============================================================================
 }}} */

#include <stdio.h>
#include <stdbool.h>

char* ex_strdup(const char *str);
char* ex_strndup(const char *str, size_t n);

char* ex_strtok_r(char *str, const char *delim, char **saveptr);

int  ex_str_split (const char *str, const char *delimiter, char ***parts);
void ex_str_split_free(char **parts, int cnt);

bool ex_str_starts_with(const char *str, const char *start);
bool ex_str_ends_with(const char *str, const char *end);

int   ex_str_substr_count(const char *str, const char *sub);
char* ex_str_replace(const char *str, const char *sub, const char *replace);

char* ex_str_trim(char *);
char* ex_str_trimr(char *);
char* ex_str_triml(char *);

const char* ex_str_bool(bool value);
const char* ex_str_Bool(bool value);
const char* ex_str_BOOL(bool value);
const char* ex_str_onoff(bool value);
const char* ex_str_OnOff(bool value);
const char* ex_str_ONOFF(bool value);

#ifdef __cplusplus
}
#endif
#endif  /* EX_STRING_H_201508222008 */

