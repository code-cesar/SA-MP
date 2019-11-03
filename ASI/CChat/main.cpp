

#include "main.h"

SAMPFramework *pSAMP;

void cmd_ccheat(char *szParams)
{

	pSAMP->getChat()->deleteUserMessages();
	pSAMP->showSampDialog(0, 230, DIALOG_STYLE_MSGBOX, "{FFFFE0}Clear User Messages", "\t{FFFFE0}Author - Cesar_Jeffwood\n\t{FFA500}vk.com/jeffwoodclan", "Закрыть", "");
}

void cmd_cchat(char *szParams)
{
	pSAMP->getChat()->clearChat();
	pSAMP->showSampDialog(0, 230, DIALOG_STYLE_MSGBOX, "{FFFFE0}Clear Messages", "\t{FFFFE0}Author - Cesar_Jeffwood\n\t{FFA500}vk.com/jeffwoodclan", "Закрыть", "");
}

void mainThread(void *pvParams)
{
	static bool inited = false;

	if (!inited)
	{
		pSAMP = new SAMPFramework(GetModuleHandle("samp.dll"));
		inited = true;
	}
	if (pSAMP)
	{
		while (!pSAMP->tryInit())
			Sleep(100);
		pSAMP->addClientCommand("jcheat", cmd_ccheat);
		pSAMP->addClientCommand("jchat", cmd_cchat);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	switch (dwReasonForCall)
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&mainThread, 0, 0, 0);
			break;
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
