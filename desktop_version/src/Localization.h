#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <vector>

namespace loc
{
	extern std::string lang;

	extern void loadtext();

	extern std::string gettext(const std::string& eng);
	extern std::string ngettext(const std::string& eng_sin, const std::string& eng_plu, long n);
}

#endif /* LOCALIZATION_H */
