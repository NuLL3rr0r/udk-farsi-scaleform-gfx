/*****************
* WARNING:
* I've converted this file using GNU libiconv,
* This file is UTF-8 encoded with compiler compability in mind.
* You must see Persian glyphs in it's corrected form,
* Or else your editor does not handle it correctly;
* And its better to avoid using your editor in such situations,
* Or you're makaing Persian comments unreadable.
* -- M.S. Babaei
*****************/


#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "text2flash.hpp"

using namespace UTFTools;


const wchar_t Text2Flash::persianGlyphs[] = {
    0x06F0, // ۰
    0x06F1, // ۱
    0x06F2, // ۲
    0x06F3, // ۳
    0x06F4, // ۴
    0x06F5, // ۵
    0x06F6, // ۶
    0x06F7, // ۷
    0x06F8, // ۸
    0x06F9, // ۹
    0x0622, // آ
    0x0627, // ا
    0x0628, // ب
    0x067E, // پ
    0x062A, // ت
    0x062B, // ث
    0x062C, // ج
    0x0686, // چ
    0x062D, // ح
    0x062E, // خ
    0x062F, // د
    0x0630, // ذ
    0x0631, // ر
    0x0632, // ز
    0x0698, // ژ
    0x0633, // س
    0x0634, // ش
    0x0635, // ص
    0x0636, // ض
    0x0637, // ط
    0x0638, // ظ
    0x0639, // ع
    0x063A, // غ
    0x0641, // ف
    0x0642, // ق
    0x06A9, // ک
    0x06AF, // گ
    0x0644, // ل
    0x0645, // م
    0x0646, // ن
    0x0648, // و
    0x0647, // ه
    0x06CC, // ی
    0x0621, // ء
    0x0626, // ئ
};

const wchar_t Text2Flash::persianDetached[] = {
    0x06F0, // ۰
    0x06F1, // ۱
    0x06F2, // ۲
    0x06F3, // ۳
    0x06F4, // ۴
    0x06F5, // ۵
    0x06F6, // ۶
    0x06F7, // ۷
    0x06F8, // ۸
    0x06F9, // ۹
    0xFE81, // ﺁ
    0xFE8D, // ﺍ
    0xFE8F, // ﺏ
    0xFB56, // ﭖ
    0xFE95, // ﺕ
    0xFE99, // ﺙ
    0xFE9D, // ﺝ
    0xFB7A, // ﭺ
    0xFEA1, // ﺡ
    0xFEA5, // ﺥ
    0xFEA9, // ﺩ
    0xFEAB, // ﺫ
    0xFEAD, // ﺭ
    0xFEAF, // ﺯ
    0xFB8A, // ﮊ
    0xFEB1, // ﺱ
    0xFEB5, // ﺵ
    0xFEB9, // ﺹ
    0xFEBD, // ﺽ
    0xFEC1, // ﻁ
    0xFEC5, // ﻅ
    0xFEC9, // ﻉ
    0xFECD, // ﻍ
    0xFED1, // ﻑ
    0xFED5, // ﻕ
    0xFB8E, // ﮎ
    0xFB92, // ﮒ
    0xFEDD, // ﻝ
    0xFEE1, // ﻡ
    0xFEE5, // ﻥ
    0xFEED, // ﻭ
    0xFEE9, // ﻩ
    0xFBFC, // ﯼ
    0xFE80, // ﺀ
    0xFE89, // ﺉ
};

