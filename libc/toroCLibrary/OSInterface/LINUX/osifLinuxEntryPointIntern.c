/*++

    toro C Library
    https://github.com/KilianKegel/toro-C-Library#toro-c-library-formerly-known-as-torito-c-library

    Copyright (c) 2017-2025, Kilian Kegel. All rights reserved.
    SPDX-License-Identifier: GNU General Public License v3.0

Module Name:

    osifUefiLinuxEntryPointIntern.c

Abstract:

    CRT0 for Linux environment

Author:

    Kilian Kegel

--*/
#define OS_EFI
//
// stdio.h
//
#define EOF    (-1)
//
// signal.h
//
#define SIGINT  2
//
// setjmp.h
//

#include <errno.h>

#undef NULL
#include <cde.h>
#include <CdeServices.h>

#include <Library/DebugLib.h>
#include <Protocol\LoadedImage.h>
#include <Protocol\ShellParameters.h>
#include "Pi\PiStatusCode.h"
#include "Protocol\StatusCode.h"
#include <Protocol\Shell.h>

#include <Guid\Acpi.h>
#include <Protocol\AcpiSystemDescriptionTable.h>
#include <Protocol\AcpiTable.h>
#include <Guid\Acpi.h>
#include <IndustryStandard/Acpi62.h>
#include <IndustryStandard/MemoryMappedConfigurationSpaceAccessTable.h>

#include <Protocol\AcpiSystemDescriptionTable.h>

//
// setjmp.h
//
#undef setjmp
extern __declspec(dllimport) int setjmp(jmp_buf);

//
// C++/"C with classes" for the Microsoft compiler
//
    typedef int(__cdecl* _PIFV)(void);
    typedef void(__cdecl* _PVFV)(void);

    #pragma section(".CRT$XCA",read)
    #pragma section(".CRT$XCZ",read)
    #pragma section(".CRT$XIA",read)
    #pragma section(".CRT$XIZ",read)
    #pragma section(".CRT$XPA",read)
    #pragma section(".CRT$XPZ",read)
    #pragma section(".CRT$XTA",read)
    #pragma section(".CRT$XTZ",read)

    #define _CRTALLOC(x) __declspec(allocate(x))

    _CRTALLOC(".CRT$XIA") _PIFV* __xi_a;//[] = { (void*)0 }; // C initializers (first)
    _CRTALLOC(".CRT$XIZ") _PIFV* __xi_z;//[] = { (void*)0 }; // C initializers (last)
    _CRTALLOC(".CRT$XCA") _PVFV* __xc_a;//[] = { (void*)0 }; // C++ initializers (first)
    _CRTALLOC(".CRT$XCZ") _PVFV* __xc_z;//[] = { (void*)0 }; // C++ initializers (last)
    _CRTALLOC(".CRT$XPA") _PVFV* __xp_a;//[] = { (void*)0 }; // C pre-terminators (first)
    _CRTALLOC(".CRT$XPZ") _PVFV* __xp_z;//[] = { (void*)0 }; // C pre-terminators (last)
    _CRTALLOC(".CRT$XTA") _PVFV* __xt_a;//[] = { (void*)0 }; // C terminators (first)
    _CRTALLOC(".CRT$XTZ") _PVFV* __xt_z;//[] = { (void*)0 }; // C terminators (last)

    #pragma comment(linker, "/merge:.CRT=.rdata")

