/**
 * file: CharCode.cpp
 * encode: utf-8
*/


#include "CharCode.hpp"


// initialize static variables
const std::uint8_t I01::CharCode::utf8 = 0;
const std::uint8_t I01::CharCode::utf16be = 1;
const std::uint8_t I01::CharCode::utf16le = 2;


I01::CharCode::CharCode(std::uint8_t page, const void *format, ...)
{
    std::va_list args;
    va_start(args, format);
    switch(page)
    {
        case utf8:
            Initialize_utf8((const char8_t*)format, args);
            break;
        case utf16be:
            Initialize_utf16be((const char16_t*)format, args);
            break;
        case utf16le:
            Initialize_utf16le((const char16_t*)format, args);
            break;
        default:
            throw std::invalid_argument("I01::CharCode::CharCode() : page error");
    }
    va_end(args);
}
I01::CharCode::~CharCode() noexcept
{
    delete heap_utf8;
    delete heap_utf16be;
    delete heap_utf16le;
}


// https://qiita.com/t-yama-3/items/07e9fbba7db73eca8c6f
void I01::CharCode::Initialize_utf8(const char8_t *format, std::va_list args)
{
    std::va_list work;
    va_copy(work, args);
    // get string size
    size_t size = 1;
    for(size_t i = 0;format[i] != 0x00;)
    {
        if(format[i] & 0x80 == 0x00)
        {
            // ascii code
            if(format[i] == 0x25)
            {
                // %%
                if(format[i+1] == 0x25)
                {
                    i += 2;
                    size += 1;
                    continue;
                }
                // %8si
                if(format[i+1] == 0x38 && format[i+2] == 0x73 && format[i+3] == 0x69)
                {
                    i += 4;
                    std::int8_t arg = va_arg(work, std::int8_t);
                    if(arg < 0) size += 1;
                    std::int8_t digit = (arg < 0) ? -100 : 100;
                    for(std::uint8_t j = 0;j < 3;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %16si
                if(format[i+1] == 0x31 && format[i+2] == 0x36 && format[i+3] == 0x73 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::int16_t arg = va_arg(work, std::int16_t);
                    if(arg < 0) size += 1;
                    std::int16_t digit = (arg < 0) ? -10000 : 10000;
                    for(std::uint8_t j = 0;j < 5;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %32si
                if(format[i+1] == 0x33 && format[i+2] == 0x32 && format[i+3] == 0x73 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::int32_t arg = va_arg(work, std::int32_t);
                    if(arg < 0) size += 1;
                    std::int32_t digit = (arg < 0) ? -1000000000 : 1000000000;
                    for(std::uint8_t j = 0;j < 10;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %64si
                if(format[i+1] == 0x36 && format[i+2] == 0x34 && format[i+3] == 0x73 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::int64_t arg = va_arg(work, std::int64_t);
                    if(arg < 0) size += 1;
                    std::int64_t digit = (arg < 0) ? -1000000000000000000 : 1000000000000000000;
                    for(std::uint8_t j = 0;j < 19;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %8ui
                if(format[i+1] == 0x38 && format[i+2] == 0x75 && format[i+3] == 0x69)
                {
                    i += 4;
                    std::uint8_t arg = va_arg(work, std::uint8_t);
                    std::uint8_t digit = 100;
                    for(std::uint8_t j = 0;j < 3;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %16ui
                if(format[i+1] == 0x31 && format[i+2] == 0x36 && format[i+3] == 0x75 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::uint16_t arg = va_arg(work, std::uint16_t);
                    std::uint16_t digit = 10000;
                    for(std::uint8_t j = 0;j < 5;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %32ui
                if(format[i+1] == 0x33 && format[i+2] == 0x32 && format[i+3] == 0x75 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::uint32_t arg = va_arg(work, std::uint32_t);
                    std::uint32_t digit = 1000000000;
                    for(std::uint8_t j = 0;j < 10;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %64ui
                if(format[i+1] == 0x36 && format[i+2] == 0x34 && format[i+3] == 0x75 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::uint64_t arg = va_arg(work, std::uint64_t);
                    std::uint64_t digit = 10000000000000000000;
                    for(std::uint8_t j = 0;j < 20;++j)
                    {
                        if(0 < arg / digit)
                        {
                            size += 1;
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Format error");
            }
            else
            {
                i += 1;
                size += 1;
                continue;
            }
        }
        if((format[i] & 0xE0 == 0xC0) && (format[i+1] & 0xC0 == 0x80))
        {
            if(format[i] & 0x1F == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            i += 2;
            size += 2;
            continue;
        }
        if((format[i] & 0xF0 == 0xE0) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80))
        {
            if(format[i] & 0x0F == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            i += 3;
            size += 3;
            continue;
        }
        if((format[i] & 0xF8 == 0xF0) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80) && (format[i+3] & 0xC0 == 0x80))
        {
            if(format[i] & 0x07 == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            i += 4;
            size += 4;
            continue;
        }
        if((format[i] & 0xFC == 0xF8) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80) && (format[i+3] & 0xC0 == 0x80) && (format[i+4] & 0xC0 == 0x80))
        {
            if(format[i] & 0x03 == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            i += 5;
            size += 5;
            continue;
        }
        if((format[i] & 0xFE == 0xFC) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80) && (format[i+3] & 0xC0 == 0x80) && (format[i+4] & 0xC0 == 0x80) && (format[i+5] & 0xC0 == 0x80))
        {
            if(format[i] & 0x01 == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            i += 6;
            size += 6;
            continue;
        }
        throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
    }
    // Assign to string
    va_copy(work, args);
    heap_utf8 = new char8_t[size];
    heap_utf8[size-1] = 0x00;
    for(size_t i = 0, j = 0;format[i] != 0x00;)
    {
        if(format[i] & 0x80 == 0x00)
        {
            // ascii code
            if(format[i] == 0x25)
            {
                // %%
                if(format[i+1] == 0x25)
                {
                    i += 2;
                    heap_utf8[j++] = 0x25;
                    continue;
                }
                // %8si
                if(format[i+1] == 0x38 && format[i+2] == 0x73 && format[i+3] == 0x69)
                {
                    i += 4;
                    std::int8_t arg = va_arg(work, std::int8_t);
                    if(arg < 0) heap_utf8[j++] = 0x2D;
                    std::int8_t digit = (arg < 0) ? -100 : 100;
                    for(std::uint8_t k = 0;k < 3;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %16si
                if(format[i+1] == 0x31 && format[i+2] == 0x36 && format[i+3] == 0x73 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::int16_t arg = va_arg(work, std::int16_t);
                    if(arg < 0) heap_utf8[j++] = 0x2D;
                    std::int16_t digit = (arg < 0) ? -10000 : 10000;
                    for(std::uint8_t k = 0;k < 5;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %32si
                if(format[i+1] == 0x33 && format[i+2] == 0x32 && format[i+3] == 0x73 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::int32_t arg = va_arg(work, std::int32_t);
                    if(arg < 0) heap_utf8[j++] = 0x2D;
                    std::int32_t digit = (arg < 0) ? -1000000000 : 1000000000;
                    for(std::uint8_t k = 0;k < 10;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %64si
                if(format[i+1] == 0x36 && format[i+2] == 0x34 && format[i+3] == 0x73 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::int64_t arg = va_arg(work, std::int64_t);
                    if(arg < 0) heap_utf8[j++] = 0x2D;
                    std::int64_t digit = (arg < 0) ? -1000000000000000000 : 1000000000000000000;
                    for(std::uint8_t k = 0;k < 19;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %8ui
                if(format[i+1] == 0x38 && format[i+2] == 0x75 && format[i+3] == 0x69)
                {
                    i += 4;
                    std::uint8_t arg = va_arg(work, std::uint8_t);
                    std::uint8_t digit = 100;
                    for(std::uint8_t k = 0;k < 3;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %16ui
                if(format[i+1] == 0x31 && format[i+2] == 0x36 && format[i+3] == 0x75 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::uint16_t arg = va_arg(work, std::uint16_t);
                    std::uint16_t digit = 10000;
                    for(std::uint8_t k = 0;k < 5;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %32ui
                if(format[i+1] == 0x33 && format[i+2] == 0x32 && format[i+3] == 0x75 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::uint32_t arg = va_arg(work, std::uint32_t);
                    std::uint32_t digit = 1000000000;
                    for(std::uint8_t k = 0;k < 10;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                // %64ui
                if(format[i+1] == 0x36 && format[i+2] == 0x34 && format[i+3] == 0x75 && format[i+4] == 0x69)
                {
                    i += 5;
                    std::uint64_t arg = va_arg(work, std::uint64_t);
                    std::uint64_t digit = 10000000000000000000;
                    for(std::uint8_t k = 0;k < 20;++k)
                    {
                        if(0 < arg / digit)
                        {
                            heap_utf8[j++] = 0x30 + char8_t(arg / digit);
                            arg -= (arg / digit) * digit;
                        }
                        digit /= 10;
                    }
                    continue;
                }
                throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Format error");
            }
            else
            {
                heap_utf8[j++] = format[i++];
                continue;
            }
        }
        if((format[i] & 0xE0 == 0xC0) && (format[i+1] & 0xC0 == 0x80))
        {
            if(format[i] & 0x1F == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            continue;
        }
        if((format[i] & 0xF0 == 0xE0) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80))
        {
            if(format[i] & 0x0F == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            continue;
        }
        if((format[i] & 0xF8 == 0xF0) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80) && (format[i+3] & 0xC0 == 0x80))
        {
            if(format[i] & 0x07 == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            continue;
        }
        if((format[i] & 0xFC == 0xF8) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80) && (format[i+3] & 0xC0 == 0x80) && (format[i+4] & 0xC0 == 0x80))
        {
            if(format[i] & 0x03 == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            continue;
        }
        if((format[i] & 0xFE == 0xFC) && (format[i+1] & 0xC0 == 0x80) && (format[i+2] & 0xC0 == 0x80) && (format[i+3] & 0xC0 == 0x80) && (format[i+4] & 0xC0 == 0x80) && (format[i+5] & 0xC0 == 0x80))
        {
            if(format[i] & 0x01 == 0x00) throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            heap_utf8[j++] = format[i++];
            continue;
        }
        throw std::invalid_argument("I01::CharCode::Initialize_utf8() : Redundant UTF-8 Encoding");
    }
    if(heap_utf8[size-1] == 0x00) throw std::logic_error("I01::CharCode::Initialize_utf8() : Algorithm(programmer) error");
}
void I01::CharCode::Initialize_utf16be(const char16_t *format, std::va_list args)
{
}
void I01::CharCode::Initialize_utf16le(const char16_t *format, std::va_list args)
{
}

