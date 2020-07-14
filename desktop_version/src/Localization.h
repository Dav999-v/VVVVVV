#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <map>
#include <vector>
#include <string>

namespace loc
{
	struct LangMeta
	{
		bool active; // = true, language is shown in the list
		std::string code;
		std::string nativename;
		std::string credit;
		bool autowordwrap; // = true; enable automatic wordwrapping
		bool toupper; // = true; enable automatic full-caps for menu options
		bool toupper_i_dot; // = false; enable Turkish i mapping when uppercasing
		bool toupper_lower_escape_char; // = false; enable ~ to mark lowercase letters for uppercasing
	};

	extern std::string lang;
	extern LangMeta langmeta;
	extern bool test_mode;
	extern std::vector<LangMeta> languagelist;
	extern int languagelist_curlang;
	extern bool show_lang_maint_menu;

	void loadtext();
	void loadlanguagelist();
	void sync_lang_files();

	std::string gettext(const std::string& eng);
	std::string getnumber(int n);

	std::string toupper(const std::string& lower);
	std::string not_toupper(const std::string& _s);
}

#endif /* LOCALIZATION_H */
