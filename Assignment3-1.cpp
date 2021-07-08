/******************************************************************************
 PROGRAM NAME:      Assignment3-1.cpp
 DATE:              6, July, 2021
 VERSION:           1.0
 AUTHOR:            Tyler Rhoads
 DESCRIPTION:       Read from file and calculates tax information and writes
                    to file and uses functions this time. 
**/
#include <iostream> 
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;
int openFiles(ifstream&, ofstream&, ofstream&);
void displayMessage(ofstream&);
void readFile(ifstream&, string&, char&, int&, double&, float&);
void displayOutPut(ofstream&,string, double, float, float, float,float);
void closeFiles(ifstream&, ofstream&, ofstream&);
float taxObligation(float);
float taxIncome(double, float, float);
void printError(ofstream&,string, char, int, double, float);
float exemption(char, int);
float penD(double, float);


int main ()
{
    string surName;
    char maritalS;
    int childrenN;
    double grossIncome;
    float pensionP;
    ifstream inFile;//file entered by user will be customers.txt
    ofstream error;//file to hold the errors
    ofstream toFile;//file for the final ourput
    float totalEx;
    float pensionDed;
    float taxableInc;
    float taxOb;

     if(!openFiles(inFile, toFile, error))
    {
        cout << "exiting program" << endl;
        return 0;
    }
          
    displayMessage(toFile);
    while (inFile)
    {
        readFile(inFile, surName, maritalS, childrenN, grossIncome, pensionP);
        
         if (!inFile)
            {
                break;
            }
        
         totalEx = exemption(maritalS,childrenN);
            
          if (maritalS!='M'&& maritalS!='S')  
            {
                printError(error,surName,maritalS,childrenN,grossIncome,pensionP);
                continue;
          }
              
              pensionDed= penD(grossIncome, pensionP);

          if(pensionP>.06)
            {
                printError(error,surName,maritalS,childrenN,grossIncome,pensionP);
                continue;
            }
        taxableInc = taxIncome(grossIncome, totalEx ,pensionDed);
    
        taxOb=taxObligation(taxableInc);
        
        
        displayOutPut(toFile,surName,  grossIncome, totalEx, pensionDed, taxableInc,taxOb);
    }
    
    closeFiles(inFile, toFile, error);


return 0;

}// end of main 

/******************************************************************************
FUNCTION NAME:    openFiles
PARAMETER(S):     ifstream&iN, ofstream&oUT, ofstream&error
RETURN TYPE:      int
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      opens the files for the program 
PRECONDITIONS:    None
POSTCONDITIONS:   all the files are open and able to read and write to them.
**/
int openFiles(ifstream&iN, ofstream&oUT, ofstream&error)
{
    string userFile;
    string errorError ="errorfile.txt";
    string out2 = "tylersoutput.txt";

    cout << " Please enter a file to run the tax return" << endl;
    cin >> userFile;
    iN.open(userFile);
    oUT.open(out2);
    error.open(errorError);
     
        if(!iN)
        {
            cout << "failed to open a file" << endl;
            return 0;
        }//checks to see if inFile opens
        
        if(!oUT)
        {
            cout << "failed to open a file" << endl;
            return 0;
        }//checks to see if error opens

        if(!error)
        {
            cout << "failed to open a file" << endl;
            return 0;
        }///checks to see if out opens

    return 1;
}// end of openFiles

/******************************************************************************
FUNCTION NAME:    displayMessage
PARAMETER(S):     ofstream&out
RETURN TYPE:      Void
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      Prints off the main message that stays constint, 
PRECONDITIONS:    the files to be open so it can write to them 
POSTCONDITIONS:   Message printed to output file. 
**/
void displayMessage(ofstream&out)
{
        cout << left << setw(15) << "Family"  << left << setw(15) << "Gross Income"  << setw(15) << "Total Ex" 
             << setw(15) <<"Pension Ded" << setw(15) << "Taxable Inc" << "Tax Ob" << endl;
        cout << endl;
        
        out << left << setw(15) << "Family"  << left << setw(15) << "Gross Income"  << setw(15) << "Total Ex" 
             << setw(15) <<"Pension Ded" << setw(15) << "Taxable Inc" << "Tax Ob" << endl;
        out << endl;
}// end of displayMessage

/******************************************************************************
FUNCTION NAME:    displayOutPut
PARAMETER(S):     ofstream&out,string name, double income, float ex, float pD,
                  float tI,float tO
RETURN TYPE:      Void
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      Prints out the info for the taxes, 
PRECONDITIONS:    Needs all of the Info like the tax exemption and obligation
POSTCONDITIONS:   Message printed to output file. 
**/
void displayOutPut(ofstream&out,string name, double income, float ex, float pD, float tI,float tO)
{
    cout << fixed <<  setprecision(2);
    cout << left << setw(15) << name  <<'$'<< setw(14) << income << '$'<< setw(14) << ex 
         <<'$'<< setw(14) << pD  <<'$'<< setw(14) << tI <<'$'<< tO << endl;
    cout << endl;
    out << fixed <<  setprecision(2);
    out << left << setw(15) << name  <<'$'<< setw(14) << income << '$'<< setw(14) << ex 
           <<'$'<< setw(14) << pD  <<'$'<< setw(14) << tI <<'$'<< tO << endl;
    out << endl;
}// end of displayOutPut

