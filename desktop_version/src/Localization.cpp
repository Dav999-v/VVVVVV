#include "Localization.h"

//#include "Graphics.h"
#include "FileSystemUtils.h"
#include <stdio.h>
#include "tinyxml2.h"

namespace loc
{
	std::string lang = "en";
	LangMeta langmeta;
	bool test_mode = false;

	// language screen list
	std::vector<LangMeta> languagelist;
	int languagelist_curlang;
	bool show_lang_maint_menu;

	std::map<std::string, std::string> translation;

	bool load_doc(std::string cat, tinyxml2::XMLDocument& doc, std::string langcode = lang)
	{
		if (!FILESYSTEM_loadTiXml2Document(("lang/" + langcode + "/" + cat + ".xml").c_str(), doc))
		{
			printf("Could not load language %s/%s.\n", langcode.c_str(), cat.c_str());
			return false;
		}
		return true;
	}

	void loadmeta(LangMeta& meta, std::string langcode = lang)
	{
		meta.code = langcode;

		tinyxml2::XMLDocument doc;
		if (!load_doc("meta", doc, langcode))
		{
			return;
		}

		tinyxml2::XMLHandle hDoc(&doc);
		tinyxml2::XMLElement* pElem;
		tinyxml2::XMLHandle hRoot(NULL);

		{
			pElem=hDoc.FirstChildElement().ToElement();
			hRoot=tinyxml2::XMLHandle(pElem);
		}

		for (pElem = hRoot.FirstChild().ToElement(); pElem; pElem=pElem->NextSiblingElement())
		{
			std::string pKey(pElem->Value());
			const char* pText = pElem->GetText();
			if (pText == NULL)
			{
				pText = "";
			}

			if (pKey == "nativename")
				meta.nativename = std::string(pText);
			else if (pKey == "credit")
				meta.credit = std::string(pText);
		}
	}

	void loadtext_strings()
	{
		tinyxml2::XMLDocument doc;
		if (!load_doc("strings", doc))
		{
			return;
		}

		tinyxml2::XMLHandle hDoc(&doc);
		tinyxml2::XMLElement* pElem;
		tinyxml2::XMLHandle hRoot(NULL);

		{
			pElem=hDoc.FirstChildElement().ToElement();
			//pElem->QueryIntAttribute("nplurals", &nplurals);
			hRoot=tinyxml2::XMLHandle(pElem);
		}

		for (pElem = hRoot.FirstChild().ToElement(); pElem; pElem=pElem->NextSiblingElement())
		{
			std::string pKey(pElem->Value());
			const char* pText = pElem->GetText();
			if (pText == NULL)
			{
				pText = "";
			}

			if (pKey == "string")
			{
				std::string eng = std::string(pElem->Attribute("english"));
				if (translation.count(eng) != 0)
				{
					printf("Warning: \"%s\" appears in language file multiple times\n", eng.c_str());
				}
				translation[eng] = std::string(pText);
			}
		}
	}

	void loadtext()
	{
		show_lang_maint_menu = FILESYSTEM_langsAreModded();

		translation.clear();

		loadmeta(langmeta);

		if (lang == "en" && !test_mode)
		{
			return;
		}

		loadtext_strings();
	}

	void loadlanguagelist()
	{
		// Load the list of languages for the language screen
		languagelist.clear();

		std::vector<std::string> codes = FILESYSTEM_getLanguageCodes();
		for (size_t i = 0; i < codes.size(); i++)
		{
			LangMeta meta;
			loadmeta(meta, codes[i]);
			languagelist.push_back(meta);

			if (lang == codes[i])
				languagelist_curlang = i;
		}
	}

	void sync_lang_file(std::string langcode)
	{
		// Update translation files for the given language with new strings from template.
		// This basically takes the template, fills in existing translations, and saves.
		printf("Syncing %s with templates...\n", langcode.c_str());

		lang = langcode;
		loadtext();

		tinyxml2::XMLDocument doc;
		if (!load_doc("strings", doc, "en"))
		{
			return;
		}

		tinyxml2::XMLHandle hDoc(&doc);
		tinyxml2::XMLElement* pElem;
		tinyxml2::XMLHandle hRoot(NULL);

		{
			pElem=hDoc.FirstChildElement().ToElement();
			hRoot=tinyxml2::XMLHandle(pElem);
		}

		for (pElem = hRoot.FirstChild().ToElement(); pElem; pElem=pElem->NextSiblingElement())
		{
			std::string pKey(pElem->Value());

			if (pKey == "string")
			{
				const char* eng = pElem->Attribute("english");
				pElem->SetText(translation[std::string(eng)].c_str());
			}
		}

		FILESYSTEM_saveTiXml2Document(("lang/" + langcode + "/strings.xml").c_str(), doc);
	}

	void sync_lang_files()
	{
		std::string oldlang = lang;

		for (size_t i = 0; i < languagelist.size(); i++)
		{
			if (languagelist[i].code != "en")
				sync_lang_file(languagelist[i].code);
		}

		lang = oldlang;
		loadtext();
	}


	std::string gettext(const std::string& eng)
	{
		if (test_mode)
		{
			if (translation.count(eng) != 0)
			{
				return "V";
			}
			else
			{
				return "X";
			}
		}

		if (lang == "en" || translation.count(eng) == 0)
		{
			return eng;
		}

		std::string& tra = translation[eng];

		if (tra.empty())
		{
			return eng;
		}

		return tra;
	}
}
