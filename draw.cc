//Seth Giovanetti
//stg160130
//GUI drawing code
//Adapted from example

#include <iostream>
#include <cdk.h>
#include "program6.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

void drawgrid(BinaryFile* file)
{
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 	*rowTitles[MATRIX_WIDTH+1] = {"R0", "R1", "R2", "R3"};
  const char 	*columnTitles[MATRIX_HEIGHT+1] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix(cdkscreen, 
			  CENTER, 
			  CENTER, 
			  MATRIX_HEIGHT, 
			  MATRIX_WIDTH, 
			  MATRIX_HEIGHT,
			  MATRIX_WIDTH, 
			  MATRIX_NAME_STRING, 
			  (char **) columnTitles, 
			  (char **) rowTitles, 
			  boxWidths,
			  boxTypes,
			  1,
			  1, 
			  ' ', 
			  ROW, 
			  true, 
			  true, 
			  false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      exit(1);
    }

  /* Draw the grids with line drawing */
  drawCDKMatrix(myMatrix, true);

  /*
   * Fill cells with text as required
   */
  char* magnum;// = (char*)"SENTINAL";
  char* vernum;// = (char*)"SENTINAL";
  char* renum;// = (char*)"SENTINAL";;
  
  sprintf(magnum, "Magic: %02X", file->header.magicNumber);
  sprintf(vernum, "Version: %u", file->header.versionNumber);
  sprintf(renum, "Records: %u", (unsigned)file->header.numRecords);

  setCDKMatrixCell(myMatrix, 1, 1, magnum );
  setCDKMatrixCell(myMatrix, 1, 2, vernum );
  setCDKMatrixCell(myMatrix, 1, 3, renum );

  /*
  for (unsigned i=0; i < file->records.size(); i++) {
    //setCDKMatrixCell(myMatrix, 2+i, 2, file->records[i].stringBuffer ); 
    cout << file->records[i].stringBuffer << endl;
  }
  */
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* Pause for user validation */
  sleep (10);


  // Cleanup screen
  endCDK();
}
