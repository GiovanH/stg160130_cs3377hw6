//Seth Giovanetti
//stg160130

using namespace std;

#include <stdint.h> //For uint types
#include <vector>

class BinaryFileHeader
{
public:
  uint32_t magicNumber; /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};

/*
 * Records in the file have a fixed length buffer
 * that will hold a C-Style string. This is the
 * size of the fixed length buffer.
 */
const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

class BinaryFile{ //This class allows us to return an entire binary file from a function. 
public:
  BinaryFileHeader header;
  vector<BinaryFileRecord> records;
  //ok, so, since we TECHNICALLY know the number of records in the file, this could be turned into a serializable array, but that is WAY beyond the scope of this project
};


int main();
void drawgrid(BinaryFile*);
BinaryFile* readBinFile(const char* filename);
