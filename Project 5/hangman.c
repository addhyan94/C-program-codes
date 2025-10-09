#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define INPUT_BUFFER_SIZE 10
#define ALPHABET_SIZE 26
#define SCREEN_CLEAR_LINES 50
#define DEFAULT_DIFFICULTY_CHOICE 2
// Difficulty settings
#define EASY_GUESSES 8
#define MEDIUM_GUESSES 6 // Default
#define HARD_GUESSES 4

char **loadWords(const char *filename, int *wordCount);
void freeWordList(char **wordList, int wordCount);
void clearScreen();
void pauseForUser();
void consumeRemainingInput();
void drawHangman(int incorrectGuesses);
/**
 * @brief Loads words from a specified file into a dynamically allocated array
 * of strings.
 *
 * Opens the file, counts the words, allocates memory for the word list (array
 * of char*) and for each individual word (char*), reads words line by line,
 * stores them, and returns the list. Also updates the word count via the output
 * parameter.
 *
 * @param filename The path to the file containing words (one word per line).
 * @param wordCount A pointer to an integer where the number of loaded words
 * will be stored. This is an output parameter.
 * @return A pointer to the dynamically allocated array of word strings
 * (char**), or NULL if an error occurs (e.g., file not found, memory allocation
 * failed). The caller is responsible for freeing the allocated memory using
 * freeWordList (which we will define later).
 */
char **loadWords(const char *filename, int *wordCount) {
  *wordCount = 0;
  FILE *file = NULL;
  file = fopen(filename, "r");
  char **wordList = NULL;
  int i = 0;
  char *currentWord = NULL;

  if (file == NULL) {

    fprintf(stderr, "Could not open the word file: %s\n", filename);
    fprintf(stderr, "Please ensure the file exists in the same directory as "
                    "the program.\n");

    return NULL;
  }

  int lineCount = 0;
  char lineBuffer[MAX_WORD_LENGTH];

  while (fgets(lineBuffer, MAX_WORD_LENGTH, file) != NULL) {
    lineCount++;
  }

  if (ferror(file)) {
    perror("Error reading file during word count");
    fprintf(stderr, "An error occurred while trying to count words in '%s'.\n",
            filename);
    fclose(file);
    return NULL;
  }

  if (lineCount == 0) {
    fprintf(stderr,
            "Warning: Word file '%s' is empty or contains no valid lines.\n",
            filename);
    fclose(file);
    // We can return NULL or an empty list. Returning NULL is simpler for now.
    // *wordCount is already 0.
    return NULL;
  }
  rewind(file);

  size_t listSize = lineCount * sizeof(char *);
  wordList = (char **)malloc(listSize);
  if (wordList == NULL) {
    perror("Memory allocation failed for word list");
    fprintf(stderr, "Error: Could not allocate memory to store %d words.\n",
            lineCount);
    fclose(file);
    return NULL;
  }
  for (int k = 0; k < lineCount; ++k) {
    wordList[k] = NULL;
  }
  i = 0;

  while (fgets(lineBuffer, MAX_WORD_LENGTH, file) != NULL) {
    if (i >= lineCount) {
      fprintf(stderr,
              "Warning: Read more lines than initially counted. Stopping at %d "
              "lines.\n",
              lineCount);
      break;
    }
    size_t len = strlen(lineBuffer);

    if (len > 0 && lineBuffer[len - 1] == '\n') {
      lineBuffer[len - 1] = '\0';
      len = strlen(lineBuffer);
    }
    if (len == 0) {
      continue;
    }

    size_t wordMemorySize = len + 1;
    currentWord = (char *)malloc(wordMemorySize);

    if (currentWord == NULL) {
      perror("Memory allocation failed for word string");
      fprintf(stderr, "Error: Could not allocate memory for word #%d ('%s').\n",
              i + 1, lineBuffer);
      fprintf(stderr, "Cleaning up allocated memory before exiting...\n");
      for (int j = 0; j < i; j++) {
        if (wordList[j] != NULL) {
          printf("DEBUG: Freeing previous word #%d at %p\n", j + 1,
                 (void *)wordList[j]);
          free(wordList[j]);
        }
      }
      free(wordList);
      fclose(file);
      return NULL;
    }

    strcpy(currentWord, lineBuffer);
    wordList[i] = currentWord;

    i++;
  }
  if (ferror(file)) {
    perror("Error reading file during second pass");
    fprintf(stderr, "An error occurred while reading words from '%s'.\n",
            filename);
    fprintf(stderr, "DEBUG: Need to implement proper cleanup for partially "
                    "loaded list on read error!\\n");
    free(wordList); // Free the array of pointers
    fclose(file);   // Close the file
    return NULL;    // Signal failure
  }
  int finalWordCount = i;

  if (fclose(file) == EOF) {
    perror("Warning: Error closing file");
  }
  *wordCount = finalWordCount;

  return wordList;
}

