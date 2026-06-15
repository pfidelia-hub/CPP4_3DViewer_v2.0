#include "gifmaker.h"

#include <QVector>

namespace s21 {

GifMakerBash::GifMakerBash() : GifMaker() {}

GifMakerBash *GifMakerBash::instance() {
  if (_instance == nullptr) {
    _instance = new GifMakerBash;
  }
  return _instance;
}

void GifMakerBash::instance_delete() {
  if (_instance != nullptr) {
    delete _instance;
    _instance = nullptr;
  }
}

void GifMakerBash::make_gif() { system("./script/gif.sh"); }

}  // namespace s21
