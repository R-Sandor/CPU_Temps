/**
 * @Author: Raphael J. Sandor
 * @Date:   10/26/2019
 * @Version: 2.0
 * 
 * Description: 
 *      This program reads in a file of CPU core tempatures and find the line of best fit
 *      using either least squares and interpolation.
 *      The program then exports the approximation for a point to a txt file. 
 */

#include <iostream>
#include <fstream> //File reader(ifstream)
#include <vector>

#include "matrixSolver.h"
#include "helper.h"
#include "interpolation.h"
using namespace std;
using boost::multiprecision::cpp_dec_float_50;


/**
 *  @param argc Argument count
 *  @param argv Takes file path
 */
int main(int argc, char **argv )
{
    if (argv[1] == NULL)
    {
        cout << "Error: Please provide path to the data file. "
             << "Refer to the README.md" << endl;
        return 1;
    }
    if (argc == 1)
    {   
        cout << "Please run program again with file path to data file" << endl;
        return 1;
    }

    //  readFile
    ifstream dataFile;
    // path to file
    string path = argv[1];
    
    string line;
    string delim = " "; 

    // Number of cores to be reading data from.
    int cores;
    vector< vector<double> > data;  

    // Check if the path is correct.    
    dataFile.open(path);
    if (!dataFile)
    {
        cout << "Error: File not found, check file path"<< endl;
        return 1;
    }
    if (dataFile.is_open())

        getline(dataFile, line);
        vector<double> inputLine = stringToVector(line, delim);

        // If there are four cores, we want to register it as 5
        // 1 for the time of recording.
        cores = inputLine.size() + 1;

        // element 0 for the time vector
        // e.g. 30, 60, 90, 120 
        for (int indexOfCore = 0; indexOfCore < cores; indexOfCore++)
        {
            vector<double> core;

            if (indexOfCore == 0)
                core.push_back(0);
            else
                core.push_back(inputLine[indexOfCore-1]);
            // push each core into its own vector   
            data.push_back(core);
        }

        // count used as index to multiply 30 against for each reading.
        int count = 1;
        while (getline(dataFile, line) )
        {

            // Now we want to take the output of each row and add
            // it to its respective vector
            inputLine = stringToVector(line, delim);
            for (int indexOfCore = 0; indexOfCore < cores ; indexOfCore++)
            {
                if (indexOfCore == 0)
                {
                    data[indexOfCore].push_back(count * 30);
                    count++;
                    continue;
                }
                else
                    data[indexOfCore].push_back(inputLine[indexOfCore-1]);
            }
        }

        // xMatrix
        vector<vector<double> > xMatrix;

        // x transpose matrix.
        vector<vector<double> > xTMatrix;

        // create the x matrix from the time column in the data vector.
        xMatrix = createXMatrix(data[0]);

        ///////////////////////////////////
        /*
         *  Interpolation work.
         */
        liMatrix mathVect;
        createLi(mathVect, data[0]);
        vector<cpp_dec_float_50> divisors;
        vector<cpp_dec_float_50> quotients;
        solveLiDivisor(mathVect, divisors);
        solveQuotients(mathVect, quotients);
        ///////////////////////////////////


        // iterates through all of the data columns to ouput to a text file.
        for (int outIndex = 1; outIndex < cores; outIndex++)
        {
            ofstream outputFile;


            int pos =  path.find(".txt");
            string baseName = path.substr(0, pos);
            baseName = baseName + "-core-"+to_string(outIndex-1)+".txt";
            outputFile.open(baseName);

            //////////////////////////////////////////////////////
            /*
             *  Least Squares work.
             */
            xTMatrix = createTMatrix(xMatrix);

            // x Transpose x and x Transpose y matrix   
            vector<vector<double> > xTx_xTyMatrix;

            // y Matrix
            vector<double> yMatrix = data[outIndex];

            // x Transpose y matrix
            vector<vector<double> > xTyMatrix;
            // Create the A matrix
            multiplyer(xTMatrix, xMatrix, xTx_xTyMatrix);
            // c Vector
            multiplyVectByMat(xTMatrix, yMatrix, xTyMatrix);
            // Add the c vector to the A matrix
            for (int addYIndx = 0; addYIndx < xTx_xTyMatrix.size(); addYIndx++)
            {
                xTx_xTyMatrix[addYIndx].push_back(xTyMatrix[addYIndx][0]);
            }

            // Finally we have phi hat
            // phi-hat = c0 + c1
            double c0 = xTx_xTyMatrix[0][2];
            double c1 = xTx_xTyMatrix[1][2];

            ////////////////////////////////////////////////////

            printFile(c0, c1, quotients, divisors, data,
                            outputFile, outIndex, count);

        }
}