//
// externs
//
extern unsigned char _gCdeCfgCmdLnParmPoolMemRetain;
extern unsigned char _gCdeCfgCmdLnParmReportStatusCodeSTDOUT;
//
// CdeServices
//
extern _PUTCHAR         _CdeDbgPutChar;
extern VWXPRINTF        _cdeCoreVwxPrintf;
extern VWXSCANF         _cdeCoreVwxScanf;
extern WCSSTRTOK        _cdeCoreWcsStrTok;
extern WCSSTRPBRKSPN    _cdeWcsStrPbrkSpn;
extern void EFIAPI      DebugPrint(IN UINTN ErrorLevel, IN const char* Format, ...);
extern MEMREALLOC       _cdeCoreMemRealloc;
extern MEMSTRXCPY       _cdeMemStrxCpy;
extern MEMSTRXCMP       _cdeMemStrxCmp;
extern OSIFGETTIME      _osifLinuxGetTime;
extern OSIFGETTSCPERSEC _osifLinuxGetTscPerSec;
extern OSIFGETTSC       _osifLinuxGetTsc;
extern OSIFMEMALLOC     _osifLinuxMemAlloc;          /*pMemAlloc     */
extern OSIFMEMFREE      _osifLinuxMemFree;           /*pfREEPages    */
extern OSIFFWRITE       _osifLinuxFileWrite;         /*pFwrite       */
extern OSIFFREAD        _osifLinuxFileRead;          /*pFread        */
extern OSIFFSETPOS      _osifLinuxFileSetPos;        /*pFsetpos      */
extern OSIFFOPEN        _osifLinuxFileOpen;          /*pFopen        */
extern OSIFFCLOSE       _osifLinuxFileClose;         /*pFclose       */
extern OSIFFDELETE      _osifLinuxFileDelete;        /*pFdelete      */
extern OSIFFRENAME      _osifLinuxFileRename;        /*pFrename;.    */
extern OSIFFFINDALL     _osifLinuxFileFindAll;       /*pFfindall     */
extern OSIFFGETSTATUS   _osifLinuxFileGetStatus;     /*pFgetstatus   */
extern OSIFDIRCREATE    _osifLinuxDirectoryCreate;   /*pDirCreate    */
extern OSIFCMDEXEC      _osifLinuxCmdExec;           /*pCmdExec      */
extern OSIFGETENV       _osifLinuxGetEnv;            /*pGetEnv       */
extern OSIFGETDCWD      _osifLinuxGetDrvCwd;         /*pGetDrvCwd    current working directory*/

extern COREFILERW       _cdeCoreFread;                   /*pFReadCORE    */
extern COREFILERW       _cdeCoreFwrite;                  /*pFWriteCORE   */
extern CORESETPOS       _cdeCoreFsetpos;                 /*pFSetPosCORE  */
extern COREFFLUSH       _cdeCoreFflush;                  /*pFFlushCORE   */

// Microsoft specific C++ initialization support
typedef int(__cdecl* _PIFV)(void);
typedef void(__cdecl* _PVFV)(void);

extern _PIFV* __xi_a; // C initializers (first)
extern _PIFV* __xi_z; // C initializers (last)
extern _PVFV* __xc_a; // C++ initializers (first)
extern _PVFV* __xc_z; // C++ initializers (last)
extern _PVFV* __xp_a; // C pre-terminators (first)
extern _PVFV* __xp_z; // C pre-terminators (last)
extern _PVFV* __xt_a; // C terminators (first)
extern _PVFV* __xt_z; // C terminators (last)
extern int main(int argc, char** argv);
extern int _cdeStr2Argcv(char** argv, char* szCmdline);
extern void _cdeSigDflt(int sig);
extern struct _CDE_LCONV_LANGUAGE _cdeCLocale;
extern struct lconv _cdeLconv_C;
extern char __cdeGetCurrentPrivilegeLevel(void);
extern EFI_GUID _gCdeDxeProtocolGuid;
extern EFI_GUID _gCdeEfiShellProtocolGuid;

extern __declspec(dllimport) void* malloc(size_t size);
extern __declspec(dllimport) void free(void* ptr);
extern __declspec(dllimport) void* memset(void* s, int c, size_t n);
extern __declspec(dllimport) int memcmp(const void* pszDst, const void* pszSrc, size_t count);
extern __declspec(dllimport) size_t strlen(const char* pszBuffer);
extern __declspec(dllimport) char* strcpy(char* pszDst, const char* pszSrc);
extern __declspec(dllimport) int fclose(FILE* stream);
extern __declspec(dllimport) int fgetc(FILE* stream);
extern __declspec(dllimport) size_t fwrite(const void* ptr, size_t size, size_t nelem, FILE* stream);
extern __declspec(dllimport) int sprintf(char* pszDest, const char* pszFormat, ...);
extern __declspec(dllimport) int raise(int sig);
extern __declspec(dllimport) int strcmp(const char* pszDst, const char* pszSrc);
extern __declspec(dllimport) int fprintf(FILE* stream, const char* pszFormat, ...);
extern char _gCdeStrLibcVersion[];
extern void __cde80387FINIT(void);

#define IsEqualGUID(rguid1, rguid2) (!memcmp(rguid1, rguid2, sizeof(GUID))) //guiddef.h
static CDEFILE _iob[CDE_FILEV_MAX];                                  /* Microsoft definition. It must be buildable within the DDK*/
static void _StdOutPutChar(int c, void** ppDest) {

    //TODO
    //    _syscall(/* sys_write */ 1, (int64_t)1, (int64_t)&c, (int64_t)1, 0, 0, 0);

    //return;
    
    if (c == EOF)
        fwrite(NULL, (size_t)EOF, 0, (FILE*)CDE_STDOUT);
    else
        fwrite(&c, 1, 1, (FILE*)CDE_STDOUT);
    fwrite(NULL, (size_t)EOF, 0, (FILE*)CDE_STDOUT);
}

