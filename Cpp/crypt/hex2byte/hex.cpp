//
// Author: Ping Chen
// Date: 2017.04.06
//

#include <iostream>
#include "hex.h"

using namespace std;
using namespace hexcodec;

int main()
{
    cout << "Please input a string to test the func" << endl;
    string input/* = "fjkdsljfjgfdzzkflls"*/;
    cin >> input;

    string hex_str = bytes2hex(input);
    string bytes_str = hex2bytes(hex_str);

    cout << "input:" << input << endl;
    cout << "hex encode:" << hex_str << endl;
    cout << "hex decode:" << bytes_str << endl;

    return 0;
}
