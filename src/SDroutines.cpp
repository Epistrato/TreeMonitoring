#include "SDroutines.h"

/*---------->Constructor
*/
SDroutines::SDroutines(uint32_t * _sleepTime, uint16_t * _smpLength, Debugger *_d, int16_t (&_ax)[MAX_N_SAMPLES], int16_t (&_ay)[MAX_N_SAMPLES], int16_t (&_az)[MAX_N_SAMPLES]):
ax(_ax),
ay(_ay),
az(_az)
{
  sleepTime = _sleepTime;
  smpLength = _smpLength;
}


/*---------->Destructor
*/
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
  File myFile = SD.open("config.txt");
  d->OpenFile(myFile, "config.txt");
  String configs;

  if (myFile) {
    while (myFile.available()) {        // read from the file until there's nothing else in it:
      configs += char(myFile.read());
    }
    myFile.close();             // close the file:
    *sleepTime = (uint32_t)configs.toInt();// Assign to variable
    d->sleepTime((uint32_t)*sleepTime);
  }
}


/*---------->getLogPath
  Get Path for saving new log
*/
String SDroutines::getLogPath(String dateTimeString){
  String logPathString = getLogDir(dateTimeString);
  logPathString += dateTimeString.substring(8);
  logPathString += ".csv";
  return logPathString;
}


/* --------> getLogDir
  Format string with directory where to save new log file
*/
String SDroutines::getLogDir(String dateTimeString){
  String logDirString = getDataDir();
  String logDateDirString = logDirString;
  logDateDirString += dateTimeString.substring(2,8)+"/";
  // Convert to char array
  char *logDateDirC = const_cast<char*>(logDateDirString.c_str());
  // Check if Date Directory exists, if not create it.
  if (!SD.exists(logDateDirC)){
    SD.mkdir(logDateDirC);
  }
  // Check if directory exists (created or existed before)
  if (SD.exists(logDateDirC)){
    logDirString = logDateDirString;
  }
  else{
    d->println(F("WARNING   --    Could not find or create directory YYYY/MM/DD."));
  }
  return logDirString;
}


/* --------> getDataDir
  Format string with "/DATA/"" directory if directory exists, else "/"
*/
String SDroutines::getDataDir(){
  String dataPathString;
  // If directory "Data" doesn't exists, create it
  if (!SD.exists(_DATA_DIR)){ SD.mkdir(_DATA_DIR);}
  // Check if directory exists again and format string accordingly
  if (SD.exists(_DATA_DIR)){
    dataPathString = _DATA_DIR;
  }else{
    d->println(F("WARNING   --    Could not find or create directory DATA. Unable to save data."));
    dataPathString = "/";
  }
  return dataPathString;
}


/* --------> logData
  Retrieve from SRAM memory the data collected and store it on the SD card
*/
void SDroutines::logData(String dateTimeString) {
  String filePathString = getLogPath(dateTimeString).c_str();
  File myFile = SD.open(filePathString.c_str(), FILE_WRITE);
  d->OpenFile(myFile, filePathString);
  if (myFile) {
    d->writeToFile(filePathString);
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
    //
    // d->print(dataString);
    // myFile.print(dataString);

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
  Write the DHT error code to the SD as 8 bytes
*/
void SDroutines::writeDhtError(File &dir, int &error) {
  dir.write('e');
  dir.write((byte)(-error));
  for (int i = 0; i < 4; i++) {
    dir.write('0');
  }
}


/*---------> writeAccError
  Write the error code for the accelerometer
*/
void SDroutines::writeAccError(String dateTimeString){
  const char * filePath = getLogPath(dateTimeString).c_str();
  File myFile = SD.open(filePath, FILE_WRITE);

  if (d->OpenFile(myFile, filePath)) {
      myFile.print("Accelerometer error\n");
  }
}
