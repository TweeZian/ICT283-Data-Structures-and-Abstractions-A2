#include <iostream>
#include <fstream>
#include "WindDataStore.h"

using namespace std;

const string DATA_SOURCE = "data/testsample_source.txt"; //sample test data txt file, all data stored in same data folder
//const string DATA_SOURCE = "data/data_source.txt"; //data source file stored in data folder
const string OUTPUT_FILE = "data/WindTempSolar.csv"; //stored in data folder

void StoreDataToSystem(WindDataStore &wds);
int GetMenuChoice();
int GetMonthChoice();
int GetYearChoice();
double ConvertSolarRad(int solarRad); //converts solarRad from W/m2 to kWh/m2
void Menu1(WindDataStore &wds);
void Menu2(WindDataStore &wds);
void Menu3(WindDataStore &wds);
void Menu4(WindDataStore &wds);
void Menu5(WindDataStore &wds);
bool CheckDataExistInMonth(int month, int year, WindDataStore &wds);
bool CheckDataExistInYear(int year, WindDataStore &wds);
void PrintDataToFile(ofstream &outFile, int month, int year, WindDataStore &wds);

//MONTH_STRING declared in Date.h

int main()
{

    WindDataStore wds;
    StoreDataToSystem(wds);
    int choice;
    do
    {
        choice = GetMenuChoice();
        switch(choice)
        {
        case 1:
            Menu1(wds);
            break;
        case 2:
            Menu2(wds);
            break;
        case 3:
            Menu3(wds);
            break;
        case 4:
            Menu4(wds);
            break;
        case 5:
            Menu5(wds);
            break;
        case 6:
            cout << "Program will now exit." << endl;
            break;
        default:
            cout << "Invalid choice, please reenter." << endl << endl;
        }
    }
    while(choice != 6);

    return 0;
}

void StoreDataToSystem(WindDataStore &wds)
{
    ifstream sourceFile(DATA_SOURCE);
    string line;
    while(getline(sourceFile,line)) //read source file to find csv file
    {
        line = "data/" + line; //set data folder into line
        wds.ReadInputFileToStorage(line); //input data into array for every data file in source txt
    }
}

int GetMenuChoice()
{
    cout << "Menu: " << endl;
    cout << "1. Display the average wind speed and sample standard deviation for this wind speed given a specified month and year." << endl;
    cout << "2. Display the average ambient air temperature and sample standard deviation for each month of a specified year." << endl;
    cout << "3. Display the Sample Pearson Correlation Coefficient for a specified month for all years." << endl;
    cout << "4. Print average wind speed(km/h), average ambient air temperature and total solar radiation in kWh/m2 for each month of a specified year to a csv file" << endl;
    cout << "5. Clear all stored information in system, and reload source file." << endl;
    cout << "6. Exit the program." << endl << endl;

    int choice;
    cout << "Please enter choice: " << endl;
    cin >> choice;
    cout << endl;
    return choice;

}

int GetMonthChoice()
{
    int month;
    do
    {
        cout << "Please enter a month as integer (e.g January = 1): " << endl;
        cin >> month;
        if(month < 1 || month > 12)
        {
            cout << "Invalid choice, please reenter." << endl << endl;
        }
    }
    while(month < 1 || month > 12); // run loop till month is valid (1-12)
    cout << endl;

    return month;
}

int GetYearChoice()
{
    int year;
    cout << "Please enter a year: " << endl;
    cin >> year;
    cout << endl;
    return year;
}

double ConvertSolarRad(int solarRad)
{
    double temp;
    temp = solarRad * 1/6;
    temp = temp/1000;
    return temp;
}

void Menu1(WindDataStore &wds)
{
    int year = GetYearChoice();
    int month = GetMonthChoice();
    cout << MONTH_STRING[month] << " " << year << ": ";

    float mean = wds.CalculateWindSpeedMean(month,year);
    float sd = wds.CalculateWindSpeedSD(month,year);

    if(mean != 0) // print info only if there is data, if mean == 0, sd assumed to be 0 too.
    {
        cout << endl;
        cout << "Average speed: " << mean * 3.6 << " km/h" << endl; // converts from m/s to km/h
        cout << "Sample stdev: " << sd << endl;
    }
    else
    {
        cout << "No Data" << endl;
    }
    cout << endl;

}

