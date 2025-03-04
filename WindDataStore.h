/***
@author Thien Twee Zian
@since 30/07/2023
@version 1.01
Holds WindData type in a combination of BST and map data structure
*/

#ifndef WINDDATASTORE_H_INCLUDED
#define WINDDATASTORE_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include "WindData.h"
#include "Bst.h"

using namespace std;

/**
Typedef for a BST holding WindData objects
Key is made of date and time combined as a string
*/
typedef Bst<WindData> wdBst;

/**
Typedef for a map holding BST objects
Key is made of month (January etc.) and year as a string
*/
typedef map<string,wdBst> bstMap;

/**
Typedef for an iterator of bstMap
*/
typedef map<string,wdBst>:: iterator itrMap;

/**
This class is used to store WindData objects into multiple BSTs, which would then be stored into
a map of the BSTs. The WindData is stored in BSTs, which would be stored into a map segregated
according to the month and year of the record.
*/
class WindDataStore
{

private:
    /**
    Map storing the BSTs, which in turn stores the data
    */
    bstMap m_bstMap;

    /**
    Vector of header names, used for indicating the csv data retrieved by its columns.
    To be used for storage of data into appropriate WindData attributes.
    */
    vector<string> m_headerNames; //vector used as number of header names to be stored remains unknown, able to adjust according to usage

    /**
    Method to store the WindData into storage, first into BSTs, then into the map
    @param wd - WindData object to be stored
    */
    void StoreIntoMap(WindData wd);

    /**
    Method used to set the headers names into the m_headerNames.
    @param line - Header name to be stored
    */
    void SetHeaderNames(string &line);

    /**
    This method is used to store the date and time into the WindData object
    @param wd - WindData object to store at
    @param line - String of data to store
    @param currentColumn - Used to indicate the current data in line
    @param fileName - The file name being read for data extraction. Used for error checking.
    */
    void StoreDateAndTime(WindData &wd, string &line, int currentColumn, const string &fileName);

    /**
    This method is used to store the air temperature into the WindData object
    @param wd - WindData object to store at
    @param line - String of data to store
    @param currentColumn - Used to indicate the current data in line
    @param fileName - The file name being read for data extraction. Used for error checking.
    */
    void StoreAirTemp(WindData &wd, string &line, int currentColumn, const string &fileName);

    /**
    This method is used to store the wind speed into the WindData object
    @param wd - WindData object to store at
    @param line - String of data to store
    @param currentColumn - Used to indicate the current data in line
    @param fileName - The file name being read for data extraction. Used for error checking.
    */
    void StoreSpeed(WindData &wd, string &line, int currentColumn, const string &fileName);

    /**
    This method is used to store the solar radiation into the WindData object
    @param wd - WindData object to store at
    @param line - String of data to store
    @param currentColumn - Used to indicate the current data in line
    @param fileName - The file name being read for data extraction. Used for error checking.
    */
    void StoreSolarRad(WindData &wd, string &line, int currentColumn, const string &fileName);

    /**
    Method used to get sum of wind speed.
    To be passed into BST InorderTraversal through function passing
    @param wd - WindData object, will be passed in by BST InorderTraversal method
    @param sum - Container for sum of wind speed calculated.
    */
    static void GetWindSpeedSum(WindData& wd, float& sum);

    /**
    Method used to get wind speed from BST, stored into a vector<float>.
    To be passed into BST InorderTraversal through function passing
    @param wd - WindData object, will be passed in by BST InorderTraversal method
    @param wsv - Container for wind speed objects to be stored
    */
    static void GetWindSpeedVector(WindData& wd, vector<float>& wsv);

    /**
    Method used to get sum of air temp.
    To be passed into BST InorderTraversal through function passing
    @param wd - WindData object, will be passed in by BST InorderTraversal method
    @param sum - Container for sum of air temp calculated.
    */
    static void GetAirTempSum(WindData& wd, float& sum);

    /**
    Method used to get air temp from BST, stored into a vector<float>.
    To be passed into BST InorderTraversal through function passing
    @param wd - WindData object, will be passed in by BST InorderTraversal method
    @param atv - Container for air temp objects to be stored
    */
    static void GetAirTempVector(WindData& wd, vector<float>& atv);

