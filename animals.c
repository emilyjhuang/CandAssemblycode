#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_utils.h"

#define BOOL int
#define TRUE 1
#define FALSE 0

NODE *root = NULL;

// Returns true if user types "yes" or "y" (upper or lower case)
// and returns false if user types "no" or "n". Keeps
// prompting otherwise.

BOOL yes_response()
{

    char response[100];
      while (1)
      {
        read_line(response);

        if (strcasecmp(response, "yes") == 0 || strcasecmp(response, "y") == 0)
          return TRUE;
        else if (strcasecmp(response, "no") == 0 || strcasecmp(response, "n") == 0)
          return FALSE;
        else
          printf("Please enter 'yes/y' or 'no/n'\n");
      }
  //Hint: You might consider using the C library function strcasecmp()

}

// This procedure creates a new NODE and copies
// the contents of string s into the 
// question_or_animal field.  It also initializes
// the left and right fields to NULL.
// It should return a pointer to the new node

NODE *new_node(char *s)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
       
    if (newNode == NULL) {
        printf("Failed to allocate memory for new node");
        exit(1);
    }
    strcpy(newNode->question_or_animal, s);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
       // Allocate memory for the string and copy it
      // if (strlen(s) < sizeof(newNode->question_or_animal)) {
      //   strcpy(newNode->question_or_animal, s);
      // } else {
    // Handle the case where 's' is too long to fit into newNode->question_or_animal
       // fprintf(stderr, "String 's' is too long\n");
    // You may choose to exit or handle the error differently

      //  newNode->question_or_animal = (char *)malloc(strlen(s) + 1);

      //  if (newNode->question_or_animal == NULL) {
      //      perror("Failed to allocate memory for string in new node");
      //      free(newNode);
      //      exit(1);
      //  }

      // strcpy(newNode->question_or_animal, s);
       
       // Initialize left and right fields to NULL
      //  newNode->left = NULL;
      //  newNode->right = NULL;
       
      //  return newNode;
// This is the procedure that performs the guessing.
// If the animal is not correctly guessed, it prompts
// the user for the name of the animal and inserts a
// new node for that animal into the tree.

void guess_animal()
{
  // If the root is NULL, then there are no animals in 
  // the tree. Prompt the player for the name of an 
  // animal, create a node for that animal, and make
  // that node the root of the tree.

  if (root == NULL) {
    char animal[200];
    printf("What animal are you thinking of: ");
    read_line(animal);
    root = new_node(animal);
    return; 
  }
  // Create a new node for the new animal
  NODE *current = root;
  NODE *previous = NULL;
  BOOL leftChildTake = FALSE;

  while(current->left && current->right) {
    printf("%s\n", current->question_or_animal);
    BOOL answer = yes_response();
    previous = current;

    if(answer) {
      current = current->left;
      leftChildTake = TRUE;
      } else {
        current = current->right;
        leftChildTake = FALSE;
      }
    }

    printf("Is it %s?\n", current->question_or_animal);
    if(yes_response()) {
        printf("I guessed it right!\n");
        return;
    }

    char new_Animal[200], new_question[200], old_animal_answer[5];
    printf("What animal were you thinking of?\n");
    read_line(new_Animal);
    printf("Provide a yes or no question distinguishing %s from %s.\n", new_Animal, current->question_or_animal);
    read_line(new_question);
    printf("What would be the answer for %s? (yes or no)\n", new_Animal);
    read_line(old_animal_answer);

    NODE *old_animal_node = new_node(current->question_or_animal);
    NODE *new_animal_node = new_node(new_Animal);

    if(strcasecmp(old_animal_answer, "yes") == 0 || strcasecmp(old_animal_answer, "y") == 0) {
      current->left = new_animal_node;
      current->right = old_animal_node;
    } else {
      current->left = old_animal_node;
      current->right = new_animal_node;
    }

    strcpy(current->question_or_animal, new_question);
  
}

    /*
      Otherwise (i.e. if the root is not NULL)
      Then descend down the tree. At each node encountered:

      If the left and right fields of the node are not NULL, i.e. the node
      is an interior node and must contain a question, then:
      - print the question_or_answer field, which will be a yes/no question.
      - read the response from the user
      - If the response is yes, follow the left field to the next node. Otherwise,
        follow the right field.
    */

      

  /*
      Otherwise, if the left and right fields are NULL (i.e. the node is a leaf), 
      then the question_or_animal field contains an animal. Print the
      the question_or_animal field as the guess and prompt the user
      if the guess was correct. If the guess was correct, then 
      return. Otherwise, do the following:
           - prompt the user for the name of the new animal she was thinking of
           - prompt the user for a yes or no question distinguishing the new animal from the guessed animal
	   - ask the user what the answer for the new animal would be (yes or no)
           - create a new node with the new animal in the question_or_animal field
	   - create another new node that has the guessed animal in the question_or_animal field
           - make the two new nodes the children of the current node, where the animal for which the
             answer to the question is "yes" is the left child and the other animal is the right child.
           - overwrite the question_or_animal field of the current node with the new question.

      Note that the tree is a stricly binary tree, i.e. left and right fields of each node are either both NULL or 
      both valid pointers to child nodes (in other words, each node is a leaf or has exactly two children).
    */
    
    // prompt the user for the name of the new animal she was thinking of

//This code is complete. Just add comments where indicated.

int main()
{ int i;
  BOOL done = FALSE;

  //FILE pointer datafile set to an open file called data.dat in read mode, no editing
  FILE *datafile = fopen("data.dat", "r"); 

  //error handle case: if datafile doesn't exist then print that the file isn't found and exit program
  if (datafile == NULL) {
    printf("data.dat not found\n");
    exit(1);
  }

  //create pointer FIlE to backupfile and set it so that a file called data.data.bak is opened in write mode
  FILE *backupfile = fopen("data.dat.bak", "w");

  //reading the tree in data file and setting root to that node
  root = read_tree(datafile);

  //call write_trees() to write the initial tree to the
  //backup file (i.e. to backup the tree data)
  write_tree(root,backupfile);

  //close both files
  fclose(backupfile);
  fclose(datafile);

  printf("Welcome to the animal guessing game (like 20 questions).\n");
  do { 
    printf("\nThink of an animal...\n"); //prints statement for user to guess an animal
    guess_animal();  //call guess animal function to have computer guess animal
    printf("\nDo you want to play again? (yes/no) >");
  } while (yes_response());  //while the answer is yes (using function to get answer)


  //sets datafile to open the data.dat file for writing
  datafile = fopen("data.dat", "w");

  //uses write tree function and gives the input root node and the datafile that is passed in as pointers
  write_tree(root, datafile);

  //close the datafile
  fclose(datafile);

}

