#pragma once
#include "pipe_params.hpp"
#include <string>
#include <map>

class PipeLoader {
public: 
	static std::map<std::string, PipeParams> load(const std::string& filepath);
};
