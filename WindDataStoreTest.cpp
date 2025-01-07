#include "WindDataStore.h"

using namespace std;

void Test01(WindDataStore &test);
void Test02(WindDataStore test);
void Test03(WindDataStore test);
void Test04(WindDataStore test);
void Test05(WindDataStore test);
void Test06(WindDataStore test);
void Test07(WindDataStore test);
void Test08(WindDataStore test);
void Test09(WindDataStore test);
void Test10(WindDataStore test);
void Test11(WindDataStore test);

int main()
{
    WindDataStore test;

    Test01(test);
    Test02(test);
    Test03(test);
    Test04(test);
    Test05(test);
    Test06(test);
    Test07(test);
    Test08(test);
    Test09(test);
    Test10(test);
    Test11(test);

    return 0;
}

void Test01(WindDataStore &test)
{
    cout << "=== Testing ReadInputFileToStorage() ===" << endl;
    test.ReadInputFileToStorage("data/testsample_data.csv");

    bstMap tm;
    test.GetMap(tm);
    itrMap it = tm.begin();
    while(it != tm.end())
    {
        wdBst tb;
        test.GetBst(tb,it);
        tb.InorderTraversal();
        ++it;
    }
    cout << endl;
}

void Test02(WindDataStore test)
{
    cout << "=== Testing CalculateWindSpeedMean() ===" << endl;
    cout << "Using March 2014" << endl;
    float mean = test.CalculateWindSpeedMean(3,2014);
    cout << "Speed Mean: " << mean << endl << endl;

    cout << "Using August 2014" << endl;
    mean = test.CalculateWindSpeedMean(8,2014);
    cout << "Speed Mean: " << mean << endl << endl;

    cout << "Using January 2015" << endl;
    mean = test.CalculateWindSpeedMean(1,2015);
    cout << "Speed Mean: " << mean << endl << endl;
}

void Test03(WindDataStore test)
{
    cout << "=== Testing CalculateWindSpeedSD() ===" << endl;
    cout << "Using March 2014" << endl;
    float sd = test.CalculateWindSpeedSD(3,2014);
    cout << "Speed SD: " << sd << endl << endl;

    cout << "Using August 2014" << endl;
    sd = test.CalculateWindSpeedSD(8,2014);
    cout << "Speed SD: " << sd << endl << endl;

    cout << "Using January 2015" << endl;
    sd = test.CalculateWindSpeedSD(1,2015);
    cout << "Speed SD: " << sd << endl << endl;
}

void Test04(WindDataStore test)
{
    cout << "=== Testing CalculateAirTempMean() ===" << endl;
    cout << "Using March 2014" << endl;
    float mean = test.CalculateAirTempMean(3,2014);
    cout << "Air Temp Mean: " << mean << endl << endl;

    cout << "Using August 2014" << endl;
    mean = test.CalculateAirTempMean(8,2014);
    cout << "Air Temp Mean: " << mean << endl << endl;

    cout << "Using January 2015" << endl;
    mean = test.CalculateAirTempMean(1,2015);
    cout << "Air Temp Mean: " << mean << endl << endl;
}

void Test05(WindDataStore test)
{
    cout << "=== Testing CalculateAirTempSD() ===" << endl;
    cout << "Using March 2014" << endl;
    float sd = test.CalculateAirTempSD(3,2014);
    cout << "Air Temp SD: " << sd << endl << endl;

    cout << "Using August 2014" << endl;
    sd = test.CalculateAirTempSD(8,2014);
    cout << "Air Temp SD: " << sd << endl << endl;

    cout << "Using January 2015" << endl;
    sd = test.CalculateAirTempSD(1,2015);
    cout << "Air Temp SD: " << sd << endl << endl;
}

void Test06(WindDataStore test)
{
    cout << "=== Testing CalculateSolarRadTotal() ===" << endl;
    cout << "Using March 2014" << endl;
    int sum = test.CalculateSolarRadTotal(3,2014);
    cout << "Solar Rad Total: " << sum << endl << endl;

    cout << "Using August 2014" << endl;
    sum = test.CalculateSolarRadTotal(8,2014);
    cout << "Solar Rad Total: " << sum << endl << endl;

    cout << "Using January 2015" << endl;
    sum = test.CalculateSolarRadTotal(1,2015);
    cout << "Solar Rad Total: " << sum << endl << endl;
}

void Test07(WindDataStore test)
{
    cout << "=== Testing wdBst Key ===" << endl;
    bstMap bm;
    wdBst wdtree;
    test.GetMap(bm);
    wdtree = bm.at("March2014");
    WindData wd;
    Date d;
    d.SetDate("1/3/2014");
    Time t;
    t.SetTime("9:40");
    wd.SetDate(d);
    wd.SetTime(t);
    if(wdtree.Get(wd))
    {
        cout << "Found" << endl;
        wd.GetDate(d);
        cout << wd << endl;
        cout << "Month Test: " << d.GetMonthString() << endl << endl;
    }

    else
        cout << "Not Found" << endl << endl;
}

void Test08(WindDataStore test)
{
    cout << "=== Testing bstMap Key ===" << endl;
    bstMap bm;
    wdBst wdtree;
    itrMap it;

    test.GetMap(bm);
    it = bm.find("March2014");
    if(it != bm.end())
        cout << "Found" << endl << endl;
    else
        cout << "Not Found" << endl << endl;
}

void Test09(WindDataStore test)
{
    cout << "=== Testing CalculatesPCCS_T ===" << endl;
    cout << "Using March" << endl;
    cout << "sPCC S_T: " << test.CalculatesPCCS_T(3) << endl << endl;
}

void Test10(WindDataStore test)
{
    cout << "=== Testing GetsPCCAirTempMean ===" << endl;
    cout << "Using March" << endl;
    cout << "sPCC S_R: " << test.CalculatesPCCS_R(3) << endl << endl;
}

void Test11(WindDataStore test)
{
    cout << "=== Testing GetsPCCSolarRadMean ===" << endl;
    cout << "Using March" << endl;
    cout << "sPCC T_R: " << test.CalculatesPCCT_R(3) << endl << endl;
}

