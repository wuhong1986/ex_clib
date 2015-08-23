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

char* exstr_dup(const char *str);
char* exstr_ndup(const char *str, size_t n);

char* exstr_tok_r(char *str, const char *delim, char **saveptr);

int  exstr_split (const char *str, const char *delimiter, char ***parts);
void exstr_split_free(char **parts, int cnt);

bool exstr_starts_with(const char *str, const char *start);
bool exstr_ends_with(const char *str, const char *end);

int   exstr_substr_count(const char *str, const char *sub);
char* exstr_replace(const char *str, const char *sub, const char *replace);

char* exstr_trim(char *);
char* exstr_trimr(char *);
char* exstr_triml(char *);

const char* exstr_bool(bool value);
const char* exstr_Bool(bool value);
const char* exstr_BOOL(bool value);
const char* exstr_onoff(bool value);
const char* exstr_OnOff(bool value);
const char* exstr_ONOFF(bool value);

#ifdef __cplusplus
}
#endif
#endif  /* EX_STRING_H_201508222008 */

