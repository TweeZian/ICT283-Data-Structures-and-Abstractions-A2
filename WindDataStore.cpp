#include "WindDataStore.h"

WindDataStore::WindDataStore() {}

int WindDataStore::Size()
{
    itrMap it = m_bstMap.begin();
    int counter;
    while(it != m_bstMap.end())
    {
        wdBst tree;
        tree = it->second;
        counter += tree.TreeNodeCount();
        ++it;
    }
    return counter;
}

void WindDataStore::GetBst(wdBst &wdBST, itrMap it)
{
    wdBST = it->second;
}

void WindDataStore::GetMap(bstMap &othermap)
{
    othermap = m_bstMap;
}

bool WindDataStore::ReadInputFileToStorage(const string &fileName)
{
    ifstream infile(fileName);
    if( !infile ) return false;

    string line;
    getline(infile,line); // get header column names
    SetHeaderNames(line);
    while(getline(infile,line))
    {
        WindData wd;
        istringstream iss(line); // initialize row into stream format to be used for processing data into individual columns
        string ssline;
        int currentColumn = 0; // first column starts at 0

        while(getline(iss,ssline,','))
        {
            // runs through every storage column, when matching column found, store data into right storage
            StoreDateAndTime(wd,ssline,currentColumn, fileName);
            StoreAirTemp(wd,ssline,currentColumn, fileName);
            StoreSpeed(wd,ssline,currentColumn, fileName);
            StoreSolarRad(wd,ssline,currentColumn, fileName);

            currentColumn++;
        }
        StoreIntoMap(wd);

    }
    infile.close();
    return true;
}

void WindDataStore::StoreIntoMap(WindData wd)
{
    Date d;
    wd.GetDate(d);
    //use iterator to check if key exist in map
    itrMap it = m_bstMap.find(d.GetMonthString()+to_string(d.GetYear()));

    //if key exist, extract wdBst, insert, and reinsert back into map
    if(it != m_bstMap.end())
    {
        wdBst tree;
        tree = it->second;
        tree.Insert(wd);
        m_bstMap[d.GetMonthString()+to_string(d.GetYear())] = tree;
    }
    //else, create new map allocation
    else
    {
        wdBst tree;
        tree.Insert(wd);
        m_bstMap[d.GetMonthString()+to_string(d.GetYear())] = tree;
    }

}

void WindDataStore::SetHeaderNames(string &line)
{
    istringstream iss(line);
    while(getline(iss,line,','))
    {
        m_headerNames.push_back(line);
    }
}

void WindDataStore::StoreDateAndTime(WindData &wd, string &line, int currentColumn, const string &fileName)
{
    string name = m_headerNames.at(currentColumn);

    if(name.compare("WAST") == 0)
    {
        Date d;
        Time t;
        istringstream iss(line);

        try //catch dirty data
        {
            iss >> d >> t;
            wd.SetDate(d);
            wd.SetTime(t);
        }
        catch(invalid_argument& e)
        {
            //commented out to avoid cluttering terminal, uncomment if necessary
            //display filename and error caught

            //cout << "Error found at WAST = " << line << " , Location: " << fileName << endl;
        }
    }
}

void WindDataStore::StoreAirTemp(WindData &wd, string &line, int currentColumn, const string &fileName)
{
    string name = m_headerNames.at(currentColumn);
    if(name.compare("T") == 0)
    {
        try //catch dirty data
        {
            wd.SetAirTemp(stof(line));
        }
        catch(invalid_argument& e)
        {
            //commented out to avoid cluttering terminal, uncomment if necessary
            //display filename and error caught

            //cout << "Error found at T = " << line << " , Location: " << fileName << endl;
        }
    }
}

void WindDataStore::StoreSpeed(WindData &wd, string &line, int currentColumn, const string &fileName)
{
    string name = m_headerNames.at(currentColumn);
    if(name.compare("S") == 0)
    {
        try //catch dirty data
        {
            wd.SetSpeed(stof(line));
        }
        catch(invalid_argument& e)
        {
            //commented out to avoid cluttering terminal, uncomment if necessary
            //display filename and error caught

            //cout << "Error found at S = " << line << " , Location: " << fileName << endl;
        }

    }
}

void WindDataStore::StoreSolarRad(WindData &wd, string &line, int currentColumn, const string &fileName)
{
    string name = m_headerNames.at(currentColumn);
    if(name.compare("SR") == 0)
    {
        try //catch dirty data
        {
            wd.SetSolarRad(stoi(line));
        }
        catch(invalid_argument& e)
        {
            //commented out to avoid cluttering terminal, uncomment if necessary
            //display filename and error caught

            //cout << "Error found at S = " << line << " , Location: " << fileName << endl;
        }
    }
}

