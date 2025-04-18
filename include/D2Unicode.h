/**
 * D2MOO
 * Copyright (c) 2020-2022  The Phrozen Keep community
 *
 * This file belongs to D2MOO.
 * File authors: Mir Drualga
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <wchar.h>

#include <D2BasicTypes.h>

#include "D2Lang.h"

enum Unicode_Direction {
  DIR_LEFT_TO_RIGHT = 0xF0,
  DIR_RIGHT_TO_LEFT = 0xF1,
  DIR_NEUTRAL = 0xF2,
};

/*
* This type must be struct in order to make certain functions'
* mangled names the same as the ones in D2Lang.
*/
struct D2LANG_DLL_DECL Unicode {
  /* unsigned short */ char ch;
};

/**
 * Performs case insensitive comparison between a Unicode code
 * unit to another.
 *
 * D2Lang.0x6FC11150 (#10022) ?compare@Unicode@@SIHU1@0@Z
 */
BOOL __cdecl Unicode_compare(struct Unicode lhs, struct Unicode rhs);

/**
 * Returns whether the specified character in the string is the last
 * character of a word. In this function, only characters in the
 * English alphabet or Arabic numerals are considered characters in
 * a word. The first character is also not considered the end of a
 * word.
 *
 * D2Lang.0x6FC11190 (#10031) ?isWordEnd@Unicode@@SIHPBU1@I@Z
 */
BOOL __cdecl Unicode_isWordEnd(const struct Unicode* str, size_t index);

/**
 * Performs string conversions on the supplied parameters, similar
 * to standard C's printf.
 *
 * Only the conversion specifiers %%, %d, %u, and %s are supported.
 * %s represents a pointer to a null-terminated Unicode string. To
 * specify an unsupported conversion specifier will result in an
 * assertion error. Flags, minimum field width, precision, and
 * length modifiers are not supported.
 *
 * D2Lang.0x6FC11670 (#10033) ?sprintf@Unicode@@SAXHPAU1@PBU1@ZZ
 */
void __cdecl Unicode_sprintf(
    int buffer_size,
    struct Unicode* buffer,
    const struct Unicode* format,
    ...);

/**
 * Appends a null-terminated string to the end of a null-terminated
 * destination string. Returns the destination string.
 *
 * D2Lang.0x6FC113F0 (#10034) ?strcat@Unicode@@SIPAU1@PAU1@PBU1@@Z
 */
struct Unicode* __cdecl Unicode_strcat(struct Unicode* dest, const struct Unicode* src);

/**
 * Returns the first occurrence of a character in a null-terminated
 * string.
 *
 * If the character could not be found, or the character to find is
 * the null-terminating character, then the function returns NULL.
 *
 * D2Lang.0x6FC113C0 (#10035) ?strchr@Unicode@@SIPAU1@PBU1@U1@@Z
 */
struct Unicode* __cdecl Unicode_strchr(const struct Unicode* str, struct Unicode ch);

/**
 * Compares two null-terminated strings lexicographically. Returns
 * -1, 0, or 1, depending on the results of the comparison.
 *
 * D2Lang.0x6FC11210 (#10036) ?strcmp@Unicode@@SIHPBU1@0@Z
 */
int __cdecl Unicode_strcmp(const struct Unicode* str1, const struct Unicode* str2);

/**
 * Copies the characters from a null-terminated source string into a
 * null-terminated destination string. Returns the destination
 * string.
 *
 * D2Lang.0x6FC114A0 (#10038) ?strcpy@Unicode@@SIPAU1@PAU1@PBU1@@Z
 */
struct Unicode* __cdecl Unicode_strcpy(struct Unicode* dest, const struct Unicode* src);

/**
 * Performs lexicographical, case-insensitive comparison between two
 * null-terminated strings. Returns -1, 0, or 1, depending on the
 * results of the comparison.
 *
 * If either string is the NULL pointer, then the behavior is
 * undefined.
 *
 * D2Lang.0x6FC112A0 (#10039) ?stricmp@Unicode@@SIHPBU1@0@Z
 */
int __cdecl Unicode_stricmp(const struct Unicode* str1, const struct Unicode* str2);