/******************************************************************************
FUNCTION NAME:    closeFiles
PARAMETER(S):     ifstream&in, ofstream&out, ofstream&Error
RETURN TYPE:      Void
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      closes the files 
PRECONDITIONS:    files are open
POSTCONDITIONS:   files close.
**/
void closeFiles(ifstream&in, ofstream&out, ofstream&Error)
{
    in.close();
    Error.close();
    out.close();
}// end of closeFiles.

/******************************************************************************
FUNCTION NAME:    taxObligation
PARAMETER(S):     float taxIn
RETURN TYPE:      float
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      determins the tax obligation 
PRECONDITIONS:    the taxeable income must be know 
POSTCONDITIONS:   send of the tax obligation as taxOb. 
**/
float taxObligation(float taxIn)
{
    float taxOb;
    if (taxIn < 30000)
        {
            taxOb = taxIn*.1;
            
        }
        else if (taxIn > 30000 && taxIn < 523600)
        {
            taxOb = ((taxIn - 30000 ) *.22)+2250;
           
        }

        else if (taxIn >523600)
        {
            taxOb = ((taxIn - 523600 ) *.37)+8460;
           
        }
        return taxOb;

} // end of taxObligation

/******************************************************************************
FUNCTION NAME:    taxIncome
PARAMETER(S):     double gI, float tE, float pD
RETURN TYPE:      float
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      determins the taxable income.  
PRECONDITIONS:    needs the gross income and tax exemption and pension
                  deduction
POSTCONDITIONS:   send of the taxable income  as taxableInc. 
**/
float taxIncome(double gI, float tE, float pD)
{
    float taxableInc = gI -tE-pD;
        if (taxableInc<0)
        {
            taxableInc =0;
        }
return taxableInc;
}// end of taxIncome

/******************************************************************************
FUNCTION NAME:    printError
PARAMETER(S):     ofstream&error, string name, char M, int N, double gI,
                  float pP
RETURN TYPE:      void
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      prints out the ones that are marked as error to file.
PRECONDITIONS:    needs all the info from file to be able to print it 
POSTCONDITIONS:   prints to file. 
**/
void printError(ofstream&error, string name, char M, int N, double gI, float pP)
{
    if (M!='M'&& M!='S')
    {   
        error << "Invalid Marital Status:" << endl;
        error << name <<' '<< M <<' '<< N <<' '<< gI <<' '<< pP<< endl;
        error << endl;
    }
    else if (pP>.06)
    {
        error << "Invalid Pension Deduction:" << endl;
        error << name <<' '<< M <<' '<< N <<' '<< gI <<' '<< pP<< endl;
        error << endl;

    }

}// end of printError

/******************************************************************************
FUNCTION NAME:    readFile
PARAMETER(S):     ifstream&in, string&name, char&M, int&N, double&gI, float&pP
RETURN TYPE:      void
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      reads from file 
PRECONDITIONS:    file open
POSTCONDITIONS:   stores info to the varibles. 
**/
void readFile(ifstream&in, string&name, char&M, int&N, double&gI, float&pP)
{
   
 
        in >> name >> M >> N >> gI >> pP;// reads data from the file
      
 
}// end of readFile

/******************************************************************************
FUNCTION NAME:    exemption
PARAMETER(S):     char mS,int kids
RETURN TYPE:      float
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      claculates the total exemption 
PRECONDITIONS:    needs the marrital status and number of kids 
POSTCONDITIONS:   sends back total exemption.
**/
float exemption(char mS,int kids)
{
    float totalEx;
    switch (mS)
          {
          case 'M':
              totalEx =  (25100.00 + ((2+kids)*700));
              break;
        case 'S':
            totalEx =  (12550 + ((1+kids)*700));
           break;
          
          default:
          break;
          }
    return totalEx;

}// end of exemption

/******************************************************************************
FUNCTION NAME:    penD
PARAMETER(S):     double gi, float pp
RETURN TYPE:      float
VERSION:          1.0
DATE:             6, July, 2021
AUTHOR:           TJ Rhoads
DESCRIPTION:      claculates pension deduction
PRECONDITIONS:    need the gross income and pension percentage 
POSTCONDITIONS:   sends back total deduction.
**/
float penD(double gi, float pp)
{
    float pensionDed;

 pensionDed= gi*pp;
 return pensionDed;
}// end of penD.