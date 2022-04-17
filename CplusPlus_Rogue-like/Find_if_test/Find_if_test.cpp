﻿#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
using namespace std;

bool HasYoung(string who)
{
    return (who.find("영") != string::npos);
}
void main()
{
    string names[] = { "김정수","구홍녀","문병대",
         "김영주","임재임","박미영","박윤자" };
    vector<string> as(&names[0], &names[7]);

    vector<string>::iterator it;
    for (it = as.begin();; it++) {
        it = find_if(it, as.end(), HasYoung);
        if (it == as.end()) break;
        cout << *it << endl;
    }

}