void Menu2(WindDataStore &wds)
{
    int year = GetYearChoice();
    cout << year << endl;

    for(int i = 1; i <= 12; i++) // run all 12 months
    {
        float mean = wds.CalculateAirTempMean(i,year);
        float sd = wds.CalculateAirTempSD(i,year);
        if(mean != 0)
        {
            cout << MONTH_STRING[i]
                 << ": average: " << mean << " degrees C"
                 << ", stdev: " << sd << endl;
        }
        else
        {
            cout << MONTH_STRING[i] << ": No Data" << endl;
        }
    }
    cout << endl;
}

void Menu3(WindDataStore &wds)
{
    int month = GetMonthChoice();
    cout << "Sample Pearson Correlation Coefficient for " << MONTH_STRING[month] << endl;

    float ST = wds.CalculatesPCCS_T(month);
    float SR = wds.CalculatesPCCS_R(month);
    float TR = wds.CalculatesPCCT_R(month);

    cout << "S_T: " << ST << endl;
    cout << "S_R: " << SR << endl;
    cout << "T_R: " << TR << endl;
    cout << endl;
}

void Menu4(WindDataStore &wds)
{
    ofstream outFile(OUTPUT_FILE);
    if(!outFile)// check if file is available for writing
    {
        cout << "Error in opening output file, please check before retrying." << endl << endl;
    }
    else
    {
        int year = GetYearChoice();
        outFile << year << endl;

        if(CheckDataExistInYear(year,wds)) // check if there is data in given year
        {
            for(int i = 1; i <= 12; i++) // set i to run as every instance of month
            {
                if(CheckDataExistInMonth(i,year,wds)) // check if there is data in given month of year
                {
                    PrintDataToFile(outFile,i,year,wds);
                }
            }
        }
        else // run if no data found in given year
        {
            outFile << "No Data";
        }
        outFile.close();

    }

}

void PrintDataToFile(ofstream &outFile, int month, int year, WindDataStore &wds)
{
    outFile << MONTH_STRING[month] << ",";
    if(wds.CalculateWindSpeedMean(month,year) != 0) // check if there is wind speed data, else skip
    {
        outFile << wds.CalculateWindSpeedMean(month,year) * 3.6 // converts from m/s to km/h
                << "(" << wds.CalculateWindSpeedSD(month,year) << "),";
    }
    else
    {
        outFile << ",";
    }

    if(wds.CalculateAirTempMean(month,year) != 0) // check if there is air temp data, else skip
    {
        outFile << wds.CalculateAirTempMean(month,year) << "("
                << wds.CalculateAirTempSD(month,year) << "),";
    }
    else
    {
        outFile << ",";
    }

    if(wds.CalculateSolarRadTotal(month,year) != 0) // check if there is solar rad data, else skip
    {
        outFile << ConvertSolarRad(wds.CalculateSolarRadTotal(month,year)) << endl;
    }
    else
    {
        outFile << endl;
    }
}

bool CheckDataExistInMonth(int month, int year, WindDataStore &wds)
{
    if(wds.CalculateWindSpeedMean(month,year) != 0)
    {
        if(wds.CalculateAirTempMean(month,year) != 0)
        {
            if(wds.CalculateSolarRadTotal(month,year) != 0)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}

bool CheckDataExistInYear(int year, WindDataStore &wds)
{
    for(int i = 1; i <= 12; i++) // check data every month for given year
    {
        if(wds.CalculateWindSpeedMean(i,year) != 0) // check if there is wind speed data
        {
            return true;
        }
        if(wds.CalculateAirTempMean(i,year) != 0) // check if there is air temp data
        {
            return true;
        }
        if(wds.CalculateSolarRadTotal(i,year) != 0) // check if there is solar rad data
        {
            return true;
        }
    }
    return false; // only when checking every month of given year, and no data can be found
}

void Menu5(WindDataStore &wds)
{
    bstMap wdmap;
    wds.GetMap(wdmap);
    itrMap it = wdmap.begin();
    wdBst tree;

    while (it != wdmap.end())
    {
        wds.GetBst(tree, it);
        tree.DeleteTree();
        ++it;
    }

    wdmap.clear();
    if(wdmap.empty())
        cout << "Data store all cleared." << endl;
    else
        cout << "Data store not cleared, error occurred." << endl;

    StoreDataToSystem(wds);
    cout << "Data reloaded into system." << endl;
    cout << endl;
}
