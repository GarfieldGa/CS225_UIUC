#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base; base.readFromFile("tests/expected.png");
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(base, 5);
  sheet.addSticker(i, 200, 200);
  sheet.addSticker(i, 500, 200);
  sheet.addSticker(alma, 0, 500);

  Image result = sheet.render();
  result.writeToFile("myImage.png");

  return 0;
}
