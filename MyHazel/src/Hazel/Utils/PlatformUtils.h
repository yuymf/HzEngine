#pragma once

#include <string>
#include <optional>

namespace Hazel {

	class FileDialogs
	{
	public:
		// These return empty strings if cancelled
		// std::optional = bool get_maybe_unset;
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
	};

}
