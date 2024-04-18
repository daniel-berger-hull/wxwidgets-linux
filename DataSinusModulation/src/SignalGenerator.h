#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#define MAX_SAMPLE_SIZE  10000


struct SignalParam
{
   unsigned int nbrSamples;
   int maxAmplitude;
};

class SignalGenerator
{
    public:
        SignalGenerator();
        virtual ~SignalGenerator();

//        bool generate(int sampleSize);
        bool generate(SignalParam params);



        bool isValidSampleSize(int sampleSize);

        int *  getSignalBuffer()            {  return signalBuffer;  }
        unsigned int getBufferSize()        {  return bufferSize;    }


    private:

        int *signalBuffer = nullptr;
        unsigned int bufferSize = 0;
};

#endif // SIGNALGENERATOR_H
