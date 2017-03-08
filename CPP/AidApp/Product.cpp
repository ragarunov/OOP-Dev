#include <iostream>
#include "Product.h"
using namespace std;
namespace sict {

	Product::Product() {

		sku_[0] = '\0';
		name_ = nullptr;
		price_ = 0;
		taxed_ = false;
		quantity_ = 0;
		qtyNeeded_ = 0;

	}

	Product::Product(const char* skuo, const char* nameO, bool taxedO, double priceO, int needed) {

		sku(skuo);
		name(nameO);
		taxed(taxedO);
		price(priceO);
		qtyNeeded(needed);
		quantity_ = 0;

	}

	Product::~Product() {

		delete [] name_;
		name_ = nullptr;

	}

	Product::Product(const Product& src) {
			
		sku(src.sku_);
		name(src.name_);
		taxed(src.taxed_);
		price(src.price_);
		qtyNeeded(src.qtyNeeded_);
		quantity(src.quantity_);

	}

	Product & Product::operator=(const Product& src) {

		if (this != &src) {
				
			sku(src.sku_);
			name(src.name_);
			taxed(src.taxed_);
			price(src.price_);
			qtyNeeded(src.qtyNeeded_);
			quantity(src.quantity_);

		}

		return *this;


	}

	void Product::sku(const char* sku) {

		strcpy(sku_, sku);

	}

	void Product::price(double price) {

		price_ = price;

	}
		
	void Product::name(const char * name) {

		name_ = new char[strlen(name)+1];
		strcpy(name_, name);

	}

	void Product::taxed(bool taxed) {

		taxed_ = taxed;

	}

	void Product::quantity(int quantity) {

		quantity_ = quantity;

	}

	void Product::qtyNeeded(int qtyNeeded) {

		qtyNeeded_ = qtyNeeded;

	}


	const char* Product::sku() const {

		return sku_;

	}

	double Product::price() const {

		return price_;

	}

	char* Product::name() const {

		return name_;

	}

	bool Product::taxed() const {

		return taxed_;

	}

	int Product::quantity() const {

		return quantity_;

	}

	int Product::qtyNeeded() const {

		return qtyNeeded_;

	}

	double Product::cost() const {

		if (taxed_ == true) {

			return (price_ * TAX) + price_;

		}

		else {

			return price_;

		}

	}

	bool Product::isEmpty() const {

		return (sku_[0] == '\0' || name_ == nullptr);

	}

	bool Product::operator==(const char* sku) {

		return strcmp(sku_, sku) == 0;

	}

	int Product::operator+=(int rec) {

		return quantity_ += rec;

	}

	int Product::operator-=(int quantity) {

		return quantity_ -= quantity;

	}

	double operator+=(double& rec, const Product& src) {

		rec += src.cost() * src.quantity();

		return rec;

	}

	std::istream & operator>> (std::istream & in, Product& a) {

		return a.read(in);

	}

	std::ostream & operator<< (std::ostream & out, Product& b) {

		return b.write(out, true);

	}

}