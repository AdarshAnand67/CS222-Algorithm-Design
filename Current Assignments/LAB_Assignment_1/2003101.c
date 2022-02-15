//#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	/*The student struct has all the data of the students*/
	char rollNo[20];
	char emailId[35];
	char lecture[3];
	char tutorial[3];
	char practical[3];
	struct student *left;
	struct student *right;
};

// This function allocates memory for a new node using malloc, receives the starting address in variable ptr and fills in the data from buffer, to the memory pointed by ptr
struct student *createNode(struct student buffer)
{
	/*createNode function creates a new node based on the input given to it*/
	struct student *ptr = (struct student *)malloc(sizeof(struct student));

	strcpy(ptr->rollNo, buffer.rollNo);
	strcpy(ptr->emailId, buffer.emailId);
	strcpy(ptr->lecture, buffer.lecture);
	strcpy(ptr->tutorial, buffer.tutorial);
	strcpy(ptr->practical, buffer.practical);

	ptr->left = NULL;
	ptr->right = NULL;
	return ptr;
}

// This function takes the address of the root node of the BST and a roll number as input and checks whether there is a corresponding record  in the BST or not. If yes, the function return the height of the node in the BST (root has height 1, and otherwise height of a node is it's parent's height plus 1) and returns 0 otherwise. You could keep a counter and every time you take one step down over the tree, you may increment the count by 1
int searchNode(struct student *ptr, char rollNumber[20])
{
	/*
		Input :
			ptr : starting address of the root node of the BST
			rollNumber : roll number of the student whose record is to be searched
		Return :
			height(node) : height of the node in the BST if the record is found
			0 : if the record is not found
	*/

	int height = 1;				// height of the root node
	struct student *root = ptr; // root is the pointer to the root node
	if (ptr == NULL)			// if the BST is empty
		return 0;

	while (root != NULL)
	{
		if (strcmp(root->rollNo, rollNumber) == 0) // if the roll number is found
			return height;
		else if (strcmp(root->rollNo, rollNumber) < 0) // if the roll number is less than the root node
			root = root->right;						   // go to the right node
		else
			root = root->left; // go to the left node

		height++; // increment the height while going down the tree
	}
	return 0; // if the element is not found
}

// This function inserts a node with pointer root to the BST. The function checks whether a node with the same the roll number is already present in the BST (whose starting address is in *startPtr) or not. If not, the function inserts the node into the BST and returns 1 on successful insertion.  If there is already a record with the same roll number, the function returns 0. Note that if in case the node that you are inserting is the first, then you have to update the treeHead variable (a local variable in main) and that justifies the function being invoked with a reference to it (&treeHead)

int insertNode(struct student **startPtr, struct student *root)
{
	/*
		Input:
			startPtr : starting address of the root node of the BST
			root : root node of the BST
		Return:
			1 : if the node is inserted successfully(and insert the node in the BST)
			0 : if the node is already present
	*/

	if (*startPtr == NULL) // if the BST is empty
	{
		*startPtr = root;
		return 1;
	}

	struct student *startcopy = *startPtr; // startcopy is a copy of the starting address of the BST
	struct student *previous;			   // previous is a pointer to the previous node of the current node

	while (startcopy != NULL)
	{
		// iterate over the BST
		previous = startcopy; // update previous

		if (strcmp(root->rollNo, startcopy->rollNo) == 0) // if the roll number is already present
		{
			return 0; // return 0 not found
		}
		else if (strcmp(root->rollNo, startcopy->rollNo) < 0)
		{
			// if the roll number is less than the current node
			startcopy = startcopy->left;
		}
		else
		{
			// if the roll number is greater than the current node
			startcopy = startcopy->right;
		}
	}

	// on reaching the null node add the elemetn to the same
	if (strcmp(previous->rollNo, root->rollNo) < 1)
		previous->right = root;
	else
		previous->left = root;
	return 1; // if the node is inserted successfully
}

struct student *inordersuccessor(struct student *node)
{
	/*
	inorder successor is the next successive element of the node
	this function is called when the left and right node of bst is not null
	then the value can be replace with the inorder successor
	*/
	struct student *cpy = node; // cpy is a copy of the node
	while (cpy != NULL && cpy->left != NULL)
	{
		cpy = cpy->left; // go to the left node
	}
	return cpy; // return the inorder successor
}

struct student *deletion(struct student *root, char rollNumber[20])
{
	/*
		Input:
			root : root node of the BST
			rollNumber : roll number of the node to be deleted
		Return:
			root : root node of the BST after deletion
	*/

	struct student *curr = root; // curr is a pointer to the current node
	if (strcmp(rollNumber, curr->rollNo) < 0)
	{
		// if the roll number is less than the current node
		curr->left = deletion(curr->left, rollNumber);
	}
	else if (strcmp(rollNumber, curr->rollNo) > 0)
	{
		// if the roll number is greater than the current node
		curr->right = deletion(curr->right, rollNumber);
	}
	else
	{
		if (curr->left == NULL && curr->right == NULL) // if the node has no children
			return NULL;
		else if (curr->right == NULL)
		{
			struct student *root = curr->left;
			free(curr);
			return root;
		}
		else if (curr->left == NULL)
		{
			struct student *root = curr->right;
			free(curr);
			return root;
		}
		else
		{
			struct student *succesor = inordersuccessor(curr->right);

			// copy the value of the successor node to the current node
			strcpy(curr->rollNo, succesor->rollNo);
			strcpy(curr->emailId, succesor->emailId);
			strcpy(curr->lecture, succesor->lecture);
			strcpy(curr->tutorial, succesor->tutorial);
			strcpy(curr->practical, succesor->practical);
			root->right = deletion(root->right, succesor->rollNo);
		}
	}
	return curr;
}
// This function looks for a node with a specific roll number in the BST and deletes it if its present and returns 1 on successful deletion and 0 otherwise. Note that if in case the node that you are deleting is the first, then you have to update the treeHead variable (a local variable in main) and that justifies the function being invoked with a reference to it (&treeHead)
int deleteNode(struct student **ptr, char rollNumber[20])
{
	/*
		use searchnode function to check if the roll number exist eslse return 0
	*/
	if (searchNode(*ptr, rollNumber) == 0)
	{
		return 0;
	}
	else
	{
		// if exist call the deleteion function
		*ptr = deletion(*ptr, rollNumber);
		return 1;
	}
}

