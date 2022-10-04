#include "gfx.hpp"
#include <pspge.h>
#include <pspdisplay.h>
#include <psputils.h>

namespace GFX{

    uint32_t* draw_buffer;
    uint32_t* disp_buffer;

    void init() {

        draw_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr());
        disp_buffer = static_cast<uint32_t*>(sceGeEdramGetAddr()) + (272 * 512 * sizeof(uint32_t));

        sceDisplaySetMode(0, 480, 272);
        sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);

    }

    void clear(uint32_t colour) {
        for (int i = 0; i < 512 * 272; i++)
        {
            draw_buffer[i] = colour;
        }
    }

    void swapBuffers() {
        uint32_t* temp = disp_buffer;
        disp_buffer = draw_buffer;
        draw_buffer = temp;

        sceKernelDcacheWritebackInvalidateAll();
        sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_NEXTFRAME);
    }

    void drawRect(int x, int y, int l, int b, uint32_t color) {

        if (x > 480)
        {
            x = 480;
        }
        
        if (y > 272)
        {
            y = 480;
        }

        if (x + l > 480)
        {
            l = 480 - x;
        }

        if (y + b > 272)
        {
            b = 272 - y;
        }

        int off = x + (y * 512);

        for (int i = 0; i < b; i++)
        {
            for (int j = 0; j < l; j++)
            {
                draw_buffer[j + off + i * 512] = color;
            }  
        }
    }
}