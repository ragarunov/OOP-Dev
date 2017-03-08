#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include "Date.h"
#include "ErrorMessage.h"
#include "Streamable.h"
#include "Product.h"
#include "AmaProduct.h"
#include "AmaPerishable.h"
#include "general.h"
using namespace std;
namespace sict {
	class AidApp {
		char filename_[256];
		Product * product_[MAX_NO_RECS];
		fstream datafile_;
		int noOfProducts_;

		void pause() const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts() const;
		int SearchProducts(const char* sku) const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);
		AidApp(const AidApp&) = delete;
		AidApp& operator=(const AidApp&) = delete;

	public:
		
		AidApp(const char* filename);
		int run();

	};
}
#endif