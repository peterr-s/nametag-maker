#ifndef CLASS_H
#define CLASS_H

typedef struct class class;
struct class
{
	char name[4095];
	char color[15]; // no color name is more than 15 characters
};

#define COLOR_CT 68
const char* colors[] = {
	"Apricot",
	"Aquamarine",
	"Bittersweet",
	"Black",
	"Blue",
	"BlueGreen",
	"BlueViolet",
	"BrickRed",
	"Brown",
	"BurntOrange",
	"CadetBlue",
	"CarnationPink",
	"Cerulean",
	"CornflowerBlue",
	"Cyan",
	"Dandelion",
	"DarkOrchid",
	"Emerald",
	"ForestGreen",
	"Fuchsia",
	"Goldenrod",
	"Gray",
	"Green",
	"GreenYellow",
	"JungleGreen",
	"Lavender",
	"LimeGreen",
	"Magenta",
	"Mahogany",
	"Maroon",
	"Melon",
	"MidnightBlue",
	"Mulberry",
	"NavyBlue",
	"OliveGreen",
	"Orange",
	"OrangeRed",
	"Orchid",
	"Peach",
	"Periwinkle",
	"PineGreen",
	"Plum",
	"ProcessBlue",
	"Purple",
	"RawSienna",
	"Red",
	"RedOrange",
	"RedViolet",
	"Rhodamine",
	"RoyalBlue",
	"RoyalPurple",
	"RubineRed",
	"Salmon",
	"SeaGreen",
	"Sepia",
	"SkyBlue",
	"SpringGreen",
	"Tan",
	"TealBlue",
	"Thistle",
	"Turquoise",
	"Violet",
	"VioletRed",
	"White",
	"WildStrawberry",
	"Yellow",
	"YellowGreen",
	"YellowOrange"
};

#endif