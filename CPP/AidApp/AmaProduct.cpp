#include "AmaProduct.h"
using namespace std;
namespace sict {

	AmaProduct::AmaProduct(char filetag) : fileTag_(filetag) {

	}

	const char* AmaProduct::unit() const {

		return unit_;

	}

	void AmaProduct::unit(const char* value) {

		strcpy(unit_, value);

	}

	fstream& AmaProduct::store(fstream& file, bool addNewLine)const {

		file << fileTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << unit() << "," << qtyNeeded();

		if (addNewLine) {

			file << endl;

		}

		return file;

	}

	fstream& AmaProduct::load(fstream& file) {

		char skuO[MAX_SKU_LEN + 1];
		char nameO[99];
		char unitO[11];
		double priceO;
		int quantityO;
		int qtyNeededO;
		int taxedO;

		file.getline(skuO, MAX_SKU_LEN + 1, ',');
		sku(skuO);
		file.getline(nameO, 99, ',');
		name(nameO);
		file >> priceO;
		file.ignore();
		price(priceO);
		file >> taxedO;
		file.ignore();
		taxed(bool(taxedO));
		file >> quantityO;
		file.ignore();
		quantity(quantityO);
		file.getline(unitO, 11, ',');
		unit(unitO);
		file >> qtyNeededO;
		file.ignore();
		qtyNeeded(qtyNeededO);

		return file;

	}

	ostream& AmaProduct::write(ostream& os, bool linear)const {

		if (err_.isClear() != true) {

			os << err_.message();

		}

		else if (!isEmpty()) {
			char N[75];
			int q = quantity();

			if (linear) {
				strncpy(N, name(), 20);
				N[20] = '\0';
				os << setfill(' ') << left << setw(MAX_SKU_LEN) << sku() << "|" << setw(20) << N << "|" << right << setw(7)
					<< fixed << setprecision(2) << cost() << "|" << setw(4) << q << "|" << left << setw(10) << unit() <<
					"|" << right << setw(4) << qtyNeeded() << "|";

			}

			else {
				strncpy(N, name(), 74);
				N[74] = '\0';
				os.clear();
				os << "Sku: " << sku() << endl;
				os << "Name: " << N << endl;
				os << "Price: " << price() << endl;
				os << "Price after tax: "; if (taxed()) os << cost() << endl; else os << "N/A" << endl;
				os << "Quantity On Hand: " << q << " " << unit() << endl;
				os << "Quantity Needed: " << qtyNeeded();

			}

		}

		return os;

	}

	istream& AmaProduct::read(istream& istr) {

		char skuO[MAX_SKU_LEN + 1];
		char nameO[74];
		char unitO[11];
		char taxO;
		double priceO;
		int quantityO;
		int qtyNeededO;

		if (!istr.fail()) err_.clear();
		istr.ignore();
		cout << "Sku: "; istr.getline(skuO, MAX_SKU_LEN+1, '\n');

		cout << "Name: "; istr.getline(nameO, 74, '\n');

		cout << "Unit: "; istr.getline(unitO, 11, '\n');

		cout << "Taxed? (y/n): "; istr >> taxO;
		if (taxO == 'y' || taxO == 'Y' || taxO == 'n' || taxO == 'N') {
			istr.ignore(1000, '\n');
			cout << "Price: "; istr >> priceO;
		}
		else {
			istr.setstate(ios::failbit); 
			err_.message("Only (Y)es or (N)o are acceptable");
		}
		if (err_.isClear() && istr.fail()) {
			err_.message("Invalid Price Entry");
		}
		if (err_.isClear()) {
			cout << "Quantity On hand: "; istr >> quantityO;
		}
		if (err_.isClear() && istr.fail()) {
			err_.message("Invalid Quantity Entry");
		}
		if (err_.isClear()) {
			cout << "Quantity Needed: "; istr >> qtyNeededO;
		}
		if (err_.isClear() && istr.fail()) {
			err_.message("Invalid Quantity Needed Entry");
		}

		if (!istr.fail()) {

			sku(skuO);
			name(nameO);
			unit(unitO);
			taxed(taxO == 'y' || taxO == 'Y');
			price(priceO);
			quantity(quantityO);
			qtyNeeded(qtyNeededO);
		}

		return istr;

	}
}
