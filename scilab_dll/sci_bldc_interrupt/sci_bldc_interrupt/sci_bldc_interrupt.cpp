// sci_bldc_interrupt.cpp : DLL 用にエクスポートされる関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include "sci_bldc_interrupt.h"
#include "sci_bldc.h"

#include <windows.h>
#include <stdio.h>

//tshiode
static const LPCWSTR ScilabSendEventName = TEXT("SciBLDCTimerInt");
static const LPCTSTR ScilabSharedMemoryName = TEXT("SciBLDCSharedMemory");		//!< Name of shared memory for register and main memory.
static HANDLE	EvSciSend = NULL;
static HANDLE	SciMemoryHandle = NULL;	//!< Handle shared memory for register values.
static BYTE		*pSciMemory = NULL;		//!< Pointer to the shared memory for commands.
static bool		gSciComReleaseFlag = false;
#if 0
// これは、エクスポートされた変数の例です
SCIBLDCINTERRUPT_API int nscibldcinterrupt = 0;

// これは、エクスポートされた関数の例です。
SCIBLDCINTERRUPT_API int fnscibldcinterrupt(void)
{
	return 0;
}

// これは、エクスポートされたクラスのコンストラクターです。
Cscibldcinterrupt::Cscibldcinterrupt()
{
	return;
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*Scilab共有関数類*/
void SciHandleInit(double *ret)
{
	*ret = 1;

	EvSciSend = OpenEvent(EVENT_ALL_ACCESS, FALSE, ScilabSendEventName);
	if (EvSciSend == NULL) {
		*ret = 0;
	}

	SciMemoryHandle = OpenFileMapping(FILE_MAP_WRITE, FALSE, ScilabSharedMemoryName);
	if (SciMemoryHandle == NULL) {
		*ret = 0;
	}
	pSciMemory = (BYTE*)MapViewOfFile(SciMemoryHandle, FILE_MAP_WRITE, 0, 0, 0);
	if (pSciMemory == NULL) {
		*ret = 0;
	}

	//共有レジスタアドレスを各モータへ通知
	SetBLDCMemoryAddress(pSciMemory);

	gSciComReleaseFlag = false;
	*(char*)(pSciMemory + SCI_COM_OFFSET) = 1;
	SciInitBLDCData();

	//CreateConsole();
}

void SciReqInt_BLDC(double *ret)
{
	unsigned char *debug_scicos = (unsigned char *)pSciMemory;
	unsigned char *sci_com_int = (unsigned char*)(pSciMemory + SCI_COM_OFFSET);
	
	if (gSciComReleaseFlag == false) {
		debug_scicos = (unsigned char*)pSciMemory;
		while ((*debug_scicos) == 1) {
			if (*sci_com_int == 0) {
				gSciComReleaseFlag = true;
				break;
			}
		}
		*debug_scicos = 1;
		SetEvent(EvSciSend);
		*ret = 1;
	}
	else {
		*ret = 0;
	}
}

#ifdef __cplusplus
}
#endif

void SciReleaseInt(void)
{
	unsigned char *debug_scicos = (unsigned char *)pSciMemory;
	*debug_scicos = 0;
	UnmapViewOfFile(pSciMemory);
	CloseHandle(SciMemoryHandle);
}

/* 新規にコンソールを開く */
void CreateConsole(void) {
	FILE* fp;
	bool ret;
	ret = AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout); /* 標準出力(stdout)を新しいコンソールに向ける */
	freopen_s(&fp, "CONOUT$", "w", stderr); /* 標準エラー出力(stderr)を新しいコンソールに向ける */

	printf("ret=%d\n", ret);
}