/*
 * Program Name: COP 2220 Project 2
 *
 * Description: Obtain the initial principal, interest rate, and number of years of a user's loan,
 *              and output payment data into an amortization table.
 *
 * Author: Austin McCallister (N01487083)
 *
 * Date: 10/26/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Declare function prototypes
double GetMonths(int, int);
double GetInterest(int, int);
double GetPrincipal(int, int);

double CalcMonthlyPayment(double, double, double);
double CalcMonthlyInterest(double, double);
double CalcAdjustedPrincipal(double, double);
double CalcNewBalance(double, double);

void PrintTable(int, double, double);

// Start main
int main(void) {
   const int MIN_YEARS = 2;
   const int MAX_YEARS = 40;
   const int MIN_INTEREST = 1;
   const int MAX_INTEREST = 20;
   const int MIN_PRINCIPAL = 5000;
   const int MAX_PRINCIPAL = 2000000;

   int numMonths;
   double interestRate;
   double initialPrincipal;

   numMonths = GetMonths(MIN_YEARS, MAX_YEARS);
   interestRate = GetInterest(MIN_INTEREST, MAX_INTEREST);
   initialPrincipal = GetPrincipal(MIN_PRINCIPAL, MAX_PRINCIPAL);

   PrintTable(numMonths, interestRate, initialPrincipal);

   return 0;
}

/*
 * Get number of years from user and convert to months
 * Check if within valid range, or prompt for additional input
 * Quit if input = 0
 */
double GetMonths(int minYears, int maxYears) {
   double numYears;

   printf("Enter in the number of years (2 to 40) for this loan, or zero to quit: ");
   scanf("%lf", &numYears);

   while (numYears > maxYears || (numYears < minYears && numYears > 0)) {
      printf("Invalid Entry. Enter 2 through 40, or zero to quit: ");
      scanf("%lf", &numYears);
   }
   if (numYears <= 0) {
      exit(0);
   }
   return (numYears * 12);
}

/*
 * Get interest rate percentage from user and convert to decimal per payment period
 * Check if within valid range, or prompt for additional input
 * Quit if input = 0
 */
double GetInterest(int minInterest, int maxInterest) {
   double interestRate;

   printf("Enter in the interest rate (1 to 20) for this loan, or zero to quit: ");
   scanf("%lf", &interestRate);

   while (interestRate > maxInterest || (interestRate < minInterest && interestRate > 0)) {
      printf("Invalid Entry. Enter 1 through 20, or zero to quit: ");
      scanf("%lf", &interestRate);
   }
   if (interestRate <= 0) {
      exit(0);
   }
   return ((interestRate / 100) / 12);
}

/*
 * Get initial principal from user
 * Check if within valid range, or prompt for additional input
 * Quit if input = 0
 */
double GetPrincipal(int minPrincipal, int maxPrincipal) {
   double startPrincipal;

   printf("Enter in the total amount (5 thousand to 2 million) for this loan, or zero to quit: ");
   scanf("%lf", &startPrincipal);

   while (startPrincipal > maxPrincipal || (startPrincipal < minPrincipal && startPrincipal > 0)) {
      printf("Invalid Entry. Enter 5 thousand through 2 million, or zero to quit: ");
      scanf("%lf", &startPrincipal);
   }
   if (startPrincipal <= 0) {
      exit(0);
   }
   return startPrincipal;
}

/*
 * Performs and returns the monthly payment calculation
 * P = Initial principal
 * r = Interest rate
 * n = Number of months
 */
double CalcMonthlyPayment(double P, double r, double n) {
   return (P * (r * pow((1 + r), n)) / (pow((1 + r), n) - 1));
}

// Calculate the monthly interest payment for each pay period
double CalcMonthlyInterest(double currentBalance, double interestRate) {
   return (currentBalance * interestRate);
}

// Calculate the amount of the fixed payment which goes to paying off principal
double CalcAdjustedPrincipal(double fixedPayment, double monthlyInterest) {
   return (fixedPayment - monthlyInterest);
}

// Re-calculate the current loan balance after each pay period
double CalcNewBalance(double currentBalance, double principalPayment) {
   return (currentBalance - principalPayment);
}

/*
 * Output amortization table
 * Calculate and print total interest, principal and overall cost of the loan
 */
void PrintTable(int numMonths, double interestRate, double newBalance) {
   double fixedPayment;
   double monthlyInterest;
   double principalPayment;

   double totalInterest = 0;
   double totalPrincipal = 0;
   double totalBalance = 0;

   fixedPayment = CalcMonthlyPayment(newBalance, interestRate, numMonths);
   monthlyInterest = CalcMonthlyInterest(newBalance, interestRate);
   principalPayment = CalcAdjustedPrincipal(fixedPayment, monthlyInterest);
   newBalance = CalcNewBalance(newBalance, principalPayment);

   printf("\n#############################################\n");
   printf("# Month | Interest | Principal |   Balance  #\n");
   printf("# ----------------------------------------- #\n");

   for (int i = 1; i <= numMonths; i++) {
      printf("#  %03d  | %8.2lf |  %8.2lf | %10.2lf #\n",
             i, monthlyInterest, principalPayment, newBalance);

      totalInterest = totalInterest + monthlyInterest;
      totalPrincipal = totalPrincipal + principalPayment;

      monthlyInterest = CalcMonthlyInterest(newBalance, interestRate);
      principalPayment = CalcAdjustedPrincipal(fixedPayment, monthlyInterest);
      newBalance = CalcNewBalance(newBalance, principalPayment);

      if (newBalance < 0) { // Gets rid of final balance sometimes returning -0.00
         newBalance = 0;
      }
   }
   printf("#############################################\n\n");

   totalBalance = totalInterest + totalPrincipal;

   printf("Total Interest Paid:  $%11.2lf\n", totalInterest);
   printf("Total Principal Paid: $%11.2lf\n", totalPrincipal);
   printf("Total Cost of Loan:   $%11.2lf\n", totalBalance);
}