#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace bitcoin_transaction_visualizer
{

class BitcoinTransactionVisualizer : public ci::app::App {
 public:
  BitcoinTransactionVisualizer();

  void draw() override;
  void update() override;
}

} // namespace bitcoin_transaction_visualizer
