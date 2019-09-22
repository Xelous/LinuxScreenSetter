#include <iostream>
#include <cstdio>
#include <string>
#include <memory>
#include <array>

std::string exec(std::string& p_Cmd)
{
	std::array<char, 128>  buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(p_Cmd.c_str(), "r"), pclose);
	if (pipe)
	{
		while(fgets(buffer.data(), buffer.size(), pipe.get()))
		{
			result += buffer.data();
		}
	}
	return result;
}

int main(int argc, char** argv)
{
	std::string l_cmd ("gtf 1920 1080 60");
	const auto reply = exec(l_cmd);
	const auto modelinePos = reply.find_last_of('"');
	if ( modelinePos != std::string::npos )
	{
		const auto firstQ = reply.find_first_of('"');
		const auto lastQ = reply.find_last_of('"') + 1;
		std::string l_modeName = reply.substr(
			firstQ,
			lastQ - firstQ);
		std::cout << l_modeName << "\r\n";

		std::string l_piece = reply.substr(modelinePos + 1);
		std::cout << l_piece << "\r\n";

		std::string addCmd { "xrandr --newmode " };
		addCmd += l_modeName;
		addCmd += " ";
		addCmd += l_piece;

		const auto reply2 = exec(addCmd);
		std::cout << reply2 << "\r\n";

		std::string addMode { "xrandr --addmode Virtual1 " };
		addMode += l_modeName;
		const auto reply3 = exec(addMode);
		std::cout << reply3 << "\r\n";

		std::string change { "xrandr --output Virtual1 --mode " };
		change += l_modeName;
		const auto reply4 = exec(change);
		std::cout << reply4 << "\r\n";
	}
	std::cout << reply << "\r\n";
}
