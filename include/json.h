#pragma once
#include "nlohmann/json.hpp"

using nlohmann::json;

namespace bitcoin
{
  struct TransactionOutput {
    bool spent;
    unsigned long tx_index;
    int type;
    std::string addr;
    long value;
    int n;
    std::string script;
  };

  struct TransactionInput {
    unsigned long sequence;
    TransactionOutput prev_out;
    std::string script;
  };

  struct TransactionBody {
    unsigned long lock_time;
    int ver;
    unsigned long size;
    std::vector<TransactionInput> inputs;
    unsigned long time;
    unsigned long tx_index;
    int vin_sz;
    std::string hash;
    int vout_sz;
    std::string relayed_by;
    std::vector<TransactionOutput> out;
  };

  struct Transaction {
    std::string op;
    TransactionBody x;
  };

  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TransactionOutput, spent, tx_index, type, addr, value, n, script);
  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TransactionInput, sequence, prev_out, script);
  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TransactionBody, lock_time, ver, size, time, tx_index, vin_sz, hash, vout_sz, relayed_by, inputs, out);
  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Transaction, op, x);
} // namespace bitcoin
