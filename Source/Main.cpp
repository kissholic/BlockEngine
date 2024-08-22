/*
 * File: Main.cpp
 * Author: kissholic
 * Copyright (c) 2024 kissholic. All wrongs reserved.
 */


#include <spdlog/spdlog.h>
#include "Graphics/GraphicsContext.h"


int main(int, char**)
{
	be::GraphicsContext Context(1280, 720, "BeEngine");
	
	if (!Context.Init()) {
		spdlog::error("Failed to initialize graphics context");
		return -1;
	}

	while (!Context.ShouldExit()) {
		Context.Step(1.0 / 60.0);
	}

	return 0;
}