const wchar_t Text2Flash::persianInitial[] = {
    NOT_DEFINED, // ۰
    NOT_DEFINED, // ۱
    NOT_DEFINED, // ۲
    NOT_DEFINED, // ۳
    NOT_DEFINED, // ۴
    NOT_DEFINED, // ۵
    NOT_DEFINED, // ۶
    NOT_DEFINED, // ۷
    NOT_DEFINED, // ۸
    NOT_DEFINED, // ۹
    NOT_DEFINED, // ﺁ
    NOT_DEFINED, // ﺍ
    0xFE91, // ﺑ
    0xFB58, // ﭘ
    0xFE97, // ﺗ
    0xFE9B, // ﺛ
    0xFE9F, // ﺟ
    0xFB7C, // ﭼ
    0xFEA3, // ﺣ
    0xFEA7, // ﺧ
    NOT_DEFINED, // ﺩ
    NOT_DEFINED, // ﺫ
    NOT_DEFINED, // ﺭ
    NOT_DEFINED, // ﺯ
    NOT_DEFINED, // ﮊ
    0xFEB3, // ﺳ
    0xFEB7, // ﺷ
    0xFEBB, // ﺻ
    0xFEBF, // ﺿ
    0xFEC3, // ﻃ
    0xFEC7, // ﻇ
    0xFECB, // ﻋ
    0xFECF, // ﻏ
    0xFED3, // ﻓ
    0xFED7, // ﻗ
    0xFB90, // ﮐ
    0xFB94, // ﮔ
    0xFEDF, // ﻟ
    0xFEE3, // ﻣ
    0xFEE7, // ﻧ
    NOT_DEFINED, // ﻭ
    0xFEEB, // ﻫ
    0xFBFE, // ﯾ
    0xFE80, // ﺀ
    0xFE8B, // ﺋ
};

const wchar_t Text2Flash::persianMedial[] = {
    NOT_DEFINED, // ۰
    NOT_DEFINED, // ۱
    NOT_DEFINED, // ۲
    NOT_DEFINED, // ۳
    NOT_DEFINED, // ۴
    NOT_DEFINED, // ۵
    NOT_DEFINED, // ۶
    NOT_DEFINED, // ۷
    NOT_DEFINED, // ۸
    NOT_DEFINED, // ۹
    NOT_DEFINED, // ﺁ
    NOT_DEFINED, // ﺎ
    0xFE92, // ﺒ
    0xFB59, // ﭙ
    0xFE98, // ﺘ
    0xFE9C, // ﺜ
    0xFEA0, // ﺠ
    0xFB7D, // ﭽ
    0xFEA4, // ﺤ
    0xFEA8, // ﺨ
    NOT_DEFINED, // ﺪ
    NOT_DEFINED, // ﺬ
    NOT_DEFINED, // ﺮ
    NOT_DEFINED, // ﺰ
    NOT_DEFINED, // ﮋ
    0xFEB4, // ﺴ
    0xFEB8, // ﺸ
    0xFEBC, // ﺼ
    0xFEC0, // ﻀ
    0xFEC4, // ﻄ
    0xFEC8, // ﻈ
    0xFECC, // ﻌ
    0xFED0, // ﻐ
    0xFED4, // ﻔ
    0xFED8, // ﻘ
    0xFB91, // ﮑ
    0xFB95, // ﮕ
    0xFEE0, // ﻠ
    0xFEE4, // ﻤ
    0xFEE8, // ﻨ
    NOT_DEFINED, // ﻮ
    0xFEEC, // ﻬ
    0xFBFF, // ﯿ
    0xFE80, // ﺀ
    0xFE8C, // ﺌ
};

const wchar_t Text2Flash::persianFinal[] = {
    NOT_DEFINED, // ۰
    NOT_DEFINED, // ۱
    NOT_DEFINED, // ۲
    NOT_DEFINED, // ۳
    NOT_DEFINED, // ۴
    NOT_DEFINED, // ۵
    NOT_DEFINED, // ۶
    NOT_DEFINED, // ۷
    NOT_DEFINED, // ۸
    NOT_DEFINED, // ۹
    NOT_DEFINED, // ﺁ
    0xFE8E, // ﺎ
    0xFE90, // ﺐ
    0xFB57, // ﭗ
    0xFE96, // ﺖ
    0xFE9A, // ﺚ
    0xFE9E, // ﺞ
    0xFB7B, // ﭻ
    0xFEA2, // ﺢ
    0xFEA6, // ﺦ
    0xFEAA, // ﺪ
    0xFEAC, // ﺬ
    0xFEAE, // ﺮ
    0xFEB0, // ﺰ
    0xFB8B, // ﮋ
    0xFEB2, // ﺲ
    0xFEB6, // ﺶ
    0xFEBA, // ﺺ
    0xFEBE, // ﺾ
    0xFEC2, // ﻂ
    0xFEC6, // ﻆ
    0xFECA, // ﻊ
    0xFECE, // ﻎ
    0xFED2, // ﻒ
    0xFED6, // ﻖ
    0xFB8F, // ﮏ
    0xFB93, // ﮓ
    0xFEDE, // ﻞ
    0xFEE2, // ﻢ
    0xFEE6, // ﻦ
    0xFEEE, // ﻮ
    0xFEEA, // ﻪ
    0xFBFD, // ﯽ
    0xFE80, // ﺀ
    0xFE8A, // ﺊ
};

