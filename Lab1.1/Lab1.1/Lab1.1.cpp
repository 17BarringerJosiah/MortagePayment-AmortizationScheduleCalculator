// <Functions and Recursion Program Assignment> --Create a monthly mortage calculator and amortization schedule using functions and recursion
//CSIS 212-<D02>
//<Citationss> -- used the examples provided in the assignment instructions


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

// Function tp validate if a double value is within a specified range
bool validDoubleRange(double value, double min, double max) {
    // Check if cin is in a fail state or if the value is outside the specified range
    if (cin.fail() || (value < min || value > max)) {
        // Print error message
        cout << "Value must be a number and must be between " << min << " and " << max << " inclusive" << endl;
        // Clear the fail state of cin and ignore the input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

//function to validate if a double value is positive
bool validDoublePositive(double num) {
    // Check if cin is in a fail state or if the value is not positive
    if (cin.fail() || num <= 0) {
        // Print error message
        cout << "Value must be a number and must be positive" << endl;
        // Clear the fail state of cin and ignore the input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// Function to validate if an integer value belongs to a specific series
bool validIntSeries(int num) {
    // Check if cin is in a fail state or if the value is nor part of the specified series
    if (cin.fail() || (num != 20 && num != 25 && num != 30 && num != 40)) {
        // Print error message
        cout << "You must enter 20, 25, 30, or 40." << endl;
        // Clear the fail state of cin and ignore the input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// Function to calculate the amortization schedule recursively
void loanAmortizeSchedule(int currentPeriod, int totalPeriods, double PaymentAmount, double MonthlyInterestRate, double currentBalance) {
    // Print column headings if it's the first perod
    if (currentPeriod == 0) {
        cout << setw(20) << left << "Payment Number" << setw(20) << left << "Payment Amount" << setw(20) << left << "Interest" << setw(20) << left << "Principal" << setw(20) << left << "Balance" << endl;
    }

    // Calculate and print amortization schedule for each period
    if (currentPeriod <= totalPeriods) {
        double AnnualInterestRate = round(MonthlyInterestRate * currentBalance * 100) / 100.0;
        double LoanPrincipal = PaymentAmount - AnnualInterestRate;
        double newBalance = currentBalance - LoanPrincipal;

        if (currentPeriod == totalPeriods) {
            PaymentAmount = currentBalance + AnnualInterestRate;
            LoanPrincipal = currentBalance;
            newBalance = 0;
        }

        cout << setw(20) << left << currentPeriod << setw(20) << left << PaymentAmount << setw(20) << left << AnnualInterestRate << setw(20) << left << LoanPrincipal << setw(20) << left << newBalance << endl;
        loanAmortizeSchedule(currentPeriod + 1, totalPeriods, PaymentAmount, MonthlyInterestRate, newBalance);
    }
}

// Function to calculate the monthly payment for the loan
double paymentCalculator(double LoanPrincipal, int LoanTerm, double AnnualInterestRate) {
    //convert annual interest rate to monthly rate
    double MonthlyInterestRate = AnnualInterestRate / 12.0 / 100.0;
    double TotalNumberOfPaymentPeriods = LoanTerm * 12.0;
    double base = 1.0 + MonthlyInterestRate;
    double denominator = pow(base, TotalNumberOfPaymentPeriods) - 1.0;
    double numerator = LoanPrincipal * MonthlyInterestRate * pow(base, TotalNumberOfPaymentPeriods);
    return numerator / denominator;
}

int main()
{
cout << "Josiah Barringer -- Lab 1 - Recursion" << endl << endl;

double LoanPrincipal, AnnualInterestRate, LoanTerm;

//input validation loop for loan principle
do {
    cout << "Principal (between 100000 and 250000): ";
    cin >> LoanPrincipal;
} while (!validDoubleRange(LoanPrincipal, 100000, 250000));

// Input validation loop for annual interest rate
do {
    cout << "Annual Interest Rate (between 1.0 and 10.0): ";
    cin >> AnnualInterestRate;
} while (!validDoubleRange(AnnualInterestRate, 1.0, 10.0));

// Input validation loop for loan term
do {
    cout << "Loan Term (20, 25, 30, or 40): ";
    cin >> LoanTerm;
} while (!validIntSeries(LoanTerm));

system("pause"); // Give user a chance to review the entries
system("cls"); // Clear the screen

//calculate monthly payment
double MonthlyInterestRate = AnnualInterestRate / 12.0 / 100.0;
double TotalNumberOfPaymentPeriods = LoanTerm * 12.0;
double PaymentAmount = paymentCalculator(LoanPrincipal, LoanTerm, AnnualInterestRate);
cout << "Payment amount per period: $" << fixed << setprecision(2) << PaymentAmount << endl;

//print loan application information
cout << "Loan Application Information and Amortization Schedule" << endl;
cout << setw(20) << left << "Principle: " << setw(20) << right << LoanPrincipal << endl;
cout << setw(20) << left << "Life of loan: " << setw(20) << right << LoanTerm << endl;
cout << setw(10) << left << "Annual interest rate: " << setw(18) << right << AnnualInterestRate << endl;
cout << setw(20) << left << "Monthly Payment: " << setw(20) << right << PaymentAmount << endl;

// Make and print the amortzation schedule
loanAmortizeSchedule(0, TotalNumberOfPaymentPeriods, PaymentAmount, MonthlyInterestRate, LoanPrincipal);



return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
