#include "Localization.h"

//#include "Graphics.h"
#include "FileSystemUtils.h"
#include <stdio.h>
#include "tinyxml2.h"

namespace loc
{
	std::string lang = "en";
	LangMeta langmeta;

	// language screen list
	std::vector<LangMeta> languagelist;
	int languagelist_curlang;

	typedef std::pair<std::string, std::string> english_plu;

	std::map<std::string, std::string> translation;
	std::map<english_plu, std::vector<std::string> > translation_plu;

	bool load_doc(std::string cat, tinyxml2::XMLDocument& doc, std::string load_lang = lang)
	{
		if (!FILESYSTEM_loadTiXml2Document(("lang/" + load_lang + "/" + cat + ".xml").c_str(), doc))
		{
			printf("Could not load language %s/%s.\n", load_lang.c_str(), cat.c_str());
			return false;
		}
		return true;
	}

	void loadmeta(LangMeta& meta, std::string load_lang = lang)
	{
		meta.code = load_lang;

		tinyxml2::XMLDocument doc;
		if (!load_doc("meta", doc, load_lang))
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
			else if (pKey == "nplurals")
				meta.nplurals = atoi(pText);
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
				const char* eng = pElem->Attribute("english");
				translation[std::string(eng)] = std::string(pText);
			}

			if (pKey == "pluralString")
			{
				const char* eng = pElem->Attribute("english");
				const char* eng_plural = pElem->Attribute("english_plural");

				std::vector<std::string> tra = std::vector<std::string>(2);

				// TODO rule cases
			}
		}
	}

	void loadtext()
	{
		translation.clear();
		translation_plu.clear();

		if (lang == "en")
		{
			return;
		}

		loadmeta(langmeta);
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

	std::string gettext(const std::string& eng)
	{
		std::string& tra = translation[eng];

		if (tra.empty())
		{
			return eng;
		}

		return tra;
	}

	std::string ngettext(const std::string& eng_sin, const std::string& eng_plu, long n)
	{
		std::vector<std::string>& tra = translation_plu[english_plu(eng_sin, eng_plu)];

		// Insert appropriate plural formula here
		short rule = n != 1;

		return tra[rule];
	}
}
