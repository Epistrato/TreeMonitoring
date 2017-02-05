#include <ACCroutines.h>


Accelerometer::Accelerometer(Debugger *_d, int16_t (&_ax)[MAX_N_SAMPLES], int16_t (&_ay)[MAX_N_SAMPLES], int16_t (&_az)[MAX_N_SAMPLES]):
d(_d),
ax(_ax),
ay(_ay),
az(_az)
{
    accelerometer = *(new MPU6050);
};

// Accelerometer::~Accelerometer()
// {};

/*---------->setupAcc
  Initializes the accelerometer
*/
bool Accelerometer::setup()
{
  Wire.begin();

  d->print(F("Initializing accelerometer..."));
  accelerometer.initialize();
  boolean connectionTest = accelerometer.testConnection();
  d->print(connectionTest ? " Successful.\n" : " Failed.\n");

  return connectionTest;
};



/*---------->sampleAccelerometer
  Stores new values from the accelerometer in the ax, ay, az variables
  and then stores them on the external sram
*/
void Accelerometer::sample(int i)
{
  accelerometer.getAcceleration(&ax[i], &ay[i], &az[i]); //sample accelerometer
};
