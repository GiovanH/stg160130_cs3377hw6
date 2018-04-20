//Seth Giovanetti
//stg160130

#include "program6.h"
#include <iostream>

using namespace std;

int main(){
  //We use binary file IO to read a binary file.
  //This binary file contains 1 header record and then a set (unspecified size) of data records. 
  //BinaryFileHeader and BinaryFileRecord classes
  //Our BinaryFile class handles this.

  BinaryFile* f = readBinFile("cs3377.bin");

  cout << "Magic number: " << f->header.magicNumber << endl;
  cout << "Version number: " << f->header.versionNumber << endl;
  cout << "Number of records: " << f->header.numRecords << endl;

  for (unsigned i=0; i < f->records.size(); i++) {
    cout << i << ": " << f->records[i].stringBuffer << endl;
  }

  drawgrid(f);
  return 0;
}
