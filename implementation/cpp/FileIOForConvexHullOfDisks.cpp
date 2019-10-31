#include "FileIOForConvexHullOfDisks.h"


void FileIOForConvexHullOfDisks::read_disks_from_file_with_single_precision(const string& inputFileNameWithPath, list<CircularDisk2D>& inputDisks)
{
    ifstream fin;
    fin.open(inputFileNameWithPath.c_str());

    char  seps[4] = " \t\n";
    char  buffer[200];

    fin.getline(buffer, 200);
    int numOfDisks = atoi(strtok(buffer, seps));

    for (int i = 0; i < numOfDisks; i++)
    {
        fin.getline(buffer, 200);
        int     id = atoi(strtok(buffer, seps));
        float    x = atof(strtok(_NULL, seps));
        float    y = atof(strtok(_NULL, seps));
        float    r = atof(strtok(_NULL, seps));

        inputDisks.push_back(CircularDisk2D(x, y, r, id));
    }

    fin.close();
}


void FileIOForConvexHullOfDisks::read_disks_from_file_with_double_precision(const string& inputFileNameWithPath, list<CircularDisk2D>& inputDisks)
{
    ifstream fin;
    fin.open(inputFileNameWithPath.c_str());

    char  seps[4] = " \t\n";
    char  buffer[200];

    fin.getline(buffer, 200);
    int numOfDisks = atoi(strtok(buffer, seps));

    for (int i = 0; i < numOfDisks; i++)
    {
        fin.getline(buffer, 200);
        int     id = atoi(strtok(buffer, seps));
        double   x = atof(strtok(_NULL, seps));
        double   y = atof(strtok(_NULL, seps));
        double   r = atof(strtok(_NULL, seps));

        inputDisks.push_back(CircularDisk2D(x, y, r, id));
    }

    fin.close();
}


void FileIOForConvexHullOfDisks::write_disks_to_file(const string& outputFileNameWithPath, const list<CircularDisk2D>& outputDisks, const int& precision)
{
    ofstream fout;
    fout.open(outputFileNameWithPath.c_str());

    fout.setf(std::ios::fixed, std::ios::floatfield);
    fout.precision(precision);

    fout << outputDisks.size() << endl;

    for (list<CircularDisk2D>::const_iterator it_Disk = outputDisks.begin(); it_Disk != outputDisks.end(); ++it_Disk)
    {
        CircularDisk2D currDisk = *it_Disk;
        fout << currDisk.get_ID()                << "\t";
        fout << currDisk.get_center_pt().get_x() << "\t";
        fout << currDisk.get_center_pt().get_y() << "\t";
        fout << currDisk.get_radius()            << endl;
    }

    fout.close();
}

