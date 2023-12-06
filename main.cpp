#include "FaceBook.h"

int main() {
	try {
		FaceBook faceBook;//inside the ctor data extraction is in progress, if the data exist
		while (faceBook.getActiveFaceBook()) {
			FaceBook::performUserSelection(faceBook);
		}
		faceBook.DataToBinFile();//Upload the data to bin file
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception caught: " << e.what() << endl;
	}
}
