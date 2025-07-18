#include "Functions.h"

static std::string readstring(std::uintptr_t address) {
    std::string result;
    result.reserve(204);
    for (int offset = 0; offset < 200; offset++) {
        char character = read<char>(address + offset);
        if (character == 0) break;
        result.push_back(character);
    }
    return result;
}

std::string GetName(uintptr_t addy)
{
    const auto nameptr = read<uintptr_t>(addy + offsets::Name); // Reads the Name Pointer
    if (nameptr)
    {
		return readstring(nameptr); // Reads the Name Pointer and returns it
    }
	return "Unknown"; // if the name pointer is not valid then we return unknown
}

std::string GetClassName(uintptr_t addy)
{
    uintptr_t ClassDescriptor = read<uintptr_t>(addy + offsets::ClassDescriptor); // Reads the Offsets or idk
    uintptr_t ClassDescriptorToName = read<uintptr_t>(ClassDescriptor + offsets::ClassDescriptorToName); // Reads the Offsets or idk
    
	const auto nameptr = read<uintptr_t>(ClassDescriptorToName); // reads the class desc to name
    if (nameptr)
    {
        return readstring(nameptr); // Reads the Class Descriptor to Name Pointer and returns it
	}

	return "Unknown"; // if the class descriptor to name pointer is not valid then we return unknown
}

std::vector<uintptr_t> GetChildren(uintptr_t addy)
{
    std::vector<uintptr_t> childrens; // store all the functions

    uintptr_t Children = read<uintptr_t>(addy + offsets::Children);
    uintptr_t ChildrenEnd = read<uintptr_t>(Children + offsets::ChildrenEnd);

    for (auto child = read<uintptr_t>(Children); child < ChildrenEnd; child += 0x10)
    {
        childrens.push_back(read<uintptr_t>(child));
    }

    return childrens; // returns the list of the children
}

uintptr_t FindFirstChild(uintptr_t addy, std::string name)
{
    for (auto child : GetChildren(addy)) {
        if (GetName(child) == name) {
            return child; // returns the first child that matches the name
        }
	}

	return 0x0; // if no child matches the name we return 0x0
}

uintptr_t GetBaseAddr()
{
    uintptr_t base = mem::find_image();
    return base;
}
