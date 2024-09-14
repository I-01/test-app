/**
 * file: CharCode.hpp
 * encode: utf-8
*/


// インクルードガード.
#ifndef I01__lib__CharCode_hpp
#define I01__lib__CharCode_hpp


// インクルード.
#include"Include.hpp"


namespace I01
{
    class CharCode
    {
        public:
            CharCode(std::uint8_t page, const void *format, ...);
            ~CharCode() noexcept;
            static const std::uint8_t utf8;
            static const std::uint8_t utf16be;
            static const std::uint8_t utf16le;
        private:
            void Initialize_utf8(const char8_t *format, std::va_list args);
            void Initialize_utf16be(const char16_t *format, std::va_list args);
            void Initialize_utf16le(const char16_t *format, std::va_list args);
            char8_t *heap_utf8 = nullptr;
            char16_t *heap_utf16be = nullptr;
            char16_t *heap_utf16le = nullptr;
    };
}


#endif

