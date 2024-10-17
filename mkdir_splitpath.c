

#include "types.h"

extern struct NODE *root;
extern struct NODE *cwd;

// make directory
void mkdir(char pathName[])
{
	// break up pathName into dirName (/a/b/c) and basename (d)
	int LENGTH = strlen(pathName);

	char *dirName = malloc(LENGTH * sizeof(char));
	char *baseName = malloc(sizeof(char));

	int i = 0;
	// NOTE: for loop instead of while loop?
	while (i != LENGTH)
	{
		dirName[i] = pathName[i]; // NOTE: may cause error - not sure if this is how to append to a char pointer
		i++;
	}
	baseName = pathName[i]; // last element in pathName

	// search for dirname node:
	//  - if absolute (/) start from root
	//  else (relative) start from CWD (curr working dir)
	//   - if dirname non-exist: ERROR message and return "FAIL"
	//   - if exist but not DIR: ERROR msg and return "FAIL"

	// search for basename (under dirname):
	//  - if already exists: ERROR msg and return "FAIL"

	//  add new dir node under dirname

	// free memory?
	return; // return success?
}

// handles tokenizing and absolute/relative pathing options
struct NODE *splitPath(char *pathName, char *baseName, char *dirName)
{
	// TO BE IMPLEMENTED
	// NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
	// rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
	// SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

	return NULL;
}
