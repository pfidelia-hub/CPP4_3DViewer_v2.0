#pragma once

namespace s21 {

class GifMaker {
 public:
  GifMaker() {}
  virtual ~GifMaker() {}

  virtual void make_gif() = 0;
};

class GifMakerBash : public GifMaker {
  static inline GifMakerBash *_instance = nullptr;

  GifMakerBash();
  virtual ~GifMakerBash() {}

 public:
  static GifMakerBash *instance();
  static void instance_delete();
  void make_gif() override;
};

}  //  namespace s21
