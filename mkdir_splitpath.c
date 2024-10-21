#include "types.h"

extern struct NODE *root;
extern struct NODE *cwd;

// helper function: navigate through tree given next dir name using current directory; 0 = successfully found dir, 1 = failure
int check_tree(struct NODE *currDir, char *targetDir)
{
	// check if the currDir is the target dir
	if (strcmp(currDir->name, targetDir) == 0)
	{
		return 0;
	}

	// else recursively check the child of the currDir and compare it to target dir
	struct NODE *child = currDir->childPtr;
	while (child != NULL)
	{
		if (check_tree(child, targetDir) == 0)
		{
			return 0;
		}
		child = child->siblingPtr;
	}

	return 1;
}

// handles tokenizing and absolute/relative pathing options
struct NODE *splitPath(char *pathName, char *baseName, char *dirName)
{
	// allocate mem for last slash?
	char *lastSlash = strchr(pathName, '/');

	if (lastSlash != NULL)
	{
		// copy everything before last slash
		int dirLen = lastSlash - pathName;
		strncpy(dirName, pathName, dirLen);
		dirName[dirLen] = '\0'; // append null terminator
		strcpy(baseName, lastSlash + 1);
	}
	else
	{
		// assume entire pathName is baseName
		strcpy(baseName, pathName);
		dirName[0] = '\0' // append null terminator
	}
	return NULL;
}

// make directory
void mkdir(char pathName[])
{
	// break up pathName into dirName (/a/b/c) and basename (d)
	int LENGTH = strlen(pathName);
	char *dirName = malloc(LENGTH * sizeof(char));
	char *baseName = malloc(64 * sizeof(char));

	splitPath(pathName, dirName, baseName);

	struct NODE *parentDir = cwd; // Start from current working directory or root

	if (pathName[0] == '/') // Absolute path starts from root
	{
		parentDir = root;
	}

	// check for if dir name is empty?

	// Navigate through directories and find parent directory node
	if (check_tree(parentDir, dirName) == 1)
	{
		printf("ERROR: Directory '%s' does not exist\n", dirName);
		free(dirName);
		free(baseName);
		return;
	}

	// check if dir already exists
	if (check_tree(parentDir, baseName) == 0)
	{
		printf("ERROR: '%c' already exists", baseName);
		free(dirName);
		free(baseName);
		return;
	}

	// Passed all tests; create a new directory node
	struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));
	if (!newNode)
	{
		printf("ERROR: Memory allocation failed\n");
		free(dirName);
		free(baseName);
		return;
	}

	// Initialize the new node
	strcpy(newNode->name, baseName);
	newNode->fileType = 'D';
	newNode->childPtr = NULL;
	newNode->siblingPtr = NULL;
	newNode->parentPtr = parentDir;

	// Add the new node to the parent's child list
	if (parentDir->childPtr == NULL)
	{
		// Parent has no children, so this becomes the first child
		parentDir->childPtr = newNode;
	}
	else
	{
		// Parent has children, so append to the sibling list
		struct NODE *sibling = parentDir->childPtr;
		while (sibling->siblingPtr != NULL)
		{
			sibling = sibling->siblingPtr; // Traverse to the last sibling
		}
		sibling->siblingPtr = newNode; // Add the new node as the last sibling
	}

	printf("Directory '%s' created successfully\n", baseName);

	free(dirName);
	free(baseName);

	return; // return success?
}
