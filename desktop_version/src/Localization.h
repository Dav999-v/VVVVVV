#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <vector>

namespace loc
{
	extern std::string lang;

	void loadtext();

	std::string gettext(const std::string& eng);
	std::string ngettext(const std::string& eng_sin, const std::string& eng_plu, long n);
}

#endif /* LOCALIZATION_H */
