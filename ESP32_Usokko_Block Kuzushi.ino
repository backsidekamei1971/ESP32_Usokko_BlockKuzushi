#include <SPI.h>
#include <ILI9486_SPI.h>
#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen.h>

#define TFT_CS       5    // CS
#define TFT_RST      27   // Reset 
#define TFT_DC       26   // DC
#define TFT_MOSI     23   // MOSI
#define TFT_SCK      18   // Clock

const int potPin=34;
int potValue = 0;

#define ILI9488_BLACK     (0x0000)
#define ILI9488_WHITE     (0xFFFF)
#define ILI9488_RED       (0xF800)
#define ILI9488_GREEN     (0x07E0)
#define ILI9488_BLUE      (0x001F)
#define ILI9488_CYAN      (0x07FF)
#define ILI9488_MAGENTA   (0xF81F)
#define ILI9488_YELLOW    (0xFFE0)
#define ILI9488_ORANGE    (0xFC00)

ILI9486_SPI tft(TFT_CS, TFT_DC, TFT_RST);

int posx=50;
int posy=90;
int dx=5;
int dy=5;

void setup(void)
{
  //SPIピン設定
  SPI.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS); 

  //TFTの初期化と初期設定
  tft.setSpiKludge(false);              // false to disable rpi_spi16_mode
  tft.init();

  tft.fillScreen(ILI9488_BLACK);        //背景の塗りつぶし

  //テキスト表示
  tft.setRotation(3);                         //画面回転
  tft.setTextSize(7);                         //サイズ

  tft.drawRect(0, 0, 110, 20, ILI9488_GREEN);
  tft.fillRect(0, 0, 110, 20, ILI9488_GREEN);

  tft.drawRect(120, 0, 110, 20, ILI9488_GREEN);
  tft.fillRect(120, 0, 110, 20, ILI9488_GREEN);

  tft.drawRect(240, 0, 110, 20, ILI9488_GREEN);
  tft.fillRect(240, 0, 110, 20, ILI9488_GREEN);

  tft.drawRect(360, 0, 110, 20, ILI9488_GREEN);
  tft.fillRect(360, 0, 110, 20, ILI9488_GREEN);

//2nd row block//
  tft.drawRect(0, 30, 110, 20, ILI9488_GREEN);
  tft.fillRect(0, 30, 110, 20, ILI9488_ORANGE);

  tft.drawRect(120, 30, 110, 20, ILI9488_GREEN);
  tft.fillRect(120, 30, 110, 20, ILI9488_ORANGE);

  tft.drawRect(240, 30, 110, 20, ILI9488_GREEN);
  tft.fillRect(240, 30, 110, 20, ILI9488_ORANGE);

  tft.drawRect(360, 30, 110, 20, ILI9488_GREEN);
  tft.fillRect(360, 30, 110, 20, ILI9488_ORANGE);

  //3rd row block//
  tft.drawRect(0, 60, 110, 20, ILI9488_GREEN);
  tft.fillRect(0, 60, 110, 20, ILI9488_MAGENTA);

  tft.drawRect(120, 60, 110, 20, ILI9488_GREEN);
  tft.fillRect(120, 60, 110, 20, ILI9488_MAGENTA);

  tft.drawRect(240, 60, 110, 20, ILI9488_GREEN);
  tft.fillRect(240, 60, 110, 20, ILI9488_MAGENTA);

  tft.drawRect(360, 60, 110, 20, ILI9488_GREEN);
  tft.fillRect(360, 60, 110, 20, ILI9488_MAGENTA);


  //tft.setCursor(0, 90);                       //カーソル位置                      
  //tft.setTextColor(ILI9488_GREEN);             //緑
  //tft.printf("TAMANEGI\n");

  //tft.setTextSize(4);                         //サイズ
  //tft.setTextColor(ILI9488_ORANGE);               //赤
  //tft.printf("4.0inch LCD\n");
  //tft.setTextColor(ILI9488_GREEN);            //黄
  //tft.printf("ILI9488\n");

  Serial.begin(9600);

}

void loop(void)
{

  potValue = analogRead(potPin);
 
  Serial.print("PotValue");
  Serial.println(potValue);
  
  //tft.setCursor(0, 210);
  //tft.setTextColor(ILI9488_YELLOW); 
  //tft.print("PotValue ");
  //tft.setTextColor(ILI9488_WHITE); 
  //tft.println(potValue);

  
  //delay(150);

  //tft.setCursor(0, 210);
  //tft.setTextColor(ILI9488_BLACK); 
  //tft.print("PotValue ");
  //tft.println(potValue);


  //delay(1);

  posx=posx+dx;
  posy=posy+dy;

  if (posx>=460 or posx<=0){  //Tate limit
    dx=-dx;
  }

  if (posy>=260 or posy<=80){  //Tate limit
    dy=-dy;
  }

  tft.drawRect(potValue/11, 270, 100, 15, ILI9488_WHITE);  //bar
  tft.fillRect(potValue/11, 270, 100, 15, ILI9488_WHITE);  //bar
  tft.fillRect(posx,posy,15,15,ILI9488_WHITE);    //ball
  delay(150);
  tft.fillRect(posx,posy,15,15,ILI9488_BLACK);    //ball
  tft.drawRect(potValue/11, 270, 100, 15, ILI9488_BLACK);  //bar
  tft.fillRect(potValue/11, 270, 100, 15, ILI9488_BLACK);  //bar

  if (posx>=(potValue/11) and posx <=(potValue/11)+100 and 250<=posy){
    tft.setTextSize(3);
    tft.setCursor((potValue/11), 90);
    tft.setTextColor(ILI9488_WHITE);
    tft.print("HIT!");
    delay(100);
    tft.setCursor((potValue/11), 90);
    tft.setTextColor(ILI9488_BLACK);
    tft.print("HIT!");
  }
    
  if ((posx<=(potValue/11) and 250<=posy) or (posx>=(potValue/11)+100 and 250<=posy)){
    tft.setTextSize(3);
    tft.setCursor((potValue/11), 90);
    tft.setTextColor(ILI9488_WHITE);
    tft.print("MISS!");
    delay(100);
    tft.setCursor((potValue/11), 90);
    tft.setTextColor(ILI9488_BLACK);
    tft.print("MISS!");
  }

  if (350<=posx and 80>=posy){
      tft.fillRect(360, 60, 110, 20, ILI9488_BLACK);
  }
  if (350>= posx and 80>=posy and 240<=posx and 80>=posy){
      tft.fillRect(240, 60, 110, 20, ILI9488_BLACK);
  }
  if (110>= posx and 80>=posy and 0<=posx and 80>=posy){
     tft.fillRect(0, 60, 110, 20, ILI9488_BLACK);
  }
  if (240>= posx and 80>=posy and 120<=posx and 80>=posy){
    tft.fillRect(120, 60, 110, 20, ILI9488_BLACK);
  }

}