Text2Flash::Text2Flash() {
    size_t len = GetArrLen(persianGlyphs);

    for (size_t i = 0; i < len; ++i) {
        std::vector < wchar_t > vec;
        std::vector < std::string > vecEnc;

        vec.push_back(persianDetached[i]);
        vec.push_back(persianInitial[i]);
        vec.push_back(persianMedial[i]);
        vec.push_back(persianFinal[i]);

        glyphs[persianGlyphs[i]] = vec;

        vec.clear();
    }
}

Text2Flash::~Text2Flash() {
}

template<typename T, size_t size>
const size_t Text2Flash::GetArrLen(T(&)[size]) {
    return size;
}

const std::string Text2Flash::EncodeChar(const wchar_t ch) {
    std::stringstream ss;
    ss << "&#";
    ss << (size_t)ch;
    ss << ";";

    return  ss.str();
}

const std::wstring Text2Flash::StrToWStr(const char *str) {
    std::string tempStr(str);
    return StrToWStr(tempStr);
}

const std::wstring Text2Flash::StrToWStr(const std::string& str) {
    std::wstring wStr(str.begin(), str.end());
    return wStr;
}

const std::wstring Text2Flash::GetFlashStr(const std::wstring& text, bool bEncode) {
    std::wstring str;

    size_t len = text.length();
    Glyph_t lastCharType = Glyph_None;

    for (size_t i = 0; i < len; ++i) {
        const wchar_t ch = text[i];

        if (ch == SPACE) {
            lastCharType = Glyph_None;
            str += ch;
            continue;
        }

        GlyphsMapType::const_iterator it = glyphs.find(ch);

        if (it != glyphs.end()) {
            std::vector < wchar_t > vec(it->second);

            Glyph_t type = Glyph_None;

            wchar_t pre;
            wchar_t post;

            bool isFirstChar = (i == 0);
            bool isLastChar = (i == len - 1);

            if (!isFirstChar && !isLastChar) {
                pre = text[i - 1];
                post = text[i + 1];

                bool hasPreSpace = (pre == SPACE);
                bool hasPostSpace = (post == SPACE);

                if (hasPreSpace && hasPostSpace) {
                    type = Glyph_Detached;
                }
                else if (hasPreSpace && !hasPostSpace) {
                    type = Glyph_Initial;
                }
                else if (!hasPreSpace && !hasPostSpace) {
                    type = Glyph_Medial;
                }
                else if (!hasPreSpace && hasPostSpace) {
                    type = Glyph_Final;
                }
            }
            else {
                if (isFirstChar) {
                    post = text[i] + 1;

                    if (post == SPACE)
                        type = Glyph_Detached;
                    else
                        type = Glyph_Initial;
                }

                if (isLastChar) {
                    pre = text[i] - 1;

                    if (pre == SPACE)
                        type = Glyph_Final;
                    else
                        type = Glyph_Detached;
                }
            }

            if (type != Glyph_None) {
                if (vec[type] == NOT_DEFINED) {
                    switch (type) {
                    case Glyph_Initial:
                        type = Glyph_Detached;
                        break;
                    case Glyph_Medial:
                        type = Glyph_Final;
                        break;
                    default:
                        break;
                    }
                }

                if (lastCharType == Glyph_None || lastCharType == Glyph_Detached || lastCharType == Glyph_Final) {
                    switch (type) {
                    case Glyph_Medial:
                        type = Glyph_Initial;
                        break;
                    case Glyph_Final:
                        type = Glyph_Detached;
                        break;
                    default:
                        break;
                    }
                }


                str += vec[type];
            }

            lastCharType = type;
            vec.clear();
            continue;
        }

        str += ch;
    }

    std::reverse(str.begin(), str.end());

    if (bEncode) {
        std::string temp;
        for (size_t i = 0; i < str.length(); ++i) {
            temp += EncodeChar(str[i]);
        }

        str = StrToWStr(temp);
    }

    return str;
}