/**
 * Performs lexicographical, case-insensitive comparison between two
 * null-terminated strings. Returns -1, 0, or 1, depending on the
 * results of the comparison.
 *
 * If either string is the NULL pointer, then the behavior is
 * undefined.
 *
 * D2Lang.0x6FC11310 (#10045) ?strnicmp@Unicode@@SIHPBU1@0I@Z
 */
int __cdecl Unicode_strnicmp(const struct Unicode* str1, const struct Unicode* str2, size_t count);

/**
 * Returns the length of the null-terminated string. If the string
 * pointer is NULL, the function returns 0;
 *
 * D2Lang.0x6FC114C0 (#10040) ?strlen@Unicode@@SIHPBU1@@Z
 */
int __cdecl Unicode_strlen(const struct Unicode* str);

/**
 * Appends a null-terminated string to the end of a destination
 * null-terminated string. The maximum number of characters appended
 * is specified as the count. The destination string will always
 * append a terminating null character, so that (count + 1)
 * characters can be written.
 *
 * D2Lang.0x6FC11420 (#10041) ?strncat@Unicode@@SIPAU1@PAU1@PBU1@H@Z
 */
struct Unicode* __cdecl Unicode_strncat(
    struct Unicode* dest,
    const struct Unicode* src,
    int count);

/*
 * Compares two null-terminated strings or substrings
 * lexicographically. Returns -1, 0, or 1, depending on the results
 * of the comparison.
 *
 * If either string is the NULL pointer, then the behavior is
 * undefined.
 *
 * Vanilla bug: If one string is a prefix of another, then the
 * function will always return 0, even when the specified count is
 * greater than the length of the prefix.
 *
 * D2Lang.0x6FC11250 (#10042) ?strncmp@Unicode@@SIHPBU1@0I@Z
 */
int __cdecl Unicode_strncmp(
    const struct Unicode* str1,
    const struct Unicode* str2,
    size_t count);

/**
 * Copies up to a specified count of characters from a
 * null-terminated source string into a null-terminated destination
 * string. If the count is greater than the length of the source
 * string, then the remaining characters are filled with the null
 * terminator character. Returns the destination string.
 *
 * 1.00: D2Lang.0x1000114A (#10042)
 * 1.10: D2Lang.0x6FC11460 (#10044)
 * 1.11: D2Lang.0x6FC0A900 (#10044)
 * 1.13c: D2Lang.0x6FC0B0D0 (#10044)
 * ?strncpy@Unicode@@SIPAU1@PAU1@PBU1@H@Z
 */
struct Unicode* __cdecl Unicode_strncpy(
    struct Unicode* dest, const struct Unicode* src, int count);

/**
 * Returns the first occurrence of a null-terminated substring in a
 * null-terminated string. If the substring is empty, or the
 * string does not contain the substring, then the function returns
 * NULL.
 *
 * D2Lang.0x6FC0B020 (#10046) ?strstr@Unicode@@SIPAU1@PBU1@0@Z
 */
struct Unicode* __cdecl Unicode_strstr(
    const struct Unicode* str,
    const struct Unicode* substr);

/**
 * Converts a null-terminated UTF-8 string into a null-terminated
 * UCS-2 string. The count indicates the capacity of the destination
 * in terms of UCS-2 characters. Returns the pointer to the
 * destination string.
 *
 * Vanilla bug: Specifying INT_MIN for the count results in
 * undefined behavior. Do not specify INT_MIN as the count.
 *
 * D2Lang.0x6FC12A40 (#10051) ?toUnicode@Unicode@@SIPAU1@PAU1@PBDH@Z
 */
struct Unicode* __cdecl Unicode_toUnicode(
    struct Unicode* dest,
    const char* src,
    int count);

/**
 * Converts a null-terminated UCS-2 string into a null-terminated
 * 7-bit ASCII string. The count indicates the capacity of the
 * destination in terms of UCS-2 characters. Returns the pointer to
 * the destination string.
 *
 * 1.00: D2Lang.0x1000109B (#10053)
 * 1.10: D2Lang.0x6FC11C20 (#10055)
 * ?unicode2Win@Unicode@@SIPADPADPBU1@H@Z
 */
char* __cdecl Unicode_unicode2Win(
    char* dest, const struct Unicode* src, int count);