    /**
    Method used to get sum of solar rad.
    To be passed into BST InorderTraversal through function passing
    @param wd - WindData object, will be passed in by BST InorderTraversal method
    @param sum - Container for sum of solar rad calculated.
    */
    static void GetSolarRadSum(WindData& wd, int& sum);

    /**
    Method used to get solar rad from BST, stored into a vector<int>.
    To be passed into BST InorderTraversal through function passing
    @param wd - WindData object, will be passed in by BST InorderTraversal method
    @param srv - Container for solar rad objects to be stored
    */
    static void GetSolarRadVector(WindData& wd, vector<int>& srv);

    /**
    Method to get the mean of wind speed in every for a specified month.
    @param month - Month to be calculated
    @return mean - Mean of wind speed
    */
    float GetsPCCWindSpeedMean(int month);

    /**
    Method to get the mean of air temp in every for a specified month.
    @param month - Month to be calculated
    @return mean - Mean of air temp
    */
    float GetsPCCAirTempMean(int month);

    /**
    Method to get the mean of solar rad in every for a specified month.
    @param month - Month to be calculated
    @return mean - Mean of solar rad
    */
    float GetsPCCSolarRadMean(int month);

public:
    /**
    Default constructor
    */
    WindDataStore();

    /**
    This method is used to find the number of elements in storage.
    @return size - Number of elements in storage
    */
    int Size();

    /**
    Method to get BST. It uses iterators for loops.
    @param wdBST - WindData BST to be retrieved by reference
    @param it - Map iterator
    */
    void GetBst(wdBst &wdBST, itrMap it);

    /**
    Method to get map
    @param othermap - Map to be retrieved by reference
    */
    void GetMap(bstMap &othermap);

    // Methods for storage is stored in this class instead of WindData as:
    // 1. It requires the use of headerNames to find the right attributes to be stored.
    // 2. This class is used to adjust the attributes to be stored, only taking the ones required,
    //    therefore keeping the WindData encapsulated and purely for the storage of data.
    /**
    This method is used to read a csv file and extract the required information within.
    This method is to be used with the appropriate data type storage methods.
    @param fileName - Name of data file
    @return boolean - Return true if operation is successful, otherwise false.
    */
    bool ReadInputFileToStorage(const string &fileName);

    /**
    This method is used to calculate the average wind speed of given month and year
    @param month - Month to be calculated
    @param year - Year to be calculated
    @return mean - Average wind speed
    */
    float CalculateWindSpeedMean(int month, int year);

    /**
    This method is used to calculate the standard deviation of wind speed of given month and year
    @param month - Month to be calculated
    @param year - Year to be calculated
    @return sd - Wind speed standard deviation
    */
    float CalculateWindSpeedSD(int month, int year);

    /**
    This method is used to calculate the average air temperature of given month and year
    @param month - Month to be calculated
    @param year - Year to be calculated
    @return mean - Average air temperature
    */
    float CalculateAirTempMean(int month, int year);

    /**
    This method is used to calculate the standard deviation of air temperature of given month and year
    @param month - Month to be calculated
    @param year - Year to be calculated
    @return sd - Air temperature standard deviation
    */
    float CalculateAirTempSD(int month, int year);

    /**
    This method is used to calculate the total solar radiation of given month and year
    @param month - Month to be calculated
    @param year - Year to be calculated
    @return sum - Total solar radiation
    */
    int CalculateSolarRadTotal(int month, int year);

    /**
    Method used to calculate the Sample Pearson Correlation Coefficient of a specified month in
    every year using wind speed and air temp.
    @param month - Month to be calculated
    @return sPPC - Sample Pearson Correlation Coefficient calculated
    */
    float CalculatesPCCS_T(int month);

    /**
    Method used to calculate the Sample Pearson Correlation Coefficient of a specified month in
    every year using wind speed and solar rad.
    @param month - Month to be calculated
    @return sPPC - Sample Pearson Correlation Coefficient calculated
    */
    float CalculatesPCCS_R(int month);

    /**
    Method used to calculate the Sample Pearson Correlation Coefficient of a specified month in
    every year using air temp and solar rad.
    @param month - Month to be calculated
    @return sPPC - Sample Pearson Correlation Coefficient calculated
    */
    float CalculatesPCCT_R(int month);

};
#endif // WINDDATASTORE_H_INCLUDED
