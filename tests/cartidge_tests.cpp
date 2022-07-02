#include <iostream>
#include "../CARTIDGE.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage " << argv[0] << " <path_to_rom>" << endl;
        return (1);
    }
    string filename(argv[1]);

    CARTIDGE myCartidge(filename);

    myCartidge.debugPrintDetails();

    return (0);
}