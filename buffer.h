#include <unistd.h>

#define BUFFER_SIZE 1024

struct Buffer
{
    char *buf;
    size_t size;
    size_t current_index = 0;

    Buffer() = delete;
    Buffer(size_t _size)
    {
        buf = static_cast<char *>(operator new(_size));
    }
    ~Buffer()
    {
        operator delete[](buf);
    }
    void MoveIndex(size_t shift)
    {
        current_index = (current_index + shift) % size;
    }
};