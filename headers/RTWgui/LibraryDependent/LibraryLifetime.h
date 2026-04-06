#ifndef LIBRARY_LIFETIME_H
#define LIBRARY_LIFETIME_H

class LibraryLifetime {
public:
    LibraryLifetime();
    ~LibraryLifetime();

    static bool isInitialized() noexcept { return s_isInitialized; }
private:
    static inline bool s_isInitialized = false;
};

#endif // !LIBRARY_LIFETIME_H