// This function takes the address of the root node in the BST as input and prints the roll number and email Id of each student in the BST, sorted in descending order of the roll number (use a variant of inorder traversal).To end with, the function returns the number of nodes in the BST. You may introduce your own global variable and increment it everytime a new value being printed
int displayBST(struct student *ptr)
{
	/*using inorder traversal but moving from right to root to left prints the
	values in descending order
	*/

	int count = 1;
	if (ptr == NULL)
	{
		return count - 1;
	}
	count += displayBST(ptr->right);
	printf("%s %s \n", ptr->rollNo, ptr->emailId);
	count += displayBST(ptr->left);
	return count;
}

// This function takes a value k as input and outputs the details of the k^th student in the lexicographically ordered list
void kthStudent(struct student *ptr, int *index)
{
	/*
	using inorder traversal to access the elmeents in ascending order
	on reaching the node
	print the values and print the answer
	*/
	struct student *curr = ptr;
	if (curr == NULL || *index <= 0)
	{
		return;
	}
	kthStudent(curr->left, index);
	*index = (*index) - 1;

	if (*index == 0)
	{
		printf("\n Students Details: \n");
		printf("Roll No: %s\n", curr->rollNo);
		printf("Email Id: %s\n", curr->emailId);
		printf("Tutorial: %s\n", curr->tutorial);
		printf("Lecture : %s\n", curr->lecture);
		printf("Practical : %s\n", curr->practical);
		return;
	}
	kthStudent(curr->right, index);
}

int main()
{
	FILE *fp1;
	FILE *fp2;
	int i, j;
	int val;
	int op;
	int hit;
	int status;
	struct student buffer;
	struct student *nodeCopy;
	struct student *treeHead = NULL;
	fp1 = fopen("testCaseForBST.txt", "r");
	fp2 = fopen("testResult.txt", "w");
	if (fp1 == NULL)
	{
		printf("\nFile read error\n");
		exit(0);
	}
	for (i = 0; i < 138; i++)
	{
		// printf("%d",i);
		fscanf(fp1, "%d", &op);

		if (op == 1) // corresponds to insertion
		{
			fscanf(fp1, "%s", buffer.rollNo);
			fscanf(fp1, "%s", buffer.emailId);
			fscanf(fp1, "%s", buffer.lecture);
			fscanf(fp1, "%s", buffer.tutorial);
			fscanf(fp1, "%s", buffer.practical);
			/*
			printf("%s ",buffer.rollNo);
			printf("%s ",buffer.emailId);
			printf("%s ",buffer.lecture);
			printf("%s ",buffer.tutorial);
			printf("%s\n",buffer.practical);
			*/
			nodeCopy = createNode(buffer);
			status = insertNode(&treeHead, nodeCopy);
			if (status == 0)
			{
				fprintf(fp2, "Insertion failed: Duplicate entry for %s\n", nodeCopy->rollNo);
				free(nodeCopy);
			}
			else
				fprintf(fp2, "Details for %s successfully inserted\n", nodeCopy->rollNo);
		}
		else
		{ // hit=1 --> value is present in the BST and 0 otherwise
			fscanf(fp1, "%d %s", &hit, buffer.rollNo);
			if ((op == 2) && (deleteNode(&treeHead, buffer.rollNo) != hit))
			{
				printf("%d\n", i);
				printf("%d %d", hit, deleteNode(&treeHead, buffer.rollNo));
				printf("\nThere is an error in delete function\n");
				exit(0);
			}
			else if (op == 2) // corresponds to deletion
			{
				if (hit == 0)
					fprintf(fp2, "Deletion Failed: %s not present in BST\n", buffer.rollNo);
				else
					fprintf(fp2, "Deletion successfull %s successfully removed\n", buffer.rollNo);
			}
			if (op == 3) // corresponds to search, comment this if block if you want to test your deletion alone
			{
				int index = searchNode(treeHead, buffer.rollNo);

				if (((hit == 0) && (index != 0)) || ((hit != 0) && (index == 0)))
				{
					printf("%d %d", hit, index);
					printf("\nThere is an error in search function\n");
					exit(0);
				}
				else if (hit == 0)
					fprintf(fp2, "%s not present in BST\n", buffer.rollNo);
				else
					fprintf(fp2, "%s present at location %d\n", buffer.rollNo, index);
			}
		}
	}
	int count = displayBST(treeHead);
	printf("\nTotal count=%d\n", count);

	fclose(fp1);
	fclose(fp2);
	int k;
	printf("\nEnter the value of k (less than total count):");
	scanf("%d", &k);
	if ((k > count) || (k <= 0))
	{
		printf("\nk should be between 1 and total count\n");
		return 1;
	}
	printf("\nDetails of the kth student in the (lexicographically) ordered list is:");
	kthStudent(treeHead, &k);
	return 0;
}
