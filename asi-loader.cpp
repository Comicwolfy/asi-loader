#include <windows.h>
#include <filesystem>
#include <vector>
#include <string>

void LoadAllAsiMods()
{
    std::string asiPath = ".\\scripts\\";  // Folder where ASI mods are stored

    for (const auto &entry : std::filesystem::directory_iterator(asiPath))
    {
        if (entry.path().extension() == ".asi")
        {
            LoadLibrary(entry.path().c_str());
        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)LoadAllAsiMods, nullptr, 0, nullptr);
    }
