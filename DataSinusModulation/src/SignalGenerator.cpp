#include "SignalGenerator.h"
#include <math.h>

SignalGenerator::SignalGenerator()
{
    //ctor
}

SignalGenerator::~SignalGenerator()
{
    if (signalBuffer != nullptr)   delete signalBuffer;

}

bool SignalGenerator::isValidSampleSize(int sampleSize)
{
    if (sampleSize <= 0 || sampleSize > MAX_SAMPLE_SIZE)
       return false;
    else
       return true;
}






//bool SignalGenerator::generate(int sampleSize)
bool SignalGenerator::generate(SignalParam params)
{

   //int signalAmplitude = 200;
   //int baseLine = signalAmplitude / 2;

   double angle,delta,result;

   if ( !isValidSampleSize(params.nbrSamples) )  return false;

    // Make sure that any previous data is cleaned first...
    if (signalBuffer != nullptr)   delete signalBuffer;

    signalBuffer = new int[params.nbrSamples];


    /*
    struct SignalParam
{
   unsigned int nbrSample;
   int maxAmplitude;
} */



    angle = 0.0;
    //delta = (2.0 * M_PI) / sampleSize;
    delta = (2.0 * M_PI) / params.nbrSamples;

    int signalRadius = params.maxAmplitude / 2;     // Amplitude is from peak to peak, so the sin function requires half of that
    for (int i=0;i<params.nbrSamples;i++)
    {
    //    float value = (sin(angle) * signalAmplitude) - baseLine;
        float value = sin(angle) * signalRadius;


        //signalBuffer[i] = -125 +  (i % 255);
        signalBuffer[i] = (int)value;

        angle += delta;
    }

    bufferSize = params.nbrSamples;

    return true;
}

