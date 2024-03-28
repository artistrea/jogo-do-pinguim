#ifndef THROW_ERROR_H_
#define THROW_ERROR_H_

class ThrowError {
private:
    ThrowError() {};
public:
    static void SDL_Error();
    static void Error(const char* message);
};

#endif