/**
 * @brief Frees the memory allocated for the word list.
 * Frees each individual word string, then frees the array of pointers.
 * @param wordList The list of words (array of char*).
 * @param wordCount The number of words in the list.
 */
void freeWordList(char **wordList, int wordCount) {
  if (wordList == NULL) {
    return;
  }
  for (int i = 0; i < wordCount; i++) {
    if (wordList[i] != NULL) {
      free(wordList[i]);
      wordList[i] = NULL;
    }
  }
  free(wordList);
}

void clearScreen() {
  for (int i = 0; i < SCREEN_CLEAR_LINES; i++) {
    printf("\n");
  }
}

void consumeRemainingInput() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void pauseForUser() {
  printf("\\nPress Enter to continue...");
  consumeRemainingInput();
}

void drawHangman(int incorrectGuesses) {
  printf("\n"); // Add a little space before the drawing

  // Use a switch statement based on the number of incorrect guesses
  switch (incorrectGuesses) {
  case 0: // 0 incorrect guesses - Empty Gallows
    printf("  +---+\n");
    printf("  |   |\n");
    printf("      |\n");
    printf("      |\n");
    printf("      |\n");
    printf("      |\n");
    printf("=========\n");
    break; // Don't fall through to the next case!

  case 1: // 1 incorrect guess - Head
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf("      |\n");
    printf("      |\n");
    printf("      |\n");
    printf("=========\n");
    break;

  case 2: // 2 incorrect guesses - Head and Body
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf("  |   |\n");
    printf("      |\n");
    printf("      |\n");
    printf("=========\n");
    break;

  case 3: // 3 incorrect guesses - Head, Body, and One Arm
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|   |\n"); // Forward slash is not an escape character
    printf("      |\n");
    printf("      |\n");
    printf("=========\n");
    break;

  case 4: // 4 incorrect guesses - Head, Body, and Both Arms
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    printf("      |\n");
    printf("      |\n");
    printf("=========\n");
    break;

  case 5: // 5 incorrect guesses - Head, Body, Arms, and One Leg
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    printf(" /    |\n");
    printf("      |\n");
    printf("=========\n");
    break;

  case 6: // 6 incorrect guesses - Full Hangman (Game Over state)
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    printf(" / \\  |\n");
    printf("      |\n");
    printf("=========\n");
    break;

  default: // Handle unexpected values (e.g., > 6) - Show the final stage
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    printf(" / \\  |\n");
    printf("      |\n");
    printf("=========\n");
    fprintf(stderr,
            "Warning: drawHangman called with unexpected value (%d). "
            "Displaying final stage.\\n",
            incorrectGuesses);
    break;
  }
  printf("\n"); // Add a little space after the drawing
}

