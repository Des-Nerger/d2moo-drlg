/**
 * Copyright (c) 2021 Mir Drualga
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

#include <D2Unicode.h>
#include <D2StrTable.h>

unsigned short Unicode_toLowerTable[256] = {
  // C0 Controls
  '\0', 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, '\a', '\b', '\t', '\n',
  '\v', '\f', '\r', 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,

  // Basic Latin
  ' ', '!', '\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',
  '-', '.', '/',

  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

  ':', ';', '<', '=', '>', '\?', '@',

  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

  '[', '\\', ']', '^', '_', '`',

  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

  '{', '|', '}', '~', 0x7F,

  // C1 Controls
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
  0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99,

  0x8A, 0x9B, 0x8C, 0x9D, 0x9E, 0x9F,

  // Latin-1 Supplement
  // Vanilla bug: The characters are uppercase.
  0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
  0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
  0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
  0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,

  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
  0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
  0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,

  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
  0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,

  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,

  0xF7,

  0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE,

  0x9F
};

unsigned short Unicode_toUpperTable[256] = {
  // C0 Controls
  L'\0', 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, L'\a', L'\b', L'\t', L'\n',
  L'\v', L'\f', L'\r', 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,

  // Basic Latin
  L' ', L'!', L'\"', L'#', L'$', L'%', L'&', L'\'', L'(', L')', L'*', L'+',
  L',', L'-', L'.', L'/',

  L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9',

  L':', L';', L'<', L'=', L'>', L'\?', L'@',

  L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J', L'K', L'L',
  L'M', L'N', L'O', L'P', L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X',
  L'Y', L'Z',

  L'[', L'\\', L']', L'^', L'_', L'`',

  L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J', L'K', L'L',
  L'M', L'N', L'O', L'P', L'Q', L'R', L'S', L'T', L'U', L'V', L'W', L'X',
  L'Y', L'Z',

  L'{', L'|', L'}', L'~', 0x7F,

  // C1 Controls
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
  0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99,

  0x8A, 0x9B, 0x8C, 0x9D, 0x9E, 0x9F,

  // Latin-1 Supplement
  0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
  0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
  0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
  0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,

  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
  0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
  0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,

  0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
  0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,

  0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,

  0xF7,

  0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE,

  0x9F
};

BOOL __cdecl Unicode_compare(struct Unicode lhs, struct Unicode rhs) {
  return Unicode_toUpper(lhs).ch == Unicode_toUpper(rhs).ch;
}

enum Unicode_Direction Unicode_directionality(struct Unicode self) {
  /*
   * Hebrew, Arabic, Syriac, Arabic Supplement, Thaana, NKo,
   * Samaritan, Mandaic, Syriac Supplement, Arabic Extended-A
   */
  if (self.ch >= 0x590 && self.ch <= 0x8FF) {
    return DIR_RIGHT_TO_LEFT;
  }

  /* Lower case a to z */
  if (self.ch >= L'a' && self.ch <= L'z') {
    return DIR_LEFT_TO_RIGHT;
  }

  /* @ character, upper case A to Z */
  if (self.ch >= L'@' && self.ch <= L'Z') {
    return DIR_LEFT_TO_RIGHT;
  }

  /* Numbers 0 to 9 */
  if (self.ch >= L'0' && self.ch <= L'9') {
    return DIR_LEFT_TO_RIGHT;
  }

  /*
   * The characters \0 to [SPACE] and the following:
   * !"#$%'()*+,-./:;<=>?
   *
   * & character is a left-to-right case
   */
  if (self.ch <= L'\?') {
    return (self.ch == L'&')
        ? DIR_LEFT_TO_RIGHT
        : DIR_NEUTRAL;
  }

  /*
   * Hiragana, Katakana, Bopomofo, Hangul Compatibility Jamo, Kanbun,
   * Bopomofo Extended, CJK Strokes, Katakana Phonetic Extensions,
   * Enclosed CJK Letters and Months, CJK Compatibility,
   * CJK Unified Ideographs Extension A, Yijing Hexagram Symbols,
   * CJK Unified Ideographs (up to 0x8BFF)
   */
  if (self.ch >= 0x3040 && self.ch <= 0x8BFF) {
    return DIR_LEFT_TO_RIGHT;
  }

  /*
   * Latin-1 Supplement (from 0xBF), Latin Extended-A,
   * Latin Extended-B, IPA Extensions, Spacing Modifier Letters,
   * Combining Diacritical Marks, Greek and Coptic, Cyrillic,
   * Cyrillic Supplement, Armenian
   *
   * Excludes 0xD7 (multiplication sign) and 0xF7 (division sign)
   */
  if (self.ch >= 0xC0 && self.ch <= 0x58F
      && self.ch != 0xD7 && self.ch != 0xF7) {
    return DIR_LEFT_TO_RIGHT;
  }

  /*
   * Devanagari, Bengali, Gurmukhi, Gujarati, Oriya, Tamil, Telugu,
   * Kannada, Malayalam, Sinhala, Thai, Lao, Tibetan, Tibetan,
   * Georgian
   */
  if (self.ch >= 0x900 && self.ch <= 0x10FF) {
    return DIR_LEFT_TO_RIGHT;
  }

  /*
   * General Punctuation, Superscripts and Subscripts,
   * Currency Symbols, Combining Diacritical Marks for Symbols,
   * Letterlike Symbols, Number Forms, Arrows
   *
   * Bitwise form of: `self.ch >= 0x2000 && self.ch <= 0x21FF`
   */
  if ((self.ch & 0xFE00) == 0x2000) {
    /* Number Forms (Roman Numerals only) */
    if (self.ch >= 0x2160 && self.ch <= 0x2182) {
      return DIR_LEFT_TO_RIGHT;
    }

    /* Combining Diacritical Marks for Symbols */
    if (self.ch >= 0x20D0 && self.ch <= 0x20FF) {
      return DIR_LEFT_TO_RIGHT;
    }

    /* Left-to-Right Mark */
    if (self.ch == 0x200E) {
      return DIR_LEFT_TO_RIGHT;
    }

    /* Right-to-Left Mark */
    if (self.ch == 0x200F) {
      return DIR_RIGHT_TO_LEFT;
    }
  }

  return DIR_NEUTRAL;
}

