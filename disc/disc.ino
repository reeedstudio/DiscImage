 /* Read Quadrature Encoder
  * Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.
  *
  * Sketch by max wolf / www.meso.net
  * v. 0.1 - very basic functions - mw 20061220
  *
  */
#define N  3

#define N1 30
#define N2 30
#define N3 30
#define N4 150

int numImage[4] = {N1, N2, N3, N4};

int nImage = 0;
int mImage = 0;
int mImage_buf = 0;

int  sum    = 0;
bool getIrq = 0;

int val;
int encoder0PinA = 2;
int encoder0PinB = 3;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup() 
{
    pinMode (encoder0PinA,INPUT);
    pinMode (encoder0PinB,INPUT);
    Serial.begin (115200);
}

void loop() 
{
    n = digitalRead(encoder0PinA);
    if ((encoder0PinALast == LOW) && (n == HIGH)) 
    {
        if (digitalRead(encoder0PinB) == LOW) 
        {
            sum--;
        }
        else 
        {
            sum++;
        }
        sum = (sum == N*400 || sum == N*(-400)) ? 0 : sum;
        getIrq = 1;

    }
    encoder0PinALast = n;
    
    if(getIrq)
    {
        getIrq = 0;
        
        int sum_t = sum;
        sum_t = sum_t<0 ? N*400+sum_t : sum_t;

        nImage = sum_t / 400;
        mImage = sum_t - nImage*400;
        
        mImage = map(mImage, 0, 399, 0, numImage[nImage]-1);
        
        if(mImage != mImage_buf)
        {
            mImage_buf = mImage;
            Serial.print(nImage);
            Serial.print('\t');
            Serial.println(mImage);
        }
    }
    
}