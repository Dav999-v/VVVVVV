#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <vector>
#include <string>

namespace loc
{
	struct LangMeta
	{
		std::string code;
		std::string nativename;
		std::string credit;
		int nplurals;
	};

	extern std::string lang;
	extern bool test_mode;
	extern std::vector<LangMeta> languagelist;
	extern int languagelist_curlang;
	extern bool show_lang_maint_menu;

	void loadtext();
	void loadlanguagelist();
	void sync_lang_files();

	std::string gettext(const std::string& eng);
	std::string ngettext(const std::string& eng_sin, const std::string& eng_plu, long n);
}

#endif /* LOCALIZATION_H */
