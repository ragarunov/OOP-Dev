#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3 
#define DAY_ERROR 4
namespace sict{


  class Date{
  private:
    int value()const;
	int year_;
	int mon_;
	int day_;
	int readErrorCode_;
  public:

   void errCode(int errorCode);
   Date();
   Date(int year, int mon, int day);
   bool operator==(const Date& D)const;
   bool operator!=(const Date& D)const;
   bool operator<(const Date& D)const;
   bool operator>(const Date& D)const;
   bool operator<=(const Date& D)const;
   bool operator>=(const Date& D)const;
   int errCode()const;
   bool bad()const;

   std::istream& read(std::istream& istr);
   std::ostream& write(std::ostream& ostr)const;



    int mdays()const;
  };

  std::istream & operator>> (std::istream & in, Date&);
  std::ostream & operator<< (std::ostream & out, const Date&);

}
#endif