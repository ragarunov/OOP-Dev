#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\opencv.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <deque>
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib" )
using namespace cv;
using namespace std;

enum gesture { OPENPALM = 1, CLOSEDPALM, FINGER, NA };
typedef vector<gesture> Gesture; 
typedef deque<gesture> gestureQ;
gestureQ lastFiveGest;
Gesture enteredGesture;

//cascades
CascadeClassifier open_palm_cascade;
CascadeClassifier closed_palm_cascade;
CascadeClassifier one_finger_cascade;

int enterPassword();
int setPassword();
void loading(double i, double length);

bool isFiveFrames = true;

int main () {
	open_palm_cascade.load("../open_palm_two.xml");
	closed_palm_cascade.load("../fist.xml");
	one_finger_cascade.load("../one_finger_new.xml");

	if (open_palm_cascade.empty()) {
		cout << "Couldn't find open palm cascade";
		waitKey(0);
		return -2;
	}

	else if (closed_palm_cascade.empty()) {
		cout << "Couldn't find closed palm cascade";
		waitKey(0);
		return -2;
	}


	else if (one_finger_cascade.empty()) {
		cout << "Couldn't find one finger cascade";
		waitKey(0);
		return -2;
	}

	int choice = 0;

	cout << endl << "You may enter the following hand gestures: open palm, fist or one finger" << endl << endl;

	do {
		do {
			cout << "Make Choice (1 - Enter Password, 2 - Set Password, 3 - Exit): ";
			cin >> choice;
		} while (choice < 1 || choice > 3);

		if (choice == 1) {
			cout << endl << "=======================" << endl << "ENTER YOUR PASSWORD NOW" << endl << "=======================" << endl;
			enterPassword();
		} 
		else if (choice == 2) {
			cout << endl << "=======================" << endl << "SET YOUR PASSWORD NOW" << endl << "=======================" << endl;
			setPassword();
			cout << endl << "=======================" << endl << "YOUR PASSWORD HAS BEEN SET" << endl << "=======================" << endl;
		}	
	} while (choice != 3);

	return 0;
}


