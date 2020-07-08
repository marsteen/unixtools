//
//
// replaceinfiles - unixtools
// Version 1.3
//
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <CFileIO2.h>

using namespace std;

static bool ReadConfig(const char* fname, std::string* str1, std::string* str2, bool& ReplaceMode)
{
    bool r = false;
    CFileIO2 fio;
    if (fio.OpenFileRead(fname, ios::binary))
    {
         fio.ReadLine(str1);
         if (fio.ReadLine(str2))
         {
             ReplaceMode = true;
         }
         fio.CloseFile();
         r = true;
    }
    return r;
}

int main(int argc, char* argv[])
{
    std::string str1;
    std::string str2;
    bool FileMode = false;
    bool ReplaceMode = false;

    if ((argc == 4) || (argc == 3))
    {
        CFileIO2 fin;
        CFileIO2 fout;
        long FileSize;


        for (int i = 1; i < argc; i++)
        {
            if (std::string(argv[i]) == "-file")
            {
                 FileMode = true;
                 ReadConfig(argv[i + 1], &str1, &str2, ReplaceMode);
            }
        }

        if (!FileMode)
        {
            str1 = argv[2];
            if (argc == 4)
            {
                str2 = argv[3];
                ReplaceMode = true;
            }
        }

        //cout << "str1=" << str1 << std::endl;
        //cout << "str2=" << str2 << std::endl;



        const char* FileData = (const char*) fin.ReadFile(argv[1], &FileSize);
        const char* fromptr  = FileData;

        if (FileData != NULL)
        {
            int FoundCounter = 0;

            const char* posptr = strstr(FileData, str1.c_str());
            if (posptr != NULL)
            {
                if (fout.OpenFileWrite(argv[1], ios::binary))
                {
                    while (posptr != NULL)
                    {
                        fout.WriteBytes(fromptr, posptr - fromptr);
                        if (ReplaceMode)
                        {
                            fout.WriteString(str2.c_str()); // Ersatzstring schreiben
                        }
                        fromptr = posptr + strlen(str1.c_str());
                        posptr = strstr(fromptr, str1.c_str());
                        FoundCounter++;

                    }
                    fout.WriteBytes(fromptr, FileSize - (fromptr - FileData));
                }
                fout.CloseFile();
                cout << "replaced " << FoundCounter << " in " << argv[1] << endl;
            }
        }
        else
        {
            cout << "***** cannot open file:" << argv[1] << endl;
        }
    }
    else
    {
        cout << "usage: replaceinfile <file> <replace_this_string> <by_this_string>" << endl;
        cout << "   or: replaceinfile <file> <remove_this_string>" << endl;
        cout << "   or: replaceinfile <file> -file <paramfile.txt>" << endl;
        cout << "Version 1.3" << endl;
    }

    return 0;
}

