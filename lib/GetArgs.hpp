/**
 * file: GetArgs.hpp
 * encode: utf-8
*/


// Windows api.
#ifdef _WIN32
    // include guard.
    #ifndef I01__lib__GetArgs_hpp
        #define I01__lib__GetArgs_hpp
        // include.
        #include"Include.hpp"
        namespace I01
        {
            class ArgGetter
            {
                public:
                    ArgGetter();
                    ~ArgGetter() noexcept;
                    int GetArgc() noexcept;
                    const wchar_t *GetArgv(int i);
                private:
                    int argc;
                    wchar_t **argv = nullptr;
            };
        }
    #endif
#endif

