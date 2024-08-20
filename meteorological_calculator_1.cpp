/*******************************************************************************
* 
* meteorological_calculator_1.cpp:
* This is a C++ code to calculate the meteorological parameters. In particular,
* it generates the Synop code that can be sent as a meteorological report.
*
* Author:
* Kazem Rezazadeh (kazem.rezazadeh@ipm.ir)
*
* Purpose:
* Calculation of meteorological parameters and generation of the Synop code
* 
* Usage:
* First enter the input parameters in the "input.txt" file. Then execute the 
* program. The results are written to the file "output.txt". The results 
* contain some meteorological parameters and the Synop code.
*
* Source:
* https://github.com/krezazadeh/meteorological_calculator
* 
* Last update:
* 2024/August/20
*
*******************************************************************************/

#include <iostream>
// #include <stdio.h>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

string remove_space(string);
string read_data(string);

int main()
{
    // Constants

    const double g = 9.7803267715;
    const double R = 287.052874;
    const double R_gas = 8.31446261815324;
    const double alpha_Hg = 0.0002328204008876278; 
    const double A_Tdew = 6.116441;
    const double m_Tdew = 7.591386;
    const double Tn_Tdew = 240.7263;
    const double K_Tdew = 0.0008;
    const double M_air = 0.029;
    const double L_Temp = 0.0065;

    // Station parameters

    string Station_Name = read_data("Station_Name");
    string Station_ID = read_data("Station_ID");
    int Station_Number = stoi(read_data("Station_Number"));
    double Lat = stod(read_data("Lat"));
    double Lon = stod(read_data("Lon"));
    double Elevation = stod(read_data("Elevation"));

    // Date and Time
    
    int Date_Year = stoi(read_data("Date_Year"));
    int Date_Month = stoi(read_data("Date_Month"));
    int Date_Day = stoi(read_data("Date_Day"));
    string Date_Day_str;
    int Time_Hour = stoi(read_data("Time_Hour"));
    string Time_Hour_str;

    // Meteorological parameters
    
    int Ir = stoi(read_data("Ir"));
    int Ix = stoi(read_data("Ix"));
    
    string Cloud_N_str = read_data("Cloud_N");
    int Cloud_N;
    // int Cloud_N = stoi(Cloud_N_str);
    string Cloud_H_str = read_data("Cloud_H");
    int Cloud_H;
    // int Cloud_H = stoi(Cloud_H_str);
    
    int Visibility = stoi(read_data("Visibility"));
    // string Min_Vis_Dir = read_data("Min_Vis_Dir");
    
    int Wind_Direction = stoi(read_data("Wind_Direction"));
    int Wind_Speed = stoi(read_data("Wind_Speed"));
    
    double Dry_Temp = round(stod(read_data("Dry_Temp"))*10.0)/10.0;
    double Wet_Temp = round(stod(read_data("Wet_Temp"))*10.0)/10.0;

    double T_12 = round(stod(read_data("T_12"))*10.0)/10.0; 
    
    double QFE;
    string QFE_str = read_data("QFE");
    
    double B_Pressure;
    double B_Temp;
    
    int Pr_Tendency = stoi(read_data("Pr_Tendency"));
    double Pr_Change;
    string Pr_Change_str = read_data("Pr_Change");
    
    double QFE_180;

    // SM

    double Rain_6h;
    int Rain_Period_6h;

    // SM, SI

    double Rain_3h;
    double Rain_24h;

    // SN
    
    double Rain_1h;
    int Rain_Period_1h;
    
    int WW;
    int W1;
    int W2;
    
    // Clouds
    
    int Cloud1 = 0;
    string Cloud1_str = read_data("Cloud1");
    int Cloud_Name1;
    string Cloud_Name1_str = read_data("Cloud_Name1");
    int Cloud_Type1;
    string Cloud_Type1_str = read_data("Cloud_Type1");
    int Cloud_H1 = stoi(read_data("Cloud_H1"));
    
    int Cloud2 = 0;
    string Cloud2_str = read_data("Cloud2");
    int Cloud_Name2;
    string Cloud_Name2_str = read_data("Cloud_Name2");
    int Cloud_Type2;
    string Cloud_Type2_str = read_data("Cloud_Type2");
    int Cloud_H2 = stoi(read_data("Cloud_H2"));
    
    int Cloud3 = 0;
    string Cloud3_str = read_data("Cloud3");
    int Cloud_Name3;
    string Cloud_Name3_str = read_data("Cloud_Name3");
    int Cloud_Type3;
    string Cloud_Type3_str = read_data("Cloud_Type3");
    int Cloud_H3 = stoi(read_data("Cloud_H3"));
    
    int Cloud4 = 0;
    string Cloud4_str = read_data("Cloud4");
    int Cloud_Name4;
    string Cloud_Name4_str = read_data("Cloud_Name4");
    int Cloud_Type4;
    string Cloud_Type4_str = read_data("Cloud_Type4");
    int Cloud_H4 = stoi(read_data("Cloud_H4"));
    
    int Cloud5 = 0;
    string Cloud5_str = read_data("Cloud5");
    int Cloud_Name5;
    string Cloud_Name5_str = read_data("Cloud_Name5");
    int Cloud_Type5;
    string Cloud_Type5_str = read_data("Cloud_Type5");
    int Cloud_H5 = stoi(read_data("Cloud_H5"));
    
    int Nhs;
    string Nhs_str = read_data("Nhs");
    string Nhs_str_new;

    // SM06
    
    int Ground_Status;
    double Ground_Temp;
    
    double Evaporation;
    string Evaporation_str;
    int Evap_Device;

    // SI03, SI15
    
    double Min_Temp;
    double Max_Temp;

    // SI03, SI09, SI15
    
    double Soil_T5;
    double Soil_T10;
    double Soil_T20;
    double Soil_T30;
    double Soil_T50;
    double Soil_T100;

    //

    string Synop_Code;
    
    int IRIXhvv;
    string IRIXhvv_str;
    int vv;
    string vv_str;
    int nddff;
    string dd_str;
    string ff_str;
    string nddff_str;
    int OneSnTTT;
    int Sn;
    int ThreeP0P0P0P0;
    double QNH;
    double Tdry;
    double Twet;
    double Pws;
    double Pw;   
    double RH;
    double Tdew;
    int TwoSnTdTdTd;
    double QFF;
    int FourPPPP;
    int FiveaPPP;
    double H850;
    int SixRRRTR;
    int SevenWWW1W2;
    int EightNHCLCMCH;

    // 333

    int OneSnTxTxTx;
    int TwoSnTnTnTn;
    int ThreeESnTgTg;
    int FiveEEEiE;
    int SevenR24R24R24R24;
    string EightNHCLCMCH_str;
    int EightNsChshs1;
    int EightNsChshs2;
    int EightNsChshs3;
    int EightNsChshs4;

    // 555

    int OneSnTwTwTw;
    int TwoNineRHRHRH;
    
    // 66666
    
    int ZeroSnT5T5T5;
    string ZeroSnT5T5T5_str;
    int OneSnT10T10T10;
    int TwoSnT20T20T20;
    int ThreeSnT30T30T30;
    int FiveSnT50T50T50;
    int NineSnT100T100T100;

    FILE *outputFile;

    //

    
    
    // outputFile = fopen("output.txt", "w");

    // string mystring = "one\ntwo\nthree\n=NNNN";

    // fprintf(outputFile, "%s", mystring.c_str());
    
    // fclose(outputFile);

    // return 0;

    
    
    Synop_Code = "ZCZC\n";

    if(Ir == 1)
    {
        Synop_Code = Synop_Code + "SMIR40";
    }
    else if((Ir == 4) and ((Time_Hour == 3) or (Time_Hour == 9) or (Time_Hour == 15) or (Time_Hour == 21)))
    {
        Synop_Code = Synop_Code + "SIIR41";
    }
    else if((Ir == 2) or (Ir == 4))
    {
        Synop_Code = Synop_Code + "SNIR42";
    }

    if(Date_Day < 10)
    {
        Date_Day_str = "0" + to_string(Date_Day);
    }
    else
    {
        Date_Day_str = to_string(Date_Day);
    }

    if(Time_Hour < 10)
    {
        Time_Hour_str = "0" + to_string(Time_Hour);
    }
    else
    {
        Time_Hour_str = to_string(Time_Hour);
    }

    Synop_Code = Synop_Code + " " + Station_ID + " " + Date_Day_str + Time_Hour_str + "00" + "\n";
    
    Synop_Code = Synop_Code + "AAXX" + " " + Date_Day_str + Time_Hour_str + "1" + "\n";

    Synop_Code = Synop_Code + to_string(Station_Number);
    
    if((Visibility < 0) or (Visibility > 75000))
    {
        cout << "Error: The visibility should be in the range 0-75000." << endl;
        return(0);
    }
    
    if((Visibility >= 0) and (Visibility <= 5000))
    {
        vv = Visibility/100;
    }
    else if((Visibility >= 6000) and (Visibility <= 30000))
    {
        vv = 50 + Visibility/1000;
    }
    else if((Visibility >= 35000) and (Visibility <= 75000))
    {
        vv = 80 + (Visibility - 30000)/5000;
    }
    
    // IRIXhvv = Ir*10000 + Ix*1000 + Cloud_H*100 + vv;
    // cout << "IRIXhvv = " << IRIXhvv << endl;

    if(vv < 10)
    {
      vv_str = "0" + to_string(vv);  
    }
    else
    {
        vv_str = to_string(vv);        
    }

    IRIXhvv_str = to_string(Ir) +  to_string(Ix) + Cloud_H_str + vv_str;

    Synop_Code = Synop_Code + " " + IRIXhvv_str;

    // nddff = Cloud_N*10000 + (Wind_Direction/10)*100 + Wind_Speed;

    // cout << "nddff = " << nddff << endl;

    if((Wind_Direction/10) < 10)
    {
        dd_str = "0" + to_string(Wind_Direction/10);
    }
    else
    {
        dd_str = to_string(Wind_Direction/10);
    }

    if(Wind_Speed < 10)
    {
        ff_str = "0" + to_string(Wind_Speed);
    }
    else
    {
        ff_str = to_string(Wind_Speed);
    }

    nddff_str = Cloud_N_str + dd_str + ff_str;

    Synop_Code = Synop_Code + " " +  nddff_str;

    if(Dry_Temp >= 0.0)
    {
        Sn = 0;
    }
    else
    {
        Sn = 1;
    }

    OneSnTTT = 10000 + Sn*1000 + round(abs(Dry_Temp)*10);

    // cout << "OneSnTTT = " << OneSnTTT << endl;

    Synop_Code = Synop_Code + " " + to_string(OneSnTTT);

    if(QFE_str != "calc")
    {
        QFE = stod(QFE_str);
    }
    else
    {
        B_Pressure = stod(read_data("B_Pressure"));
        B_Temp = stod(read_data("B_Temp"));

        // Calculation of QFE
        // Correction due to the linear heat expansion of mercury (Hg)

        QFE = B_Pressure/(1 + alpha_Hg*B_Temp);
    }
    
    // cout << "QFE = " << QFE << endl;

    ThreeP0P0P0P0 = 30000 + int(round(QFE*10.0));

    // cout << "ThreeP0P0P0P0 = " << ThreeP0P0P0P0 << endl;

    // Calculation of Tdew, RH
    // Using the equations from: https://www.metpod.co.uk/calculators/dew-point/

    Tdry = Dry_Temp;

    Twet = Wet_Temp;

    if (Twet > Tdry)
    {
        cout << "Error: Wet_Temp should be less than or equal to Dry_Temp." << endl;
        exit(0);
    }

    Pws = A_Tdew*pow(10.0, (m_Tdew*Twet)/(Twet + Tn_Tdew));

    Pw = Pws - (K_Tdew*QFE*(Tdry - Twet));

    Tdew = Tn_Tdew/(-1.0 + (m_Tdew*log(10))/log(Pw/A_Tdew));

    Pws = A_Tdew*pow(10.0, (m_Tdew*Tdry)/(Tdry + Tn_Tdew));

    RH = 100.0*(Pw/Pws);

    if(Tdew >= 0.0)
    {
        Sn = 0;
    }
    else
    {
        Sn = 1;
    }

    TwoSnTdTdTd = 20000 + Sn*1000 + round(abs(Tdew)*10);

    // cout << "RH = " << round(RH) << endl;

    // cout << "Tdew = " << double(round(Tdew*10))/10.0 << endl;

    // cout << "VP = " << double(round(Pw*10))/10.0 << endl;

    // cout << "TwoSnTdTdTd = " << TwoSnTdTdTd << endl;

    Synop_Code = Synop_Code + " " + to_string(TwoSnTdTdTd);

    Synop_Code = Synop_Code + " " + to_string(ThreeP0P0P0P0);

    // https://docs.vaisala.com/r/M211676EN-G/en-US/GUID-D9BCDC5D-9C4A-4FF7-830E-A5841C3007BE/GUID-5B047C37-CC21-4172-81B1-3C5243657B7F

    QNH = 1013.25*pow(1.0 - (0.0065*(44330.77 - 11880.32*pow(QFE, 0.190263) - Elevation))/288.15, 5.25588);

    // cout << "QNH = " << round(QNH*10.0)/10.0 << endl;

    // https://docs.vaisala.com/r/M211676EN-G/en-US/GUID-D9BCDC5D-9C4A-4FF7-830E-A5841C3007BE/GUID-5B047C37-CC21-4172-81B1-3C5243657B7F

    // QFF = QFE*exp((g*Elevation)/(R*(Pw*(0.1074 + 0.0000251*Elevation) + (0.0065*Elevation)/2.0 + (Dry_Temp + 273.15))));

    QFF = QFE*exp((g*Elevation)/(R*(Pw*(0.1074 + 0.0000251*Elevation) + (0.0065*Elevation)/2.0 + ((Dry_Temp + T_12)/2.0 + 273.15))));

    // cout << "QFF = " << round(QFF*10.0)/10.0 << endl;

    FourPPPP = 40000 + int(round(QFF*10.0));

    // cout << "FourPPPP = " << FourPPPP << endl;

    Synop_Code = Synop_Code + " " + to_string(FourPPPP);
    
    if(Pr_Change_str != "calc")
    {
        Pr_Change = stod(Pr_Change_str);
    }
    else
    {
        QFE_180 = stod(read_data("QFE_180"));
        Pr_Change = abs(QFE - QFE_180);
    }

    // cout << "Pr_Change = " << Pr_Change << endl;

    FiveaPPP = 50000 + Pr_Tendency*1000 + int(round(Pr_Change*10));

    // cout << "FiveaPPP = " << FiveaPPP << endl;

    Synop_Code = Synop_Code + " " + to_string(FiveaPPP); 

    // H850

    H850 = (Elevation*L_Temp + (Dry_Temp + 273.15) - pow(850.0, (L_Temp*R_gas)/(g*M_air))*pow(1.0/QFE, (L_Temp*R_gas)/(g*M_air))*(Dry_Temp + 273.15))/L_Temp;

    // cout << "H850 = " << round(H850*10.0)/10.0 << endl;

    // flag

    if(Ir == 1)
    {
        Rain_6h = stod(read_data("Rain_6h"));
        Rain_Period_6h = stoi(read_data("Rain_Period_6h"));
        
        SixRRRTR = 60000 + 1000*int(round(Rain_6h*10.0)) + Rain_Period_6h;

        // cout << "SixRRRTR = " << SixRRRTR << endl;

        Synop_Code = Synop_Code + " " + to_string(SixRRRTR);
    }

    if((Ix == 1) or (Visibility < 10000))
    {
        WW = stoi(read_data("WW"));
        W1 = stoi(read_data("W1"));
        W2 = stoi(read_data("W2"));

        SevenWWW1W2 = 70000 + 100*WW + 10*W1 + W2;

        // cout << "SevenWWW1W2 = " << SevenWWW1W2 << endl;

        Synop_Code = Synop_Code + " " + to_string(SevenWWW1W2);
    }

    if(Cloud1_str != "/")
    {
        Cloud_Name1 = stoi(Cloud_Name1_str);
        Cloud_Type1 = stoi(Cloud_Type1_str);
        
        if(Cloud1_str == "TR")
        {
            Cloud1 = 1;
        }
        else
        {
            Cloud1 = stoi(Cloud1_str);
        }
    }
    else
    {
        Cloud1 = 0;
    }
    
    if(Cloud2_str != "/")
    {
        Cloud_Name2 = stoi(Cloud_Name2_str);
        Cloud_Type2 = stoi(Cloud_Type2_str);

        if(Cloud2_str == "TR")
        {
            Cloud2 = 1;
        }
        else
        {
            Cloud2 = stoi(Cloud2_str);
        }
    }
    else
    {
        Cloud2 = 0;
    }

    if(Cloud3_str != "/")
    {
        Cloud_Name3 = stoi(Cloud_Name3_str);
        Cloud_Type3 = stoi(Cloud_Type3_str);

        if(Cloud3_str == "TR")
        {
            Cloud3 = 1;
        }
        else
        {
            Cloud3 = stoi(Cloud3_str);
        }
    }
    else
    {
        Cloud3 = 0;
    }

    if(Cloud4_str != "/")
    {
        Cloud_Name4 = stoi(Cloud_Name4_str);
        Cloud_Type4 = stoi(Cloud_Type4_str);

        if(Cloud4_str == "TR")
        {
            Cloud4 = 1;
        }
        else
        {
            Cloud4 = stoi(Cloud4_str);
        }
    }
    else
    {
        Cloud4 = 0;
    }

    if(Cloud5_str != "/")
    {
        Cloud_Name5 = stoi(Cloud_Name5_str);
        Cloud_Type5 = stoi(Cloud_Type5_str);

        if(Cloud5_str == "TR")
        {
            Cloud5 = 1;
        }
        else
        {
            Cloud5 = stoi(Cloud5_str);
        }
    }
    else
    {
        Cloud5 = 0;
    }

    if((Cloud1 == 8) or (Cloud2 == 8) or (Cloud3 == 8))
    {
        Cloud4_str = "/";
        Cloud4 = 0;
        Cloud_Name4_str = "/";
        Cloud_Type4_str = "/";
        Cloud5_str = "/";
        Cloud5 = 0;
        Cloud_Name5_str = "/";
        Cloud_Type5_str = "/";
    }
    else if(Cloud4 == 8)
    {
        Cloud5_str = "/";
        Cloud5 = 0;
        Cloud_Name5_str = "/";
        Cloud_Type5_str = "/";
    }

    if((Cloud1 > 0) or (Cloud4 > 0) or (Cloud5 > 0))
    {
        
        if(Nhs_str == "TR")
        {
            Nhs_str_new = "1";
        }
        else
        {
            Nhs_str_new = Nhs_str;
        }

        EightNHCLCMCH_str = "8" + Nhs_str_new + Cloud_Type1_str + Cloud_Type4_str + Cloud_Type5_str;

        // cout << "EightNHCLCMCH_str = " << EightNHCLCMCH_str << endl;

        Synop_Code = Synop_Code + " " + EightNHCLCMCH_str;
    }

    // return(0);
    // exit(0);

    // cout << Synop_Code << endl;
    // return(0);

    // 333

    Synop_Code = Synop_Code + " " + "333"; 

    // SI03, SI15

    if((Ir == 4) and ((Time_Hour == 3) or (Time_Hour == 15)))
    {
        Min_Temp = stod(read_data("Min_Temp"));
        Max_Temp = stod(read_data("Max_Temp"));

        if(Max_Temp >= 0.0)
        {
            OneSnTxTxTx =  10000 + round(abs(Max_Temp)*10);
        }
        else
        {
            OneSnTxTxTx =  11000 + round(abs(Max_Temp)*10);
        }

        // cout <<  "OneSnTxTxTx = " << OneSnTxTxTx << endl;

        Synop_Code = Synop_Code + " " + to_string(OneSnTxTxTx);

        if(Min_Temp >= 0.0)
        {
            TwoSnTnTnTn =  20000 + round(abs(Min_Temp)*10);
        }
        else
        {
             TwoSnTnTnTn =  21000 + round(abs(Min_Temp)*10);
        }

        // cout <<  "TwoSnTnTnTn = " << TwoSnTnTnTn << endl;

        Synop_Code = Synop_Code + " " + to_string(TwoSnTnTnTn);
    }

    // SM06

    if((Ir == 1) and (Time_Hour == 6))
    {
        Ground_Status = stoi(read_data("Ground_Status"));
        Ground_Temp = stod(read_data("Ground_Temp"));

        if(Ground_Temp >= 0)
        {
            Sn = 0;
        }
        else
        {
            Sn = 1;
        }

        ThreeESnTgTg = 30000 + 1000*Ground_Status + 100*Sn + round(abs(Ground_Temp));

        // cout << "ThreeESnTgTg = " << ThreeESnTgTg << endl;

        Synop_Code = Synop_Code + " " + to_string(ThreeESnTgTg); 

        Evaporation_str = read_data("Evaporation");
        Evap_Device = stoi(read_data("Evap_Device"));

        if(Evaporation_str != "/")
        {
            Evaporation = stod(Evaporation_str);
            FiveEEEiE = 50000 + 10*round(Evaporation*10.0) + Evap_Device;

            // cout << "FiveEEEiE = " << FiveEEEiE << endl;

            Synop_Code = Synop_Code + " " + to_string(FiveEEEiE);
        }
        else
        {
            // cout << "FiveEEEiE = " << 5 << "///" <<  Evap_Device << endl;

            Synop_Code = Synop_Code + " " + "5///" + to_string(Evap_Device);
        }

    }

    // Rain_1h

    if(Ir == 2)
    {
        Rain_1h = stod(read_data("Rain_1h"));
        Rain_Period_1h = stoi(read_data("Rain_Period_1h"));
        
        SixRRRTR = 60000 + 1000*int(round(Rain_1h*10.0)) + Rain_Period_1h;

        // cout << "SixRRRTR = " << SixRRRTR << endl;

        Synop_Code = Synop_Code + " " + to_string(SixRRRTR);
    }

    // Rain_24h

    if(Ir == 1)
    {
        Rain_3h = stod(read_data("Rain_3h"));
        Rain_24h = stod(read_data("Rain_24h"));

        SevenR24R24R24R24 = 70000 + int(round(Rain_24h*10.0));

        // cout << "SevenR24R24R24R24 = " << SevenR24R24R24R24 << endl;

        Synop_Code = Synop_Code + " " + to_string(SevenR24R24R24R24);
    }

    if((Ir == 4) and ((Time_Hour == 3) or (Time_Hour == 9) or (Time_Hour == 15) or (Time_Hour == 21)))
    {
        Rain_3h = stod(read_data("Rain_3h"));
        Rain_24h = stod(read_data("Rain_24h"));

        SevenR24R24R24R24 = 70000 + int(round(Rain_24h*10.0));

        // cout << "SevenR24R24R24R24 = " << SevenR24R24R24R24 << endl;

        Synop_Code = Synop_Code + " " + to_string(SevenR24R24R24R24);
    }

    // Clouds

    if((Cloud1_str == "/") or (Cloud1_str == "TR"))
    {
        Cloud1 = 0;
    }
    else

    if((Cloud2_str == "/") or (Cloud2_str == "TR"))
    {
        Cloud2 = 0;
    }

    if((Cloud3_str == "/") or (Cloud3_str == "TR"))
    {
        Cloud3 = 0;
    }

    if((Cloud4_str == "/") or (Cloud4_str == "TR"))
    {
        Cloud4 = 0;
    }

    if((Cloud5_str == "/") or (Cloud5_str == "TR"))
    {
        Cloud5 = 0;
    }

    EightNsChshs1 = 0;
    EightNsChshs2 = 0;
    EightNsChshs3 = 0;
    EightNsChshs4 = 0;

    if((Cloud1 >= 1))
    {   
        EightNsChshs1 = 80000 + 1000*Cloud1 + 100*Cloud_Name1 + Cloud_H1;
    }
    else if((Cloud1 < 1) and (Cloud2 >= 1))
    {   
        EightNsChshs1 = 80000 + 1000*Cloud2 + 100*Cloud_Name2 + Cloud_H2;
    }
    else if((Cloud1 < 1) and (Cloud2 < 1) and (Cloud3 >= 1))
    {
        EightNsChshs1 = 80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3;
    }
    else if((Cloud1 < 1) and (Cloud2 < 1) and (Cloud3 < 1) and (Cloud4 >= 1))
    {
        EightNsChshs1 = 80000 + 1000*Cloud4 + 100*Cloud_Name4 + Cloud_H4;
    }
    else if((Cloud1 < 1) and (Cloud2 < 1) and (Cloud3 < 1) and (Cloud4 < 1) and (Cloud5 >= 1))
    {
        EightNsChshs1 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }

    if(EightNsChshs1 > 0)
    { 
        // cout << "EightNsChshs1 = " << EightNsChshs1 << endl;

        Synop_Code = Synop_Code + " " + to_string(EightNsChshs1); 
    }

    if((Cloud1 >= 1) and (Cloud2 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud2 + 100*Cloud_Name2 + Cloud_H2;
    }
    else if((Cloud1 >= 1) and (Cloud2 < 3) and (Cloud3 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3;
    }
    else if((Cloud1 >= 1) and (Cloud2 < 3) and (Cloud3 < 3) and (Cloud4 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud4 + 100*Cloud_Name4 + Cloud_H4;
    }
    else if((Cloud1 >= 1) and (Cloud2 < 3) and (Cloud3 < 3) and (Cloud4 < 3) and (Cloud5 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }
    else if((Cloud1 < 1) and (Cloud2 >= 1) and (Cloud3 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3;
    }
    else if((Cloud1 < 1) and (Cloud2 >= 1) and (Cloud3 < 3) and (Cloud4 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud4 + 100*Cloud_Name4 + Cloud_H4;
    }
    else if((Cloud1 < 1) and (Cloud2 >= 1) and (Cloud3 < 3) and (Cloud4 < 3) and (Cloud5 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }
    else if((Cloud1 < 1) and (Cloud2 < 1) and (Cloud3 >= 1) and (Cloud4 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud4 + 100*Cloud_Name4 + Cloud_H4;
    }
    else if((Cloud1 < 1) and (Cloud2 < 1) and (Cloud3 >= 1) and (Cloud4 < 3) and (Cloud5 >= 3))
    {
        EightNsChshs2 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }

    if(EightNsChshs2 > 0)
    { 
        // cout << "EightNsChshs2 = " << EightNsChshs2 << endl;

        Synop_Code = Synop_Code + " " + to_string(EightNsChshs2);
    }

    if((Cloud1 >= 1) and (Cloud2 >= 3) and (Cloud3 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3;
    }
    else if((Cloud1 >= 1) and (Cloud2 >= 3) and (Cloud3 < 5) and (Cloud4 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud4 + 100*Cloud_Name4 + Cloud_H4;
    }
    else if((Cloud1 >= 1) and (Cloud2 >= 3) and (Cloud3 < 5) and (Cloud4 <5) and (Cloud5 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }
    else if((Cloud1 >= 1) and (Cloud2 < 3) and (Cloud3 >= 3) and (Cloud4 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud4 + 100*Cloud_Name4 + Cloud_H4;
    }
    else if((Cloud1 >= 1) and (Cloud2 < 3) and (Cloud3 >= 3) and (Cloud4 <5) and (Cloud5 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }
    else if((Cloud1 >= 1) and (Cloud2 < 3) and (Cloud3 < 3) and (Cloud4 >= 3) and (Cloud5 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }
    else if((Cloud1 < 1) and (Cloud2 >= 1) and (Cloud3 >= 3) and (Cloud4 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud4 + 100*Cloud_Name4 + Cloud_H4;
    }
    else if((Cloud1 < 1) and (Cloud2 >= 1) and (Cloud3 >= 3) and (Cloud4 < 5) and (Cloud5 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }
    else if((Cloud1 < 1) and (Cloud2 >= 1) and (Cloud3 < 3) and (Cloud4 >= 3) and (Cloud5 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }
    else if((Cloud1 < 1) and (Cloud2 < 1) and (Cloud3 >= 1) and (Cloud4 >= 3) and (Cloud5 >= 5))
    {
        EightNsChshs3 = 80000 + 1000*Cloud5 + 100*Cloud_Name5 + Cloud_H5;
    }

    if(EightNsChshs3 > 0)
    { 
        // cout << "EightNsChshs3 = " << EightNsChshs3 << endl;

        Synop_Code = Synop_Code + " " + to_string(EightNsChshs3);
    }

    if(((Cloud_Type1 == 3) or (Cloud_Type1 == 9)) and (EightNsChshs1 != (80000 + 1000*Cloud1 + 100*Cloud_Name1 + Cloud_H1)) and (EightNsChshs2 != (80000 + 1000*Cloud1 + 100*Cloud_Name1 + Cloud_H1)) and (EightNsChshs3 != (80000 + 1000*Cloud1 + 100*Cloud_Name1 + Cloud_H1)))
    {
        EightNsChshs4 = 80000 + 1000*Cloud1 + 100*Cloud_Name1 + Cloud_H1;
    }
    else if(((Cloud_Type2 == 3) or (Cloud_Type2 == 9)) and (EightNsChshs1 != (80000 + 1000*Cloud2 + 100*Cloud_Name2 + Cloud_H2)) and (EightNsChshs2 != (80000 + 1000*Cloud2 + 100*Cloud_Name2 + Cloud_H2)) and (EightNsChshs3 != (80000 + 1000*Cloud2 + 100*Cloud_Name2 + Cloud_H2)))
    {
        EightNsChshs4 = 80000 + 1000*Cloud2 + 100*Cloud_Name2 + Cloud_H2;
    }
    else if(((Cloud_Type3 == 3) or (Cloud_Type3 == 9)) and (EightNsChshs1 != (80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3)) and (EightNsChshs2 != (80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3)) and (EightNsChshs3 != (80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3)))
    {
        EightNsChshs4 = 80000 + 1000*Cloud3 + 100*Cloud_Name3 + Cloud_H3;
    }

    if(EightNsChshs4 > 0)
    { 
        // cout << "EightNsChshs4 = " << EightNsChshs4 << endl;

        Synop_Code = Synop_Code + " " + to_string(EightNsChshs4);
    }

    // 555

    Synop_Code = Synop_Code + " " + "555";

    if(Wet_Temp >= 0.0)
    {
        Sn = 0;
    }
    else
    {
        Sn = 1;
    }

    OneSnTwTwTw = 10000 + 1000*Sn + int(round(abs(Wet_Temp)*10));

    // cout << "OneSnTwTwTw = " << OneSnTwTwTw << endl;

    Synop_Code = Synop_Code + " " + to_string(OneSnTwTwTw);

    TwoNineRHRHRH = 29000 + int(round(RH));

    // cout << "TwoNineRHRHRH = " << TwoNineRHRHRH << endl;

    Synop_Code = Synop_Code + " " + to_string(TwoNineRHRHRH);

    // 66666

    if((Ir == 4) and ((Time_Hour == 3) or (Time_Hour == 9) or (Time_Hour == 15)))
    {
        Synop_Code = Synop_Code + " " + "66666";
        
        Soil_T5 = stod(read_data("Soil_T5"));
        Soil_T10 = stod(read_data("Soil_T10"));
        Soil_T20 = stod(read_data("Soil_T20"));
        Soil_T30 = stod(read_data("Soil_T30"));
        Soil_T50 = stod(read_data("Soil_T50"));
        Soil_T100 = stod(read_data("Soil_T100"));

        if(Soil_T5 >= 0)
        {
            ZeroSnT5T5T5_str = "00" + to_string(int(round(abs(Soil_T5)*10)));
        }
        else
        {
            ZeroSnT5T5T5_str = "01" + to_string(int(round(abs(Soil_T5)*10)));
        }

        // cout << "ZeroSnT5T5T5_str = " << ZeroSnT5T5T5_str << endl;

        Synop_Code = Synop_Code + " " + ZeroSnT5T5T5_str;

        if(Soil_T10 >= 0)
        {
            OneSnT10T10T10 = 10000 + round(abs(Soil_T10)*10);
        }
        else
        {
            OneSnT10T10T10 = 11000 + round(abs(Soil_T10)*10);
        }

        // cout << "OneSnT10T10T10 = " << OneSnT10T10T10 << endl;

        Synop_Code = Synop_Code + " " + to_string(OneSnT10T10T10);

        if(Soil_T20 >= 0)
        {
            TwoSnT20T20T20 = 20000 + round(abs(Soil_T20)*10);
        }
        else
        {
            TwoSnT20T20T20 = 21000 + round(abs(Soil_T20)*10);
        }

        // cout << "TwoSnT20T20T20 = " << TwoSnT20T20T20 << endl;

        Synop_Code = Synop_Code + " " + to_string(TwoSnT20T20T20);

        if(Soil_T30 >= 0)
        {
            ThreeSnT30T30T30 = 30000 + round(abs(Soil_T30)*10);
        }
        else
        {
            ThreeSnT30T30T30 = 31000 + round(abs(Soil_T30)*10);
        }

        // cout << "ThreeSnT30T30T30 = " << ThreeSnT30T30T30 << endl;

        Synop_Code = Synop_Code + " " + to_string(ThreeSnT30T30T30);

        if(Soil_T50 >= 0)
        {
            FiveSnT50T50T50 = 50000 + round(abs(Soil_T50)*10);
        }
        else
        {
            FiveSnT50T50T50 = 51000 + round(abs(Soil_T50)*10);
        }

        // cout << "FiveSnT50T50T50 = " << FiveSnT50T50T50 << endl;

        Synop_Code = Synop_Code + " " + to_string(FiveSnT50T50T50);

        if(Soil_T100 >= 0)
        {
            NineSnT100T100T100 = 90000 + round(abs(Soil_T100)*10);
        }
        else
        {
            NineSnT100T100T100 = 91000 + round(abs(Soil_T100)*10);
        }

        // cout << "NineSnT100T100T100 = " << NineSnT100T100T100 << endl;

        Synop_Code = Synop_Code + " " + to_string(NineSnT100T100T100);

    }

    Synop_Code = Synop_Code + "=\n";

    Synop_Code = Synop_Code + "NNNN" + "\n";

    // outputFile = fopen("output.txt", "w");

    // string mystring = "one\ntwo\nthree\n=NNNN";

    // fprintf(outputFile, "%s", mystring.c_str());
    
    // fclose(outputFile);

    // return(0);
    // exit(0);

    outputFile = fopen("output.txt", "w");

    fprintf(outputFile, "%s %s\n", "Station_Name = ", Station_Name.c_str());
    fprintf(outputFile, "%s %s\n", "Station_ID = ", Station_ID.c_str());
    fprintf(outputFile, "%s %i\n", "Station_Number = ", Station_Number);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %i\n", "Date_Year = ", Date_Year);
    fprintf(outputFile, "%s %i\n", "Date_Month = ", Date_Month);
    fprintf(outputFile, "%s %i\n", "Date_Day = ", Date_Day);
    fprintf(outputFile, "%s %i\n", "Time_Hour = ", Time_Hour);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %i\n", "Ir = ", Ir);
    fprintf(outputFile, "%s %i\n", "Ix = ", Ix);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %i\n", "Wind_Direction = ", Wind_Direction);
    fprintf(outputFile, "%s %i\n", "Wind_Speed = ", Wind_Speed);
    fprintf(outputFile, "%s %i\n", "Visibility = ", Visibility);
    fprintf(outputFile, "\n");

    if((Ix == 1) or (Visibility < 10000))
    {
        fprintf(outputFile, "%s %i\n", "WW = ", WW);
        fprintf(outputFile, "%s %i\n", "W1 = ", W1);
        fprintf(outputFile, "%s %i\n", "W2 = ", W2);
        fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "%s %s\n", "Cloud_N = ", Cloud_N_str.c_str());
    fprintf(outputFile, "\n");

    if((Cloud1_str != "/") and (Cloud1_str != "0"))
    {
        fprintf(outputFile, "%s %s\n", "Cloud1 = ", Cloud1_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Name1 = ", Cloud_Name1_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Type1 = ", Cloud_Type1_str.c_str());
        fprintf(outputFile, "%s %i\n", "Cloud_H1 = ", Cloud_H1);
        fprintf(outputFile, "\n");
    }

    if((Cloud2_str != "/") and (Cloud2_str != "0"))
    {
        fprintf(outputFile, "%s %s\n", "Cloud2 = ", Cloud2_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Name2 = ", Cloud_Name2_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Type2 = ", Cloud_Type2_str.c_str());
        fprintf(outputFile, "%s %i\n", "Cloud_H2 = ", Cloud_H2);
        fprintf(outputFile, "\n");
    }

    if((Cloud3_str != "/") and (Cloud3_str != "0"))
    {
        fprintf(outputFile, "%s %s\n", "Cloud3 = ", Cloud3_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Name3 = ", Cloud_Name3_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Type3 = ", Cloud_Type3_str.c_str());
        fprintf(outputFile, "%s %i\n", "Cloud_H3 = ", Cloud_H3);
        fprintf(outputFile, "\n");
    }

    if((Cloud4_str != "/") and (Cloud4_str != "0"))
    {
        fprintf(outputFile, "%s %s\n", "Cloud4 = ", Cloud4_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Name4 = ", Cloud_Name4_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Type4 = ", Cloud_Type4_str.c_str());
        fprintf(outputFile, "%s %i\n", "Cloud_H4 = ", Cloud_H4);
        fprintf(outputFile, "\n");
    }

    if((Cloud5_str != "/") and (Cloud5_str != "0"))
    {
        fprintf(outputFile, "%s %s\n", "Cloud5 = ", Cloud5_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Name5 = ", Cloud_Name5_str.c_str());
        fprintf(outputFile, "%s %s\n", "Cloud_Type5 = ", Cloud_Type5_str.c_str());
        fprintf(outputFile, "%s %i\n", "Cloud_H5 = ", Cloud_H5);
        fprintf(outputFile, "\n");
    }

    if(QFE_str != "calc")
    {
        fprintf(outputFile, "%s %.1f\n", "QFE = ", QFE);
        fprintf(outputFile, "\n");
    }
    else
    {
        fprintf(outputFile, "%s %f\n", "B_Pressure = ", B_Pressure);
        fprintf(outputFile, "%s %f\n", "B_Temp = ", B_Temp);
        fprintf(outputFile, "\n");
        fprintf(outputFile, "%s %.1f\n", "QFE = ", QFE);
        fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "%s %f\n", "QNH = ", QNH);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %f\n", "QFF = ", QFF);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %f\n", "H850 = ", H850);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %i\n", "Pr_Tendency = ", Pr_Tendency);
    fprintf(outputFile, "%s %f\n", "Pr_Change = ", Pr_Change);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %f\n", "Dry_Temp = ", Dry_Temp);
    fprintf(outputFile, "%s %f\n", "Wet_Temp = ", Wet_Temp);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %f\n", "Dew_Point_Temp = ", Tdew);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "%s %f\n", "VP = ", Pw);
    fprintf(outputFile, "%s %i\n", "RH = ", int(round(RH)));
    fprintf(outputFile, "\n");

    // SM

    if((Ir == 1))
    {
        fprintf(outputFile, "%s %.1f\n", "Rain_6h = ", Rain_6h);
        fprintf(outputFile, "%s %i\n", "Rain_Period_6h = ", Rain_Period_6h);
        fprintf(outputFile, "\n");
    }

    // SM, SI

    if((Ir == 1))
    {
        fprintf(outputFile, "%s %.1f\n", "Rain_3h = ", Rain_3h);
        fprintf(outputFile, "%s %.1f\n", "Rain_24h = ", Rain_24h);
        fprintf(outputFile, "\n");
    }

    if((Ir == 4) and ((Time_Hour == 3) or (Time_Hour == 9) or (Time_Hour == 15) or (Time_Hour == 21)))
    {
        fprintf(outputFile, "%s %.1f\n", "Rain_3h = ", Rain_3h);
        fprintf(outputFile, "%s %.1f\n", "Rain_24h = ", Rain_24h);
        fprintf(outputFile, "\n");
    }
    
    // SN

    if((Ir == 2))
    {
        fprintf(outputFile, "%s %.1f\n", "Rain_1h = ", Rain_1h);
        fprintf(outputFile, "%s %i\n", "Rain_Period_1h = ", Rain_Period_1h);
        fprintf(outputFile, "\n");
    }

    // SM06
    
    if((Ir == 1) and (Time_Hour == 6))
    {
        fprintf(outputFile, "%s %i\n", "Ground_Status = ", Ground_Status);
        fprintf(outputFile, "%s %.1f\n", "Ground_Temp = ", Ground_Temp);
        fprintf(outputFile, "\n");
        fprintf(outputFile, "%s %s\n", "Evaporation = ", Evaporation_str.c_str());
        fprintf(outputFile, "%s %i\n", "Evap_Device = ", Evap_Device);
        fprintf(outputFile, "\n");
    }

    // SI03, SI15

    if((Ir == 4) and ((Time_Hour == 3) or (Time_Hour == 15)))
    {
        fprintf(outputFile, "%s %.1f\n", "Min_Temp = ", Min_Temp);
        fprintf(outputFile, "%s %.1f\n", "Max_Temp = ", Max_Temp);
        fprintf(outputFile, "\n");
    }

    // SI03, SI09, SI15

    if((Ir == 4) and ((Time_Hour == 3) or (Time_Hour == 9) or (Time_Hour == 15)))
    {
        fprintf(outputFile, "%s %.1f\n", "Soil_T5 = ", Soil_T5);
        fprintf(outputFile, "%s %.1f\n", "Soil_T10 = ", Soil_T10);
        fprintf(outputFile, "%s %.1f\n", "Soil_T20 = ", Soil_T20);
        fprintf(outputFile, "%s %.1f\n", "Soil_T30 = ", Soil_T30);
        fprintf(outputFile, "%s %.1f\n", "Soil_T50 = ", Soil_T50);
        fprintf(outputFile, "%s %.1f\n", "Soil_T100 = ", Soil_T100);
        fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "%s\n", "Synop_Code = ");
    fprintf(outputFile, "%s\n", Synop_Code.c_str());

    fclose(outputFile);

    return(0);
}

string remove_space(string s)
{
    //traversing the string
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            //using in-built function to erase element
            s.erase(s.begin() + i);
            i--;
        }
    }
    return(s);
}

string read_data(string variable_name)
{
string search;
ifstream inFile;
string line;

inFile.open("input.txt");

if(!inFile){
cout << "Unable to open file" << endl;
exit(1);
}
search = variable_name;

size_t pos_variable_name;
size_t pos_equality;
size_t pos_endl;
while(inFile.good())
  {
      getline(inFile, line); // get line from file
      pos_variable_name = line.find(search); // search
      pos_equality = line.find("=");
      pos_endl = line.find("\n");
      if((pos_variable_name !=string::npos) and (pos_equality != string::npos)) // string::npos is returned if string is not found
        {
            return(remove_space(line.substr(pos_equality + 1, pos_endl)));
            break;
        }
  }
return("null");
}
