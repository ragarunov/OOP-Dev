#include "AmaPerishable.h"
using namespace std;
namespace sict {

	AmaPerishable::AmaPerishable() : AmaProduct('P') {

	}

	const Date& AmaPerishable::expiry() const {

		return expiry_;

	}

	void AmaPerishable::expiry(const Date& value) {

		expiry_ = value;

	}

	fstream& AmaPerishable::store(fstream& file, bool addNewLine)const {

		AmaProduct::store(file, false);

		file << "," << expiry_;

		if (addNewLine) file << endl;

		return file;

	}

	fstream& AmaPerishable::load(fstream& file) {

		AmaProduct::load(file);
		expiry_.read(file);
		file.ignore();

		return file;

	}

	ostream& AmaPerishable::write(ostream& ostr, bool linear)const {

		AmaProduct::write(ostr, linear);

		if (err_.isClear() && !isEmpty()) {

			if (linear == true) {

				ostr << expiry() << setfill(' ');

			}

			else {

				ostr << endl;
				ostr << "Expiry date: " << expiry();

			}

		}

		return ostr;

	}

	istream& AmaPerishable::read(istream& istr) {

		Date temp;

		AmaProduct::read(istr);

		if (err_.isClear()) {

			cout << "Expiry date (YYYY/MM/DD): ";
			istr >> temp;

			if (err_.isClear() && temp.bad()) {

				if (temp.errCode() == CIN_FAILED) err_.message("Invalid Date Entry");

				else if (temp.errCode() == YEAR_ERROR) err_.message("Invalid Year in Date Entry");

				else if (temp.errCode() == MON_ERROR) err_.message("Invalid Month in Date Entry");

				else if (temp.errCode() == DAY_ERROR) err_.message("Invalid Day in Date Entry");


				istr.setstate(ios::failbit);

			}

		}

		if (!istr.fail()) expiry(temp);

		return istr;

	}

}