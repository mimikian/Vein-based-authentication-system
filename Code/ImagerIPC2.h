#pragma once
// Imager IPC.h
// Definitions for Imager Interprocess Communication

#ifdef __cplusplus 
extern "C"
{
#endif

#ifdef IMAGERIPC_EXPORTS
#define IMAGERIPC_API __declspec(dllexport)
#else
#define IMAGERIPC_API __declspec(dllimport)
#endif

#ifndef WINAPI
#define WINAPI __stdcall 
#endif

#ifndef HRESULT
#define HRESULT long
#endif

enum TIPCMode { ipcColors, ipcTemps, ipcADUs };
enum TFlagState {fsFlagOpen, fsFlagClose, fsFlagOpening, fsFlagClosing, fsError};
struct FrameMetadata
{
	unsigned short Size;	// size of this structure
	unsigned int Counter;	// frame counter
	unsigned int CounterHW;	// frame counter hardware
	long long Timestamp;	// time stamp in UNITS (10000000 per second)
	long long TimestampMedia;
	TFlagState FlagState;
	float TempChip;
	float TempFlag;
	float TempBox;
	WORD PIFin[2];			
	// DI = PIFin[0] & 0x8000
	// AI1 = PIFin[0] & 0x03FF
	// AI2 = PIFin[1] & 0x03FF
};

struct VideoFormat
{
	int WidthIR;
	int HeightIR;
	int FramerateIR;
	int WidthVisible;
	int HeightVisible;
	int FramerateVisible;
};

enum TRotationMode {
	rmOff,		// off
	rmCW90,		// clockwise 90 degrees
	rmACW90,	// anti-clockwise 90 degrees
	rmCW180,	// clockwise 180 degrees
	rmCWH,		// clockwise horizontal diagonal
	rmCWV,		// clockwise vertical diagonal
	rmACWH,		// anti-clockwise horizontal diagonal
	rmACWV,		// anti-clockwise vertical diagonal
	rmUser		// user defined
};
struct IRArranging
{
	TRotationMode Rotation;
	float RotationAngle;
	BOOL Zoom;
	RECT ZoomRect;
};

#define IPC_EVENT_INIT_COMPLETED	0x0001
#define IPC_EVENT_SERVER_STOPPED	0x0002
#define IPC_EVENT_CONFIG_CHANGED	0x0004
#define IPC_EVENT_FILE_CMD_READY	0x0008
#define IPC_EVENT_FRAME_INIT		0x0010
#define IPC_EVENT_VIS_FRAME_INIT	0x0020

// type definitions for function pointer
typedef HRESULT (WINAPI *fpOnServerStopped)(int reason);
typedef HRESULT (WINAPI *fpOnFrameInit)(int, int, int);
typedef HRESULT (WINAPI *fpOnNewFrame)(char*, int);
typedef HRESULT (WINAPI *fpOnNewFrameEx)(void*, FrameMetadata*);
typedef HRESULT (WINAPI *fpOnInitCompleted)(void );
typedef HRESULT (WINAPI *fpOnConfigChanged)(long reserved);
typedef HRESULT (WINAPI *fpOnFileCommandReady)(wchar_t *Path);


IMAGERIPC_API HRESULT WINAPI SetImagerIPCCount(WORD count);
IMAGERIPC_API HRESULT WINAPI InitImagerIPC(WORD index);
IMAGERIPC_API HRESULT WINAPI InitNamedImagerIPC(WORD index, wchar_t *InstanceName);
IMAGERIPC_API HRESULT WINAPI InitPollingImagerIPC(WORD index, WORD timeout, wchar_t *InstanceName, int *pWidth, int *pHeight, int *pDepth);
IMAGERIPC_API HRESULT WINAPI RunImagerIPC(WORD index);
IMAGERIPC_API HRESULT WINAPI StartImagerIPC(WORD index);
IMAGERIPC_API HRESULT WINAPI ReleaseImagerIPC(WORD index);
IMAGERIPC_API HRESULT WINAPI ImagerIPCProcessMessages(WORD index);
IMAGERIPC_API HRESULT WINAPI AcknowledgeFrame(WORD index);
IMAGERIPC_API HRESULT WINAPI GetFrameConfig(WORD index, int *pWidth, int *pHeight, int *pDepth);
IMAGERIPC_API HRESULT WINAPI GetVisibleFrameConfig(WORD index, int *pWidth, int *pHeight, int *pDepth);
IMAGERIPC_API HRESULT WINAPI GetFrame(WORD index, WORD timeout, void *pBuf, unsigned int  Size, FrameMetadata *pMetadata);
IMAGERIPC_API HRESULT WINAPI GetVisibleFrame(WORD index, WORD timeout, void *pBuf, unsigned int Size, FrameMetadata *pMetadata);
IMAGERIPC_API HRESULT WINAPI SetLogFile(wchar_t *LogFilename, int LogLevel, bool Append);
IMAGERIPC_API HRESULT WINAPI Log(WORD index, char *logstring, int LogLevel);

//--------------------------------------------------------------------------------------
// Callback procedures:
IMAGERIPC_API HRESULT WINAPI SetCallback_OnServerStopped(WORD index, fpOnServerStopped OnServerStopped);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnFrameInit(WORD index, fpOnFrameInit OnFrameInit);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnNewFrame(WORD index, fpOnNewFrame OnNewFrame);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnNewFrameEx(WORD index, fpOnNewFrameEx OnNewFrameEx);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnVisibleFrameInit(WORD index, fpOnFrameInit OnVisibleFrameInit);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnNewVisibleFrame(WORD index, fpOnNewFrame OnNewVisibleFrame);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnNewVisibleFrameEx(WORD index, fpOnNewFrameEx OnNewVisibleFrameEx);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnInitCompleted(WORD index, fpOnInitCompleted OnInitCompleted);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnConfigChanged(WORD index, fpOnConfigChanged OnConfigChanged);
IMAGERIPC_API HRESULT WINAPI SetCallback_OnFileCommandReady(WORD index, fpOnFileCommandReady OnFileCommandReady);

//--------------------------------------------------------------------------------------
// Get & Set procedures: 
IMAGERIPC_API __int64 WINAPI GetVersionApplication(WORD index);
IMAGERIPC_API __int64 WINAPI GetVersionHID_DLL(WORD index);
IMAGERIPC_API __int64 WINAPI GetVersionCD_DLL(WORD index);
IMAGERIPC_API __int64 WINAPI GetVersionIPC_DLL(WORD index);

IMAGERIPC_API float WINAPI GetTempChip(WORD index);
IMAGERIPC_API float WINAPI GetTempFlag(WORD index);
IMAGERIPC_API float WINAPI GetTempProc(WORD index); 
IMAGERIPC_API float WINAPI GetTempBox(WORD index);
IMAGERIPC_API float WINAPI GetTempHousing(WORD index);
IMAGERIPC_API float WINAPI GetTempTarget(WORD index);
IMAGERIPC_API float WINAPI GetHumidity(WORD index);
IMAGERIPC_API USHORT WINAPI GetTempRangeCount(WORD index);
IMAGERIPC_API USHORT WINAPI GetOpticsCount(WORD index);
IMAGERIPC_API USHORT WINAPI GetMeasureAreaCount(WORD index);
IMAGERIPC_API USHORT WINAPI GetVideoFormatCount(WORD index);
IMAGERIPC_API float WINAPI GetTempMinRange(WORD index, ULONG Index);
IMAGERIPC_API float WINAPI GetTempMaxRange(WORD index, ULONG Index);
IMAGERIPC_API USHORT WINAPI GetOpticsFOV(WORD index, ULONG Index);
IMAGERIPC_API float WINAPI GetTempMeasureArea(WORD index, ULONG Index);
IMAGERIPC_API HRESULT WINAPI GetLocMeasureArea(WORD index, ULONG Index, PPOINT Loc);
IMAGERIPC_API HRESULT WINAPI SetLocMeasureArea(WORD index, ULONG Index, POINT Loc);
IMAGERIPC_API USHORT WINAPI GetInitCounter(WORD index);
IMAGERIPC_API USHORT WINAPI GetIPCState(WORD index, bool reset);
IMAGERIPC_API USHORT WINAPI GetIPCMode(WORD index);
IMAGERIPC_API USHORT WINAPI SetIPCMode(WORD index, USHORT Value);
IMAGERIPC_API USHORT WINAPI GetFrameQueue(WORD index);				
IMAGERIPC_API USHORT WINAPI GetVisibleFrameQueue(WORD index);
IMAGERIPC_API HRESULT WINAPI GetVideoFormat(WORD index, ULONG Index, VideoFormat *videoFormat);
IMAGERIPC_API HRESULT WINAPI GetIRArranging(WORD index, IRArranging *irArranging); 
IMAGERIPC_API HRESULT WINAPI SetIRArranging(WORD index, IRArranging *irArranging); 
IMAGERIPC_API HRESULT WINAPI GetPathOfStoredFile(WORD index, wchar_t *path, int maxlen);

IMAGERIPC_API bool WINAPI GetFlag(WORD index);
IMAGERIPC_API bool WINAPI SetFlag(WORD index, bool Value);
IMAGERIPC_API USHORT WINAPI GetOpticsIndex(WORD index);
IMAGERIPC_API USHORT WINAPI SetOpticsIndex(WORD index, USHORT Value);
IMAGERIPC_API USHORT WINAPI GetTempRangeIndex(WORD index);
IMAGERIPC_API USHORT WINAPI SetTempRangeIndex(WORD index, USHORT Value);
IMAGERIPC_API USHORT WINAPI GetVideoFormatIndex(WORD index);
IMAGERIPC_API USHORT WINAPI SetVideoFormatIndex(WORD index, USHORT Value);
IMAGERIPC_API USHORT WINAPI GetTempRangeDecimal(WORD index, bool Effective);
IMAGERIPC_API bool   WINAPI GetMainWindowEmbedded(WORD index);
IMAGERIPC_API bool   WINAPI SetMainWindowEmbedded(WORD index, bool Value);
IMAGERIPC_API USHORT WINAPI GetMainWindowLocX(WORD index);
IMAGERIPC_API USHORT WINAPI SetMainWindowLocX(WORD index, USHORT Value);
IMAGERIPC_API USHORT WINAPI GetMainWindowLocY(WORD index);
IMAGERIPC_API USHORT WINAPI SetMainWindowLocY(WORD index, USHORT Value);
IMAGERIPC_API USHORT WINAPI GetMainWindowWidth(WORD index);
IMAGERIPC_API USHORT WINAPI SetMainWindowWidth(WORD index, USHORT Value);
IMAGERIPC_API USHORT WINAPI GetMainWindowHeight(WORD index);
IMAGERIPC_API USHORT WINAPI SetMainWindowHeight(WORD index, USHORT Value);
IMAGERIPC_API float	 WINAPI GetFixedEmissivity(WORD index);
IMAGERIPC_API float	 WINAPI SetFixedEmissivity(WORD index, float Value);
IMAGERIPC_API float	 WINAPI GetFixedTransmissivity(WORD index);
IMAGERIPC_API float	 WINAPI SetFixedTransmissivity(WORD index, float Value);
IMAGERIPC_API float	 WINAPI GetFixedTempAmbient(WORD index);
IMAGERIPC_API float	 WINAPI SetFixedTempAmbient(WORD index, float Value);
IMAGERIPC_API float	 WINAPI GetPifOut(WORD index, WORD channel, float Value);
IMAGERIPC_API float	 WINAPI SetPifOut(WORD index, WORD channel, float Value);
IMAGERIPC_API bool   WINAPI FailSafe(WORD index, bool Value);

IMAGERIPC_API UCHAR  WINAPI GetHardware_Model(WORD index); // deprecated
IMAGERIPC_API UCHAR  WINAPI GetHardware_Spec(WORD index); // deprecated
IMAGERIPC_API ULONG  WINAPI GetSerialNumber(WORD index);
IMAGERIPC_API ULONG  WINAPI GetSerialNumberULIS(WORD index);
IMAGERIPC_API ULONG  WINAPI GetAvgTimePerFrame(WORD index);
IMAGERIPC_API ULONG  WINAPI GetVisibleAvgTimePerFrame(WORD index);
IMAGERIPC_API USHORT WINAPI GetFirmware_MSP(WORD index); // deprecated
IMAGERIPC_API USHORT WINAPI GetFirmware_Cypress(WORD index); // deprecated
IMAGERIPC_API USHORT WINAPI GetHardwareRev(WORD index);
IMAGERIPC_API USHORT WINAPI GetFirmwareRev(WORD index);
IMAGERIPC_API USHORT WINAPI GetPID(WORD index);
IMAGERIPC_API USHORT WINAPI GetVID(WORD index);
IMAGERIPC_API ULONG  WINAPI GetPIFSerialNumber(WORD index);
IMAGERIPC_API USHORT WINAPI GetPIFVersion(WORD index);

//--------------------------------------------------------------------------------------
// Control commands:
IMAGERIPC_API void WINAPI ResetFlag(WORD index);
IMAGERIPC_API bool WINAPI RenewFlag(WORD index);
IMAGERIPC_API void WINAPI CloseApplication(WORD index);
IMAGERIPC_API void WINAPI ReinitDevice(WORD index);
IMAGERIPC_API void WINAPI FileSnapshot(WORD index);
IMAGERIPC_API void WINAPI FileRecord(WORD index);
IMAGERIPC_API void WINAPI FileStop(WORD index); 
IMAGERIPC_API void WINAPI FilePlay(WORD index);
IMAGERIPC_API void WINAPI FilePause(WORD index); 
IMAGERIPC_API USHORT WINAPI FileOpen(WORD index, wchar_t * FileName);
IMAGERIPC_API USHORT WINAPI LoadLayout(WORD index, wchar_t * LayoutName); 
IMAGERIPC_API USHORT WINAPI MasterInstanceName(WORD index, wchar_t * InstanceName); 

#ifdef __cplusplus 
}
#endif