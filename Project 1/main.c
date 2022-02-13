/*
* Program Name: COP 2220 Project 1
*
* Description: Collect the inputs of various test grades and calculate the resulting
*              overall course grade, displaying the calculated totals to the user.
*
* Author: Austin McCallister (N01487083)
*
* Date: 09/08/2021
*/

#include <stdio.h>

int main(void) {
   const int QUIZ_MAX = 400; //declare constants and variables
   const int MID_MAX = 200;
   const int FINAL_MAX = 100;

   const double QUIZ_WEIGHT = 0.30;
   const double MID_WEIGHT = 0.40;
   const double FINAL_WEIGHT = 0.30;

   double quizPercent;
   double midPercent;
   double finalPercent;
   double totalPercent;

   double quizScore1;
   double quizScore2;
   double quizScore3;
   double quizScore4;
   double quizTotal;

   double midScore1;
   double midScore2;
   double midTotal;

   double finalScore;

   printf("\n########### QUIZ ###########\n\n"); //start

   printf("Enter Quiz 1 Score: "); //enter quiz scores
   scanf("%lf", &quizScore1);
   printf("Enter Quiz 2 Score: ");
   scanf("%lf", &quizScore2);
   printf("Enter Quiz 3 Score: ");
   scanf("%lf", &quizScore3);
   printf("Enter Quiz 4 Score: ");
   scanf("%lf", &quizScore4);

   printf("\n########## MIDTERM #########\n\n");

   printf("Enter Midterm 1 Score: "); //enter midterm scores
   scanf("%lf", &midScore1);
   printf("Enter Midterm 2 Score: ");
   scanf("%lf", &midScore2);

   printf("\n########### FINAL ##########\n\n");

   printf("Enter Final Score: "); //enter final score
   scanf("%lf", &finalScore);

   printf("\n########## TOTALS ##########\n\n");

   printf("Quiz 1: %14.2lf\n", quizScore1); //print quiz total
   printf("Quiz 2: %14.2lf\n", quizScore2);
   printf("Quiz 3: %14.2lf\n", quizScore3);
   printf("Quiz 4: %14.2lf\n", quizScore4);
    
   quizTotal = quizScore1 + quizScore2 + quizScore3 + quizScore4; //add all quiz scores for total

   printf("Quiz Total: %10.2lf\n\n", quizTotal);

   printf("Midterm 1: %11.2lf\n", midScore1); //print midterm total
   printf("Midterm 2: %11.2lf\n", midScore2);

   midTotal = midScore1 + midScore2; //add all midterm scores for total

   printf("Midterm Total: %7.2lf\n\n", midTotal);

   printf("Final: %15.2lf\n\n", finalScore); //print final total

   printf("######## PERCENTAGES #######\n\n");

   quizPercent = quizTotal / QUIZ_MAX * QUIZ_WEIGHT * 100; //calculate score percentage breakdown
   midPercent = midTotal / MID_MAX * MID_WEIGHT * 100;
   finalPercent = finalScore / FINAL_MAX * FINAL_WEIGHT * 100;
   totalPercent = quizPercent + midPercent + finalPercent;

   printf("Quiz: %16.2lf%%\n", quizPercent); //print course percentage breakdown
   printf("Midterm: %13.2lf%%\n", midPercent);
   printf("Final: %15.2lf%%\n", finalPercent);

   printf("____________________________\n\n");

   printf("Total: %15.2lf%%\n\n", totalPercent); //final course grade

   return 0;
}
