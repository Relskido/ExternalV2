#pragma once
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>
#include <iostream> 
#include <vector>

#include "Driver/driver.h"
#include "Offsets.h"

std::string GetName(uintptr_t addy);
std::string GetClassName(uintptr_t addy);
std::vector<uintptr_t> GetChildren(uintptr_t addy);
uintptr_t FindFirstChild(uintptr_t addy, std::string name);
uintptr_t GetBaseAddr();