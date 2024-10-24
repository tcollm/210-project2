#include "types.h"

extern struct NODE *root;
extern struct NODE *cwd;

// FIX?
struct NODE *splitPath(char *pathName, char *baseName, char *dirName)
{
	// // allocate mem for last slash?
	// char *lastSlash = strchr(pathName, '/');

	// if (lastSlash != NULL)
	// {
	// 	// copy everything before last slash
	// 	int dirLen = lastSlash - pathName;
	// 	strncpy(dirName, pathName, dirLen);
	// 	dirName[dirLen] = '\0'; // append null terminator
	// 	strcpy(baseName, lastSlash + 1);
	// }
	// else
	// {
	// 	// assume entire pathName is baseName
	// 	strcpy(baseName, pathName);
	// 	dirName[0] = '\0'; // append null terminator
	// }
	return NULL;
}

// helper function to check if node already exists in tree
// returns 0 if false and 1 if true
int findNode(struct NODE *current, const char *target)
{
	if (current == NULL)
	{
		return 0;
	}

	// target is found
	if (strcmp(current->name, target) == 0)
	{
		return 1;
	}

	// recursively search children
	if (findNode(current->childPtr, target))
	{
		return 1;
	}

	// recursively search siblings
	if (findNode(current->siblingPtr, target))
	{
		return 1;
	}

	// not found
	return 0;
}

void mkdir(char pathName[])
{

	struct NODE *parentDir = cwd; // Start from current working directory or root

	if (pathName[0] == '/') // Absolute path starts from root
	{
		parentDir = root;
	}

	int LENGTH = strlen(pathName);

	// for node in tree
	// check if pathName is the same as child or siblings
	if (findNode(parentDir, pathName))
	{
		printf("ERROR: '%c' already exists\n", pathName[LENGTH - 1]);
		return;
	}

	struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));

	if (!newNode)
	{
		printf("ERROR: Memory allocation failed\n");
		return;
	}

	newNode->fileType = 'D';
	newNode->childPtr = NULL;
	newNode->siblingPtr = NULL;
	newNode->parentPtr = parentDir;

	printf("MKDIR SUCCESS: node '%s' successfully created", pathName);

	return;
}
