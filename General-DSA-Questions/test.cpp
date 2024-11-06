// Just to test some code

#include <iostream>
#include<set>
using namespace std;

int main() {
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(-1);
    cout << s.count(1) << endl;
    return 0;
}