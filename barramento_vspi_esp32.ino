#include <SD.h>
#include <FS.h>
#include <SPI.h>
//HSPI Interface and VSPI Choose one from two interfaces 
//#define hspi
#define vspi
#ifdef vspi
SPIClass sdSPI(VSPI);
#define SD_MISO 19
#define SD_MOSI 23
#define SD_SCLK 18
#define SD_CS 5

#endif
void SD_init();
 
void setup()
{
    
  Serial.begin(115200);
  delay(500);
#ifdef vspi 
  Serial.println(" Please insert the memory card ");
  delay(12000);
#endif 
  SD_init();// initialization SD function 

}
 
void loop() {
    
  // Print memory card information 
  Serial.printf(" The total size of the memory card is ： %lluMB \n", SD.cardSize() / (1024 * 1024)); // "/ (1024 * 1024)" Can be replaced by ">> 20"
  Serial.printf(" The total file system size is ： %lluB \n", SD.totalBytes());
  Serial.printf(" The file system used size is ： %lluB \n", SD.usedBytes());
  delay(5000);
}
 
 
void SD_init() {
    
  // Mount file system 
   sdSPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, sdSPI))
  {
    
    // if(!SD.begin()){
    
    Serial.println(" Memory card mount failed ");
    return;
  }
  uint8_t cardType = SD.cardType();
 
  if (cardType == CARD_NONE)
  {
    
    Serial.println(" No memory card connected ");
    return;
  }
  else if (cardType == CARD_MMC)
  {
    
    Serial.println(" Mounted MMC card ");
  }
  else if (cardType == CARD_SD)
  {
    
    Serial.println(" Mounted SDSC card ");
  }
  else if (cardType == CARD_SDHC)
  {
    
    Serial.println(" Mounted SDHC card ");
  }
  else
  {
    
    Serial.println(" An unknown memory card is mounted ");
  }
}
