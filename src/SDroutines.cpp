#include "SDroutines.h"

SDroutines::SDroutines(uint32_t * _sleepTime, uint16_t * _smpLength, Debugger *_d, int16_t (&_ax)[MAX_N_SAMPLES], int16_t (&_ay)[MAX_N_SAMPLES], int16_t (&_az)[MAX_N_SAMPLES]):
ax(_ax),
ay(_ay),
az(_az)
{
  sleepTime = _sleepTime;
  smpLength = _smpLength;
}
SDroutines::~SDroutines()
{}


/*---------->setup
  Sets up the sd card module
*/
bool SDroutines::setup() {
  bool sdTest = SD.begin(SD_PIN);
  d->SDinitialization(sdTest);
  if (sdTest) {
    readSettings();
  }
  return sdTest;
}


/*---------->close
  Closes the sd card module
*/
void SDroutines::close(){
  SD.end();
}


/*---------->readSettings
  Reads settings from a file called config.txt on the sd
*/
void SDroutines::readSettings() {
  myFile = SD.open("config.txt");

  String configs;

  if (d->OpenFile(myFile, "config.txt")) {
    while (myFile.available()) {        // read from the file until there's nothing else in it:
      configs += char(myFile.read());
    }
    myFile.close();             // close the file:
    *sleepTime = (uint32_t)configs.toInt();// Assign to variable
    d->sleepTime((uint32_t)*sleepTime);
  }
}



/* --------> writeToSD
  Retrieve from SRAM memory the data collected and store it on the SD card
*/

void SDroutines::write() {
  myFile = SD.open("/DATA/", FILE_WRITE);

  long newFileId = getLastFile(myFile) + 1;
  String stringFileDir = "/DATA/" + String(newFileId) + ".csv";
  const char * fileDir = stringFileDir.c_str() ;

  myFile = SD.open(fileDir, FILE_WRITE);

  if (d->OpenFile(myFile, fileDir)) {
    d->writeToFile(fileDir);

    String dataString;
    //short am2301 = readAM2301();//read humidity/temperature sensor (returns 1 for success)

    // if (false) {
    //   //      writeFloatToByte(myFile, temp);    //log temperature in bytes
    //   //      writeFloatToByte(myFile, humid);   //log humidity in bytes
    //   debugString = "t," + String(temp) + "," + "h," + String(humid) + "\n";
    // }
    // else {
    //   //writeDhtError(myFile, am2301);    //log error data in byte
    //   debugString = "E," + String(am2301) + "\n";
    // }

    d->print(dataString);
    myFile.print(dataString);

    //loop through each sample to be written to file
    for (uint32_t i = 0; i < *smpLength; i++) {
      //LOG in Bytes
      // writeIntToByte(myFile, ax[i]);
      // writeIntToByte(myFile, ay[i]);
      // writeIntToByte(myFile, az[i]);

      dataString = String(ax[i + 10]) + "\t" + String(ay[i + 10]) + "\t" + String(az[i + 10]) + "\n"; //discard the first 10 samples
      myFile.print(dataString);
      // d->print(dataString);
    }
    d->print(F("Finished writing to SD\n"));
  } else {
    flashLed(5);
  }

  myFile.close();
}



/*------------> getLastFile
  Function that calculates the name of the new file for storing the new
  samples depending on the previous ones.
*/

long SDroutines::getLastFile(File dir) {
  long lastFile = 0;
  boolean finished = false;

  do {
    File entry =  dir.openNextFile();

    if (!entry)   finished = true;
    int entryId = String(entry.name()).toInt();
    if (entryId > lastFile) {
      lastFile = entryId;
    }
    entry.close();
  } while (!finished);
  return lastFile;
}



/*----------> writeFloatToByte
  Write a float variable as 4 bytes to SD
*/

void SDroutines::writeFloatToByte(File &dir, float &data) {
  UNPACKFLOAT newFloat;

  newFloat.f = data;

  dir.write(newFloat.b[0]);
  dir.write(newFloat.b[1]);
  dir.write(newFloat.b[2]);
  dir.write(newFloat.b[3]);
}



/*----------> writeIntToByte
  Write an integer to SD as 2 bytes
*/
void SDroutines::writeIntToByte(File &dir, int16_t &data) {
  uint8_t firstByte = (uint8_t)(data >> 8);
  uint8_t secondByte = (uint8_t)(data & 0xFF);
  dir.write(firstByte);
  dir.write(secondByte);
}



/*---------> writeDhtError
  Write the error code to the SD as 8 bytes
*/

void SDroutines::writeDhtError(File &dir, int &error) {
  dir.write('e');
  dir.write((byte)(-error));
  for (int i = 0; i < 4; i++) {
    dir.write('0');
  }
}

void SDroutines::writeAccError(){
  myFile = SD.open("/DATA/", FILE_WRITE);

  long newFileId = getLastFile(myFile) + 1;
  String stringFileDir = "/DATA/" + String(newFileId) + ".csv";
  const char * fileDir = stringFileDir.c_str() ;

  myFile = SD.open(fileDir, FILE_WRITE);

  if (d->OpenFile(myFile, fileDir)) {
      myFile.print("Accelerometer error\n");
  }
}
