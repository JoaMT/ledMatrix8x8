//www.elegoo.com
//2016.12.12

const int latch=7;  //74HC595  pin 9 STCP       10
const int clock=8; //74HC595  pin 10 SHCP       11
const int data=6;   //74HC595  pin 8 DS          9

const unsigned char lineScan[]=
{0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

const int fpsDelay=6; // frame duration

int linesRefresh=0;
int fotograma=0;
int frame=fpsDelay;
unsigned char pantalla[8] = 
    {B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
unsigned char pantalla2[12] = 
    {B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

void setup() {
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(data,OUTPUT);

  randomSeed(analogRead(0));
}

void loop() { //efectoAnimacionTetris();
  switch(random(9)) {
    case 0:
      efectoRandomOff();
    break;
    case 1:
      efectoAnimacionTetris();
    break;
    case 2:
      efectoAnimacionLlenaEsquinas();
    break;
    case 3:
      efectoAnimacionOlas();
    break;
    case 4:
      efectoAnimacionHelice();
    break;
    case 5:
      efectoAnimacionSnakes();
    break;
    case 6:
      efectoAnimacionSaludo();
    break;
    case 7:
      efectoAnimacionOnda();
    break;
    case 8:
      efectoAnimacionBarrotes();
    break;
  }
  //efectoPrueba();
}

bool displayLedMatrix(){
  
  for (int num = 0; num < 8; num++) {    
     digitalWrite(latch, LOW) ;
     shiftOut(data, clock, LSBFIRST, lineScan[num]); 
     shiftOut(data, clock, MSBFIRST, pantalla[num]);
     digitalWrite(latch, HIGH);
  }
  if (++linesRefresh>6){
    linesRefresh=0;
    if (--frame<1) {
       frame=fpsDelay;
       return true;
    }
  }
  return false; 
}

void efectoRandomOff() {
  for (int num=0;num<8;num++){
    pantalla[num]=255;
  }
  while (fotograma<96){
    if (displayLedMatrix()){
      fotograma++;
      if (fotograma>86) {
        pantalla[fotograma-87]=0;
      } else {
        bitWrite(pantalla[random(8)],random(8),false);
      }
    }
  } fotograma=0;
}

void efectoAnimacionTetris() {
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  int count=0;
  while (fotograma<96){
    if (displayLedMatrix()){
      if (--count<1 && fotograma<88) {
        count=6;
        tetrisFicha(random(2));
        //tetrisFicha(1); tetrisFicha(1); tetrisFicha(1);
        tetrisFicha(4+random(2));
      }
      for (int num=11;num>=0;num--){
        pantalla2[num]=pantalla2[num-1];
      }
      for (int num=0;num<8;num++){
        pantalla[num]=pantalla2[num+4];
      }
      fotograma++;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}

void tetrisFicha(int px) {
  const byte tetris[7][4][4]={
   {  // cuadrdado                    
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000}, 
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B11000000,   
     B11000000,    
     B00000000,    
     B00000000}
  },
  {   // palo                   
    {B01000000,   
     B01000000,    
     B01000000,    
     B01000000},
    {B01000000,   
     B01000000,    
     B01000000,    
     B01000000}, 
    {B00000000,   
     B11110000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B01000000,    
     B01000000,    
     B01000000}
  },   
  {   // L                   
    {B10000000,   
     B10000000,    
     B11000000,    
     B00000000},
    {B11100000,   
     B10000000,    
     B00000000,    
     B00000000}, 
    {B11000000,   
     B01000000,    
     B01000000,    
     B00000000},
    {B00100000,   
     B11100000,    
     B00000000,    
     B00000000}
  },   
  {  //L invertida                    
    {B01000000,   
     B01000000,    
     B11000000,    
     B00000000},
    {B10000000,   
     B11100000,    
     B00000000,    
     B00000000}, 
    {B11000000,   
     B10000000,    
     B10000000,    
     B00000000},
    {B11100000,   
     B00100000,    
     B00000000,    
     B00000000}
  },   
  { // T                     
    {B01000000,   
     B11100000,    
     B00000000,    
     B00000000},
    {B10000000,   
     B11000000,    
     B10000000,    
     B00000000}, 
    {B11100000,   
     B01000000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B11000000,    
     B01000000,    
     B00000000}
  },   
  { // Z                      
    {B11000000,   
     B01100000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B11000000,    
     B10000000,    
     B00000000}, 
    {B11000000,   
     B01100000,    
     B00000000,    
     B00000000},
    {B01000000,   
     B11000000,    
     B10000000,    
     B00000000}
  },   
  { // Z invertida                     
    {B01100000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B10000000,   
     B11000000,    
     B01000000,    
     B00000000}, 
    {B01100000,   
     B11000000,    
     B00000000,    
     B00000000},
    {B10000000,   
     B11000000,    
     B01000000,    
     B00000000}  
  }
  };
  int ficha=random(6);
  int estado=random(3);
  int py=random(3);
  bool choca=false;
  /*for(int row=0;row<4;row++) {
    for(int col=0;col<4;col++) {
      if (bitRead(tetris[ficha][estado][row],7-col)) {
        if (bitRead(pantalla2[row+py],7-col-px)) { choca=true; }
      }
    }
  }*/
  if (!choca){
    for(int row=0;row<4;row++) {
      for(int col=0;col<4;col++) {
        if (bitRead(tetris[ficha][estado][row],7-col)) {
          bitWrite(pantalla2[row+py],7-col-px,true);//
        }
      }
    }
  }
}

void efectoAnimacionLlenaEsquinas() {
  const unsigned char animacion[31][8] = {
    { B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B11000000,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B11100000,B11100000,B11100000,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B11110000,B11110000,B11110000,B11110000,B00000000,B00000000,B00000000,B00000000},
    { B11111000,B11111000,B11111000,B11111000,B11111000,B00000000,B00000000,B00000000},
    { B11111100,B11111100,B11111100,B11111100,B11111100,B11111100,B00000000,B00000000},
    { B11111110,B11111110,B11111110,B11111110,B11111110,B11111110,B11111110,B00000000},
    { B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B01111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B00111111,B00111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B00011111,B00011111,B00011111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B00001111,B00001111,B00001111,B00001111,B11111111,B11111111,B11111111,B11111111},
    { B00000111,B00000111,B00000111,B00000111,B00000111,B11111111,B11111111,B11111111},
    { B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,B11111111,B11111111},
    { B00000001,B00000001,B00000001,B00000001,B00000001,B00000001,B00000001,B11111111},
    { B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B00000001,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B00000011,B00000011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B00000111,B00000111,B00000111,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B00001111,B00001111,B00001111,B00001111,B00000000,B00000000,B00000000,B00000000},
    { B00011111,B00011111,B00011111,B00011111,B00011111,B00000000,B00000000,B00000000},
    { B00111111,B00111111,B00111111,B00111111,B00111111,B00111111,B00000000,B00000000},
    { B01111111,B01111111,B01111111,B01111111,B01111111,B01111111,B01111111,B00000000},
    { B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B11111110,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B11111100,B11111100,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B11111000,B11111000,B11111000,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B11110000,B11110000,B11110000,B11110000,B11111111,B11111111,B11111111,B11111111},
    { B11100000,B11100000,B11100000,B11100000,B11100000,B11111111,B11111111,B11111111},
    { B11000000,B11000000,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111},
    { B10000000,B10000000,B10000000,B10000000,B10000000,B10000000,B10000000,B11111111},
  };
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<31){
    if (displayLedMatrix()){
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[fotograma][num];
      } fotograma++;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}

void efectoAnimacionOlas() {
  const unsigned char animacion[12][8] = {
    { B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111},
    { B00000000,B00000000,B00000000,B00000000,B00000000,B10000001,B11000011,B11111111},
    { B00000000,B00000000,B00000000,B10000001,B10000001,B11000011,B11100111,B11111111},
    { B00000000,B10000001,B10000001,B11000011,B11100111,B11111111,B11111111,B11111111},
    { B10000001,B10000001,B11000011,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B00000000,B10000001,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B00000000,B00011000,B01111110,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B00000000,B00000000,B00111100,B01111110,B01111110,B11111111,B11111111,B11111111},
    { B00000000,B00000000,B00000000,B00000000,B00111100,B01111110,B11111111,B11111111},
    { B00000000,B00000000,B00000000,B00000000,B00000000,B00011000,B00111100,B11111111},
    { B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00011000,B11111111},
    { B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B10101010},
  };
  byte cont=0;
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<12){
    if (displayLedMatrix()){
      if (fotograma==11 && cont<5 && random(2)>0) { fotograma=0; cont++; }
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[fotograma][num];
      } fotograma++;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}

void efectoAnimacionHelice() {
  const unsigned char animacion[10][8] = {
    { B10000001,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B10000001},
    { B01000010,B11000011,B00000000,B00000000,B00000000,B00000000,B11000011,B01000010},
    { B00100100,B00100100,B11100111,B00000000,B00000000,B11100111,B00100100,B00100100},
    { B00011000,B00011000,B00011000,B11111111,B11111111,B00011000,B00011000,B00011000},
    { B00110000,B00110000,B00011011,B00111111,B11111100,B11011000,B00001100,B00001100},//
    { B00100000,B01110010,B00011011,B00111110,B01111100,B11011000,B01001110,B00000100},
    { B00000010,B11110110,B01110110,B00011110,B01111000,B01101110,B01101111,B01000000},
    { B00000110,B11100110,B11110110,B00011100,B00111000,B01101111,B01100111,B01100000},
    { B00001100,B00001100,B11101100,B11111000,B00011111,B00110111,B00110000,B00110000},
    { B00011000,B00011000,B00011000,B11111111,B11111111,B00011000,B00011000,B00011000},//
  };
  byte cont=0;
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<10){
    if (displayLedMatrix()){
      if (fotograma==9 && cont<10 && random(3)>0) { fotograma=4; cont++; }
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[fotograma][num];
      } fotograma++;
    }
  } fotograma=3;
  while (fotograma>=0){
    if (displayLedMatrix()){
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[fotograma][num];
      } fotograma--;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}

void efectoAnimacionSnakes() {
  int posx=random(8); int posy=0;
  int incx=1-random(3); int incy=1;
  if (incx==0 && incy==0) { incx=1; }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<48){
    if (displayLedMatrix()){
      if (posx>7 || posy>7 || posx<0 || posy<0) {
        posx=random(8); posy=0;
        incx=1-random(3); incy=1;
        if (incx==0 && incy==0) { incx=1; }
      }
      bitWrite(pantalla[posy],posx,true);
      posx+=incx; posy+=incy;
      fotograma++;
    }
  } fotograma=0;
  incx=0; while (incx<8){ if (displayLedMatrix()){ pantalla[incx]=0; incx++; } }
}
/*
void efectoAnimacionSnakes() {
  int posx=random(8); int posy=random(8); bool choca=false;
  int incx=1-random(3); int incy=1-random(3);
  if (incx==0 && incy==0) { incx=1; }
  if (incx==1 && incy==1) { incx=0; }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (!choca){
    if (displayLedMatrix()){
       choca=bitRead(pantalla[posx],posy);
       if (posx>7 || posy>7 || posx<0 || posy<0 || choca) {
         posx=random(8); posy=random(8);
         incx=1-random(3); incy=1-random(3);
         if (incx==0 && incy==0) { incx=1; }
         if (incx==1 && incy==1) { incx=0; }
       }
       bitWrite(pantalla[posx],posy,true);
       posx+=incx; posy+=incy;
       fotograma++;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}*/

void efectoAnimacionOnda() {
  const unsigned char animacion[44][8] = {
    { B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000,B00000000},//
    { B00000000,B00000000,B00000000,B00000000,B00000011,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B00000111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B00001111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B00011111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B00111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B01111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000001,B11111110,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000010,B11111101,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000100,B11111010,B00000001,B00000001,B00000000},
    { B00000000,B00000000,B00000000,B00001000,B11110100,B00000010,B00000011,B00000000},
    { B00000000,B00000000,B00000000,B00010000,B11101001,B00000101,B00000110,B00000000},
    { B00000000,B00000000,B00000001,B00100001,B11010010,B00001010,B00001100,B00000000},
    { B00000001,B00000001,B00000010,B01000010,B10100100,B00010100,B00011000,B00000000},
    { B00000010,B00000010,B00000101,B10000101,B01001000,B00101000,B00110000,B00000000},
    { B00000100,B00000100,B00001010,B00001010,B10010001,B01010001,B01100000,B00000000},
    { B00001000,B00001000,B00010100,B00010100,B00100010,B10100010,B11000001,B00000001},
    { B00010000,B00010000,B00101000,B00101000,B01000101,B01000101,B10000010,B00000010},
    { B00100000,B00100000,B01010000,B01010001,B10001010,B10001010,B00000100,B00000100},
    { B01000000,B01000000,B10100001,B10100010,B00010100,B00010100,B00001000,B00001000},
    { B10000000,B10000000,B01000010,B01000101,B00101000,B00101000,B00010000,B00010000},
    { B00000000,B00000000,B10000100,B10001010,B01010001,B01010000,B00100000,B00100000},
    { B00000000,B00000000,B00001000,B00010101,B10100010,B10100000,B01000000,B01000000},
    { B00000000,B00000000,B00010000,B00101010,B01000101,B01000000,B10000000,B00000000},
    { B00000000,B00000000,B00100000,B01010100,B10001011,B10000000,B00000000,B00000000},
    { B00000000,B00000000,B01000000,B10101000,B00010111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B10000000,B01010000,B00101111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B10000000,B10100000,B01011111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B01000000,B10111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B10000000,B01111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111110,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111100,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11111000,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11110000,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11100000,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B11000000,B00000000,B00000000,B00000000},
    { B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,B00000000},
  };
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<44){
    if (displayLedMatrix()){
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[fotograma][num];
      } fotograma++;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}

void efectoAnimacionSaludo() {
  const unsigned char animacion[26][8] = {   
    { B00000001,B00000001,B00000001,B00000001,B00000001,B00000001,B00000001,B00000000},//textos
    { B00000010,B00000010,B00000010,B00000011,B00000010,B00000010,B00000010,B00000000},
    { B00000100,B00000100,B00000100,B00000111,B00000100,B00000100,B00000100,B00000000},
    { B00001001,B00001001,B00001001,B00001111,B00001001,B00001001,B00001001,B00000000},
    { B00010010,B00010010,B00010010,B00011110,B00010010,B00010010,B00010010,B00000000},
    { B00100100,B00100101,B00100101,B00111101,B00100101,B00100101,B00100100,B00000000},
    { B01001001,B01001010,B01001010,B01111010,B01001010,B01001010,B01001001,B00000000},
    { B10010011,B10010100,B10010100,B11110100,B10010100,B10010100,B10010011,B00000000},
    { B00100110,B00101001,B00101001,B11101001,B00101001,B00101001,B00100110,B00000000},
    { B01001100,B01010010,B01010010,B11010010,B01010010,B01010010,B01001100,B00000000},
    { B10011001,B10100101,B10100101,B10100101,B10100101,B10100101,B10011001,B00000000},
    { B00110010,B01001010,B01001010,B01001010,B01001010,B01001010,B00110011,B00000000},
    { B01100100,B10010100,B10010100,B10010100,B10010100,B10010100,B01100111,B00000000},
    { B11001000,B00101000,B00101000,B00101000,B00101000,B00101000,B11001110,B00000000},
    { B10010000,B01010001,B01010001,B01010001,B01010001,B01010001,B10011101,B00000000},
    { B00100001,B10100010,B10100010,B10100011,B10100010,B10100010,B00111010,B00000000},
    { B01000011,B01000100,B01000100,B01000111,B01000100,B01000100,B01110100,B00000000},
    { B10000110,B10001001,B10001001,B10001111,B10001001,B10001001,B11101001,B00000000},
    { B00001100,B00010010,B00010010,B00011110,B00010010,B00010010,B11010010,B00000000},
    { B00011000,B00100100,B00100100,B00111100,B00100100,B00100100,B10100100,B00000000},
    { B00110000,B01001000,B01001000,B01111000,B01001000,B01001000,B01001000,B00000000},
    { B01100000,B10010000,B10010000,B11110000,B10010000,B10010000,B10010000,B00000000},
    { B11000000,B00100000,B00100000,B11100000,B00100000,B00100000,B00100000,B00000000},
    { B10000000,B01000000,B01000000,B11000000,B01000000,B01000000,B01000000,B00000000},
    { B00000000,B10000000,B10000000,B10000000,B10000000,B10000000,B10000000,B00000000},
  };
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<26){
    if (displayLedMatrix()){
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[fotograma][num];
      } fotograma++;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}

void efectoAnimacionBarrotes() {
  const unsigned char animacion[15][8] = {   
    { B01010101,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B10101010},//
    { B01010101,B01010101,B00000000,B00000000,B00000000,B00000000,B10101010,B10101010},
    { B01010101,B01010101,B01010101,B00000000,B00000000,B10101010,B10101010,B10101010},
    { B01010101,B01010101,B01010101,B01010101,B10101010,B10101010,B10101010,B10101010},
    { B01010101,B01010101,B01010101,B11111111,B11111111,B10101010,B10101010,B10101010},
    { B01010101,B01010101,B11111111,B11111111,B11111111,B11111111,B10101010,B10101010},
    { B01010101,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B10101010},
    { B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
    { B10101010,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B01010101},
    { B10101010,B10101010,B11111111,B11111111,B11111111,B11111111,B01010101,B01010101},
    { B10101010,B10101010,B10101010,B11111111,B11111111,B01010101,B01010101,B01010101},
    { B10101010,B10101010,B10101010,B10101010,B01010101,B01010101,B01010101,B01010101},
    { B10101010,B10101010,B10101010,B00000000,B00000000,B01010101,B01010101,B01010101},
    { B10101010,B10101010,B00000000,B00000000,B00000000,B00000000,B01010101,B01010101},
    { B10101010,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01010101},
  };
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<15){
    if (displayLedMatrix()){
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[fotograma][num];
      } fotograma++;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}

void efectoPrueba() {
  const unsigned char animacion[10][8] = {
    { B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
    { B01000010,B11000011,B00000000,B00000000,B00000000,B00000000,B11000011,B01000010},
    { B00100100,B00100100,B11100111,B00000000,B00000000,B11100111,B00100100,B00100100},
    { B00011000,B00011000,B00011000,B11111111,B11111111,B00011000,B00011000,B00011000},
    { B00110000,B00110000,B00011011,B00111111,B11111100,B11011000,B00001100,B00001100},//
    { B00100000,B01110010,B00011011,B00111110,B01111100,B11011000,B01001110,B00000100},
    { B00000010,B11110110,B01110110,B00011110,B01111000,B01101110,B01101111,B01000000},
    { B00000110,B11100110,B11110110,B00011100,B00111000,B01101111,B01100111,B01100000},
    { B00001100,B00001100,B11101100,B11111000,B00011111,B00110111,B00110000,B00110000},
    { B00011000,B00011000,B00011000,B11111111,B11111111,B00011000,B00011000,B00011000},//
  };
  byte cont=0;
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
  while (fotograma<10){
    if (displayLedMatrix()){
      if (fotograma==9 && cont<10 && random(3)>0) { fotograma=4; cont++; }
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[0][num];
      } fotograma++;
    }
  } fotograma=3;
  while (fotograma>=0){
    if (displayLedMatrix()){
      for (int num=0;num<8;num++){
        pantalla[num]=animacion[0][num];
      } fotograma--;
    }
  } fotograma=0;
  while (!displayLedMatrix()){ }
  for (int num=0;num<8;num++){ pantalla[num]=0; } while (!displayLedMatrix()){ }
}
