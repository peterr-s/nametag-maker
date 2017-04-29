#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "class.h"
#include "person.h"
#include "arrayutils.h"

#define ERR_ARG 1
#define ERR_FILE 2

int main(int argc, char* argv[])
{
	char name_path[4095] = "",
		class_path[4095] = "";
	
	// process arguments
	/* switches:
	 * 		--help			Display help and exit
	 * 		--list-colors	List all valid colors and exit
	 *
	 * not yet implemented:
	 * -l					LaTeX output
	 * -p					PDF output
	 * -d					DOC output
	 * -s	--simple		No classes
	 * -n [path]			Use [path] as output filename
	 * -e					Live on the edge by not checking for double assignment
	 */
	for(size_t i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "--help"))
		{
			printf("Syntax: [switches] name_file class_file\n\tname_file should be a csv with the format:\n\t\tName, Class\n\tclass_file should be a csv with the format:\n\t\tClass, Color\nswitches:\n\t--help\t\tDisplay this help and exit\n\t--list-colors\tList all available colors\n\nMade by Peter Schoener.\n\"Do as thou wilt and that is the whole of the license.\"\n\t-- paraphrased from Bertram Gilfoyle\n");
			return 0;
		}
		else if(!strcmp(argv[i], "--list-colors"))
		{
			printf("Apricot\nAquamarine\nBittersweet\nBlack\nBlue\nBlueGreen\nBlueViolet\nBrickRed\nBrown\nBurntOrange\nCadetBlue\nCarnationPink\nCerulean\nCornflowerBlue\nCyan\nDandelion\nDarkOrchid\nEmerald\nForestGreen\nFuchsia\nGoldenrod\nGray\nGreen\nGreenYellow\nJungleGreen\nLavender\nLimeGreen\nMagenta\nMahogany\nMaroon\nMelon\nMidnightBlue\nMulberry\nNavyBlue\nOliveGreen\nOrange\nOrangeRed\nOrchid\nPeach\nPeriwinkle\nPineGreen\nPlum\nProcessBlue\nPurple\nRawSienna\nRed\nRedOrange\nRedViolet\nRhodamine\nRoyalBlue\nRoyalPurple\nRubineRed\nSalmon\nSeaGreen\nSepia\nSkyBlue\nSpringGreen\nTan\nTealBlue\nThistle\nTurquoise\nViolet\nVioletRed\nWhite\nWildStrawberry\nYellow\nYellowGreen\nYellowOrange\n");
			return 0;
		}
		else if(argv[i][0] == '-')
		{
			fprintf(stderr, "Error: Switch \"%s\" not recognized.\n", argv[i]);
			return ERR_ARG;
		}
		else if(!name_path[0])
			strcpy(name_path, argv[i]);
		else
		{
			strcpy(class_path, argv[i]);
			break;
		}
	}
	if(!(class_path[0] && name_path[0])) // if the first character of either is NUL it hasn't been assigned
	{
		fprintf(stderr, "Not enough arguments. Use the --help switch for more info.\n");
		return ERR_ARG;
	}
	
	// read from class file
	size_t class_ct = 0;
	class** class_list = malloc(sizeof(class*));
	FILE* class_file = fopen(class_path, "r");
	if(!class_file)
	{
		fprintf(stderr, "Error: Unable to open class file (%s).\n", class_path);
		return ERR_FILE;
	}
	while(!feof(class_file))
	{
		// get and validate line
		char t_name[4095],
			t_color[4095];
		if(fscanf(class_file, " %s , %s \n", t_name, t_color) != 2)
		{
			printf("Warning: unable to parse line; skipping.\n");
			if(ferror(class_file) || errno == EILSEQ)
			{
				printf("Error: Unable to read class file (%s).\n", class_path);
				return ERR_FILE;
			}
		}
		else
		{
			// check whether color is valid
			// skip if not
			bool color_ok = false;
			for(size_t i = 0; i < COLOR_CT; i++)
			{
				if(!strcmp(t_color, colors[i]))
				{
					color_ok = true;
					break;
				}
			}
			if(!color_ok)
			{
				printf("Note: color %s is not valid; skipping (%s).", t_color, t_name);
				continue;
			}
			
			// check whether color and class already exist
			// skip if class exists, but warn and proceed if color is in use
			bool class_exists = false;
			int color_used = false;
			for(size_t i = 0; i < class_ct; i++)
				if(!strcmp(t_name, class_list[i]->name))
					class_exists = true;
				else if(!strcmp(t_color, class_list[i]->color))
					color_used = i;
			if(class_exists)
			{
				printf("Note: class %s already exists; skipping.\n", t_color);
				continue;
			}
			else if(color_used)
				printf("Warning: color %s already in use by class\"%s\" (%s).\n", t_color, class_list[color_used]->name, t_name);
			
			// expand array
			class** temp = malloc((class_ct + 1) * sizeof(class*));
			memcpy(temp, class_list, (class_ct * sizeof(class*)));
			free(class_list);
			class_list = temp;
			
			// add new element
			class* t_element = malloc(sizeof(class));
			strcpy(t_element->name, t_name);
			strcpy(t_element->color, t_color);
			class_list[class_ct] = t_element;
			
			class_ct++;
		}
	}
	fclose(class_file);
	
	// sort class names for better lookup
	class** temp = merge_sort_class(class_list, class_ct);
	free(class_list);
	class_list = temp;
	
	// read from name file
	size_t person_ct = 0;
	person* person_list = malloc(sizeof(person));
	FILE* name_file = fopen(name_path, "r");
	if(!name_file)
	{
		fprintf(stderr, "Error: Unable to open name file (%s).\n", name_path);
		return ERR_FILE;
	}
	while(!feof(name_file))
	{
		char t_name_first[4095],
			t_name_last[4095],
			t_class[4095];
		if(fscanf(name_file, " %s , %s , %s \n", t_name_first, t_name_last, t_class) != 3)
		{
			printf("Warning: unable to parse line; skipping.\n");
			if(ferror(name_file) || errno == EILSEQ)
			{
				printf("Error: Unable to read name file (%s).\n", name_path);
				return ERR_FILE;
			}
		}
		else
		{
			// check if valid class
			// skip if not
			class* p_class = find_class(class_list, class_ct, t_class);
			if(!p_class)
			{
				printf("Warning: %s %s was assigned to an undeclared class (%s); skipping.\n", t_name_first, t_name_last, t_class);
				continue;
			}
			
			// resize array
			person* temp = malloc((person_ct + 1) * sizeof(person));
			memcpy(temp, person_list, person_ct * sizeof(person));
			free(person_list);
			person_list = temp;
			
			// add new element
			strcpy(person_list[person_ct].name_first, t_name_first);
			person_list[person_ct].cl = p_class;
		}
	}
	fclose(name_file);
	
	// create file for output
	char output_path[4095] = "tags.tex";
	FILE* output_file;
	for(unsigned int i = 1; output_file = fopen(output_path, "r"); i++)
	{
		fclose(output_file);
		sprintf(output_path, "tags-%u.tex", i);
	}
	output_file = fopen(output_path, "w");
	
	// write beginning chunk to file
	fputs("\\documentclass[17pt, oneside]{memoir}\n\\usepackage[newdimens]{labels}\n\\usepackage[usenames, dvipsnames]{color}\n\\LabelCols = 2\n\\LabelRows = 5\n\\InterLabelColumn = 0mm\n\\InterLabelRow = 0mm\n\\LeftLabelBorder = 6mm\n\\RightLabelBorder = 6mm\n\\TopLabelBorder = 7mm\n\\BottomLabelBorder = 6mm\n\\LabelGridtrue\n\\begin{document}\n", output_file);
	
	// write variable data to file
	for(size_t i = 0; i < person_ct; i++)
		fprintf(output_file, "\\addresslabel[\\fboxsep = 5mm]\n{\n\\begin{center}\n{\\LARGE %s} \\\\ [1ex]\n{\\LARGE %s} \\\\ [1ex]\n{\\LARGE %s} \\\\ [1ex]\n\\colorbox{BurntOrange}{\\hspace{3in}}\n\\end{center}\n}", person_list[i].cl->color, person_list[i].name_first, person_list[i].name_last);
	
	// write end chunk to file
	fputs("\\end{document}", output_file);
	
	// close file
	fclose(output_file);
	
	// display success
	printf("Output written to %s.\n", output_path);
	return 0;
}