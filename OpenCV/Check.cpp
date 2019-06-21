#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <windows.h>
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib" )

using namespace cv;
using namespace std;

	bool gt [361];
	bool palm_res [361];
	bool fist_gt [89];
	bool fists_res [89];
	bool finger_gt [92];
	bool finger_res [92];
	bool pred [19];
	bool * random;
	double cont [19];
	double P = 0;
	double R = 0;
	double PRvals [9];
	Mat img1;
	Mat imgPred;
	Mat imgGt;


	CascadeClassifier open_palm_cascade;
	CascadeClassifier closed_palm_cascade;
	CascadeClassifier one_finger_cascade;


	void readPalmGTFiles();
	void readPalmResults();
	void checkPalm();

	void readFistGTFiles();
	void readFistResults();
	void checkFist();

	void readFingerGTFiles();
	void readFingerResults();
	void checkFinger();

	void genRandomBool(int length);
	void loading(double i, double length);

	int calcPR(bool *pred, bool *gt, int len, double *P, double *R);
	double calcFb(double P, double R, double beta);



	int main (int argc, char** argv) {

		open_palm_cascade.load("../open_palm_two.xml");
		closed_palm_cascade.load("../fist.xml");
		one_finger_cascade.load("../one_finger_new.xml");

		if (open_palm_cascade.empty()) {
			cout << "Couldn't find open palm cascade";
			waitKey(0);
			return -2;
		}

		if (one_finger_cascade.empty()) {
			cout << "Couldn't find one finger cascade";
			waitKey(0);
			return -2;
		}

		if (closed_palm_cascade.empty()) {
			cout << "Couldn't find closed palm cascade";
			waitKey(0);
			return -2;
		}

		int choice = 0;

		do {
			do {
				cout << "Make Choice (1: Open Palm | 2: Closed Palm | 3: Finger): ";
				cin >> choice;
			} while (choice < 1 || choice > 3);

			if (choice == 1) {
				readPalmGTFiles(); //read ground truth 
				checkPalm(); //run algo on images in test
				readPalmResults(); //copy results to bool array

				calcPR(palm_res, gt, (sizeof(palm_res)/sizeof(*palm_res)), &P, &R);

				cout << "P = " << P << " R = " << R << endl;

				cout << "FB = " << calcFb(P, R, 1) << endl << endl;


				cout << "Random Palm Prediction: " << endl;
				genRandomBool(361);

				calcPR(random, gt, (sizeof(palm_res)/sizeof(*palm_res)), &P, &R);

				cout << "P = " << P << " R = " << R << endl;

				cout << "FB = " << calcFb(P, R, 1) << endl << endl;
			} 
			else if (choice == 2) {
				readFistGTFiles(); //read ground truth 
				checkFist(); //run algo on images in test
				readFistResults(); //copy results to bool array

				calcPR(fists_res, fist_gt, (sizeof(fists_res)/sizeof(*fists_res)), &P, &R);

				cout << "P = " << P << " R = " << R << endl;

				cout << "FB = " << calcFb(P, R, 1) << endl << endl;

				cout << "Random Fist Prediction: " << endl;
				genRandomBool(89);

				calcPR(random, fist_gt, (sizeof(fists_res)/sizeof(*fists_res)), &P, &R);

				cout << "P = " << P << " R = " << R << endl;

				cout << "FB = " << calcFb(P, R, 1) << endl << endl;

			}
			else if (choice == 3) {
				readFingerGTFiles(); //read ground truth 
				checkFinger(); //run algo on images in test
				readFingerResults(); //copy results to bool array

				calcPR(finger_res, finger_gt, (sizeof(finger_res)/sizeof(*finger_res)), &P, &R);

				cout << "P = " << P << " R = " << R << endl;

				cout << "FB = " << calcFb(P, R, 1) << endl << endl;

				cout << "Random Finger Prediction: " << endl;
				genRandomBool(92);

				calcPR(random, finger_gt, (sizeof(finger_res)/sizeof(*finger_res)), &P, &R);

				cout << "P = " << P << " R = " << R << endl;

				cout << "FB = " << calcFb(P, R, 1) << endl << endl;
			}
			else if (choice == 4) {

			}
		} while (choice != 5);

		return 0;
	}

	int calcPR(bool *pred, bool *gt, int len, double *P, double *R) {
		double FP = 0, TP = 0, FN = 0, TN = 0;
		for (int j = 0; j < len; j++) {
			if (*(pred + j) && !(*(gt + j)))
				FP++;
			else if (*(pred + j) && (*(gt + j)))
				TP++;
			else if (!*(pred + j) && !(*(gt + j)))
				TN++;
			else if (!*(pred + j) && (*(gt + j)))
				FN++;
		}
		if (TP != 0) {
			*P = TP / (TP + FP);
			*R = TP / (TP + FN);
		} else {
			*P = 0;
			*R = 0;
		}

		return 1;
	}

	double calcFb(double P, double R, double beta) {
		if (P == 0 || R == 0)
			return 0;
		return ((1 + (beta * beta)) * ((P * R) / ((beta * beta) * P + R)));
	}

	void readPalmGTFiles() {
		std::ifstream fileGt("../PalmGT.csv");
		string line;
		for (int i = 0; getline(fileGt, line); i++) {
			gt[i] = stod(line);
		}
		cout << "Files Read" << endl;
	}

	void readPalmResults() {
		std::ifstream filePalm("../palm_results.csv");
		string line;
		for (int i = 0; getline(filePalm, line); i++) {
			palm_res[i] = stod(line);
		}
		cout << "\n\nPalm Results Read" << endl;
	}

	void checkPalm() {
		vector<Rect> open_palms;
		vector<Rect> l_palms;
		vector<Rect> r_palms;
		std::stringstream stream;
		int numTemp = 0;

		std::ofstream myfile;
		myfile.open ("../palm_results.csv");

		for (double i = 0; i < 361; i ++) {
			numTemp = 10000 + i;
			stream.str(std::string());
			stream << "../TestPalm/hand-" << numTemp << ".jpg";

			loading(i, 361);

			Mat imgTemp = imread(stream.str());
			open_palm_cascade.detectMultiScale(imgTemp, open_palms, 1.05, 2, 0, Size(30,30));
			if (open_palms.size() != 0)
				myfile << 1 << "\n";
			else {
				myfile << 0 << "\n";
			}
		}

		myfile.close();
	}


	void readFistGTFiles() {
		std::ifstream fileGt("../FistGT.csv");
		string line;
		for (int i = 0; getline(fileGt, line); i++) {
			fist_gt[i] = stod(line);
		}
		cout << "Files Read" << endl;
	}

	void readFistResults() {
		std::ifstream filePalm("../fist_results.csv");
		string line;
		for (int i = 0; getline(filePalm, line); i++) {
			fists_res[i] = stod(line);
		}
		cout << "\n\nFist Results Read" << endl;
	}

	void checkFist() {
		vector<Rect> fists;
		std::stringstream stream;
		int numTemp = 0;
		double length = 89;

		std::ofstream myfile;
		myfile.open ("../fist_results.csv");

		for (double i = 0; i < length; i ++) {
			numTemp = 101 + i;
			stream.str(std::string());
			stream << "../TestFist/hand-" << numTemp << ".jpg";

			loading(i, length);

			Mat imgTemp = imread(stream.str());
			closed_palm_cascade.detectMultiScale(imgTemp, fists, 1.05, 3, 0, Size(25, 75));
			if (fists.size() != 0)
				myfile << 1 << "\n";
			else {
				myfile << 0 << "\n";
			}
		}

		myfile.close();
	}

	// one finger cascade functions
	void readFingerGTFiles() {
		std::ifstream fileGt("../FingerGT.csv");
		string line;
		for (int i = 0; getline(fileGt, line); i++) {
			finger_gt[i] = stod(line);
		}
		cout << "Files Read" << endl;
	}

	void readFingerResults() {
		std::ifstream fileFinger("../finger_results.csv");
		string line;
		for (int i = 0; getline(fileFinger, line); i++) {
			finger_res[i] = stod(line);
		}
		cout << "\n\nFinger Results Read" << endl;
	}

	void checkFinger() {
		vector<Rect> finger;
		std::stringstream stream;
		int numTemp = 0;
		double length = 92;

		std::ofstream myfile;
		myfile.open ("../finger_results.csv");

		for (double i = 0; i < length; i ++) {
			numTemp = 1000 + i;
			stream.str(std::string());
			stream << "../TestFinger/hand-" << numTemp << ".jpg";

			loading(i, length);

			Mat imgTemp = imread(stream.str());
			one_finger_cascade.detectMultiScale(imgTemp, finger, 1.01, 2, 0, Size(20, 75));
			if (finger.size() != 0)
				myfile << 1 << "\n";
			else {
				myfile << 0 << "\n";
			}
		}

		myfile.close();
	}

	void genRandomBool(int length) {
		random = new bool [length];

		for (int i = 0; i < length; i ++) {
			random[i] = rand() % 2;
		}
	}

	void loading(double i, double length) {
		if ((i / length) * 100 < 10) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b:.........   0%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 20) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b.:........   10%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 30) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b..:.......   20%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 40) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b...:......   30%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 50) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b....:.....   40%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 60) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b.....:....   50%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 70) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b......:...   60%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 80) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b.......:..   70%" << std::flush;
			Sleep(10);
		}
		else if ((i / length) * 100 < 90) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b........:.   80%" << std::flush;
			Sleep(10);
		}

		else if ((i / length) * 100 < 100) {
			std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b.........:   90%" << std::flush;
			Sleep(10);
		}


}
	