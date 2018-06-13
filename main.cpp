#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

void open_files(ifstream& in_stream, ofstream& out_stream);
double wind_chill(double temp, double windSpeed);
double cloud_base(double temp, double dewPoint);
void output_header(ofstream& out_stream);
void output_data(ofstream& out_stream, double temp, double windSpeed, double dewPoint, double wc, double cb, bool& warn);
void output_warning(ofstream& out_stream, double temp, double windSpeed);

int main()
{
    ifstream in_stream;
    ofstream out_stream;
    //variables
    double temp, windSpeed, dewPoint, wc, cb;
    bool warn; //using this as a variable to keep track if temp or windSpeed have undesired entries.  It will be placed in the conditional statement for their outputs.  After the loop if this variable was called it will dispaly the warning with an if statement.

    open_files(in_stream, out_stream);

    output_header(out_stream);

    while (in_stream)
    {
        in_stream >> temp >> windSpeed >> dewPoint;

        wc = wind_chill(temp, windSpeed);

        cb = cloud_base(temp, dewPoint);

        output_data(out_stream, temp, windSpeed, dewPoint, wc, cb, warn);

    }

    if (warn == true)
    {
        output_warning(out_stream, temp, windSpeed);
    }

    in_stream.close();
    out_stream.close();

    return 0;
}

void open_files(ifstream& in_stream, ofstream& out_stream)
{
    in_stream.open("/Users/chris/Desktop/project1/weatherData.txt");
    if(in_stream.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);

    }

    out_stream.open("/Users/chris/Desktop/project1/results.txt");
    if(out_stream.fail())
    {
        cout << "Output file opening failed.\n";
        exit(1);

    }
}

double wind_chill(double temp, double windSpeed)
{
    const double PW = pow( windSpeed, 0.16 );
    double wc = 35.74 + .6215 * temp -35.75 * PW + 0.4275 * temp * PW;
    return wc;
}


double cloud_base(double temp, double dewPoint)
{
    double tempSpread = temp - dewPoint;
    double cb = (tempSpread/4.4)*1000;
    return cb;
}

void output_header(ofstream& out_stream)
{
    cout << " Temperature" << "     " << "Wind Speed" << "       " << "Dew Point" << "       " << "Wind Chill" << "      " << "Cloud Base" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    out_stream << " Temperature" << "     " << "Wind Speed" << "       " << "Dew Point" << "       " << "Wind Chill" << "      " << "Cloud Base" << endl;
    out_stream << "-----------------------------------------------------------------------------" << endl;
}

void output_data(ofstream& out_stream, double temp, double windSpeed, double dewPoint, double wc, double cb, bool& warn)
{
    cout << fixed << setprecision(1);
    out_stream << fixed << setprecision(1);

    if ((temp > 0.0 && temp < 50.0) && windSpeed > 3.0)
    {
        cout << setw(7) << temp << " dF "<< setw(10) << windSpeed << " mph " << setw(12) << dewPoint << " dF " << setw(13) << wc << " dF " << setw(13) <<cb << " ft " << endl;

        out_stream << setw(7) << temp << " dF "<< setw(10) << windSpeed << " mph " << setw(12) << dewPoint << " dF " << setw(13) << wc << " dF " << setw(13) <<cb << " ft " << endl;
    }

    else if (temp > 50.0 || (windSpeed <=3.0 && windSpeed > 0))
    {
        warn = true;
        wc = wind_chill(temp, windSpeed);
        cb = cloud_base(temp, dewPoint);

        cout << setw(7) << temp << " dF "<< setw(10) << windSpeed << " mph " << setw(12) << dewPoint << " dF " << setw(13) << "***" << setw(17) <<cb << " ft " << endl;

        out_stream << setw(7) << temp << " dF "<< setw(10) << windSpeed << " mph " << setw(12) << dewPoint << " dF " << setw(13) << "***" << setw(17) <<cb << " ft " << endl;
    }
}

void output_warning(ofstream& out_stream, double temp, double windSpeed)
{

        cout <<"\n*** There is no wind chill factor at this temperature or wind speed. ***" << endl;
        cout << "\n    *** Temperature must be 50 degrees  or less, and wind speed" << endl;
        cout << "               must be > 3 mph to compute  wind chill." << endl;

        out_stream <<"\n*** There is no wind chill factor at this temperature or wind speed. ***" << endl;
        out_stream << "\n    *** Temperature must be 50 degrees  or less, and wind speed" << endl;
        out_stream << "               must be > 3 mph to compute  wind chill." << endl;

}
