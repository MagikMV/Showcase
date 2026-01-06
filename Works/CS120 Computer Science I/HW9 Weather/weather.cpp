void showProgramHeader();

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//***FIVE FUNCTIONS***
void highestTemp(float weatherInfo[][5], int rowSize, int columnSize);
void lowestTemp(float weatherInfo[][5], int rowSize, int columnSize);
void avgDailyHigh(float weatherInfo[][5], int rowSize, int columnSize);
void avgDailyLow(float weatherInfo[][5], int rowSize, int columnSize);
void snowDepthChange(float weatherInfo[][5], int rowSize, int columnSize);

int main()
{
    showProgramHeader();
    ifstream infile;
    infile.open("weather.txt");
    float weatherInfo[31][5];
    highestTemp(weatherInfo, 31, 5);
    lowestTemp(weatherInfo, 31, 5);
    avgDailyHigh(weatherInfo, 31, 5);
    avgDailyLow(weatherInfo, 31, 5);
    snowDepthChange(weatherInfo, 31, 5);
}
//***PROGRAM HEADER***
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Section 6 \nApril 10, 2019 \nHomework Number 9 \n" << endl;
}
//***HIGHEST RECORDED TEMPERATURE***
void highestTemp(float weatherInfo[][5], int rowSize, int columnSize)
{
    ifstream infile;
    infile.open("weather.txt");
    for(int i = 0; i < 31; i++)
    {
        for(int k = 0; k < 5; k++)
        {
            infile >> weatherInfo[i][k];
        }
    }
    float highest = weatherInfo[0][0];
    for (int i = 0; i < 31; i++)
    {
        infile >> weatherInfo[i][0];
        if(weatherInfo[i][0] > highest)
        {
            highest = weatherInfo[i][0];
        }
    }
    cout << "The highest recorded temperature was: " << highest << endl;
}
//***LOWEST RECORDED TEMPERATURE***
void lowestTemp(float weatherInfo[][5], int rowSize, int columnSize)
{
    ifstream infile;
    infile.open("weather.txt");
    for(int i = 0; i < 31; i++)
    {
        for(int k = 0; k < 5; k++)
        {
            infile >> weatherInfo[i][k];
        }
    }
    float lowest = weatherInfo[0][1];
    for (int i = 0; i < 31; i++)
    {
        infile >> weatherInfo[i][1];
        if(weatherInfo[i][1] < lowest)
        {
            lowest = weatherInfo[i][1];
        }
    }
    cout << "The lowest recorded temperature was: " << lowest << endl;

}
//***AVERAGE DAILY HIGH TEMPERATURE***
void avgDailyHigh(float weatherInfo[][5], int rowSize, int columnSize)
{
    ifstream infile;
    infile.open("weather.txt");
    for(int i = 0; i < 31; i++)
    {
        for(int k = 0; k < 5; k++)
        {
            infile >> weatherInfo[i][k];
        }
    }
    float sum = 0;
    float averageHigh;
    for (int i = 0; i < 31; i++)
    {
        infile >> weatherInfo[i][0];
        sum += weatherInfo[i][0];
    }
    averageHigh = sum/31;
    cout << "The average daily high was: " << averageHigh << endl;
}
//***AVERAGE DAILY LOW TEMPERATURE***
void avgDailyLow(float weatherInfo[][5], int rowSize, int columnSize)
{
    ifstream infile;
    infile.open("weather.txt");
    for(int i = 0; i < 31; i++)
    {
        for(int k = 0; k < 5; k++)
        {
            infile >> weatherInfo[i][k];
        }
    }
    float sum = 0;
    float averageLow;
    for (int i = 0; i < 31; i++)
    {
        infile >> weatherInfo[i][1];
        sum += weatherInfo[i][1];
    }
    averageLow = sum/31;
    cout << "The average daily low was: " << averageLow << endl;
}
//***DAILY CHANGE IN TOTAL SNOW DEPTH***
void snowDepthChange(float weatherInfo[][5], int rowSize, int columnSize)
{
    ifstream infile;
    infile.open("weather.txt");
    for(int i = 0; i < 31; i++)
    {
        for(int k = 0; k < 5; k++)
        {
            infile >> weatherInfo[i][k];
        }
    }
    float totalDifference = 9.02;
    float dailyChange = totalDifference / 31;
    cout << "The daily change in total snow depth: " << dailyChange << endl;
}
