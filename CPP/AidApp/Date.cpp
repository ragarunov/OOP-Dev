#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"
#include "general.h"
namespace sict {
	int Date::value()const {
		return year_ * 372 + mon_ * 31 + day_;
	}
	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}

	void Date::errCode(int errorCode) {

		readErrorCode_ = errorCode;

	}

	Date::Date() {

		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;

	}

Date::Date(int year, int mon, int day) {

	year_ = year;
	mon_ = mon;
	day_ = day;
	readErrorCode_ = NO_ERROR;

}

  int Date::errCode()const {

	  return readErrorCode_;

  }

  bool Date::bad()const {

	  if (readErrorCode_ != 0) {

		  return true;

	  }

	  else {

		  return false;

	  }

  }

  bool Date::operator==(const Date& D)const {


	  if (this->value() == D.value()) {
	  
		  return true;
	  
	  }

	  else {

		  return false;

	  }


  }

  bool Date::operator!=(const Date& D)const {

	  if (this->value() != D.value()) {

		  return true;

	  }

	  else {

		  return false;

	  }

  }

  bool Date::operator<(const Date& D)const {

	  if (this->value() < D.value()) {

		  return true;

	  }

	  else {

		  return false;

	  }

  }

  bool Date::operator>(const Date& D)const {

	  if (this->value() > D.value()) {

		  return true;

	  }

	  else {

		  return false;

	  }

  }

  bool Date::operator<=(const Date& D)const {

	  if (this->value() <= D.value()) {

		  return true;

	  }

	  else {

		  return false;

	  }

  }

  bool Date::operator>=(const Date& D)const {

	  if (this->value() >= D.value()) {

		  return true;

	  }

	  else {

		  return false;

	  }

  }

  std::istream& Date::read(std::istream& istr) {
	  
	  char s;
	  char d;

	 istr >> year_ >> s >> mon_ >> d >> day_;

	 if (istr.fail()) {

		 readErrorCode_ = CIN_FAILED;

	 }

	 else if (year_ < MIN_YEAR || year_ > MAX_YEAR) {

		 readErrorCode_ = YEAR_ERROR;

	 }


	 else if (mon_ < 0 || mon_ > 12) {

			 readErrorCode_ = MON_ERROR;

		 }


	 else if (day_ < 0 || day_ > 31) {

			 readErrorCode_ = DAY_ERROR;

	 }

	 return istr;


  }

  std::ostream& Date::write(std::ostream& ostr)const {

	  ostr << setfill('0') << year_ << "/" << setw(2) << mon_ << "/" << setw(2) << day_;

	  return ostr;

  }

  std::istream & operator>> (std::istream & in, Date& d) {

	  d.read(in);

	  return in;

  }

  std::ostream & operator<< (std::ostream & out, const Date& dsp) {

	  dsp.write(out);

	  return out;

  }

}
