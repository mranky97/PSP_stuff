#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include "gfx.hpp"


PSP_MODULE_INFO("Tutorial", 0, 1, 0);

int exit_callback(int arg1, int arg2, void* common)
{
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void* argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}

int setupCallbacks()
{
    int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, NULL);
    if(thid >= 0)
    {
        sceKernelStartThread(thid, 0, NULL);
    }
    return thid;
}

int main()
{
    setupCallbacks();
    GFX::init();

    while(1)
    {
        GFX::clear(0xFFFFCA82);

        GFX::drawRect(10, 10, 30, 30, 0xFF00FFFF);

        GFX::swapBuffers();
        sceDisplayWaitVblankStart();
    }


    return 0;
}