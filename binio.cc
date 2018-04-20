//Seth Giovanetti
//stg160130

#include "program6.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

BinaryFile* readBinFile(const char* fileName){
  BinaryFile* file = new BinaryFile(); //Create a data structure to store our results.

  //Open a file in binary mode, check to make sure it's good.
  ifstream binInFile(fileName, ios::in | ios::binary);
  if (!binInFile.good()){
    cout << "Bad file!" << endl;
    exit(1);
  }

  //OK so this gets into some messy pointer business, so let me explain. 

  //header is a pointer. The value of the pointer is the pointer to the file's header.
  BinaryFileHeader* header = &(file->header);
  //Now we read data directly in to the file's header, USING that pointer.
  binInFile.read(((char*)header), sizeof(BinaryFileHeader));

  //We will be referring to file->records as "records." This shouldn't allocate any memory.
  vector<BinaryFileRecord> records = file->records;
  //Now we loop over the file using the number of records we expect based on the header.
  for (unsigned i = 0; i < file->header.numRecords; i++){
    //For each file, we make a record, read to the record, and push the record to the vector.
    BinaryFileRecord *r = new BinaryFileRecord();
    binInFile.read((char*)r, sizeof(BinaryFileRecord));
    file->records.push_back(*r);
  }
  return file;
} 