/**
 * Converts a null-terminated UCS-2 string into a null-terminated
 * UTF-8 string. The count indicates the capacity of the destination
 * in terms of UTF-8 code units. Returns the pointer to the
 * destination string.
 *
 * Vanilla bug: Specifying INT_MIN for the count results in
 * undefined behavior. Do not specify INT_MIN as the count.
 *
 * Vanilla bug: Count is insufficient for preventing buffer overrun
 * for code points that require three UTF-8 code units. To work
 * around this, specify a lower count value.
 *
 * D2Lang.0x6FC12B60 (#10053) ?toUtf@Unicode@@SIPADPADPBU1@H@Z
 */
char* __cdecl Unicode_toUtf(char* dest, const struct Unicode* src, int count);

//1.10f: D2Lang.0x6FC11B30 (#10059) ?utf8ToUnicode@Unicode@@SIPAU1@PAU1@PBDH@Z
struct Unicode* __cdecl Unicode_utf8ToUnicode(struct Unicode* dest, char const* src, int count);

/**
 * Converts a null-terminated 7-bit ASCII string into a
 * null-terminated UCS-2 string. The count indicates the capacity of
 * the destination in terms of UCS-2 characters. Returns the pointer
 * to the destination string.
 *
 * 1.00: D2Lang.0x10001122 (#10059)
 * 1.10: D2Lang.0x6FC11BD0 (#10062)
 * ?win2Unicode@Unicode@@SIPAU1@PAU1@PBDH@Z
 */
struct Unicode* __cdecl Unicode_win2Unicode(
    struct Unicode* dest, const char* src, int count);

// D2Lang.0x6FC11C50 (#10023) ?directionality@Unicode@@QAE?AW4Direction@1@XZ
enum Unicode_Direction Unicode_directionality(struct Unicode self);

/**
 * Returns whether or not this Unicode character is in 
 * "C0 Controls and Basic Latin" character block, otherwise known as
 * the ASCII character block.
 *
 * D2Lang.0x6FC11080 (#10024) ?isASCII@Unicode@@QBEHXZ
 */
BOOL Unicode_isASCII(struct Unicode self);

/**
 * Returns whether or not this Unicode character is an alphabetic
 * character.
 *
 * D2Lang.0x6FC11090 (#10025) ?isAlpha@Unicode@@QBEHXZ
 */
BOOL Unicode_isAlpha(struct Unicode self);

// D2Lang.0x6FC11A30 (#10027) ?isLineBreak@Unicode@@SIHPBU1@I@Z
BOOL __cdecl Unicode_isLineBreak(const struct Unicode* str, size_t count);

// D2Lang.0x6FC11050 (#10028) ?isNewline@Unicode@@QBEHXZ
BOOL Unicode_isNewline(struct Unicode self);

// D2Lang.0x6FC11060 (#10029) ?isPipe@Unicode@@QBEHXZ
BOOL Unicode_isPipe(struct Unicode self);

// D2Lang.0x6FC11030 (#10030) ?isWhitespace@Unicode@@QBEHXZ
BOOL Unicode_isWhitespace(struct Unicode self);

/**
 * Returns this character's lowercase if there is a lowercase for
 * this character. Otherwise, returns a copy of this character.
 *
 * Vanilla bug: Returns uppercase for characters in the
 * "Latin-1 Supplement" block.
 *
 * D2Lang.0x6FC110E0 (#10050) ?toLower@Unicode@@QBE?AU1@XZ
 */
struct Unicode Unicode_toLower(struct Unicode self);

/**
 * Returns this character's uppercase if there is an uppercase for
 * this character. Otherwise, returns a copy of this character.
 *
 * D2Lang.0x6FC110B0 (#10052) ?toUpper@Unicode@@QBE?AU1@XZ
 */
struct Unicode Unicode_toUpper(struct Unicode self);

/**
 * Vanilla bug: The characters in the Latin-1 Supplement block are
 * uppercase.
 *
 * D2Lang.[0x6FC1D508 to 0x6FC1D708) (#10019) ?_toLowerTable@Unicode@@0PAGA
 */
extern unsigned short Unicode_toLowerTable[256];

// D2Lang.[0x6FC1D308 to 0x6FC1D508) (#10020) ?_toUpperTable@Unicode@@0PAGA
extern unsigned short Unicode_toUpperTable[256];
