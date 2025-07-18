#include <iostream>
#include "Offsets.h"
#include "Functions.h"

int main()
{
    SetConsoleTitleA("Rzie UserMode");

    if (!mem::find_driver())
    {
        return 0;
    }

    std::cout << "[+] Found Driver" << std::endl;

    if (!mem::find_process(L"RobloxPlayerBeta.exe"))
    {
        std::cout << "[!] Failed to find Process" << std::endl;
        return 0;
    }

    uintptr_t baseaddr = GetBaseAddr();

    if (!baseaddr)
    {
        std::cout << "[!] Failed to find Base Address" << std::endl;
        return 0;
    }

    std::cout << "[+] Found Base Address. 0x" << std::hex << baseaddr << std::endl;

    uintptr_t FakeDataModel = read<uintptr_t>(baseaddr + offsets::FakeDataModelPointer);
    uintptr_t DataModel = read<uintptr_t>(FakeDataModel + offsets::FakeDataModelToDataModel);

    if (!DataModel)
    {
        std::cout << "[!] Failed to find Datamodel" << std::endl;
        return 0;
    }

    std::cout << "[+] Found Datamodel. 0x" << std::hex << DataModel << std::endl;

    // yeah yeah ik this shi is like the ExternalV1 but idk any other way
    uintptr_t Players = FindFirstChild(DataModel, "Players");
    if (!Players)
    {
        std::cerr << "[!] Failed to find PlayerService" << std::endl;
        return 0;
	}  

    std::cout << "[+] Found PlayerService" << std::endl;

    uintptr_t LocalPlayer = read<uintptr_t>(Players + offsets::LocalPlayer);
    if (!LocalPlayer)
    {
        std::cerr << "[!] Failed to find LocalPlayer" << std::endl;
        return 0;
	}

    std::cout << "[+] Found LocalPlayer" << std::endl;

    uintptr_t character = read<uintptr_t>(LocalPlayer + offsets::ModelInstance);

    if (!character)
    {
        std::cerr << "[!] Failed to find Character" << std::endl;
        return 0;
	}

    std::cout << "[+] Found character" << std::endl;

    uintptr_t Humanoid = FindFirstChild(character, "Humanoid");
    if (!Humanoid)
    {
        std::cerr << "[!] Failed to find Humanoid" << std::endl;
        return 0;
    }

    std::cout << "[+] Found Humanoid" << std::endl;

    uintptr_t Walkspeed = read<uintptr_t>(Humanoid + offsets::WalkSpeed);
    uintptr_t WalkspeedCheck = read<uintptr_t>(Humanoid + offsets::WalkSpeedCheck);
    uintptr_t JumpPower = read<uintptr_t>(Humanoid + offsets::JumpPower);

    std::cout << "[*] Current Walkspeed: " << Walkspeed << std::endl;
    std::cout << "[*] Current WalkspeedCheck: " << WalkspeedCheck << std::endl;
    std::cout << "[*] Current JumpPower: " << JumpPower << std::endl;

	write<float>(Humanoid + offsets::WalkSpeed, 200.0f); // Set Walkspeed to 200
    write<float>(Humanoid + offsets::WalkSpeedCheck, 200.0f); // Set WalkspeedCheck to 200 for kick preventing
    write<float>(Humanoid + offsets::JumpPower, 200.0f); // Set JumpPower to 200

    std::cout << "[+] New Walkspeed: " << read<uintptr_t>(Humanoid + offsets::WalkSpeed) << std::endl;
    
    std::cout << "[+] New WalkspeedCheck: " << read<uintptr_t>(Humanoid + offsets::WalkSpeedCheck) << std::endl;

    std::cout << "[+] New JumpPower: " << read<uintptr_t>(Humanoid + offsets::JumpPower) << std::endl;
}