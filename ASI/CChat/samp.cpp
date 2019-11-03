/*
	SA:MP ASI Framework
	Author: CentiuS
*/

#pragma once

#include "main.h"

void SAMPFramework::addMessageToChat(D3DCOLOR cColor, char *szMsg, ...)
{
	if (g_Chat == nullptr)
		return;

	void(__thiscall *AddToChatWindowBuffer) (const void *_this, int iType, char *szText, char *szPrefix, DWORD cColor, DWORD cPrefixColor) =
		(void(__thiscall *) (const void *, int, char *, char *, DWORD, DWORD)) (dwSAMPAddr + SAMP_FUNC_ADDTOCHATWND);

	if (szMsg == NULL)
		return;

	va_list ap;
	char tmp[512];
	memset(tmp, 0, 512);
	va_start(ap, szMsg);
	vsnprintf(tmp, sizeof(tmp) - 1, szMsg, ap);
	va_end(ap);

	return AddToChatWindowBuffer((void *) g_Chat, 8, tmp, NULL, cColor, 0x00);
}

void SAMPFramework::addClientCommand(char *szCmd, CMDPROC pFunc)
{
	if (g_Input == nullptr)
		return;

	void(__thiscall *AddClientCommand) (const void *_this, char *szCommand, CMDPROC pFunc) =
		(void(__thiscall *) (const void *, char *, CMDPROC)) (dwSAMPAddr + SAMP_FUNC_ADDCLIENTCMD);

	if (szCmd == NULL)
		return;

	return AddClientCommand(g_Input, szCmd, pFunc);
}
#define SAMP_COLOR_OFFSET							0x216378
D3DCOLOR SAMPFramework::samp_color_get(int id, DWORD trans)
{
	if (dwSAMPAddr == NULL)
		return NULL;

	D3DCOLOR	*color_table;
	if (id < 0 || id >= (SAMP_MAX_PLAYERS + 3))
		return D3DCOLOR_ARGB(0xFF, 0x99, 0x99, 0x99);

	switch (id)
	{
	case (SAMP_MAX_PLAYERS):
		return 0xFF888888;

	case (SAMP_MAX_PLAYERS + 1):
		return 0xFF0000AA;

	case (SAMP_MAX_PLAYERS + 2):
		return 0xFF63C0E2;
	}

	color_table = (D3DCOLOR *)((uint8_t *)dwSAMPAddr + SAMP_COLOR_OFFSET);
	return (color_table[id] >> 8) | trans;
}

void SAMPFramework::sendPacket(BitStream *bsParams)
{
	g_RakClient->Send(bsParams, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void SAMPFramework::sendRPC(int rpcId, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	g_RakClient->RPC(&rpcId, bitStream, priority, reliability, orderingChannel, shiftTimestamp);
}

void SAMPFramework::showSampDialog(int send, int dialogID, int typedialog, char *caption, char *text, char *button1, char *button2)
{
	uint32_t    samp_dll = (uint32_t)GetModuleHandle("samp.dll");
	dwSAMPAddr = (uint32_t)samp_dll;

	uint32_t func = dwSAMPAddr + SAMP_DIALOG_SHOW;
	uint32_t data = dwSAMPAddr + SAMP_DIALOG_INFO_OFFSET;

	__asm mov eax, dword ptr[data]
		__asm mov ecx, dword ptr[eax] //mov to offset
		__asm push send //0 - No send response, 1 - Send response
	__asm push button2
	__asm push button1
	__asm push text
	__asm push caption
	__asm push typedialog
	__asm push dialogID
	__asm call func
	return;
}
void stChatInfo::deleteUserMessages()
{
	for (int i = 0; i < 100; ++i) {
		while (chatEntry[i].iType == 8 && chatEntry[i].clTextColor != clInfoColor && chatEntry[i].clTextColor != clDebugColor)
			deletenoudate(i);
	}
	updateChat();
}

void stChatInfo::clearChat()
{
	memset(chatEntry, 0, 100 * sizeof(stChatEntry));
	updateChat();
}

void stChatInfo::updateChat()
{
	m_nPrevScrollBarPosition = 1;
}

void stChatInfo::deletenoudate(int id)
{
	if (id != 99)
		memcpy((void*)((int)chatEntry + sizeof(stChatEntry) * id), (void*)((int)chatEntry + sizeof(stChatEntry) * (id + 1)), (99 - id) * sizeof(stChatEntry));
	memcpy((void*)((int)chatEntry + sizeof(stChatEntry)), chatEntry, 99 * sizeof(stChatEntry));
	memset(chatEntry, 0, sizeof(stChatEntry));
}