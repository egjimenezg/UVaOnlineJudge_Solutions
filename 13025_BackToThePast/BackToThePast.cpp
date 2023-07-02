#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int main() {
  tm date;
  date.tm_year = 2013-1900;
  date.tm_mday = 29;
  date.tm_mon = 4;

  stringstream s;
 
  mktime(&date);
  s << put_time(&date, "%B %d, %Y %A");
  cout << s.str() << endl;
  
  return 0;
}
