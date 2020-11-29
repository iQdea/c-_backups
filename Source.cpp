#include "iostream"
#include "exception"
#include "FileSystem.h"
#include "StorageArchive.h"
#include "StorageSeparate.h"
#include "Test.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	try {
		FileSystem fileSystem;
		fileSystem.init("filesystem.ini");

		StorageArchive storage1("archive1.ini");
		Test test(&fileSystem, &storage1);
		test.init("test1.ini");

		StorageSeparate storage2("separate2");
		test = Test(&fileSystem, &storage2);
		test.init("test1.ini");

		test = Test(&fileSystem);
		test.init("test1.ini");

		test = Test(&fileSystem);
		test.init("test1.ini");
	}
	catch (exception excep) {
		cout << excep.what() << endl;
	}
	catch (...) {
		cout << "Неизвестная ошибка." << endl;
	}

	return 0;
}