The English language files are basically templates for other languages (all the translations are empty).

If there is a `lang` folder in the VVVVVV folder (next to the levels folder), files inside that folder will take priority over data.zip, just like any other custom assets.

VVVVVV will show a "Translation maintenance" menu if a `lang` folder exists in the VVVVVV folder. That menu allows syncing all translations with the template file, and getting statistics on translation progress.
To add new strings, add them to the English/template language files, and use the maintenance option to sync all languages. This will add the new strings to all translated language files.

To create a new language, simply copy the `en` folder and fill out the xml files, probably starting with meta.xml.


== strings.xml ==
This file contains general strings for the interface and some parts of the game.
The following attributes may be found:

* english: the English text that can be translated.

* explanation: an explanation about the context, location and possibly the formatting.

* max:
---> if a single number (for example 40): the hard maximum number of characters that are known to fit. Being exactly on the limit may not look good, so try to go at least a character under it if possible.
---> if X*Y (for example 38*3): the text should fit within an area of X characters wide and Y lines high. If enabled in meta.xml, the text is automatically word-wrapped to fit. If automatic word-wrapping is disabled, you need to manually insert newlines, either as &#10; or by having a literal newline. The 8x8 font is assumed in * notation. NYI: If you use a larger font than 8x8, make sure to use the language files sync option to get the notation as described below.
---> if XxY (for example 30x2): NYI. same as X*Y notation, but characters are counted in a differently sized font than 8x8, as set in meta.xml. If you set the font size in meta.xml and sync language files from the translation maintenance menu, then all limits for the 8x8 font (X*Y notation) are automatically converted to XxY notation for the correct font size.

max is not always given. Notoriously, menu option buttons are placed diagonally, thus they have maximums that are hard to look up. Even more so, making an option differ too much in length from the other options might even make it look out of place. Best thing to do there is probably just translate as usual and then test all menus. (TODO: can we make menus more dynamic? If an option runs offscreen, automatically move the whole menu left, move options closer together, etc.)

* comment: some extra comments you can fill in as a translator. NYI: Will be kept when syncing. It obviously should.