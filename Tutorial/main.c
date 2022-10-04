#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>


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
    pspDebugScreenInit();
    
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    struct SceCtrlData ctrlData;

    while(1)
    {
        pspDebugScreenSetXY(0, 2);
        pspDebugScreenSetTextColor(5504794);
        sceCtrlReadBufferPositive(&ctrlData, 1);

        pspDebugScreenPrintf("Analog X = %d, ", ctrlData.Lx);
        pspDebugScreenPrintf("Analog Y = %d \n", ctrlData.Ly);

        if(ctrlData.Buttons & PSP_CTRL_CROSS)
        {
            pspDebugScreenPrintf("x\n");
        }

        if(ctrlData.Buttons & PSP_CTRL_CIRCLE)
        {
            pspDebugScreenPrintf("o\n");
        }

        if(ctrlData.Buttons & PSP_CTRL_TRIANGLE)
        {
            pspDebugScreenPrintf("△\n");
        }

        if(ctrlData.Buttons & PSP_CTRL_SQUARE)
        {
            pspDebugScreenPrintf("□\n");
        }
    }


    return 0;
}