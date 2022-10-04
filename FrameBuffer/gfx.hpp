#include <cstdint>

namespace GFX{
    void init();
    void clear(uint32_t colour);
    void swapBuffers();
    void drawRect(int x, int y, int l, int b, uint32_t color);
}