The English language files are basically templates for other languages (all the translations are empty).

If there is a `lang` folder in the VVVVVV folder (next to the levels folder), files inside that folder will take priority over data.zip, just like any other custom assets.

VVVVVV will show a "Translation maintenance" menu if a `lang` folder exists in the VVVVVV folder. That menu allows syncing all translations with the template file, and getting statistics on translation progress.
To add new strings, add them to the English/template language files, and use the maintenance option to sync all languages. This will add the new strings to all translated language files.

To create a new language, simply copy the `en` folder and fill out the xml files, probably starting with meta.xml.