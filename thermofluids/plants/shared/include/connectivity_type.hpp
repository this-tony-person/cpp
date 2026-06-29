#pragma once
#include <string>
#include <unordered_map>

struct PortInfo {
	std::string name;
	std::string port;
};

// Map: ComponentName -> (Map: PortID -> TargetInfo)
using ConnectivityMap = std::unordered_map<std::string, std::unordered_map<std::string, PortInfo>>;
