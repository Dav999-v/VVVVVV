#include "Localization.h"

//#include "Graphics.h"
#include "FileSystemUtils.h"

namespace loc
{
	std::string lang = "nl"; // TODO: get language from unlock.vvv

	typedef std::pair<std::string, std::string> english_plu;

	std::map<std::string, std::string> translation;
	std::map<english_plu, std::vector<std::string> > translation_plu;

	bool load_doc(std::string cat, TiXmlDocument *doc)
	{
		if (!FILESYSTEM_loadTiXmlDocument(("lang/" + lang + "/" + cat + ".xml").c_str(), doc))
		{
			printf("Could not load language %s/%s.\n", lang.c_str(), cat.c_str());
			return false;
		}
		return true;
	}

	void loadtext_strings()
	{
		TiXmlDocument doc;
		if (!load_doc("strings", &doc))
		{
			return;
		}

		TiXmlHandle hDoc(&doc);
		TiXmlElement* pElem;
		TiXmlHandle hRoot(0);

		int nplurals = 1;
		std::string credit;

		{
			pElem=hDoc.FirstChildElement().Element();
			pElem->QueryIntAttribute("nplurals", &nplurals);
			//pElem->QueryStringAttribute("credit", &credit); TODO
			hRoot=TiXmlHandle(pElem);
		}

		for (pElem = hRoot.FirstChild().Element(); pElem; pElem=pElem->NextSiblingElement())
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

		loadtext_strings();
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