static int _StdInGetChar(void** ppDest) {
    return fgetc((FILE*)CDE_STDIN);
}

CDE_APP_IF gCdeAppIfLinux;

//
// CTRL-C support
//
extern void __restore_rt(void);
static volatile char fCtrl_C = 0;

static void LinuxCtrlCHandlerRoutine(int signum)
{
    fCtrl_C |= 1;
   
}

static void __CdeChkCtrlC(void) {

    if (1 == fCtrl_C) {

        fCtrl_C = 0;

        raise(SIGINT);

    }
}

CDE_APP_IF* _GetCdeAppIf(void) {
    __CdeChkCtrlC();
    return &gCdeAppIfLinux;
}

CDE_SERVICES gCdeServicesLinux = {/*CDE_PROTOCOL*/

    .wVerMajor = 0,
    .wVerMinor = 0,
    .fx64Opcode = 8 == sizeof(void*),
    .HeapStart = {(void*)-1,ENDOFMEM,1,NULL,NULL,0,0,(void*)-1},
    .TSClocksAtCdeTrace = 0,
    .TimeAtSystemStart = 0,
    .ReportStatusCode = 0,
    ////    FNDECL_MAINSTART(*pmainstart);          // the fjMainDxeEntryPoint/fjMainSmmEntryPoint loader     /* kg0705F0*/
    ////    FNDECL_SMMSTART(*psmmstart);            // wrapper for fjLoadDriverToSmm
    .pGetConIn = _StdInGetChar,
    .pPutConOut = _StdOutPutChar,
    .pPutDebug = _CdeDbgPutChar,
    .pVwxPrintf = _cdeCoreVwxPrintf,
    .pVwxScanf = _cdeCoreVwxScanf,
    .pMemRealloc = _cdeCoreMemRealloc,
    .pMemStrxCpy = _cdeMemStrxCpy,
    .pMemStrxCmp = _cdeMemStrxCmp,
    ////// ----- string processing functions
    .pWcsStrPbrkSpn = _cdeWcsStrPbrkSpn,
    .pWcsStrTok = _cdeCoreWcsStrTok,
//
// core C functions, running on driver side
//
    .pFReadCORE = _cdeCoreFread,                   /* core fread()    */
    .pFWriteCORE = _cdeCoreFwrite,                 /* core fwrite()   */
    .pFSetPosCORE = _cdeCoreFsetpos,               /* core fsetpos()  */
    .pFFlushCORE = _cdeCoreFflush,                 /* core fflush()   */

    // OSIF - operating system interface
    //
        .pGetTime = _osifLinuxGetTime,
        .pSetRtcTime = 0,
        .pGetTscPerSec = _osifLinuxGetTscPerSec,
        .pGetTsc = _osifLinuxGetTsc,
        .pMemAlloc = _osifLinuxMemAlloc,
        .pMemFree = _osifLinuxMemFree,
        .pFopen = _osifLinuxFileOpen,            /* OSIFFOPEN        *pFopen     */
        .pFclose = _osifLinuxFileClose,          /* OSIFFCLOSE       *pFclose    */
        .pFread = _osifLinuxFileRead,            /* OSIFFREAD        *pFread     */
        .pFwrite = _osifLinuxFileWrite,          /* OSIFFWRITE       *pFwrite    */
        .pFsetpos = _osifLinuxFileSetPos,        /* OSIFFSETPOS      *pFsetpos   */
        .pFdelete = _osifLinuxFileDelete,        /* OSIFFDELETE      *pFdelete   */
        .pFrename = _osifLinuxFileRename,        /* OSIFFRENAME      *pFrename   */
        //.pCmdExec = _osifLinuxCmdExec,           /* OSIFCMDEXEC      *pCmdExec   */
        .pGetEnv = _osifLinuxGetEnv,             /* OSIFGETENV       *pGetEnv    */
        //.pFfindall = _osifLinuxFileFindAll,      /* OSIFFFINDALL     *pFfindall  */
        //.pFgetstatus = _osifLinuxFileGetStatus,  /* OSIFFGETSTATUS   *pFgetstatus*/
        //.pGetDrvCwd = _osifLinuxGetDrvCwd,       /* OSIFGETDCWD      *pGetDrvCwd */
        //.pDirCreate = _osifLinuxDirectoryCreate, /* OSIFDIRCREATE    *pDirCreate */
        .pDirRemove = NULL,                          /* OSIFDIRCREATE    *pDirCreate */
    //
    // diagnostic
    //
};

