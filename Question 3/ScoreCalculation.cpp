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
    const int NUM_STUDENTS = 5;
    const int MIN_SCORE = 0;
    const int MAX_SCORE = 100;

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        do
        {
            cout << "Please enter the score of student " << i + 1 << " (0-100): ";
            cin >> studentScores[i];
        } while (studentScores[i] < MIN_SCORE || studentScores[i] > MAX_SCORE);

        // Calculations for the sum of scores, max score, and min score:
        sumScore += studentScores[i];
        maxScore = max(maxScore, studentScores[i]);
        minScore = min(minScore, studentScores[i]);
    }
    return;
}

// Function for calculating the average score using the sum of scores:
double calculateAvg(double sumScore)
{
    return (sumScore / 5);
}

// Function to display all of the inputted scores back to the user in the order they were entered:
void displayScores(const int studentScores[])
{
    cout << "Here are the scores of your five students:" << endl;

    // Loop for displaying the student socores:
    for (int i = 0; i < 5; i++)
    {
        cout << "Student " << i + 1 << ": " << studentScores[i] << endl;
    }
    return;
}

// Function to display some of the other key elements:
void displayOthers(double avgScore, int maxScore, int minScore)
{
    cout << "Your average score: " << avgScore << endl;
    cout << "Your highest score: " << maxScore << endl;
    cout << "Your lowest score: " << minScore << endl;
    return;
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
    cout << "Have a great day!";
    this_thread::sleep_for(chrono::seconds(3)); // Brief wait timer for the user to read the final message
    return 0;
}
