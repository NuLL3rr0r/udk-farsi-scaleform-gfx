#ifndef TEXT2FLASH_H
#define TEXT2FLASH_H


namespace std {
    typedef __SIZE_TYPE__ size_t;
    typedef basic_string<char> string;
    typedef basic_string<wchar_t> wstring;
    template <class T, class Allocator> class vector;
    template <class Key, class T, class Compare, class Allocator> class map;
}

namespace UTFTools {
    class Text2Flash;
}

class UTFTools::Text2Flash {
#define     SPACE           0x0020
#define     NOT_DEFINED     0x0000

public:
    Text2Flash();
    ~Text2Flash();

    const std::wstring GetFlashStr(const std::wstring& text, bool bEncode);

private:
    template<typename T, size_t size>
    const size_t GetArrLen(T(&)[size]);

    const std::string EncodeChar(const wchar_t ch);
    const std::wstring StrToWStr(const char *str);
    const std::wstring StrToWStr(const std::string& str);

private:
    typedef std::map < wchar_t, std::vector < wchar_t > > GlyphsMapType;

    enum Glyph_t { Glyph_None = 255,
                   Glyph_Detached = 0,
                   Glyph_Initial = 1,
                   Glyph_Medial = 2,
                   Glyph_Final = 3
               };

    static const wchar_t persianGlyphs[];
    static const wchar_t persianDetached[];
    static const wchar_t persianInitial[];
    static const wchar_t persianMedial[];
    static const wchar_t persianFinal[];

    GlyphsMapType glyphs;
};


#endif // TEXT2FLASH_H