int setPassword() {
	gesture prevGesture = NA;

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "No webcam attached";
		return -1;
	}

	// Start the open_palm and eye detection phase
	vector<Rect> open_palms;
	vector<Rect> closed_palms;
	vector<Rect> fingers;

	ofstream myfile;
	myfile.open ("../password.csv");

	while (char(waitKey(1)) != 'q' && cap.isOpened()) {
		double t0 = getTickCount();
		Mat frame;
		cap >> frame;
		if (frame.empty()) {
			cout << "Video over!";
			break;
		}

		// Detect possibilities.
		open_palm_cascade.detectMultiScale(frame, open_palms, 1.05, 3, 0, Size(100,100));
		closed_palm_cascade.detectMultiScale(frame, closed_palms, 1.05, 10, 0, Size(50, 150));
		one_finger_cascade.detectMultiScale(frame, fingers, 1.02, 4, 0, Size(150, 50));

		if (closed_palms.size() > 0 && closed_palms.size() < 2) {
			for (int i = 0; i < closed_palms.size(); i++) {
				// Top left and bottom right points of rectangle.
				Point closed_palm_rect_p1(closed_palms[i].x, closed_palms[i].y);
				Point closed_palm_rect_p2(closed_palms[i].x + closed_palms[i].width, closed_palms[i].y + closed_palms[i].height);

				// Draw the rectangle in the image.
				rectangle(frame, closed_palm_rect_p1, closed_palm_rect_p2, Scalar(0, 255, 0));
				putText(frame, "Closed Palm", closed_palm_rect_p1, FONT_HERSHEY_SIMPLEX,
					1, Scalar(0, 255, 0), 1, 5, false);

				//make sure prev five frames were closed palm aka must hold gesture for 1 second
				isFiveFrames = true; 
				for (int j = 0; j < lastFiveGest.size() && j < 12; j ++) {
					if (lastFiveGest[j] != CLOSEDPALM)
					{
						isFiveFrames = false;
					}
				}	

				if (lastFiveGest.size() > 11) 
					lastFiveGest.pop_front();
				lastFiveGest.push_back(CLOSEDPALM);

				if (prevGesture != CLOSEDPALM) {
					enteredGesture.push_back(CLOSEDPALM);
					if (isFiveFrames && lastFiveGest.size() > 11) {
						prevGesture = CLOSEDPALM;
						cout << "closed palm set" << endl;
						myfile << 2 << "\n";
					}
				}
			}
		}
		else if (open_palms.size() > 0 && open_palms.size() < 2) {
			for (int i = 0; i < open_palms.size(); i++) {
				//if open palm detected

				// Top left and bottom right points of rectangle.
				Point open_palm_rect_p1(open_palms[i].x, open_palms[i].y);
				Point open_palm_rect_p2(open_palms[i].x + open_palms[i].width, open_palms[i].y + open_palms[i].height);
				// cout << open_palms[i].height << " " << open_palms[i].width;
				// Draw the rectangle in the image.
				rectangle(frame, open_palm_rect_p1, open_palm_rect_p2, Scalar(255, 0, 0));
				putText(frame, "Open Palm", open_palm_rect_p1, FONT_HERSHEY_SIMPLEX,
					1, Scalar(255, 0, 0), 1, 5, false);

				//make sure prev five frames were open palm aka must hold gesture for 1 second
				isFiveFrames = true; 
				for (int j = 0; j < lastFiveGest.size() && j < 12; j ++) {
					if (lastFiveGest[j] != OPENPALM)
					{
						isFiveFrames = false;
					}
				}	

				if (lastFiveGest.size() > 11) 
					lastFiveGest.pop_front();
				lastFiveGest.push_back(OPENPALM);

				if (prevGesture != OPENPALM) {
					enteredGesture.push_back(OPENPALM);
					if (isFiveFrames && lastFiveGest.size() > 11) {
						prevGesture = OPENPALM;
						cout << "open palm set" << endl;
						myfile << 1 << "\n";
					}
				}
			}
		}
		else if (fingers.size() > 0 && fingers.size() < 2) {

			for (int i = 0; i < fingers.size(); i++) {
				// Top left and bottom right points of rectangle.
				Point closed_palm_rect_p1(fingers[i].x, fingers[i].y);
				Point closed_palm_rect_p2(fingers[i].x + fingers[i].width, fingers[i].y + fingers[i].height);

				// Draw the rectangle in the image.
				rectangle(frame, closed_palm_rect_p1, closed_palm_rect_p2, Scalar(0, 255, 0));
				putText(frame, "One Finger", closed_palm_rect_p1, FONT_HERSHEY_SIMPLEX,
					1, Scalar(0, 0, 255), 1, 5, false);
				//make sure prev five frames were closed palm aka must hold gesture for 1 second
				isFiveFrames = true; 
				for (int j = 0; j < lastFiveGest.size() && j < 12; j ++) {
					if (lastFiveGest[j] != FINGER)
					{
						isFiveFrames = false;
					}
				}	

				if (lastFiveGest.size() > 11) 
					lastFiveGest.pop_front();
				lastFiveGest.push_back(FINGER);

				if (prevGesture != FINGER) {
					enteredGesture.push_back(FINGER);
					if (isFiveFrames && lastFiveGest.size() > 11) {
						prevGesture = FINGER;
						cout << "one finger set" << endl;
						myfile << 3 << "\n";
					}
				}
			}
		}


		imshow("Secret Handshake", frame);
	}
	return 0;
}

