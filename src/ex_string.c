/* {{{
 * =============================================================================
 *      Filename    :   ex_string.c
 *      Description :
 *      Created     :   2015-08-22 20:08:40
 *      Author      :   Wu Hong
 * =============================================================================
 }}} */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/ex_string.h"

char* ex_strdup(const char *str)
{
    int   len = 0;
    char *buf = NULL;

    if (!str) return NULL;

    len = strlen(str) + 1;
    buf = (char*)malloc(len);

    if(buf) { memcpy(buf, str, len); }

    return buf;
}

char* ex_strndup(const char *str, size_t n)
{
    char* str_copy = (char*)malloc(n+1);

    if (str_copy) {
        strncpy(str_copy, str, n);
        str_copy[n] = '\0';
    }

    return str_copy;
}


char* ex_strtok_r(char* string,             /* string to break into tokens */
                  const char * separators,	/* the separators */
                  char** ppLast             /* pointer to serve as string index */)
{
    if((string == NULL) && ((string = *ppLast) == NULL))
        return (NULL);
    if (*(string += strspn (string, separators)) == '\0')
        return (*ppLast = NULL);
    if ((*ppLast = strpbrk (string, separators)) != NULL)
        *(*ppLast)++ = '\0';
    return (string);
}

int ex_str_split_cnt(const char *str, const char *delimiter)
{
    char *s = (char*)str;
    int cnt = 0;

    while(s && s[0] != '\0') {
        /* printf("hee %s\n", s); */
        while(s && s[0] != '\0' && strchr(delimiter, *s)) s++;
        ++cnt;
        while(s && s[0] != '\0' && !strchr(delimiter, *s)) s++;
    }
        /* exit(0); */

    return cnt;
}


int  ex_str_split_charset(const char *str, const char *charset, char ***parts)
{
    char *pch = NULL;
    char *saveptr = NULL;
    int i = 0;
    int cnt = 0;
    char *tmp = ex_strdup(str);
    char **result = NULL;

    cnt    = ex_str_split_cnt(str, charset) + 1;
    *parts = (char**)malloc(sizeof(char*) * cnt);
    result = *parts;

    pch = ex_strtok_r(tmp, charset, &saveptr);

    result[i]= ex_strdup(pch);
    ++i;

    while (pch) {
        pch = ex_strtok_r(NULL, charset, &saveptr);
        if (NULL == pch) break;
        result[i] = ex_strdup(pch);
        ++i;
        if(i >= cnt) { break; }
    }

    free(tmp);
    return i;
}

int  ex_str_split_substr(const char *str, const char *delimiter, char ***parts)
{
    char *pch = (char*)str;
    int i = 0;
    int l = 0;
    int cnt = 0;
    int offset = 0;
    char **result = NULL;

    cnt    = ex_str_substr_count(str, delimiter) + 1;
    *parts = (char**)malloc(sizeof(char*) * cnt);
    result = *parts;

    printf("cnt:%d\n", cnt);

    l = strlen(delimiter);
    for(i = 0; i < cnt; ++i) {
        pch = strstr(pch, delimiter);

        if(pch) {
            result[i] = ex_strndup(str + offset, pch - str - offset);
            offset += strlen(result[i]) + l;
            pch += l;
        } else {
            result[i] = ex_strdup(str + offset);
        }
    }

    return i;
}

void ex_str_split_free(char **parts, int cnt)
{
    int i = 0;

    for(i = 0; i < cnt; ++i) {
        free(parts[i]);
    }

    free(parts);
}

bool ex_str_starts_with(const char *str, const char *start)
{
    for (; ; str++, start++) {
        if (!*start) {
            return true;
        } else if (*str != *start) {
            return false;
        }
    }
}

bool ex_str_ends_with(const char *str, const char *end)
{
    int end_len = 0;
    int str_len = 0;

    if (NULL == str || NULL == end) return false;

    end_len = strlen(end);
    str_len = strlen(str);

    return str_len < end_len
         ? false
         : !strcmp(str + str_len - end_len, end);
}

int   ex_str_substr_count(const char *str, const char *sub)
{
    char *pos = (char *)str;
    int i = 0;
    int l = 0;

    if (NULL == str || NULL == sub) return -1;

    l = strlen(sub);

    while ((pos = strstr(pos, sub))) {
        pos += l;
        i++;
    }

    return i;
}

char* ex_str_replace(const char *str, const char *sub, const char *replace)
{
    char *pos = (char *) str;
    char *result = NULL;
    char *current = NULL;
    int count = ex_str_substr_count(str, sub);
    int size = 0;

    if (0 >= count) return ex_strdup(str);

    size = (strlen(str) - (strlen(sub) * count) + strlen(replace) * count) + 1;

    result = (char *) malloc(size);
    if (NULL == result) return NULL;
    memset(result, '\0', size);

    while ((current = strstr(pos, sub))) {
        int len = current - pos;
        strncat(result, pos, len);
        strncat(result, replace, strlen(replace));
        pos = current + strlen(sub);
    }

    if (pos != (str + strlen(str))) {
        strncat(result, pos, (str - pos));
    }

    return result;
}

char* ex_str_triml(char *str)
{
    int len = strlen(str);
    char *cur = str;

    while (*cur && isspace(*cur)) {
        ++cur;
        --len;
    }

    if (str != cur) memmove(str, cur, len + 1);

    return str;
}

char* ex_str_trimr(char *str)
{
    int len = strlen(str);
    char *cur = str + len - 1;

    while (cur != str && isspace(*cur)) --cur;
    cur[isspace(*cur) ? 0 : 1] = '\0';

    return str;
}

char* ex_str_trim(char *str)
{
    ex_str_trimr(str);
    ex_str_triml(str);

    return str;
}

const char* ex_str_bool(bool value)
{
    return value ? "true" : "false";
}

const char* ex_str_Bool(bool value)
{
    return value ? "True" : "False";
}

const char* ex_str_BOOL(bool value)
{
    return value ? "TRUE" : "FALSE";
}

const char* ex_str_onoff(bool value)
{
    return value ? "on" : "off";
}

const char* ex_str_OnOff(bool value)
{
    return value ? "On" : "Off";
}

const char* ex_str_ONOFF(bool value)
{
    return value ? "ON" : "OFF";
}

const char* ex_strtime_t(time_t time_val)
{
    static char str[32] = {0};

    time_t time_now    = time_val;
    struct tm* tm_time = localtime(&time_now);

    memset(str, 0, sizeof(str));
    sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d",
            tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
            tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);

    return str;
}

const char* ex_strtime_t_now(void)
{
    return ex_strtime_t(time(NULL));
}

const char* ex_strbytesize(double size)
{
    static char str[128] = {0};

    if(size < 1024){
        sprintf(str, "%g B", size);
    } else if(size < 1024.0 * 1024){
        sprintf(str, "%.2f KB", size / 1024.0);
    } else if(size < 1024.0 * 1024 * 1024){
        sprintf(str, "%.2f MB", size / 1024.0 / 1024.0);
    } else if(size < 1024.0 * 1024.0 * 1024.0 * 1024.0){
        sprintf(str, "%.2f GB", size / 1024.0 / 1024.0 / 1024.0);
    } else {
        sprintf(str, "%.2f TB", size / 1024.0 / 1024.0 / 1024.0 / 1024.0);
    }

    return str;
}
