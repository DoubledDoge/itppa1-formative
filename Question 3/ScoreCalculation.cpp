// (My Documentation Placeholder)

// Preamble libraries:
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Function to get the scores and do some calculations with them:
void inputScores(int studentScores[], int &sumScore, int &maxScore, int &minScore)
{
    // Repeat for the entire length of the array:
    for (int i = 0; i < 5; i++)
    {
        // Input validation:
        do
        {
            // Getting all 5 student scores from the user:
            cout << "Please enter the score of student " << i + 1 << ": ";
            cin >> studentScores[i];
        } while (studentScores[i] < 0 || studentScores[i] > 100);

        // Adding inputted score to the sum of all scores:
        sumScore += studentScores[i];

        // Determine current highest score (if applicable):
        if (studentScores[i] > maxScore)
        {
            maxScore = studentScores[i];
        }
        // Determine current lowest score:
        if (studentScores[i] < minScore)
        {
            minScore = studentScores[i];
        }
    }
}

// Function for calculating the average score using the sum of scores:
double calculateAvg(int sumScore)
{
    return (sumScore / 5);
}

// Function to display all of the inputted scores back to the user in the order they were entered:
void displayScores(int studentScores[])
{
    // Displaying a label
    cout << "Here are your scores of your five students:" << endl;

    // Loop for displaying the student socores:
    for (int i = 0; i < 5; i++)
    {
        cout << "Student " << i + 1 << ":" << studentScores[i] << endl;
    }
}

// Function to display some of the other key elements:
void displayOthers(double avgScore, int maxScore, int minScore)
{
    cout << "Your average score: " << avgScore << endl;
    cout << "Your highest score: " << maxScore << endl;
    cout << "Your lowest score: " << minScore << endl;
}

int main()
{
    int studentScores[5];
    int sumScore = 0, maxScore = 0, minScore = 100;
    double avgScore;

    // My optional greeting message:
    cout << "Hello user! Please note that student scores should be a number that is between these ranges: (0 - 100)." << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the greeting message
    cout << endl;

    // Function to get the scores and do some calculations with them:
    inputScores(studentScores, sumScore, maxScore, minScore);
    cout << endl;

    // Function for calculating the average score using the sum of scores:
    avgScore = calculateAvg(sumScore);

    // Function to display all of the inputted scores back to the user in the order they were entered:
    displayScores(studentScores);
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the student scores
    cout << endl;

    // Function to display some of the other key elements:
    displayOthers(avgScore, maxScore, minScore);
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the other elements
    cout << endl;

    // Final message:
    cout << "END OF PROGRAM";
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the final message
}
