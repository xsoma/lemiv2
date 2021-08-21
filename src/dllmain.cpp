#include <Windows.h>
#include "hack_core.h"
#include "interfaces.h"
#include <future>
#include <string>
#include"command_executor.h"


bool BeforeInject(HMODULE hModule)
{
    return true;
}


void start()
{
    CHackCore::get().init();

    //std::async(std::launch::async, []() {
    //    std::string cmd;
    //    while (true)
    //    {
    //        std::cin >> cmd;
    //        CCommandExecutor::get().execute(cmd);
    //    }
    //    });
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    DisableThreadLibraryCalls(hModule);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (BeforeInject(hModule))
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, NULL, NULL, NULL);
        CHackCore::get().dll = hModule;
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