int main() {
  srand(time(NULL));
  // Program logic will go here in later steps.
  printf("Welcome to Hangman!\n"); // Simple message

  // Placeholder call to loadWords (will be refined in Task 20)
  int loadedWordCount = 0;
  char **wordList = loadWords("words.txt", &loadedWordCount);

  // Placeholder check (will be refined in Task 21)
  if (wordList == NULL) {
    fprintf(stderr, "Error loading words from file.\n");
    return 1;
  }
  if (loadedWordCount <= 0) {
    fprintf(stderr, "Error: No words were loaded (%d). Cannot start game.\\n",
            loadedWordCount);
    // Even if wordListMain isn't NULL in some strange case, we need to free it.
    freeWordList(wordList, loadedWordCount); // Use the cleanup function
    return 1;                                // Indicate failure
  }
  // If we reach here, loading was successful!
  printf("Word list loaded successfully. Ready to play!\n\n");

  char playAgain = 'y';
  int maxIncorrectGuesses = MEDIUM_GUESSES;
  do {

    printf("\n--- Select Difficulty ---\n");
    printf("1. Easy   (8 incorrect guesses)\n");
    printf("2. Medium (6 incorrect guesses)\n");
    printf("3. Hard   (4 incorrect guesses)\n");
    printf("Enter your choice (1-3): ");

    char difficultyBuffer[INPUT_BUFFER_SIZE]; // Buffer for difficulty input
    int difficultyChoice = -1;                // Initialize to an invalid choice

    if (fgets(difficultyBuffer, sizeof(difficultyBuffer), stdin) == NULL) {
      if (feof(stdin)) {
        printf("\nEOF detected. Exiting.\n");
      } else {
        perror("Error reading difficulty choice");
      }
      playAgain = 'n'; // Signal to exit
      continue;        // Skip rest of this loop iteration
    }
    sscanf(difficultyBuffer, "%d", &difficultyChoice);
    switch (difficultyChoice) {
    case 1:
      maxIncorrectGuesses = EASY_GUESSES; // Set to 8
      printf("-> Easy difficulty selected (%d guesses).\n",
             maxIncorrectGuesses);
      break;
    case 2:
      maxIncorrectGuesses = MEDIUM_GUESSES; // Set to 6
      printf("-> Medium difficulty selected (%d guesses).\n",
             maxIncorrectGuesses);
      break;
    case 3:
      maxIncorrectGuesses = HARD_GUESSES; // Set to 4
      printf("-> Hard difficulty selected (%d guesses).\n",
             maxIncorrectGuesses);
      break;
    default:
      // This handles cases where sscanf failed (sscanf_result != 1)
      // OR the number entered was not 1, 2, or 3.
      printf("Invalid choice. Defaulting to Medium difficulty.\n");
      maxIncorrectGuesses = MEDIUM_GUESSES; // Set default (6)
      break;                                // Exit the switch
    }
    pauseForUser();

    int randomIndex = rand() % loadedWordCount;
    char *secretWord = wordList[randomIndex];
    printf("DEBUG: Random word selected: %s\n", secretWord);
    printf("DEBUG: Maximum incorrect guesses allowed: %d\n",
           maxIncorrectGuesses);

    int incorrectGuesses = 0;
    size_t wordLength = strlen(secretWord);
    char displayWord[wordLength + 1];
    for (size_t j = 0; j < wordLength; j++) {
      displayWord[j] = '_';
    }
    displayWord[wordLength] = '\0';

    char guessedLetters[ALPHABET_SIZE + 1] = {0};
    int numGuessedLetters = 0;

    int gameOver = 0;
    int playerWon = 0;

    printf("\nStarting the game loop...\n");

    while (!gameOver) {
      clearScreen();
      printf("--- HANGMAN ---\n");
      drawHangman(incorrectGuesses);
      printf("Hangman state (Incorrect guesses: %d/%d)\n", incorrectGuesses,
             maxIncorrectGuesses);
      printf("Word: ");
      for (size_t i = 0; i < wordLength; i++) {
        printf("%c ", displayWord[i]); // Print with spaces
      }
      printf("\n");

      int guessesRemaining = maxIncorrectGuesses - incorrectGuesses;
      printf("Incorrect guesses remaining: %d\n", guessesRemaining);
      printf("Guessed letters: %s\n", guessedLetters);

      printf("Enter your guess (a single letter): ");
      char inputBuffer[INPUT_BUFFER_SIZE]; // Buffer to hold the raw input line
      char currentGuess = '\0';            // Initialize guess character

      // Read a line from standard input (keyboard)
      if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
        // Handle error or EOF (End Of File) condition
        // If fgets returns NULL, it could be an error or EOF.
        // EOF is often triggered by Ctrl+D (Unix/Linux/macOS) or Ctrl+Z then
        // Enter (Windows).
        if (feof(stdin)) {
          printf("\nEOF detected on input. Exiting game.\n");
        } else {
          // A read error occurred, less common with stdin
          perror("Error reading input");
        }
        gameOver = 1; // Set flag to exit the game loop
        continue;     // Skip the rest of this loop iteration
      }

      if (strlen(inputBuffer) != 2) {
        printf(
            "Invalid input format. Please enter exactly one letter and press "
            "Enter.\n");
        pauseForUser();
        continue;
      } else {
        currentGuess = inputBuffer[0];
        currentGuess = tolower(currentGuess);
        if (!isalpha(currentGuess)) {
          printf("Invalid input. Please enter a letter (a-z).\n");
          pauseForUser();
          continue;
        }
      }

      if (strchr(guessedLetters, currentGuess) != NULL) {
        printf("\n-> You already guessed '%c'. Try a different letter.\n",
               currentGuess);
        pauseForUser();
        continue; // Skip the rest of this turn
      } else {
        // Letter is new and valid!
        guessedLetters[numGuessedLetters] = currentGuess;
        numGuessedLetters++;
        guessedLetters[numGuessedLetters] = '\0';

        int correctGuess = 0;
        printf("\n-> Processing new guess '%c'...\n", currentGuess);
        printf("    -> Checking '%c' against secret word '%s'...\n",
               currentGuess,
               secretWord); // Debug
        for (size_t i = 0; i < wordLength; i++) {
          if (secretWord[i] == currentGuess) {
            displayWord[i] = currentGuess;
            correctGuess = 1;
          }
        }

        if (!correctGuess) {
          printf(
              "Guess '%c' was INCORRECT. (Will increment incorrectGuesses)\n",
              currentGuess); // Debug
          incorrectGuesses++;
        } else {
          printf("Guess '%c' was CORRECT.\n", currentGuess); // Debug
        }

      } // End of check for new/repeat guess

      if (incorrectGuesses == maxIncorrectGuesses) {
        // Player has lost.
        gameOver = 1;
        playerWon = 0;
      } else {
        if (strchr(displayWord, '_') == NULL) {
          gameOver = 1;
          playerWon = 1;
        }
      }

    } // End of while (!gameOver) loop
    clearScreen();
    // --- After the loop (Game Over) ---
    printf("\n--- Game Over --- \n");
    drawHangman(incorrectGuesses);
    // Check playerWon flag (from Step 8) to display final message
    if (playerWon) {
      printf("Congratulations! You guessed the word: %s\n", secretWord);
    } else {
      printf("Sorry, you ran out of guesses. The word was: %s\n", secretWord);
    }

    printf("\nPlay Again? (y/n): ");
    char responseBuffer[INPUT_BUFFER_SIZE];
    if (fgets(responseBuffer, sizeof(responseBuffer), stdin) == NULL) {
      if (feof(stdin)) {
        printf("\nEOF detected. Exiting.\n");
      } else {
        perror("Error reading play again response");
      }
      playAgain = 'n'; // Set to 'n' to ensure loop termination
    } else {
      if (strlen(responseBuffer) > 0) {
        playAgain = tolower(responseBuffer[0]);
      } else {
        playAgain = 'n';
      }
    }
  } while (playAgain == 'y');
  // --- Memory cleanup ---
  printf("\nCleaning up allocated memory...\n");
  freeWordList(wordList, loadedWordCount);
  printf("\nGame Over. Thanks for playing!\n");
  return 0;
}