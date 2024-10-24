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

	printf("TEST 00: current = '%s\n", current->name);
	// target is found
	if (strcmp(current->name, target) == 0)
	{
		return 1;
	}

	printf("TEST 01: child = '%s\n", current->childPtr->name);
	// recursively search children
	if (findNode(current->childPtr, target))
	{
		return 1;
	}

	printf("TEST 02: sibling = '%s\n", current->siblingPtr->name);
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

	char baseName[64];

	// copy end of pathName to baseName
	strncpy(baseName, pathName + (strrchr(pathName, '/') ? (strrchr(pathName, '/') - pathName + 1) : 0), 64);
	// baseName[64] = '\0'; // Null-terminate the baseName?

	if (findNode(parentDir, baseName))
	{
		printf("ERROR: '%s' already exists\n", baseName);
		return;
	}

	struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));

	if (!newNode)
	{
		printf("ERROR: Memory allocation failed\n");
		return;
	}

	strncpy(newNode->name, baseName, 64);
	// newNode->name[64] = '\0'; // Ensure null-termination?

	newNode->fileType = 'D';
	newNode->childPtr = NULL;
	newNode->siblingPtr = NULL;
	newNode->parentPtr = parentDir;

	printf("MKDIR SUCCESS: node '%s' successfully created\n", pathName);

	return;
}
