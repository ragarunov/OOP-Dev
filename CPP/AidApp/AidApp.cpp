#include "AidApp.h"

namespace sict {

	AidApp::AidApp(const char* filename) {

		strcpy(filename_, filename);
		*product_ = nullptr;
		noOfProducts_ = 0;
		loadRecs();

	}


	void AidApp::pause() const {

		cout << "Press Enter to continue..." << endl;
		cin.get();

	}

	int AidApp::menu() {

		int selection;

		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> selection;
		cin.clear();

		if (selection > 5 || selection < 0) { 
			
			return -1;

		
		}

		return selection;

	}

	void AidApp::loadRecs() {

		int readIndex = 0;
		char t;

		datafile_.open(filename_, ios::in);

		if (datafile_.fail()) {

			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_, ios::out);
			datafile_.close();

		}

		else {
					
			while (!datafile_.fail()) {

				if (!product_[readIndex]) delete [] product_[readIndex];
				
				datafile_.get(t);

				if (t == 'P') {

					AmaPerishable* pProduct = new AmaPerishable;
					product_[readIndex] = pProduct;

				}

				else if (t == 'N') {

					AmaProduct* nProduct = new AmaProduct;
					product_[readIndex] = nProduct;

				}

				if (t == 'N' || t == 'P') {

					datafile_.get(t);
					product_[readIndex]->load(datafile_);
					readIndex++;

				}

			}

		}

		noOfProducts_ = readIndex;
		datafile_.close();

	}

	void AidApp::saveRecs() {

		datafile_.open(filename_, ios::out);

		for (int i = 0; i < noOfProducts_; i++) {

			product_[i]->store(datafile_, true);

		}

		datafile_.close();

	}

	void AidApp::listProducts() const {

		double cost = 0;

		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		
		for (int i = 0; i < noOfProducts_; ++i) {

			cout << right << setw(4) << (i+1);
			cout << " | " << *product_[i] << endl;

			if (i == 10) {

				cin.ignore();
				pause();

			}

			cost += product_[i]->cost() * product_[i]->quantity();

		}

		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << cost << endl;

	}

	int AidApp::SearchProducts(const char* sku)const {

		for (int i = 0; i < noOfProducts_; i++) {

			if (strcmp(sku, product_[i]->sku()) == 0) {

				return i;

			}

		}

		return -1;

	}


	void AidApp::addQty(const char* sku) {

		int q = SearchProducts(sku);
		int input;
		int tooMuch;
		int back;

		if (q == -1) {

			cout << "Not found!" << endl;

		}

		else {

			product_[q]->write(cout, false);
			cout << endl << "Please enter the number of purchased items: ";
			cin >> input;

			if (cin.fail()) cout << "Invalid quantity value!" << endl;
			else {

				if (input <= product_[q]->qtyNeeded() - product_[q]->quantity()) {

					*product_[q] += input;
				
				}

				else {

					tooMuch = product_[q]->qtyNeeded() - product_[q]->quantity();
					back = input - tooMuch;

					cout << "Too many items; only " << tooMuch << " is needed, please return the extra " << back << " items." << endl;

					*product_[q] += tooMuch;

				}

				saveRecs();
				cout << "Updated!" << endl;
				cin.clear();
				cin.ignore();

			}

		}

	}


	void AidApp::addProduct(bool isPerishable) {
		
		noOfProducts_++;

		if (isPerishable) {

			AmaPerishable* pProduct = new AmaPerishable;

			pProduct->read(cin);

			if (cin.fail()) cout << *pProduct << endl;

			else {

				product_[noOfProducts_ - 1] = pProduct;
				saveRecs();
				cout << "Product added" << endl;

			}


		}

		else {

			AmaProduct * nProduct = new AmaProduct;

			nProduct->read(cin);

			if (cin.fail()) cout << *nProduct << endl;

			else {

				product_[noOfProducts_ - 1] = nProduct;
				saveRecs();
				cout << "Product added" << endl;

			}

		}

	}


	int AidApp::run() {

		int ini = -1;
		char sku[MAX_SKU_LEN];

		while (ini != 0) {

			int ini = menu();
			cout << endl;

			if (ini == 1) {

				listProducts();
				cout << endl;
				pause();

			}

			else if (ini == 2) {

				cout << "Please enter the SKU: ";
				cin >> sku;
				
				int search = SearchProducts(sku);

				if (search != -1) {

					product_[search]->write(cout, false);
					cout << endl;

				}

				else {

					cout << "Not found!" << endl;

				}

				cout << endl;

			}

			else if (ini == 3) {

				addProduct(false);
				loadRecs();
				cout << endl;

			}

			else if (ini == 4) {

				addProduct(true);
				loadRecs();
				cout << endl;

			}

			else if (ini == 5) {

				cout << "Please enter the SKU: ";
				cin >> sku;

				addQty(sku);
				cout << endl;

			}

			else if (ini == 0) {

				cout << "Goodbye!!" << endl;
				exit(0);

			}

			else {

				cout << "===Invalid Selection, try again.===" << endl;
				pause();
				cin.ignore();

			}

		}
		
		return 0;

	}

}