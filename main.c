// Hello World for the PSP, meant for ARK-4's "Custom App" slot in the XMB.

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <string.h>

PSP_MODULE_INFO("HelloWorld", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// The debug screen font is 8 px tall with 7 px per character: 68 x 34 cells.
#define COLUMNS 68
#define ROWS 34

// HOME → "Quit" in the system menu calls this.
static int exit_callback(int arg1, int arg2, void *common) {
	sceKernelExitGame();
	return 0;
}

static int callback_thread(SceSize args, void *argp) {
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

static void setup_callbacks(void) {
	int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, NULL);
	if (thid >= 0)
		sceKernelStartThread(thid, 0, NULL);
}

static void print_centered(int row, unsigned int color, const char *text) {
	pspDebugScreenSetTextColor(color);
	pspDebugScreenSetXY((COLUMNS - (int)strlen(text)) / 2, row);
	pspDebugScreenPrintf("%s", text);
}

int main(void) {
	setup_callbacks();

	pspDebugScreenInit();
	print_centered(ROWS / 2 - 1, 0xFFFFFFFF, "Hello World");
	print_centered(ROWS - 3, 0xFF999999, "Press START to go back to the XMB");

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	SceCtrlData pad;
	do {
		sceDisplayWaitVblankStart();
		sceCtrlReadBufferPositive(&pad, 1);
	} while (!(pad.Buttons & PSP_CTRL_START));

	sceKernelExitGame();
	return 0;
}
