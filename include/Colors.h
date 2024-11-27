#ifndef COLORS_H
#define COLORS_H
#include <string>
using namespace std;

// Reset
string Color_Off="\033[0m";       // Text Reset

// Regular Colors
string Black="\033[0;30m";        // Black
string Red="\033[0;31m";          // Red
string Green="\033[0;32m";        // Green
string Yellow="\033[0;33m";       // Yellow
string Blue="\033[0;34m";         // Blue
string Purple="\033[0;35m";       // Purple
string Cyan="\033[0;36m";         // Cyan
string White="\033[0;37m";        // White

// Bold
string BBlack="\033[1;30m";       // Black
string BRed="\033[1;31m";         // Red
string BGreen="\033[1;32m";       // Green
string BYellow="\033[1;33m";      // Yellow
string BBlue="\033[1;34m";        // Blue
string BPurple="\033[1;35m";      // Purple
string BCyan="\033[1;36m";        // Cyan
string BWhite="\033[1;37m";       // White

// Underline
string UBlack="\033[4;30m";       // Black
string URed="\033[4;31m";         // Red
string UGreen="\033[4;32m";       // Green
string UYellow="\033[4;33m";      // Yellow
string UBlue="\033[4;34m";        // Blue
string UPurple="\033[4;35m";      // Purple
string UCyan="\033[4;36m";        // Cyan
string UWhite="\033[4;37m";       // White

// Background
string On_Black="\033[40m";       // Black
string On_Red="\033[41m";         // Red
string On_Green="\033[42m";       // Green
string On_Yellow="\033[43m";      // Yellow
string On_Blue="\033[44m";        // Blue
string On_Purple="\033[45m";      // Purple
string On_Cyan="\033[46m";        // Cyan
string On_White="\033[47m";       // White

// High Intensity
string IBlack="\033[0;90m";       // Black
string IRed="\033[0;91m";         // Red
string IGreen="\033[0;92m";       // Green
string IYellow="\033[0;93m";      // Yellow
string IBlue="\033[0;94m";        // Blue
string IPurple="\033[0;95m";      // Purple
string ICyan="\033[0;96m";        // Cyan
string IWhite="\033[0;97m";       // White

// Bold High Intensity
string BIBlack="\033[1;90m";      // Black
string BIRed="\033[1;91m";        // Red
string BIGreen="\033[1;92m";      // Green
string BIYellow="\033[1;93m";     // Yellow
string BIBlue="\033[1;94m";       // Blue
string BIPurple="\033[1;95m";     // Purple
string BICyan="\033[1;96m";       // Cyan
string BIWhite="\033[1;97m";      // White

// High Intensity backgrounds
string On_IBlack="\033[0;100m";   // Black
string On_IRed="\033[0;101m";     // Red
string On_IGreen="\033[0;102m";   // Green
string On_IYellow="\033[0;103m";  // Yellow
string On_IBlue="\033[0;104m";    // Blue
string On_IPurple="\033[0;105m";  // Purple
string On_ICyan="\033[0;106m";    // Cyan
string On_IWhite="\033[0;107m";   // White

#endif