float WindDataStore::CalculateWindSpeedMean(int month, int year)
{
    float sum;
    string key = MONTH_STRING[month]+to_string(year);
    if(m_bstMap.find(key) != m_bstMap.end())
    {
        wdBst tree = m_bstMap.at(key);
        tree.InorderTraversal(GetWindSpeedSum,sum);

        float mean = sum / (float)tree.TreeNodeCount();

        if(mean == 0)
        {
            return 0;
        }
        else
        {
            return mean;
        }
    }
    else
    {
        return 0;
    }
}

void WindDataStore::GetWindSpeedSum(WindData& wd, float& sum)
{
    sum += wd.GetSpeed();
}

float WindDataStore::CalculateWindSpeedSD(int month, int year)
{
    string key = MONTH_STRING[month]+to_string(year);
    vector<float> wsv;
    if(m_bstMap.find(key) != m_bstMap.end())
    {
        wdBst tree = m_bstMap.at(key);
        tree.InorderTraversal(GetWindSpeedVector,wsv);

        float sd;
        float mean = CalculateWindSpeedMean(month,year);
        for(float speed : wsv)
        {
            sd += (speed - mean)*(speed - mean);
        }

        sd = sd / wsv.size();
        sd = sqrt(sd);

        if(sd == 0)
        {
            return 0;
        }
        else
        {
            return sd;
        }
    }
    else
    {
        return 0;
    }
}

void WindDataStore::GetWindSpeedVector(WindData& wd, vector<float>& wsv)
{
    wsv.push_back(wd.GetSpeed());
}

float WindDataStore::CalculateAirTempMean(int month, int year)
{
    float sum;
    string key = MONTH_STRING[month]+to_string(year);
    if(m_bstMap.find(key) != m_bstMap.end())
    {
        wdBst tree = m_bstMap.at(key);
        tree.InorderTraversal(GetAirTempSum,sum);

        float mean = sum / (float)tree.TreeNodeCount();

        if(mean == 0)
        {
            return 0;
        }
        else
        {
            return mean;
        }
    }
    else
    {
        return 0;
    }
}

void WindDataStore::GetAirTempSum(WindData& wd, float& sum)
{
    sum += wd.GetAirTemp();
}

float WindDataStore::CalculateAirTempSD(int month, int year)
{
    string key = MONTH_STRING[month]+to_string(year);
    vector<float> wsv;
    if(m_bstMap.find(key) != m_bstMap.end())
    {
        wdBst tree = m_bstMap.at(key);
        tree.InorderTraversal(GetAirTempVector,wsv);

        float sd;
        float mean = CalculateAirTempMean(month,year);
        for(float speed : wsv)
        {
            sd += (speed - mean)*(speed - mean);
        }

        sd = sd / wsv.size();
        sd = sqrt(sd);

        if(sd == 0)
        {
            return 0;
        }
        else
        {
            return sd;
        }
    }
    else
    {
        return 0;
    }
}

void WindDataStore::GetAirTempVector(WindData& wd, vector<float>& atv)
{
    atv.push_back(wd.GetAirTemp());
}

int WindDataStore::CalculateSolarRadTotal(int month, int year)
{
    int sum;
    string key = MONTH_STRING[month]+to_string(year);
    if(m_bstMap.find(key) != m_bstMap.end())
    {
        wdBst tree = m_bstMap.at(key);
        tree.InorderTraversal(GetSolarRadSum,sum);
        return sum;
    }
    else
    {
        return 0;
    }
}

void WindDataStore::GetSolarRadSum(WindData& wd, int& sum)
{
    sum += wd.GetSolarRad();
}

float WindDataStore::GetsPCCWindSpeedMean(int month)
{
    itrMap it = m_bstMap.begin();
    wdBst tree;
    WindData wd;
    Date d;
    bool found = false;
    float sum = 0;
    int counter = 0;

    while(it != m_bstMap.end()) //iterate through every map element
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);

        if(d.GetMonth() == month) //find tree with matching month
        {
            found = true;
            tree.InorderTraversal(GetWindSpeedSum,sum);
            counter += tree.TreeNodeCount();
        }
        ++it;
    }

    if(found)
    {
        sum = sum / (float)counter;
        return sum;
    }
    else
    {
        return 0;
    }
}

float WindDataStore::GetsPCCAirTempMean(int month)
{
    itrMap it = m_bstMap.begin();
    wdBst tree;
    WindData wd;
    Date d;
    bool found = false;
    float sum = 0;
    int counter = 0;

    while(it != m_bstMap.end()) //iterate through every map element
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);

        if(d.GetMonth() == month) //find tree with matching month
        {
            found = true;
            tree.InorderTraversal(GetAirTempSum,sum);
            counter += tree.TreeNodeCount();
        }
        ++it;
    }

    if(found)
    {
        sum = sum / (float)counter;
        return sum;
    }
    else
    {
        return 0;
    }
}

