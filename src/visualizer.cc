#include "visualizer.h"
#include "renderables.h"
#include "engine.h"
#include "mass.h"
#include "nlohmann/json.hpp"
#include <sstream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

#define TRANSACTION_COLOR "blue"
#define OUTPUT_COLOR "green"
#define INPUT_COLOR "red"
#define MIXED_COLOR "yellow"

namespace bitcoin {
  BitcoinApp::BitcoinApp() {
    ci::app::setWindowSize(kWindowHeight, kWindowWidth);
    json j = 
    "{"
      "\"op\": \"utx\","
      "\"x\": {"
      "  \"lock_time\": 0,"
      "  \"ver\": 1,"
      "  \"size\": 192,"
      "  \"inputs\": ["
      "    {"
      "      \"sequence\": 4294967295,"
      "      \"prev_out\": {"
      "        \"spent\": true,"
      "        \"tx_index\": 99005468,"
      "        \"type\": 0,"
      "        \"addr\": \"1BwGf3z7n2fHk6NoVJNkV32qwyAYsMhkWf\","
      "        \"value\": 65574000,"
      "        \"n\": 0,"
      "        \"script\": \"76a91477f4c9ee75e449a74c21a4decfb50519cbc245b388ac\""
      "      },"
      "      \"script\": \"483045022100e4ff962c292705f051c2c2fc519fa775a4d8955bce1a3e29884b2785277999ed02200b537ebd22a9f25fbbbcc9113c69c1389400703ef2017d80959ef0f1d685756c012102618e08e0c8fd4c5fe539184a30fe35a2f5fccf7ad62054cad29360d871f8187d\""
      "    }"
      "  ],"
      "  \"time\": 1440086763,"
      "  \"tx_index\": 99006637,"
      "  \"vin_sz\": 1,"
      "  \"hash\": \"0857b9de1884eec314ecf67c040a2657b8e083e1f95e31d0b5ba3d328841fc7f\","
      "  \"vout_sz\": 1,"
      "  \"relayed_by\": \"127.0.0.1\","
      "  \"out\": ["
      "    {"
      "      \"spent\": false,"
      "      \"tx_index\": 99006637,"
      "      \"type\": 0,"
      "      \"addr\": \"1A828tTnkVFJfSvLCqF42ohZ51ksS3jJgX\","
      "      \"value\": 65564000,"
      "      \"n\": 0,"
      "      \"script\": \"76a914640cfdf7b79d94d1c980133e3587bd6053f091f388ac\""
      "    }"
      "  ]"
      "}"
    "}"_json;
    FrictionForceConfig config(0.5);
    engine_.AddForce(&config);

    try
    {
        // Check command line arguments.
        std::string host = "ws.blockchain.info";
        auto const  text = "{\"op\": \"unconfirmed_sub\"}";

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};

        // Look up the domain name
        auto const results = resolver.resolve(host);

        // Make the connection on the IP address we get from a lookup
        auto ep = net::connect(ws.next_layer(), results);

        // Update the host_ string. This will provide the value of the
        // Host HTTP header during the WebSocket handshake.
        // See https://tools.ietf.org/html/rfc7230#section-5.4
        host += ':' + std::to_string(ep.port());

        // Set a decorator to change the User-Agent of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

        // Perform the websocket handshake
        ws.handshake(host, "/inv");

        // Send the message
        ws.write(net::buffer(std::string(text)));

        // This buffer will hold the incoming message
        beast::flat_buffer buffer;

        // Read a message into our buffer
        ws.read(buffer);

        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);

        // If we get here then the connection is closed gracefully

