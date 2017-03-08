#ifndef SICT__Product_H_
#define SICT__Product_H_
#include "general.h"
#include "Streamable.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
namespace sict{
  class Product : public Streamable{
  private:
	  char sku_[MAX_SKU_LEN+1];
	  char * name_;
	  double price_;
	  bool taxed_;
	  int quantity_;
	  int qtyNeeded_;

  public:
	  Product();
	  Product(const char* skuO, const char* nameO, bool taxedO = true, double priceO = 0, int needed = 0);
	  Product(const Product& src);
	  virtual ~Product();

	  //setters
	  void sku(const char* sku);
	  void price(double price);
	  void name(const char * name);
	  void taxed(bool taxed);
	  void quantity(int quantity);
	  void qtyNeeded(int qtyNeeded);

	  //getters
	  const char* sku() const;
	  double price() const;
	  char* name()const;
	  bool taxed() const;
	  int quantity() const;
	  int qtyNeeded() const;
	  double cost() const;
	  bool isEmpty() const;

	  //member operators
	  Product & operator=(const Product& src);
	  bool operator==(const char* sku);
	  int operator+=(int rec);
	  int operator-=(int quantity);

  };

  double operator+=(double&, const Product&);

  std::istream & operator>> (std::istream &, Product&);
  std::ostream & operator<< (std::ostream &, Product&);

}
#endif