BOOL Unicode_isASCII(struct Unicode self) {
  return self.ch < 0x80;
}

BOOL Unicode_isAlpha(struct Unicode self) {
  return (Unicode_isASCII(self) && isalpha((char)self.ch));
}

BOOL __cdecl Unicode_isLineBreak(const struct Unicode* str, size_t count)
{
    if (!count)
    {
        return TRUE;
    }

    enum D2C_Language nLocale = STRTABLE_GetLanguage();
    if (nLocale == LANGUAGE_JAPANESE || nLocale > LANGUAGE_KOREAN && nLocale <= LANGUAGE_CHINESETWN)
    {
        const wchar_t nWChar = str[count].ch;
        if (nWChar == 8230
            || nWChar == 12289
            || nWChar == 12290
            || nWChar == 0xFF01
            || nWChar == 0xFF0C
            || nWChar == 0xFF0E
            || nWChar == 0xFF1F
            || nWChar == 0xFF61
            || nWChar == 0xFF64
            || nWChar >= 0x61u && nWChar <= 0x7Au
            || nWChar >= 0xFF41u && nWChar <= 0xFF5Au
            || nWChar >= 0x41u && nWChar <= 0x5Au
            || nWChar >= 0xFF21u && nWChar <= 0xFF3Au
            || nWChar >= 0x30u && nWChar <= 0x39u
            || nWChar >= 0xFF10u && nWChar <= 0xFF19u)
        {
            return FALSE;
        }
    }
    else if (str[count].ch < 256u && isspace(str[count].ch) || str[count - 1].ch >= 256u || !isspace(str[count - 1].ch))
    {
        return FALSE;
    }
    return TRUE;
}

BOOL Unicode_isNewline(struct Unicode self) {
  return self.ch == L'\n';
}

BOOL Unicode_isPipe(struct Unicode self) {
  if (self.ch < 0x100) {
    return self.ch == 0xFF;
  }

  return FALSE;
}

BOOL Unicode_isWhitespace(struct Unicode self) {
  if (self.ch < 0x100) {
    return isspace(self.ch);
  }

  return FALSE;
}

struct Unicode Unicode_toLower(struct Unicode self) {
  if (self.ch > 0xFF) {
    return self;
  }

  // Vanilla bug: Returns uppercase for characters in the
  // "Latin-1 Supplement" block.
  return (struct Unicode){Unicode_toLowerTable[self.ch]};
}

struct Unicode Unicode_toUpper(struct Unicode self) {
  if (self.ch > 0xFF) {
    return self;
  }

  return (struct Unicode){Unicode_toUpperTable[self.ch]};
}
