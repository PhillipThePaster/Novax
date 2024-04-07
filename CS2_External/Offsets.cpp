#include "Offsets.h"

DWORD64 SearchOffsets(std::string Signature, DWORD64 ModuleAddress) {
    auto TempAddressList = ProcessMgr.SearchMemory(Signature, ModuleAddress, ModuleAddress + 0x4000000);
    if (TempAddressList.empty()) return 0;
    DWORD Offsets = 0;
    if (!ProcessMgr.ReadMemory<DWORD>(TempAddressList[0] + 3, Offsets)) return 0;
    return TempAddressList[0] + Offsets + 7;
}

bool Offset::UpdateOffsets()
{
    DWORD64 ClientDLL = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("client.dll"));
    if (ClientDLL == 0)
        return false;

    DWORD64 TempAddress = 0;

    if ((TempAddress = SearchOffsets(Offset::Signatures::EntityList, ClientDLL)) == 0 ||
        (Offset::EntityList = TempAddress - ClientDLL, false) ||
        (TempAddress = SearchOffsets(Offset::Signatures::LocalPlayerController, ClientDLL)) == 0 ||
        (Offset::LocalPlayerController = TempAddress - ClientDLL, false) ||
        (TempAddress = SearchOffsets(Offset::Signatures::ViewMatrix, ClientDLL)) == 0 ||
        (Offset::Matrix = TempAddress - ClientDLL, false) ||
        (TempAddress = SearchOffsets(Offset::Signatures::GlobalVars, ClientDLL)) == 0 ||
        (Offset::GlobalVars = TempAddress - ClientDLL, false) ||
        (TempAddress = SearchOffsets(Offset::Signatures::LocalPlayerPawn, ClientDLL)) == 0)
        return false;

    Offset::LocalPlayerPawn = TempAddress + 0x138 - ClientDLL;
    return true;
}
