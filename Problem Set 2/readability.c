#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Methods
float calculate_average(float valueA, float valueB);
int calculate_coleman_liau_index(float letters, float sentences);

int main(void)
{
    string userInput = get_string("Text: ");

    // Variables
    int inputLength = strlen(userInput);

    int characterCount = 0;
    int words = 1;
    int sentences = 0;

    float averageLetters;
    float averageSentences;
    int colemanLiauIndex;

    for (int i = 0; i < inputLength; i++)
	{
	    // Count all the characters and total amount of words
	    if (isalpha(userInput[i]))
	    {
	        characterCount++;
	    }

	    // Use spaces foud to determine how many words there are
	    if (isspace(userInput[i]))
	    {
	        words++;
	    }

	    // Count all the sentences
	    if (userInput[i] == '!' || userInput[i] == '?' || userInput[i] == '.'){
	        sentences++;
	    }
	}

    // Calculate the averages
    averageLetters = calculate_average((float)characterCount, (float)words);
    averageSentences = calculate_average((float)sentences, (float)words);


    colemanLiauIndex = calculate_coleman_liau_index(averageLetters, averageSentences);

    // Convert the coleman index to a grade
    if (colemanLiauIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (colemanLiauIndex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", colemanLiauIndex);
    }
}

/* Function: calculate_average
 *
 * Returns: float value of valueA divided by valueB and multiplied by 100
 *
*/
float calculate_average(float valueA, float valueB)
{
    return valueA / valueB * 100.0;
}

/* Function: calculate_coleman_liau_index
 *
 * Description: Coleman Liau index is used to determine the readability of a series of words. This index is US based.
 *
 * Returns: int value that represents the grade level of reading
 * based on the average letters per 100 words and the average sentences per 100 words
 *
*/
int calculate_coleman_liau_index(float letters, float sentences)
{
    return round((0.0588 * letters) - (0.296 * sentences) - 15.8);
}