int enterPassword() {
	int currEl = 0;
	vector<int> passwordArray;
	//check if a password is set
	std::ifstream filePassword("../password.csv");
	if(filePassword.fail()){
		cout << "Password not set" << endl;
		return 2;
	}

	string line;

	for (int i = 0; getline(filePassword, line); i++) {
		passwordArray.push_back(stoi(line));
	}


	gesture prevGesture = NA;

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "No webcam attached";
		return -1;
	}

	// Start the open_palm and eye detection phase
	vector<Rect> open_palms;
	vector<Rect> closed_palms;
	vector<Rect> fingers;

	while (char(waitKey(1)) != 'q' && cap.isOpened()) {
		double t0 = getTickCount();
		Mat frame;
		cap >> frame;
		if (frame.empty()) {
			cout << "Video over!";
			break;
		}

		if (passwordArray.size() == currEl) {
			cout << endl << "=======================" << endl << "PASSWORD UNLOCKED" << endl << "=======================" << endl;
			cout << endl << "You may enter the clubhouse." << endl;
			return 0;
		}

		loading((double)currEl, passwordArray.size());
		// Detect possibilities.
		open_palm_cascade.detectMultiScale(frame, open_palms, 1.05, 2, 0, Size(85,95));
		closed_palm_cascade.detectMultiScale(frame, closed_palms, 1.05, 3, 0, Size(25, 75));
		one_finger_cascade.detectMultiScale(frame, fingers, 1.01, 2, 0, Size(75, 200));

		if (closed_palms.size() > 0 && closed_palms.size() < 2) {
			for (int i = 0; i < closed_palms.size(); i++) {
				// Top left and bottom right points of rectangle.
				Point closed_palm_rect_p1(closed_palms[i].x, closed_palms[i].y);
				Point closed_palm_rect_p2(closed_palms[i].x + closed_palms[i].width, closed_palms[i].y + closed_palms[i].height);

				// Draw the rectangle in the image.
				rectangle(frame, closed_palm_rect_p1, closed_palm_rect_p2, Scalar(0, 255, 0));
				putText(frame, "Closed Palm", closed_palm_rect_p1, FONT_HERSHEY_SIMPLEX,
					1, Scalar(0, 255, 0), 1, 5, false);

				//make sure prev five frames were closed palm aka must hold gesture for 1 second
				isFiveFrames = true; 
				for (int j = 0; j < lastFiveGest.size() && j < 12; j ++) {
					if (lastFiveGest[j] != CLOSEDPALM)
					{
						isFiveFrames = false;
					}
				}	

				if (lastFiveGest.size() > 11) 
					lastFiveGest.pop_front();
				lastFiveGest.push_back(CLOSEDPALM);

				if (prevGesture != CLOSEDPALM) {
					enteredGesture.push_back(CLOSEDPALM);
					if (isFiveFrames && lastFiveGest.size() > 11) {
						prevGesture = CLOSEDPALM;
						cout << " > closed palm entered" << endl;
						if (passwordArray[currEl] == 2)
							currEl++;
						else {
							cout << "wrong password" << endl;
							return 0;
						}
					}
				}
			}
		}
		else if (open_palms.size() > 0 && open_palms.size() < 2) {
			for (int i = 0; i < open_palms.size(); i++) {
				//if open palm detected

				// Top left and bottom right points of rectangle.
				Point open_palm_rect_p1(open_palms[i].x, open_palms[i].y);
				Point open_palm_rect_p2(open_palms[i].x + open_palms[i].width, open_palms[i].y + open_palms[i].height);
				// cout << open_palms[i].height << " " << open_palms[i].width;
				// Draw the rectangle in the image.
				rectangle(frame, open_palm_rect_p1, open_palm_rect_p2, Scalar(255, 0, 0));
				putText(frame, "Open Palm", open_palm_rect_p1, FONT_HERSHEY_SIMPLEX,
					1, Scalar(255, 0, 0), 1, 5, false);

				//make sure prev five frames were open palm aka must hold gesture for 1 second
				isFiveFrames = true; 
				for (int j = 0; j < lastFiveGest.size() && j < 12; j ++) {
					if (lastFiveGest[j] != OPENPALM)
					{
						isFiveFrames = false;
					}
				}	

				if (lastFiveGest.size() > 11) 
					lastFiveGest.pop_front();
				lastFiveGest.push_back(OPENPALM);

				if (prevGesture != OPENPALM) {
					enteredGesture.push_back(OPENPALM);
					if (isFiveFrames && lastFiveGest.size() > 11) {
						prevGesture = OPENPALM;
						cout << " > open palm entered" << endl;
						if (passwordArray[currEl] == 1)
							currEl++;
						else {
							cout << "wrong password" << endl;
							return 0;
						}
					}
				}
			}
		}
		else if (fingers.size() > 0 && fingers.size() < 2) {

			for (int i = 0; i < fingers.size(); i++) {
				// Top left and bottom right points of rectangle.
				Point closed_palm_rect_p1(fingers[i].x, fingers[i].y);
				Point closed_palm_rect_p2(fingers[i].x + fingers[i].width, fingers[i].y + fingers[i].height);

				// Draw the rectangle in the image.
				rectangle(frame, closed_palm_rect_p1, closed_palm_rect_p2, Scalar(0, 255, 0));
				putText(frame, "One Finger", closed_palm_rect_p1, FONT_HERSHEY_SIMPLEX,
					1, Scalar(0, 0, 255), 1, 5, false);
				//make sure prev five frames were closed palm aka must hold gesture for 1 second
				isFiveFrames = true; 
				for (int j = 0; j < lastFiveGest.size() && j < 12; j ++) {
					if (lastFiveGest[j] != FINGER)
					{
						isFiveFrames = false;
					}
				}	

				if (lastFiveGest.size() > 11) 
					lastFiveGest.pop_front();
				lastFiveGest.push_back(FINGER);

				if (prevGesture != FINGER) {
					enteredGesture.push_back(FINGER);
					if (isFiveFrames && lastFiveGest.size() > 11) {
						prevGesture = FINGER;
						cout << " > one finger entered" << endl;
						if (passwordArray[currEl] == 3)
							currEl++;
						else {
							cout << "wrong password" << endl;
							return 0;
						}
					}
				}
			}
		}


		imshow("Secret Handshake", frame);
	}
	return 0;
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