CDE_APP_IF CdeAppIfLinux = {

    .nErrno = 0,
    .nEfiErrno = 0,
    
    .pCdeServices = &gCdeServicesLinux,
    {
        .CommParm.OSIf = LINUXIF,
        .CommParm.CommHandle = 0,
        .CommParm.pCommAPI = 0
    },
    .pStrtokStaticInternal = 0,
    .nNextRandStaticInternal = 0,
    .exit_buf = {0},
    .exit_status = EFI_SUCCESS,
    .rgcbAtexit = {0},
    .lTmpNamNum = 0,
    .rgfnSignal = {_cdeSigDflt,_cdeSigDflt,_cdeSigDflt,_cdeSigDflt,_cdeSigDflt,_cdeSigDflt,_cdeSigDflt,_cdeSigDflt},
    .pIob = &_iob[0],
    .cIob = CDE_FILEV_MAX,
    .bmRuntimeFlags = 0,    /* clear all runtimeflags   */
    .ActiveLocale = { "C", &_cdeLconv_C, NULL }/*&_cdeCLocale*/
};


/** __cdeGetAppIf()

Synopsis
    void* __cdeGetAppIf(void);
Description

    Function locates the "Application Interface" (r/w memory) that is exclusive for each driver
    at runtime.
    For PeiDrivers this chunk of memory is placed in a HOB, allocated at startup

    Returns

    @param[in]  void

    @retval (void*)pCdeAppIfDxe

**/
void* __cdeGetAppIf(void) {
    __CdeChkCtrlC();
    return &CdeAppIfLinux;
}
int _osifLinuxEntryPointIntern(void** rsp)
{
    int Status = 0;
    //intptr_t argc = (intptr_t) (rsp[0]);
    //char** argv = &((char*)(rsp[1]));
    //char** envp = argv;
    //while (*envp++)
    //    ;
    ////////__debugbreak();
    //if (1/*_gCdeCopyRight[0]*/)
    //{
    //    do {
    //        int i;
    //        CDEFILE* pCdeFile = (CDEFILE*)&_iob[0];
    //        //void* argvex[CDE_ARGV_MAX + 2] = { NULL,NULL };//ADD SUPPORT FOR argv[-1] argv[-2]
    //        CDE_APP_IF* pCdeAppIf = _GetCdeAppIf();

    //        pCdeAppIf->pIob = pCdeFile;

    //        //memset(pCdeFile, 0, sizeof(_iob));                        // clear entire structure

    //        /*stdin->*/ pCdeFile[0].fRsv = TRUE;								                                                                        // resered/in use
    //        /*stdin->*/ pCdeFile[0].emufp = /* -=PORTING=- */(void*)0;
    //        /*stdin->*/ pCdeFile[0].openmode = O_TEXT + O_RDONLY + O_CDENOSEEK + O_CDESTDIN /*TODO + (FILE_TYPE_DISK == GetFileType(pCdeFile[0].emufp) ? O_CDEREDIR : 0)*/;

    //        /*stdout->*/pCdeFile[1].fRsv = TRUE;								// resered/in use
    //        /*stdout->*/pCdeFile[1].emufp = /* -=PORTING=- */(void*)1;
    //        /*stdout->*/pCdeFile[1].openmode = O_TEXT + O_WRONLY + O_CDENOSEEK + O_CDESTDOUT /*TODO + (FILE_TYPE_DISK == GetFileType(pCdeFile[1].emufp) ? O_CDEREDIR : 0)*/;

    //        /*stderr->*/pCdeFile[2].fRsv = TRUE;								// resered/in use
    //        /*stderr->*/pCdeFile[2].emufp = /* -=PORTING=- */(void*)2;
    //        /*stderr->*/pCdeFile[2].openmode = O_TEXT + O_WRONLY + O_CDENOSEEK + O_CDESTDERR /*TODO + (FILE_TYPE_DISK == GetFileType(pCdeFile[2].emufp) ? O_CDEREDIR : 0)*/;

    //        ////__debugbreak();
    //        ////__debugbreak();
    //        //
    //        // clock() initialization
    //        //
    //        /* -=PORTING=- */ pCdeAppIf->pCdeServices->TSClocksPerSec = gCdeServicesLinux.pGetTscPerSec(pCdeAppIf,0);
    //        pCdeAppIf->pCdeServices->TimeAtSystemStart = gCdeServicesLinux.pGetTime(pCdeAppIf);
    //        pCdeAppIf->pCdeServices->TSClocksAtSystemStart = gCdeServicesLinux.pGetTsc(pCdeAppIf);
    //        
    //        //
    //        // redirect CTRL-C handler from OS to App
    //        //
    //        if (1)
    //        {
    //            size_t qwRet = (size_t)-1LL;
    //            /* Type of a signal handler.  */
    //            typedef void (__cdecl *_crt_signal_t) (int);
    //            struct /*kernel_*/sigact/*ion*/
    //            {
    //                _crt_signal_t handler;
    //                uint64_t flags;
    //                void (*restorer) (void);
    //                uint64_t mask;
    //            }_sigact = {
    //                .handler = LinuxCtrlCHandlerRoutine,
    //                .flags = 0x04000000,
    //                .restorer = __restore_rt,
    //                .mask = 0
    //            };
    //            qwRet = _syscall(13/*sys_rt_sigaction*/, SIGINT, (int64_t)&_sigact, (int64_t)NULL, 8, 0, 0);
    //        }

    //        //gszCdeDriverName = argvex[0 + 2];
    //        gszCdeDriverName = argv[0];

    //        ////__debugbreak();
    //        if (1)
    //        {
    //            //
    //            // initialize C/C++ runtime library
    //            //
    //                //if (_initterm_e(__xi_a, __xi_z) != 0){
    //                //    Status = EFI_LOAD_ERROR;
    //                //    break;
    //                //}
    //                //_initterm(__xc_a, __xc_z);
    //            typedef  void (*FUNCPTR)();
    //            typedef  int (*FUNCPTR2)();

    //            /* inits */
    //            char* pFctEntry = (char*)&__xc_a;
    //            char* pFctEntry2 = (char*)&__xi_a;
    //            int nRet = 0;
    //            /*
    //             * walk the table of function pointers from the bottom up, until
    //             * the end is encountered.  Do not skip the first entry.  The initial
    //             * value of pfbegin points to the first valid entry.  Do not try to
    //             * execute what pfend points to.  Only entries before pfend are valid.
    //             */

    //             /* walk through function pointer table */
    //            while ((void*)pFctEntry != (void*)&__xc_z)
    //            {
    //                FUNCPTR pFct = *((FUNCPTR*)pFctEntry);

    //                if (pFct) {
    //                    //printf("<-->%p\n", pFct);
    //                    //getchar();
    //                    //__debugbreak();
    //                    pFct();
    //                }

    //                pFctEntry = pFctEntry + sizeof(void*);
    //            }

    //            /* walk through function pointer table */
    //            while (0 == nRet && ((void*)pFctEntry2 != (void*)&__xi_z))
    //            {
    //                FUNCPTR2 pFct2 = *((FUNCPTR2*)pFctEntry2);
    //                if (pFct2) {
    //                    nRet = pFct2();
    //                }
    //                pFctEntry2 = pFctEntry2 + sizeof(void*);
    //                if (0 != nRet)
    //                    break;
    //            }
    //        }
    //        //
    //        // invoke "main()"
    //        //
    //        Status = setjmp(pCdeAppIf->exit_buf) ? pCdeAppIf->exit_status : main((int)argc, (char**)argv);

    //        //
    //        // run the "atexit" registered functions (N1124 chap. 7.20.4.2)
    //        //
    //        for (i = CDE_ATEXIT_REGISTRATION_NUM - 1; i >= 0; i--) {
    //            if (NULL != pCdeAppIf->rgcbAtexit[i]) {
    //                (*pCdeAppIf->rgcbAtexit[i])();
    //            }
    //        }

    //        //
    //        // close open files
    //        //
    //        for (i = 3/*skip stdin,stdout,stderr*/; i < CDE_FILEV_MAX; i++)
    //            fclose((FILE*)&_iob[i]);

    //        //
    //        // flush and close stdout + stderr, if redirected
    //        //
    //        fwrite(NULL, (size_t)EOF, 0, (FILE*)CDE_STDOUT);    // NULL,EOF,0,stream == flush parameter
    //        fwrite(NULL, (size_t)EOF, 0, (FILE*)CDE_STDERR);    // NULL,EOF,0,stream == flush parameter

    //        for (i = 1/*skip stdin*/; i <= 2; i++)
    //            if (O_CDEREOPEN & _iob[i].openmode)
    //                fclose((FILE*)&_iob[i]);

    //        //
    //        // free memory allocated during runtime
    //        //
    //        // automatically freed with sys_exit

    //        _syscall(60/*sys_exit*/, Status, 0, 0, 0, 0, 0);


    //    } while (0);
    //}
    return Status;

}