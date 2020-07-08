//---------------------------------------------------------------------------
//
//
// replaceinfiles - unixtools
// Version 1.3
//
//
//---------------------------------------------------------------------------

#include <iostream>
#include <cstdio>
#include <cstring>
#include <CFileIO2.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   ReadConfig
//
//---------------------------------------------------------------------------

static bool ReadConfig(const char* fname, std::string* str1, std::string* str2)
{
    bool r = false;
    CFileIO2 fio;
    if (fio.OpenFileRead(fname, ios::binary))
    {
         fio.ReadLine(str1);
         fio.ReadLine(str2);
         fio.CloseFile();
         r = true;
    }
    return r;
}

//---------------------------------------------------------------------------
//
// Klasse:    static
// Methode:   ReplaceInFile
//
//---------------------------------------------------------------------------

static bool ReplaceInFile(const char* filenameIn, const char* filenameOut, const char* srcString, const char* dstString)
{
    CFileIO2 fin;
    CFileIO2 fout;
    long FileSize;
    bool r = false;

    cout << "reading file:" << filenameIn << endl;
    const char* FileData = (const char*) fin.ReadFile(filenameIn, &FileSize);
    const char* fromptr  = FileData;

    if (FileData != NULL)
    {
        int FoundCounter = 0;

        const char* posptr = strstr(FileData, srcString);
        if (posptr != NULL)
        {
            if (fout.OpenFileWrite(filenameOut, ios::binary))
            {
                r = true;
                while (posptr != NULL)
                {
                    fout.WriteBytes(fromptr, posptr - fromptr);
                    if (dstString != NULL)
                    {
                        fout.WriteString(dstString); // Ersatzstring schreiben
                    }
                    fromptr = posptr + strlen(srcString);
                    posptr = strstr(fromptr, srcString);
                    FoundCounter++;

                }
                fout.WriteBytes(fromptr, FileSize - (fromptr - FileData));
            }
            fout.CloseFile();
            cout << "replaced " << FoundCounter << " in " << filenameIn << endl;
        }
    }
    return r;
}

//---------------------------------------------------------------------------
//
// Klasse:    global
// Methode:   main
//
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        int error = 0;
        if (std::string(argv[2]) == "-rtab")
        {
            if (argc == 4)
            {
                int numSpaces = atoi(argv[3]);
                std::string spaces(numSpaces, ' ');
                cout << "replacing tabs with " << numSpaces << " spaces" << endl; 
                ReplaceInFile(argv[1], argv[1], "\t", spaces.c_str());
            }
            else error = 2;
        }
        else
        if (std::string(argv[2]) == "-file")
        {
            if (argc == 4)
            {
                std::string str1, str2;
                if (ReadConfig(argv[3], &str1, &str2))
                {
                    ReplaceInFile(argv[1], argv[1], str1.c_str(), str2.c_str());
                }
            }
            else error = 2;            
        }
        else
        if (argc == 4)
        {
            ReplaceInFile(argv[1], argv[1], argv[2], argv[3]);
        }
        else
        if (argc == 3)
        {   
            ReplaceInFile(argv[1], argv[1], argv[2], NULL);
        }
        else error = 2;

        if (error > 0)
        {
            cout << "***** param number error" << endl;
        }
    }
    else
    {
        cout << "usage: replaceinfile <file> <replace_this_string> <by_this_string>" << endl;
        cout << "   or: replaceinfile <file> <remove_this_string>" << endl;
        cout << "   or: replaceinfile <file> -file <paramfile.txt>" << endl;
        cout << "   or: replaceinfile <file> -rtab <spaces>" << endl;
        cout << "Version 1.4" << endl;
    }

    return 0;
}






