#include "ErrorMessage.h"
#include <cstring>
namespace sict{

	ErrorMessage::ErrorMessage() {

		message_ = nullptr;

	}

	ErrorMessage::ErrorMessage(const char* errorMessage) {

		message_ = nullptr;
		message(errorMessage);

	}

	ErrorMessage& ErrorMessage::operator=(const char* errorMessage) {

		clear();
		message(errorMessage);

		return *this;

	}

	ErrorMessage::~ErrorMessage() {

		delete message_;

	}

	void ErrorMessage::clear() {

		delete message_;
		message_ = nullptr;

	}

	bool ErrorMessage::isClear() const {

		return message_ == nullptr;

	}

	void ErrorMessage::message(const char* value) {

		delete message_;
		message_ = new char [strlen(value)+1];
		strcpy(message_, value);

	}

	const char* ErrorMessage::message() const {

		return message_;

	}

	std::ostream & operator<< (std::ostream & out, const ErrorMessage& dsp) {

		if (dsp.isClear() != 0) {

			out << dsp.message();

		}

		return out;

	}


}