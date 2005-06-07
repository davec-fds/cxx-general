/*****************************************************************************
 * Timestamp-test.cxx
 *****************************************************************************
 * Tests the class Timestamp.
 *****************************************************************************/

// STL includes.
#include <iostream>

// Internal includes.
#include "demangle.hxx"
#include "Exception.hxx"

// Testing include.
#include "Timestamp.hxx"

// Namespace declarations.
using namespace std;
using namespace DAC;

// This is where it all happens.
int main (int argc, char** argv, char** envp) {
  
  try {
    
    /** /
    Timestamp::Interval interval;
    
    Timestamp lastdate;
    Timestamp thisdate;
    
    interval.Year(-5000).Month(1).Day(1).Hour(0).Minute(0).Second(0);
    thisdate.set(interval);
    for (;;) {
      
      lastdate = thisdate;
      interval.Day(interval.Day() + Timestamp::TimeVal(1));
      if (interval.Day() > interval.Month().daysInMonth(interval.Year())) {
        interval.Day(1);
        interval.Month(interval.Month() + Timestamp::TimeVal(1));
        if (interval.Month() > Timestamp::TimeVal(12)) {
          interval.Month(1);
          interval.Year(interval.Year() + Timestamp::TimeVal(1));
          if (interval.Year().isZero()) {
            interval.Year(1);
          }
        }
      }
      thisdate.set(interval);
      cout << "last: " << lastdate.Julian() << "  this: " << thisdate.Julian() << ": ";
      if ((thisdate - lastdate) == Timestamp::TimeVal(1)) {
        cout << "Success!" << endl;
      } else {
        cout << "Failure!" << endl;
        exit(1);
      }
      
    }
    //*/
    
    /**/
    Timestamp test1;
    
    test1.getSystemTime();
    
    cout << "Current:" << endl
         << "  Julian: " << test1.Julian() << endl;
    
    Timestamp test2;
    
    typedef Timestamp::TimeVal TV;
    
    TV s, n, h, d, m, y;
    
    cout << "Year:   "; cin >> y;
    cout << "Month:  "; cin >> m;
    cout << "Day:    "; cin >> d;
    cout << "Hour:   "; cin >> h;
    cout << "Minute: "; cin >> n;
    cout << "Second: "; cin >> s;
    
    test2.set(Timestamp::Interval().Year(y).Month(m).Day(d).Hour(h).Minute(n).Second(s));
    
    cout << "Julian: " << test2.Julian() << endl;
    
    Timestamp::Interval ti;
    
    ti = test2.get();
    
    cout << "Year:   " << ti.Year()   << endl
         << "Month:  " << ti.Month()  << endl
         << "Day:    " << ti.Day()    << endl
         << "Hour:   " << ti.Hour()   << endl
         << "Minute: " << ti.Minute() << endl
         << "Second: " << ti.Second() << endl;
    //*/
    
    return 0;
    
  } catch (Exception& e) {
    
    cout << "Exception (" << e.type() << "): " << e << endl;
    exit(1);
    
  } catch (exception& e) {
    
    cout << "Exception (" << demangle(e) << "): " << e.what() << endl;
    exit(1);
    
  } catch (...) {
    
    cout << "Unexpected exception caught." << endl;
    exit(1);
    
  }
  
};