float WindDataStore::GetsPCCSolarRadMean(int month)
{
    itrMap it = m_bstMap.begin();
    wdBst tree;
    WindData wd;
    Date d;
    bool found = false;
    int sum = 0;
    int counter = 0;

    while(it != m_bstMap.end()) //iterate through every map element
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);

        if(d.GetMonth() == month) //find tree with matching month
        {
            found = true;
            tree.InorderTraversal(GetSolarRadSum,sum);
            counter += tree.TreeNodeCount();
        }
        ++it;
    }

    if(found)
    {
        sum = sum / (float)counter;
        return sum;
    }
    else
    {
        return 0;
    }
}

float WindDataStore::CalculatesPCCS_T(int month)
{
    itrMap it = m_bstMap.begin();
    wdBst tree;
    WindData wd;
    Date d;

    //do windspeed first
    vector<float> wsVector;
    while(it != m_bstMap.end())
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);
        if(d.GetMonth() == month)
        {
            tree.InorderTraversal(GetWindSpeedVector,wsVector);
        }
        ++it;
    }

    float wsSum;
    float wsMean = GetsPCCWindSpeedMean(month);
    for(float speed : wsVector)
    {
        wsSum += (speed - wsMean) * (speed - wsMean);
    }

    //do airtemp
    it = m_bstMap.begin();
    vector<float> atVector;
    while(it != m_bstMap.end())
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);
        if(d.GetMonth() == month)
        {
            tree.InorderTraversal(GetAirTempVector,atVector);
        }
        ++it;
    }

    float atSum;
    float atMean = GetsPCCAirTempMean(month);
    for(float temp : atVector)
    {
        atSum += (temp - atMean) * (temp - atMean);
    }

    //find numerator
    float numerator = 0;
    for(int i = 0; i < atVector.size(); i++)
    {
        numerator += (wsVector.at(i) - wsMean) * (atVector.at(i) - atMean);
    }

    //find denominator
    float denominator = sqrt(wsSum*atSum);

    float sPCC = numerator/denominator;
    return sPCC;
}

void WindDataStore::GetSolarRadVector(WindData& wd, vector<int>& srv)
{
    srv.push_back(wd.GetSolarRad());
}

float WindDataStore::CalculatesPCCS_R(int month)
{
    itrMap it = m_bstMap.begin();
    wdBst tree;
    WindData wd;
    Date d;

    //do windspeed first
    vector<float> wsVector;
    while(it != m_bstMap.end())
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);
        if(d.GetMonth() == month)
        {
            tree.InorderTraversal(GetWindSpeedVector,wsVector);
        }
        ++it;
    }

    float wsSum;
    float wsMean = GetsPCCWindSpeedMean(month);
    for(float speed : wsVector)
    {
        wsSum += (speed - wsMean) * (speed - wsMean);
    }

    //do solarrad
    it = m_bstMap.begin();
    vector<int> srVector;
    while(it != m_bstMap.end())
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);
        if(d.GetMonth() == month)
        {
            tree.InorderTraversal(GetSolarRadVector,srVector);
        }
        ++it;
    }

    float srSum;
    float srMean = GetsPCCSolarRadMean(month);
    for(float rad : srVector)
    {
        srSum += (rad - srMean) * (rad - srMean);
    }

    //find numerator
    float numerator = 0;
    for(int i = 0; i < srVector.size(); i++)
    {
        numerator += (wsVector.at(i) - wsMean) * (srVector.at(i) - srMean);
    }

    //find denominator
    float denominator = sqrt(wsSum*srSum);

    float sPCC = numerator/denominator;
    return sPCC;
}

float WindDataStore::CalculatesPCCT_R(int month)
{
    itrMap it = m_bstMap.begin();
    wdBst tree;
    WindData wd;
    Date d;

    //do airtemp first
    vector<float> atVector;
    while(it != m_bstMap.end())
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);
        if(d.GetMonth() == month)
        {
            tree.InorderTraversal(GetAirTempVector,atVector);
        }
        ++it;
    }

    float atSum;
    float atMean = GetsPCCAirTempMean(month);
    for(float temp : atVector)
    {
        atSum += (temp - atMean) * (temp - atMean);
    }

    //do solarrad
    it = m_bstMap.begin();
    vector<int> srVector;
    while(it != m_bstMap.end())
    {
        tree = it->second;
        tree.GetRootElement(wd);
        wd.GetDate(d);
        if(d.GetMonth() == month)
        {
            tree.InorderTraversal(GetSolarRadVector,srVector);
        }
        ++it;
    }

    float srSum;
    float srMean = GetsPCCSolarRadMean(month);
    for(float rad : srVector)
    {
        srSum += (rad - srMean) * (rad - srMean);
    }

    //find numerator
    float numerator = 0;
    for(int i = 0; i < srVector.size(); i++)
    {
        numerator += (atVector.at(i) - atMean) * (srVector.at(i) - srMean);
    }

    //find denominator
    float denominator = sqrt(atSum*srSum);

    float sPCC = numerator/denominator;
    return sPCC;
}
