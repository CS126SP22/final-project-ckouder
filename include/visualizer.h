#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "engine.h"
#include "renderables.h"
#include "config.h"
#include "json.h"

using cinder::app::MouseEvent;
using glm::ivec2;

namespace bitcoin
{

enum TransactionType {
  INPUT,
  OUTPUT,
  MIXED,
  TRANSACTION
};

struct TransactionObject {
  std::string from = "";
  std::string to = "";
  int value = 0;
  TransactionType type = TRANSACTION;
  Box* mass = nullptr;

  TransactionObject () {};
  TransactionObject(
    TransactionType type, std::string from, std::string to, int value
    ) : from(from), to(to), value(value), type(type) {};
};

class BitcoinApp : public ci::app::App {
 public:
  BitcoinApp();

  void draw() override;
  void update() override;
  void mouseDown(MouseEvent event) override;
  void mouseDrag(MouseEvent event) override;
  void mouseMove(MouseEvent event) override;
  void mouseWheel(MouseEvent event) override;

 private:
  const int kTolerance = 30;
  const int kWindowHeight = WINDOW_HEIGHT;
  const int kWindowWidth = WINDOW_WIDTH;
  const ci::Color kFrameColor = ci::Color(FRAME_COLOR);
  const ci::Color kBackgroundColor = ci::Color(BACKGROUND_COLOR);
  Engine engine_ = Engine();
  std::map<std::string, TransactionObject*> transaction_map_;
  std::vector<String*> links_;
  std::string address_string_ = "";
  std::string balance_string_ = "";
  ivec2 drag_acc_ = vec2(0);
  ivec2 drag_ = vec2(0);

  TransactionObject* FindNodeAt(const vec2 &);
  ivec2 GetRealShapePos(const ivec2 &);
  void AddTransaction(Transaction);
  String* AddLink(Shape*, Shape*);
  Box* CreateMassFor(TransactionObject*);
};

} // namespace bitcoin