        // The make_printable() function helps print a ConstBufferSequence
        std::cout << beast::make_printable(buffer.data()) << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Transaction p1 = j.get<Transaction>();
    AddTransaction(p1);
  }

  void BitcoinApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    for (auto transaction : transaction_map_) {
      transaction.second->mass->Render(drag_acc_);
    }
    for (auto link : links_) {
      link->Render(drag_acc_);
    }
    ci::gl::drawString(address_string_, vec2(20, 20));
    ci::gl::drawString(balance_string_, vec2(20, 40));
  }

  void BitcoinApp::update() {
    engine_.Compute();
  }

  void BitcoinApp::mouseDown(MouseEvent event) {
    TransactionObject* target = FindNodeAt(GetRealShapePos(event.getPos()));
    if (target != nullptr && event.isLeft()) {
      std::stringstream s, d;
      s << "Address: " << target->from << std::endl;
      d << "\n Balance: " << target->value << std::endl;
      address_string_ = s.str();
      balance_string_ = d.str();
      target->mass->status = FREEZED;

    } else if (event.isRight()) {
      address_string_ = "";
      balance_string_ = "";
      for (auto transaction : transaction_map_) {
        transaction.second->mass->status = ACTIVE;
      }
    }
  }

  void BitcoinApp::mouseMove(MouseEvent event) {
    drag_ = event.getPos();
  }

  void BitcoinApp::mouseDrag(MouseEvent event) {
    TransactionObject* target = FindNodeAt(GetRealShapePos(event.getPos()));
    if (target != nullptr) {
      target->mass->status = FREEZED;
      target->mass->position = GetRealShapePos(event.getPos());
    } else {
      drag_acc_ += event.getPos() - drag_;
      drag_ = event.getPos();
    }
  }

  void BitcoinApp::mouseWheel(MouseEvent event) {
    // scale view
  }

  TransactionObject* BitcoinApp::FindNodeAt(const vec2 & coordinate) {
    for (auto object : transaction_map_) {
      if (glm::length(coordinate - object.second->mass->position) <= kTolerance) {
        return object.second;
      }
    }
    return nullptr;
  }

  ivec2 BitcoinApp::GetRealShapePos(const ivec2 & position) {
    return position - drag_acc_;
  }

  void BitcoinApp::AddTransaction(Transaction transaction) {
    // Add transaction data
    TransactionObject* tx_obj = new TransactionObject();
    transaction_map_.emplace(transaction.x.hash, tx_obj);
    CreateMassFor(tx_obj);

    // Add Input Data
    for (TransactionInput input : transaction.x.inputs) {
      auto ptr = transaction_map_.find(input.prev_out.addr);
      if (ptr != transaction_map_.end() && ptr->second->type == OUTPUT) {
        ptr->second->type = MIXED;
        CreateMassFor(ptr->second);
        AddLink(ptr->second->mass, tx_obj->mass);
      } else {
        TransactionObject* obj = new TransactionObject(
          INPUT, 
          input.prev_out.addr, 
          transaction.x.hash, 
          input.prev_out.value
        );
        transaction_map_.emplace(obj->from, obj);
        CreateMassFor(obj);
        AddLink(obj->mass, tx_obj->mass);
      }
    }

    // Add Output Data
    for (TransactionOutput output : transaction.x.out) {
      auto ptr = transaction_map_.find(output.addr);
      if (ptr != transaction_map_.end() && ptr->second->type == OUTPUT) {
        ptr->second->type = MIXED;
        CreateMassFor(ptr->second);
        AddLink(ptr->second->mass, tx_obj->mass);
      } else {
        TransactionObject* obj = new TransactionObject(
          OUTPUT,
          transaction.x.hash,
          output.addr,
          output.value
        );
        transaction_map_.emplace(obj->to, obj);
        CreateMassFor(obj);
        AddLink(obj->mass, tx_obj->mass);
      }
    }
  }

  Box* BitcoinApp::CreateMassFor(TransactionObject* obj) {
    if (obj->mass != nullptr && obj->type == MIXED) {
      obj->mass->color = ci::Color(MIXED_COLOR);
      return obj->mass;

    } else if (obj->mass == nullptr) {
      Box* x = new Box();
      x->position = vec2(kWindowWidth / 2, kWindowHeight / 2);
      switch (obj->type) {
        case INPUT:
          x->color = ci::Color(INPUT_COLOR);
          break;

        case OUTPUT:
          x->color = ci::Color(OUTPUT_COLOR);
          break;

        case TRANSACTION:
          x->color = ci::Color(TRANSACTION_COLOR);
          break;

        case MIXED:
          x->color = ci::Color(MIXED_COLOR);
          break;
      }
      obj->mass = x;
      engine_.AddMass(x);
      return x;
    }
    throw -1;
  }

  String* BitcoinApp::AddLink(Shape *from, Shape *to) {
    String *link = new String(from, to);
    links_.push_back(link);
    engine_.AddMass(link);
    return link;
  }
} // namespace bitcoin